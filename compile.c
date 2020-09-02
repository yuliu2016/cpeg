#include "astgen.h"
#include "tokenmap.h"

void compile_single_input(FAstNode *n);
void compile_single_input_4(FAstNode *n);
void compile_file_input(FAstNode *n);
void compile_eval_input(FAstNode *n);
void compile_stmt_list(FAstNode *n);
void compile_stmt(FAstNode *n);
void compile_stmt_1(FAstNode *n);
void compile_simple_stmt(FAstNode *n);
void compile_small_stmt(FAstNode *n);
void compile_del_stmt(FAstNode *n);
void compile_return_stmt(FAstNode *n);
void compile_raise_stmt(FAstNode *n);
void compile_raise_stmt_3(FAstNode *n);
void compile_nonlocal_stmt(FAstNode *n);
void compile_assert_stmt(FAstNode *n);
void compile_assert_stmt_3(FAstNode *n);
void compile_name_list(FAstNode *n);
void compile_star_expr(FAstNode *n);
void compile_exprlist(FAstNode *n);
void compile_target(FAstNode *n);
void compile_target_1(FAstNode *n);
void compile_target_2(FAstNode *n);
void compile_target_4(FAstNode *n);
void compile_targetlist_sp(FAstNode *n);
void compile_t_primary(FAstNode *n);
void compile_t_primary_1(FAstNode *n);
void compile_t_primary_2(FAstNode *n);
void compile_t_primary_3(FAstNode *n);
void compile_t_primary_4(FAstNode *n);
void compile_t_lookahead(FAstNode *n);
void compile_targetlist(FAstNode *n);
void compile_expr_or_star(FAstNode *n);
void compile_exprlist_star(FAstNode *n);
void compile_subscript(FAstNode *n);
void compile_slicelist(FAstNode *n);
void compile_slice(FAstNode *n);
void compile_slice_1(FAstNode *n);
void compile_slice_expr(FAstNode *n);
void compile_dict_item(FAstNode *n);
void compile_dict_item_1(FAstNode *n);
void compile_dict_item_2(FAstNode *n);
void compile_dict_items(FAstNode *n);
void compile_list_item(FAstNode *n);
void compile_list_items(FAstNode *n);
void compile_set_items(FAstNode *n);
void compile_as_name(FAstNode *n);
void compile_iter_for(FAstNode *n);
void compile_iter_if(FAstNode *n);
void compile_iterator(FAstNode *n);
void compile_list_iterator(FAstNode *n);
void compile_dict_iterator(FAstNode *n);
void compile_assignment(FAstNode *n);
void compile_pubassign(FAstNode *n);
void compile_annassign(FAstNode *n);
void compile_annassign_4(FAstNode *n);
void compile_augassign(FAstNode *n);
void compile_simple_assign(FAstNode *n);
void compile_simple_assign_1(FAstNode *n);
void compile_augassign_op(FAstNode *n);
void compile_import_name(FAstNode *n);
void compile_import_from(FAstNode *n);
void compile_import_from_names(FAstNode *n);
void compile_import_from_names_2(FAstNode *n);
void compile_import_from_items(FAstNode *n);
void compile_import_as_names_sp(FAstNode *n);
void compile_import_as_name(FAstNode *n);
void compile_dotted_as_name(FAstNode *n);
void compile_import_as_names(FAstNode *n);
void compile_dotted_as_names(FAstNode *n);
void compile_dotted_name(FAstNode *n);
void compile_compound_stmt(FAstNode *n);
void compile_if_stmt(FAstNode *n);
void compile_elif_stmt(FAstNode *n);
void compile_while_stmt(FAstNode *n);
void compile_for_stmt(FAstNode *n);
void compile_try_stmt(FAstNode *n);
void compile_try_stmt_3(FAstNode *n);
void compile_with_stmt(FAstNode *n);
void compile_expr_as_name(FAstNode *n);
void compile_block_suite(FAstNode *n);
void compile_block_suite_1(FAstNode *n);
void compile_block_suite_2(FAstNode *n);
void compile_suite(FAstNode *n);
void compile_suite_1(FAstNode *n);
void compile_else_suite(FAstNode *n);
void compile_finally_suite(FAstNode *n);
void compile_except_clause(FAstNode *n);
void compile_except_suite(FAstNode *n);
void compile_invocation(FAstNode *n);
void compile_call_arg_list(FAstNode *n);
void compile_call_arg(FAstNode *n);
void compile_call_arg_1(FAstNode *n);
void compile_call_arg_2(FAstNode *n);
void compile_call_arg_3(FAstNode *n);
void compile_call_arg_4(FAstNode *n);
void compile_typed_arg_list(FAstNode *n);
void compile_full_arg_list(FAstNode *n);
void compile_full_arg_list_2(FAstNode *n);
void compile_full_arg_list_2_2(FAstNode *n);
void compile_args_kwargs(FAstNode *n);
void compile_args_kwargs_3(FAstNode *n);
void compile_args_kwargs_4(FAstNode *n);
void compile_kwargs(FAstNode *n);
void compile_default_arg(FAstNode *n);
void compile_default_arg_2(FAstNode *n);
void compile_typed_arg(FAstNode *n);
void compile_typed_arg_2(FAstNode *n);
void compile_simple_arg(FAstNode *n);
void compile_simple_arg_2(FAstNode *n);
void compile_simple_args(FAstNode *n);
void compile_builder_hint(FAstNode *n);
void compile_builder_args(FAstNode *n);
void compile_builder_args_2(FAstNode *n);
void compile_named_expr(FAstNode *n);
void compile_named_expr_1(FAstNode *n);
void compile_conditional(FAstNode *n);
void compile_expr(FAstNode *n);
void compile_disjunction(FAstNode *n);
void compile_disjunction_1(FAstNode *n);
void compile_conjunction(FAstNode *n);
void compile_conjunction_1(FAstNode *n);
void compile_inversion(FAstNode *n);
void compile_inversion_1(FAstNode *n);
void compile_comparison(FAstNode *n);
void compile_comparison_1(FAstNode *n);
void compile_comparison_1_2(FAstNode *n);
void compile_comp_op(FAstNode *n);
void compile_comp_op_8(FAstNode *n);
void compile_comp_op_10(FAstNode *n);
void compile_bitwise_or(FAstNode *n);
void compile_bitwise_or_1(FAstNode *n);
void compile_bitwise_xor(FAstNode *n);
void compile_bitwise_xor_1(FAstNode *n);
void compile_bitwise_and(FAstNode *n);
void compile_bitwise_and_1(FAstNode *n);
void compile_shift_expr(FAstNode *n);
void compile_shift_expr_1(FAstNode *n);
void compile_shift_expr_2(FAstNode *n);
void compile_sum(FAstNode *n);
void compile_sum_1(FAstNode *n);
void compile_sum_2(FAstNode *n);
void compile_term(FAstNode *n);
void compile_term_1(FAstNode *n);
void compile_term_2(FAstNode *n);
void compile_term_3(FAstNode *n);
void compile_term_4(FAstNode *n);
void compile_term_5(FAstNode *n);
void compile_pipe_expr(FAstNode *n);
void compile_pipe_expr_1(FAstNode *n);
void compile_factor(FAstNode *n);
void compile_factor_1(FAstNode *n);
void compile_factor_2(FAstNode *n);
void compile_factor_3(FAstNode *n);
void compile_power(FAstNode *n);
void compile_power_1(FAstNode *n);
void compile_primary(FAstNode *n);
void compile_primary_1(FAstNode *n);
void compile_primary_2(FAstNode *n);
void compile_primary_3(FAstNode *n);
void compile_tuple_atom(FAstNode *n);
void compile_list_iterable(FAstNode *n);
void compile_list_atom(FAstNode *n);
void compile_set_atom(FAstNode *n);
void compile_dict_iterable(FAstNode *n);
void compile_dict_atom(FAstNode *n);
void compile_builder(FAstNode *n);
void compile_builder_1(FAstNode *n);
void compile_builder_2(FAstNode *n);
void compile_atom(FAstNode *n);

