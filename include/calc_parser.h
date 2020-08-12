#ifndef CPEG_CALC_PARSER_H
#define CPEG_CALC_PARSER_H

#include "peg.h"

/*
# Calculator Grammar

sum:
    | sum '+' term
    | sum '-' term
    | term
term:
    | term '*' factor
    | term '/' factor
    | term '%' factor
    | factor
factor:
    | '+' factor
    | '-' factor
    | '~' factor
    | power
power:
    | atom '**' factor
    | atom
atom:
    | '(' sum ')'
    | NAME '(' [parameters] ')'
    | NAME
    | NUMBER
parameters:
    | ','.sum+ [',']
 */

typedef struct calc_node_ calc_node;
typedef struct calc_sequence_ calc_sequence;

typedef union calc_node_v {
    struct {
        calc_node *sum;
        calc_node *term;
    } sum_plus_term;

    struct {
        calc_node *sum;
        calc_node *term;
    } sum_minus_term;

    struct {
        calc_node *term;
        calc_node *factor;
    } term_multiply_factor;

    struct {
        calc_node *term;
        calc_node *factor;
    } term_divide_factor;

    struct {
        calc_node *term;
        calc_node *factor;
    } term_modulus_factor;

    struct {
        calc_node *factor;
    } plus_factor;

    struct {
        calc_node *factor;
    } minus_factor;

    struct {
        calc_node *factor;
    } invert_factor;

    struct {
        calc_node *atom;
        calc_node *factor;
    } atom_power_factor;

    struct {
        calc_node *sum;
    } lpar_sum_rpar;

    struct {
        FToken *name;
        calc_node *parameters;
    } name_lpar_parameters_rpar;

    struct {
        calc_sequence *sum_list;
        FToken *comma;
    } sum_list_comma;

    FToken *token;
} calc_node_v;

struct calc_node_ {
    int t;
    calc_node_v v;
};

struct calc_sequence_ {
    int t;
    int len;
    calc_node **items;
};

#define ENTER_FRAME(p, type, name) \
    ENTER_FRAME_X(p, type, name); \
    calc_node *res = ((void *) 0)

#define EXIT_FRAME(p)  \
    EXIT_FRAME_X(p); \
    return res

#define NEW_NODE(p) PARSER_ALLOC(p, sizeof(calc_node))
#define NEW_SEQ(p) PARSER_ALLOC(p, sizeof(calc_sequence))

#define TOKEN_AS_NODE(p, type, value) peg_node_from_token(p, CONSUME_TOKEN(p, type, value))

#define COPY_SEQUENCE(p, li) peg_copy_sequence(p, li)

calc_node *peg_node_from_token(FPegParser *p, FToken *token) {
    if (token) {
        calc_node *node = NEW_NODE(p);
        if (!node) return NULL;
        node->t = 2;
        node->v.token = token;
        return node;
    }
    return NULL;
}

calc_sequence *peg_copy_sequence(FPegParser *p, FPegList *li) {
    size_t len = LIST_LENGTH(li);
    calc_sequence *res = NEW_SEQ(p);
    res->t = 32;
    res->len = len;
    res->items = PARSER_ALLOC(p, sizeof(calc_node));
    for (int i = 0; i < len; ++i) {
        res->items[i] = (calc_node *) LIST_GET(li, i);
    }

    return res;
}

calc_node *sum(FPegParser *p);

calc_node *sum_1(FPegParser *p);

calc_node *sum_2(FPegParser *p);

calc_node *term(FPegParser *p);

calc_node *term_1(FPegParser *p);

calc_node *term_2(FPegParser *p);

calc_node *term_3(FPegParser *p);

calc_node *factor(FPegParser *p);

calc_node *factor_1(FPegParser *p);

calc_node *factor_2(FPegParser *p);

calc_node *factor_3(FPegParser *p);

calc_node *power(FPegParser *p);

calc_node *power_1(FPegParser *p);

calc_node *atom(FPegParser *p);

calc_node *atom_1(FPegParser *p);

calc_node *atom_2(FPegParser *p);

calc_node *parameters(FPegParser *p);

calc_sequence *sum_list(FPegParser *p);


#endif //CPEG_CALC_PARSER_H
