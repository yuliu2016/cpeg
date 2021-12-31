#ifndef CPEG_AST_H
#define CPEG_AST_H

#include "mem.h"
#include "peg.h"


static inline void *node(parser_t *p, void *f) {
    return PARSER_ALLOC(p, sizeof(char));
}

#endif //CPEG_AST_H
