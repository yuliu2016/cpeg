#ifndef CPEG_ASTGEN_H
#define CPEG_ASTGEN_H

#include "peg.h"

#define FVAR(name, node, i) FAstNode *name = (node)->ast_v.fields[i]
#define TVAR(name, node, i) FToken *name = (node)->ast_v.fields[i]->ast_v.token

#define R_SINGLE_INPUT 1

#define R_SINGLE_INPUT_4 2
#define UNPACK_SINGLE_INPUT_4(n) \
    FVAR(compound_stmt, n, 0); \
    TVAR(newline, n, 1); \

#define R_FILE_INPUT 3
#define UNPACK_FILE_INPUT(n) \
    FVAR(stmt_list, n, 0); \
    TVAR(endmarker, n, 1); \

#define R_EVAL_INPUT 4
#define UNPACK_EVAL_INPUT(n) \
    FVAR(exprlist, n, 0); \
    TVAR(newlines, n, 1); \
    TVAR(endmarker, n, 2); \

#define R_STMT_LIST 5
#define UNPACK_STMT_LIST(n) \
    FVAR(stmts, n, 0); \

#define R_STMT 6
#define UNPACK_STMT(n) \
    FVAR(simple_stmt_or_compound_stmt, n, 0); \
    TVAR(newline, n, 1); \

#define R_STMT_1 7

#define R_SIMPLE_STMT 8
#define UNPACK_SIMPLE_STMT(n) \
    FVAR(small_stmts, n, 0); \
    TVAR(is_op_semicolon, n, 1); \

#define R_SMALL_STMT 9

#define R_DEL_STMT 10
#define UNPACK_DEL_STMT(n) \
    FVAR(targetlist, n, 0); \

#define R_RETURN_STMT 11
#define UNPACK_RETURN_STMT(n) \
    FVAR(exprlist_star, n, 0); \

#define R_RAISE_STMT 12
#define UNPACK_RAISE_STMT(n) \
    FVAR(expr, n, 0); \
    FVAR(from_expr, n, 1); \

#define R_RAISE_STMT_3 13
#define UNPACK_RAISE_STMT_3(n) \
    FVAR(expr, n, 0); \

#define R_NONLOCAL_STMT 14
#define UNPACK_NONLOCAL_STMT(n) \
    FVAR(name_list, n, 0); \

#define R_ASSERT_STMT 15
#define UNPACK_ASSERT_STMT(n) \
    FVAR(expr, n, 0); \
    FVAR(op_comma_expr, n, 1); \

#define R_ASSERT_STMT_3 16
#define UNPACK_ASSERT_STMT_3(n) \
    FVAR(expr, n, 0); \

#define R_NAME_LIST 17
#define UNPACK_NAME_LIST(n) \
    TVAR(names, n, 0); \

#define R_STAR_EXPR 18
#define UNPACK_STAR_EXPR(n) \
    FVAR(bitwise_or, n, 0); \

#define R_EXPRLIST 19
#define UNPACK_EXPRLIST(n) \
    FVAR(exprs, n, 0); \
    TVAR(is_op_comma, n, 1); \

#define R_TARGET 20

#define R_TARGET_1 21
#define UNPACK_TARGET_1(n) \
    FVAR(t_primary, n, 0); \
    TVAR(name, n, 1); \

#define R_TARGET_2 22
#define UNPACK_TARGET_2(n) \
    FVAR(t_primary, n, 0); \
    FVAR(subscript, n, 1); \

#define R_TARGET_4 23
#define UNPACK_TARGET_4(n) \
    FVAR(targetlist_sp, n, 0); \

#define R_TARGETLIST_SP 24
#define UNPACK_TARGETLIST_SP(n) \
    FVAR(targetlist, n, 0); \

#define R_T_PRIMARY 25

#define R_T_PRIMARY_1 26
#define UNPACK_T_PRIMARY_1(n) \
    FVAR(t_primary, n, 0); \
    TVAR(name, n, 1); \

