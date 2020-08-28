#ifndef CPEG_ASTGEN_H
#define CPEG_ASTGEN_H

#include "peg.h"

typedef union ast_gen_t FAstGen;

#define ASC(node) ((FAstGen *) &(node)->ast_v)

union ast_gen_t {

#define R_SINGLE_INPUT 1

#define R_SINGLE_INPUT_3 2
    struct {
        FAstNode *compound_stmt;
        FAstNode *newline;
    } single_input_3;

#define R_FILE_INPUT 3
    struct {
        FAstNode *newline_or_stmts;
        FAstNode *endmarker;
    } file_input;

#define R_FILE_INPUT_1 4

#define R_EVAL_INPUT 5
    struct {
        FAstNode *exprlist;
        FAstNode *newlines;
        FAstNode *endmarker;
    } eval_input;

#define R_STMT 6
    struct {
        FAstNode *simple_stmt_or_compound_stmt;
        FAstNode *newline;
    } stmt;

#define R_STMT_1 7

#define R_SIMPLE_STMT 8
    struct {
        FAstNode *small_stmts;
        FAstNode *is_semicolon;
    } simple_stmt;

#define R_SMALL_STMT 9

#define R_DEL_STMT 10
    struct {
        FAstNode *targetlist;
    } del_stmt;

#define R_RETURN_STMT 11
    struct {
        FAstNode *exprlist_star;
    } return_stmt;

#define R_RAISE_STMT 12
    struct {
        FAstNode *expr;
        FAstNode *from_expr;
    } raise_stmt;

#define R_RAISE_STMT_3 13
    struct {
        FAstNode *expr;
    } raise_stmt_3;

#define R_NONLOCAL_STMT 14
    struct {
        FAstNode *name_list;
    } nonlocal_stmt;

#define R_ASSERT_STMT 15
    struct {
        FAstNode *expr;
        FAstNode *comma_expr;
    } assert_stmt;

#define R_ASSERT_STMT_3 16
    struct {
        FAstNode *expr;
    } assert_stmt_3;

#define R_NAME_LIST 17
    struct {
        FAstNode *names;
    } name_list;

#define R_STAR_EXPR 18
    struct {
        FAstNode *bitwise_or;
    } star_expr;

#define R_EXPRLIST 19
    struct {
        FAstNode *exprs;
        FAstNode *is_comma;
    } exprlist;

#define R_TARGET 20

#define R_TARGET_1 21
    struct {
        FAstNode *t_primary;
        FAstNode *name;
    } target_1;

#define R_TARGET_2 22
    struct {
        FAstNode *t_primary;
        FAstNode *subscript;
    } target_2;

#define R_TARGET_4 23
    struct {
        FAstNode *targetlist;
    } target_4;

#define R_T_PRIMARY 24

#define R_T_PRIMARY_1 25
    struct {
        FAstNode *t_primary;
        FAstNode *name;
    } t_primary_1;

#define R_T_PRIMARY_2 26
    struct {
        FAstNode *t_primary;
        FAstNode *invocation;
    } t_primary_2;

#define R_T_PRIMARY_3 27
    struct {
        FAstNode *t_primary;
        FAstNode *subscript;
    } t_primary_3;

#define R_T_PRIMARY_4 28
    struct {
        FAstNode *atom;
    } t_primary_4;

#define R_T_LOOKAHEAD 29

#define R_TARGETLIST 30
    struct {
        FAstNode *targets;
        FAstNode *is_comma;
    } targetlist;

#define R_EXPR_OR_STAR 31

#define R_EXPRLIST_STAR 32
    struct {
        FAstNode *expr_or_stars;
        FAstNode *is_comma;
    } exprlist_star;

#define R_NAMED_EXPR_STAR 33

#define R_NAMED_EXPR_LIST 34
    struct {
        FAstNode *named_expr_stars;
        FAstNode *is_comma;
    } named_expr_list;

#define R_SUBSCRIPT 35
    struct {
        FAstNode *slicelist;
    } subscript;

#define R_SLICELIST 36
    struct {
        FAstNode *slices;
        FAstNode *is_comma;
    } slicelist;

#define R_SLICE 37

#define R_SLICE_1 38
    struct {
        FAstNode *expr;
        FAstNode *slice_expr;
        FAstNode *slice_expr_1;
    } slice_1;

#define R_SLICE_EXPR 39
    struct {
        FAstNode *expr;
    } slice_expr;

#define R_DICT_ITEM 40

#define R_DICT_ITEM_1 41
    struct {
        FAstNode *expr;
        FAstNode *expr_1;
    } dict_item_1;

#define R_DICT_ITEM_2 42
    struct {
        FAstNode *bitwise_or;
    } dict_item_2;

#define R_DICT_ITEMS 43
    struct {
        FAstNode *dict_items;
        FAstNode *is_comma;
    } dict_items;

#define R_AS_NAME 44
    struct {
        FAstNode *name;
    } as_name;

#define R_ITER_FOR 45
    struct {
        FAstNode *targetlist;
        FAstNode *disjunction;
        FAstNode *iter_if;
    } iter_for;

#define R_ITER_IF 46
    struct {
        FAstNode *named_expr;
    } iter_if;

#define R_ITERATOR 47
    struct {
        FAstNode *iter_fors;
        FAstNode *targetlist;
        FAstNode *iter_if;
    } iterator;

#define R_ASSIGNMENT 48

#define R_PUBASSIGN 49
    struct {
        FAstNode *name;
        FAstNode *exprlist;
    } pubassign;

#define R_ANNASSIGN 50
    struct {
        FAstNode *target;
        FAstNode *expr;
        FAstNode *assign_exprlist;
    } annassign;

#define R_ANNASSIGN_4 51
    struct {
        FAstNode *exprlist;
    } annassign_4;

#define R_AUGASSIGN 52
    struct {
        FAstNode *target;
        FAstNode *augassign_op;
        FAstNode *exprlist;
    } augassign;

#define R_SIMPLE_ASSIGN 53
    struct {
        FAstNode *targetlist_assigns;
        FAstNode *exprlist_star;
    } simple_assign;

#define R_SIMPLE_ASSIGN_1 54
    struct {
        FAstNode *targetlist;
    } simple_assign_1;

#define R_AUGASSIGN_OP 55

#define R_IMPORT_NAME 56
    struct {
        FAstNode *dotted_as_names;
    } import_name;

#define R_IMPORT_FROM 57
    struct {
        FAstNode *import_from_names;
        FAstNode *import_from_items;
    } import_from;

#define R_IMPORT_FROM_NAMES 58

#define R_IMPORT_FROM_NAMES_2 59
    struct {
        FAstNode *dotted_name;
    } import_from_names_2;

#define R_IMPORT_FROM_ITEMS 60

#define R_IMPORT_FROM_ITEMS_2 61
    struct {
        FAstNode *import_as_names;
        FAstNode *is_comma;
    } import_from_items_2;

#define R_IMPORT_AS_NAME 62
    struct {
        FAstNode *name;
        FAstNode *as_name;
    } import_as_name;

#define R_DOTTED_AS_NAME 63
    struct {
        FAstNode *dotted_name;
        FAstNode *as_name;
    } dotted_as_name;

#define R_IMPORT_AS_NAMES 64
    struct {
        FAstNode *import_as_names;
    } import_as_names;

#define R_DOTTED_AS_NAMES 65
    struct {
        FAstNode *dotted_as_names;
    } dotted_as_names;

#define R_DOTTED_NAME 66
    struct {
        FAstNode *names;
    } dotted_name;

#define R_COMPOUND_STMT 67

#define R_IF_STMT 68
    struct {
        FAstNode *named_expr;
        FAstNode *suite;
        FAstNode *elif_stmts;
        FAstNode *else_suite;
    } if_stmt;

#define R_ELIF_STMT 69
    struct {
        FAstNode *named_expr;
        FAstNode *suite;
    } elif_stmt;

#define R_WHILE_STMT 70
    struct {
        FAstNode *named_expr;
        FAstNode *suite;
        FAstNode *else_suite;
    } while_stmt;

#define R_FOR_STMT 71
    struct {
        FAstNode *targetlist;
        FAstNode *exprlist;
        FAstNode *suite;
        FAstNode *else_suite;
    } for_stmt;

#define R_TRY_STMT 72
    struct {
        FAstNode *suite;
        FAstNode *except_suite_or_finally_suite;
    } try_stmt;

#define R_TRY_STMT_3 73

#define R_WITH_STMT 74
    struct {
        FAstNode *expr_as_names;
        FAstNode *suite;
    } with_stmt;

#define R_EXPR_AS_NAME 75
    struct {
        FAstNode *expr;
        FAstNode *as_name;
    } expr_as_name;

#define R_BLOCK_SUITE 76

#define R_BLOCK_SUITE_1 77
    struct {
        FAstNode *newline;
        FAstNode *stmts;
    } block_suite_1;

#define R_BLOCK_SUITE_2 78

#define R_SUITE 79

#define R_SUITE_1 80
    struct {
        FAstNode *simple_stmt;
    } suite_1;

#define R_ELSE_SUITE 81
    struct {
        FAstNode *suite;
    } else_suite;

#define R_FINALLY_SUITE 82
    struct {
        FAstNode *suite;
    } finally_suite;

#define R_EXCEPT_CLAUSE 83
    struct {
        FAstNode *expr_as_name;
        FAstNode *suite;
    } except_clause;

#define R_EXCEPT_SUITE 84
    struct {
        FAstNode *except_clauses;
        FAstNode *else_suite;
        FAstNode *finally_suite;
    } except_suite;

#define R_INVOCATION 85
    struct {
        FAstNode *call_arg_list;
    } invocation;

#define R_CALL_ARG_LIST 86
    struct {
        FAstNode *call_args;
        FAstNode *is_comma;
    } call_arg_list;

#define R_CALL_ARG 87

#define R_CALL_ARG_1 88
    struct {
        FAstNode *name;
        FAstNode *expr;
    } call_arg_1;

#define R_CALL_ARG_2 89
    struct {
        FAstNode *name;
        FAstNode *expr;
    } call_arg_2;

#define R_CALL_ARG_3 90
    struct {
        FAstNode *expr;
    } call_arg_3;

#define R_CALL_ARG_4 91
    struct {
        FAstNode *expr;
    } call_arg_4;

#define R_TYPED_ARG_LIST 92

#define R_FULL_ARG_LIST 93
    struct {
        FAstNode *default_args;
        FAstNode *full_arg_list;
    } full_arg_list;

#define R_FULL_ARG_LIST_2 94
    struct {
        FAstNode *kwargs_or_args_kwargs;
    } full_arg_list_2;

#define R_FULL_ARG_LIST_2_2 95

#define R_ARGS_KWARGS 96
    struct {
        FAstNode *typed_arg;
        FAstNode *comma_default_args;
        FAstNode *args_kwargs;
    } args_kwargs;

#define R_ARGS_KWARGS_3 97
    struct {
        FAstNode *default_arg;
    } args_kwargs_3;

#define R_ARGS_KWARGS_4 98
    struct {
        FAstNode *kwargs;
    } args_kwargs_4;

#define R_KWARGS 99
    struct {
        FAstNode *typed_arg;
        FAstNode *is_comma;
    } kwargs;

#define R_DEFAULT_ARG 100
    struct {
        FAstNode *typed_arg;
        FAstNode *assign_expr;
    } default_arg;

#define R_DEFAULT_ARG_2 101
    struct {
        FAstNode *expr;
    } default_arg_2;

#define R_TYPED_ARG 102
    struct {
        FAstNode *name;
        FAstNode *colon_expr;
    } typed_arg;

#define R_TYPED_ARG_2 103
    struct {
        FAstNode *expr;
    } typed_arg_2;

#define R_SIMPLE_ARG 104
    struct {
        FAstNode *name;
        FAstNode *assign_expr;
    } simple_arg;

#define R_SIMPLE_ARG_2 105
    struct {
        FAstNode *expr;
    } simple_arg_2;

#define R_SIMPLE_ARGS 106
    struct {
        FAstNode *simple_args;
    } simple_args;

#define R_BUILDER_HINT 107
    struct {
        FAstNode *name_list;
    } builder_hint;

#define R_BUILDER_ARGS 108

#define R_BUILDER_ARGS_2 109
    struct {
        FAstNode *typed_arg_list;
    } builder_args_2;

#define R_NAMED_EXPR 110

#define R_NAMED_EXPR_1 111
    struct {
        FAstNode *name;
        FAstNode *expr;
    } named_expr_1;

#define R_CONDITIONAL 112
    struct {
        FAstNode *disjunction;
        FAstNode *disjunction_1;
        FAstNode *expr;
    } conditional;

#define R_EXPR 113

#define R_DISJUNCTION 114

#define R_DISJUNCTION_1 115
    struct {
        FAstNode *disjunction;
        FAstNode *conjunction;
    } disjunction_1;

#define R_CONJUNCTION 116

#define R_CONJUNCTION_1 117
    struct {
        FAstNode *conjunction;
        FAstNode *inversion;
    } conjunction_1;

#define R_INVERSION 118

#define R_INVERSION_1 119
    struct {
        FAstNode *inversion;
    } inversion_1;

#define R_COMPARISON 120

#define R_COMPARISON_1 121
    struct {
        FAstNode *bitwise_or;
        FAstNode *comp_op_bitwise_ors;
    } comparison_1;

#define R_COMPARISON_1_2 122
    struct {
        FAstNode *comp_op;
        FAstNode *bitwise_or;
    } comparison_1_2;

#define R_COMP_OP 123

#define R_COMP_OP_8 124

#define R_COMP_OP_10 125

#define R_BITWISE_OR 126

#define R_BITWISE_OR_1 127
    struct {
        FAstNode *bitwise_or;
        FAstNode *bitwise_xor;
    } bitwise_or_1;

#define R_BITWISE_XOR 128

#define R_BITWISE_XOR_1 129
    struct {
        FAstNode *bitwise_xor;
        FAstNode *bitwise_and;
    } bitwise_xor_1;

#define R_BITWISE_AND 130

#define R_BITWISE_AND_1 131
    struct {
        FAstNode *bitwise_and;
        FAstNode *shift_expr;
    } bitwise_and_1;

#define R_SHIFT_EXPR 132

#define R_SHIFT_EXPR_1 133
    struct {
        FAstNode *shift_expr;
        FAstNode *sum;
    } shift_expr_1;

#define R_SHIFT_EXPR_2 134
    struct {
        FAstNode *shift_expr;
        FAstNode *sum;
    } shift_expr_2;

#define R_SUM 135

#define R_SUM_1 136
    struct {
        FAstNode *sum;
        FAstNode *term;
    } sum_1;

#define R_SUM_2 137
    struct {
        FAstNode *sum;
        FAstNode *term;
    } sum_2;

#define R_TERM 138

#define R_TERM_1 139
    struct {
        FAstNode *term;
        FAstNode *pipe_expr;
    } term_1;

#define R_TERM_2 140
    struct {
        FAstNode *term;
        FAstNode *pipe_expr;
    } term_2;

#define R_TERM_3 141
    struct {
        FAstNode *term;
        FAstNode *pipe_expr;
    } term_3;

#define R_TERM_4 142
    struct {
        FAstNode *term;
        FAstNode *pipe_expr;
    } term_4;

#define R_TERM_5 143
    struct {
        FAstNode *term;
        FAstNode *pipe_expr;
    } term_5;

#define R_PIPE_EXPR 144

#define R_PIPE_EXPR_1 145
    struct {
        FAstNode *pipe_expr;
        FAstNode *factor;
    } pipe_expr_1;

#define R_FACTOR 146

#define R_FACTOR_1 147
    struct {
        FAstNode *factor;
    } factor_1;

#define R_FACTOR_2 148
    struct {
        FAstNode *factor;
    } factor_2;

#define R_FACTOR_3 149
    struct {
        FAstNode *factor;
    } factor_3;

#define R_POWER 150

#define R_POWER_1 151
    struct {
        FAstNode *primary;
        FAstNode *factor;
    } power_1;

#define R_PRIMARY 152

#define R_PRIMARY_1 153
    struct {
        FAstNode *primary;
        FAstNode *name;
    } primary_1;

#define R_PRIMARY_2 154
    struct {
        FAstNode *primary;
        FAstNode *invocation;
    } primary_2;

#define R_PRIMARY_3 155
    struct {
        FAstNode *primary;
        FAstNode *subscript;
    } primary_3;

#define R_TUPLE_ATOM 156
    struct {
        FAstNode *named_expr_list;
    } tuple_atom;

#define R_LIST_ITER 157
    struct {
        FAstNode *expr_or_star;
        FAstNode *iterator;
    } list_iter;

#define R_LIST_ATOM 158
    struct {
        FAstNode *named_expr_list;
    } list_atom;

#define R_SET_ATOM 159
    struct {
        FAstNode *exprlist_star;
    } set_atom;

#define R_DICT_ITER 160
    struct {
        FAstNode *dict_item;
        FAstNode *iterator;
    } dict_iter;

#define R_DICT_ATOM 161
    struct {
        FAstNode *dict_items;
    } dict_atom;

#define R_BUILDER 162

#define R_BUILDER_1 163
    struct {
        FAstNode *name;
        FAstNode *simple_args;
        FAstNode *expr;
    } builder_1;

#define R_BUILDER_2 164
    struct {
        FAstNode *name;
        FAstNode *builder_hint;
        FAstNode *builder_args;
        FAstNode *block_suite;
    } builder_2;

#define R_ATOM 165
} ;

#endif //CPEG_ASTGEN_H
