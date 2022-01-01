#ifndef CPEG_AST_H
#define CPEG_AST_H

#include "mem.h"
#include "peg.h"


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
double *call_func(parser_t *p, token_t *name, ast_list_t *params);
double *to_double(parser_t *p, token_t *tok);

#endif //CPEG_AST_H