// single_input:
//     | NEWLINE
//     | ENDMARKER
//     | simple_stmt
//     | compound_stmt NEWLINE
void compile_single_input(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == 0 && o->ast_v.token->type == T_NEWLINE) {
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_ENDMARKER) {
        return;
    }
    if (o->ast_t == R_SIMPLE_STMT) {
        compile_simple_stmt(o);
        return;
    }
    if (o->ast_t == R_SINGLE_INPUT_4) {
        compile_single_input_4(o);
        return;
    }
}

void compile_single_input_4(FAstNode *n) {
    UNPACK_SINGLE_INPUT_4(n)
    compile_compound_stmt(compound_stmt);
}

// file_input:
//     | [stmt_list] ENDMARKER
void compile_file_input(FAstNode *n) {
    UNPACK_FILE_INPUT(n)
    compile_stmt_list(stmt_list);
}

// eval_input:
//     | exprlist NEWLINE* ENDMARKER
void compile_eval_input(FAstNode *n) {
    UNPACK_EVAL_INPUT(n)
    compile_exprlist(exprlist);
}

// stmt_list:
//     | stmt+
void compile_stmt_list(FAstNode *n) {
    UNPACK_STMT_LIST(n)
    compile_stmt(stmts);
}

// stmt:
//     | (simple_stmt | compound_stmt) NEWLINE
void compile_stmt(FAstNode *n) {
    UNPACK_STMT(n)
    compile_stmt_1(simple_stmt_or_compound_stmt);
}

void compile_stmt_1(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_SIMPLE_STMT) {
        compile_simple_stmt(o);
        return;
    }
    if (o->ast_t == R_COMPOUND_STMT) {
        compile_compound_stmt(o);
        return;
    }
}

// simple_stmt:
//     | ';'.small_stmt+ [';']
void compile_simple_stmt(FAstNode *n) {
    UNPACK_SIMPLE_STMT(n)
    compile_small_stmt(small_stmts);
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
void compile_small_stmt(FAstNode *n) {
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
        compile_return_stmt(o);
        return;
    }
    if (o->ast_t == R_RAISE_STMT) {
        compile_raise_stmt(o);
        return;
    }
    if (o->ast_t == R_DEL_STMT) {
        compile_del_stmt(o);
        return;
    }
    if (o->ast_t == R_NONLOCAL_STMT) {
        compile_nonlocal_stmt(o);
        return;
    }
    if (o->ast_t == R_ASSERT_STMT) {
        compile_assert_stmt(o);
        return;
    }
    if (o->ast_t == R_IMPORT_NAME) {
        compile_import_name(o);
        return;
    }
    if (o->ast_t == R_IMPORT_FROM) {
        compile_import_from(o);
        return;
    }
    if (o->ast_t == R_ASSIGNMENT) {
        compile_assignment(o);
        return;
    }
}

// del_stmt:
//     | 'del' targetlist
void compile_del_stmt(FAstNode *n) {
    UNPACK_DEL_STMT(n)
    compile_targetlist(targetlist);
}

// return_stmt:
//     | 'return' [exprlist_star]
void compile_return_stmt(FAstNode *n) {
    UNPACK_RETURN_STMT(n)
    compile_exprlist_star(exprlist_star);
}

// raise_stmt:
//     | 'raise' expr ['from' expr]
void compile_raise_stmt(FAstNode *n) {
    UNPACK_RAISE_STMT(n)
    compile_expr(expr);
    compile_raise_stmt_3(from_expr);
}

void compile_raise_stmt_3(FAstNode *n) {
    UNPACK_RAISE_STMT_3(n)
    compile_expr(expr);
}

// nonlocal_stmt:
//     | 'nonlocal' name_list
void compile_nonlocal_stmt(FAstNode *n) {
    UNPACK_NONLOCAL_STMT(n)
    compile_name_list(name_list);
}

