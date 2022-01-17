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
    const frame_t f = {251, p->pos, FUNC};
    double *res_251 = 0;
    if (is_memoized(p, &f, (void **) &res_251)) {
        return res_251;
    }
    double *alt_251;
    size_t maxpos;
    double *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_251;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_251 = (
                (alt_251 = sum_1(p)) ||
                (alt_251 = sum_2(p)) ||
                (alt_251 = term(p))
            ) ? alt_251 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_251 = max;
    }
    insert_memo(p, &f, res_251);
    return exit_frame(p, &f, res_251);
}

// sum '+' term
static double *sum_1(parser_t *p) {
    const frame_t f = {205, p->pos, FUNC};
    double *res_205;
    double *_sum;
    double *_term;
    res_205 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 21, "+")) &&
        (_term = term(p))
    ) ? binop_add(p, _sum, _term) : 0;
    return exit_frame(p, &f, res_205);
}

// sum '-' term
static double *sum_2(parser_t *p) {
    const frame_t f = {206, p->pos, FUNC};
    double *res_206;
    double *_sum;
    double *_term;
    res_206 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 22, "-")) &&
        (_term = term(p))
    ) ? binop_sub(p, _sum, _term) : 0;
    return exit_frame(p, &f, res_206);
}

// term (left_recursive):
//     | term '*' factor
//     | term '/' factor
//     | term '%' factor
//     | factor
static double *term(parser_t *p) {
    const frame_t f = {460, p->pos, FUNC};
    double *res_460 = 0;
    if (is_memoized(p, &f, (void **) &res_460)) {
        return res_460;
    }
    double *alt_460;
    size_t maxpos;
    double *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_460;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_460 = (
                (alt_460 = term_1(p)) ||
                (alt_460 = term_2(p)) ||
                (alt_460 = term_3(p)) ||
                (alt_460 = factor(p))
            ) ? alt_460 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_460 = max;
    }
    insert_memo(p, &f, res_460);
    return exit_frame(p, &f, res_460);
}

// term '*' factor
static double *term_1(parser_t *p) {
    const frame_t f = {758, p->pos, FUNC};
    double *res_758;
    double *_term;
    double *_factor;
    res_758 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 23, "*")) &&
        (_factor = factor(p))
    ) ? binop_mul(p, _term, _factor) : 0;
    return exit_frame(p, &f, res_758);
}

// term '/' factor
static double *term_2(parser_t *p) {
    const frame_t f = {759, p->pos, FUNC};
    double *res_759;
    double *_term;
    double *_factor;
    res_759 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 24, "/")) &&
        (_factor = factor(p))
    ) ? binop_div(p, _term, _factor) : 0;
    return exit_frame(p, &f, res_759);
}

// term '%' factor
static double *term_3(parser_t *p) {
    const frame_t f = {760, p->pos, FUNC};
    double *res_760;
    double *_term;
    double *_factor;
    res_760 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 25, "%")) &&
        (_factor = factor(p))
    ) ? binop_mod(p, _term, _factor) : 0;
    return exit_frame(p, &f, res_760);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static double *factor(parser_t *p) {
    const frame_t f = {983, p->pos, FUNC};
    double *res_983;
    double *alt_983;
    res_983 = enter_frame(p, &f) && (
        (alt_983 = factor_1(p)) ||
        (alt_983 = factor_2(p)) ||
        (alt_983 = factor_3(p)) ||
        (alt_983 = power(p))
    ) ? alt_983 : 0;
    return exit_frame(p, &f, res_983);
}

// '+' factor
static double *factor_1(parser_t *p) {
    const frame_t f = {609, p->pos, FUNC};
    double *res_609;
    double *_factor;
    res_609 = enter_frame(p, &f) && (
        (consume(p, 21, "+")) &&
        (_factor = factor(p))
    ) ? _factor : 0;
    return exit_frame(p, &f, res_609);
}

// '-' factor
static double *factor_2(parser_t *p) {
    const frame_t f = {610, p->pos, FUNC};
    double *res_610;
    double *_factor;
    res_610 = enter_frame(p, &f) && (
        (consume(p, 22, "-")) &&
        (_factor = factor(p))
    ) ? unary_minus(p, _factor) : 0;
    return exit_frame(p, &f, res_610);
}

// '~' factor
static double *factor_3(parser_t *p) {
    const frame_t f = {611, p->pos, FUNC};
    double *res_611;
    double *_factor;
    res_611 = enter_frame(p, &f) && (
        (consume(p, 29, "~")) &&
        (_factor = factor(p))
    ) ? unary_not(p, _factor) : 0;
    return exit_frame(p, &f, res_611);
}

// power:
//     | atom '**' factor
//     | atom
static double *power(parser_t *p) {
    const frame_t f = {757, p->pos, FUNC};
    double *res_757;
    double *alt_757;
    res_757 = enter_frame(p, &f) && (
        (alt_757 = power_1(p)) ||
        (alt_757 = atom(p))
    ) ? alt_757 : 0;
    return exit_frame(p, &f, res_757);
}

// atom '**' factor
static double *power_1(parser_t *p) {
    const frame_t f = {367, p->pos, FUNC};
    double *res_367;
    double *_atom;
    double *_factor;
    res_367 = enter_frame(p, &f) && (
        (_atom = atom(p)) &&
        (consume(p, 38, "**")) &&
        (_factor = factor(p))
    ) ? binop_pow(p, _atom, _factor) : 0;
    return exit_frame(p, &f, res_367);
}

// atom:
//     | '(' sum ')'
//     | NAME '(' [parameters] ')'
//     | NAME
//     | NUMBER
static double *atom(parser_t *p) {
    const frame_t f = {753, p->pos, FUNC};
    double *res_753;
    token_t *_name;
    token_t *_number;
    double *alt_753;
    res_753 = enter_frame(p, &f) && (
        (alt_753 = atom_1(p)) ||
        (alt_753 = atom_2(p)) || (
            (_name = consume(p, 3, "NAME")) &&
            (alt_753 = load_const(p, _name))
        ) || (
            (_number = consume(p, 4, "NUMBER")) &&
            (alt_753 = to_double(p, _number)))
    ) ? alt_753 : 0;
    return exit_frame(p, &f, res_753);
}

// '(' sum ')'
static double *atom_1(parser_t *p) {
    const frame_t f = {331, p->pos, FUNC};
    double *res_331;
    double *_sum;
    res_331 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_sum = sum(p)) &&
        (consume(p, 14, ")"))
    ) ? _sum : 0;
    return exit_frame(p, &f, res_331);
}

// NAME '(' [parameters] ')'
static double *atom_2(parser_t *p) {
    const frame_t f = {332, p->pos, FUNC};
    double *res_332;
    token_t *_name;
    ast_list_t *_parameters;
    res_332 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 13, "(")) &&
        (_parameters = parameters(p), 1) &&
        (consume(p, 14, ")"))
    ) ? call_func(p, _name, _parameters) : 0;
    return exit_frame(p, &f, res_332);
}

// parameters:
//     | ','.sum+ [',']
static ast_list_t *parameters(parser_t *p) {
    const frame_t f = {106, p->pos, FUNC};
    ast_list_t *res_106;
    ast_list_t *_sums;
    res_106 = enter_frame(p, &f) && (
        (_sums = sum_delimited(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _sums : 0;
    return exit_frame(p, &f, res_106);
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
