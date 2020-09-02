#include "astgen.h"
#include "tokenmap.h"

void dummy_single_input(FAstNode *n);
void dummy_single_input_4(FAstNode *n);
void dummy_file_input(FAstNode *n);
void dummy_eval_input(FAstNode *n);
void dummy_stmt_list(FAstNode *n);
void dummy_stmt(FAstNode *n);
void dummy_stmt_1(FAstNode *n);
void dummy_simple_stmt(FAstNode *n);
void dummy_small_stmt(FAstNode *n);
void dummy_del_stmt(FAstNode *n);
void dummy_return_stmt(FAstNode *n);
void dummy_raise_stmt(FAstNode *n);
void dummy_raise_stmt_3(FAstNode *n);
void dummy_nonlocal_stmt(FAstNode *n);
void dummy_assert_stmt(FAstNode *n);
void dummy_assert_stmt_3(FAstNode *n);
void dummy_name_list(FAstNode *n);
void dummy_star_expr(FAstNode *n);
void dummy_exprlist(FAstNode *n);
void dummy_target(FAstNode *n);
void dummy_target_1(FAstNode *n);
void dummy_target_2(FAstNode *n);
void dummy_target_4(FAstNode *n);
void dummy_targetlist_sp(FAstNode *n);
void dummy_t_primary(FAstNode *n);
void dummy_t_primary_1(FAstNode *n);
void dummy_t_primary_2(FAstNode *n);
void dummy_t_primary_3(FAstNode *n);
void dummy_t_primary_4(FAstNode *n);
void dummy_t_lookahead(FAstNode *n);
void dummy_targetlist(FAstNode *n);
void dummy_expr_or_star(FAstNode *n);
void dummy_exprlist_star(FAstNode *n);
void dummy_subscript(FAstNode *n);
void dummy_slicelist(FAstNode *n);
void dummy_slice(FAstNode *n);
void dummy_slice_1(FAstNode *n);
void dummy_slice_expr(FAstNode *n);
void dummy_dict_item(FAstNode *n);
void dummy_dict_item_1(FAstNode *n);
void dummy_dict_item_2(FAstNode *n);
void dummy_dict_items(FAstNode *n);
void dummy_list_item(FAstNode *n);
void dummy_list_items(FAstNode *n);
void dummy_set_items(FAstNode *n);
void dummy_as_name(FAstNode *n);
void dummy_iter_for(FAstNode *n);
void dummy_iter_if(FAstNode *n);
void dummy_iterator(FAstNode *n);
void dummy_list_iterator(FAstNode *n);
void dummy_dict_iterator(FAstNode *n);
void dummy_assignment(FAstNode *n);
void dummy_pubassign(FAstNode *n);
void dummy_annassign(FAstNode *n);
void dummy_annassign_4(FAstNode *n);
void dummy_augassign(FAstNode *n);
void dummy_simple_assign(FAstNode *n);
void dummy_simple_assign_1(FAstNode *n);
void dummy_augassign_op(FAstNode *n);
void dummy_import_name(FAstNode *n);
void dummy_import_from(FAstNode *n);
void dummy_import_from_names(FAstNode *n);
void dummy_import_from_names_2(FAstNode *n);
void dummy_import_from_items(FAstNode *n);
void dummy_import_as_names_sp(FAstNode *n);
void dummy_import_as_name(FAstNode *n);
void dummy_dotted_as_name(FAstNode *n);
void dummy_import_as_names(FAstNode *n);
void dummy_dotted_as_names(FAstNode *n);
void dummy_dotted_name(FAstNode *n);
void dummy_compound_stmt(FAstNode *n);
void dummy_if_stmt(FAstNode *n);
void dummy_elif_stmt(FAstNode *n);
void dummy_while_stmt(FAstNode *n);
void dummy_for_stmt(FAstNode *n);
void dummy_try_stmt(FAstNode *n);
void dummy_try_stmt_3(FAstNode *n);
void dummy_with_stmt(FAstNode *n);
void dummy_expr_as_name(FAstNode *n);
void dummy_block_suite(FAstNode *n);
void dummy_block_suite_1(FAstNode *n);
void dummy_block_suite_2(FAstNode *n);
void dummy_suite(FAstNode *n);
void dummy_suite_1(FAstNode *n);
void dummy_else_suite(FAstNode *n);
void dummy_finally_suite(FAstNode *n);
void dummy_except_clause(FAstNode *n);
void dummy_except_suite(FAstNode *n);
void dummy_invocation(FAstNode *n);
void dummy_call_arg_list(FAstNode *n);
void dummy_call_arg(FAstNode *n);
void dummy_call_arg_1(FAstNode *n);
void dummy_call_arg_2(FAstNode *n);
void dummy_call_arg_3(FAstNode *n);
void dummy_call_arg_4(FAstNode *n);
void dummy_typed_arg_list(FAstNode *n);
void dummy_full_arg_list(FAstNode *n);
void dummy_full_arg_list_2(FAstNode *n);
void dummy_full_arg_list_2_2(FAstNode *n);
void dummy_args_kwargs(FAstNode *n);
void dummy_args_kwargs_3(FAstNode *n);
void dummy_args_kwargs_4(FAstNode *n);
void dummy_kwargs(FAstNode *n);
void dummy_default_arg(FAstNode *n);
void dummy_default_arg_2(FAstNode *n);
void dummy_typed_arg(FAstNode *n);
void dummy_typed_arg_2(FAstNode *n);
void dummy_simple_arg(FAstNode *n);
void dummy_simple_arg_2(FAstNode *n);
void dummy_simple_args(FAstNode *n);
void dummy_builder_hint(FAstNode *n);
void dummy_builder_args(FAstNode *n);
void dummy_builder_args_2(FAstNode *n);
void dummy_named_expr(FAstNode *n);
void dummy_named_expr_1(FAstNode *n);
void dummy_conditional(FAstNode *n);
void dummy_expr(FAstNode *n);
void dummy_disjunction(FAstNode *n);
void dummy_disjunction_1(FAstNode *n);
void dummy_conjunction(FAstNode *n);
void dummy_conjunction_1(FAstNode *n);
void dummy_inversion(FAstNode *n);
void dummy_inversion_1(FAstNode *n);
void dummy_comparison(FAstNode *n);
void dummy_comparison_1(FAstNode *n);
void dummy_comparison_1_2(FAstNode *n);
void dummy_comp_op(FAstNode *n);
void dummy_comp_op_8(FAstNode *n);
void dummy_comp_op_10(FAstNode *n);
void dummy_bitwise_or(FAstNode *n);
void dummy_bitwise_or_1(FAstNode *n);
void dummy_bitwise_xor(FAstNode *n);
void dummy_bitwise_xor_1(FAstNode *n);
void dummy_bitwise_and(FAstNode *n);
void dummy_bitwise_and_1(FAstNode *n);
void dummy_shift_expr(FAstNode *n);
void dummy_shift_expr_1(FAstNode *n);
void dummy_shift_expr_2(FAstNode *n);
void dummy_sum(FAstNode *n);
void dummy_sum_1(FAstNode *n);
void dummy_sum_2(FAstNode *n);
void dummy_term(FAstNode *n);
void dummy_term_1(FAstNode *n);
void dummy_term_2(FAstNode *n);
void dummy_term_3(FAstNode *n);
void dummy_term_4(FAstNode *n);
void dummy_term_5(FAstNode *n);
void dummy_pipe_expr(FAstNode *n);
void dummy_pipe_expr_1(FAstNode *n);
void dummy_factor(FAstNode *n);
void dummy_factor_1(FAstNode *n);
void dummy_factor_2(FAstNode *n);
void dummy_factor_3(FAstNode *n);
void dummy_power(FAstNode *n);
void dummy_power_1(FAstNode *n);
void dummy_primary(FAstNode *n);
void dummy_primary_1(FAstNode *n);
void dummy_primary_2(FAstNode *n);
void dummy_primary_3(FAstNode *n);
void dummy_tuple_atom(FAstNode *n);
void dummy_list_iterable(FAstNode *n);
void dummy_list_atom(FAstNode *n);
void dummy_set_atom(FAstNode *n);
void dummy_dict_iterable(FAstNode *n);
void dummy_dict_atom(FAstNode *n);
void dummy_builder(FAstNode *n);
void dummy_builder_1(FAstNode *n);
void dummy_builder_2(FAstNode *n);
void dummy_atom(FAstNode *n);

