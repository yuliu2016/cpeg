#include "include/tokenmap.h"
#include "include/ast.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


ast_list_t *ast_list_new(FParser *p) {
    ast_list_t *seq = PARSER_ALLOC(p, sizeof(ast_list_t));
    if (!seq) {
        return NULL;
    }
    seq->capacity = 0;
    seq->len = 0;
    seq->items = NULL;
    return seq;
}


void ast_list_append(FParser *p, ast_list_t *seq, void *item) {
    if (seq->len >= seq->capacity) {
        if (!seq->capacity) {
            seq->capacity = 1;
            seq->len = 0;
            seq->items = PARSER_ALLOC(p, sizeof(void *));
        } else {
            seq->capacity = seq->capacity << 1u;
            // Since realloc isn't available with memory regions,
            // the nodes needs to be copied in a loop
            void **old_items = seq->items;
            seq->items = PARSER_ALLOC(p, seq->capacity * sizeof(void *));
            for (int i = 0; i < seq->len; ++i) {
                seq->items[i] = old_items[i];
            }
        }
    }
    seq->items[seq->len++] = item;
}


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

double *binop_add(FParser *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a + *b;
    return r;
}

double *binop_sub(FParser *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a - *b;
    return r;
}


double *binop_mul(FParser *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a * *b;
    return r;
}


double *binop_div(FParser *p, double *a, double *b) {
    if (*b == 0) {
        return 0;
    }
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a / *b;
    return r;
}

double *binop_mod(FParser *p, double *a, double *b) {
    if (*b == 0) {
        return 0;
    }
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = fmod(*a, *b);
    return r;
}


double *binop_pow(FParser *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a + *b;
    return r;
}

double *unary_plus(FParser *p, double *a) {
    return a;
}

double *unary_minus(FParser *p, double *a) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = -*a;
    return r;
}

double *unary_not(FParser *p, double *a) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = 0;
    return r;
}

double *load_const(FParser *p, FToken *token) {
    if (!token) return NULL;
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = 0;
    return r;
}


double *call_func(FParser *p, FToken *name, ast_list_t *token) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = 0;
    return r;
}

double *to_double(FParser *p, FToken *tok) {
    if (!tok) return NULL;
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = strtod(tok->start, NULL);
    return r;
}