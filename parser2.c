#include "include/ast2.h"


static double *sum(parser_t *);
static double *sum_1(parser_t *);
static double *sum_2(parser_t *);
static double *term(parser_t *);
static double *term_1(parser_t *);
static double *term_2(parser_t *);
static double *term_3(parser_t *);
static double *factor(parser_t *);
static double *factor_1(parser_t *);
static double *factor_2(parser_t *);
static double *factor_3(parser_t *);
static double *power(parser_t *);
static double *power_1(parser_t *);
static double *atom(parser_t *);
static double *atom_1(parser_t *);
static double *atom_2(parser_t *);
static ast_list_t *parameters(parser_t *);
static ast_list_t *sum_delimited(parser_t *);



// Parser Entry Point
double *parse_calc(parser_t *p) {
    return sum(p);
}

// sum (left_recursive):
//     | sum '+' term
//     | sum '-' term
//     | term
static double *sum(parser_t *p) {
    frame_t f = {1, p->pos, FUNC, 0, 1};
    double *res_1 = 0;
    double *alt_1;
    size_t maxpos;
    double *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_1;
            memoize(p, &f, max, maxpos);
            p->pos = f.f_pos;
            res_1 = (
                (alt_1 = sum_1(p)) ||
                (alt_1 = sum_2(p)) ||
                (alt_1 = term(p))
            ) ? alt_1 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_1 = max;
    }
    return exit_frame(p, &f, res_1);
}

static double *sum_1(parser_t *p) {
    frame_t f = {2, p->pos, FUNC, 0, 0};
    double *res_2;
    double *_sum;
    double *_term;
    res_2 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 21, "+")) &&
        (_term = term(p))
    ) ? binop_add(p, _sum, _term) : 0;
    return exit_frame(p, &f, res_2);
}

static double *sum_2(parser_t *p) {
    frame_t f = {3, p->pos, FUNC, 0, 0};
    double *res_3;
    double *_sum;
    double *_term;
    res_3 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 22, "-")) &&
        (_term = term(p))
    ) ? binop_sub(p, _sum, _term) : 0;
    return exit_frame(p, &f, res_3);
}

// term (left_recursive):
//     | term '*' factor
//     | term '/' factor
//     | term '%' factor
//     | factor
static double *term(parser_t *p) {
    frame_t f = {4, p->pos, FUNC, 0, 1};
    double *res_4 = 0;
    double *alt_4;
    size_t maxpos;
    double *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_4;
            memoize(p, &f, max, maxpos);
            p->pos = f.f_pos;
            res_4 = (
                (alt_4 = term_1(p)) ||
                (alt_4 = term_2(p)) ||
                (alt_4 = term_3(p)) ||
                (alt_4 = factor(p))
            ) ? alt_4 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_4 = max;
    }
    return exit_frame(p, &f, res_4);
}

static double *term_1(parser_t *p) {
    frame_t f = {5, p->pos, FUNC, 0, 0};
    double *res_5;
    double *_term;
    double *_factor;
    res_5 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 23, "*")) &&
        (_factor = factor(p))
    ) ? binop_mul(p, _term, _factor) : 0;
    return exit_frame(p, &f, res_5);
}

static double *term_2(parser_t *p) {
    frame_t f = {6, p->pos, FUNC, 0, 0};
    double *res_6;
    double *_term;
    double *_factor;
    res_6 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 24, "/")) &&
        (_factor = factor(p))
    ) ? binop_div(p, _term, _factor) : 0;
    return exit_frame(p, &f, res_6);
}

static double *term_3(parser_t *p) {
    frame_t f = {7, p->pos, FUNC, 0, 0};
    double *res_7;
    double *_term;
    double *_factor;
    res_7 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 25, "%")) &&
        (_factor = factor(p))
    ) ? binop_mod(p, _term, _factor) : 0;
    return exit_frame(p, &f, res_7);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static double *factor(parser_t *p) {
    frame_t f = {8, p->pos, FUNC, 0, 0};
    double *res_8;
    double *alt_8;
    res_8 = enter_frame(p, &f) && (
        (alt_8 = factor_1(p)) ||
        (alt_8 = factor_2(p)) ||
        (alt_8 = factor_3(p)) ||
        (alt_8 = power(p))
    ) ? alt_8 : 0;
    return exit_frame(p, &f, res_8);
}