// single_input:
//     | NEWLINE
//     | ENDMARKER
//     | simple_stmt
//     | compound_stmt NEWLINE
void dummy_single_input(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == 0 && o->ast_v.token->type == T_NEWLINE) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_ENDMARKER) {
        return;
    }
    if (o->ast_t == R_SIMPLE_STMT) {
        dummy_simple_stmt(o);
        return;
    }
    if (o->ast_t == R_SINGLE_INPUT_4) {
        dummy_single_input_4(o);
        return;
    }
}

void dummy_single_input_4(FAstNode *n) {
    UNPACK_SINGLE_INPUT_4(n)
    dummy_compound_stmt(compound_stmt);
}

// file_input:
//     | [stmt_list] ENDMARKER
void dummy_file_input(FAstNode *n) {
    UNPACK_FILE_INPUT(n)
    dummy_stmt_list(stmt_list);
}

// eval_input:
//     | exprlist NEWLINE* ENDMARKER
void dummy_eval_input(FAstNode *n) {
    UNPACK_EVAL_INPUT(n)
    dummy_exprlist(exprlist);
}

// stmt_list:
//     | stmt+
void dummy_stmt_list(FAstNode *n) {
    UNPACK_STMT_LIST(n)
    dummy_stmt(stmts);
}

// stmt:
//     | (simple_stmt | compound_stmt) NEWLINE
void dummy_stmt(FAstNode *n) {
    UNPACK_STMT(n)
    dummy_stmt_1(simple_stmt_or_compound_stmt);
}

void dummy_stmt_1(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_SIMPLE_STMT) {
        dummy_simple_stmt(o);
        return;
    }
    if (o->ast_t == R_COMPOUND_STMT) {
        dummy_compound_stmt(o);
        return;
    }
}

// simple_stmt:
//     | ';'.small_stmt+ [';']
void dummy_simple_stmt(FAstNode *n) {
    UNPACK_SIMPLE_STMT(n)
    dummy_small_stmt(small_stmts);
}

// small_stmt:
//     | 'pass'
//     | 'break'
//     | 'continue'
//     | return_stmt
//     | raise_stmt
//     | del_stmt
//     | nonlocal_stmt
//     | assert_stmt
//     | import_name
//     | import_from
//     | assignment
void dummy_small_stmt(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == 0 && o->ast_v.token->type == T_PASS) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_BREAK) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_CONTINUE) {
        return;
    }
    if (o->ast_t == R_RETURN_STMT) {
        dummy_return_stmt(o);
        return;
    }
    if (o->ast_t == R_RAISE_STMT) {
        dummy_raise_stmt(o);
        return;
    }
    if (o->ast_t == R_DEL_STMT) {
        dummy_del_stmt(o);
        return;
    }
    if (o->ast_t == R_NONLOCAL_STMT) {
        dummy_nonlocal_stmt(o);
        return;
    }
    if (o->ast_t == R_ASSERT_STMT) {
        dummy_assert_stmt(o);
        return;
    }
    if (o->ast_t == R_IMPORT_NAME) {
        dummy_import_name(o);
        return;
    }
    if (o->ast_t == R_IMPORT_FROM) {
        dummy_import_from(o);
        return;
    }
    if (o->ast_t == R_ASSIGNMENT) {
        dummy_assignment(o);
        return;
    }
}

// del_stmt:
//     | 'del' targetlist
void dummy_del_stmt(FAstNode *n) {
    UNPACK_DEL_STMT(n)
    dummy_targetlist(targetlist);
}

// return_stmt:
//     | 'return' [exprlist_star]
void dummy_return_stmt(FAstNode *n) {
    UNPACK_RETURN_STMT(n)
    dummy_exprlist_star(exprlist_star);
}

// raise_stmt:
//     | 'raise' expr ['from' expr]
void dummy_raise_stmt(FAstNode *n) {
    UNPACK_RAISE_STMT(n)
    dummy_expr(expr);
    dummy_raise_stmt_3(from_expr);
}

void dummy_raise_stmt_3(FAstNode *n) {
    UNPACK_RAISE_STMT_3(n)
    dummy_expr(expr);
}

// nonlocal_stmt:
//     | 'nonlocal' name_list
void dummy_nonlocal_stmt(FAstNode *n) {
    UNPACK_NONLOCAL_STMT(n)
    dummy_name_list(name_list);
}

