#include "include/ast2.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


/*
csum[double] (left_recursive):
    | csum '+' cterm { "binop_add(p, %a, %b)" }
    | csum '-' cterm { "binop_sub(p, %a, %b)" }
    | cterm { a }
cterm[double] (left_recursive):
    | cterm '*' cfactor { "binop_mul(p, %a, %b)" }
    | cterm '/' cfactor { "binop_div(p, %a, %b)" }
    | cterm '%' cfactor { "binop_mod(p, %a, %b)" }
    | cfactor { a }
cfactor[double]:
    | '+' cfactor { "unary_plus(p, %a)" }
    | '-' cfactor { "unary_minus(p, %a)" }
    | '~' cfactor { "unary_not(p, %a)" }
    | cpower { a }
cpower[double]:
    | catom '**' cfactor { "binop_pow(p, %a, %b)" }
    | catom { a }
catom[double]:
    | '(' csum ')' { a }
    | NAME '(' [cparameters] ')' { "call_func(p, %a)" }
    | NAME { "load_const(p, %a)" }
    | NUMBER { "to_double(p, %a)" }
cparameters[ast_list_t]:
    | ','.csum+ [','] { a }
    */

double *binop_add(parser_t *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a + *b;
    return r;
}

double *binop_sub(parser_t *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a - *b;
    return r;
}


double *binop_mul(parser_t *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a * *b;
    return r;
}


double *binop_div(parser_t *p, double *a, double *b) {
    if (*b == 0) {
        p->error = "Division by zero";
        return 0;
    }
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a / *b;
    return r;
}

double *binop_mod(parser_t *p, double *a, double *b) {
    if (*b == 0) {
        return 0;
    }
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = fmod(*a, *b);
    return r;
}


double *binop_pow(parser_t *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a + *b;
    return r;
}

double *unary_plus(parser_t *p, double *a) {
    return a;
}

double *unary_minus(parser_t *p, double *a) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = -*a;
    return r;
}

double *unary_not(parser_t *p, double *a) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = 0;
    return r;
}

double *load_const(parser_t *p, token_t *token) {
    if (!token) return NULL;
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = 0;
    return r;
}


double *call_func(parser_t *p, token_t *name, ast_list_t *token) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = 0;
    return r;
}

double *to_double(parser_t *p, token_t *tok) {
    if (!tok) return NULL;
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = strtod(tok->start, NULL);
    return r;
}