#include "../src/libstring.h"
#include <stdio.h>

int main(void)
{
    cstr_t * str = string_init("hey there.");
    //printf("%s\n", str->value);
    //printf("%zu %zu\n", str->reserved, str->size);
    string_free_all();
}
