#include "../src/libstring.h"
#include <string.h>
#include <criterion/criterion.h>
#include <stdio.h>

Test(libstring_tests, string_to_lower_case_test) {
    cstr_t * str = string_init("THE CarmesiM PROJECT.");
    cstr_t * strlow = string_to_lower_case(str);
    cr_expect(!strcmp(strlow->value, "the carmesim project."), "Expected \"THE CarmesiM PROJECT.\" to have been transformed to \"the carmesim project.\".");
    string_free_all();
}

Test(libstring_tests, string_to_upper_case_test) {
    cstr_t * str = string_init("The Carmesim Project.");
    cstr_t * strlow = string_to_upper_case(str);
    cr_expect(!strcmp(strlow->value, "THE CARMESIM PROJECT."), "Expected \"The Carmesim Project.\" to have been transformed to \"THE CARMESIM PROJECT.\".");
    string_free_all();
}

Test(libstring_tests, string_reserve_test) {
    cstr_t * str = string_init("test");
    string_reserve(str, 20);
    cr_expect(str->reserved == 20, "Expected `str->reserved` to be 20.");
    string_free_all();
}

Test(libstring_tests, string_swap_test) {
    cstr_t * str1 = string_init("oranges");
    cstr_t * str2 = string_init("apples");
    string_swap(str1, str2);
    cr_expect(!strcmp(str1->value, "apples") && !strcmp(str2->value, "oranges"), "Expected str1 to have become \"apples\" and str2 to have become \"oranges\".");
    string_free_all();
}

Test(libstring_tests, string_replace_char_test) {
    cstr_t * str = string_init("Oompa loompas are doomed.");
    string_replace_char(str, 'o', 'z');
    cr_expect(!strcmp(str->value, "Ozmpa lzzmpas are dzzmed."), "Expected \"Oompa loompas are doomed.\" to have become \"Ozmpa lzzmpas are dzzmed.\"");
    string_free_all();
}

Test(libstring_tests, string_update_test) {
    cstr_t * str = string_init("Oompa loompas are doomed.");
    string_update(str, "Oompa loompas are not doomed!");
    cr_expect(!strcmp(str->value, "Oompa loompas are not doomed!"), "Expected `str` to have been updated.");
    string_free_all();
}

Test(libstring_tests, string_contains_test) {
    cstr_t * str = string_init("Oompa loompas are doomed.");
    cr_expect(string_contains(str, "loompas"), "Expected string_contains(str, \"loompas\") to result in true.");
    string_free_all();
}

Test(libstring_tests, string_concat_test) {
    cstr_t * str  = string_init("The Carmesim");
    cstr_t * strc = string_concat(str, " project.");
    cr_expect(!strcmp(strc->value, "The Carmesim project."), "Expected \"The Carmesim\" to have had \" project.\" appended");
    string_free_all();
}

Test(libstring_tests, string_concat_to_test) {
    cstr_t * str  = string_init("The Carmesim");
    string_concat_to(str, " project.");
    cr_expect(!strcmp(str->value, "The Carmesim project."), "Expected \"The Carmesim\" to have had \" project.\" appended");
    string_free_all();
}

        // Tests both string_get_token and also string_first_token
Test(libstring_tests, string_get_token_test) {
    char s[] = "The Carmesim Project";
    cstr_t * token = string_init(string_first_token(s, " "));
    //printf("%s\n", token->value);
    cr_expect(!strcmp(token->value, "The"), "Expected \"The\" in string_get_token_test.");
    string_update(token, string_get_token(" "));
    cr_expect(!strcmp(token->value, "Carmesim"), "Expected \"Carmesim\" in string_get_token_test.");
    string_update(token, string_get_token(" "));
    cr_expect(!strcmp(token->value, "Project"), "Expected \"Project\" in string_get_token_test.");
    string_free_all();
}

Test(libstring_tests, string_replace_test) {
    cstr_t * pathname = string_init("home/user/path");
    string_replace(pathname, "home/user", "~");
    cr_expect(!strcmp(pathname->value, "~/path"), "Expected \"home/user\" to have been changed to \"~\".");
    string_free_all();
}