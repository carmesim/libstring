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
#include <string.h>

/*
 * TODOs
 * invalid write on string_alloc, when writing to alloc_list_head->val->size and alloc_list_head->val->reserved
 */

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

    /* Portable and simple reimplementation of strlen
     * Does not totally conform to the C ISO standard, but is good enough for our uses.
     */
size_t __strlen(const char *s) {
    size_t i;
    for (i = 0; s[i] != '\0'; i++) ;
    return i;
}


struct alloc_node
{
    cstr_t            * val;
    struct alloc_node * next;
};

    /* We'll keep a simple linked list of heap allocations as to allow for string_free_all() */
struct alloc_node * alloc_list_head = NULL;

/*!
 * \brief Allocates memory for a cstr_t * and adds it to the allocation list.
 * \param nbytes The number of bytes to be allocated.
 */
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

/*!
 * \brief Frees all heap memory allocated by libstring.
 */
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

/* VRM: I've changed lower_case and upper_case
* to no longer return anything.
*/
/*!
 * \brief Alters a string to contain only lower case characters.
 * \param origin The cstr_t * to be altered.
 */
void string_to_lower_case(cstr_t * origin)
{
    size_t i;
    for(i=0; i<origin->size; i++)
    {
        if ((origin->value[i] >= 'A') && (origin->value[i] <= 'Z'))
        {
            origin->value[i] |= ' ';
        }
    }
}

/*!
 * \brief Alters a string to contain only lower case characters.
 * \param origin The cstr_t * to be altered.
 * Makes use of bit manipulation to alter the ASCII values.
 */
void string_to_upper_case(cstr_t * origin)
{
    size_t i;
    for(i=0; i<origin->size; i++)
    {
        if ((origin->value[i] >= 'a') && (origin->value[i] <= 'z'))
        {
            origin->value[i] &= '_';
        }
    }
}

cstr_t * string_init(const char * origin)
{
    cstr_t * new = string_alloc(__strlen(origin)+1);
    strncpy(new->value, origin, __strlen(origin));                   // TODO: change to string_copy
    return new;
}
