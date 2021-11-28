#include "calc2_parser.h"
#include "peg_macros.h"

// sum:
//     | sum '+' term
//     | sum '-' term
//     | term
static FAstNode *sum(FParser *p) {
    frame_t f = {1, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = sum_1(p)) ||
        (a = sum_2(p)) ||
        (a = term(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *sum_1(FParser *p) {
    frame_t f = {2, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = sum(p)) &&
        (consume(p, 21, "+")) &&
        (b = term(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *sum_2(FParser *p) {
    frame_t f = {3, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = sum(p)) &&
        (consume(p, 22, "-")) &&
        (b = term(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// term:
//     | term '*' factor
//     | term '/' factor
//     | term '%' factor
//     | factor
static FAstNode *term(FParser *p) {
    frame_t f = {4, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = term_1(p)) ||
        (a = term_2(p)) ||
        (a = term_3(p)) ||
        (a = factor(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *term_1(FParser *p) {
    frame_t f = {5, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = term(p)) &&
        (consume(p, 23, "*")) &&
        (b = factor(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *term_2(FParser *p) {
    frame_t f = {6, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = term(p)) &&
        (consume(p, 24, "/")) &&
        (b = factor(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *term_3(FParser *p) {
    frame_t f = {7, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = term(p)) &&
        (consume(p, 25, "%")) &&
        (b = factor(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static FAstNode *factor(FParser *p) {
    frame_t f = {8, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = factor_1(p)) ||
        (a = factor_2(p)) ||
        (a = factor_3(p)) ||
        (a = power(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *factor_1(FParser *p) {
    frame_t f = {9, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 21, "+")) &&
        (a = factor(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *factor_2(FParser *p) {
    frame_t f = {10, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 22, "-")) &&
        (a = factor(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *factor_3(FParser *p) {
    frame_t f = {11, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 29, "~")) &&
        (a = factor(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// power:
//     | atom '**' factor
//     | atom
static FAstNode *power(FParser *p) {
    frame_t f = {12, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = power_1(p)) ||
        (a = atom(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *power_1(FParser *p) {
    frame_t f = {13, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = atom(p)) &&
        (consume(p, 38, "**")) &&
        (b = factor(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// atom:
//     | '(' sum ')'
//     | NAME '(' [parameters] ')'
//     | NAME
//     | NUMBER
static FAstNode *atom(FParser *p) {
    frame_t f = {14, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = atom_1(p)) ||
        (a = atom_2(p)) ||
        (a = consume(p, 3, "NAME")) ||
        (a = consume(p, 4, "NUMBER"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *atom_1(FParser *p) {
    frame_t f = {15, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = sum(p)) &&
        (consume(p, 14, ")"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *atom_2(FParser *p) {
    frame_t f = {16, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (consume(p, 13, "(")) &&
        (b = parameters(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// parameters:
//     | ','.sum+ [',']
static FAstNode *parameters(FParser *p) {
    frame_t f = {17, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 7, ",", sum)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}