// assert_stmt:
//     | 'assert' expr [',' expr]
void compile_assert_stmt(FAstNode *n) {
    UNPACK_ASSERT_STMT(n)
    compile_expr(expr);
    compile_assert_stmt_3(op_comma_expr);
}

void compile_assert_stmt_3(FAstNode *n) {
    UNPACK_ASSERT_STMT_3(n)
    compile_expr(expr);
}

// name_list:
//     | ','.NAME+
void compile_name_list(FAstNode *n) {
    UNPACK_NAME_LIST(n)
}

// star_expr:
//     | '*' bitwise_or
void compile_star_expr(FAstNode *n) {
    UNPACK_STAR_EXPR(n)
    compile_bitwise_or(bitwise_or);
}

// exprlist:
//     | ','.expr+ [',']
void compile_exprlist(FAstNode *n) {
    UNPACK_EXPRLIST(n)
    compile_expr(exprs);
}

// target:
//     | t_primary '.' NAME !t_lookahead
//     | t_primary subscript !t_lookahead
//     | NAME
//     | '(' targetlist_sp ')'
void compile_target(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_TARGET_1) {
        compile_target_1(o);
        return;
    }
    if (o->ast_t == R_TARGET_2) {
        compile_target_2(o);
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_NAME) {
        return;
    }
    if (o->ast_t == R_TARGET_4) {
        compile_target_4(o);
        return;
    }
}

void compile_target_1(FAstNode *n) {
    UNPACK_TARGET_1(n)
    compile_t_primary(t_primary);
}

void compile_target_2(FAstNode *n) {
    UNPACK_TARGET_2(n)
    compile_t_primary(t_primary);
    compile_subscript(subscript);
}

void compile_target_4(FAstNode *n) {
    UNPACK_TARGET_4(n)
    compile_targetlist_sp(targetlist_sp);
}

// targetlist_sp (allow_whitespace=true):
//     | targetlist
void compile_targetlist_sp(FAstNode *n) {
    UNPACK_TARGETLIST_SP(n)
    compile_targetlist(targetlist);
}

// t_primary (left_recursive):
//     | t_primary '.' NAME &t_lookahead
//     | t_primary invocation &t_lookahead
//     | t_primary subscript &t_lookahead
//     | atom &t_lookahead
void compile_t_primary(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_T_PRIMARY_1) {
        compile_t_primary_1(o);
        return;
    }
    if (o->ast_t == R_T_PRIMARY_2) {
        compile_t_primary_2(o);
        return;
    }
    if (o->ast_t == R_T_PRIMARY_3) {
        compile_t_primary_3(o);
        return;
    }
    if (o->ast_t == R_T_PRIMARY_4) {
        compile_t_primary_4(o);
        return;
    }
}

void compile_t_primary_1(FAstNode *n) {
    UNPACK_T_PRIMARY_1(n)
    compile_t_primary(t_primary);
}

void compile_t_primary_2(FAstNode *n) {
    UNPACK_T_PRIMARY_2(n)
    compile_t_primary(t_primary);
    compile_invocation(invocation);
}

void compile_t_primary_3(FAstNode *n) {
    UNPACK_T_PRIMARY_3(n)
    compile_t_primary(t_primary);
    compile_subscript(subscript);
}

void compile_t_primary_4(FAstNode *n) {
    UNPACK_T_PRIMARY_4(n)
    compile_atom(atom);
}

// t_lookahead:
//     | '.'
//     | '('
//     | '['
void compile_t_lookahead(FAstNode *n) {
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
void compile_targetlist(FAstNode *n) {
    UNPACK_TARGETLIST(n)
    compile_target(targets);
}

// expr_or_star:
//     | star_expr
//     | expr
void compile_expr_or_star(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_STAR_EXPR) {
        compile_star_expr(o);
        return;
    }
    if (o->ast_t == R_EXPR) {
        compile_expr(o);
        return;
    }
}

// exprlist_star:
//     | ','.expr_or_star+ [',']
void compile_exprlist_star(FAstNode *n) {
    UNPACK_EXPRLIST_STAR(n)
    compile_expr_or_star(expr_or_stars);
}

// subscript:
//     | '[' slicelist ']'
void compile_subscript(FAstNode *n) {
    UNPACK_SUBSCRIPT(n)
    compile_slicelist(slicelist);
}

// slicelist:
//     | ','.slice+ [',']
void compile_slicelist(FAstNode *n) {
    UNPACK_SLICELIST(n)
    compile_slice(slices);
}

// slice:
//     | [expr] slice_expr [slice_expr]
//     | expr
void compile_slice(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_SLICE_1) {
        compile_slice_1(o);
        return;
    }
    if (o->ast_t == R_EXPR) {
        compile_expr(o);
        return;
    }
}

void compile_slice_1(FAstNode *n) {
    UNPACK_SLICE_1(n)
    compile_expr(expr);
    compile_slice_expr(slice_expr);
    compile_slice_expr(slice_expr_1);
}

// slice_expr:
//     | ':' [expr]
void compile_slice_expr(FAstNode *n) {
    UNPACK_SLICE_EXPR(n)
    compile_expr(expr);
}

// dict_item:
//     | expr ':' expr
//     | '**' bitwise_or
void compile_dict_item(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_DICT_ITEM_1) {
        compile_dict_item_1(o);
        return;
    }
    if (o->ast_t == R_DICT_ITEM_2) {
        compile_dict_item_2(o);
        return;
    }
}

void compile_dict_item_1(FAstNode *n) {
    UNPACK_DICT_ITEM_1(n)
    compile_expr(expr);
    compile_expr(expr_1);
}

void compile_dict_item_2(FAstNode *n) {
    UNPACK_DICT_ITEM_2(n)
    compile_bitwise_or(bitwise_or);
}

// dict_items (allow_whitespace=true):
//     | ','.dict_item+ [',']
void compile_dict_items(FAstNode *n) {
    UNPACK_DICT_ITEMS(n)
    compile_dict_item(dict_items);
}

