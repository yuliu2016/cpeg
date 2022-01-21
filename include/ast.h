#ifndef CPEG_AST_H
#define CPEG_AST_H

#include "mem.h"
#include "peg.h"


static inline void *node(parser_t *p) {
    return parser_alloc(p, sizeof(char));
}


enum expr_opcode {
    CMP_LT,
    CMP_GT,
    CMP_EQ,
    CMP_GE,
    CMP_LE,
    CMP_NE,
    CMP_IN,
    CMP_NI,
    CMP_IS,
    CMP_NS,

    BINOP_PRIMARY,
    BINOP_IOR,
    BINOP_XOR,
    BINOP_AND,
    BINOP_SHL,
    BINOP_SHR,
    BINOP_PLS,
    BINOP_MIN,
    BINOP_MUL,
    BINOP_DIV,
    BINOP_MOD,
    BINOP_FDV,
    BINOP_MML,
    BINOP_PIP,
    BINOP_POW,

    UNARY_PLS,
    UNARY_MIN,
    UNARY_INV,

    LOGIC_AND,
    LOGIC_OR,
    LOGIC_NOT
};



typedef struct ast_expr {
    enum expr_opcode opcode;
    struct ast_expr *left;
    union {
        void *primary;
        struct ast_expr *expr;
        struct ast_expr **comp_terms;
    } right;
} ast_expr_t;

typedef struct ast_named {
    char *name;
    ast_expr_t *expr;
} ast_named_t;

typedef struct ast_primary {
    char *name;
} ast_primary_t;

typedef struct ast_stmt {
    char *name;
} ast_stmt_t;


#endif //CPEG_AST_H
