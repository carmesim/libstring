/*
 * libstring
 * https://github.com/carmesim/libstring
 *
 * Copyright (c) 2020 Vinícius R. Miguel, Ivan dos Santos Muniz
 * <vinicius.miguel at unifesp.br>
 * <ivan.muniz at unifesp.br>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "libstring.h"
#include <stdio.h>

//! **** Defining internal functions **** !//

//!
//! \brief __malloc Simple error-printing wrapper around malloc.
//! \param size     Quantity of memory to be allocated
//! \return         A pointer to the allocated memory.
//!
void * __malloc(size_t size)
{
    void * ptr = malloc(size);
    if(!ptr)
    {
        fprintf(stderr, "Fatal error: malloc failed.\n");
        // TODO: exit?
    }
    return ptr;
}

//!
//! \brief __strlen Portable and simple reimplementation of strlen
//! \param s        The NUL-terminated char array whose length will be calculated.
//! \return         The size of the given char array.
//!
size_t __strlen(const char *s)
{
    size_t i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

//!
//! \brief __memeq Compares two char arrays and returns true if they're equal on their first `size` elements.
//! \param str1    First char array
//! \param str2    Second char array
//! \param size    Number of elements to be compared
//! \return        Returns true if both char arrays are equal on their first `size` elements.
//! In short, __memeq(s1, s2, n) <-> !memcmp(s1, s2, n)
bool __memeq(char * str1, char * str2, size_t size)
{
    if (size)
    {
        char *pstr1 = str1, *pstr2 = str2;

        for(; size; --size)
        {
            if (*pstr1++ != *pstr2++)
            {
                return false;
            }
        }
    }
    return true;
}

//!
//! \brief __strstr Verifies if `find` is a substring within `str`.
//! \param str      A char array.
//! \param find     The possible substring within `str`.
//! \return         Returns NULL if `find` is not a substring of `str`.
//! This function does *not* verify if __strlen(find) > __strlen(str).
//!
char * __strstr(char * str, char *find)
{
    char c = *find++;
    if (c != '\0')
    {
        char sc;
        size_t len =__strlen(find);
        while(!__memeq(str, find, len))
        {
            for(sc = *str++; sc != c; sc = *str++)
                if (sc == '\0')
                {
                    return NULL;
                }
        }
        str--;
    }
    return str;
}

//!
//! \brief __memcpy  Simple implementation of memcpy. This implementation is specific to char arrays.
//! \param dest      The destination char array, whose contents will be written to src.
//! \param src       The source char array, where the contents of dest will be written to.
//! \param n         The quantity of elements to be copied.
//! \return          Returns the destination char array.
//!
char * __memcpy(char * dest, const char *src, size_t n) {
   while (n--)
   {
       *dest++ = *src++;
   }
   return dest;
}

//!
//! \brief __strcpy  A simple string copy function. It will always null-terminate the destination char array.
//! \param dest      Destination char array.
//! \param src       Source char array.
//! \param size      Quantitity of elements to be copied. It may be larger than __strlen(src), but the function will not write more than __strlen(src).
//!
void __strcpy(char *dest, const char *src, size_t size)
{
    if(!size)
    {
        fprintf(stderr, "__strcpy should not be called with size==0\n");
        return;
    }

    size_t source_len = __strlen(src);
    size_t n;

    if (size < source_len)    // Truncate to the size of the smaller string
    {
        n = size;
    } else
    {
        n = source_len;
    }

    __memcpy(dest, src, n);      // Copy the contents of src to dest
    dest[n] = '\0';              // Null-terminate dest.
}

/*!
 * \struct alloc_node A single node of the allocation linked list.
 * \param nbytes The number of bytes to be allocated.
 * \property val  A pointer to struct cstr.
 * \property next A pointer to the next node in the allocation list.
 */
struct alloc_node
{
    cstr_t            * val;
    struct alloc_node * next;
};

//! We keep a simple linked list of heap allocations as to allow for string_free_all()
struct alloc_node * alloc_list_head = NULL;