// assert_stmt:
//     | 'assert' expr [',' expr]
void dummy_assert_stmt(FAstNode *n) {
    UNPACK_ASSERT_STMT(n)
    dummy_expr(expr);
    dummy_assert_stmt_3(op_comma_expr);
}

void dummy_assert_stmt_3(FAstNode *n) {
    UNPACK_ASSERT_STMT_3(n)
    dummy_expr(expr);
}

// name_list:
//     | ','.NAME+
void dummy_name_list(FAstNode *n) {
    UNPACK_NAME_LIST(n)
}

// star_expr:
//     | '*' bitwise_or
void dummy_star_expr(FAstNode *n) {
    UNPACK_STAR_EXPR(n)
    dummy_bitwise_or(bitwise_or);
}

// exprlist:
//     | ','.expr+ [',']
void dummy_exprlist(FAstNode *n) {
    UNPACK_EXPRLIST(n)
    dummy_expr(exprs);
}

// target:
//     | t_primary '.' NAME !t_lookahead
//     | t_primary subscript !t_lookahead
//     | NAME
//     | '(' targetlist_sp ')'
void dummy_target(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_TARGET_1) {
        dummy_target_1(o);
        return;
    }
    if (o->ast_t == R_TARGET_2) {
        dummy_target_2(o);
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_NAME) {
        return;
    }
    if (o->ast_t == R_TARGET_4) {
        dummy_target_4(o);
        return;
    }
}

void dummy_target_1(FAstNode *n) {
    UNPACK_TARGET_1(n)
    dummy_t_primary(t_primary);
}

void dummy_target_2(FAstNode *n) {
    UNPACK_TARGET_2(n)
    dummy_t_primary(t_primary);
    dummy_subscript(subscript);
}

void dummy_target_4(FAstNode *n) {
    UNPACK_TARGET_4(n)
    dummy_targetlist_sp(targetlist_sp);
}

// targetlist_sp (allow_whitespace=true):
//     | targetlist
void dummy_targetlist_sp(FAstNode *n) {
    UNPACK_TARGETLIST_SP(n)
    dummy_targetlist(targetlist);
}

// t_primary (left_recursive):
//     | t_primary '.' NAME &t_lookahead
//     | t_primary invocation &t_lookahead
//     | t_primary subscript &t_lookahead
//     | atom &t_lookahead
void dummy_t_primary(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_T_PRIMARY_1) {
        dummy_t_primary_1(o);
        return;
    }
    if (o->ast_t == R_T_PRIMARY_2) {
        dummy_t_primary_2(o);
        return;
    }
    if (o->ast_t == R_T_PRIMARY_3) {
        dummy_t_primary_3(o);
        return;
    }
    if (o->ast_t == R_T_PRIMARY_4) {
        dummy_t_primary_4(o);
        return;
    }
}

void dummy_t_primary_1(FAstNode *n) {
    UNPACK_T_PRIMARY_1(n)
    dummy_t_primary(t_primary);
}

void dummy_t_primary_2(FAstNode *n) {
    UNPACK_T_PRIMARY_2(n)
    dummy_t_primary(t_primary);
    dummy_invocation(invocation);
}

void dummy_t_primary_3(FAstNode *n) {
    UNPACK_T_PRIMARY_3(n)
    dummy_t_primary(t_primary);
    dummy_subscript(subscript);
}

void dummy_t_primary_4(FAstNode *n) {
    UNPACK_T_PRIMARY_4(n)
    dummy_atom(atom);
}

// t_lookahead:
//     | '.'
//     | '('
//     | '['
void dummy_t_lookahead(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_DOT) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_LPAR) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_LSQB) {
        return;
    }
}

// targetlist:
//     | ','.target+ [',']
void dummy_targetlist(FAstNode *n) {
    UNPACK_TARGETLIST(n)
    dummy_target(targets);
}

// expr_or_star:
//     | star_expr
//     | expr
void dummy_expr_or_star(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_STAR_EXPR) {
        dummy_star_expr(o);
        return;
    }
    if (o->ast_t == R_EXPR) {
        dummy_expr(o);
        return;
    }
}

// exprlist_star:
//     | ','.expr_or_star+ [',']
void dummy_exprlist_star(FAstNode *n) {
    UNPACK_EXPRLIST_STAR(n)
    dummy_expr_or_star(expr_or_stars);
}

// subscript:
//     | '[' slicelist ']'
void dummy_subscript(FAstNode *n) {
    UNPACK_SUBSCRIPT(n)
    dummy_slicelist(slicelist);
}

// slicelist:
//     | ','.slice+ [',']
void dummy_slicelist(FAstNode *n) {
    UNPACK_SLICELIST(n)
    dummy_slice(slices);
}

// slice:
//     | [expr] slice_expr [slice_expr]
//     | expr
void dummy_slice(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_SLICE_1) {
        dummy_slice_1(o);
        return;
    }
    if (o->ast_t == R_EXPR) {
        dummy_expr(o);
        return;
    }
}

void dummy_slice_1(FAstNode *n) {
    UNPACK_SLICE_1(n)
    dummy_expr(expr);
    dummy_slice_expr(slice_expr);
    dummy_slice_expr(slice_expr_1);
}

// slice_expr:
//     | ':' [expr]
void dummy_slice_expr(FAstNode *n) {
    UNPACK_SLICE_EXPR(n)
    dummy_expr(expr);
}

// dict_item:
//     | expr ':' expr
//     | '**' bitwise_or
void dummy_dict_item(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_DICT_ITEM_1) {
        dummy_dict_item_1(o);
        return;
    }
    if (o->ast_t == R_DICT_ITEM_2) {
        dummy_dict_item_2(o);
        return;
    }
}

void dummy_dict_item_1(FAstNode *n) {
    UNPACK_DICT_ITEM_1(n)
    dummy_expr(expr);
    dummy_expr(expr_1);
}

void dummy_dict_item_2(FAstNode *n) {
    UNPACK_DICT_ITEM_2(n)
    dummy_bitwise_or(bitwise_or);
}

// dict_items (allow_whitespace=true):
//     | ','.dict_item+ [',']
void dummy_dict_items(FAstNode *n) {
    UNPACK_DICT_ITEMS(n)
    dummy_dict_item(dict_items);
}

// list_item:
//     | star_expr
//     | named_expr
void dummy_list_item(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_STAR_EXPR) {
        dummy_star_expr(o);
        return;
    }
    if (o->ast_t == R_NAMED_EXPR) {
        dummy_named_expr(o);
        return;
    }
}

