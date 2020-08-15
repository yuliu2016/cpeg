#ifndef CPEG_CALC_PARSER_H
#define CPEG_CALC_PARSER_H

#include "peg.h"

typedef struct calc_node_ calc_node;

typedef union calc_node_v {

    struct {
        FToken *tk_val;
    } token;

    struct {
        int len;
        calc_node **items;
    } sequence;

    struct {
        calc_node *sum;
        calc_node *term;
    } sum_plus_term;

    struct {
        calc_node *sum;
        calc_node *term;
    } sum_minus_term;

    struct {
        calc_node *term;
        calc_node *factor;
    } term_multiply_factor;

    struct {
        calc_node *term;
        calc_node *factor;
    } term_divide_factor;

    struct {
        calc_node *term;
        calc_node *factor;
    } term_modulus_factor;

    struct {
        calc_node *factor;
    } plus_factor;

    struct {
        calc_node *factor;
    } minus_factor;

    struct {
        calc_node *factor;
    } invert_factor;

    struct {
        calc_node *atom;
        calc_node *factor;
    } atom_power_factor;

    struct {
        calc_node *sum;
    } lpar_sum_rpar;

    struct {
        calc_node *name;
        calc_node *parameters;
    } name_lpar_parameters_rpar;

    struct {
        calc_node *sum_list;
        calc_node *comma;
    } sum_list_comma;
} calc_node_v;

struct calc_node_ {
    int t;
    calc_node_v v;
};

typedef enum {
    calc_entry_sum
} calc_entry_point;

calc_node *calc_parse(FPegParser *p, calc_entry_point entry_point);

FToken *calc_get_token(calc_node *node);


typedef struct calc_node_xx2 calc_node_xx2;

struct calc_node_xx2 {
    size_t t;
    union {
        struct {
            size_t len;
            calc_node_xx2 **items;
        } sequence;

        FToken *token;
        calc_node_xx2 *fields[4];
    }v;
} calc_node_x2;

#endif //CPEG_CALC_PARSER_H
