#ifndef CPEG_AST_H
#define CPEG_AST_H

#include "mem.h"
#include "peg.h"

typedef struct ast_list {
    size_t len;
    size_t capacity;
    void **items;
} ast_list_t;

ast_list_t *ast_list_new(FParser *p);

void ast_list_append(FParser *p, ast_list_t *seq, void *item);


static inline void *node_0(FParser *p, void *f) {
    return PARSER_ALLOC(p, sizeof(char));
}

static inline void *node_1(FParser *p, void *f, void *a) {
    return PARSER_ALLOC(p, sizeof(char));
}

static inline void *node_2(FParser *p, void *f, void *a , void *b) {
    return PARSER_ALLOC(p, sizeof(char));
}

static inline void *node_3(FParser *p, void *f, void *a, void *b, void *c) {
    return PARSER_ALLOC(p, sizeof(char));
}

static inline void *node_4(FParser *p, void *f, void *a, void *b, void *c, void *d) {
    return PARSER_ALLOC(p, sizeof(char));
}

double *binop_add(FParser *p, double *a, double *b);
double *binop_sub(FParser *p, double *a, double *b);
double *binop_mul(FParser *p, double *a, double *b);
double *binop_div(FParser *p, double *a, double *b);
double *binop_mod(FParser *p, double *a, double *b);
double *binop_pow(FParser *p, double *a, double *b);
double *unary_plus(FParser *p, double *a);
double *unary_minus(FParser *p, double *a);
double *unary_not(FParser *p, double *a);
double *load_const(FParser *p, FToken *token);
double *call_func(FParser *p, FToken *name, ast_list_t *token);
double *to_double(FParser *p, FToken *tok);

#endif //CPEG_AST_H