// list_item:
//     | star_expr
//     | named_expr
void compile_list_item(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_STAR_EXPR) {
        compile_star_expr(o);
        return;
    }
    if (o->ast_t == R_NAMED_EXPR) {
        compile_named_expr(o);
        return;
    }
}

// list_items (allow_whitespace=true):
//     | ','.list_item+ [',']
void compile_list_items(FAstNode *n) {
    UNPACK_LIST_ITEMS(n)
    compile_list_item(list_items);
}

// set_items (allow_whitespace=true):
//     | exprlist_star
void compile_set_items(FAstNode *n) {
    UNPACK_SET_ITEMS(n)
    compile_exprlist_star(exprlist_star);
}

// as_name:
//     | 'as' NAME
void compile_as_name(FAstNode *n) {
    UNPACK_AS_NAME(n)
}

// iter_for:
//     | 'for' targetlist 'in' disjunction [iter_if]
void compile_iter_for(FAstNode *n) {
    UNPACK_ITER_FOR(n)
    compile_targetlist(targetlist);
    compile_disjunction(disjunction);
    compile_iter_if(iter_if);
}

// iter_if:
//     | 'if' named_expr
void compile_iter_if(FAstNode *n) {
    UNPACK_ITER_IF(n)
    compile_named_expr(named_expr);
}

// iterator:
//     | iter_for* 'for' targetlist [iter_if]
void compile_iterator(FAstNode *n) {
    UNPACK_ITERATOR(n)
    compile_iter_for(iter_fors);
    compile_targetlist(targetlist);
    compile_iter_if(iter_if);
}

// list_iterator (allow_whitespace=true):
//     | expr_or_star iterator
void compile_list_iterator(FAstNode *n) {
    UNPACK_LIST_ITERATOR(n)
    compile_expr_or_star(expr_or_star);
    compile_iterator(iterator);
}

// dict_iterator (allow_whitespace=true):
//     | dict_item iterator
void compile_dict_iterator(FAstNode *n) {
    UNPACK_DICT_ITERATOR(n)
    compile_dict_item(dict_item);
    compile_iterator(iterator);
}

// assignment:
//     | pubassign
//     | annassign
//     | augassign
//     | simple_assign
void compile_assignment(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_PUBASSIGN) {
        compile_pubassign(o);
        return;
    }
    if (o->ast_t == R_ANNASSIGN) {
        compile_annassign(o);
        return;
    }
    if (o->ast_t == R_AUGASSIGN) {
        compile_augassign(o);
        return;
    }
    if (o->ast_t == R_SIMPLE_ASSIGN) {
        compile_simple_assign(o);
        return;
    }
}

// pubassign:
//     | '/' NAME '=' exprlist
void compile_pubassign(FAstNode *n) {
    UNPACK_PUBASSIGN(n)
    compile_exprlist(exprlist);
}

// annassign:
//     | target ':' expr ['=' exprlist]
void compile_annassign(FAstNode *n) {
    UNPACK_ANNASSIGN(n)
    compile_target(target);
    compile_expr(expr);
    compile_annassign_4(op_assign_exprlist);
}

void compile_annassign_4(FAstNode *n) {
    UNPACK_ANNASSIGN_4(n)
    compile_exprlist(exprlist);
}

