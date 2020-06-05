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
bool string_reserve(cstr_t *str, size_t capacity);
bool string_resize(cstr_t *str, size_t new_size);
bool string_free(cstr_t * str);
/* Frees all allocated strings */
void string_free_all(void);                                // Free all alloc-ed strings

// Utility functions
int string_compare(cstr_t * str1, cstr_t * str2);      // Follows C++ standard
cstr_t * string_concat(cstr_t * str1, cstr_t * str2);  // returns str1 + str2
size_t string_concat_to(cstr_t * str1, cstr_t * str2); // str1 = str1 + str2
bool string_ends_with_x(cstr_t * str, cstr_t * x);
char string_get_char_at(cstr_t * str, size_t pos);                       // Bound-checking
size_t string_index_of(cstr_t *str, char c);
size_t string_last_index_of(cstr_t *str, char c);
cstr_t * string_left(cstr_t * str, size_t length); // SIM TÔ COPIANDO FUNÇÃO DO QT NA CARA DURA E DAÍ
cstr_t * string_mid(cstr_t * str, size_t pos, size_t length);
size_t string_replace_char(cstr_t *str, char before, char after);
cstr_t * string_reverse(cstr_t * str);
size_t string_reserved_size();
cstr_t string_right(cstr_t * str, size_t length);
bool string_set_char_at(cstr_t * str, size_t pos);                       // Bound-checking
size_t string_size(cstr_t * str);
bool string_starts_with_x(cstr_t * str, cstr_t * x);
bool string_swap(cstr_t * str1, cstr_t * str2);
int string_to_int(cstr_t * str);

cstr_t * string_to_lower_case(cstr_t * origin);
cstr_t * string_to_upper_case(cstr_t * origin);

/* Implement if possible (not a priority atm) */
//cstr_t string_tokenize(cstr_t * str, char delim); // Que inferno vai ser isso aqui.
//stol   - Convert string to long int
//stoul  - Convert string to unsigned integer
//stoll  - Convert string to long long
//stoull - Convert string to unsigned long long
//stof   - Convert string to float
//stod   - Convert string to double (function template )
