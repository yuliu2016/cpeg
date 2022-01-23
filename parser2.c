#include "include/ast2.h"
#include "include/internal/static_parser.h"


static double *sum();
static double *sum_1();
static double *sum_2();
static double *term();
static double *term_1();
static double *term_2();
static double *term_3();
static double *factor();
static double *factor_1();
static double *factor_2();
static double *factor_3();
static double *power();
static double *power_1();
static ast_list_t *parameters();
static ast_list_t *sum_delimited();
static double *atom();
static double *atom_1();
static double *atom_2();


#define p &__parser

// sum (left_recursive):
//     | sum '+' term
//     | sum '-' term
//     | term
static double *sum() {
    size_t _pos = pos();
    double *res_251 = 0;
    memo_t *memo = fetch_memo(251, FUNC);
    if (memo) {
        return memo->node;
    }
    double *alt_251;
    size_t maxpos;
    double *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_251;
        insert_memo(_pos, 251, max);
        restore(_pos);
        res_251 = (
            (alt_251 = sum_1()) ||
            (alt_251 = sum_2()) ||
            (alt_251 = term())
        ) ? alt_251 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_251 = max;
    insert_memo(_pos, 251, res_251);
    return exit_frame(_pos, res_251, FUNC);
}

// sum '+' term
static double *sum_1() {
    size_t _pos = pos();
    double *_sum;
    double *_term;
    return (
        (_sum = sum()) &&
        (consume(21, "+")) &&
        (_term = term())
    ) ? binop_add(p, _sum, _term) :
        (restore(_pos), NULL);
}

// sum '-' term
static double *sum_2() {
    size_t _pos = pos();
    double *_sum;
    double *_term;
    return (
        (_sum = sum()) &&
        (consume(22, "-")) &&
        (_term = term())
    ) ? binop_sub(p, _sum, _term) :
        (restore(_pos), NULL);
}

// term (left_recursive):
//     | term '*' factor
//     | term '/' factor
//     | term '%' factor
//     | factor
static double *term() {
    size_t _pos = pos();
    double *res_460 = 0;
    memo_t *memo = fetch_memo(460, FUNC);
    if (memo) {
        return memo->node;
    }
    double *alt_460;
    size_t maxpos;
    double *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_460;
        insert_memo(_pos, 460, max);
        restore(_pos);
        res_460 = (
            (alt_460 = term_1()) ||
            (alt_460 = term_2()) ||
            (alt_460 = term_3()) ||
            (alt_460 = factor())
        ) ? alt_460 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_460 = max;
    insert_memo(_pos, 460, res_460);
    return exit_frame(_pos, res_460, FUNC);
}

// term '*' factor
static double *term_1() {
    size_t _pos = pos();
    double *_term;
    double *_factor;
    return (
        (_term = term()) &&
        (consume(23, "*")) &&
        (_factor = factor())
    ) ? binop_mul(p, _term, _factor) :
        (restore(_pos), NULL);
}

// term '/' factor
static double *term_2() {
    size_t _pos = pos();
    double *_term;
    double *_factor;
    return (
        (_term = term()) &&
        (consume(24, "/")) &&
        (_factor = factor())
    ) ? binop_div(p, _term, _factor) :
        (restore(_pos), NULL);
}

// term '%' factor
static double *term_3() {
    size_t _pos = pos();
    double *_term;
    double *_factor;
    return (
        (_term = term()) &&
        (consume(25, "%")) &&
        (_factor = factor())
    ) ? binop_mod(p, _term, _factor) :
        (restore(_pos), NULL);
}

// factor (memo):
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static double *factor() {
    size_t _pos = pos();
    double *res_983;
    memo_t *memo = fetch_memo(983, FUNC);
    if (memo) {
        return memo->node;
    }
    double *alt_983;
    res_983 = enter_frame(FUNC) && (
        (alt_983 = factor_1()) ||
        (alt_983 = factor_2()) ||
        (alt_983 = factor_3()) ||
        (alt_983 = power())
    ) ? alt_983 : 0;
    insert_memo(_pos, 983, res_983);
    return exit_frame(_pos, res_983, FUNC);
}