// augassign:
//     | target augassign_op exprlist
void compile_augassign(FAstNode *n) {
    UNPACK_AUGASSIGN(n)
    compile_target(target);
    compile_augassign_op(augassign_op);
    compile_exprlist(exprlist);
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
void compile_simple_assign(FAstNode *n) {
    UNPACK_SIMPLE_ASSIGN(n)
    compile_simple_assign_1(targetlist_op_assigns);
    compile_exprlist_star(exprlist_star);
}

void compile_simple_assign_1(FAstNode *n) {
    UNPACK_SIMPLE_ASSIGN_1(n)
    compile_targetlist(targetlist);
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
void compile_augassign_op(FAstNode *n) {
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
void compile_import_name(FAstNode *n) {
    UNPACK_IMPORT_NAME(n)
    compile_dotted_as_names(dotted_as_names);
}

// import_from:
//     | 'from' import_from_names 'import' import_from_items
void compile_import_from(FAstNode *n) {
    UNPACK_IMPORT_FROM(n)
    compile_import_from_names(import_from_names);
    compile_import_from_items(import_from_items);
}

// import_from_names:
//     | dotted_name
//     | '.'+ [dotted_name]
void compile_import_from_names(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_DOTTED_NAME) {
        compile_dotted_name(o);
        return;
    }
    if (o->ast_t == R_IMPORT_FROM_NAMES_2) {
        compile_import_from_names_2(o);
        return;
    }
}

void compile_import_from_names_2(FAstNode *n) {
    UNPACK_IMPORT_FROM_NAMES_2(n)
    compile_dotted_name(dotted_name);
}

// import_from_items:
//     | '*'
//     | import_as_names_sp
//     | import_as_names
void compile_import_from_items(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == 0 && o->ast_v.token->type == T_OP_TIMES) {
        return;
    }
    if (o->ast_t == R_IMPORT_AS_NAMES_SP) {
        compile_import_as_names_sp(o);
        return;
    }
    if (o->ast_t == R_IMPORT_AS_NAMES) {
        compile_import_as_names(o);
        return;
    }
}

// import_as_names_sp (allow_whitespace=true):
//     | '(' import_as_names [','] ')'
void compile_import_as_names_sp(FAstNode *n) {
    UNPACK_IMPORT_AS_NAMES_SP(n)
    compile_import_as_names(import_as_names);
}

// import_as_name:
//     | NAME [as_name]
void compile_import_as_name(FAstNode *n) {
    UNPACK_IMPORT_AS_NAME(n)
    compile_as_name(as_name);
}

// dotted_as_name:
//     | dotted_name [as_name]
void compile_dotted_as_name(FAstNode *n) {
    UNPACK_DOTTED_AS_NAME(n)
    compile_dotted_name(dotted_name);
    compile_as_name(as_name);
}

// import_as_names:
//     | ','.import_as_name+
void compile_import_as_names(FAstNode *n) {
    UNPACK_IMPORT_AS_NAMES(n)
    compile_import_as_name(import_as_names);
}

// dotted_as_names:
//     | ','.dotted_as_name+
void compile_dotted_as_names(FAstNode *n) {
    UNPACK_DOTTED_AS_NAMES(n)
    compile_dotted_as_name(dotted_as_names);
}

// dotted_name:
//     | '.'.NAME+
void compile_dotted_name(FAstNode *n) {
    UNPACK_DOTTED_NAME(n)
}

// compound_stmt:
//     | if_stmt
//     | while_stmt
//     | for_stmt
//     | try_stmt
//     | with_stmt
void compile_compound_stmt(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_IF_STMT) {
        compile_if_stmt(o);
        return;
    }
    if (o->ast_t == R_WHILE_STMT) {
        compile_while_stmt(o);
        return;
    }
    if (o->ast_t == R_FOR_STMT) {
        compile_for_stmt(o);
        return;
    }
    if (o->ast_t == R_TRY_STMT) {
        compile_try_stmt(o);
        return;
    }
    if (o->ast_t == R_WITH_STMT) {
        compile_with_stmt(o);
        return;
    }
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
void compile_if_stmt(FAstNode *n) {
    UNPACK_IF_STMT(n)
    compile_named_expr(named_expr);
    compile_suite(suite);
    compile_elif_stmt(elif_stmts);
    compile_else_suite(else_suite);
}

// elif_stmt:
//     | 'elif' named_expr suite
void compile_elif_stmt(FAstNode *n) {
    UNPACK_ELIF_STMT(n)
    compile_named_expr(named_expr);
    compile_suite(suite);
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
void compile_while_stmt(FAstNode *n) {
    UNPACK_WHILE_STMT(n)
    compile_named_expr(named_expr);
    compile_suite(suite);
    compile_else_suite(else_suite);
}

// for_stmt:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
void compile_for_stmt(FAstNode *n) {
    UNPACK_FOR_STMT(n)
    compile_targetlist(targetlist);
    compile_exprlist(exprlist);
    compile_suite(suite);
    compile_else_suite(else_suite);
}

// try_stmt:
//     | 'try' suite (except_suite | finally_suite)
void compile_try_stmt(FAstNode *n) {
    UNPACK_TRY_STMT(n)
    compile_suite(suite);
    compile_try_stmt_3(except_suite_or_finally_suite);
}

void compile_try_stmt_3(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_EXCEPT_SUITE) {
        compile_except_suite(o);
        return;
    }
    if (o->ast_t == R_FINALLY_SUITE) {
        compile_finally_suite(o);
        return;
    }
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
void compile_with_stmt(FAstNode *n) {
    UNPACK_WITH_STMT(n)
    compile_expr_as_name(expr_as_names);
    compile_suite(suite);
}

// expr_as_name:
//     | expr [as_name]
void compile_expr_as_name(FAstNode *n) {
    UNPACK_EXPR_AS_NAME(n)
    compile_expr(expr);
    compile_as_name(as_name);
}

// block_suite (allow_whitespace=false):
//     | '{' NEWLINE stmt_list '}'
//     | '{' [simple_stmt] '}'
void compile_block_suite(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_BLOCK_SUITE_1) {
        compile_block_suite_1(o);
        return;
    }
    if (o->ast_t == R_BLOCK_SUITE_2) {
        compile_block_suite_2(o);
        return;
    }
}

void compile_block_suite_1(FAstNode *n) {
    UNPACK_BLOCK_SUITE_1(n)
    compile_stmt_list(stmt_list);
}

void compile_block_suite_2(FAstNode *n) {
    UNPACK_BLOCK_SUITE_2(n)
    compile_simple_stmt(simple_stmt);
}

// suite:
//     | ':' simple_stmt
//     | block_suite
void compile_suite(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_SUITE_1) {
        compile_suite_1(o);
        return;
    }
    if (o->ast_t == R_BLOCK_SUITE) {
        compile_block_suite(o);
        return;
    }
}

void compile_suite_1(FAstNode *n) {
    UNPACK_SUITE_1(n)
    compile_simple_stmt(simple_stmt);
}

// else_suite:
//     | 'else' suite
void compile_else_suite(FAstNode *n) {
    UNPACK_ELSE_SUITE(n)
    compile_suite(suite);
}

// finally_suite:
//     | 'finally' suite
void compile_finally_suite(FAstNode *n) {
    UNPACK_FINALLY_SUITE(n)
    compile_suite(suite);
}

// except_clause:
//     | 'except' [expr_as_name] suite
void compile_except_clause(FAstNode *n) {
    UNPACK_EXCEPT_CLAUSE(n)
    compile_expr_as_name(expr_as_name);
    compile_suite(suite);
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
void compile_except_suite(FAstNode *n) {
    UNPACK_EXCEPT_SUITE(n)
    compile_except_clause(except_clauses);
    compile_else_suite(else_suite);
    compile_finally_suite(finally_suite);
}

// invocation:
//     | '(' [call_arg_list] ')'
void compile_invocation(FAstNode *n) {
    UNPACK_INVOCATION(n)
    compile_call_arg_list(call_arg_list);
}

// call_arg_list (allow_whitespace=true):
//     | ','.call_arg+ [',']
void compile_call_arg_list(FAstNode *n) {
    UNPACK_CALL_ARG_LIST(n)
    compile_call_arg(call_args);
}

// call_arg:
//     | NAME ':=' expr
//     | NAME '=' expr
//     | '**' expr
//     | '*' expr
//     | expr
void compile_call_arg(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_CALL_ARG_1) {
        compile_call_arg_1(o);
        return;
    }
    if (o->ast_t == R_CALL_ARG_2) {
        compile_call_arg_2(o);
        return;
    }
    if (o->ast_t == R_CALL_ARG_3) {
        compile_call_arg_3(o);
        return;
    }
    if (o->ast_t == R_CALL_ARG_4) {
        compile_call_arg_4(o);
        return;
    }
    if (o->ast_t == R_EXPR) {
        compile_expr(o);
        return;
    }
}

