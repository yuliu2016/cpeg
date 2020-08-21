#include "include/calc_parser.h"
#include "include/internal/peg_macros.h"

FAstNode *sum_rule(FPegParser *p);

FAstNode *sum_1(FPegParser *p);

FAstNode *sum_2(FPegParser *p);

FAstNode *term_rule(FPegParser *p);

FAstNode *term_1(FPegParser *p);

FAstNode *term_2(FPegParser *p);

FAstNode *term_3(FPegParser *p);

FAstNode *factor_rule(FPegParser *p);

FAstNode *factor_1(FPegParser *p);

FAstNode *factor_2(FPegParser *p);

FAstNode *factor_3(FPegParser *p);

FAstNode *power_rule(FPegParser *p);

FAstNode *power_1(FPegParser *p);

FAstNode *atom_rule(FPegParser *p);

FAstNode *atom_1(FPegParser *p);

FAstNode *atom_2(FPegParser *p);

FAstNode *parameters_rule(FPegParser *p);

FAstNode *sum_loop(FPegParser *p);

// Parser Entry Point
FAstNode *calc_parse(FPegParser *p, calc_entry_point entry_point) {
    if (entry_point == calc_entry_sum) return sum_rule(p);
    return ((void *) 0);
}

// sum:
//     | sum '+' term
//     | sum '-' term
//     | term
FAstNode *sum_rule(FPegParser *p) {
    ENTER_FRAME(p, 0, "sum");
    RETURN_IF_MEMOIZED(p)
    ENTER_LEFT_RECURSION(p);
    (res = sum_1(p)) ||
    (res = sum_2(p)) ||
    (res = term_rule(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// sum '+' term
FAstNode *sum_1(FPegParser *p) {
    ENTER_FRAME(p, 1, "sum_1");
    FAstNode *sum, *term;
    (sum = sum_rule(p)) &&
    (AST_CONSUME(p, 3, "+")) &&
    (term = term_rule(p))
    ? (res = AST_NODE_2(p, sum, term)) : 0;
    EXIT_FRAME(p);
}

// sum '-' term
FAstNode *sum_2(FPegParser *p) {
    ENTER_FRAME(p, 1, "sum_2");
    FAstNode *sum, *term;
    (sum = sum_rule(p)) &&
    (AST_CONSUME(p, 4, "-")) &&
    (term = term_rule(p))
    ? (res = AST_NODE_2(p, sum, term)) : 0;
    EXIT_FRAME(p);
}

// term:
//     | term '*' factor
//     | term '/' factor
//     | term '%' factor
//     | factor
FAstNode *term_rule(FPegParser *p) {
    ENTER_FRAME(p, 1, "term");
    RETURN_IF_MEMOIZED(p)
    ENTER_LEFT_RECURSION(p);
    (res = term_1(p)) ||
    (res = term_2(p)) ||
    (res = term_3(p)) ||
    (res = factor_rule(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// term '*' factor
FAstNode *term_1(FPegParser *p) {
    ENTER_FRAME(p, 6, "term_1");
    FAstNode *term, *factor;
    (term = term_rule(p)) &&
    (AST_CONSUME(p, 5, "*")) &&
    (factor = factor_rule(p))
    ? (res = AST_NODE_2(p, term, factor)) : 0;
    EXIT_FRAME(p);
}

// term '/' factor
FAstNode *term_2(FPegParser *p) {
    ENTER_FRAME(p, 7, "term_2");
    FAstNode *term, *factor;
    (term = term_rule(p)) &&
    (AST_CONSUME(p, 5, "/")) &&
    (factor = factor_rule(p))
    ? (res = AST_NODE_2(p, term, factor)) : 0;
    EXIT_FRAME(p);
}

// term '%' factor
FAstNode *term_3(FPegParser *p) {
    ENTER_FRAME(p, 8, "term_3");
    FAstNode *term, *factor;
    (term = term_rule(p)) &&
    (AST_CONSUME(p, 5, "%")) &&
    (factor = factor_rule(p))
    ? (res = AST_NODE_2(p, term, factor)) : 0;
    EXIT_FRAME(p);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
FAstNode *factor_rule(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor");
    (res = factor_1(p)) ||
    (res = factor_2(p)) ||
    (res = factor_3(p)) ||
    (res = power_rule(p));
    EXIT_FRAME(p);
}

// '+' factor
FAstNode *factor_1(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor_1");
    FAstNode *factor;
    (AST_CONSUME(p, 5, "+")) &&
    (factor = factor_rule(p))
    ? (res = AST_NODE_1(p, factor)) : 0;
    EXIT_FRAME(p);
}

// '-' factor
FAstNode *factor_2(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor_2");
    FAstNode *factor;
    (AST_CONSUME(p, 5, "-")) &&
    (factor = factor_rule(p))
    ? (res = AST_NODE_1(p, factor)) : 0;
    EXIT_FRAME(p);
}

// '~' factor
FAstNode *factor_3(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor_3");
    FAstNode *factor;
    (AST_CONSUME(p, 5, "~")) &&
    (factor = factor_rule(p))
    ? (res = AST_NODE_1(p, factor)) : 0;
    EXIT_FRAME(p);
}

// power:
//     | atom '**' factor
//     | atom
FAstNode *power_rule(FPegParser *p) {
    ENTER_FRAME(p, 9, "power");
    (res = power_1(p)) ||
    (res = atom_rule(p));
    EXIT_FRAME(p);
}

// atom '**' factor
FAstNode *power_1(FPegParser *p) {
    ENTER_FRAME(p, 8, "power_1");
    FAstNode *atom, *factor;
    (atom = atom_rule(p)) &&
    (AST_CONSUME(p, 5, "**")) &&
    (factor = factor_rule(p))
    ? (res = AST_NODE_2(p, atom, factor)) : 0;
    EXIT_FRAME(p);
}

// atom:
//     | '(' sum ')'
//     | NAME '(' [parameters] ')'
//     | NAME
//     | NUMBER
FAstNode *atom_rule(FPegParser *p) {
    ENTER_FRAME(p, 8, "power_2");
    (res = atom_1(p)) ||
    (res = atom_2(p)) ||
    (res = AST_CONSUME(p, 3, "NAME")) ||
    (res = AST_CONSUME(p, 8, "NUMBER"));
    EXIT_FRAME(p);
}

// '(' sum ')'
FAstNode *atom_1(FPegParser *p) {
    ENTER_FRAME(p, 9, "atom_1");
    FAstNode *sum;
    (AST_CONSUME(p, 19, "(")) &&
    (sum = sum_rule(p)) &&
    (AST_CONSUME(p, 20, ")"))
    ? (res = AST_NODE_1(p, sum)) : 0;
    EXIT_FRAME(p);
}

// NAME '(' [parameters] ')'
FAstNode *atom_2(FPegParser *p) {
    ENTER_FRAME(p, 10, "atom_2");
    FAstNode *name, *parameters;
    (name = AST_CONSUME(p, 17, "NAME")) &&
    (AST_CONSUME(p, 3, "(")) &&
    (parameters = OPTIONAL(parameters_rule(p))) &&
    (AST_CONSUME(p, 8, ")"))
    ? (res = AST_NODE_2(p, name, parameters)) : 0;
    EXIT_FRAME(p);
}

// parameters:
//     | ','.sum+ [',']
FAstNode *parameters_rule(FPegParser *p) {
    ENTER_FRAME(p, 10, "paramters");
    FAstNode *sum_list_, *comma;
    (sum_list_ = sum_loop(p)) &&
    (comma = OPTIONAL_TOKEN(p, 21, ","))
    ? (res = AST_NODE_2(p, sum_list_, comma)) : 0;
    EXIT_FRAME(p);
}

// ','.sum+
FAstNode *sum_loop(FPegParser *p) {
    FAstNode *node, *seq;
    if (!(node = sum_rule(p))) { return ((void *) 0); }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 20, ",")) &&
            (node = sum_rule(p)));
    p->pos = pos;
    return seq;
}