#define R_T_PRIMARY_2 27
#define UNPACK_T_PRIMARY_2(n) \
    FVAR(t_primary, n, 0); \
    FVAR(invocation, n, 1); \

#define R_T_PRIMARY_3 28
#define UNPACK_T_PRIMARY_3(n) \
    FVAR(t_primary, n, 0); \
    FVAR(subscript, n, 1); \

#define R_T_PRIMARY_4 29
#define UNPACK_T_PRIMARY_4(n) \
    FVAR(atom, n, 0); \

#define R_T_LOOKAHEAD 30

#define R_TARGETLIST 31
#define UNPACK_TARGETLIST(n) \
    FVAR(targets, n, 0); \
    TVAR(is_op_comma, n, 1); \

#define R_EXPR_OR_STAR 32

#define R_EXPRLIST_STAR 33
#define UNPACK_EXPRLIST_STAR(n) \
    FVAR(expr_or_stars, n, 0); \
    TVAR(is_op_comma, n, 1); \

#define R_SUBSCRIPT 34
#define UNPACK_SUBSCRIPT(n) \
    FVAR(slicelist, n, 0); \

#define R_SLICELIST 35
#define UNPACK_SLICELIST(n) \
    FVAR(slices, n, 0); \
    TVAR(is_op_comma, n, 1); \

#define R_SLICE 36

#define R_SLICE_1 37
#define UNPACK_SLICE_1(n) \
    FVAR(expr, n, 0); \
    FVAR(slice_expr, n, 1); \
    FVAR(slice_expr_1, n, 2); \

#define R_SLICE_EXPR 38
#define UNPACK_SLICE_EXPR(n) \
    FVAR(expr, n, 0); \

#define R_DICT_ITEM 39

#define R_DICT_ITEM_1 40
#define UNPACK_DICT_ITEM_1(n) \
    FVAR(expr, n, 0); \
    FVAR(expr_1, n, 1); \

#define R_DICT_ITEM_2 41
#define UNPACK_DICT_ITEM_2(n) \
    FVAR(bitwise_or, n, 0); \

#define R_DICT_ITEMS 42
#define UNPACK_DICT_ITEMS(n) \
    FVAR(dict_items, n, 0); \
    TVAR(is_op_comma, n, 1); \

#define R_LIST_ITEM 43

#define R_LIST_ITEMS 44
#define UNPACK_LIST_ITEMS(n) \
    FVAR(list_items, n, 0); \
    TVAR(is_op_comma, n, 1); \

#define R_SET_ITEMS 45
#define UNPACK_SET_ITEMS(n) \
    FVAR(exprlist_star, n, 0); \

#define R_AS_NAME 46
#define UNPACK_AS_NAME(n) \
    TVAR(name, n, 0); \

#define R_ITER_FOR 47
#define UNPACK_ITER_FOR(n) \
    FVAR(targetlist, n, 0); \
    FVAR(disjunction, n, 1); \
    FVAR(iter_if, n, 2); \

#define R_ITER_IF 48
#define UNPACK_ITER_IF(n) \
    FVAR(named_expr, n, 0); \

#define R_ITERATOR 49
#define UNPACK_ITERATOR(n) \
    FVAR(iter_fors, n, 0); \
    FVAR(targetlist, n, 1); \
    FVAR(iter_if, n, 2); \

#define R_LIST_ITERATOR 50
#define UNPACK_LIST_ITERATOR(n) \
    FVAR(expr_or_star, n, 0); \
    FVAR(iterator, n, 1); \

#define R_DICT_ITERATOR 51
#define UNPACK_DICT_ITERATOR(n) \
    FVAR(dict_item, n, 0); \
    FVAR(iterator, n, 1); \

#define R_ASSIGNMENT 52

#define R_PUBASSIGN 53
#define UNPACK_PUBASSIGN(n) \
    TVAR(name, n, 0); \
    FVAR(exprlist, n, 1); \

#define R_ANNASSIGN 54
#define UNPACK_ANNASSIGN(n) \
    FVAR(target, n, 0); \
    FVAR(expr, n, 1); \
    FVAR(op_assign_exprlist, n, 2); \