// list_items (allow_whitespace=true):
//     | ','.list_item+ [',']
void dummy_list_items(FAstNode *n) {
    UNPACK_LIST_ITEMS(n)
    dummy_list_item(list_items);
}

// set_items (allow_whitespace=true):
//     | exprlist_star
void dummy_set_items(FAstNode *n) {
    UNPACK_SET_ITEMS(n)
    dummy_exprlist_star(exprlist_star);
}

// as_name:
//     | 'as' NAME
void dummy_as_name(FAstNode *n) {
    UNPACK_AS_NAME(n)
}

// iter_for:
//     | 'for' targetlist 'in' disjunction [iter_if]
void dummy_iter_for(FAstNode *n) {
    UNPACK_ITER_FOR(n)
    dummy_targetlist(targetlist);
    dummy_disjunction(disjunction);
    dummy_iter_if(iter_if);
}

// iter_if:
//     | 'if' named_expr
void dummy_iter_if(FAstNode *n) {
    UNPACK_ITER_IF(n)
    dummy_named_expr(named_expr);
}

// iterator:
//     | iter_for* 'for' targetlist [iter_if]
void dummy_iterator(FAstNode *n) {
    UNPACK_ITERATOR(n)
    dummy_iter_for(iter_fors);
    dummy_targetlist(targetlist);
    dummy_iter_if(iter_if);
}

// list_iterator (allow_whitespace=true):
//     | expr_or_star iterator
void dummy_list_iterator(FAstNode *n) {
    UNPACK_LIST_ITERATOR(n)
    dummy_expr_or_star(expr_or_star);
    dummy_iterator(iterator);
}

// dict_iterator (allow_whitespace=true):
//     | dict_item iterator
void dummy_dict_iterator(FAstNode *n) {
    UNPACK_DICT_ITERATOR(n)
    dummy_dict_item(dict_item);
    dummy_iterator(iterator);
}

// assignment:
//     | pubassign
//     | annassign
//     | augassign
//     | simple_assign
void dummy_assignment(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_PUBASSIGN) {
        dummy_pubassign(o);
        return;
    }
    if (o->ast_t == R_ANNASSIGN) {
        dummy_annassign(o);
        return;
    }
    if (o->ast_t == R_AUGASSIGN) {
        dummy_augassign(o);
        return;
    }
    if (o->ast_t == R_SIMPLE_ASSIGN) {
        dummy_simple_assign(o);
        return;
    }
}

// pubassign:
//     | '/' NAME '=' exprlist
void dummy_pubassign(FAstNode *n) {
    UNPACK_PUBASSIGN(n)
    dummy_exprlist(exprlist);
}

// annassign:
//     | target ':' expr ['=' exprlist]
void dummy_annassign(FAstNode *n) {
    UNPACK_ANNASSIGN(n)
    dummy_target(target);
    dummy_expr(expr);
    dummy_annassign_4(op_assign_exprlist);
}

void dummy_annassign_4(FAstNode *n) {
    UNPACK_ANNASSIGN_4(n)
    dummy_exprlist(exprlist);
}

// augassign:
//     | target augassign_op exprlist
void dummy_augassign(FAstNode *n) {
    UNPACK_AUGASSIGN(n)
    dummy_target(target);
    dummy_augassign_op(augassign_op);
    dummy_exprlist(exprlist);
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
void dummy_simple_assign(FAstNode *n) {
    UNPACK_SIMPLE_ASSIGN(n)
    dummy_simple_assign_1(targetlist_op_assigns);
    dummy_exprlist_star(exprlist_star);
}

void dummy_simple_assign_1(FAstNode *n) {
    UNPACK_SIMPLE_ASSIGN_1(n)
    dummy_targetlist(targetlist);
}

// augassign_op:
//     | '+='
//     | '-='
//     | '*='
//     | '@='
//     | '/='
//     | '%='
//     | '&='
//     | '|='
//     | '^='
//     | '<<='
//     | '>>='
//     | '**='
//     | '//='
void dummy_augassign_op(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_PLUS_ASSIGN) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_MINUS_ASSIGN) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_TIMES_ASSIGN) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_MATRIX_TIMES_ASSIGN) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_DIV_ASSIGN) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_MODULUS_ASSIGN) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_BIT_AND_ASSIGN) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_BIT_OR_ASSIGN) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_BIT_XOR_ASSIGN) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_LSHIFT_ASSIGN) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_RSHIFT_ASSIGN) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_POWER_ASSIGN) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_FLOOR_DIV_ASSIGN) {
        return;
    }
}

// import_name:
//     | 'import' dotted_as_names
void dummy_import_name(FAstNode *n) {
    UNPACK_IMPORT_NAME(n)
    dummy_dotted_as_names(dotted_as_names);
}

// import_from:
//     | 'from' import_from_names 'import' import_from_items
void dummy_import_from(FAstNode *n) {
    UNPACK_IMPORT_FROM(n)
    dummy_import_from_names(import_from_names);
    dummy_import_from_items(import_from_items);
}

// import_from_names:
//     | dotted_name
//     | '.'+ [dotted_name]
void dummy_import_from_names(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_DOTTED_NAME) {
        dummy_dotted_name(o);
        return;
    }
    if (o->ast_t == R_IMPORT_FROM_NAMES_2) {
        dummy_import_from_names_2(o);
        return;
    }
}

void dummy_import_from_names_2(FAstNode *n) {
    UNPACK_IMPORT_FROM_NAMES_2(n)
    dummy_dotted_name(dotted_name);
}

// import_from_items:
//     | '*'
//     | import_as_names_sp
//     | import_as_names
void dummy_import_from_items(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_TIMES) {
        return;
    }
    if (o->ast_t == R_IMPORT_AS_NAMES_SP) {
        dummy_import_as_names_sp(o);
        return;
    }
    if (o->ast_t == R_IMPORT_AS_NAMES) {
        dummy_import_as_names(o);
        return;
    }
}

// import_as_names_sp (allow_whitespace=true):
//     | '(' import_as_names [','] ')'
void dummy_import_as_names_sp(FAstNode *n) {
    UNPACK_IMPORT_AS_NAMES_SP(n)
    dummy_import_as_names(import_as_names);
}

