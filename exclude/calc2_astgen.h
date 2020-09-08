#ifndef CPEG_CALC2_ASTGEN_H
#define CPEG_CALC2_ASTGEN_H

#include "peg.h"

#define FVAR(name, node, i) FAstNode *name = (node)->ast_v.fields[i]
#define TVAR(name, node, i) FToken *name = (node)->ast_v.fields[i]->ast_v.token

#define R_SUM 1

#define R_SUM_1 2
#define UNPACK_SUM_1(n) \
    FVAR(sum, n, 0); \
    FVAR(term, n, 1); \

#define R_SUM_2 3
#define UNPACK_SUM_2(n) \
    FVAR(sum, n, 0); \
    FVAR(term, n, 1); \

#define R_TERM 4

#define R_TERM_1 5
#define UNPACK_TERM_1(n) \
    FVAR(term, n, 0); \
    FVAR(factor, n, 1); \

#define R_TERM_2 6
#define UNPACK_TERM_2(n) \
    FVAR(term, n, 0); \
    FVAR(factor, n, 1); \

#define R_TERM_3 7
#define UNPACK_TERM_3(n) \
    FVAR(term, n, 0); \
    FVAR(factor, n, 1); \

#define R_FACTOR 8

#define R_FACTOR_1 9
#define UNPACK_FACTOR_1(n) \
    FVAR(factor, n, 0); \

#define R_FACTOR_2 10
#define UNPACK_FACTOR_2(n) \
    FVAR(factor, n, 0); \

#define R_FACTOR_3 11
#define UNPACK_FACTOR_3(n) \
    FVAR(factor, n, 0); \

#define R_POWER 12

#define R_POWER_1 13
#define UNPACK_POWER_1(n) \
    FVAR(atom, n, 0); \
    FVAR(factor, n, 1); \

#define R_ATOM 14

#define R_ATOM_1 15
#define UNPACK_ATOM_1(n) \
    FVAR(sum, n, 0); \

#define R_ATOM_2 16
#define UNPACK_ATOM_2(n) \
    TVAR(name, n, 0); \
    FVAR(parameters, n, 1); \

#define R_PARAMETERS 17
#define UNPACK_PARAMETERS(n) \
    FVAR(sums, n, 0); \
    TVAR(is_op_comma, n, 1); \

#endif // CPEG_CALC2_ASTGEN_H
