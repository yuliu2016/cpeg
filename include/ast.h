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


typedef struct ast_atom {
    char *name;
} ast_atom_t;

typedef struct ast_stmt {
    char *name;
} ast_stmt_t;

ast_expr_t *ast_binary(parser_t *p, ast_expr_t *left, 
        ast_expr_t *right, enum expr_opcode binop_code);

ast_expr_t *ast_unary(parser_t *p, ast_expr_t *expr, enum expr_opcode unary_opcode);


ast_expr_t *ast_primary_expr(parser_t *p, void *primary);

int *ast_integer(parser_t *p, int i);

ast_expr_t *ast_conditional(parser_t *p, ast_expr_t *cond, ast_expr_t *a, ast_expr_t *b);

ast_named_t *ast_named(parser_t *p, token_t *name, ast_expr_t *expr);

ast_named_t *ast_unnamed(parser_t *p, ast_expr_t *expr);

ast_expr_t *ast_comp_term(parser_t *p, int *comp_op, ast_expr_t *operand);

ast_expr_t *ast_comparison(parser_t *p, ast_expr_t *first, ast_list_t *terms);

ast_stmt_t *ast_nop(parser_t *p);

ast_stmt_t *ast_break(parser_t *p);

ast_stmt_t *ast_continue(parser_t *p);

ast_atom_t *ast_name_atom(parser_t *p, token_t *name);
ast_atom_t *ast_number_atom(parser_t *p, token_t *name);
ast_atom_t *ast_string_atom(parser_t *p, token_t *name);
ast_atom_t *ast_none(parser_t *p);
ast_atom_t *ast_true(parser_t *p);
ast_atom_t *ast_false(parser_t *p);


#endif //CPEG_AST_H
