#include "include/calc_parser.h"

// sum:
//     | sum '+' term
//     | sum '-' term
//     | term
calc_node *sum(FPegParser *p) {
    ENTER_FRAME(p, 0, "sum");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    if ((res = sum_1(p)) ||
        (res = sum_2(p)) ||
        (res = term(p))) {}
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// sum '+' term
calc_node *sum_1(FPegParser *p) {
    ENTER_FRAME(p, 1, "sum_1");
    calc_node *sum_, *term_;
    if ((sum_ = sum(p)) &&
        (CONSUME_TOKEN(p, 3, "+")) &&
        (term_ = term(p))) {
        res = NEW_NODE(p);
        res->t = 2;
        res->v.sum_plus_term.sum = sum_;
        res->v.sum_plus_term.term = term_;
    }
    EXIT_FRAME(p);
}

// sum '-' term
calc_node *sum_2(FPegParser *p) {
    ENTER_FRAME(p, 1, "sum_2");
    calc_node *sum_, *term_;
    if ((sum_ = sum(p)) &&
        (CONSUME_TOKEN(p, 4, "-")) &&
        (term_ = term(p))) {
        res = NEW_NODE(p);
        res->t = 3;
        res->v.sum_minus_term.sum = sum_;
        res->v.sum_minus_term.term = term_;
    }
    EXIT_FRAME(p);
}

// term:
//     | term '*' factor
//     | term '/' factor
//     | term '%' factor
//     | factor
calc_node *term(FPegParser *p) {
    ENTER_FRAME(p, 1, "term");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    if ((res = term_1(p)) ||
        (res = term_2(p)) ||
        (res = term_3(p)) ||
        (res = factor(p))) {}
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// term '*' factor
calc_node *term_1(FPegParser *p) {
    ENTER_FRAME(p, 6, "term_1");
    calc_node *term_, *factor_;
    if ((term_ = sum(p)) &&
        (CONSUME_TOKEN(p, 5, "*")) &&
        (factor_ = term(p))) {
        res = NEW_NODE(p);
        res->t = 1;
        res->v.term_multiply_factor.term = term_;
        res->v.term_multiply_factor.factor = factor_;
    }
    EXIT_FRAME(p);
}

// term '/' factor
calc_node *term_2(FPegParser *p) {
    ENTER_FRAME(p, 7, "term_2");
    calc_node *term_, *factor_;
    if ((term_ = sum(p)) &&
        (CONSUME_TOKEN(p, 5, "/")) &&
        (factor_ = term(p))) {
        res = NEW_NODE(p);
        res->t = 1;
        res->v.term_divide_factor.term = term_;
        res->v.term_divide_factor.factor = factor_;
    }
    EXIT_FRAME(p);
}

// term '%' factor
calc_node *term_3(FPegParser *p) {
    ENTER_FRAME(p, 8, "term_3");
    calc_node *term_, *factor_;
    if ((term_ = sum(p)) &&
        (CONSUME_TOKEN(p, 5, "%")) &&
        (factor_ = term(p))) {
        res = NEW_NODE(p);
        res->t = 1;
        res->v.term_modulus_factor.term = term_;
        res->v.term_modulus_factor.factor = factor_;
    }
    EXIT_FRAME(p);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
calc_node *factor(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor");
    if ((res = factor_1(p)) ||
        (res = factor_2(p)) ||
        (res = factor_3(p)) ||
        (res = power(p))) {}
    EXIT_FRAME(p);
}

// '+' factor
calc_node *factor_1(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor_1");
    calc_node *factor_;
    if ((CONSUME_TOKEN(p, 5, "+")) &&
        (factor_ = factor(p))) {
        res = NEW_NODE(p);
        res->t = 1;
        res->v.plus_factor.factor = factor_;
    }
    EXIT_FRAME(p);
}

// '-' factor
calc_node *factor_2(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor_2");
    calc_node *factor_;
    if ((CONSUME_TOKEN(p, 5, "-")) &&
        (factor_ = factor(p))) {
        res = NEW_NODE(p);
        res->t = 1;
        res->v.minus_factor.factor = factor_;
    }
    EXIT_FRAME(p);
}

// '~' factor
calc_node *factor_3(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor_3");
    calc_node *factor_;
    if ((CONSUME_TOKEN(p, 5, "~")) &&
        (factor_ = factor(p))) {
        res = NEW_NODE(p);
        res->t = 1;
        res->v.invert_factor.factor = factor_;
    }
    EXIT_FRAME(p);
}

// power:
//     | atom '**' factor
//     | atom
calc_node *power(FPegParser *p) {
    ENTER_FRAME(p, 9, "power");
    if ((res = power_1(p)) ||
        (res = atom(p))) {}
    EXIT_FRAME(p);
}

// atom '**' factor
calc_node *power_1(FPegParser *p) {
    ENTER_FRAME(p, 8, "power_1");
    calc_node *atom_, *factor_;
    if ((atom_ = atom(p)) &&
        (CONSUME_TOKEN(p, 5, "**")) &&
        (factor_ = factor(p))) {
        res = NEW_NODE(p);
        res->t = 1;
        res->v.atom_power_factor.atom = atom_;
        res->v.atom_power_factor.factor = factor_;
    }
    EXIT_FRAME(p);
}

// atom:
//     | '(' sum ')'
//     | NAME '(' [parameters] ')'
//     | NAME
//     | NUMBER
calc_node *atom(FPegParser *p) {
    ENTER_FRAME(p, 8, "power_2");
    if ((res = atom_1(p)) ||
        (res = atom_2(p)) ||
        (res = TOKEN_AS_NODE(p, 3, "NAME")) ||
        (res = TOKEN_AS_NODE(p, 8, "NUMBER"))) {
    }
    EXIT_FRAME(p);
}

// '(' sum ')'
calc_node *atom_1(FPegParser *p) {
    ENTER_FRAME(p, 9, "atom_1");
    calc_node *sum_;
    if ((CONSUME_TOKEN(p, 19, "(")) &&
        (sum_ = sum(p)) &&
        (CONSUME_TOKEN(p, 20, ")"))) {
        res = NEW_NODE(p);
        res->t = 9;
        res->v.lpar_sum_rpar.sum = sum_;
    }
    EXIT_FRAME(p);
}

// NAME '(' [parameters] ')'
calc_node *atom_2(FPegParser *p) {
    ENTER_FRAME(p, 10, "atom_2");
    FToken *name_;
    calc_node *parameters_;
    if ((name_ = CONSUME_TOKEN(p, 17, "NAME")) &&
        (CONSUME_TOKEN(p, 3, "(")) &&
        (parameters_ = OPTIONAL(parameters(p))) &&
        (CONSUME_TOKEN(p, 8, ")"))) {
        res = NEW_NODE(p);
        res->t = 10;
        res->v.name_lpar_parameters_rpar.name = name_;
        res->v.name_lpar_parameters_rpar.parameters = parameters_;
    }
    EXIT_FRAME(p);
}

// parameters:
//     | ','.sum+ [',']
calc_node *parameters(FPegParser *p) {
    ENTER_FRAME(p, 10, "paramters");
    calc_sequence *sum_list_;
    FToken *comma;
    if ((sum_list_ = sum_list(p)) &&
        (comma = OPTIONAL(CONSUME_TOKEN(p, 21, ",")))) {
        res = NEW_NODE(p);
        res->t = 10;
        res->v.sum_list_comma.sum_list = sum_list_;
        res->v.sum_list_comma.comma = comma;
    }
    EXIT_FRAME(p);
}

// ','.sum+
calc_sequence *sum_list(FPegParser *p) {
    calc_node *node;
    if (!(node = sum(p))) {
        return ((void *) 0);
    }
    FPegList *li = LIST_NEW();
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