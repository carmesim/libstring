#include "../src/libstring.h"
#include <stdio.h>

void test_routine(void)
{
    //! Testing string_init(const char *);
    printf("Testing string_init(const char *);\n");
    cstr_t * str1 = string_init("THE CARMESIM PROJECT.");
    cstr_t * str2 = string_init("The Carmesim Project.");
    //!

    //! Testing string_to_lower_case(cstr_t*, bool)
    printf("\nTesting string_to_lower_case(cstr_t*, bool)\n");

    printf("Before: %s\n", str1->value);
    cstr_t * str1low = string_to_lower_case(str1);     //! str1low is a copy of str1 with all lower-case characters.
    printf("After: %s\n", str1low->value);
    //!

    //! Testing string_to_upper_case(cstr_t*)
    printf("\nTesting string_to_upper_case(cstr_t*, bool)\n");

    printf("Before: %s\n", str2->value);
    cstr_t * str2low = string_to_upper_case(str2);     //! str1low is a copy of str1 with all lower-case characters.
    printf("After: %s\n", str2low->value);
    //!

    //! Testing string_resize(cstr_t*, bool);
    printf("\nTesting string_resize(cstr_t*, bool);\n");
    if (string_reserve(str1, 55))
    {
        printf("string_reserve worked with cap=%zu.\n", str1->reserved);
    }
    //!

    //! Testing string_swap();
    printf("\nTesting string_swap(cstr_t*, cstr_t*);\n");

    printf("Before string_swap: str1->val = %s, str2->val = %s.\n", str1->value, str2->value);
    if(string_swap(str1, str2))
    {
        printf("string_swap worked.\n");
        printf("After string_swap: str1->val = %s, str2->val = %s.\n", str1->value, str2->value);
    }
    //!

    //! Testing string_replace_char(cstr_t *, char, char);
    string_replace_char(str2, 'T', 'o');
    printf("After string_replace_char: str2->val = %s.\n", str2->value);
    //!

    //! Testing string_contains(cstr_t *, cstr_t *) and string_update(cstr_t *, const char *);
    printf("\nTesting string_contains(cstr_t *, cstr_t *) and string_update(cstr_t *, const char *);\n");
    string_update(str1, "carmesim");
    if (string_contains(str1, "armes"))
    {
        printf("%s is in %s\n", "armes", str1->value);
    }

    //! Testing string_concat(cstr_t *, const char *)
    printf("\nTesting string_concat(cstr_t *, const char *)\n");
    cstr_t * concat = string_concat(str1, " project");
    printf("\"%s\" + \" project\" = \"%s\"\n", str1->value, concat->value);
    //!

    //! Testing string_concat_to(cstr_t *, const char *)
    printf("\nTesting string_concat_to(cstr_t *, const char *)\n");
    string_concat_to(concat, " 2020.");
    printf("\"carmesim project\" + \" 2020.\" = \"%s\"\n", concat->value);
    //!

    // Freeing all heap-allocated memory
    string_free_all();
}
typedef cstr_t * string;

int main(void)
{
    test_routine();
}