// import_as_name:
//     | NAME [as_name]
void dummy_import_as_name(FAstNode *n) {
    UNPACK_IMPORT_AS_NAME(n)
    dummy_as_name(as_name);
}

// dotted_as_name:
//     | dotted_name [as_name]
void dummy_dotted_as_name(FAstNode *n) {
    UNPACK_DOTTED_AS_NAME(n)
    dummy_dotted_name(dotted_name);
    dummy_as_name(as_name);
}

// import_as_names:
//     | ','.import_as_name+
void dummy_import_as_names(FAstNode *n) {
    UNPACK_IMPORT_AS_NAMES(n)
    dummy_import_as_name(import_as_names);
}

// dotted_as_names:
//     | ','.dotted_as_name+
void dummy_dotted_as_names(FAstNode *n) {
    UNPACK_DOTTED_AS_NAMES(n)
    dummy_dotted_as_name(dotted_as_names);
}

// dotted_name:
//     | '.'.NAME+
void dummy_dotted_name(FAstNode *n) {
    UNPACK_DOTTED_NAME(n)
}

// compound_stmt:
//     | if_stmt
//     | while_stmt
//     | for_stmt
//     | try_stmt
//     | with_stmt
void dummy_compound_stmt(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_IF_STMT) {
        dummy_if_stmt(o);
        return;
    }
    if (o->ast_t == R_WHILE_STMT) {
        dummy_while_stmt(o);
        return;
    }
    if (o->ast_t == R_FOR_STMT) {
        dummy_for_stmt(o);
        return;
    }
    if (o->ast_t == R_TRY_STMT) {
        dummy_try_stmt(o);
        return;
    }
    if (o->ast_t == R_WITH_STMT) {
        dummy_with_stmt(o);
        return;
    }
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
void dummy_if_stmt(FAstNode *n) {
    UNPACK_IF_STMT(n)
    dummy_named_expr(named_expr);
    dummy_suite(suite);
    dummy_elif_stmt(elif_stmts);
    dummy_else_suite(else_suite);
}

// elif_stmt:
//     | 'elif' named_expr suite
void dummy_elif_stmt(FAstNode *n) {
    UNPACK_ELIF_STMT(n)
    dummy_named_expr(named_expr);
    dummy_suite(suite);
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
void dummy_while_stmt(FAstNode *n) {
    UNPACK_WHILE_STMT(n)
    dummy_named_expr(named_expr);
    dummy_suite(suite);
    dummy_else_suite(else_suite);
}

// for_stmt:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
void dummy_for_stmt(FAstNode *n) {
    UNPACK_FOR_STMT(n)
    dummy_targetlist(targetlist);
    dummy_exprlist(exprlist);
    dummy_suite(suite);
    dummy_else_suite(else_suite);
}

// try_stmt:
//     | 'try' suite (except_suite | finally_suite)
void dummy_try_stmt(FAstNode *n) {
    UNPACK_TRY_STMT(n)
    dummy_suite(suite);
    dummy_try_stmt_3(except_suite_or_finally_suite);
}

void dummy_try_stmt_3(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_EXCEPT_SUITE) {
        dummy_except_suite(o);
        return;
    }
    if (o->ast_t == R_FINALLY_SUITE) {
        dummy_finally_suite(o);
        return;
    }
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
void dummy_with_stmt(FAstNode *n) {
    UNPACK_WITH_STMT(n)
    dummy_expr_as_name(expr_as_names);
    dummy_suite(suite);
}

// expr_as_name:
//     | expr [as_name]
void dummy_expr_as_name(FAstNode *n) {
    UNPACK_EXPR_AS_NAME(n)
    dummy_expr(expr);
    dummy_as_name(as_name);
}

// block_suite (allow_whitespace=false):
//     | '{' NEWLINE stmt_list '}'
//     | '{' [simple_stmt] '}'
void dummy_block_suite(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_BLOCK_SUITE_1) {
        dummy_block_suite_1(o);
        return;
    }
    if (o->ast_t == R_BLOCK_SUITE_2) {
        dummy_block_suite_2(o);
        return;
    }
}

void dummy_block_suite_1(FAstNode *n) {
    UNPACK_BLOCK_SUITE_1(n)
    dummy_stmt_list(stmt_list);
}

void dummy_block_suite_2(FAstNode *n) {
    UNPACK_BLOCK_SUITE_2(n)
    dummy_simple_stmt(simple_stmt);
}

// suite:
//     | ':' simple_stmt
//     | block_suite
void dummy_suite(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_SUITE_1) {
        dummy_suite_1(o);
        return;
    }
    if (o->ast_t == R_BLOCK_SUITE) {
        dummy_block_suite(o);
        return;
    }
}

void dummy_suite_1(FAstNode *n) {
    UNPACK_SUITE_1(n)
    dummy_simple_stmt(simple_stmt);
}

// else_suite:
//     | 'else' suite
void dummy_else_suite(FAstNode *n) {
    UNPACK_ELSE_SUITE(n)
    dummy_suite(suite);
}

// finally_suite:
//     | 'finally' suite
void dummy_finally_suite(FAstNode *n) {
    UNPACK_FINALLY_SUITE(n)
    dummy_suite(suite);
}

// except_clause:
//     | 'except' [expr_as_name] suite
void dummy_except_clause(FAstNode *n) {
    UNPACK_EXCEPT_CLAUSE(n)
    dummy_expr_as_name(expr_as_name);
    dummy_suite(suite);
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
void dummy_except_suite(FAstNode *n) {
    UNPACK_EXCEPT_SUITE(n)
    dummy_except_clause(except_clauses);
    dummy_else_suite(else_suite);
    dummy_finally_suite(finally_suite);
}

// invocation:
//     | '(' [call_arg_list] ')'
void dummy_invocation(FAstNode *n) {
    UNPACK_INVOCATION(n)
    dummy_call_arg_list(call_arg_list);
}

// call_arg_list (allow_whitespace=true):
//     | ','.call_arg+ [',']
void dummy_call_arg_list(FAstNode *n) {
    UNPACK_CALL_ARG_LIST(n)
    dummy_call_arg(call_args);
}

// call_arg:
//     | NAME ':=' expr
//     | NAME '=' expr
//     | '**' expr
//     | '*' expr
//     | expr
void dummy_call_arg(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_CALL_ARG_1) {
        dummy_call_arg_1(o);
        return;
    }
    if (o->ast_t == R_CALL_ARG_2) {
        dummy_call_arg_2(o);
        return;
    }
    if (o->ast_t == R_CALL_ARG_3) {
        dummy_call_arg_3(o);
        return;
    }
    if (o->ast_t == R_CALL_ARG_4) {
        dummy_call_arg_4(o);
        return;
    }
    if (o->ast_t == R_EXPR) {
        dummy_expr(o);
        return;
    }
}

