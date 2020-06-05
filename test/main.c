#include "../src/libstring.h"
#include <stdio.h>

int main(void)
{
    cstr_t * str1 = string_init("hey there.");
    printf("%s\n", str1->value);
    printf("%zu %zu\n", str1->reserved, str1->size);

    cstr_t * str2 = string_init("ayayayyy I'm a little buttahfly");
    printf("%s\n", str2->value);
    printf("%zu %zu\n", str2->reserved, str2->size);

    string_free_all();
}
