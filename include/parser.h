#ifndef CPEG_PARSER_H
#define CPEG_PARSER_H

#include "peg.h"

RULE(single_input);
RULE(single_input_4);
RULE(file_input);
RULE(eval_input);
RULE(stmt_list);
RULE(stmt);
RULE(stmt_1);
RULE(simple_stmt);
RULE(small_stmt);
RULE(del_stmt);
RULE(return_stmt);
RULE(raise_stmt);
RULE(raise_stmt_3);
RULE(nonlocal_stmt);
RULE(assert_stmt);
RULE(assert_stmt_3);
RULE(name_list);
RULE(star_expr);
RULE(exprlist);
RULE(target);
RULE(target_1);
RULE(target_2);
RULE(target_4);
RULE(targetlist_sp);
RULE(t_primary);
RULE(t_primary_1);
RULE(t_primary_2);
RULE(t_primary_3);
RULE(t_primary_4);
RULE(t_lookahead);
RULE(targetlist);
RULE(expr_or_star);
RULE(exprlist_star);
RULE(subscript);
RULE(slicelist);
RULE(slice);
RULE(slice_1);
RULE(slice_expr);
RULE(dict_item);
RULE(dict_item_1);
RULE(dict_item_2);
RULE(dict_items);
RULE(list_item);
RULE(list_items);
RULE(set_items);
RULE(as_name);
RULE(iter_for);
RULE(iter_if);
RULE(iterator);
RULE(list_iterator);
RULE(dict_iterator);
RULE(assignment);
RULE(pubassign);
RULE(annassign);
RULE(annassign_4);
RULE(augassign);
RULE(simple_assign);
RULE(simple_assign_1);
RULE(augassign_op);
RULE(import_name);
RULE(import_from);
RULE(import_from_names);
RULE(import_from_names_2);
RULE(import_from_items);
RULE(import_as_names_sp);
RULE(import_as_name);
RULE(dotted_as_name);
RULE(import_as_names);
RULE(dotted_as_names);
RULE(dotted_name);
RULE(compound_stmt);
RULE(if_stmt);
RULE(elif_stmt);
RULE(while_stmt);
RULE(for_stmt);
RULE(try_stmt);
RULE(try_stmt_3);
RULE(with_stmt);
RULE(expr_as_name);
RULE(block_suite);
RULE(block_suite_1);
RULE(block_suite_2);
RULE(suite);
RULE(suite_1);
RULE(else_suite);
RULE(finally_suite);
RULE(except_clause);
RULE(except_suite);
RULE(invocation);
RULE(call_arg_list);
RULE(call_arg);
RULE(call_arg_1);
RULE(call_arg_2);
RULE(call_arg_3);
RULE(call_arg_4);
RULE(typed_arg_list);
RULE(full_arg_list);
RULE(full_arg_list_2);
RULE(full_arg_list_2_2);
RULE(args_kwargs);
RULE(args_kwargs_3);
RULE(args_kwargs_4);
RULE(kwargs);
RULE(default_arg);
RULE(default_arg_2);
RULE(typed_arg);
RULE(typed_arg_2);
RULE(simple_arg);
RULE(simple_arg_2);
RULE(simple_args);
RULE(builder_hint);
RULE(builder_args);
RULE(builder_args_2);
RULE(named_expr);
RULE(named_expr_1);
RULE(conditional);
RULE(expr);
RULE(disjunction);
RULE(disjunction_1);
RULE(conjunction);
RULE(conjunction_1);
RULE(inversion);
RULE(inversion_1);
RULE(comparison);
RULE(comparison_1);
RULE(comparison_1_2);
RULE(comp_op);
RULE(comp_op_8);
RULE(comp_op_10);
RULE(bitwise_or);
RULE(bitwise_or_1);
RULE(bitwise_xor);
RULE(bitwise_xor_1);
RULE(bitwise_and);
RULE(bitwise_and_1);
RULE(shift_expr);
RULE(shift_expr_1);
RULE(shift_expr_2);
RULE(sum);
RULE(sum_1);
RULE(sum_2);
RULE(term);
RULE(term_1);
RULE(term_2);
RULE(term_3);
RULE(term_4);
RULE(term_5);
RULE(pipe_expr);
RULE(pipe_expr_1);
RULE(factor);
RULE(factor_1);
RULE(factor_2);
RULE(factor_3);
RULE(power);
RULE(power_1);
RULE(primary);
RULE(primary_1);
RULE(primary_2);
RULE(primary_3);
RULE(tuple_atom);
RULE(list_iterable);
RULE(list_atom);
RULE(set_atom);
RULE(dict_iterable);
RULE(dict_atom);
RULE(builder);
RULE(builder_1);
RULE(builder_2);
RULE(atom);

#endif // CPEG_PARSER_H
