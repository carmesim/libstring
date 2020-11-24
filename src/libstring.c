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

#ifdef __STDC_VERSION__
#   define LIBSTRING_INLINE inline
#else
#   define LIBSTRING_INLINE
#endif

//! **** Defining internal functions **** !//

//!
//! \brief __malloc Simple error-printing wrapper around malloc.
//! \param size     Quantity of memory to be allocated
//! \return         A pointer to the allocated memory.
//!
static void * __malloc(size_t size)
{
    void * ptr = malloc(size);
    if(!ptr)
    {
        fprintf(stderr, "Fatal error: malloc failed!\n");
        // TODO: exit?
    }
    return ptr;
}

//!
//! \brief __strlen Portable and simple reimplementation of strlen
//! \param s        The NUL-terminated char array whose length will be calculated.
//! \return         The size of the given char array.
//!
static size_t __strlen(const char *s)
{/*
    if (s[0] == '\0')
    {
        return 0;
    }*/
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
static bool __memeq(char * str1, char * str2, size_t size)
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
static char * __strstr(char * str, char *find)
{
    char c = *find++;
    if (c != '\0')
    {
        char sc;
        size_t len =__strlen(find);
        do
        {
            for(sc = *str++; sc != c; sc = *str++)
            {
                if (sc == '\0')
                {
                    return NULL;
                }
            }
        } while(!__memeq(str, find, len));
        str--;
    }
    return str;
}

//!
//! \brief __strtok
//! \param str
//! \param delim
//! \return
//! Based on a version of strtok by Chris Dodd.
//! Update: this should be reentrant/safer now.
//! Note: this *will* modify `str`. Duplicate the string before usage.
static char * __strtok(char *str, char *delim, char ** prev)
{
    if (!str)
    {
        str = *prev;
    }
    if (str)
    {
        char *end = __strstr(str, delim);
        if (end)
        {
            *prev = end + __strlen(delim);
            *end = 0;
        } else
        {
            *prev = 0;
        }
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
static LIBSTRING_INLINE char * __memcpy(char * dest, const char *src, size_t n) {
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
static size_t __strcpy(char *dest, const char *src, size_t size)
{
    if (!dest || !src)
    {
        return 0;
    }

    if(!size)
    {
        fprintf(stderr, "In __strcpy: `size` should not be 0.\n");
        return 0;
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
    return source_len;
}

static size_t __strncat(char *dest, const char *src, size_t size)
{
    size_t dest_len = __strlen(dest);
    if (dest_len < size)
    {
        return(dest_len + __strcpy(dest + dest_len, src, size - dest_len));
    }
    return(dest_len + __strlen(src));
}

//!
//! \brief __cstr_min Quick internal implementation of a min function for size_t.
//! \param x One of the elements to be compared.
//! \param y The other element to be compared.
//! \return The lesser element.
//!
static LIBSTRING_INLINE size_t __cstr_min(size_t x, size_t y)
{
    if (x < y)
        return x;
    else
        return y;
}

//!
//! \brief __cstr_max Quick internal implementation of a max function for size_t.
//! \param x One of the elements to be compared.
//! \param y The other element to be compared.
//! \return The greater element.
//!
//static size_t __cstr_max(size_t x, size_t y)
//{
//    if (x > y)
//        return x;
//    else
//        return y;
//}

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
        alloc_list_head->val->value    = __malloc(nbytes + 1);
        alloc_list_head->val->size     = nbytes-1;  //! Remove one from nbytes because it includes the NULL-terminator.
        alloc_list_head->val->reserved = nbytes;
        alloc_list_head->next          = NULL;
        return alloc_list_head->val;
    }

    struct alloc_node * current = alloc_list_head;
    while (current->next)
        current = current->next;

    current->next       = __malloc(sizeof(struct alloc_node));
    current->next->val  = __malloc(sizeof(struct cstr));
    current->next->val->value = __malloc(nbytes + 1);
    current->next->val->size = nbytes-1;
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
    current = NULL;
    alloc_list_head = NULL;
}

static char * __strtok_wrapper(char *str, char *delim)
{
    static char *last;
    return __strtok(str, delim, &last);
}

bool sanity_check(cstr_t * str)
{
    if (!str)
    {
        fprintf(stderr, "In sanity_check: the given string is NULL.\n");
        return false;
    }

    if (str->size > str->reserved)
    {
        //! str->size would only be bigger than str->reserved
        //! if str is uninitialized
        fprintf(stderr, "In sanity_check: the given string is probably not initialized.\n");
        return false;
    }

    return true;
}

LIBSTRING_INLINE char * string_first_token(char * str, char * delim)
{
    return __strtok_wrapper(str, delim);
}

LIBSTRING_INLINE char * string_get_token(char * delim)
{
    return __strtok_wrapper(NULL, delim);
}

//!
//! \brief string_to_lower_case Alters a string to contain only lower-case characters.
//! \param origin               The string whose value will be converted to lower-case characters. This parameters does not get modified.
//! \return                     A brand new cstr_t * that contains the altered value.
//!
cstr_t * string_to_lower_case(cstr_t * origin)
{
    if (!sanity_check(origin))
    {
        fprintf(stderr, "In string_to_lower_case: sanity check on `origin` failed.\n");
        return string_init("");
    }

    cstr_t* lower = string_init(origin->value);
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
    if (!sanity_check(origin))
    {
        fprintf(stderr, "In string_to_lower_case: sanity check on `origin` failed.\n");
        return string_init("");
    }

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


//!
//! \brief __strset
//! \param dest
//! \param ch
//! \param n
//! \return
//!
void * __strset(char * dest, char ch, size_t n)
{
    if (n) {
        char *d = dest;
        do {
            *d++ = ch;
        } while (--n);
    }
    return dest;
}

char * __strcat(char *dst, const char *src)
 {
     char *ret = dst;

     for (; *dst; ++dst);
     while ((*dst++ = *src++) != '\0');
     return ret;
}

// TODO: change to use __strcpy
static char * __strlcpy(char *dst, const char *src)
{
    char *save = dst;
    for (; (*dst = *src) != '\0'; ++src, ++dst);
    return save;
}

void string_replace(cstr_t * str, char * old_val, const char * new_val)
{
    // TODO: check for overflows here

    if (!sanity_check(str))
    {
        fprintf(stderr, "In string_replace: sanity check on `str` failed.\n");
        return;
    }

    char * src = str->value;
    char *p = __strstr(src, old_val);
    do
    {
        if(p)   // If the substring was found
        {
            char buf[1024] = {'\0'};

            if(src == p)
            {
                __strlcpy(buf,new_val);
                __strcat(buf,p+__strlen(old_val));
            }
            else
            {
                __strcpy(buf,src,__strlen(src) - __strlen(p));
                __strcat(buf,new_val);
                __strcat(buf,p+__strlen(old_val));
            }

            __strset(src,'\0', __strlen(src));
            __strlcpy(src, buf);
        }

    }while(p && (p = __strstr(src, old_val)));
}

//!
//! \brief string_init Initializes a new cstr_t *.
//! \param origin      The char array to be the value of the new string.
//! \return            A brand new cstr_t *.
//!
cstr_t * string_init(const char * origin)
{
    if (!origin || origin[0] == '\0')
    {
        cstr_t * new = string_alloc(1);
        new->value[0] = '\0';
        return new;
    }
    cstr_t * new = string_alloc(__strlen(origin)+1);
    __strcpy(new->value, origin, __strlen(origin));
    return new;
}

//!
//! \brief string_update  Updates the value of an cstr_t *. Increases its memory reservation if needed.
//! \param str            The cstr_t * to be modified.
//! \param new_val        The new char array value.
//! \return               The new string's size.
//!
size_t string_update(cstr_t * str, const char * new_val)
{
    if(!sanity_check(str))
    {
        fprintf(stderr, "In string_update: sanity check on `str` failed.\n");
    }

    if (!new_val)
    {
        return 0;
    }

    size_t new_string_len = new_val[0] == '\0' ? 0 : __strlen(new_val);
    if (new_string_len > str->reserved)
    {
        if (!string_reserve(str, new_string_len+1))
        {
            fprintf(stderr, "In string_replace: string_reserve(str, %zu) failed.", new_string_len+1);
            return 0;
        }
    }

    if (new_val[0] == '\0')
    {
        str->value[0] = '\0';
    } else {
        __strcpy(str->value, new_val, new_string_len);
    }
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
    if (!sanity_check(str1))
    {
        fprintf(stderr, "In string_contains: sanity check on `str1` failed.\n");
        return false;
    }

    if (str1->size < __strlen(str2))
    {
        //! str2 is bigger than str1, so it can't be a substring.
        return false;
    }

    if(__strstr(str1->value, (char *) str2))
    {
        // If __strstr returned a non-NULL pointer, str2 is a substring of str1.
        return true;
    }

    return  false;
}

/*!
 * \brief  Initializes a new string, a pointer to cstr_t
 * \param  str       The cstr_t * whose capacity will be altered.
 * \param  capacity  The new memory reserve of the cstr_t *.
 * \retval bool    Returns true if the operation was succesful, false otherwise.
 */
bool string_reserve(cstr_t *str, size_t capacity)
{
    if (!sanity_check(str))
    {
        fprintf(stderr, "In string_reserve: sanity check on `str` failed.\n");
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
//! \brief string_concat_to Concatenates a string str2 to str1.
//! \param str1 The cstr_t * to where str2 will be concatenated to.
//! \param str2 The string that will be concatenated to str1.
//! \return The new size of the resulting cstr_t *.
//!
size_t string_concat_to(cstr_t * str1, const char * str2)
{
    if (!sanity_check(str1))
    {
        fprintf(stderr, "In string_concat_to: sanity check on `str1` failed.\n");
        return 0;
    }

    size_t str2len = __strlen(str2);

    if(!str2len) {
        return 0;
    }

    if(str1->reserved < str1->size + str2len + 1)
    {
        if(!string_reserve(str1, str1->size + str2len + 1))
        {
            fprintf(stderr, "In string_concat_to: string_reserve failed.\n");
            return 0;
        }
    }

    str1->size += str2len;
    __strncat(str1->value, str2, str1->size);
    return str2len;
}

//!
//! \brief string_concat Concatenates str2 to str1 and returns that value into a new cstr_t *.
//! \param str1          The value to where str2 will be concatenated to. The function does not alter str1.
//! \param str2          The string that will be concatenated to str1.
//! \return              A new value containing str1 + str2
//!
cstr_t * string_concat(cstr_t * str1, const char * str2)
{
    if (!sanity_check(str1))
    {
        fprintf(stderr, "In string_concat: sanity check on `str1` failed.\n");
        return 0;
    }
    cstr_t * new = string_init(str1->value);

    size_t str2len = __strlen(str2);
    if(new->reserved < str1->size + str2len + 1)
    {
        if(!string_reserve(new, new->size + str2len + 1))
        {
            fprintf(stderr, "In string_concat: string_reserve failed.\n");
            return new;
        }
    }
    new->size = str1->size + str2len;
    __strncat(new->value, str2, new->size);
    return new;
}

//!
//! \brief string_replace_char Replaces all instances of `before` in str to `after`.
//! \param str                 The cstr_t * to be altered.
//! \param before              The char to be replaced by `after`.
//! \param after               The char to replace `before`.
//! \return                    The quantity of changed characters.
//!
//! TODO: make string_replace_char_to
//!
size_t string_replace_char(cstr_t *str, char before, char after)
{
    if(!sanity_check(str))
    {
        fprintf(stderr, "In string_replace_char: sanity  check on `str` failed.\n");
        return 0;
    }

    size_t i, modified = 0;

    for(i=0; i < str->size; i++)
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
    if (!sanity_check(str1))
    {
        fprintf(stderr, "In string_swap: sanity check on `str1` failed.\n");
        return false;
    }
    if (!sanity_check(str2))
    {
        fprintf(stderr, "In string_swap: sanity check on `str2` failed.\n");
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

//!
//! \brief string_mid Returns a substring of a given string starting at position pos with a given length.
//! \param str Source string for the substring.
//! \param pos Position of the starting character.
//! \param length Desired length of the substring. -1 for everything after pos.
//! \return Generated substring.
//!
cstr_t * string_mid(cstr_t *str, size_t pos, long length)
{
    if (!sanity_check(str))
    {
        fprintf(stderr, "In string_mid: sanity check on `str` failed.\n");
        return 0;
    }

    if (str->size <= pos || str->size == 0 || (length < 1 && length != -1))
    {
        return string_init("");
    }

    size_t stop_element;

    if (length == -1)
        stop_element = str->size;
    else
        stop_element = __cstr_min(str->size, pos + (size_t) length);

    cstr_t *result = string_init("\0");
    string_reserve(result, stop_element - pos + 1);

    __strcpy(result->value, &str->value[pos], stop_element - pos);

    return result;
}

//!
//! \brief string_left Returns the first (length) characters of a string starting from the left.
//! \param str Source string for the substring.
//! \param length Amount of characters desired.
//! \return Generated substring.
//!
LIBSTRING_INLINE cstr_t * string_left(cstr_t *str, long length)
{
    return string_mid(str, 0, (long) length);
}

//!
//! \brief string_left Returns the first (length) characters of a string starting from the right.
//! \param str Source string for the substring.
//! \param length Amount of characters desired.
//! \return Generated substring.
//!
cstr_t * string_right(cstr_t *str, long length)
{
    size_t start_pos;
    if ((unsigned) length >= str->size)
    {
        start_pos = 0;
    }
    else
    {
        start_pos = str->size - length;
    }

    return string_mid(str, start_pos, -1);
}
