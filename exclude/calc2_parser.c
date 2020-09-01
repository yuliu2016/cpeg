#include "calc2_parser.h"
#include "peg_macros.h"

// sum:
//     | sum '+' term
//     | sum '-' term
//     | term
RULE(sum) {
    ENTER_FRAME(p, 1);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = sum_1(p)) ||
    (a = sum_2(p)) ||
    (a = term(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(sum_1) {
    ENTER_FRAME(p, 2);
    (a = sum(p)) &&
    (TOKEN(p, 21, "+")) &&
    (b = term(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(sum_2) {
    ENTER_FRAME(p, 3);
    (a = sum(p)) &&
    (TOKEN(p, 22, "-")) &&
    (b = term(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// term:
//     | term '*' factor
//     | term '/' factor
//     | term '%' factor
//     | factor
RULE(term) {
    ENTER_FRAME(p, 4);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = term_1(p)) ||
    (a = term_2(p)) ||
    (a = term_3(p)) ||
    (a = factor(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(term_1) {
    ENTER_FRAME(p, 5);
    (a = term(p)) &&
    (TOKEN(p, 23, "*")) &&
    (b = factor(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(term_2) {
    ENTER_FRAME(p, 6);
    (a = term(p)) &&
    (TOKEN(p, 24, "/")) &&
    (b = factor(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(term_3) {
    ENTER_FRAME(p, 7);
    (a = term(p)) &&
    (TOKEN(p, 25, "%")) &&
    (b = factor(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
RULE(factor) {
    ENTER_FRAME(p, 8);
    (a = factor_1(p)) ||
    (a = factor_2(p)) ||
    (a = factor_3(p)) ||
    (a = power(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(factor_1) {
    ENTER_FRAME(p, 9);
    (TOKEN(p, 21, "+")) &&
    (a = factor(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(factor_2) {
    ENTER_FRAME(p, 10);
    (TOKEN(p, 22, "-")) &&
    (a = factor(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(factor_3) {
    ENTER_FRAME(p, 11);
    (TOKEN(p, 29, "~")) &&
    (a = factor(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// power:
//     | atom '**' factor
//     | atom
RULE(power) {
    ENTER_FRAME(p, 12);
    (a = power_1(p)) ||
    (a = atom(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(power_1) {
    ENTER_FRAME(p, 13);
    (a = atom(p)) &&
    (TOKEN(p, 38, "**")) &&
    (b = factor(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// atom:
//     | '(' sum ')'
//     | NAME '(' [parameters] ')'
//     | NAME
//     | NUMBER
RULE(atom) {
    ENTER_FRAME(p, 14);
    (a = atom_1(p)) ||
    (a = atom_2(p)) ||
    (a = TOKEN(p, 3, "NAME")) ||
    (a = TOKEN(p, 4, "NUMBER"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(atom_1) {
    ENTER_FRAME(p, 15);
    (TOKEN(p, 13, "(")) &&
    (a = sum(p)) &&
    (TOKEN(p, 14, ")"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(atom_2) {
    ENTER_FRAME(p, 16);
    (a = TOKEN(p, 3, "NAME")) &&
    (TOKEN(p, 13, "(")) &&
    (b = OPTIONAL(parameters(p))) &&
    (TOKEN(p, 14, ")"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// parameters:
//     | ','.sum+ [',']
RULE(parameters) {
    ENTER_FRAME(p, 17);
    (a = DELIMITED(p, 7, ",", sum)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}
