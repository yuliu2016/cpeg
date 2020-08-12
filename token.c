#include "token.h"
#include "mem.h"

FTokenStr *FToken_str_from_ptr(char *src) {
    size_t len = 0;
    while (1) {
        char ch = src[len];
        if (!ch) {
            break;
        }
        ++len;
    }
    FTokenStr *s = FMem_malloc(sizeof(FTokenStr));
    s->start = src;
    s->len = len;
    return s;
}