void dummy_call_arg_1(FAstNode *n) {
    UNPACK_CALL_ARG_1(n)
    dummy_expr(expr);
}

void dummy_call_arg_2(FAstNode *n) {
    UNPACK_CALL_ARG_2(n)
    dummy_expr(expr);
}

void dummy_call_arg_3(FAstNode *n) {
    UNPACK_CALL_ARG_3(n)
    dummy_expr(expr);
}

void dummy_call_arg_4(FAstNode *n) {
    UNPACK_CALL_ARG_4(n)
    dummy_expr(expr);
}

// typed_arg_list (allow_whitespace=true):
//     | kwargs
//     | args_kwargs
//     | full_arg_list
void dummy_typed_arg_list(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_KWARGS) {
        dummy_kwargs(o);
        return;
    }
    if (o->ast_t == R_ARGS_KWARGS) {
        dummy_args_kwargs(o);
        return;
    }
    if (o->ast_t == R_FULL_ARG_LIST) {
        dummy_full_arg_list(o);
        return;
    }
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
void dummy_full_arg_list(FAstNode *n) {
    UNPACK_FULL_ARG_LIST(n)
    dummy_default_arg(default_args);
    dummy_full_arg_list_2(full_arg_list);
}

void dummy_full_arg_list_2(FAstNode *n) {
    UNPACK_FULL_ARG_LIST_2(n)
    dummy_full_arg_list_2_2(kwargs_or_args_kwargs);
}

void dummy_full_arg_list_2_2(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_KWARGS) {
        dummy_kwargs(o);
        return;
    }
    if (o->ast_t == R_ARGS_KWARGS) {
        dummy_args_kwargs(o);
        return;
    }
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
void dummy_args_kwargs(FAstNode *n) {
    UNPACK_ARGS_KWARGS(n)
    dummy_typed_arg(typed_arg);
    dummy_args_kwargs_3(op_comma_default_args);
    dummy_args_kwargs_4(args_kwargs);
}

void dummy_args_kwargs_3(FAstNode *n) {
    UNPACK_ARGS_KWARGS_3(n)
    dummy_default_arg(default_arg);
}

void dummy_args_kwargs_4(FAstNode *n) {
    UNPACK_ARGS_KWARGS_4(n)
    dummy_kwargs(kwargs);
}

// kwargs:
//     | '**' typed_arg [',']
void dummy_kwargs(FAstNode *n) {
    UNPACK_KWARGS(n)
    dummy_typed_arg(typed_arg);
}

// default_arg:
//     | typed_arg ['=' expr]
void dummy_default_arg(FAstNode *n) {
    UNPACK_DEFAULT_ARG(n)
    dummy_typed_arg(typed_arg);
    dummy_default_arg_2(op_assign_expr);
}

void dummy_default_arg_2(FAstNode *n) {
    UNPACK_DEFAULT_ARG_2(n)
    dummy_expr(expr);
}

// typed_arg:
//     | NAME [':' expr]
void dummy_typed_arg(FAstNode *n) {
    UNPACK_TYPED_ARG(n)
    dummy_typed_arg_2(op_colon_expr);
}

void dummy_typed_arg_2(FAstNode *n) {
    UNPACK_TYPED_ARG_2(n)
    dummy_expr(expr);
}

// simple_arg:
//     | NAME ['=' expr]
void dummy_simple_arg(FAstNode *n) {
    UNPACK_SIMPLE_ARG(n)
    dummy_simple_arg_2(op_assign_expr);
}

void dummy_simple_arg_2(FAstNode *n) {
    UNPACK_SIMPLE_ARG_2(n)
    dummy_expr(expr);
}

// simple_args:
//     | ','.simple_arg+
void dummy_simple_args(FAstNode *n) {
    UNPACK_SIMPLE_ARGS(n)
    dummy_simple_arg(simple_args);
}

// builder_hint:
//     | '<' name_list '>'
void dummy_builder_hint(FAstNode *n) {
    UNPACK_BUILDER_HINT(n)
    dummy_name_list(name_list);
}

// builder_args:
//     | simple_args
//     | '(' [typed_arg_list] ')'
void dummy_builder_args(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_SIMPLE_ARGS) {
        dummy_simple_args(o);
        return;
    }
    if (o->ast_t == R_BUILDER_ARGS_2) {
        dummy_builder_args_2(o);
        return;
    }
}

void dummy_builder_args_2(FAstNode *n) {
    UNPACK_BUILDER_ARGS_2(n)
    dummy_typed_arg_list(typed_arg_list);
}

// named_expr:
//     | NAME ':=' expr
//     | expr
void dummy_named_expr(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_NAMED_EXPR_1) {
        dummy_named_expr_1(o);
        return;
    }
    if (o->ast_t == R_EXPR) {
        dummy_expr(o);
        return;
    }
}

void dummy_named_expr_1(FAstNode *n) {
    UNPACK_NAMED_EXPR_1(n)
    dummy_expr(expr);
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
void dummy_conditional(FAstNode *n) {
    UNPACK_CONDITIONAL(n)
    dummy_disjunction(disjunction);
    dummy_disjunction(disjunction_1);
    dummy_expr(expr);
}

// expr:
//     | conditional
//     | disjunction
void dummy_expr(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_CONDITIONAL) {
        dummy_conditional(o);
        return;
    }
    if (o->ast_t == R_DISJUNCTION) {
        dummy_disjunction(o);
        return;
    }
}

// disjunction (left_recursive):
//     | disjunction 'or' conjunction
//     | conjunction
void dummy_disjunction(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_DISJUNCTION_1) {
        dummy_disjunction_1(o);
        return;
    }
    if (o->ast_t == R_CONJUNCTION) {
        dummy_conjunction(o);
        return;
    }
}

void dummy_disjunction_1(FAstNode *n) {
    UNPACK_DISJUNCTION_1(n)
    dummy_disjunction(disjunction);
    dummy_conjunction(conjunction);
}

