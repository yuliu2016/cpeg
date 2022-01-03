#include "unicode.h"
#include "mem.h"
#include "unicode_type.h"
#include "string.h"
#include "stdlib.h"

struct stringbuffer_t {
    size_t len;
    size_t capacity;
    VALUE *objects;
};

VALUE FUnicode_from_ascii_and_size(const char * array, size_t len) {
    if (!array) return NULL;
    const char *p = array;

    FUnicode *u = malloc(sizeof(FUnicode) + len);
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

    for (int i = 0; i < len; ++i) {
        *cp = *p;
        cp++;
        p++;
    }

    u->buffer = NULL;

    return (VALUE) u;
}

VALUE FUnicode_from_ascii(const char *array) {
    if (!array) return NULL;
    return FUnicode_from_ascii_and_size(array, strlen(array));
}