void compile_call_arg_1(FAstNode *n) {
    UNPACK_CALL_ARG_1(n)
    compile_expr(expr);
}

void compile_call_arg_2(FAstNode *n) {
    UNPACK_CALL_ARG_2(n)
    compile_expr(expr);
}

void compile_call_arg_3(FAstNode *n) {
    UNPACK_CALL_ARG_3(n)
    compile_expr(expr);
}

void compile_call_arg_4(FAstNode *n) {
    UNPACK_CALL_ARG_4(n)
    compile_expr(expr);
}

// typed_arg_list (allow_whitespace=true):
//     | kwargs
//     | args_kwargs
//     | full_arg_list
void compile_typed_arg_list(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_KWARGS) {
        compile_kwargs(o);
        return;
    }
    if (o->ast_t == R_ARGS_KWARGS) {
        compile_args_kwargs(o);
        return;
    }
    if (o->ast_t == R_FULL_ARG_LIST) {
        compile_full_arg_list(o);
        return;
    }
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
void compile_full_arg_list(FAstNode *n) {
    UNPACK_FULL_ARG_LIST(n)
    compile_default_arg(default_args);
    compile_full_arg_list_2(full_arg_list);
}

void compile_full_arg_list_2(FAstNode *n) {
    UNPACK_FULL_ARG_LIST_2(n)
    compile_full_arg_list_2_2(kwargs_or_args_kwargs);
}

void compile_full_arg_list_2_2(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_KWARGS) {
        compile_kwargs(o);
        return;
    }
    if (o->ast_t == R_ARGS_KWARGS) {
        compile_args_kwargs(o);
        return;
    }
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
void compile_args_kwargs(FAstNode *n) {
    UNPACK_ARGS_KWARGS(n)
    compile_typed_arg(typed_arg);
    compile_args_kwargs_3(op_comma_default_args);
    compile_args_kwargs_4(args_kwargs);
}

void compile_args_kwargs_3(FAstNode *n) {
    UNPACK_ARGS_KWARGS_3(n)
    compile_default_arg(default_arg);
}

void compile_args_kwargs_4(FAstNode *n) {
    UNPACK_ARGS_KWARGS_4(n)
    compile_kwargs(kwargs);
}

// kwargs:
//     | '**' typed_arg [',']
void compile_kwargs(FAstNode *n) {
    UNPACK_KWARGS(n)
    compile_typed_arg(typed_arg);
}

// default_arg:
//     | typed_arg ['=' expr]
void compile_default_arg(FAstNode *n) {
    UNPACK_DEFAULT_ARG(n)
    compile_typed_arg(typed_arg);
    compile_default_arg_2(op_assign_expr);
}

void compile_default_arg_2(FAstNode *n) {
    UNPACK_DEFAULT_ARG_2(n)
    compile_expr(expr);
}

// typed_arg:
//     | NAME [':' expr]
void compile_typed_arg(FAstNode *n) {
    UNPACK_TYPED_ARG(n)
    compile_typed_arg_2(op_colon_expr);
}

void compile_typed_arg_2(FAstNode *n) {
    UNPACK_TYPED_ARG_2(n)
    compile_expr(expr);
}

// simple_arg:
//     | NAME ['=' expr]
void compile_simple_arg(FAstNode *n) {
    UNPACK_SIMPLE_ARG(n)
    compile_simple_arg_2(op_assign_expr);
}

void compile_simple_arg_2(FAstNode *n) {
    UNPACK_SIMPLE_ARG_2(n)
    compile_expr(expr);
}

// simple_args:
//     | ','.simple_arg+
void compile_simple_args(FAstNode *n) {
    UNPACK_SIMPLE_ARGS(n)
    compile_simple_arg(simple_args);
}

// builder_hint:
//     | '<' name_list '>'
void compile_builder_hint(FAstNode *n) {
    UNPACK_BUILDER_HINT(n)
    compile_name_list(name_list);
}

// builder_args:
//     | simple_args
//     | '(' [typed_arg_list] ')'
void compile_builder_args(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_SIMPLE_ARGS) {
        compile_simple_args(o);
        return;
    }
    if (o->ast_t == R_BUILDER_ARGS_2) {
        compile_builder_args_2(o);
        return;
    }
}

void compile_builder_args_2(FAstNode *n) {
    UNPACK_BUILDER_ARGS_2(n)
    compile_typed_arg_list(typed_arg_list);
}

// named_expr:
//     | NAME ':=' expr
//     | expr
void compile_named_expr(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_NAMED_EXPR_1) {
        compile_named_expr_1(o);
        return;
    }
    if (o->ast_t == R_EXPR) {
        compile_expr(o);
        return;
    }
}

void compile_named_expr_1(FAstNode *n) {
    UNPACK_NAMED_EXPR_1(n)
    compile_expr(expr);
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
void compile_conditional(FAstNode *n) {
    UNPACK_CONDITIONAL(n)
    compile_disjunction(disjunction);
    compile_disjunction(disjunction_1);
    compile_expr(expr);
}

// expr:
//     | conditional
//     | disjunction
void compile_expr(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_CONDITIONAL) {
        compile_conditional(o);
        return;
    }
    if (o->ast_t == R_DISJUNCTION) {
        compile_disjunction(o);
        return;
    }
}

// disjunction (left_recursive):
//     | disjunction 'or' conjunction
//     | conjunction
void compile_disjunction(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_DISJUNCTION_1) {
        compile_disjunction_1(o);
        return;
    }
    if (o->ast_t == R_CONJUNCTION) {
        compile_conjunction(o);
        return;
    }
}

void compile_disjunction_1(FAstNode *n) {
    UNPACK_DISJUNCTION_1(n)
    compile_disjunction(disjunction);
    compile_conjunction(conjunction);
}