// '+' factor
static double *factor_1() {
    size_t _pos = pos();
    double *_factor;
    return (
        (consume(21, "+")) &&
        (_factor = factor())
    ) ? _factor : (restore(_pos), NULL);
}

// '-' factor
static double *factor_2() {
    size_t _pos = pos();
    double *_factor;
    return (
        (consume(22, "-")) &&
        (_factor = factor())
    ) ? unary_minus(p, _factor) :
        (restore(_pos), NULL);
}

// '~' factor
static double *factor_3() {
    size_t _pos = pos();
    double *_factor;
    return (
        (consume(29, "~")) &&
        (_factor = factor())
    ) ? unary_not(p, _factor) :
        (restore(_pos), NULL);
}

// power (memo):
//     | atom '**' factor
//     | atom
static double *power() {
    size_t _pos = pos();
    double *res_757;
    memo_t *memo = fetch_memo(757, FUNC);
    if (memo) {
        return memo->node;
    }
    double *alt_757;
    res_757 = enter_frame(FUNC) && (
        (alt_757 = power_1()) ||
        (alt_757 = atom())
    ) ? alt_757 : 0;
    insert_memo(_pos, 757, res_757);
    return exit_frame(_pos, res_757, FUNC);
}

// atom '**' factor
static double *power_1() {
    size_t _pos = pos();
    double *_atom;
    double *_factor;
    return (
        (_atom = atom()) &&
        (consume(38, "**")) &&
        (_factor = factor())
    ) ? binop_pow(p, _atom, _factor) :
        (restore(_pos), NULL);
}

// parameters:
//     | ','.sum+ [',']
static ast_list_t *parameters() {
    size_t _pos = pos();
    ast_list_t *res_106;
    ast_list_t *_sums;
    res_106 = enter_frame(FUNC) && (
        (_sums = sum_delimited()) &&
        (consume(7, ","), 1)
    ) ? _sums : 0;
    return exit_frame(_pos, res_106, FUNC);
}

static ast_list_t *sum_delimited() {
    double *_sum = sum();
    if (!_sum) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    size_t _pos;
    do {
        ast_list_append(list, _sum);
        _pos = pos();
    } while (consume(7, ",") &&
            (_sum = sum()));
    restore(_pos);
    return list;
}

// atom (memo):
//     | '(' sum ')'
//     | NAME '(' [parameters] ')'
//     | NAME
//     | NUMBER
static double *atom() {
    size_t _pos = pos();
    double *res_753;
    memo_t *memo = fetch_memo(753, FUNC);
    if (memo) {
        return memo->node;
    }
    token_t *_name;
    token_t *_number;
    double *alt_753;
    res_753 = enter_frame(FUNC) && (
        (alt_753 = atom_1()) ||
        (alt_753 = atom_2()) || (
            (_name = consume(3, "NAME")) &&
            (alt_753 = load_const(p, _name))
        ) || (
            (_number = consume(4, "NUMBER")) &&
            (alt_753 = to_double(p, _number)))
    ) ? alt_753 : 0;
    insert_memo(_pos, 753, res_753);
    return exit_frame(_pos, res_753, FUNC);
}

// '(' sum ')'
static double *atom_1() {
    size_t _pos = pos();
    double *_sum;
    return (
        (consume(13, "(")) &&
        (_sum = sum()) &&
        (consume(14, ")"))
    ) ? _sum : (restore(_pos), NULL);
}

// NAME '(' [parameters] ')'
static double *atom_2() {
    size_t _pos = pos();
    token_t *_name;
    ast_list_t *_parameters;
    return (
        (_name = consume(3, "NAME")) &&
        (consume(13, "(")) &&
        (_parameters = parameters(), 1) &&
        (consume(14, ")"))
    ) ? call_func(p, _name, _parameters) :
        (restore(_pos), NULL);
}


// Provide the static parser struct
parser_t *get_calc_parser() {
    return p;
}

// Parser Entry Point
double *parse_calc() {
    return sum();
}
