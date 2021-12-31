#ifndef CPEG_AST_H
#define CPEG_AST_H

#include "mem.h"
#include "peg.h"


static inline void *node(parser_t *p, void *f) {
    return PARSER_ALLOC(p, sizeof(char));
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
    UNARY_INV
};

typedef struct ast_expr {
    enum expr_opcode opcode;
    union {
        void *primary;
        struct ast_expr *expr;
    } left;
    struct ast_expr *right;
} ast_expr_t;



ast_expr_t *ast_binary(parser_t *p, ast_expr_t *left, 
        ast_expr_t *right, enum expr_opcode binop_code);

ast_expr_t *ast_unary(parser_t *p, ast_expr_t *expr, enum expr_opcode unary_opcode);


ast_expr_t *ast_primary_expr(parser_t *p, void *primary);

int *ast_integer(parser_t *p, int i);

#endif //CPEG_AST_H