#define R_ANNASSIGN_4 55
#define UNPACK_ANNASSIGN_4(n) \
    FVAR(exprlist, n, 0); \

#define R_AUGASSIGN 56
#define UNPACK_AUGASSIGN(n) \
    FVAR(target, n, 0); \
    FVAR(augassign_op, n, 1); \
    FVAR(exprlist, n, 2); \

#define R_SIMPLE_ASSIGN 57
#define UNPACK_SIMPLE_ASSIGN(n) \
    FVAR(targetlist_op_assigns, n, 0); \
    FVAR(exprlist_star, n, 1); \

#define R_SIMPLE_ASSIGN_1 58
#define UNPACK_SIMPLE_ASSIGN_1(n) \
    FVAR(targetlist, n, 0); \

#define R_AUGASSIGN_OP 59

#define R_IMPORT_NAME 60
#define UNPACK_IMPORT_NAME(n) \
    FVAR(dotted_as_names, n, 0); \

#define R_IMPORT_FROM 61
#define UNPACK_IMPORT_FROM(n) \
    FVAR(import_from_names, n, 0); \
    FVAR(import_from_items, n, 1); \

#define R_IMPORT_FROM_NAMES 62

#define R_IMPORT_FROM_NAMES_2 63
#define UNPACK_IMPORT_FROM_NAMES_2(n) \
    FVAR(dotted_name, n, 0); \

#define R_IMPORT_FROM_ITEMS 64

#define R_IMPORT_AS_NAMES_SP 65
#define UNPACK_IMPORT_AS_NAMES_SP(n) \
    FVAR(import_as_names, n, 0); \
    TVAR(is_op_comma, n, 1); \

#define R_IMPORT_AS_NAME 66
#define UNPACK_IMPORT_AS_NAME(n) \
    TVAR(name, n, 0); \
    FVAR(as_name, n, 1); \

#define R_DOTTED_AS_NAME 67
#define UNPACK_DOTTED_AS_NAME(n) \
    FVAR(dotted_name, n, 0); \
    FVAR(as_name, n, 1); \

#define R_IMPORT_AS_NAMES 68
#define UNPACK_IMPORT_AS_NAMES(n) \
    FVAR(import_as_names, n, 0); \

#define R_DOTTED_AS_NAMES 69
#define UNPACK_DOTTED_AS_NAMES(n) \
    FVAR(dotted_as_names, n, 0); \

#define R_DOTTED_NAME 70
#define UNPACK_DOTTED_NAME(n) \
    TVAR(names, n, 0); \

#define R_COMPOUND_STMT 71

#define R_IF_STMT 72
#define UNPACK_IF_STMT(n) \
    FVAR(named_expr, n, 0); \
    FVAR(suite, n, 1); \
    FVAR(elif_stmts, n, 2); \
    FVAR(else_suite, n, 3); \

#define R_ELIF_STMT 73
#define UNPACK_ELIF_STMT(n) \
    FVAR(named_expr, n, 0); \
    FVAR(suite, n, 1); \

#define R_WHILE_STMT 74
#define UNPACK_WHILE_STMT(n) \
    FVAR(named_expr, n, 0); \
    FVAR(suite, n, 1); \
    FVAR(else_suite, n, 2); \

#define R_FOR_STMT 75
#define UNPACK_FOR_STMT(n) \
    FVAR(targetlist, n, 0); \
    FVAR(exprlist, n, 1); \
    FVAR(suite, n, 2); \
    FVAR(else_suite, n, 3); \

#define R_TRY_STMT 76
#define UNPACK_TRY_STMT(n) \
    FVAR(suite, n, 0); \
    FVAR(except_suite_or_finally_suite, n, 1); \

#define R_TRY_STMT_3 77

#define R_WITH_STMT 78
#define UNPACK_WITH_STMT(n) \
    FVAR(expr_as_names, n, 0); \
    FVAR(suite, n, 1); \