//!
//! \brief string_alloc Allocates memory for a cstr_t * and adds it to the allocation list.
//! \param nbytes       The number of bytes to be allocated.
//! \return             Returns a new cstr_t* allocated within the alloc. list.
//!
cstr_t * string_alloc (size_t nbytes)
{
    if (!alloc_list_head)   // If the list's head hasn't been initialized
    {
        alloc_list_head                = __malloc(sizeof(struct alloc_node));
        alloc_list_head->val           = __malloc(sizeof(struct cstr));
        alloc_list_head->val->value    = __malloc(nbytes * sizeof(char));
        alloc_list_head->val->size     = nbytes;
        alloc_list_head->val->reserved = nbytes;
        alloc_list_head->next          = NULL;
        return alloc_list_head->val;
    }

    struct alloc_node * current = alloc_list_head;
    while (current->next)
        current = current->next;

    current->next       = __malloc(sizeof(struct alloc_node));
    current->next->val  = __malloc(sizeof(struct cstr));
    current->next->val->value = __malloc(nbytes);
    current->next->val->size = nbytes;
    current->next->val->reserved = nbytes;
    current->next->next = NULL;
    return current->next->val;
}

//!
//! \brief string_free_all Frees all heap memory allocated by libstring.
//!
void string_free_all (void)
{
    struct alloc_node * current = alloc_list_head;
    while (current)
    {
        struct alloc_node * temp = current;
        current = current->next;
        free(temp->val->value);
        free(temp->val);
        free(temp);
    }
}

//!
//! \brief string_to_lower_case Alters a string to contain only lower-case characters.
//! \param origin               The string whose value will be converted to lower-case characters. This parameters does not get modified.
//! \return                     A brand new cstr_t * that contains the altered value.
//!
cstr_t * string_to_lower_case(cstr_t * origin)
{
    cstr_t* lower;
    lower = string_init(origin->value);
    __strcpy(lower->value, origin->value, origin->size);

    size_t i;
    for(i=0; i<lower->size; i++)
    {
        if ((lower->value[i] >= 'A') && (lower->value[i] <= 'Z'))
        {
            lower->value[i] |= ' ';
        }
    }
    return lower;
}

//!
//! \brief string_to_upper_case Alters a string to contain only upper-case characters.
//! \param origin               The string whose value will be converted to upper-case characters. This parameters does not get modified.
//! \return                     A brand new cstr_t * that contains the altered value.
//! Makes use of bit manipulation to alter the ASCII values.
//!
cstr_t * string_to_upper_case(cstr_t * origin)
{
    cstr_t* upper;
    upper = string_init(origin->value);
    __strcpy(upper->value, origin->value, origin->size);

    size_t i;
    for(i=0; i<upper->size; i++)
    {
        if ((upper->value[i] >= 'a') && (upper->value[i] <= 'z'))
        {
            upper->value[i] &= '_';
        }
    }
    return upper;
}

/*!
 * \brief  Initializes a new string, a poitner to cstr_t
 * \param  origin  The char array to be the value of the new string.
 * \retval upper   A brand new cstr_t *.
 * Adds to the allocation list.
 */
cstr_t * string_init(const char * origin)
{
    cstr_t * new = string_alloc(__strlen(origin)+1);
    __strcpy(new->value, origin, __strlen(origin));
    return new;
}

//!
//! \brief string_replace Replaces the value of an cstr_t *. Increases its memory reservation if needed.
//! \param str            The cstr_t * to be modified.
//! \param new_val        The new char array value.
//! \return               The new char array size.
//!
size_t string_replace(cstr_t * str, const char * new_val)
{
    size_t new_string_len = __strlen(new_val);
    if (new_string_len > str->reserved)
    {
        if (!string_reserve(str, new_string_len+1))
        {
            fprintf(stderr, "In string_replace: string_reserve(str, %zu) failed.", new_string_len+1);
            return 0;
        }
    }

    __strcpy(str->value, new_val, new_string_len);
    //printf("strlen: %zu, new_string_len: %zu\n", __strlen(str->value), new_string_len);
    str->size = new_string_len;
    return new_string_len;
}

