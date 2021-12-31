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


enum expr_opcode {
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

#endif //CPEG_AST_H