// conjunction (left_recursive):
//     | conjunction 'and' inversion
//     | inversion
void dummy_conjunction(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_CONJUNCTION_1) {
        dummy_conjunction_1(o);
        return;
    }
    if (o->ast_t == R_INVERSION) {
        dummy_inversion(o);
        return;
    }
}

void dummy_conjunction_1(FAstNode *n) {
    UNPACK_CONJUNCTION_1(n)
    dummy_conjunction(conjunction);
    dummy_inversion(inversion);
}

// inversion:
//     | 'not' inversion
//     | comparison
void dummy_inversion(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_INVERSION_1) {
        dummy_inversion_1(o);
        return;
    }
    if (o->ast_t == R_COMPARISON) {
        dummy_comparison(o);
        return;
    }
}

void dummy_inversion_1(FAstNode *n) {
    UNPACK_INVERSION_1(n)
    dummy_inversion(inversion);
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
void dummy_comparison(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_COMPARISON_1) {
        dummy_comparison_1(o);
        return;
    }
    if (o->ast_t == R_BITWISE_OR) {
        dummy_bitwise_or(o);
        return;
    }
}

void dummy_comparison_1(FAstNode *n) {
    UNPACK_COMPARISON_1(n)
    dummy_bitwise_or(bitwise_or);
    dummy_comparison_1_2(comp_op_bitwise_ors);
}

void dummy_comparison_1_2(FAstNode *n) {
    UNPACK_COMPARISON_1_2(n)
    dummy_comp_op(comp_op);
    dummy_bitwise_or(bitwise_or);
}

// comp_op:
//     | '<'
//     | '>'
//     | '=='
//     | '>='
//     | '<='
//     | '!='
//     | 'in'
//     | 'not' 'in'
//     | 'is'
//     | 'is' 'not'
void dummy_comp_op(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_LESS) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_GREATER) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_EQUAL) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_MORE_EQUAL) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_LESS_EQUAL) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_NEQUAL) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_IN) {
        return;
    }
    if (o->ast_t == R_COMP_OP_8) {
        dummy_comp_op_8(o);
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_IS) {
        return;
    }
    if (o->ast_t == R_COMP_OP_10) {
        dummy_comp_op_10(o);
        return;
    }
}

void dummy_comp_op_8(FAstNode *n) {
}

void dummy_comp_op_10(FAstNode *n) {
}

// bitwise_or (left_recursive):
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
void dummy_bitwise_or(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_BITWISE_OR_1) {
        dummy_bitwise_or_1(o);
        return;
    }
    if (o->ast_t == R_BITWISE_XOR) {
        dummy_bitwise_xor(o);
        return;
    }
}

void dummy_bitwise_or_1(FAstNode *n) {
    UNPACK_BITWISE_OR_1(n)
    dummy_bitwise_or(bitwise_or);
    dummy_bitwise_xor(bitwise_xor);
}

// bitwise_xor (left_recursive):
//     | bitwise_xor '^' bitwise_and
//     | bitwise_and
void dummy_bitwise_xor(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_BITWISE_XOR_1) {
        dummy_bitwise_xor_1(o);
        return;
    }
    if (o->ast_t == R_BITWISE_AND) {
        dummy_bitwise_and(o);
        return;
    }
}

void dummy_bitwise_xor_1(FAstNode *n) {
    UNPACK_BITWISE_XOR_1(n)
    dummy_bitwise_xor(bitwise_xor);
    dummy_bitwise_and(bitwise_and);
}

// bitwise_and (left_recursive):
//     | bitwise_and '&' shift_expr
//     | shift_expr
void dummy_bitwise_and(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_BITWISE_AND_1) {
        dummy_bitwise_and_1(o);
        return;
    }
    if (o->ast_t == R_SHIFT_EXPR) {
        dummy_shift_expr(o);
        return;
    }
}

void dummy_bitwise_and_1(FAstNode *n) {
    UNPACK_BITWISE_AND_1(n)
    dummy_bitwise_and(bitwise_and);
    dummy_shift_expr(shift_expr);
}

// shift_expr (left_recursive):
//     | shift_expr '<<' sum
//     | shift_expr '>>' sum
//     | sum
void dummy_shift_expr(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_SHIFT_EXPR_1) {
        dummy_shift_expr_1(o);
        return;
    }
    if (o->ast_t == R_SHIFT_EXPR_2) {
        dummy_shift_expr_2(o);
        return;
    }
    if (o->ast_t == R_SUM) {
        dummy_sum(o);
        return;
    }
}

void dummy_shift_expr_1(FAstNode *n) {
    UNPACK_SHIFT_EXPR_1(n)
    dummy_shift_expr(shift_expr);
    dummy_sum(sum);
}

void dummy_shift_expr_2(FAstNode *n) {
    UNPACK_SHIFT_EXPR_2(n)
    dummy_shift_expr(shift_expr);
    dummy_sum(sum);
}

// sum (left_recursive):
//     | sum '+' term
//     | sum '-' term
//     | term
void dummy_sum(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_SUM_1) {
        dummy_sum_1(o);
        return;
    }
    if (o->ast_t == R_SUM_2) {
        dummy_sum_2(o);
        return;
    }
    if (o->ast_t == R_TERM) {
        dummy_term(o);
        return;
    }
}

void dummy_sum_1(FAstNode *n) {
    UNPACK_SUM_1(n)
    dummy_sum(sum);
    dummy_term(term);
}

void dummy_sum_2(FAstNode *n) {
    UNPACK_SUM_2(n)
    dummy_sum(sum);
    dummy_term(term);
}

// term (left_recursive):
//     | term '*' pipe_expr
//     | term '/' pipe_expr
//     | term '%' pipe_expr
//     | term '//' pipe_expr
//     | term '@' pipe_expr
//     | pipe_expr
void dummy_term(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_TERM_1) {
        dummy_term_1(o);
        return;
    }
    if (o->ast_t == R_TERM_2) {
        dummy_term_2(o);
        return;
    }
    if (o->ast_t == R_TERM_3) {
        dummy_term_3(o);
        return;
    }
    if (o->ast_t == R_TERM_4) {
        dummy_term_4(o);
        return;
    }
    if (o->ast_t == R_TERM_5) {
        dummy_term_5(o);
        return;
    }
    if (o->ast_t == R_PIPE_EXPR) {
        dummy_pipe_expr(o);
        return;
    }
}

void dummy_term_1(FAstNode *n) {
    UNPACK_TERM_1(n)
    dummy_term(term);
    dummy_pipe_expr(pipe_expr);
}

