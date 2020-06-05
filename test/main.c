#include "../src/libstring.h"
#include <stdio.h>

int main(void)
{
    cstr_t * str1 = string_init("THE CARMESIM PROJECT.");
    cstr_t * str2 = string_init("The Carmesim Project.");

    //! Testing string_to_lower_case(cstr_t*, bool)
    printf("Testing string_to_lower_case(cstr_t*, bool)\n");

    printf("Before: %s\n", str1->value);
    cstr_t * str1low = string_to_lower_case(str1);     //! str1low is a copy of str1 with all lower-case characters.
    printf("After: %s\n", str1low->value);
    //!

    //! Testing string_to_upper_case(cstr_t*)
    printf("Testing string_to_upper_case(cstr_t*, bool)\n");

    printf("Before: %s\n", str2->value);
    cstr_t * str2low = string_to_upper_case(str2);     //! str1low is a copy of str1 with all lower-case characters.
    printf("After: %s\n", str2low->value);
    //!

//    //! Testing string_resize(cstr_t*, bool);
//    printf("Testing string_to_upper_case(cstr_t*, bool);\n");
//    if (string_reserve(str1, 2))
//    {
//        printf("string_resized worked with cap=%zu.\n", str1->reserved);
//    }
//    //!

    //! Testing string_swap();
    printf("Testing string_swap(cstr_t*, cstr_t*);\n");

    printf("Before string_swap: str1->val = %s, str2->val = %s.\n", str1->value, str2->value);
    if(string_swap(str1, str2))
    {
        printf("string_swap worked.\n");
        printf("After string_swap: str1->val = %s, str2->val = %s.\n", str1->value, str2->value);
    }
    //!


    string_free_all();
}
