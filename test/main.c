#include "../src/libstring.h"
#include <stdio.h>

int main(void)
{
    cstr_t * str1 = string_init("THE CARMESIM PROJECT.");
    cstr_t * str2 = string_init("The Carmesim Project.");
    printf("%s\n", str1->value);
    printf("%zu %zu\n", str1->reserved, str1->size);

    //! Testing string_to_lower_case(cstr_t*, bool)
    printf("Testing string_to_lower_case(cstr_t*, bool)\n");

    printf("Before: %s\n", str1->value);
    cstr_t * str1low = string_to_lower_case(str1);     //! str1low is a copy of str1 with all lower-case characters.
    printf("After: %s\n", str1low->value);


    //! Testing string_to_upper_case(cstr_t*)
    printf("Testing string_to_upper_case(cstr_t*, bool)\n");

    printf("Before: %s\n", str2->value);
    cstr_t * str2low = string_to_upper_case(str2);     //! str1low is a copy of str1 with all lower-case characters.
    printf("After: %s\n", str2low->value);


    //! Testing string_resize();
    if (string_reserve(str1, 2))
    {
        printf("string_resized worked with cap=%zu.\n", str1->reserved);
    }

    string_free_all();
}