static double *factor_1(parser_t *p) {
    frame_t f = {9, p->pos, FUNC, 0, 0};
    double *res_9;
    double *_factor;
    res_9 = enter_frame(p, &f) && (
        (consume(p, 21, "+")) &&
        (_factor = factor(p))
    ) ? unary_plus(p, _factor) : 0;
    return exit_frame(p, &f, res_9);
}

static double *factor_2(parser_t *p) {
    frame_t f = {10, p->pos, FUNC, 0, 0};
    double *res_10;
    double *_factor;
    res_10 = enter_frame(p, &f) && (
        (consume(p, 22, "-")) &&
        (_factor = factor(p))
    ) ? unary_minus(p, _factor) : 0;
    return exit_frame(p, &f, res_10);
}

static double *factor_3(parser_t *p) {
    frame_t f = {11, p->pos, FUNC, 0, 0};
    double *res_11;
    double *_factor;
    res_11 = enter_frame(p, &f) && (
        (consume(p, 29, "~")) &&
        (_factor = factor(p))
    ) ? unary_not(p, _factor) : 0;
    return exit_frame(p, &f, res_11);
}

// power:
//     | atom '**' factor
//     | atom
static double *power(parser_t *p) {
    frame_t f = {12, p->pos, FUNC, 0, 0};
    double *res_12;
    double *alt_12;
    res_12 = enter_frame(p, &f) && (
        (alt_12 = power_1(p)) ||
        (alt_12 = atom(p))
    ) ? alt_12 : 0;
    return exit_frame(p, &f, res_12);
}

static double *power_1(parser_t *p) {
    frame_t f = {13, p->pos, FUNC, 0, 0};
    double *res_13;
    double *_atom;
    double *_factor;
    res_13 = enter_frame(p, &f) && (
        (_atom = atom(p)) &&
        (consume(p, 38, "**")) &&
        (_factor = factor(p))
    ) ? binop_pow(p, _atom, _factor) : 0;
    return exit_frame(p, &f, res_13);
}

// atom:
//     | '(' sum ')'
//     | NAME '(' [parameters] ')'
//     | NAME
//     | NUMBER
static double *atom(parser_t *p) {
    frame_t f = {14, p->pos, FUNC, 0, 0};
    double *res_14;
    token_t *_name;
    token_t *_number;
    double *alt_14;
    res_14 = enter_frame(p, &f) && (
        (alt_14 = atom_1(p)) ||
        (alt_14 = atom_2(p)) || (
            (_name = consume(p, 3, "NAME")) &&
            (alt_14 = load_const(p, _name))
        ) || (
            (_number = consume(p, 4, "NUMBER")) &&
            (alt_14 = to_double(p, _number)))
    ) ? alt_14 : 0;
    return exit_frame(p, &f, res_14);
}

static double *atom_1(parser_t *p) {
    frame_t f = {15, p->pos, FUNC, 0, 0};
    double *res_15;
    double *_sum;
    res_15 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_sum = sum(p)) &&
        (consume(p, 14, ")"))
    ) ? _sum : 0;
    return exit_frame(p, &f, res_15);
}

static double *atom_2(parser_t *p) {
    frame_t f = {16, p->pos, FUNC, 0, 0};
    double *res_16;
    token_t *_name;
    ast_list_t *_parameters;
    res_16 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 13, "(")) &&
        (_parameters = parameters(p), 1) &&
        (consume(p, 14, ")"))
    ) ? call_func(p, _name, _parameters) : 0;
    return exit_frame(p, &f, res_16);
}

// parameters:
//     | ','.sum+ [',']
static ast_list_t *parameters(parser_t *p) {
    frame_t f = {17, p->pos, FUNC, 0, 0};
    ast_list_t *res_17;
    ast_list_t *_sums;
    res_17 = enter_frame(p, &f) && (
        (_sums = sum_delimited(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _sums : 0;
    return exit_frame(p, &f, res_17);
}

static ast_list_t *sum_delimited(parser_t *p) {
    double *_sum = sum(p);
    if (!_sum) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _sum);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_sum = sum(p)));
    p->pos = pos;
    return list;
}
