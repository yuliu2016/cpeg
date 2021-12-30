#ifndef CPEG_AST_H
#define CPEG_AST_H

#include "mem.h"
#include "peg.h"

typedef struct ast_list {
    size_t len;
    size_t capacity;
    void **items;
} ast_list_t;

ast_list_t *ast_list_new(parser_t *p);

void ast_list_append(parser_t *p, ast_list_t *seq, void *item);


static inline void *node(parser_t *p, void *f) {
    return PARSER_ALLOC(p, sizeof(char));
}

double *binop_add(parser_t *p, double *a, double *b);
double *binop_sub(parser_t *p, double *a, double *b);
double *binop_mul(parser_t *p, double *a, double *b);
double *binop_div(parser_t *p, double *a, double *b);
double *binop_mod(parser_t *p, double *a, double *b);
double *binop_pow(parser_t *p, double *a, double *b);
double *unary_plus(parser_t *p, double *a);
double *unary_minus(parser_t *p, double *a);
double *unary_not(parser_t *p, double *a);
double *load_const(parser_t *p, token_t *token);
double *call_func(parser_t *p, token_t *name, ast_list_t *token);
double *to_double(parser_t *p, token_t *tok);

#endif //CPEG_AST_H