void dummy_term_2(FAstNode *n) {
    UNPACK_TERM_2(n)
    dummy_term(term);
    dummy_pipe_expr(pipe_expr);
}

void dummy_term_3(FAstNode *n) {
    UNPACK_TERM_3(n)
    dummy_term(term);
    dummy_pipe_expr(pipe_expr);
}

void dummy_term_4(FAstNode *n) {
    UNPACK_TERM_4(n)
    dummy_term(term);
    dummy_pipe_expr(pipe_expr);
}

void dummy_term_5(FAstNode *n) {
    UNPACK_TERM_5(n)
    dummy_term(term);
    dummy_pipe_expr(pipe_expr);
}

// pipe_expr (left_recursive):
//     | pipe_expr '->' factor
//     | factor
void dummy_pipe_expr(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_PIPE_EXPR_1) {
        dummy_pipe_expr_1(o);
        return;
    }
    if (o->ast_t == R_FACTOR) {
        dummy_factor(o);
        return;
    }
}

void dummy_pipe_expr_1(FAstNode *n) {
    UNPACK_PIPE_EXPR_1(n)
    dummy_pipe_expr(pipe_expr);
    dummy_factor(factor);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
void dummy_factor(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_FACTOR_1) {
        dummy_factor_1(o);
        return;
    }
    if (o->ast_t == R_FACTOR_2) {
        dummy_factor_2(o);
        return;
    }
    if (o->ast_t == R_FACTOR_3) {
        dummy_factor_3(o);
        return;
    }
    if (o->ast_t == R_POWER) {
        dummy_power(o);
        return;
    }
}

void dummy_factor_1(FAstNode *n) {
    UNPACK_FACTOR_1(n)
    dummy_factor(factor);
}

void dummy_factor_2(FAstNode *n) {
    UNPACK_FACTOR_2(n)
    dummy_factor(factor);
}

void dummy_factor_3(FAstNode *n) {
    UNPACK_FACTOR_3(n)
    dummy_factor(factor);
}

// power:
//     | primary '**' factor
//     | primary
void dummy_power(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_POWER_1) {
        dummy_power_1(o);
        return;
    }
    if (o->ast_t == R_PRIMARY) {
        dummy_primary(o);
        return;
    }
}

void dummy_power_1(FAstNode *n) {
    UNPACK_POWER_1(n)
    dummy_primary(primary);
    dummy_factor(factor);
}

// primary (left_recursive):
//     | primary '.' NAME
//     | primary invocation
//     | primary subscript
//     | atom
void dummy_primary(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_PRIMARY_1) {
        dummy_primary_1(o);
        return;
    }
    if (o->ast_t == R_PRIMARY_2) {
        dummy_primary_2(o);
        return;
    }
    if (o->ast_t == R_PRIMARY_3) {
        dummy_primary_3(o);
        return;
    }
    if (o->ast_t == R_ATOM) {
        dummy_atom(o);
        return;
    }
}

void dummy_primary_1(FAstNode *n) {
    UNPACK_PRIMARY_1(n)
    dummy_primary(primary);
}

void dummy_primary_2(FAstNode *n) {
    UNPACK_PRIMARY_2(n)
    dummy_primary(primary);
    dummy_invocation(invocation);
}

void dummy_primary_3(FAstNode *n) {
    UNPACK_PRIMARY_3(n)
    dummy_primary(primary);
    dummy_subscript(subscript);
}

// tuple_atom:
//     | '(' [list_items] ')'
void dummy_tuple_atom(FAstNode *n) {
    UNPACK_TUPLE_ATOM(n)
    dummy_list_items(list_items);
}

// list_iterable:
//     | '[' list_iterator ']'
void dummy_list_iterable(FAstNode *n) {
    UNPACK_LIST_ITERABLE(n)
    dummy_list_iterator(list_iterator);
}

// list_atom:
//     | '[' [list_items] ']'
void dummy_list_atom(FAstNode *n) {
    UNPACK_LIST_ATOM(n)
    dummy_list_items(list_items);
}

// set_atom:
//     | '{' [set_items] '}'
void dummy_set_atom(FAstNode *n) {
    UNPACK_SET_ATOM(n)
    dummy_set_items(set_items);
}

// dict_iterable:
//     | '{' dict_iterator '}'
void dummy_dict_iterable(FAstNode *n) {
    UNPACK_DICT_ITERABLE(n)
    dummy_dict_iterator(dict_iterator);
}

// dict_atom:
//     | '{' [dict_items] '}'
void dummy_dict_atom(FAstNode *n) {
    UNPACK_DICT_ATOM(n)
    dummy_dict_items(dict_items);
}

// builder:
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
void dummy_builder(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_BUILDER_1) {
        dummy_builder_1(o);
        return;
    }
    if (o->ast_t == R_BUILDER_2) {
        dummy_builder_2(o);
        return;
    }
}

void dummy_builder_1(FAstNode *n) {
    UNPACK_BUILDER_1(n)
    dummy_simple_args(simple_args);
    dummy_expr(expr);
}

void dummy_builder_2(FAstNode *n) {
    UNPACK_BUILDER_2(n)
    dummy_builder_hint(builder_hint);
    dummy_builder_args(builder_args);
    dummy_block_suite(block_suite);
}

// atom:
//     | tuple_atom
//     | list_iterable
//     | list_atom
//     | set_atom
//     | dict_iterable
//     | dict_atom
//     | builder
//     | NAME
//     | NUMBER
//     | STRING
//     | 'None'
//     | 'True'
//     | 'False'
void dummy_atom(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_TUPLE_ATOM) {
        dummy_tuple_atom(o);
        return;
    }
    if (o->ast_t == R_LIST_ITERABLE) {
        dummy_list_iterable(o);
        return;
    }
    if (o->ast_t == R_LIST_ATOM) {
        dummy_list_atom(o);
        return;
    }
    if (o->ast_t == R_SET_ATOM) {
        dummy_set_atom(o);
        return;
    }
    if (o->ast_t == R_DICT_ITERABLE) {
        dummy_dict_iterable(o);
        return;
    }
    if (o->ast_t == R_DICT_ATOM) {
        dummy_dict_atom(o);
        return;
    }
    if (o->ast_t == R_BUILDER) {
        dummy_builder(o);
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_NAME) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_NUMBER) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_STRING) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_NONE) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_TRUE) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_FALSE) {
        return;
    }
}
