#include "include/internal/parser.h"


static void *csum(parser_t *);
static void *csum_1(parser_t *);
static void *csum_2(parser_t *);
static void *cterm(parser_t *);
static void *cterm_1(parser_t *);
static void *cterm_2(parser_t *);
static void *cterm_3(parser_t *);
static void *cfactor(parser_t *);
static void *cfactor_1(parser_t *);
static void *cfactor_2(parser_t *);
static void *cfactor_3(parser_t *);
static void *cpower(parser_t *);
static void *cpower_1(parser_t *);
static void *catom(parser_t *);
static void *catom_1(parser_t *);
static void *catom_2(parser_t *);
static void *cparameters(parser_t *);
static ast_list_t *csum_delimited(parser_t *);



// Parser Entry Point
void *parse_calc(FParser *p) {
    return csum(p);
}

// csum:
//     | csum '+' cterm
//     | csum '-' cterm
//     | cterm
static void *csum(parser_t *p) {
    frame_t f = {1, p->pos, FUNC, 0, 1};
    void *a = 0, *r = 0, *max = 0;
    size_t maxpos;
    if (!enter_frame(p, &f)) goto exit;
    do {
        memoize(p, &f, max = a, maxpos = p->pos);
        p->pos = f.f_pos;
        (a = csum_1(p)) ||
        (a = csum_2(p)) ||
        (a = cterm(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    r = max ? node_1(p, &f, max) : 0;
exit:
    return exit_frame(p, &f, r);
}

static void *csum_1(parser_t *p) {
    frame_t f = {2, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *r;
    r = enter_frame(p, &f) && (
        (a = csum(p)) &&
        (consume(p, 21, "+")) &&
        (b = cterm(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit_frame(p, &f, r);
}

static void *csum_2(parser_t *p) {
    frame_t f = {3, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *r;
    r = enter_frame(p, &f) && (
        (a = csum(p)) &&
        (consume(p, 22, "-")) &&
        (b = cterm(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit_frame(p, &f, r);
}

// cterm:
//     | cterm '*' cfactor
//     | cterm '/' cfactor
//     | cterm '%' cfactor
//     | cfactor
static void *cterm(parser_t *p) {
    frame_t f = {4, p->pos, FUNC, 0, 1};
    void *a = 0, *r = 0, *max = 0;
    size_t maxpos;
    if (!enter_frame(p, &f)) goto exit;
    do {
        memoize(p, &f, max = a, maxpos = p->pos);
        p->pos = f.f_pos;
        (a = cterm_1(p)) ||
        (a = cterm_2(p)) ||
        (a = cterm_3(p)) ||
        (a = cfactor(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    r = max ? node_1(p, &f, max) : 0;
exit:
    return exit_frame(p, &f, r);
}

static void *cterm_1(parser_t *p) {
    frame_t f = {5, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *r;
    r = enter_frame(p, &f) && (
        (a = cterm(p)) &&
        (consume(p, 23, "*")) &&
        (b = cfactor(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit_frame(p, &f, r);
}

static void *cterm_2(parser_t *p) {
    frame_t f = {6, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *r;
    r = enter_frame(p, &f) && (
        (a = cterm(p)) &&
        (consume(p, 24, "/")) &&
        (b = cfactor(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit_frame(p, &f, r);
}

static void *cterm_3(parser_t *p) {
    frame_t f = {7, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *r;
    r = enter_frame(p, &f) && (
        (a = cterm(p)) &&
        (consume(p, 25, "%")) &&
        (b = cfactor(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit_frame(p, &f, r);
}

// cfactor:
//     | '+' cfactor
//     | '-' cfactor
//     | '~' cfactor
//     | cpower
static void *cfactor(parser_t *p) {
    frame_t f = {8, p->pos, FUNC, 0, 0};
    void *a;
    void *r;
    r = enter_frame(p, &f) && (
        (a = cfactor_1(p)) ||
        (a = cfactor_2(p)) ||
        (a = cfactor_3(p)) ||
        (a = cpower(p))
    ) ? a : 0;
    return exit_frame(p, &f, r);
}

static void *cfactor_1(parser_t *p) {
    frame_t f = {9, p->pos, FUNC, 0, 0};
    void *a;
    void *r;
    r = enter_frame(p, &f) && (
        (consume(p, 21, "+")) &&
        (a = cfactor(p))
    ) ? node_1(p, &f, a) : 0;
    return exit_frame(p, &f, r);
}

static void *cfactor_2(parser_t *p) {
    frame_t f = {10, p->pos, FUNC, 0, 0};
    void *a;
    void *r;
    r = enter_frame(p, &f) && (
        (consume(p, 22, "-")) &&
        (a = cfactor(p))
    ) ? node_1(p, &f, a) : 0;
    return exit_frame(p, &f, r);
}

static void *cfactor_3(parser_t *p) {
    frame_t f = {11, p->pos, FUNC, 0, 0};
    void *a;
    void *r;
    r = enter_frame(p, &f) && (
        (consume(p, 29, "~")) &&
        (a = cfactor(p))
    ) ? node_1(p, &f, a) : 0;
    return exit_frame(p, &f, r);
}

// cpower:
//     | catom '**' cfactor
//     | catom
static void *cpower(parser_t *p) {
    frame_t f = {12, p->pos, FUNC, 0, 0};
    void *a;
    void *r;
    r = enter_frame(p, &f) && (
        (a = cpower_1(p)) ||
        (a = catom(p))
    ) ? a : 0;
    return exit_frame(p, &f, r);
}

static void *cpower_1(parser_t *p) {
    frame_t f = {13, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *r;
    r = enter_frame(p, &f) && (
        (a = catom(p)) &&
        (consume(p, 38, "**")) &&
        (b = cfactor(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit_frame(p, &f, r);
}

// catom:
//     | '(' csum ')'
//     | NAME '(' [cparameters] ')'
//     | NAME
//     | NUMBER
static void *catom(parser_t *p) {
    frame_t f = {14, p->pos, FUNC, 0, 0};
    void *a;
    void *r;
    r = enter_frame(p, &f) && (
        (a = catom_1(p)) ||
        (a = catom_2(p)) ||
        (a = consume(p, 3, "NAME")) ||
        (a = consume(p, 4, "NUMBER"))
    ) ? a : 0;
    return exit_frame(p, &f, r);
}

static void *catom_1(parser_t *p) {
    frame_t f = {15, p->pos, FUNC, 0, 0};
    void *a;
    void *r;
    r = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = csum(p)) &&
        (consume(p, 14, ")"))
    ) ? node_1(p, &f, a) : 0;
    return exit_frame(p, &f, r);
}

static void *catom_2(parser_t *p) {
    frame_t f = {16, p->pos, FUNC, 0, 0};
    token_t *a;
    void *b;
    void *r;
    r = enter_frame(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (consume(p, 13, "(")) &&
        (b = cparameters(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node_2(p, &f, a, b) : 0;
    return exit_frame(p, &f, r);
}

// cparameters:
//     | ','.csum+ [',']
static void *cparameters(parser_t *p) {
    frame_t f = {17, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    token_t *b;
    void *r;
    r = enter_frame(p, &f) && (
        (a = csum_delimited(p)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit_frame(p, &f, r);
}

static ast_list_t *csum_delimited(parser_t *p) {
    ast_list_t *s;
    void *a = csum(p);
    if (!a) return 0;
    s = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, s, a);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (a = csum(p)));
    p->pos = pos;
    return s;
}
