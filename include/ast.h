#ifndef CPEG_AST_H
#define CPEG_AST_H

#include "mem.h"
#include "peg.h"


static inline void *node(parser_t *p, void *f) {
    return PARSER_ALLOC(p, sizeof(char));
}


static int CMP_LT = 0;
static int CMP_GT = 1;
static int CMP_EQ = 2;
static int CMP_GE = 3;
static int CMP_LE = 4;
static int CMP_NE = 5;
static int CMP_IN = 6;
static int CMP_NI = 7;
static int CMP_IS = 8;
static int CMP_NS = 9;

#endif //CPEG_AST_H
