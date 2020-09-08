#include "calc2_parser.h"
#include "peg_macros.h"

// sum:
//     | sum '+' term
//     | sum '-' term
//     | term
RULE(sum) {
    ENTER(1);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = sum_1(p)) ||
    (a = sum_2(p)) ||
    (a = term(p));
    EXIT_LEFT_RECURSION(p);
    EXIT();
}

RULE(sum_1) {
    ENTER(2);
    (a = sum(p)) &&
    (TOKEN(21, "+")) &&
    (b = term(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(sum_2) {
    ENTER(3);
    (a = sum(p)) &&
    (TOKEN(22, "-")) &&
    (b = term(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// term:
//     | term '*' factor
//     | term '/' factor
//     | term '%' factor
//     | factor
RULE(term) {
    ENTER(4);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = term_1(p)) ||
    (a = term_2(p)) ||
    (a = term_3(p)) ||
    (a = factor(p));
    EXIT_LEFT_RECURSION(p);
    EXIT();
}

RULE(term_1) {
    ENTER(5);
    (a = term(p)) &&
    (TOKEN(23, "*")) &&
    (b = factor(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(term_2) {
    ENTER(6);
    (a = term(p)) &&
    (TOKEN(24, "/")) &&
    (b = factor(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(term_3) {
    ENTER(7);
    (a = term(p)) &&
    (TOKEN(25, "%")) &&
    (b = factor(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
RULE(factor) {
    ENTER(8);
    (a = factor_1(p)) ||
    (a = factor_2(p)) ||
    (a = factor_3(p)) ||
    (a = power(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(factor_1) {
    ENTER(9);
    (TOKEN(21, "+")) &&
    (a = factor(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

RULE(factor_2) {
    ENTER(10);
    (TOKEN(22, "-")) &&
    (a = factor(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

RULE(factor_3) {
    ENTER(11);
    (TOKEN(29, "~")) &&
    (a = factor(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// power:
//     | atom '**' factor
//     | atom
RULE(power) {
    ENTER(12);
    (a = power_1(p)) ||
    (a = atom(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(power_1) {
    ENTER(13);
    (a = atom(p)) &&
    (TOKEN(38, "**")) &&
    (b = factor(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// atom:
//     | '(' sum ')'
//     | NAME '(' [parameters] ')'
//     | NAME
//     | NUMBER
RULE(atom) {
    ENTER(14);
    (a = atom_1(p)) ||
    (a = atom_2(p)) ||
    (a = TOKEN(3, "NAME")) ||
    (a = TOKEN(4, "NUMBER"))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(atom_1) {
    ENTER(15);
    (TOKEN(13, "(")) &&
    (a = sum(p)) &&
    (TOKEN(14, ")"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

RULE(atom_2) {
    ENTER(16);
    (a = TOKEN(3, "NAME")) &&
    (TOKEN(13, "(")) &&
    (b = OPTIONAL(parameters(p))) &&
    (TOKEN(14, ")"))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// parameters:
//     | ','.sum+ [',']
RULE(parameters) {
    ENTER(17);
    (a = DELIMITED(p, 7, ",", sum)) &&
    (b = OPTIONAL(TOKEN(7, ",")))
    ? (r = NODE_2()) : 0; 
    EXIT();
}