#define R_EXPR_AS_NAME 79
#define UNPACK_EXPR_AS_NAME(n) \
    FVAR(expr, n, 0); \
    FVAR(as_name, n, 1); \

#define R_BLOCK_SUITE 80

#define R_BLOCK_SUITE_1 81
#define UNPACK_BLOCK_SUITE_1(n) \
    TVAR(newline, n, 0); \
    FVAR(stmt_list, n, 1); \

#define R_BLOCK_SUITE_2 82
#define UNPACK_BLOCK_SUITE_2(n) \
    FVAR(simple_stmt, n, 0); \

#define R_SUITE 83

#define R_SUITE_1 84
#define UNPACK_SUITE_1(n) \
    FVAR(simple_stmt, n, 0); \

#define R_ELSE_SUITE 85
#define UNPACK_ELSE_SUITE(n) \
    FVAR(suite, n, 0); \

#define R_FINALLY_SUITE 86
#define UNPACK_FINALLY_SUITE(n) \
    FVAR(suite, n, 0); \

#define R_EXCEPT_CLAUSE 87
#define UNPACK_EXCEPT_CLAUSE(n) \
    FVAR(expr_as_name, n, 0); \
    FVAR(suite, n, 1); \

#define R_EXCEPT_SUITE 88
#define UNPACK_EXCEPT_SUITE(n) \
    FVAR(except_clauses, n, 0); \
    FVAR(else_suite, n, 1); \
    FVAR(finally_suite, n, 2); \

#define R_INVOCATION 89
#define UNPACK_INVOCATION(n) \
    FVAR(call_arg_list, n, 0); \

#define R_CALL_ARG_LIST 90
#define UNPACK_CALL_ARG_LIST(n) \
    FVAR(call_args, n, 0); \
    TVAR(is_op_comma, n, 1); \

#define R_CALL_ARG 91

#define R_CALL_ARG_1 92
#define UNPACK_CALL_ARG_1(n) \
    TVAR(name, n, 0); \
    FVAR(expr, n, 1); \

#define R_CALL_ARG_2 93
#define UNPACK_CALL_ARG_2(n) \
    TVAR(name, n, 0); \
    FVAR(expr, n, 1); \

#define R_CALL_ARG_3 94
#define UNPACK_CALL_ARG_3(n) \
    FVAR(expr, n, 0); \

#define R_CALL_ARG_4 95
#define UNPACK_CALL_ARG_4(n) \
    FVAR(expr, n, 0); \

#define R_TYPED_ARG_LIST 96

#define R_FULL_ARG_LIST 97
#define UNPACK_FULL_ARG_LIST(n) \
    FVAR(default_args, n, 0); \
    FVAR(full_arg_list_2, n, 1); \

#define R_FULL_ARG_LIST_2 98
#define UNPACK_FULL_ARG_LIST_2(n) \
    FVAR(kwargs_or_args_kwargs, n, 0); \

#define R_FULL_ARG_LIST_2_2 99

#define R_ARGS_KWARGS 100
#define UNPACK_ARGS_KWARGS(n) \
    FVAR(typed_arg, n, 0); \
    FVAR(op_comma_default_args, n, 1); \
    FVAR(args_kwargs_4, n, 2); \

#define R_ARGS_KWARGS_3 101
#define UNPACK_ARGS_KWARGS_3(n) \
    FVAR(default_arg, n, 0); \

#define R_ARGS_KWARGS_4 102
#define UNPACK_ARGS_KWARGS_4(n) \
    FVAR(kwargs, n, 0); \

#define R_KWARGS 103
#define UNPACK_KWARGS(n) \
    FVAR(typed_arg, n, 0); \
    TVAR(is_op_comma, n, 1); \

#define R_DEFAULT_ARG 104
#define UNPACK_DEFAULT_ARG(n) \
    FVAR(typed_arg, n, 0); \
    FVAR(op_assign_expr, n, 1); \

#define R_DEFAULT_ARG_2 105
#define UNPACK_DEFAULT_ARG_2(n) \
    FVAR(expr, n, 0); \

