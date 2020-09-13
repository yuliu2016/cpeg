#include "unicode.h"
#include "mem.h"
#include "unicode_type.h"

FObject *FUnicode_from_ascii(const char *array) {
    if (!array) return NULL;

    size_t len = 0;
    const char *p = array;
    while (*p) {
        ++len;
        ++p;
    }

    FUnicode *u = FMem_malloc(sizeof(FUnicode) + len);
    if (!u) return NULL;
    u->base.refcount = 0;

    u->length = len;
    u->hash = 0;
    u->hashed = 0;
    u->width = 1;
    u->inlined = 1;
    u->is_compact = 0;
    u->compact = NULL;

    uint8_t *cp = (uint8_t *) (u + 1);
    u->data.ucs1 = cp;

    p = array;
    for (int i = 0; i < len; ++i) {
        *cp = *p;
        cp++;
        p++;
    }

    u->buffer = NULL;

    return (FObject *) u;
}