// conjunction (left_recursive):
//     | conjunction 'and' inversion
//     | inversion
void compile_conjunction(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_CONJUNCTION_1) {
        compile_conjunction_1(o);
        return;
    }
    if (o->ast_t == R_INVERSION) {
        compile_inversion(o);
        return;
    }
}

void compile_conjunction_1(FAstNode *n) {
    UNPACK_CONJUNCTION_1(n)
    compile_conjunction(conjunction);
    compile_inversion(inversion);
}

// inversion:
//     | 'not' inversion
//     | comparison
void compile_inversion(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_INVERSION_1) {
        compile_inversion_1(o);
        return;
    }
    if (o->ast_t == R_COMPARISON) {
        compile_comparison(o);
        return;
    }
}

void compile_inversion_1(FAstNode *n) {
    UNPACK_INVERSION_1(n)
    compile_inversion(inversion);
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
void compile_comparison(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_COMPARISON_1) {
        compile_comparison_1(o);
        return;
    }
    if (o->ast_t == R_BITWISE_OR) {
        compile_bitwise_or(o);
        return;
    }
}

void compile_comparison_1(FAstNode *n) {
    UNPACK_COMPARISON_1(n)
    compile_bitwise_or(bitwise_or);
    compile_comparison_1_2(comp_op_bitwise_ors);
}

void compile_comparison_1_2(FAstNode *n) {
    UNPACK_COMPARISON_1_2(n)
    compile_comp_op(comp_op);
    compile_bitwise_or(bitwise_or);
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
void compile_comp_op(FAstNode *n) {
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
        compile_comp_op_8(o);
        return;
    }
    if (o->ast_t == 0 && o->ast_v.token->type == T_IS) {
        return;
    }
    if (o->ast_t == R_COMP_OP_10) {
        compile_comp_op_10(o);
        return;
    }
}

void compile_comp_op_8(FAstNode *n) {
}

void compile_comp_op_10(FAstNode *n) {
}

// bitwise_or (left_recursive):
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
void compile_bitwise_or(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_BITWISE_OR_1) {
        compile_bitwise_or_1(o);
        return;
    }
    if (o->ast_t == R_BITWISE_XOR) {
        compile_bitwise_xor(o);
        return;
    }
}

void compile_bitwise_or_1(FAstNode *n) {
    UNPACK_BITWISE_OR_1(n)
    compile_bitwise_or(bitwise_or);
    compile_bitwise_xor(bitwise_xor);
}

// bitwise_xor (left_recursive):
//     | bitwise_xor '^' bitwise_and
//     | bitwise_and
void compile_bitwise_xor(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_BITWISE_XOR_1) {
        compile_bitwise_xor_1(o);
        return;
    }
    if (o->ast_t == R_BITWISE_AND) {
        compile_bitwise_and(o);
        return;
    }
}

void compile_bitwise_xor_1(FAstNode *n) {
    UNPACK_BITWISE_XOR_1(n)
    compile_bitwise_xor(bitwise_xor);
    compile_bitwise_and(bitwise_and);
}

// bitwise_and (left_recursive):
//     | bitwise_and '&' shift_expr
//     | shift_expr
void compile_bitwise_and(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_BITWISE_AND_1) {
        compile_bitwise_and_1(o);
        return;
    }
    if (o->ast_t == R_SHIFT_EXPR) {
        compile_shift_expr(o);
        return;
    }
}

void compile_bitwise_and_1(FAstNode *n) {
    UNPACK_BITWISE_AND_1(n)
    compile_bitwise_and(bitwise_and);
    compile_shift_expr(shift_expr);
}

// shift_expr (left_recursive):
//     | shift_expr '<<' sum
//     | shift_expr '>>' sum
//     | sum
void compile_shift_expr(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_SHIFT_EXPR_1) {
        compile_shift_expr_1(o);
        return;
    }
    if (o->ast_t == R_SHIFT_EXPR_2) {
        compile_shift_expr_2(o);
        return;
    }
    if (o->ast_t == R_SUM) {
        compile_sum(o);
        return;
    }
}

void compile_shift_expr_1(FAstNode *n) {
    UNPACK_SHIFT_EXPR_1(n)
    compile_shift_expr(shift_expr);
    compile_sum(sum);
}

void compile_shift_expr_2(FAstNode *n) {
    UNPACK_SHIFT_EXPR_2(n)
    compile_shift_expr(shift_expr);
    compile_sum(sum);
}

// sum (left_recursive):
//     | sum '+' term
//     | sum '-' term
//     | term
void compile_sum(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_SUM_1) {
        compile_sum_1(o);
        return;
    }
    if (o->ast_t == R_SUM_2) {
        compile_sum_2(o);
        return;
    }
    if (o->ast_t == R_TERM) {
        compile_term(o);
        return;
    }
}

void compile_sum_1(FAstNode *n) {
    UNPACK_SUM_1(n)
    compile_sum(sum);
    compile_term(term);
}

void compile_sum_2(FAstNode *n) {
    UNPACK_SUM_2(n)
    compile_sum(sum);
    compile_term(term);
}

// term (left_recursive):
//     | term '*' pipe_expr
//     | term '/' pipe_expr
//     | term '%' pipe_expr
//     | term '//' pipe_expr
//     | term '@' pipe_expr
//     | pipe_expr
void compile_term(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_TERM_1) {
        compile_term_1(o);
        return;
    }
    if (o->ast_t == R_TERM_2) {
        compile_term_2(o);
        return;
    }
    if (o->ast_t == R_TERM_3) {
        compile_term_3(o);
        return;
    }
    if (o->ast_t == R_TERM_4) {
        compile_term_4(o);
        return;
    }
    if (o->ast_t == R_TERM_5) {
        compile_term_5(o);
        return;
    }
    if (o->ast_t == R_PIPE_EXPR) {
        compile_pipe_expr(o);
        return;
    }
}

void compile_term_1(FAstNode *n) {
    UNPACK_TERM_1(n)
    compile_term(term);
    compile_pipe_expr(pipe_expr);
}

