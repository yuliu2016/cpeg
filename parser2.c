#include "include/internal/parser.h"


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
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    double *a = 0;
    double *res_1 = 0;
    double *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = sum_1(p)) ||
        (a = sum_2(p)) ||
        (a = term(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_1 = max;
    return exit_frame(p, &f, res_1);
}

static double *sum_1(parser_t *p) {
    frame_t f = {2, p->pos, FUNC, 0, 0};
    double *_sum;
    double *_term;
    double *res_2;
    res_2 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 21, "+")) &&
        (_term = term(p))
    ) ? binop_add(p, _sum, _term) : 0;
    return exit_frame(p, &f, res_2);
}

static double *sum_2(parser_t *p) {
    frame_t f = {3, p->pos, FUNC, 0, 0};
    double *_sum;
    double *_term;
    double *res_3;
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
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    double *a = 0;
    double *res_4 = 0;
    double *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = term_1(p)) ||
        (a = term_2(p)) ||
        (a = term_3(p)) ||
        (a = factor(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_4 = max;
    return exit_frame(p, &f, res_4);
}

static double *term_1(parser_t *p) {
    frame_t f = {5, p->pos, FUNC, 0, 0};
    double *_term;
    double *_factor;
    double *res_5;
    res_5 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 23, "*")) &&
        (_factor = factor(p))
    ) ? binop_mul(p, _term, _factor) : 0;
    return exit_frame(p, &f, res_5);
}

static double *term_2(parser_t *p) {
    frame_t f = {6, p->pos, FUNC, 0, 0};
    double *_term;
    double *_factor;
    double *res_6;
    res_6 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 24, "/")) &&
        (_factor = factor(p))
    ) ? binop_div(p, _term, _factor) : 0;
    return exit_frame(p, &f, res_6);
}

static double *term_3(parser_t *p) {
    frame_t f = {7, p->pos, FUNC, 0, 0};
    double *_term;
    double *_factor;
    double *res_7;
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
    double *_plus_factor;
    double *_minus_factor;
    double *_bit_not_factor;
    double *_power;
    double *a;
    double *res_8;
    res_8 = enter_frame(p, &f) && (
        (a = factor_1(p)) ||
        (a = factor_2(p)) ||
        (a = factor_3(p)) ||
        (a = power(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_8);
}

static double *factor_1(parser_t *p) {
    frame_t f = {9, p->pos, FUNC, 0, 0};
    double *_factor;
    double *res_9;
    res_9 = enter_frame(p, &f) && (
        (consume(p, 21, "+")) &&
        (_factor = factor(p))
    ) ? unary_plus(p, _factor) : 0;
    return exit_frame(p, &f, res_9);
}

static double *factor_2(parser_t *p) {
    frame_t f = {10, p->pos, FUNC, 0, 0};
    double *_factor;
    double *res_10;
    res_10 = enter_frame(p, &f) && (
        (consume(p, 22, "-")) &&
        (_factor = factor(p))
    ) ? unary_minus(p, _factor) : 0;
    return exit_frame(p, &f, res_10);
}

static double *factor_3(parser_t *p) {
    frame_t f = {11, p->pos, FUNC, 0, 0};
    double *_factor;
    double *res_11;
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
    double *_atom_power_factor;
    double *_atom;
    double *a;
    double *res_12;
    res_12 = enter_frame(p, &f) && (
        (a = power_1(p)) ||
        (a = atom(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_12);
}

static double *power_1(parser_t *p) {
    frame_t f = {13, p->pos, FUNC, 0, 0};
    double *_atom;
    double *_factor;
    double *res_13;
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
    double *_lpar_sum_rpar;
    double *_atom_2;
    token_t *_name;
    token_t *_number;
    double *a;
    double *res_14;
    res_14 = enter_frame(p, &f) && (
        (a = atom_1(p)) ||
        (a = atom_2(p)) ||
        (a = load_const(p, consume(p, 3, "NAME"))) ||
        (a = to_double(p, consume(p, 4, "NUMBER")))
    ) ? a : 0;
    return exit_frame(p, &f, res_14);
}

static double *atom_1(parser_t *p) {
    frame_t f = {15, p->pos, FUNC, 0, 0};
    double *_sum;
    double *res_15;
    res_15 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_sum = sum(p)) &&
        (consume(p, 14, ")"))
    ) ? _sum : 0;
    return exit_frame(p, &f, res_15);
}

static double *atom_2(parser_t *p) {
    frame_t f = {16, p->pos, FUNC, 0, 0};
    token_t *_name;
    ast_list_t *_parameters;
    double *res_16;
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
    ast_list_t *_sums;
    token_t *_is_comma;
    ast_list_t *res_17;
    res_17 = enter_frame(p, &f) && (
        (_sums = sum_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
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
