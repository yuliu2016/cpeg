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
    double *_sum = 0;
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
    _sum = max;
    return exit_frame(p, &f, _sum);
}

static double *sum_1(parser_t *p) {
    frame_t f = {2, p->pos, FUNC, 0, 0};
    double *a;
    double *b;
    double *_sum_1;
    _sum_1 = enter_frame(p, &f) && (
        (a = sum(p)) &&
        (consume(p, 21, "+")) &&
        (b = term(p))
    ) ? binop_add(p, a, b) : 0;
    return exit_frame(p, &f, _sum_1);
}

static double *sum_2(parser_t *p) {
    frame_t f = {3, p->pos, FUNC, 0, 0};
    double *a;
    double *b;
    double *_sum_2;
    _sum_2 = enter_frame(p, &f) && (
        (a = sum(p)) &&
        (consume(p, 22, "-")) &&
        (b = term(p))
    ) ? binop_sub(p, a, b) : 0;
    return exit_frame(p, &f, _sum_2);
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
    double *_term = 0;
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
    _term = max;
    return exit_frame(p, &f, _term);
}

static double *term_1(parser_t *p) {
    frame_t f = {5, p->pos, FUNC, 0, 0};
    double *a;
    double *b;
    double *_term_1;
    _term_1 = enter_frame(p, &f) && (
        (a = term(p)) &&
        (consume(p, 23, "*")) &&
        (b = factor(p))
    ) ? binop_mul(p, a, b) : 0;
    return exit_frame(p, &f, _term_1);
}

static double *term_2(parser_t *p) {
    frame_t f = {6, p->pos, FUNC, 0, 0};
    double *a;
    double *b;
    double *_term_2;
    _term_2 = enter_frame(p, &f) && (
        (a = term(p)) &&
        (consume(p, 24, "/")) &&
        (b = factor(p))
    ) ? binop_div(p, a, b) : 0;
    return exit_frame(p, &f, _term_2);
}

static double *term_3(parser_t *p) {
    frame_t f = {7, p->pos, FUNC, 0, 0};
    double *a;
    double *b;
    double *_term_3;
    _term_3 = enter_frame(p, &f) && (
        (a = term(p)) &&
        (consume(p, 25, "%")) &&
        (b = factor(p))
    ) ? binop_mod(p, a, b) : 0;
    return exit_frame(p, &f, _term_3);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static double *factor(parser_t *p) {
    frame_t f = {8, p->pos, FUNC, 0, 0};
    double *a;
    double *_factor;
    _factor = enter_frame(p, &f) && (
        (a = factor_1(p)) ||
        (a = factor_2(p)) ||
        (a = factor_3(p)) ||
        (a = power(p))
    ) ? a : 0;
    return exit_frame(p, &f, _factor);
}

static double *factor_1(parser_t *p) {
    frame_t f = {9, p->pos, FUNC, 0, 0};
    double *a;
    double *_factor_1;
    _factor_1 = enter_frame(p, &f) && (
        (consume(p, 21, "+")) &&
        (a = factor(p))
    ) ? unary_plus(p, a) : 0;
    return exit_frame(p, &f, _factor_1);
}

static double *factor_2(parser_t *p) {
    frame_t f = {10, p->pos, FUNC, 0, 0};
    double *a;
    double *_factor_2;
    _factor_2 = enter_frame(p, &f) && (
        (consume(p, 22, "-")) &&
        (a = factor(p))
    ) ? unary_minus(p, a) : 0;
    return exit_frame(p, &f, _factor_2);
}

static double *factor_3(parser_t *p) {
    frame_t f = {11, p->pos, FUNC, 0, 0};
    double *a;
    double *_factor_3;
    _factor_3 = enter_frame(p, &f) && (
        (consume(p, 29, "~")) &&
        (a = factor(p))
    ) ? unary_not(p, a) : 0;
    return exit_frame(p, &f, _factor_3);
}

// power:
//     | atom '**' factor
//     | atom
static double *power(parser_t *p) {
    frame_t f = {12, p->pos, FUNC, 0, 0};
    double *a;
    double *_power;
    _power = enter_frame(p, &f) && (
        (a = power_1(p)) ||
        (a = atom(p))
    ) ? a : 0;
    return exit_frame(p, &f, _power);
}

static double *power_1(parser_t *p) {
    frame_t f = {13, p->pos, FUNC, 0, 0};
    double *a;
    double *b;
    double *_power_1;
    _power_1 = enter_frame(p, &f) && (
        (a = atom(p)) &&
        (consume(p, 38, "**")) &&
        (b = factor(p))
    ) ? binop_pow(p, a, b) : 0;
    return exit_frame(p, &f, _power_1);
}

// atom:
//     | '(' sum ')'
//     | NAME '(' [parameters] ')'
//     | NAME
//     | NUMBER
static double *atom(parser_t *p) {
    frame_t f = {14, p->pos, FUNC, 0, 0};
    double *a;
    double *_atom;
    _atom = enter_frame(p, &f) && (
        (a = atom_1(p)) ||
        (a = atom_2(p)) ||
        (a = load_const(p, consume(p, 3, "NAME"))) ||
        (a = to_double(p, consume(p, 4, "NUMBER")))
    ) ? a : 0;
    return exit_frame(p, &f, _atom);
}

static double *atom_1(parser_t *p) {
    frame_t f = {15, p->pos, FUNC, 0, 0};
    double *a;
    double *_atom_1;
    _atom_1 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = sum(p)) &&
        (consume(p, 14, ")"))
    ) ? a : 0;
    return exit_frame(p, &f, _atom_1);
}

static double *atom_2(parser_t *p) {
    frame_t f = {16, p->pos, FUNC, 0, 0};
    token_t *a;
    ast_list_t *b;
    double *_atom_2;
    _atom_2 = enter_frame(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (consume(p, 13, "(")) &&
        (b = parameters(p), 1) &&
        (consume(p, 14, ")"))
    ) ? call_func(p, a, b) : 0;
    return exit_frame(p, &f, _atom_2);
}

// parameters:
//     | ','.sum+ [',']
static ast_list_t *parameters(parser_t *p) {
    frame_t f = {17, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    token_t *b;
    ast_list_t *_parameters;
    _parameters = enter_frame(p, &f) && (
        (a = sum_delimited(p)) &&
        (b = consume(p, 7, ","), 1)
    ) ? a : 0;
    return exit_frame(p, &f, _parameters);
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
