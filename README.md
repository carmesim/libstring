# libstring [![Codacy Badge](https://app.codacy.com/project/badge/Grade/265e20e3a7b6416d85609612e600d16f)](https://www.codacy.com/gh/carmesim/libstring?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=carmesim/libstring&amp;utm_campaign=Badge_Grade) [![CodeFactor](https://www.codefactor.io/repository/github/carmesim/libstring/badge)](https://www.codefactor.io/repository/github/carmesim/libstring) [![TODOs](https://img.shields.io/endpoint?url=https://api.tickgit.com/badge?repo=github.com/carmesim/libstring)](https://www.tickgit.com/browse?repo=github.com/carmesim/libstring) [![Build Status](https://travis-ci.org/carmesim/libstring.svg?branch=master)](https://travis-ci.org/carmesim/libstring) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

  **Early work in progress. ⚠️*

`libstring` aims to be a highly portable, [Valgrind](https://www.valgrind.org/)-passing, single-header library that brings better support for strings and string manipulation to ANSI C. This library does **not** depend on `string.h` or `strings.h`, using only `stdio.h`, `stdlib.h` and `stdbool.h` (when available, falls back to the usual typedef when not on C99 or newer).

## Currently implemented public functions

```C
cstr_t * string_init(const char * origin);                 // Initializes a new cstr_t *.
void  string_free_all (void);                              // Frees all heap allocations made by libstring.
cstr_t * string_to_lower_case(cstr_t * origin);            // Returns a new cstr_t * with the contents of origin lower-cased
cstr_t * string_to_upper_case(cstr_t * origin);            // Returns a new cstr_t * with the contents of origin upper-cased
cstr_t * string_concat(cstr_t * str1, const char * str2);  // Returns a new cstr_t * with the concatenation of str1 and str2
size_t string_concat_to(cstr_t * str1, const char * str2); // Concatenates str1 and str2 to str1.
bool string_contains(cstr_t * str1, const char * str2);    // Returns true if str2 is a substring of str1.
size_t string_update(cstr_t * str, const char * new_val);  // Updates the value of str. Increases its memory reservation if needed.
bool string_swap(cstr_t * str1, cstr_t * str2);            // Swaps the contents of str1 and str2.
bool string_reserve(cstr_t *str, size_t capacity);         // Increases str's memory reservation
size_t string_replace_char(cstr_t *str, char before, char after); // Replaces all instances of a char with another.
```

The other functions defined in `libstring.c` are internal and not accessible.

## Building the test file

### For C99 or up

#### Using qmake

``` qmake && make ```

#### Pure GCC

``` gcc -Wall -Wextra test/main.c src/libstring.c -o libstring-test ```

### For C89

Building for C89 is annoying because GCC with `-std=c89` does not like the C++-style comments.

You can solve this problem by removing all comments and then building:

```bash
gcc -fpreprocessed -dD -E src/libstring.c >> src/89libstring.c
gcc -fpreprocessed -dD -E src/libstring.h >> src/89libstring.h
gcc -fpreprocessed -dD -E test/main.c     >> test/89main.c
cp src/89libstring.c src/libstring.c
cp src/89libstring.h src/libstring.h
cp test/89main.c test/main.c
gcc -std=c89 -Wall -Wextra test/89main.c src/89libstring.c -o libstring-test
```

