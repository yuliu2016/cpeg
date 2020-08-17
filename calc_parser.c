#include "include/calc_parser.h"
#include "include/internal/peg_macros.h"

FAstNode *sum(FPegParser *p);

FAstNode *sum_1(FPegParser *p);

FAstNode *sum_2(FPegParser *p);

FAstNode *term(FPegParser *p);

FAstNode *term_1(FPegParser *p);

FAstNode *term_2(FPegParser *p);

FAstNode *term_3(FPegParser *p);

FAstNode *factor(FPegParser *p);

FAstNode *factor_1(FPegParser *p);

FAstNode *factor_2(FPegParser *p);

FAstNode *factor_3(FPegParser *p);

FAstNode *power(FPegParser *p);

FAstNode *power_1(FPegParser *p);

FAstNode *atom(FPegParser *p);

FAstNode *atom_1(FPegParser *p);

FAstNode *atom_2(FPegParser *p);

FAstNode *parameters(FPegParser *p);

FAstNode *sum_list(FPegParser *p);

// Parser Entry Point
FAstNode *calc_parse(FPegParser *p, calc_entry_point entry_point) {
    if (entry_point == calc_entry_sum) return sum(p);
    return ((void *) 0);
}

// sum:
//     | sum '+' term
//     | sum '-' term
//     | term
FAstNode *sum(FPegParser *p) {
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
FAstNode *sum_1(FPegParser *p) {
    ENTER_FRAME(p, 1, "sum_1");
    FAstNode *sum_, *term_;
    (sum_ = sum(p)) &&
    (AST_CONSUME(p, 3, "+")) &&
    (term_ = term(p))
    ? (res = AST_NODE_2(p, 1, sum_, term_)) : 0;
    EXIT_FRAME(p);
}

// sum '-' term
FAstNode *sum_2(FPegParser *p) {
    ENTER_FRAME(p, 1, "sum_2");
    FAstNode *sum_, *term_;
    (sum_ = sum(p)) &&
    (AST_CONSUME(p, 4, "-")) &&
    (term_ = term(p))
    ? (res = AST_NODE_2(p, 2, sum_, term_)) : 0;
    EXIT_FRAME(p);
}

// term:
//     | term '*' factor
//     | term '/' factor
//     | term '%' factor
//     | factor
FAstNode *term(FPegParser *p) {
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
FAstNode *term_1(FPegParser *p) {
    ENTER_FRAME(p, 6, "term_1");
    FAstNode *term_, *factor_;
    (term_ = sum(p)) &&
    (AST_CONSUME(p, 5, "*")) &&
    (factor_ = term(p))
    ? (res = AST_NODE_2(p, 3, term_, factor_)) : 0;
    EXIT_FRAME(p);
}

// term '/' factor
FAstNode *term_2(FPegParser *p) {
    ENTER_FRAME(p, 7, "term_2");
    FAstNode *term_, *factor_;
    (term_ = sum(p)) &&
    (AST_CONSUME(p, 5, "/")) &&
    (factor_ = term(p))
    ? (res = AST_NODE_2(p, 3, term_, factor_)) : 0;
    EXIT_FRAME(p);
}

// term '%' factor
FAstNode *term_3(FPegParser *p) {
    ENTER_FRAME(p, 8, "term_3");
    FAstNode *term_, *factor_;
    (term_ = sum(p)) &&
    (AST_CONSUME(p, 5, "%")) &&
    (factor_ = term(p))
    ? (res = AST_NODE_2(p, 3, term_, factor_)) : 0;
    EXIT_FRAME(p);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
FAstNode *factor(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor");
    (res = factor_1(p)) ||
    (res = factor_2(p)) ||
    (res = factor_3(p)) ||
    (res = power(p));
    EXIT_FRAME(p);
}

// '+' factor
FAstNode *factor_1(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor_1");
    FAstNode *factor_;
    (AST_CONSUME(p, 5, "+")) &&
    (factor_ = factor(p))
    ? (res = AST_NODE_1(p, 2, factor_)) : 0;
    EXIT_FRAME(p);
}

// '-' factor
FAstNode *factor_2(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor_2");
    FAstNode *factor_;
    (AST_CONSUME(p, 5, "-")) &&
    (factor_ = factor(p))
    ? (res = AST_NODE_1(p, 2, factor_)) : 0;
    EXIT_FRAME(p);
}

// '~' factor
FAstNode *factor_3(FPegParser *p) {
    ENTER_FRAME(p, 8, "factor_3");
    FAstNode *factor_;
    (AST_CONSUME(p, 5, "~")) &&
    (factor_ = factor(p))
    ? (res = AST_NODE_1(p, 2, factor_)) : 0;
    EXIT_FRAME(p);
}

// power:
//     | atom '**' factor
//     | atom
FAstNode *power(FPegParser *p) {
    ENTER_FRAME(p, 9, "power");
    (res = power_1(p)) ||
    (res = atom(p));
    EXIT_FRAME(p);
}

// atom '**' factor
FAstNode *power_1(FPegParser *p) {
    ENTER_FRAME(p, 8, "power_1");
    FAstNode *atom_, *factor_;
    (atom_ = atom(p)) &&
    (AST_CONSUME(p, 5, "**")) &&
    (factor_ = factor(p))
    ? (res = AST_NODE_2(p, 1, atom_, factor_)) : 0;
    EXIT_FRAME(p);
}

// atom:
//     | '(' sum ')'
//     | NAME '(' [parameters] ')'
//     | NAME
//     | NUMBER
FAstNode *atom(FPegParser *p) {
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
    FAstNode *sum_;
    (AST_CONSUME(p, 19, "(")) &&
    (sum_ = sum(p)) &&
    (AST_CONSUME(p, 20, ")"))
    ? (res = AST_NODE_1(p, 2, sum_)) : 0;
    EXIT_FRAME(p);
}

// NAME '(' [parameters] ')'
FAstNode *atom_2(FPegParser *p) {
    ENTER_FRAME(p, 10, "atom_2");
    FAstNode *name_, *parameters_;
    (name_ = AST_CONSUME(p, 17, "NAME")) &&
    (AST_CONSUME(p, 3, "(")) &&
    (parameters_ = OPTIONAL(parameters(p))) &&
    (AST_CONSUME(p, 8, ")"))
    ? (res = AST_NODE_2(p, 10, name_, parameters_)) : 0;
    EXIT_FRAME(p);
}

// parameters:
//     | ','.sum+ [',']
FAstNode *parameters(FPegParser *p) {
    ENTER_FRAME(p, 10, "paramters");
    FAstNode *sum_list_, *comma;
    (sum_list_ = sum_list(p)) &&
    (comma = OPTIONAL_TOKEN(p, 21, ","))
    ? (res = AST_NODE_2(p, 11, sum_list_, comma)) : 0;
    EXIT_FRAME(p);
}

// ','.sum+
FAstNode *sum_list(FPegParser *p) {
    FAstNode *node, *seq;
    if (!(node = sum(p))) { return ((void *) 0); }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 20, ",")) &&
            (node = sum(p)));
    p->pos = pos;
    return seq;
}