#define R_TYPED_ARG 106
#define UNPACK_TYPED_ARG(n) \
    TVAR(name, n, 0); \
    FVAR(op_colon_expr, n, 1); \

#define R_TYPED_ARG_2 107
#define UNPACK_TYPED_ARG_2(n) \
    FVAR(expr, n, 0); \

#define R_SIMPLE_ARG 108
#define UNPACK_SIMPLE_ARG(n) \
    TVAR(name, n, 0); \
    FVAR(op_assign_expr, n, 1); \

#define R_SIMPLE_ARG_2 109
#define UNPACK_SIMPLE_ARG_2(n) \
    FVAR(expr, n, 0); \

#define R_SIMPLE_ARGS 110
#define UNPACK_SIMPLE_ARGS(n) \
    FVAR(simple_args, n, 0); \

#define R_BUILDER_HINT 111
#define UNPACK_BUILDER_HINT(n) \
    FVAR(name_list, n, 0); \

#define R_BUILDER_ARGS 112

#define R_BUILDER_ARGS_2 113
#define UNPACK_BUILDER_ARGS_2(n) \
    FVAR(typed_arg_list, n, 0); \

#define R_NAMED_EXPR 114

#define R_NAMED_EXPR_1 115
#define UNPACK_NAMED_EXPR_1(n) \
    TVAR(name, n, 0); \
    FVAR(expr, n, 1); \

#define R_CONDITIONAL 116
#define UNPACK_CONDITIONAL(n) \
    FVAR(disjunction, n, 0); \
    FVAR(disjunction_1, n, 1); \
    FVAR(expr, n, 2); \

#define R_EXPR 117

#define R_DISJUNCTION 118

#define R_DISJUNCTION_1 119
#define UNPACK_DISJUNCTION_1(n) \
    FVAR(disjunction, n, 0); \
    FVAR(conjunction, n, 1); \

#define R_CONJUNCTION 120

#define R_CONJUNCTION_1 121
#define UNPACK_CONJUNCTION_1(n) \
    FVAR(conjunction, n, 0); \
    FVAR(inversion, n, 1); \

#define R_INVERSION 122

#define R_INVERSION_1 123
#define UNPACK_INVERSION_1(n) \
    FVAR(inversion, n, 0); \

#define R_COMPARISON 124

#define R_COMPARISON_1 125
#define UNPACK_COMPARISON_1(n) \
    FVAR(bitwise_or, n, 0); \
    FVAR(comp_op_bitwise_ors, n, 1); \

#define R_COMPARISON_1_2 126
#define UNPACK_COMPARISON_1_2(n) \
    FVAR(comp_op, n, 0); \
    FVAR(bitwise_or, n, 1); \

#define R_COMP_OP 127

#define R_COMP_OP_8 128

#define R_COMP_OP_10 129

#define R_BITWISE_OR 130

#define R_BITWISE_OR_1 131
#define UNPACK_BITWISE_OR_1(n) \
    FVAR(bitwise_or, n, 0); \
    FVAR(bitwise_xor, n, 1); \

#define R_BITWISE_XOR 132

#define R_BITWISE_XOR_1 133
#define UNPACK_BITWISE_XOR_1(n) \
    FVAR(bitwise_xor, n, 0); \
    FVAR(bitwise_and, n, 1); \

#define R_BITWISE_AND 134

#define R_BITWISE_AND_1 135
#define UNPACK_BITWISE_AND_1(n) \
    FVAR(bitwise_and, n, 0); \
    FVAR(shift_expr, n, 1); \

#define R_SHIFT_EXPR 136

#define R_SHIFT_EXPR_1 137
#define UNPACK_SHIFT_EXPR_1(n) \
    FVAR(shift_expr, n, 0); \
    FVAR(sum, n, 1); \

#define R_SHIFT_EXPR_2 138
#define UNPACK_SHIFT_EXPR_2(n) \
    FVAR(shift_expr, n, 0); \
    FVAR(sum, n, 1); \

