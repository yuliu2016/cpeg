#ifndef CPEG_CALC2_PARSER_H
#define CPEG_CALC2_PARSER_H

#include "peg.h"

static void *sum(FParser *);
static void *sum_1(FParser *);
static void *sum_2(FParser *);
static void *term(FParser *);
static void *term_1(FParser *);
static void *term_2(FParser *);
static void *term_3(FParser *);
static void *factor(FParser *);
static void *factor_1(FParser *);
static void *factor_2(FParser *);
static void *factor_3(FParser *);
static void *power(FParser *);
static void *power_1(FParser *);
static void *atom(FParser *);
static void *atom_1(FParser *);
static void *atom_2(FParser *);
static void *parameters(FParser *);

#endif // CPEG_CALC2_PARSER_H
