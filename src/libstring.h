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

    /* Type definitions */

#ifndef LIBSTRING_H
#define LIBSTRING_H

#include <stdlib.h>

#ifdef __STDC_VERSION__
#   include <stdbool.h>
#else
    typedef enum { false, true,} bool;
#endif

struct cstr
{
    char * value;
    size_t size;
    size_t reserved;
};

typedef struct cstr cstr_t;

// TODO:
//bool string_resize(cstr_t *str, size_t new_size);
//bool string_free(cstr_t * str);
//bool string_ends_with_x(cstr_t * str, cstr_t * x);
//char string_get_char_at(cstr_t * str, size_t pos);
//size_t string_index_of(cstr_t *str, char c);
//size_t string_last_index_of(cstr_t *str, char c);
// int string_to_int(cstr_t * str);
// bool string_set_char_at(cstr_t * str, size_t pos);
// size_t string_size(cstr_t * str);
// bool string_starts_with_x(cstr_t * str, cstr_t * x);
// cstr_t * string_reverse(cstr_t * str);
// cstr_t * string_reverse_to(cstr_t * str, cstr_t * dest);
// bool string_is_equal(cstr_t * str1, const char str2);

    /***  Function prototypes ***/
// Initialization and memory
cstr_t * string_init(const char * origin);
/* Attempts to reserve `capacity` bytes onto the string, returns true if possible. */
bool string_reserve(cstr_t *str, size_t capacity);
/* Frees all allocated strings */
void string_free_all(void);


// Utility functions
int string_compare(cstr_t * str1, cstr_t * str2);
cstr_t * string_concat(cstr_t * str1, const char * str2);
size_t string_concat_to(cstr_t * str1, const char * str2);
cstr_t * string_left(cstr_t * str, long length);
cstr_t * string_mid(cstr_t * str, size_t pos, long length);
void string_replace(cstr_t *str, char * old_val, const char * new_val); // TODO: add a return value
size_t string_replace_char(cstr_t *str, char before, char after);
cstr_t * string_right(cstr_t * str, long length);
bool string_swap(cstr_t * str1, cstr_t * str2);

cstr_t * string_to_lower_case(cstr_t * origin);
cstr_t * string_to_upper_case(cstr_t * origin);
bool string_contains(cstr_t * str1, const char * str2);
size_t string_update(cstr_t * str, const char * new_val);


char * string_first_token(char * str, char * delim);
char * string_get_token(char * delim);

/* Implement if possible (not a priority atm) */
//cstr_t string_tokenize(cstr_t * str, char delim);
//stol   - Convert string to long int
//stoul  - Convert string to unsigned integer
//stoll  - Convert string to long long
//stoull - Convert string to unsigned long long
//stof   - Convert string to float
//stod   - Convert string to double (function template )

#endif
