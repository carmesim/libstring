#include "../src/libstring.h"
#include <stdio.h>

int main(void)
{
    cstr_t * str = string_init("hey there.");
    printf("%s\n", str->value);
    printf("%zu %zu\n", str->reserved, str->size);
    str = string_to_upper_case(str);
    printf("%s\n", str->value);
    string_free_all();
}
