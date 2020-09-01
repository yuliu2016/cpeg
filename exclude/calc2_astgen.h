#ifndef CPEG_CALC2_ASTGEN_H
#define CPEG_CALC2_ASTGEN_H

#include "peg.h"

typedef union ast_gen_t FAstGen;

#define ASC(node) ((FAstGen *) &(node)->ast_v)

union ast_gen_t {

#define R_SUM 1

#define R_SUM_1 2
    struct {
        FAstNode *sum;
        FAstNode *term;
    } sum_1;

#define R_SUM_2 3
    struct {
        FAstNode *sum;
        FAstNode *term;
    } sum_2;

#define R_TERM 4

#define R_TERM_1 5
    struct {
        FAstNode *term;
        FAstNode *factor;
    } term_1;

#define R_TERM_2 6
    struct {
        FAstNode *term;
        FAstNode *factor;
    } term_2;

#define R_TERM_3 7
    struct {
        FAstNode *term;
        FAstNode *factor;
    } term_3;

#define R_FACTOR 8

#define R_FACTOR_1 9
    struct {
        FAstNode *factor;
    } factor_1;

#define R_FACTOR_2 10
    struct {
        FAstNode *factor;
    } factor_2;

#define R_FACTOR_3 11
    struct {
        FAstNode *factor;
    } factor_3;

#define R_POWER 12

#define R_POWER_1 13
    struct {
        FAstNode *atom;
        FAstNode *factor;
    } power_1;

#define R_ATOM 14

#define R_ATOM_1 15
    struct {
        FAstNode *sum;
    } atom_1;

#define R_ATOM_2 16
    struct {
        FAstNode *name;
        FAstNode *parameters;
    } atom_2;

#define R_PARAMETERS 17
    struct {
        FAstNode *sums;
        FAstNode *is_op_comma;
    } parameters;
} ;

#endif // CPEG_CALC2_ASTGEN_H