void compile_term_2(FAstNode *n) {
    UNPACK_TERM_2(n)
    compile_term(term);
    compile_pipe_expr(pipe_expr);
}

void compile_term_3(FAstNode *n) {
    UNPACK_TERM_3(n)
    compile_term(term);
    compile_pipe_expr(pipe_expr);
}

void compile_term_4(FAstNode *n) {
    UNPACK_TERM_4(n)
    compile_term(term);
    compile_pipe_expr(pipe_expr);
}

void compile_term_5(FAstNode *n) {
    UNPACK_TERM_5(n)
    compile_term(term);
    compile_pipe_expr(pipe_expr);
}

// pipe_expr (left_recursive):
//     | pipe_expr '->' factor
//     | factor
void compile_pipe_expr(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_PIPE_EXPR_1) {
        compile_pipe_expr_1(o);
        return;
    }
    if (o->ast_t == R_FACTOR) {
        compile_factor(o);
        return;
    }
}

void compile_pipe_expr_1(FAstNode *n) {
    UNPACK_PIPE_EXPR_1(n)
    compile_pipe_expr(pipe_expr);
    compile_factor(factor);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
void compile_factor(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_FACTOR_1) {
        compile_factor_1(o);
        return;
    }
    if (o->ast_t == R_FACTOR_2) {
        compile_factor_2(o);
        return;
    }
    if (o->ast_t == R_FACTOR_3) {
        compile_factor_3(o);
        return;
    }
    if (o->ast_t == R_POWER) {
        compile_power(o);
        return;
    }
}

void compile_factor_1(FAstNode *n) {
    UNPACK_FACTOR_1(n)
    compile_factor(factor);
}

void compile_factor_2(FAstNode *n) {
    UNPACK_FACTOR_2(n)
    compile_factor(factor);
}

void compile_factor_3(FAstNode *n) {
    UNPACK_FACTOR_3(n)
    compile_factor(factor);
}

// power:
//     | primary '**' factor
//     | primary
void compile_power(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_POWER_1) {
        compile_power_1(o);
        return;
    }
    if (o->ast_t == R_PRIMARY) {
        compile_primary(o);
        return;
    }
}

void compile_power_1(FAstNode *n) {
    UNPACK_POWER_1(n)
    compile_primary(primary);
    compile_factor(factor);
}

// primary (left_recursive):
//     | primary '.' NAME
//     | primary invocation
//     | primary subscript
//     | atom
void compile_primary(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_PRIMARY_1) {
        compile_primary_1(o);
        return;
    }
    if (o->ast_t == R_PRIMARY_2) {
        compile_primary_2(o);
        return;
    }
    if (o->ast_t == R_PRIMARY_3) {
        compile_primary_3(o);
        return;
    }
    if (o->ast_t == R_ATOM) {
        compile_atom(o);
        return;
    }
}

void compile_primary_1(FAstNode *n) {
    UNPACK_PRIMARY_1(n)
    compile_primary(primary);
}

void compile_primary_2(FAstNode *n) {
    UNPACK_PRIMARY_2(n)
    compile_primary(primary);
    compile_invocation(invocation);
}

void compile_primary_3(FAstNode *n) {
    UNPACK_PRIMARY_3(n)
    compile_primary(primary);
    compile_subscript(subscript);
}

// tuple_atom:
//     | '(' [list_items] ')'
void compile_tuple_atom(FAstNode *n) {
    UNPACK_TUPLE_ATOM(n)
    compile_list_items(list_items);
}

// list_iterable:
//     | '[' list_iterator ']'
void compile_list_iterable(FAstNode *n) {
    UNPACK_LIST_ITERABLE(n)
    compile_list_iterator(list_iterator);
}

// list_atom:
//     | '[' [list_items] ']'
void compile_list_atom(FAstNode *n) {
    UNPACK_LIST_ATOM(n)
    compile_list_items(list_items);
}

// set_atom:
//     | '{' [set_items] '}'
void compile_set_atom(FAstNode *n) {
    UNPACK_SET_ATOM(n)
    compile_set_items(set_items);
}

// dict_iterable:
//     | '{' dict_iterator '}'
void compile_dict_iterable(FAstNode *n) {
    UNPACK_DICT_ITERABLE(n)
    compile_dict_iterator(dict_iterator);
}

// dict_atom:
//     | '{' [dict_items] '}'
void compile_dict_atom(FAstNode *n) {
    UNPACK_DICT_ATOM(n)
    compile_dict_items(dict_items);
}

// builder:
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
void compile_builder(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_BUILDER_1) {
        compile_builder_1(o);
        return;
    }
    if (o->ast_t == R_BUILDER_2) {
        compile_builder_2(o);
        return;
    }
}

void compile_builder_1(FAstNode *n) {
    UNPACK_BUILDER_1(n)
    compile_simple_args(simple_args);
    compile_expr(expr);
}

void compile_builder_2(FAstNode *n) {
    UNPACK_BUILDER_2(n)
    compile_builder_hint(builder_hint);
    compile_builder_args(builder_args);
    compile_block_suite(block_suite);
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
void compile_atom(FAstNode *n) {
    FAstNode *o = n->ast_v.fields[0];
    if (o->ast_t == R_TUPLE_ATOM) {
        compile_tuple_atom(o);
        return;
    }
    if (o->ast_t == R_LIST_ITERABLE) {
        compile_list_iterable(o);
        return;
    }
    if (o->ast_t == R_LIST_ATOM) {
        compile_list_atom(o);
        return;
    }
    if (o->ast_t == R_SET_ATOM) {
        compile_set_atom(o);
        return;
    }
    if (o->ast_t == R_DICT_ITERABLE) {
        compile_dict_iterable(o);
        return;
    }
    if (o->ast_t == R_DICT_ATOM) {
        compile_dict_atom(o);
        return;
    }
    if (o->ast_t == R_BUILDER) {
        compile_builder(o);
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
