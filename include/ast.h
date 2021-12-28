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


static inline void *node_0(parser_t *p, void *f) {
    return PARSER_ALLOC(p, sizeof(char));
}

static inline void *node_1(parser_t *p, void *f, void *a) {
    return PARSER_ALLOC(p, sizeof(char));
}

static inline void *node_2(parser_t *p, void *f, void *a , void *b) {
    return PARSER_ALLOC(p, sizeof(char));
}

static inline void *node_3(parser_t *p, void *f, void *a, void *b, void *c) {
    return PARSER_ALLOC(p, sizeof(char));
}

static inline void *node_4(parser_t *p, void *f, void *a, void *b, void *c, void *d) {
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
double *load_const(parser_t *p, FToken *token);
double *call_func(parser_t *p, FToken *name, ast_list_t *token);
double *to_double(parser_t *p, FToken *tok);

#endif //CPEG_AST_H
