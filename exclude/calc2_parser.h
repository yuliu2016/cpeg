#ifndef CPEG_CALC2_PARSER_H
#define CPEG_CALC2_PARSER_H

#include "peg.h"

static FAstNode *sum(FParser *);
static FAstNode *sum_1(FParser *);
static FAstNode *sum_2(FParser *);
static FAstNode *term(FParser *);
static FAstNode *term_1(FParser *);
static FAstNode *term_2(FParser *);
static FAstNode *term_3(FParser *);
static FAstNode *factor(FParser *);
static FAstNode *factor_1(FParser *);
static FAstNode *factor_2(FParser *);
static FAstNode *factor_3(FParser *);
static FAstNode *power(FParser *);
static FAstNode *power_1(FParser *);
static FAstNode *atom(FParser *);
static FAstNode *atom_1(FParser *);
static FAstNode *atom_2(FParser *);
static FAstNode *parameters(FParser *);

#endif // CPEG_CALC2_PARSER_H
