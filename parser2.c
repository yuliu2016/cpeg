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
    frame_t f = {251, _pos(), FUNC};
    double *res_251 = 0;
    if (_is_memoized(&f, (void **) &res_251)) {
        return res_251;
    }
    double *alt_251;
    size_t maxpos;
    double *max;
    if (_enter_frame(&f)) {
        do {
            maxpos = _pos();
            max = res_251;
            _insert_memo(&f, max);
            _set_pos(f.f_pos);
            res_251 = (
                (alt_251 = sum_1()) ||
                (alt_251 = sum_2()) ||
                (alt_251 = term())
            ) ? alt_251 : 0;
        } while (_pos() > maxpos);
        _set_pos(maxpos);
        res_251 = max;
    }
    _insert_memo(&f, res_251);
    return _exit_frame(&f, res_251);
}

// sum '+' term
static double *sum_1() {
    size_t pos = _pos();
    double *_sum;
    double *_term;
    return (
        (_sum = sum()) &&
        (_consume(21, "+")) &&
        (_term = term())
    ) ? binop_add(p, _sum, _term) :
        (_set_pos(pos), NULL);
}

// sum '-' term
static double *sum_2() {
    size_t pos = _pos();
    double *_sum;
    double *_term;
    return (
        (_sum = sum()) &&
        (_consume(22, "-")) &&
        (_term = term())
    ) ? binop_sub(p, _sum, _term) :
        (_set_pos(pos), NULL);
}

// term (left_recursive):
//     | term '*' factor
//     | term '/' factor
//     | term '%' factor
//     | factor
static double *term() {
    frame_t f = {460, _pos(), FUNC};
    double *res_460 = 0;
    if (_is_memoized(&f, (void **) &res_460)) {
        return res_460;
    }
    double *alt_460;
    size_t maxpos;
    double *max;
    if (_enter_frame(&f)) {
        do {
            maxpos = _pos();
            max = res_460;
            _insert_memo(&f, max);
            _set_pos(f.f_pos);
            res_460 = (
                (alt_460 = term_1()) ||
                (alt_460 = term_2()) ||
                (alt_460 = term_3()) ||
                (alt_460 = factor())
            ) ? alt_460 : 0;
        } while (_pos() > maxpos);
        _set_pos(maxpos);
        res_460 = max;
    }
    _insert_memo(&f, res_460);
    return _exit_frame(&f, res_460);
}

// term '*' factor
static double *term_1() {
    size_t pos = _pos();
    double *_term;
    double *_factor;
    return (
        (_term = term()) &&
        (_consume(23, "*")) &&
        (_factor = factor())
    ) ? binop_mul(p, _term, _factor) :
        (_set_pos(pos), NULL);
}

// term '/' factor
static double *term_2() {
    size_t pos = _pos();
    double *_term;
    double *_factor;
    return (
        (_term = term()) &&
        (_consume(24, "/")) &&
        (_factor = factor())
    ) ? binop_div(p, _term, _factor) :
        (_set_pos(pos), NULL);
}

// term '%' factor
static double *term_3() {
    size_t pos = _pos();
    double *_term;
    double *_factor;
    return (
        (_term = term()) &&
        (_consume(25, "%")) &&
        (_factor = factor())
    ) ? binop_mod(p, _term, _factor) :
        (_set_pos(pos), NULL);
}

// factor (memo):
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static double *factor() {
    frame_t f = {983, _pos(), FUNC};
    double *res_983;
    if (_is_memoized(&f, (void **) &res_983)) {
        return res_983;
    }
    double *alt_983;
    res_983 = _enter_frame(&f) && (
        (alt_983 = factor_1()) ||
        (alt_983 = factor_2()) ||
        (alt_983 = factor_3()) ||
        (alt_983 = power())
    ) ? alt_983 : 0;
    _insert_memo(&f, res_983);
    return _exit_frame(&f, res_983);
}

