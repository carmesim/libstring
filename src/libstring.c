#include "libstring.h"
#include <stdio.h>
#include <stdlib.h>

struct alloc_node
{
    cstr_t            * val;
    struct alloc_node * next;
}
