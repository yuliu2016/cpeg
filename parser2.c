#include "include/internal/parser.h"


static double *csum(parser_t *);
static double *csum_1(parser_t *);
static double *csum_2(parser_t *);
static double *cterm(parser_t *);
static double *cterm_1(parser_t *);
static double *cterm_2(parser_t *);
static double *cterm_3(parser_t *);
static double *cfactor(parser_t *);
static double *cfactor_1(parser_t *);
static double *cfactor_2(parser_t *);
static double *cfactor_3(parser_t *);
static double *cpower(parser_t *);
static double *cpower_1(parser_t *);
static double *catom(parser_t *);
static double *catom_1(parser_t *);
static double *catom_2(parser_t *);
static ast_list_t *cparameters(parser_t *);
static ast_list_t *csum_delimited(parser_t *);



// Parser Entry Point
void *parse_calc(FParser *p) {
    return csum(p);
}

// csum (left_recursive):
//     | csum '+' cterm
//     | csum '-' cterm
//     | cterm
static double *csum(parser_t *p) {
    frame_t f = {1, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    double *a = 0;
    double *_csum = 0;
    double *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = csum_1(p)) ||
        (a = csum_2(p)) ||
        (a = cterm(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    _csum = max ? node_1(p, &f, max) : 0;
    return exit_frame(p, &f, _csum);
}

static double *csum_1(parser_t *p) {
    frame_t f = {2, p->pos, FUNC, 0, 0};
    double *a;
    double *b;
    double *_csum_1;
    _csum_1 = enter_frame(p, &f) && (
        (a = csum(p)) &&
        (consume(p, 21, "+")) &&
        (b = cterm(p))
    ) ? binop_add(p, a, b) : 0;
    return exit_frame(p, &f, _csum_1);
}

static double *csum_2(parser_t *p) {
    frame_t f = {3, p->pos, FUNC, 0, 0};
    double *a;
    double *b;
    double *_csum_2;
    _csum_2 = enter_frame(p, &f) && (
        (a = csum(p)) &&
        (consume(p, 22, "-")) &&
        (b = cterm(p))
    ) ? binop_sub(p, a, b) : 0;
    return exit_frame(p, &f, _csum_2);
}

// cterm (left_recursive):
//     | cterm '*' cfactor
//     | cterm '/' cfactor
//     | cterm '%' cfactor
//     | cfactor
static double *cterm(parser_t *p) {
    frame_t f = {4, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    double *a = 0;
    double *_cterm = 0;
    double *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = cterm_1(p)) ||
        (a = cterm_2(p)) ||
        (a = cterm_3(p)) ||
        (a = cfactor(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    _cterm = max ? node_1(p, &f, max) : 0;
    return exit_frame(p, &f, _cterm);
}

static double *cterm_1(parser_t *p) {
    frame_t f = {5, p->pos, FUNC, 0, 0};
    double *a;
    double *b;
    double *_cterm_1;
    _cterm_1 = enter_frame(p, &f) && (
        (a = cterm(p)) &&
        (consume(p, 23, "*")) &&
        (b = cfactor(p))
    ) ? binop_mul(p, a, b) : 0;
    return exit_frame(p, &f, _cterm_1);
}

static double *cterm_2(parser_t *p) {
    frame_t f = {6, p->pos, FUNC, 0, 0};
    double *a;
    double *b;
    double *_cterm_2;
    _cterm_2 = enter_frame(p, &f) && (
        (a = cterm(p)) &&
        (consume(p, 24, "/")) &&
        (b = cfactor(p))
    ) ? binop_div(p, a, b) : 0;
    return exit_frame(p, &f, _cterm_2);
}

static double *cterm_3(parser_t *p) {
    frame_t f = {7, p->pos, FUNC, 0, 0};
    double *a;
    double *b;
    double *_cterm_3;
    _cterm_3 = enter_frame(p, &f) && (
        (a = cterm(p)) &&
        (consume(p, 25, "%")) &&
        (b = cfactor(p))
    ) ? binop_mod(p, a, b) : 0;
    return exit_frame(p, &f, _cterm_3);
}

// cfactor:
//     | '+' cfactor
//     | '-' cfactor
//     | '~' cfactor
//     | cpower
static double *cfactor(parser_t *p) {
    frame_t f = {8, p->pos, FUNC, 0, 0};
    double *a;
    double *_cfactor;
    _cfactor = enter_frame(p, &f) && (
        (a = cfactor_1(p)) ||
        (a = cfactor_2(p)) ||
        (a = cfactor_3(p)) ||
        (a = cpower(p))
    ) ? a : 0;
    return exit_frame(p, &f, _cfactor);
}

static double *cfactor_1(parser_t *p) {
    frame_t f = {9, p->pos, FUNC, 0, 0};
    double *a;
    double *_cfactor_1;
    _cfactor_1 = enter_frame(p, &f) && (
        (consume(p, 21, "+")) &&
        (a = cfactor(p))
    ) ? unary_plus(p, a) : 0;
    return exit_frame(p, &f, _cfactor_1);
}

static double *cfactor_2(parser_t *p) {
    frame_t f = {10, p->pos, FUNC, 0, 0};
    double *a;
    double *_cfactor_2;
    _cfactor_2 = enter_frame(p, &f) && (
        (consume(p, 22, "-")) &&
        (a = cfactor(p))
    ) ? unary_minus(p, a) : 0;
    return exit_frame(p, &f, _cfactor_2);
}

static double *cfactor_3(parser_t *p) {
    frame_t f = {11, p->pos, FUNC, 0, 0};
    double *a;
    double *_cfactor_3;
    _cfactor_3 = enter_frame(p, &f) && (
        (consume(p, 29, "~")) &&
        (a = cfactor(p))
    ) ? unary_not(p, a) : 0;
    return exit_frame(p, &f, _cfactor_3);
}

// cpower:
//     | catom '**' cfactor
//     | catom
static double *cpower(parser_t *p) {
    frame_t f = {12, p->pos, FUNC, 0, 0};
    double *a;
    double *_cpower;
    _cpower = enter_frame(p, &f) && (
        (a = cpower_1(p)) ||
        (a = catom(p))
    ) ? a : 0;
    return exit_frame(p, &f, _cpower);
}

static double *cpower_1(parser_t *p) {
    frame_t f = {13, p->pos, FUNC, 0, 0};
    double *a;
    double *b;
    double *_cpower_1;
    _cpower_1 = enter_frame(p, &f) && (
        (a = catom(p)) &&
        (consume(p, 38, "**")) &&
        (b = cfactor(p))
    ) ? binop_pow(p, a, b) : 0;
    return exit_frame(p, &f, _cpower_1);
}

// catom:
//     | '(' csum ')'
//     | NAME '(' [cparameters] ')'
//     | NAME
//     | NUMBER
static double *catom(parser_t *p) {
    frame_t f = {14, p->pos, FUNC, 0, 0};
    double *a;
    double *_catom;
    _catom = enter_frame(p, &f) && (
        (a = catom_1(p)) ||
        (a = catom_2(p)) ||
        (a = load_const(p, consume(p, 3, "NAME"))) ||
        (a = to_double(p, consume(p, 4, "NUMBER")))
    ) ? a : 0;
    return exit_frame(p, &f, _catom);
}

static double *catom_1(parser_t *p) {
    frame_t f = {15, p->pos, FUNC, 0, 0};
    double *a;
    double *_catom_1;
    _catom_1 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = csum(p)) &&
        (consume(p, 14, ")"))
    ) ? a : 0;
    return exit_frame(p, &f, _catom_1);
}

static double *catom_2(parser_t *p) {
    frame_t f = {16, p->pos, FUNC, 0, 0};
    token_t *a;
    ast_list_t *b;
    double *_catom_2;
    _catom_2 = enter_frame(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (consume(p, 13, "(")) &&
        (b = cparameters(p), 1) &&
        (consume(p, 14, ")"))
    ) ? call_func(p, a, b) : 0;
    return exit_frame(p, &f, _catom_2);
}

// cparameters:
//     | ','.csum+ [',']
static ast_list_t *cparameters(parser_t *p) {
    frame_t f = {17, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    token_t *b;
    ast_list_t *_cparameters;
    _cparameters = enter_frame(p, &f) && (
        (a = csum_delimited(p)) &&
        (b = consume(p, 7, ","), 1)
    ) ? a : 0;
    return exit_frame(p, &f, _cparameters);
}

static ast_list_t *csum_delimited(parser_t *p) {
    double *_csum = csum(p);
    if (!_csum) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _csum);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_csum = csum(p)));
    p->pos = pos;
    return list;
}