// '+' factor
static double *factor_1() {
    size_t pos = _pos();
    double *_factor;
    return (
        (_consume(21, "+")) &&
        (_factor = factor())
    ) ? _factor : (_set_pos(pos), NULL);
}

// '-' factor
static double *factor_2() {
    size_t pos = _pos();
    double *_factor;
    return (
        (_consume(22, "-")) &&
        (_factor = factor())
    ) ? unary_minus(p, _factor) :
        (_set_pos(pos), NULL);
}

// '~' factor
static double *factor_3() {
    size_t pos = _pos();
    double *_factor;
    return (
        (_consume(29, "~")) &&
        (_factor = factor())
    ) ? unary_not(p, _factor) :
        (_set_pos(pos), NULL);
}

// power (memo):
//     | atom '**' factor
//     | atom
static double *power() {
    frame_t f = {757, _pos(), FUNC};
    double *res_757;
    if (_is_memoized(&f, (void **) &res_757)) {
        return res_757;
    }
    double *alt_757;
    res_757 = _enter_frame(&f) && (
        (alt_757 = power_1()) ||
        (alt_757 = atom())
    ) ? alt_757 : 0;
    _insert_memo(&f, res_757);
    return _exit_frame(&f, res_757);
}

// atom '**' factor
static double *power_1() {
    size_t pos = _pos();
    double *_atom;
    double *_factor;
    return (
        (_atom = atom()) &&
        (_consume(38, "**")) &&
        (_factor = factor())
    ) ? binop_pow(p, _atom, _factor) :
        (_set_pos(pos), NULL);
}

// parameters:
//     | ','.sum+ [',']
static ast_list_t *parameters() {
    frame_t f = {106, _pos(), FUNC};
    ast_list_t *res_106;
    ast_list_t *_sums;
    res_106 = _enter_frame(&f) && (
        (_sums = sum_delimited()) &&
        (_consume(7, ","), 1)
    ) ? _sums : 0;
    return _exit_frame(&f, res_106);
}

static ast_list_t *sum_delimited() {
    double *_sum = sum();
    if (!_sum) {
        return 0;
    }
    ast_list_t *list = _ast_list_new();
    size_t pos;
    do {
        _ast_list_append(list, _sum);
        pos = _pos();
    } while (_consume(7, ",") &&
            (_sum = sum()));
    _set_pos(pos);
    return list;
}

// atom (memo):
//     | '(' sum ')'
//     | NAME '(' [parameters] ')'
//     | NAME
//     | NUMBER
static double *atom() {
    frame_t f = {753, _pos(), FUNC};
    double *res_753;
    if (_is_memoized(&f, (void **) &res_753)) {
        return res_753;
    }
    token_t *_name;
    token_t *_number;
    double *alt_753;
    res_753 = _enter_frame(&f) && (
        (alt_753 = atom_1()) ||
        (alt_753 = atom_2()) || (
            (_name = _consume(3, "NAME")) &&
            (alt_753 = load_const(p, _name))
        ) || (
            (_number = _consume(4, "NUMBER")) &&
            (alt_753 = to_double(p, _number)))
    ) ? alt_753 : 0;
    _insert_memo(&f, res_753);
    return _exit_frame(&f, res_753);
}

// '(' sum ')'
static double *atom_1() {
    size_t pos = _pos();
    double *_sum;
    return (
        (_consume(13, "(")) &&
        (_sum = sum()) &&
        (_consume(14, ")"))
    ) ? _sum : (_set_pos(pos), NULL);
}

// NAME '(' [parameters] ')'
static double *atom_2() {
    size_t pos = _pos();
    token_t *_name;
    ast_list_t *_parameters;
    return (
        (_name = _consume(3, "NAME")) &&
        (_consume(13, "(")) &&
        (_parameters = parameters(), 1) &&
        (_consume(14, ")"))
    ) ? call_func(p, _name, _parameters) :
        (_set_pos(pos), NULL);
}


// Provide the static parser struct
parser_t *get_calc_parser() {
    return p;
}

// Parser Entry Point
double *parse_calc() {
    return sum();
}
