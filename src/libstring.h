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

#include <stdbool.h>
#include <stdlib.h>

    /* Type definitions */

struct cstr
{
    char * value;
    size_t size;
    size_t reserved;
    // enum encoding;  libstring 2.0 or more
};

typedef struct cstr cstr_t;

    /***  Function prototypes ***/
// Initialization and memory
cstr_t * string_init(const char * origin);
/* Attempts to reserve `capacity` bytes onto the string, returns true if possible. */
bool string_reserve(cstr_t *str, size_t capacity);         // def, tested, needs one more test case
bool string_resize(cstr_t *str, size_t new_size);          // undef
bool string_free(cstr_t * str);                            // undef
/* Frees all allocated strings */
void string_free_all(void);                                // def, tested, unfinished

// Utility functions
int string_compare(cstr_t * str1, cstr_t * str2);          // undef, Follows C++ standard
cstr_t * string_concat(cstr_t * str1, cstr_t * str2);      // undef, returns str1 + str2
size_t string_concat_to(cstr_t * str1, cstr_t * str2);     // undef, str1 = str1 + str2
bool string_ends_with_x(cstr_t * str, cstr_t * x);         // undef
char string_get_char_at(cstr_t * str, size_t pos);         // undef, bound-checking
size_t string_index_of(cstr_t *str, char c);               // undef
size_t string_last_index_of(cstr_t *str, char c);          // undef
cstr_t * string_left(cstr_t * str, size_t length);         // undef
cstr_t * string_mid(cstr_t * str, size_t pos, size_t length);       // undef
size_t string_replace_char(cstr_t *str, char before, char after);   // def, tested, see related to-do inside function.
cstr_t * string_reverse(cstr_t * str);                     // undef
cstr_t string_right(cstr_t * str, size_t length);          // undef
bool string_set_char_at(cstr_t * str, size_t pos);         // undef
size_t string_size(cstr_t * str);                          // undef, TODO: unneeded? size is accessible within the string
bool string_starts_with_x(cstr_t * str, cstr_t * x);       // undef
bool string_swap(cstr_t * str1, cstr_t * str2);            // def, tested
int string_to_int(cstr_t * str);                           // undef

cstr_t * string_to_lower_case(cstr_t * origin);            // def, tested
cstr_t * string_to_upper_case(cstr_t * origin);            // def, tested
bool string_contains(cstr_t * str, cstr_t * substr);       // def, untested
size_t string_replace(cstr_t * str, const char * new_val); // def, untested

/* Implement if possible (not a priority atm) */
//cstr_t string_tokenize(cstr_t * str, char delim); // Que inferno vai ser isso aqui.
//stol   - Convert string to long int
//stoul  - Convert string to unsigned integer
//stoll  - Convert string to long long
//stoull - Convert string to unsigned long long
//stof   - Convert string to float
//stod   - Convert string to double (function template )
