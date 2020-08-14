#ifndef CPEG_CALC_PARSER_INTERNAL_H
#define CPEG_CALC_PARSER_INTERNAL_H

#include "../calc_parser.h"
#include "peg_internal.h"


#define ENTER_FRAME(p, type, name) \
    ENTER_FRAME_X(p, type, name) \
    calc_node *res = ((void *) 0)

#define EXIT_FRAME(p)  \
    EXIT_FRAME_X(p) \
    return res

#define NEW_NODE(p) PARSER_ALLOC(p, sizeof(calc_node))

// Rules

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

calc_node *sum_list(FPegParser *p);

// Utils

#define CONSUME_TOKEN(p, type, value) calc_node_from_token(p, CONSUME_TOKEN_X(p, type, value))
#define OPTIONAL_TOKEN(p, type, value) OPTIONAL(CONSUME_TOKEN(p, type, value))

calc_node *calc_node_from_token(FPegParser *p, FToken *token);

#define COPY_SEQUENCE(p, li) calc_copy_sequence(p, li)

calc_node *calc_copy_sequence(FPegParser *p, FPegList *li);

#define NODE_1(p, t, a) calc_node_1(p, t, a)

calc_node *calc_node_1(FPegParser *p, int t, calc_node *a);

#define NODE_2(p, t, a, b) calc_node_2(p, t, a, b)

calc_node *calc_node_2(FPegParser *p, int t, calc_node *a, calc_node *b);

// implementations

FToken *calc_get_token(calc_node *node) {
    if (node->t != 0) {
        return NULL;
    }
    return node->v.token.tk_val;
}

calc_node *calc_node_from_token(FPegParser *p, FToken *token) {
    if (token) {
        calc_node *node = NEW_NODE(p);
        node->t = 0;
        node->v.token.tk_val = token;
        return node;
    }
    return NULL;
}

calc_node *calc_copy_sequence(FPegParser *p, FPegList *li) {
    size_t len = LIST_LENGTH(li);
    calc_node *res = NEW_NODE(p);
    res->t = 32;
    res->v.sequence.len = len;
    res->v.sequence.items = PARSER_ALLOC(p, sizeof(calc_node));
    for (int i = 0; i < len; ++i) {
        res->v.sequence.items[i] = (calc_node *) LIST_GET(li, i);
    }

    return res;
}

calc_node *calc_node_1(FPegParser *p, int t, calc_node *a) {
    calc_node *res = NEW_NODE(p);
    res->t = t;
    res->v.invert_factor.factor = a;
    return res;
}

calc_node *calc_node_2(FPegParser *p, int t, calc_node *a, calc_node *b) {
    calc_node *res = NEW_NODE(p);
    res->t = t;
    res->v.sum_plus_term.sum = a;
    res->v.sum_plus_term.term = b;
    return res;
}

#endif //CPEG_CALC_PARSER_INTERNAL_H