//!
//! \brief string_contains
//! \param str1
//! \param str2
//! \return
//!
bool string_contains(cstr_t * str1, const char * str2)
{
    if (!str1)
    {
        fprintf(stderr, "In string_contains: `str1` unitialized.\n");
        return false;
    }

    if (str1->size < __strlen(str2))
    {
        //! str2 is bigger than str1, so it can't be a substring.
        return false;
    }

    if(__strstr(str1->value, (char *) str2))
    {
        return true;        // If __strstr returned a non-NULL pointer, str2 is a substring of str1.
    }
    return  false;
}

/*!
 * \brief  Initializes a new string, a poitner to cstr_t
 * \param  str       The cstr_t * whose capacity will be altered.
 * \param  capacity  The new memory reserve of the cstr_t *.
 * \retval bool    Returns true if the operation was succesful, false otherwise.
 */
bool string_reserve(cstr_t *str, size_t capacity)
{
    if (!str)
    {
        fprintf(stderr, "In string_reserve: string not initialized.\n");
        return false;
    }

    if (capacity < str->size)
    {
        //! TODO: Implement truncation?
        fprintf(stderr, "In string_reserve: new capacity supplied is smaller than the string's current size.\n");
        return false;
    }

    char * val_backup = __malloc(str->size + 1);
    str->value        = realloc(str->value, capacity);
    if(!str->value)
    {
        //! TODO: needs testing
        //! I couldn't get realloc to fail in order to test
        fprintf(stderr, "In string_reserve: reallocation failed with capacity %zu\n", capacity);
        str->value = val_backup;
        return false;
    }

        //! In this case, reallocation worked
    free (val_backup);      //! Get rid of the backup
    str->reserved = capacity;
    return true;
}

//!
//! \brief string_replace_char Replaces all instances of `before` in str to `after`.
//! \param str                 The cstr_t * to be altered.
//! \param before              The char to be replaced by `after`.
//! \param after               The char to replace `before`.
//! \return                    The quantity of changed characters.
//!
//! TODO: should this function return a copy and maintain the original untouched?
//!
size_t string_replace_char(cstr_t *str, char before, char after)
{
    if(!str)
    {
        fprintf(stderr, "In string_replace_char: str is uninitialized.\n");
        return 0;
    }

    size_t i, modified = 0;

    size_t str_len = __strlen(str->value);  // TODO: I'm doing this because I think size is sometimes is counting the NUL character. FIXME

    for(i=0; i < str_len; i++)
    {
        if(str->value[i] == before)
        {
            str->value[i] = after;
            modified++;
        }
    }
    return modified;
}


//!
//! \brief string_swap Swaps the content of str1 with str2.
//! \param str1        An initialized cstr_t *.
//! \param str2        An initialized cstr_t *.
//! \return A success-run boolean.
//!
bool string_swap(cstr_t * str1, cstr_t * str2)
{
    if (!str1)
    {
        fprintf(stderr, "In string_swap: str1 uninitialized.\n");
        return false;
    }
    if (!str2)
    {
        fprintf(stderr, "In string_swap: str2 unitialized.\n");
        return false;
    }

    size_t str1_val_size   = str1->size;
    char * str1_val_backup = malloc(str1_val_size + 1);
    if(!str1_val_backup)
    {
        fprintf(stderr, "In string_swap: malloc failed.\n");
        return false;
    }

    __strcpy(str1_val_backup, str1->value, str1_val_size);
    size_t str1_res_backup = str1->reserved;
    free(str1->value);
    str1->value    = str2->value;
    str1->size     = str2->size;
    str1->reserved = str2->reserved;

    str2->value    = str1_val_backup;
    str2->size     = str1_val_size;
    str2->reserved = str1_res_backup;

    return true;
}
