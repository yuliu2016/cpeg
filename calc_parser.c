#include "include/internal/calc_parser_internal.h"

calc_node *calc_parse(FPegParser *p, calc_entry_point entry_point) {
    if (entry_point == calc_entry_sum) return sum(p);
    return ((void *) 0);
}

// sum:
//     | sum '+' term
//     | sum '-' term
//     | term
calc_node *sum(FPegParser *p) {
    ENTER_FRAME(p, 0, "sum");
    RETURN_IF_MEMOIZED(p)
    ENTER_LEFT_RECURSION(p);
    (res = sum_1(p)) ||
    (res = sum_2(p)) ||
    (res = term(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// sum '+' term
calc_node *sum_1(FPegParser *p) {
    ENTER_FRAME(p, 1, "sum_1");
    calc_node *sum_, *term_;
    (sum_ = sum(p)) &&
    (CONSUME_TOKEN(p, 3, "+")) &&
    (term_ = term(p))
    ? (res = NODE_2(p, 1, sum_, term_)) : 0;
    EXIT_FRAME(p);
}

// sum '-' term
calc_node *sum_2(FPegParser *p) {
    ENTER_FRAME(p, 1, "sum_2");
    calc_node *sum_, *term_;
    (sum_ = sum(p)) &&
    (CONSUME_TOKEN(p, 4, "-")) &&
    (term_ = term(p))
    ? (res = NODE_2(p, 2, sum_, term_)) : 0;
    EXIT_FRAME(p);
}

// term:
//     | term '*' factor
//     | term '/' factor
//     | term '%' factor
//     | factor
calc_node *term(FPegParser *p) {
    ENTER_FRAME(p, 1, "term");
    RETURN_IF_MEMOIZED(p)
    ENTER_LEFT_RECURSION(p);
    (res = term_1(p)) ||
    (res = term_2(p)) ||
    (res = term_3(p)) ||
    (res = factor(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// term '*' factor
calc_node *term_1(FPegParser *p) {
    ENTER_FRAME(p, 6, "term_1");
    calc_node *term_, *factor_;
    (term_ = sum(p)) &&
    (CONSUME_TOKEN(p, 5, "*")) &&
    (factor_ = term(p))
    ? (res = NODE_2(p, 3, term_, factor_)) : 0;
    EXIT_FRAME(p);
}

// term '/' factor
calc_node *term_2(FPegParser *p) {
    ENTER_FRAME(p, 7, "term_2");
    calc_node *term_, *factor_;
    (term_ = sum(p)) &&
    (CONSUME_TOKEN(p, 5, "/")) &&
    (factor_ = term(p))
    ? (res = NODE_2(p, 3, term_, factor_)) : 0;
    EXIT_FRAME(p);
}

// term '%' factor
calc_node *term_3(FPegParser *p) {
    ENTER_FRAME(p, 8, "term_3");
    calc_node *term_, *factor_;
    (term_ = sum(p)) &&
    (CONSUME_TOKEN(p, 5, "%")) &&
    (factor_ = term(p))
    ? (res = NODE_2(p, 3, term_, factor_)) : 0;
    EXIT_FRAME(p);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
calc_node *factor(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor");
    (res = factor_1(p)) ||
    (res = factor_2(p)) ||
    (res = factor_3(p)) ||
    (res = power(p));
    EXIT_FRAME(p);
}

// '+' factor
calc_node *factor_1(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor_1");
    calc_node *factor_;
    (CONSUME_TOKEN(p, 5, "+")) &&
    (factor_ = factor(p))
    ? (res = NODE_1(p, 2, factor_)) : 0;
    EXIT_FRAME(p);
}

// '-' factor
calc_node *factor_2(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor_2");
    calc_node *factor_;
    (CONSUME_TOKEN(p, 5, "-")) &&
    (factor_ = factor(p))
    ? (res = NODE_1(p, 2, factor_)) : 0;
    EXIT_FRAME(p);
}

// '~' factor
calc_node *factor_3(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor_3");
    calc_node *factor_;
    (CONSUME_TOKEN(p, 5, "~")) &&
    (factor_ = factor(p))
    ? (res = NODE_1(p, 2, factor_)) : 0;
    EXIT_FRAME(p);
}

// power:
//     | atom '**' factor
//     | atom
calc_node *power(FPegParser *p) {
    ENTER_FRAME(p, 9, "power");
    (res = power_1(p)) ||
    (res = atom(p));
    EXIT_FRAME(p);
}

// atom '**' factor
calc_node *power_1(FPegParser *p) {
    ENTER_FRAME(p, 8, "power_1");
    calc_node *atom_, *factor_;
    (atom_ = atom(p)) &&
    (CONSUME_TOKEN(p, 5, "**")) &&
    (factor_ = factor(p))
    ? (res = NODE_2(p, 1, atom_, factor_)) : 0;
    EXIT_FRAME(p);
}

// atom:
//     | '(' sum ')'
//     | NAME '(' [parameters] ')'
//     | NAME
//     | NUMBER
calc_node *atom(FPegParser *p) {
    ENTER_FRAME(p, 8, "power_2");
    (res = atom_1(p)) ||
    (res = atom_2(p)) ||
    (res = CONSUME_TOKEN(p, 3, "NAME")) ||
    (res = CONSUME_TOKEN(p, 8, "NUMBER"));
    EXIT_FRAME(p);
}

// '(' sum ')'
calc_node *atom_1(FPegParser *p) {
    ENTER_FRAME(p, 9, "atom_1");
    calc_node *sum_;
    (CONSUME_TOKEN(p, 19, "(")) &&
    (sum_ = sum(p)) &&
    (CONSUME_TOKEN(p, 20, ")"))
    ? (res = NODE_1(p, 2, sum_)) : 0;
    EXIT_FRAME(p);
}

// NAME '(' [parameters] ')'
calc_node *atom_2(FPegParser *p) {
    ENTER_FRAME(p, 10, "atom_2");
    calc_node *name_, *parameters_;
    (name_ = CONSUME_TOKEN(p, 17, "NAME")) &&
    (CONSUME_TOKEN(p, 3, "(")) &&
    (parameters_ = OPTIONAL(parameters(p))) &&
    (CONSUME_TOKEN(p, 8, ")"))
    ? (res = NODE_2(p, 10, name_, parameters_)) : 0;
    EXIT_FRAME(p);
}

// parameters:
//     | ','.sum+ [',']
calc_node *parameters(FPegParser *p) {
    ENTER_FRAME(p, 10, "paramters");
    calc_node *sum_list_, *comma;
    (sum_list_ = sum_list(p)) &&
    (comma = OPTIONAL_TOKEN(p, 21, ","))
    ? (res = NODE_2(p, 11, sum_list_, comma)) : 0;
    EXIT_FRAME(p);
}

// ','.sum+
calc_node *sum_list(FPegParser *p) {
    void *node;
    if (!(node = sum(p))) {
        return ((void *) 0);
    }
    FAstList *li = LIST_NEW();
    LIST_APPEND(li, node);
    for (;;) {
        size_t pos = p->pos;
        if ((CONSUME_TOKEN(p, 20, ",")) &&
            (node = sum(p))) {
            LIST_APPEND(li, node);
        } else {
            p->pos = pos;
            break;
        }
    }
    return COPY_SEQUENCE(p, li);
}