#define R_SUM 139

#define R_SUM_1 140
#define UNPACK_SUM_1(n) \
    FVAR(sum, n, 0); \
    FVAR(term, n, 1); \

#define R_SUM_2 141
#define UNPACK_SUM_2(n) \
    FVAR(sum, n, 0); \
    FVAR(term, n, 1); \

#define R_TERM 142

#define R_TERM_1 143
#define UNPACK_TERM_1(n) \
    FVAR(term, n, 0); \
    FVAR(pipe_expr, n, 1); \

#define R_TERM_2 144
#define UNPACK_TERM_2(n) \
    FVAR(term, n, 0); \
    FVAR(pipe_expr, n, 1); \

#define R_TERM_3 145
#define UNPACK_TERM_3(n) \
    FVAR(term, n, 0); \
    FVAR(pipe_expr, n, 1); \

#define R_TERM_4 146
#define UNPACK_TERM_4(n) \
    FVAR(term, n, 0); \
    FVAR(pipe_expr, n, 1); \

#define R_TERM_5 147
#define UNPACK_TERM_5(n) \
    FVAR(term, n, 0); \
    FVAR(pipe_expr, n, 1); \

#define R_PIPE_EXPR 148

#define R_PIPE_EXPR_1 149
#define UNPACK_PIPE_EXPR_1(n) \
    FVAR(pipe_expr, n, 0); \
    FVAR(factor, n, 1); \

#define R_FACTOR 150

#define R_FACTOR_1 151
#define UNPACK_FACTOR_1(n) \
    FVAR(factor, n, 0); \

#define R_FACTOR_2 152
#define UNPACK_FACTOR_2(n) \
    FVAR(factor, n, 0); \

#define R_FACTOR_3 153
#define UNPACK_FACTOR_3(n) \
    FVAR(factor, n, 0); \

#define R_POWER 154

#define R_POWER_1 155
#define UNPACK_POWER_1(n) \
    FVAR(primary, n, 0); \
    FVAR(factor, n, 1); \

#define R_PRIMARY 156

#define R_PRIMARY_1 157
#define UNPACK_PRIMARY_1(n) \
    FVAR(primary, n, 0); \
    TVAR(name, n, 1); \

#define R_PRIMARY_2 158
#define UNPACK_PRIMARY_2(n) \
    FVAR(primary, n, 0); \
    FVAR(invocation, n, 1); \

#define R_PRIMARY_3 159
#define UNPACK_PRIMARY_3(n) \
    FVAR(primary, n, 0); \
    FVAR(subscript, n, 1); \

#define R_TUPLE_ATOM 160
#define UNPACK_TUPLE_ATOM(n) \
    FVAR(list_items, n, 0); \

#define R_LIST_ITERABLE 161
#define UNPACK_LIST_ITERABLE(n) \
    FVAR(list_iterator, n, 0); \

#define R_LIST_ATOM 162
#define UNPACK_LIST_ATOM(n) \
    FVAR(list_items, n, 0); \

#define R_SET_ATOM 163
#define UNPACK_SET_ATOM(n) \
    FVAR(set_items, n, 0); \

#define R_DICT_ITERABLE 164
#define UNPACK_DICT_ITERABLE(n) \
    FVAR(dict_iterator, n, 0); \

#define R_DICT_ATOM 165
#define UNPACK_DICT_ATOM(n) \
    FVAR(dict_items, n, 0); \

#define R_BUILDER 166

#define R_BUILDER_1 167
#define UNPACK_BUILDER_1(n) \
    TVAR(name, n, 0); \
    FVAR(simple_args, n, 1); \
    FVAR(expr, n, 2); \

#define R_BUILDER_2 168
#define UNPACK_BUILDER_2(n) \
    TVAR(name, n, 0); \
    FVAR(builder_hint, n, 1); \
    FVAR(builder_args, n, 2); \
    FVAR(block_suite, n, 3); \

#define R_ATOM 169

#endif // CPEG_ASTGEN_H
