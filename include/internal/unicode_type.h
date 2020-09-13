#ifndef CPEG_UNICODETYPE_H
#define CPEG_UNICODETYPE_H

#include "../object.h"
#include "stdint.h"

typedef struct stringbuffer_t FStringBuffer;

typedef struct unicode_t {
    FObject base;

    // Number of code-points
    size_t length;

    // Hashed on demand
    size_t hash;

    // set if already hashed
    unsigned int hashed: 1;

    // the width of each code point
    // 001 - 1 byte
    // 010 - 2 bytes
    // 100 - 4 bytes
    unsigned int width: 3;

    // Interned state
    unsigned int interned: 2;

    // Inlined state - set if character
    // data is part of the same allocation.
    // If not, the pointer needs to be freed separately
    unsigned int inlined: 1;

    // Set if string starts out in the compact format
    // If set, indexable data is computed on demand
    unsigned int is_compact: 1;

    // align to 4 bytes
    unsigned int : 24;

    // Compact representation of string
    uint8_t *compact;

    // Indexable data access
    // union access is determined by FUnicode->kind
    union {
        uint8_t *ucs1;
        uint16_t *ucs2;
        uint32_t *ucs4;
    } data;

    FStringBuffer *buffer;

} FUnicode;

#endif //CPEG_UNICODETYPE_H
