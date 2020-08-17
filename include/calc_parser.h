#ifndef CPEG_CALC_PARSER_H
#define CPEG_CALC_PARSER_H

#include "peg.h"


typedef union calc_ast_node {

    struct {
        FAstNode *sum;
        FAstNode *term;
    } sum_plus_term;

    struct {
        FAstNode *sum;
        FAstNode *term;
    } sum_minus_term;

    struct {
        FAstNode *term;
        FAstNode *factor;
    } term_multiply_factor;

    struct {
        FAstNode *term;
        FAstNode *factor;
    } term_divide_factor;

    struct {
        FAstNode *term;
        FAstNode *factor;
    } term_modulus_factor;

    struct {
        FAstNode *factor;
    } plus_factor;

    struct {
        FAstNode *factor;
    } minus_factor;

    struct {
        FAstNode *factor;
    } invert_factor;

    struct {
        FAstNode *atom;
        FAstNode *factor;
    } atom_power_factor;

    struct {
        FAstNode *sum;
    } lpar_sum_rpar;

    struct {
        FAstNode *name;
        FAstNode *parameters;
    } name_lpar_parameters_rpar;

    struct {
        FAstNode *sum_list;
        FAstNode *comma;
    } sum_list_comma;
} calc_ast_node;

typedef enum {
    calc_entry_sum
} calc_entry_point;

FAstNode *calc_parse(FPegParser *p, calc_entry_point entry_point);

#endif //CPEG_CALC_PARSER_H
