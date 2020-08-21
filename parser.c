#include <peg_macros.h>

RULE(single_input);
RULE(single_input_3);
RULE(file_input);
RULE(file_input_1_loop);
RULE(file_input_1);
RULE(eval_input);
RULE(eval_input_loop);
RULE(stmt);
RULE(stmt_1);
RULE(simple_stmt);
RULE(small_stmt_loop);
RULE(small_stmt);
RULE(del_stmt);
RULE(return_stmt);
RULE(raise_stmt);
RULE(raise_stmt_3);
RULE(nonlocal_stmt);
RULE(assert_stmt);
RULE(assert_stmt_3);
RULE(name_list);
RULE(name_list_loop);
RULE(star_expr);
RULE(exprlist);
RULE(expr_loop);
RULE(target);
RULE(target_1);
RULE(target_2);
RULE(target_4);
RULE(t_primary);
RULE(t_primary_1);
RULE(t_primary_2);
RULE(t_primary_3);
RULE(t_primary_4);
RULE(t_lookahead);
RULE(targetlist);
RULE(target_loop);
RULE(expr_or_star);
RULE(exprlist_star);
RULE(expr_or_star_loop);
RULE(named_expr_star);
RULE(named_expr_list);
RULE(named_expr_star_loop);
RULE(subscript);
RULE(slicelist);
RULE(slice_loop);
RULE(slice);
RULE(slice_1);
RULE(slice_expr);
RULE(dict_item);
RULE(dict_item_1);
RULE(dict_item_2);
RULE(dict_items);
RULE(dict_item_loop);
RULE(as_name);
RULE(iter_for);
RULE(iter_if);
RULE(iterator);
RULE(iter_for_loop);
RULE(assignment);
RULE(pubassign);
RULE(annassign);
RULE(annassign_4);
RULE(augassign);
RULE(simple_assign);
RULE(simple_assign_1_loop);
RULE(simple_assign_1);
RULE(augassign_op);
RULE(import_name);
RULE(import_from);
RULE(import_from_names);
RULE(import_from_names_2);
RULE(import_from_names_2_loop);
RULE(import_from_items);
RULE(import_from_items_2);
RULE(import_as_name);
RULE(dotted_as_name);
RULE(import_as_names);
RULE(import_as_name_loop);
RULE(dotted_as_names);
RULE(dotted_as_name_loop);
RULE(dotted_name);
RULE(dotted_name_loop);
RULE(compound_stmt);
RULE(if_stmt);
RULE(elif_stmt_loop);
RULE(elif_stmt);
RULE(while_stmt);
RULE(for_stmt);
RULE(try_stmt);
RULE(try_stmt_3);
RULE(with_stmt);
RULE(expr_as_name_loop);
RULE(expr_as_name);
RULE(block_suite);
RULE(block_suite_1);
RULE(stmt_loop);
RULE(block_suite_2);
RULE(suite);
RULE(suite_1);
RULE(else_suite);
RULE(finally_suite);
RULE(except_clause);
RULE(except_suite);
RULE(except_clause_loop);
RULE(invocation);
RULE(call_arg_list);
RULE(call_arg_loop);
RULE(call_arg);
RULE(call_arg_1);
RULE(call_arg_2);
RULE(call_arg_3);
RULE(call_arg_4);
RULE(typed_arg_list);
RULE(full_arg_list);
RULE(default_arg_loop);
RULE(full_arg_list_2);
RULE(full_arg_list_2_2);
RULE(args_kwargs);
RULE(args_kwargs_3_loop);
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
RULE(simple_arg_loop);
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
RULE(comparison_1_2_loop);
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
RULE(list_iter);
RULE(list_atom);
RULE(set_atom);
RULE(dict_iter);
RULE(dict_atom);
RULE(builder);
RULE(builder_1);
RULE(builder_2);
RULE(atom);


// single_input:
//     | NEWLINE
//     | simple_stmt
//     | compound_stmt NEWLINE
RULE(single_input) {
    ENTER_FRAME(p, 1, "single_input");
    (res = AST_CONSUME(p, 2, "NEWLINE")) ||
    (res = simple_stmt(p)) ||
    (res = single_input_3(p));
    EXIT_FRAME(p);
}

// compound_stmt NEWLINE
RULE(single_input_3) {
    ENTER_FRAME(p, 2, "single_input:3");
    FAstNode *compound_stmt_, *newline_;
    (compound_stmt_ = compound_stmt(p)) &&
    (newline_ = AST_CONSUME(p, 2, "NEWLINE"))
    ? (res = AST_NODE_2(p, compound_stmt_, newline_)) : 0;
    EXIT_FRAME(p);
}

// file_input:
//     | (NEWLINE | stmt)* ENDMARKER
RULE(file_input) {
    ENTER_FRAME(p, 3, "file_input");
    FAstNode *newlineOrStmts_, *endmarker_;
    (newlineOrStmts_ = OPTIONAL(file_input_1_loop(p))) &&
    (endmarker_ = AST_CONSUME(p, 1, "ENDMARKER"))
    ? (res = AST_NODE_2(p, newlineOrStmts_, endmarker_)) : 0;
    EXIT_FRAME(p);
}

// NEWLINE | stmt
RULE(file_input_1) {
    ENTER_FRAME(p, 4, "file_input:1");
    (res = AST_CONSUME(p, 2, "NEWLINE")) ||
    (res = stmt(p));
    EXIT_FRAME(p);
}

// eval_input:
//     | exprlist NEWLINE* ENDMARKER
RULE(eval_input) {
    ENTER_FRAME(p, 5, "eval_input");
    FAstNode *exprlist_, *newlines_, *endmarker_;
    (exprlist_ = exprlist(p)) &&
    (newlines_ = OPTIONAL(eval_input_loop(p))) &&
    (endmarker_ = AST_CONSUME(p, 1, "ENDMARKER"))
    ? (res = AST_NODE_3(p, exprlist_, newlines_, endmarker_)) : 0;
    EXIT_FRAME(p);
}

// stmt:
//     | (simple_stmt | compound_stmt) NEWLINE
RULE(stmt) {
    ENTER_FRAME(p, 6, "stmt");
    FAstNode *simple_stmtOrCompound_stmt_, *newline_;
    (simple_stmtOrCompound_stmt_ = stmt_1(p)) &&
    (newline_ = AST_CONSUME(p, 2, "NEWLINE"))
    ? (res = AST_NODE_2(p, simple_stmtOrCompound_stmt_, newline_)) : 0;
    EXIT_FRAME(p);
}

// simple_stmt | compound_stmt
RULE(stmt_1) {
    ENTER_FRAME(p, 7, "stmt:1");
    (res = simple_stmt(p)) ||
    (res = compound_stmt(p));
    EXIT_FRAME(p);
}

// simple_stmt:
//     | ';'.small_stmt+ [';']
RULE(simple_stmt) {
    ENTER_FRAME(p, 8, "simple_stmt");
    FAstNode *small_stmts_, *is_semicolon_;
    (small_stmts_ = small_stmt_loop(p)) &&
    (is_semicolon_ = OPTIONAL(AST_CONSUME(p, 12, ";")))
    ? (res = AST_NODE_2(p, small_stmts_, is_semicolon_)) : 0;
    EXIT_FRAME(p);
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
RULE(small_stmt) {
    ENTER_FRAME(p, 9, "small_stmt");
    (res = AST_CONSUME(p, 64, "pass")) ||
    (res = AST_CONSUME(p, 74, "break")) ||
    (res = AST_CONSUME(p, 73, "continue")) ||
    (res = return_stmt(p)) ||
    (res = raise_stmt(p)) ||
    (res = del_stmt(p)) ||
    (res = nonlocal_stmt(p)) ||
    (res = assert_stmt(p)) ||
    (res = import_name(p)) ||
    (res = import_from(p)) ||
    (res = assignment(p));
    EXIT_FRAME(p);
}

// del_stmt:
//     | 'del' targetlist
RULE(del_stmt) {
    ENTER_FRAME(p, 10, "del_stmt");
    FAstNode *targetlist_;
    (AST_CONSUME(p, 79, "del")) &&
    (targetlist_ = targetlist(p))
    ? (res = AST_NODE_1(p, targetlist_)) : 0;
    EXIT_FRAME(p);
}

// return_stmt:
//     | 'return' [exprlist_star]
RULE(return_stmt) {
    ENTER_FRAME(p, 11, "return_stmt");
    FAstNode *exprlist_star_;
    (AST_CONSUME(p, 54, "return")) &&
    (exprlist_star_ = OPTIONAL(exprlist_star(p)))
    ? (res = AST_NODE_1(p, exprlist_star_)) : 0;
    EXIT_FRAME(p);
}

// raise_stmt:
//     | 'raise' expr ['from' expr]
RULE(raise_stmt) {
    ENTER_FRAME(p, 12, "raise_stmt");
    FAstNode *expr_, *from_expr_;
    (AST_CONSUME(p, 78, "raise")) &&
    (expr_ = expr(p)) &&
    (from_expr_ = OPTIONAL(raise_stmt_3(p)))
    ? (res = AST_NODE_2(p, expr_, from_expr_)) : 0;
    EXIT_FRAME(p);
}

// 'from' expr
RULE(raise_stmt_3) {
    ENTER_FRAME(p, 13, "raise_stmt:3");
    FAstNode *expr_;
    (AST_CONSUME(p, 66, "from")) &&
    (expr_ = expr(p))
    ? (res = AST_NODE_1(p, expr_)) : 0;
    EXIT_FRAME(p);
}

// nonlocal_stmt:
//     | 'nonlocal' name_list
RULE(nonlocal_stmt) {
    ENTER_FRAME(p, 14, "nonlocal_stmt");
    FAstNode *name_list_;
    (AST_CONSUME(p, 55, "nonlocal")) &&
    (name_list_ = name_list(p))
    ? (res = AST_NODE_1(p, name_list_)) : 0;
    EXIT_FRAME(p);
}

// assert_stmt:
//     | 'assert' expr [',' expr]
RULE(assert_stmt) {
    ENTER_FRAME(p, 15, "assert_stmt");
    FAstNode *expr_, *comma_expr_;
    (AST_CONSUME(p, 80, "assert")) &&
    (expr_ = expr(p)) &&
    (comma_expr_ = OPTIONAL(assert_stmt_3(p)))
    ? (res = AST_NODE_2(p, expr_, comma_expr_)) : 0;
    EXIT_FRAME(p);
}

// ',' expr
RULE(assert_stmt_3) {
    ENTER_FRAME(p, 16, "assert_stmt:3");
    FAstNode *expr_;
    (AST_CONSUME(p, 7, ",")) &&
    (expr_ = expr(p))
    ? (res = AST_NODE_1(p, expr_)) : 0;
    EXIT_FRAME(p);
}

// name_list:
//     | ','.NAME+
RULE(name_list) {
    ENTER_FRAME(p, 17, "name_list");
    FAstNode *names_;
    (names_ = name_list_loop(p))
    ? (res = AST_NODE_1(p, names_)) : 0;
    EXIT_FRAME(p);
}

// star_expr:
//     | '*' bitwise_or
RULE(star_expr) {
    ENTER_FRAME(p, 18, "star_expr");
    FAstNode *bitwise_or_;
    (AST_CONSUME(p, 23, "*")) &&
    (bitwise_or_ = bitwise_or(p))
    ? (res = AST_NODE_1(p, bitwise_or_)) : 0;
    EXIT_FRAME(p);
}

// exprlist:
//     | ','.expr+ [',']
RULE(exprlist) {
    ENTER_FRAME(p, 19, "exprlist");
    FAstNode *exprs_, *is_comma_;
    (exprs_ = expr_loop(p)) &&
    (is_comma_ = OPTIONAL(AST_CONSUME(p, 7, ",")))
    ? (res = AST_NODE_2(p, exprs_, is_comma_)) : 0;
    EXIT_FRAME(p);
}

// target:
//     | t_primary '.' NAME !t_lookahead
//     | t_primary subscript !t_lookahead
//     | NAME
//     | '(' targetlist ')'
RULE(target) {
    ENTER_FRAME(p, 20, "target");
    (res = target_1(p)) ||
    (res = target_2(p)) ||
    (res = AST_CONSUME(p, 3, "NAME")) ||
    (res = target_4(p));
    EXIT_FRAME(p);
}

// t_primary '.' NAME !t_lookahead
RULE(target_1) {
    ENTER_FRAME(p, 21, "target:1");
    FAstNode *t_primary_, *name_;
    (t_primary_ = t_primary(p)) &&
    (AST_CONSUME(p, 6, ".")) &&
    (name_ = AST_CONSUME(p, 3, "NAME")) &&
    (!TEST(p, t_lookahead(p)))
    ? (res = AST_NODE_2(p, t_primary_, name_)) : 0;
    EXIT_FRAME(p);
}

// t_primary subscript !t_lookahead
RULE(target_2) {
    ENTER_FRAME(p, 22, "target:2");
    FAstNode *t_primary_, *subscript_;
    (t_primary_ = t_primary(p)) &&
    (subscript_ = subscript(p)) &&
    (!TEST(p, t_lookahead(p)))
    ? (res = AST_NODE_2(p, t_primary_, subscript_)) : 0;
    EXIT_FRAME(p);
}

// '(' targetlist ')'
RULE(target_4) {
    ENTER_FRAME(p, 23, "target:4");
    FAstNode *targetlist_;
    (AST_CONSUME(p, 13, "(")) &&
    (targetlist_ = targetlist(p)) &&
    (AST_CONSUME(p, 14, ")"))
    ? (res = AST_NODE_1(p, targetlist_)) : 0;
    EXIT_FRAME(p);
}

// t_primary:
//     | t_primary '.' NAME &t_lookahead
//     | t_primary invocation &t_lookahead
//     | t_primary subscript &t_lookahead
//     | atom &t_lookahead
RULE(t_primary) {
    ENTER_FRAME(p, 24, "t_primary");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (res = t_primary_1(p)) ||
    (res = t_primary_2(p)) ||
    (res = t_primary_3(p)) ||
    (res = t_primary_4(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// t_primary '.' NAME &t_lookahead
RULE(t_primary_1) {
    ENTER_FRAME(p, 25, "t_primary:1");
    FAstNode *t_primary_, *name_;
    (t_primary_ = t_primary(p)) &&
    (AST_CONSUME(p, 6, ".")) &&
    (name_ = AST_CONSUME(p, 3, "NAME")) &&
    (TEST(p, t_lookahead(p)))
    ? (res = AST_NODE_2(p, t_primary_, name_)) : 0;
    EXIT_FRAME(p);
}

// t_primary invocation &t_lookahead
RULE(t_primary_2) {
    ENTER_FRAME(p, 26, "t_primary:2");
    FAstNode *t_primary_, *invocation_;
    (t_primary_ = t_primary(p)) &&
    (invocation_ = invocation(p)) &&
    (TEST(p, t_lookahead(p)))
    ? (res = AST_NODE_2(p, t_primary_, invocation_)) : 0;
    EXIT_FRAME(p);
}

// t_primary subscript &t_lookahead
RULE(t_primary_3) {
    ENTER_FRAME(p, 27, "t_primary:3");
    FAstNode *t_primary_, *subscript_;
    (t_primary_ = t_primary(p)) &&
    (subscript_ = subscript(p)) &&
    (TEST(p, t_lookahead(p)))
    ? (res = AST_NODE_2(p, t_primary_, subscript_)) : 0;
    EXIT_FRAME(p);
}

// atom &t_lookahead
RULE(t_primary_4) {
    ENTER_FRAME(p, 28, "t_primary:4");
    FAstNode *atom_;
    (atom_ = atom(p)) &&
    (TEST(p, t_lookahead(p)))
    ? (res = AST_NODE_1(p, atom_)) : 0;
    EXIT_FRAME(p);
}

// t_lookahead:
//     | '.'
//     | '('
//     | '['
RULE(t_lookahead) {
    ENTER_FRAME(p, 29, "t_lookahead");
    (res = AST_CONSUME(p, 6, ".")) ||
    (res = AST_CONSUME(p, 13, "(")) ||
    (res = AST_CONSUME(p, 17, "["));
    EXIT_FRAME(p);
}

// targetlist:
//     | ','.target+ [',']
RULE(targetlist) {
    ENTER_FRAME(p, 30, "targetlist");
    FAstNode *targets_, *is_comma_;
    (targets_ = target_loop(p)) &&
    (is_comma_ = OPTIONAL(AST_CONSUME(p, 7, ",")))
    ? (res = AST_NODE_2(p, targets_, is_comma_)) : 0;
    EXIT_FRAME(p);
}

// expr_or_star:
//     | star_expr
//     | expr
RULE(expr_or_star) {
    ENTER_FRAME(p, 31, "expr_or_star");
    (res = star_expr(p)) ||
    (res = expr(p));
    EXIT_FRAME(p);
}

// exprlist_star:
//     | ','.expr_or_star+ [',']
RULE(exprlist_star) {
    ENTER_FRAME(p, 32, "exprlist_star");
    FAstNode *expr_or_stars_, *is_comma_;
    (expr_or_stars_ = expr_or_star_loop(p)) &&
    (is_comma_ = OPTIONAL(AST_CONSUME(p, 7, ",")))
    ? (res = AST_NODE_2(p, expr_or_stars_, is_comma_)) : 0;
    EXIT_FRAME(p);
}

// named_expr_star:
//     | star_expr
//     | named_expr
RULE(named_expr_star) {
    ENTER_FRAME(p, 33, "named_expr_star");
    (res = star_expr(p)) ||
    (res = named_expr(p));
    EXIT_FRAME(p);
}

// named_expr_list:
//     | ','.named_expr_star+ [',']
RULE(named_expr_list) {
    ENTER_FRAME(p, 34, "named_expr_list");
    FAstNode *named_expr_stars_, *is_comma_;
    (named_expr_stars_ = named_expr_star_loop(p)) &&
    (is_comma_ = OPTIONAL(AST_CONSUME(p, 7, ",")))
    ? (res = AST_NODE_2(p, named_expr_stars_, is_comma_)) : 0;
    EXIT_FRAME(p);
}

// subscript:
//     | '[' slicelist ']'
RULE(subscript) {
    ENTER_FRAME(p, 35, "subscript");
    FAstNode *slicelist_;
    (AST_CONSUME(p, 17, "[")) &&
    (slicelist_ = slicelist(p)) &&
    (AST_CONSUME(p, 18, "]"))
    ? (res = AST_NODE_1(p, slicelist_)) : 0;
    EXIT_FRAME(p);
}

// slicelist:
//     | ','.slice+ [',']
RULE(slicelist) {
    ENTER_FRAME(p, 36, "slicelist");
    FAstNode *slices_, *is_comma_;
    (slices_ = slice_loop(p)) &&
    (is_comma_ = OPTIONAL(AST_CONSUME(p, 7, ",")))
    ? (res = AST_NODE_2(p, slices_, is_comma_)) : 0;
    EXIT_FRAME(p);
}

// slice:
//     | [expr] slice_expr [slice_expr]
//     | expr
RULE(slice) {
    ENTER_FRAME(p, 37, "slice");
    (res = slice_1(p)) ||
    (res = expr(p));
    EXIT_FRAME(p);
}

// [expr] slice_expr [slice_expr]
RULE(slice_1) {
    ENTER_FRAME(p, 38, "slice:1");
    FAstNode *expr_, *slice_expr_, *slice_expr_1_;
    (expr_ = OPTIONAL(expr(p))) &&
    (slice_expr_ = slice_expr(p)) &&
    (slice_expr_1_ = OPTIONAL(slice_expr(p)))
    ? (res = AST_NODE_3(p, expr_, slice_expr_, slice_expr_1_)) : 0;
    EXIT_FRAME(p);
}

// slice_expr:
//     | ':' [expr]
RULE(slice_expr) {
    ENTER_FRAME(p, 39, "slice_expr");
    FAstNode *expr_;
    (AST_CONSUME(p, 9, ":")) &&
    (expr_ = OPTIONAL(expr(p)))
    ? (res = AST_NODE_1(p, expr_)) : 0;
    EXIT_FRAME(p);
}

// dict_item:
//     | expr ':' expr
//     | '**' bitwise_or
RULE(dict_item) {
    ENTER_FRAME(p, 40, "dict_item");
    (res = dict_item_1(p)) ||
    (res = dict_item_2(p));
    EXIT_FRAME(p);
}

// expr ':' expr
RULE(dict_item_1) {
    ENTER_FRAME(p, 41, "dict_item:1");
    FAstNode *expr_, *expr_1_;
    (expr_ = expr(p)) &&
    (AST_CONSUME(p, 9, ":")) &&
    (expr_1_ = expr(p))
    ? (res = AST_NODE_2(p, expr_, expr_1_)) : 0;
    EXIT_FRAME(p);
}

// '**' bitwise_or
RULE(dict_item_2) {
    ENTER_FRAME(p, 42, "dict_item:2");
    FAstNode *bitwise_or_;
    (AST_CONSUME(p, 38, "**")) &&
    (bitwise_or_ = bitwise_or(p))
    ? (res = AST_NODE_1(p, bitwise_or_)) : 0;
    EXIT_FRAME(p);
}

// dict_items:
//     | ','.dict_item+ [',']
RULE(dict_items) {
    ENTER_FRAME(p, 43, "dict_items");
    FAstNode *dict_items_, *is_comma_;
    (dict_items_ = dict_item_loop(p)) &&
    (is_comma_ = OPTIONAL(AST_CONSUME(p, 7, ",")))
    ? (res = AST_NODE_2(p, dict_items_, is_comma_)) : 0;
    EXIT_FRAME(p);
}

// as_name:
//     | 'as' NAME
RULE(as_name) {
    ENTER_FRAME(p, 44, "as_name");
    FAstNode *name_;
    (AST_CONSUME(p, 65, "as")) &&
    (name_ = AST_CONSUME(p, 3, "NAME"))
    ? (res = AST_NODE_1(p, name_)) : 0;
    EXIT_FRAME(p);
}

// iter_for:
//     | 'for' targetlist 'in' disjunction [iter_if]
RULE(iter_for) {
    ENTER_FRAME(p, 45, "iter_for");
    FAstNode *targetlist_, *disjunction_, *iter_if_;
    (AST_CONSUME(p, 72, "for")) &&
    (targetlist_ = targetlist(p)) &&
    (AST_CONSUME(p, 63, "in")) &&
    (disjunction_ = disjunction(p)) &&
    (iter_if_ = OPTIONAL(iter_if(p)))
    ? (res = AST_NODE_3(p, targetlist_, disjunction_, iter_if_)) : 0;
    EXIT_FRAME(p);
}

// iter_if:
//     | 'if' named_expr
RULE(iter_if) {
    ENTER_FRAME(p, 46, "iter_if");
    FAstNode *named_expr_;
    (AST_CONSUME(p, 56, "if")) &&
    (named_expr_ = named_expr(p))
    ? (res = AST_NODE_1(p, named_expr_)) : 0;
    EXIT_FRAME(p);
}

// iterator:
//     | iter_for* 'for' targetlist [iter_if]
RULE(iterator) {
    ENTER_FRAME(p, 47, "iterator");
    FAstNode *iter_fors_, *targetlist_, *iter_if_;
    (iter_fors_ = OPTIONAL(iter_for_loop(p))) &&
    (AST_CONSUME(p, 72, "for")) &&
    (targetlist_ = targetlist(p)) &&
    (iter_if_ = OPTIONAL(iter_if(p)))
    ? (res = AST_NODE_3(p, iter_fors_, targetlist_, iter_if_)) : 0;
    EXIT_FRAME(p);
}

// assignment:
//     | pubassign
//     | annassign
//     | augassign
//     | simple_assign
RULE(assignment) {
    ENTER_FRAME(p, 48, "assignment");
    (res = pubassign(p)) ||
    (res = annassign(p)) ||
    (res = augassign(p)) ||
    (res = simple_assign(p));
    EXIT_FRAME(p);
}

// pubassign:
//     | '/' NAME '=' exprlist
RULE(pubassign) {
    ENTER_FRAME(p, 49, "pubassign");
    FAstNode *name_, *exprlist_;
    (AST_CONSUME(p, 24, "/")) &&
    (name_ = AST_CONSUME(p, 3, "NAME")) &&
    (AST_CONSUME(p, 8, "=")) &&
    (exprlist_ = exprlist(p))
    ? (res = AST_NODE_2(p, name_, exprlist_)) : 0;
    EXIT_FRAME(p);
}

// annassign:
//     | target ':' expr ['=' exprlist]
RULE(annassign) {
    ENTER_FRAME(p, 50, "annassign");
    FAstNode *target_, *expr_, *assign_exprlist_;
    (target_ = target(p)) &&
    (AST_CONSUME(p, 9, ":")) &&
    (expr_ = expr(p)) &&
    (assign_exprlist_ = OPTIONAL(annassign_4(p)))
    ? (res = AST_NODE_3(p, target_, expr_, assign_exprlist_)) : 0;
    EXIT_FRAME(p);
}

// '=' exprlist
RULE(annassign_4) {
    ENTER_FRAME(p, 51, "annassign:4");
    FAstNode *exprlist_;
    (AST_CONSUME(p, 8, "=")) &&
    (exprlist_ = exprlist(p))
    ? (res = AST_NODE_1(p, exprlist_)) : 0;
    EXIT_FRAME(p);
}

// augassign:
//     | target augassign_op exprlist
RULE(augassign) {
    ENTER_FRAME(p, 52, "augassign");
    FAstNode *target_, *augassign_op_, *exprlist_;
    (target_ = target(p)) &&
    (augassign_op_ = augassign_op(p)) &&
    (exprlist_ = exprlist(p))
    ? (res = AST_NODE_3(p, target_, augassign_op_, exprlist_)) : 0;
    EXIT_FRAME(p);
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
RULE(simple_assign) {
    ENTER_FRAME(p, 53, "simple_assign");
    FAstNode *targetlist_assigns_, *exprlist_star_;
    (targetlist_assigns_ = OPTIONAL(simple_assign_1_loop(p))) &&
    (exprlist_star_ = exprlist_star(p))
    ? (res = AST_NODE_2(p, targetlist_assigns_, exprlist_star_)) : 0;
    EXIT_FRAME(p);
}

// targetlist '='
RULE(simple_assign_1) {
    ENTER_FRAME(p, 54, "simple_assign:1");
    FAstNode *targetlist_;
    (targetlist_ = targetlist(p)) &&
    (AST_CONSUME(p, 8, "="))
    ? (res = AST_NODE_1(p, targetlist_)) : 0;
    EXIT_FRAME(p);
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
RULE(augassign_op) {
    ENTER_FRAME(p, 55, "augassign_op");
    (res = AST_CONSUME(p, 39, "+=")) ||
    (res = AST_CONSUME(p, 40, "-=")) ||
    (res = AST_CONSUME(p, 41, "*=")) ||
    (res = AST_CONSUME(p, 44, "@=")) ||
    (res = AST_CONSUME(p, 42, "/=")) ||
    (res = AST_CONSUME(p, 43, "%=")) ||
    (res = AST_CONSUME(p, 46, "&=")) ||
    (res = AST_CONSUME(p, 45, "|=")) ||
    (res = AST_CONSUME(p, 47, "^=")) ||
    (res = AST_CONSUME(p, 52, "<<=")) ||
    (res = AST_CONSUME(p, 53, ">>=")) ||
    (res = AST_CONSUME(p, 51, "**=")) ||
    (res = AST_CONSUME(p, 50, "//="));
    EXIT_FRAME(p);
}

// import_name:
//     | 'import' dotted_as_names
RULE(import_name) {
    ENTER_FRAME(p, 56, "import_name");
    FAstNode *dotted_as_names_;
    (AST_CONSUME(p, 67, "import")) &&
    (dotted_as_names_ = dotted_as_names(p))
    ? (res = AST_NODE_1(p, dotted_as_names_)) : 0;
    EXIT_FRAME(p);
}

// import_from:
//     | 'from' import_from_names 'import' import_from_items
RULE(import_from) {
    ENTER_FRAME(p, 57, "import_from");
    FAstNode *import_from_names_, *import_from_items_;
    (AST_CONSUME(p, 66, "from")) &&
    (import_from_names_ = import_from_names(p)) &&
    (AST_CONSUME(p, 67, "import")) &&
    (import_from_items_ = import_from_items(p))
    ? (res = AST_NODE_2(p, import_from_names_, import_from_items_)) : 0;
    EXIT_FRAME(p);
}

// import_from_names:
//     | dotted_name
//     | '.'+ [dotted_name]
RULE(import_from_names) {
    ENTER_FRAME(p, 58, "import_from_names");
    (res = dotted_name(p)) ||
    (res = import_from_names_2(p));
    EXIT_FRAME(p);
}

// '.'+ [dotted_name]
RULE(import_from_names_2) {
    ENTER_FRAME(p, 59, "import_from_names:2");
    FAstNode *dotted_name_;
    (import_from_names_2_loop(p)) &&
    (dotted_name_ = OPTIONAL(dotted_name(p)))
    ? (res = AST_NODE_1(p, dotted_name_)) : 0;
    EXIT_FRAME(p);
}

// import_from_items:
//     | '*'
//     | '(' import_as_names [','] ')'
//     | import_as_names
RULE(import_from_items) {
    ENTER_FRAME(p, 60, "import_from_items");
    (res = AST_CONSUME(p, 23, "*")) ||
    (res = import_from_items_2(p)) ||
    (res = import_as_names(p));
    EXIT_FRAME(p);
}

// '(' import_as_names [','] ')'
RULE(import_from_items_2) {
    ENTER_FRAME(p, 61, "import_from_items:2");
    FAstNode *import_as_names_, *is_comma_;
    (AST_CONSUME(p, 13, "(")) &&
    (import_as_names_ = import_as_names(p)) &&
    (is_comma_ = OPTIONAL(AST_CONSUME(p, 7, ","))) &&
    (AST_CONSUME(p, 14, ")"))
    ? (res = AST_NODE_2(p, import_as_names_, is_comma_)) : 0;
    EXIT_FRAME(p);
}

// import_as_name:
//     | NAME [as_name]
RULE(import_as_name) {
    ENTER_FRAME(p, 62, "import_as_name");
    FAstNode *name_, *as_name_;
    (name_ = AST_CONSUME(p, 3, "NAME")) &&
    (as_name_ = OPTIONAL(as_name(p)))
    ? (res = AST_NODE_2(p, name_, as_name_)) : 0;
    EXIT_FRAME(p);
}

// dotted_as_name:
//     | dotted_name [as_name]
RULE(dotted_as_name) {
    ENTER_FRAME(p, 63, "dotted_as_name");
    FAstNode *dotted_name_, *as_name_;
    (dotted_name_ = dotted_name(p)) &&
    (as_name_ = OPTIONAL(as_name(p)))
    ? (res = AST_NODE_2(p, dotted_name_, as_name_)) : 0;
    EXIT_FRAME(p);
}

// import_as_names:
//     | ','.import_as_name+
RULE(import_as_names) {
    ENTER_FRAME(p, 64, "import_as_names");
    FAstNode *import_as_names_;
    (import_as_names_ = import_as_name_loop(p))
    ? (res = AST_NODE_1(p, import_as_names_)) : 0;
    EXIT_FRAME(p);
}

// dotted_as_names:
//     | ','.dotted_as_name+
RULE(dotted_as_names) {
    ENTER_FRAME(p, 65, "dotted_as_names");
    FAstNode *dotted_as_names_;
    (dotted_as_names_ = dotted_as_name_loop(p))
    ? (res = AST_NODE_1(p, dotted_as_names_)) : 0;
    EXIT_FRAME(p);
}

// dotted_name:
//     | '.'.NAME+
RULE(dotted_name) {
    ENTER_FRAME(p, 66, "dotted_name");
    FAstNode *names_;
    (names_ = dotted_name_loop(p))
    ? (res = AST_NODE_1(p, names_)) : 0;
    EXIT_FRAME(p);
}

// compound_stmt:
//     | if_stmt
//     | while_stmt
//     | for_stmt
//     | try_stmt
//     | with_stmt
RULE(compound_stmt) {
    ENTER_FRAME(p, 67, "compound_stmt");
    (res = if_stmt(p)) ||
    (res = while_stmt(p)) ||
    (res = for_stmt(p)) ||
    (res = try_stmt(p)) ||
    (res = with_stmt(p));
    EXIT_FRAME(p);
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
RULE(if_stmt) {
    ENTER_FRAME(p, 68, "if_stmt");
    FAstNode *named_expr_, *suite_, *elif_stmts_, *else_suite_;
    (AST_CONSUME(p, 56, "if")) &&
    (named_expr_ = named_expr(p)) &&
    (suite_ = suite(p)) &&
    (elif_stmts_ = OPTIONAL(elif_stmt_loop(p))) &&
    (else_suite_ = OPTIONAL(else_suite(p)))
    ? (res = AST_NODE_4(p, named_expr_, suite_, elif_stmts_, else_suite_)) : 0;
    EXIT_FRAME(p);
}

// elif_stmt:
//     | 'elif' named_expr suite
RULE(elif_stmt) {
    ENTER_FRAME(p, 69, "elif_stmt");
    FAstNode *named_expr_, *suite_;
    (AST_CONSUME(p, 57, "elif")) &&
    (named_expr_ = named_expr(p)) &&
    (suite_ = suite(p))
    ? (res = AST_NODE_2(p, named_expr_, suite_)) : 0;
    EXIT_FRAME(p);
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
RULE(while_stmt) {
    ENTER_FRAME(p, 70, "while_stmt");
    FAstNode *named_expr_, *suite_, *else_suite_;
    (AST_CONSUME(p, 71, "while")) &&
    (named_expr_ = named_expr(p)) &&
    (suite_ = suite(p)) &&
    (else_suite_ = OPTIONAL(else_suite(p)))
    ? (res = AST_NODE_3(p, named_expr_, suite_, else_suite_)) : 0;
    EXIT_FRAME(p);
}

// for_stmt:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
RULE(for_stmt) {
    ENTER_FRAME(p, 71, "for_stmt");
    FAstNode *targetlist_, *exprlist_, *suite_, *else_suite_;
    (AST_CONSUME(p, 72, "for")) &&
    (targetlist_ = targetlist(p)) &&
    (AST_CONSUME(p, 63, "in")) &&
    (exprlist_ = exprlist(p)) &&
    (suite_ = suite(p)) &&
    (else_suite_ = OPTIONAL(else_suite(p)))
    ? (res = AST_NODE_4(p, targetlist_, exprlist_, suite_, else_suite_)) : 0;
    EXIT_FRAME(p);
}

// try_stmt:
//     | 'try' suite (except_suite | finally_suite)
RULE(try_stmt) {
    ENTER_FRAME(p, 72, "try_stmt");
    FAstNode *suite_, *except_suiteOrFinally_suite_;
    (AST_CONSUME(p, 75, "try")) &&
    (suite_ = suite(p)) &&
    (except_suiteOrFinally_suite_ = try_stmt_3(p))
    ? (res = AST_NODE_2(p, suite_, except_suiteOrFinally_suite_)) : 0;
    EXIT_FRAME(p);
}

// except_suite | finally_suite
RULE(try_stmt_3) {
    ENTER_FRAME(p, 73, "try_stmt:3");
    (res = except_suite(p)) ||
    (res = finally_suite(p));
    EXIT_FRAME(p);
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
RULE(with_stmt) {
    ENTER_FRAME(p, 74, "with_stmt");
    FAstNode *expr_as_names_, *suite_;
    (AST_CONSUME(p, 68, "with")) &&
    (expr_as_names_ = expr_as_name_loop(p)) &&
    (suite_ = suite(p))
    ? (res = AST_NODE_2(p, expr_as_names_, suite_)) : 0;
    EXIT_FRAME(p);
}

// expr_as_name:
//     | expr [as_name]
RULE(expr_as_name) {
    ENTER_FRAME(p, 75, "expr_as_name");
    FAstNode *expr_, *as_name_;
    (expr_ = expr(p)) &&
    (as_name_ = OPTIONAL(as_name(p)))
    ? (res = AST_NODE_2(p, expr_, as_name_)) : 0;
    EXIT_FRAME(p);
}

// block_suite:
//     | '{' NEWLINE stmt+ '}'
//     | '{' '}'
RULE(block_suite) {
    ENTER_FRAME(p, 76, "block_suite");
    (res = block_suite_1(p)) ||
    (res = block_suite_2(p));
    EXIT_FRAME(p);
}

// '{' NEWLINE stmt+ '}'
RULE(block_suite_1) {
    ENTER_FRAME(p, 77, "block_suite:1");
    FAstNode *newline_, *stmts_;
    (AST_CONSUME(p, 15, "{")) &&
    (newline_ = AST_CONSUME(p, 2, "NEWLINE")) &&
    (stmts_ = stmt_loop(p)) &&
    (AST_CONSUME(p, 16, "}"))
    ? (res = AST_NODE_2(p, newline_, stmts_)) : 0;
    EXIT_FRAME(p);
}

// '{' '}'
RULE(block_suite_2) {
    ENTER_FRAME(p, 78, "block_suite:2");
    (AST_CONSUME(p, 15, "{")) &&
    (AST_CONSUME(p, 16, "}"));
    EXIT_FRAME(p);
}

// suite:
//     | ':' simple_stmt
//     | block_suite
RULE(suite) {
    ENTER_FRAME(p, 79, "suite");
    (res = suite_1(p)) ||
    (res = block_suite(p));
    EXIT_FRAME(p);
}

// ':' simple_stmt
RULE(suite_1) {
    ENTER_FRAME(p, 80, "suite:1");
    FAstNode *simple_stmt_;
    (AST_CONSUME(p, 9, ":")) &&
    (simple_stmt_ = simple_stmt(p))
    ? (res = AST_NODE_1(p, simple_stmt_)) : 0;
    EXIT_FRAME(p);
}

// else_suite:
//     | 'else' suite
RULE(else_suite) {
    ENTER_FRAME(p, 81, "else_suite");
    FAstNode *suite_;
    (AST_CONSUME(p, 58, "else")) &&
    (suite_ = suite(p))
    ? (res = AST_NODE_1(p, suite_)) : 0;
    EXIT_FRAME(p);
}

// finally_suite:
//     | 'finally' suite
RULE(finally_suite) {
    ENTER_FRAME(p, 82, "finally_suite");
    FAstNode *suite_;
    (AST_CONSUME(p, 77, "finally")) &&
    (suite_ = suite(p))
    ? (res = AST_NODE_1(p, suite_)) : 0;
    EXIT_FRAME(p);
}

// except_clause:
//     | 'except' [expr_as_name] suite
RULE(except_clause) {
    ENTER_FRAME(p, 83, "except_clause");
    FAstNode *expr_as_name_, *suite_;
    (AST_CONSUME(p, 76, "except")) &&
    (expr_as_name_ = OPTIONAL(expr_as_name(p))) &&
    (suite_ = suite(p))
    ? (res = AST_NODE_2(p, expr_as_name_, suite_)) : 0;
    EXIT_FRAME(p);
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
RULE(except_suite) {
    ENTER_FRAME(p, 84, "except_suite");
    FAstNode *except_clauses_, *else_suite_, *finally_suite_;
    (except_clauses_ = except_clause_loop(p)) &&
    (else_suite_ = OPTIONAL(else_suite(p))) &&
    (finally_suite_ = OPTIONAL(finally_suite(p)))
    ? (res = AST_NODE_3(p, except_clauses_, else_suite_, finally_suite_)) : 0;
    EXIT_FRAME(p);
}

// invocation:
//     | '(' [call_arg_list] ')'
RULE(invocation) {
    ENTER_FRAME(p, 85, "invocation");
    FAstNode *call_arg_list_;
    (AST_CONSUME(p, 13, "(")) &&
    (call_arg_list_ = OPTIONAL(call_arg_list(p))) &&
    (AST_CONSUME(p, 14, ")"))
    ? (res = AST_NODE_1(p, call_arg_list_)) : 0;
    EXIT_FRAME(p);
}

// call_arg_list:
//     | ','.call_arg+ [',']
RULE(call_arg_list) {
    ENTER_FRAME(p, 86, "call_arg_list");
    FAstNode *call_args_, *is_comma_;
    (call_args_ = call_arg_loop(p)) &&
    (is_comma_ = OPTIONAL(AST_CONSUME(p, 7, ",")))
    ? (res = AST_NODE_2(p, call_args_, is_comma_)) : 0;
    EXIT_FRAME(p);
}

// call_arg:
//     | NAME ':=' expr
//     | NAME '=' expr
//     | '**' expr
//     | '*' expr
//     | expr
RULE(call_arg) {
    ENTER_FRAME(p, 87, "call_arg");
    (res = call_arg_1(p)) ||
    (res = call_arg_2(p)) ||
    (res = call_arg_3(p)) ||
    (res = call_arg_4(p)) ||
    (res = expr(p));
    EXIT_FRAME(p);
}

// NAME ':=' expr
RULE(call_arg_1) {
    ENTER_FRAME(p, 88, "call_arg:1");
    FAstNode *name_, *expr_;
    (name_ = AST_CONSUME(p, 3, "NAME")) &&
    (AST_CONSUME(p, 36, ":=")) &&
    (expr_ = expr(p))
    ? (res = AST_NODE_2(p, name_, expr_)) : 0;
    EXIT_FRAME(p);
}

// NAME '=' expr
RULE(call_arg_2) {
    ENTER_FRAME(p, 89, "call_arg:2");
    FAstNode *name_, *expr_;
    (name_ = AST_CONSUME(p, 3, "NAME")) &&
    (AST_CONSUME(p, 8, "=")) &&
    (expr_ = expr(p))
    ? (res = AST_NODE_2(p, name_, expr_)) : 0;
    EXIT_FRAME(p);
}

// '**' expr
RULE(call_arg_3) {
    ENTER_FRAME(p, 90, "call_arg:3");
    FAstNode *expr_;
    (AST_CONSUME(p, 38, "**")) &&
    (expr_ = expr(p))
    ? (res = AST_NODE_1(p, expr_)) : 0;
    EXIT_FRAME(p);
}

// '*' expr
RULE(call_arg_4) {
    ENTER_FRAME(p, 91, "call_arg:4");
    FAstNode *expr_;
    (AST_CONSUME(p, 23, "*")) &&
    (expr_ = expr(p))
    ? (res = AST_NODE_1(p, expr_)) : 0;
    EXIT_FRAME(p);
}

// typed_arg_list:
//     | kwargs
//     | args_kwargs
//     | full_arg_list
RULE(typed_arg_list) {
    ENTER_FRAME(p, 92, "typed_arg_list");
    (res = kwargs(p)) ||
    (res = args_kwargs(p)) ||
    (res = full_arg_list(p));
    EXIT_FRAME(p);
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
RULE(full_arg_list) {
    ENTER_FRAME(p, 93, "full_arg_list");
    FAstNode *default_args_, *full_arg_list_;
    (default_args_ = default_arg_loop(p)) &&
    (full_arg_list_ = OPTIONAL(full_arg_list_2(p)))
    ? (res = AST_NODE_2(p, default_args_, full_arg_list_)) : 0;
    EXIT_FRAME(p);
}

// ',' [kwargs | args_kwargs]
RULE(full_arg_list_2) {
    ENTER_FRAME(p, 94, "full_arg_list:2");
    FAstNode *kwargsOrArgs_kwargs_;
    (AST_CONSUME(p, 7, ",")) &&
    (kwargsOrArgs_kwargs_ = OPTIONAL(full_arg_list_2_2(p)))
    ? (res = AST_NODE_1(p, kwargsOrArgs_kwargs_)) : 0;
    EXIT_FRAME(p);
}

// kwargs | args_kwargs
RULE(full_arg_list_2_2) {
    ENTER_FRAME(p, 95, "full_arg_list:2:2");
    (res = kwargs(p)) ||
    (res = args_kwargs(p));
    EXIT_FRAME(p);
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
RULE(args_kwargs) {
    ENTER_FRAME(p, 96, "args_kwargs");
    FAstNode *typed_arg_, *comma_default_args_, *args_kwargs_;
    (AST_CONSUME(p, 23, "*")) &&
    (typed_arg_ = OPTIONAL(typed_arg(p))) &&
    (comma_default_args_ = OPTIONAL(args_kwargs_3_loop(p))) &&
    (args_kwargs_ = OPTIONAL(args_kwargs_4(p)))
    ? (res = AST_NODE_3(p, typed_arg_, comma_default_args_, args_kwargs_)) : 0;
    EXIT_FRAME(p);
}

// ',' default_arg
RULE(args_kwargs_3) {
    ENTER_FRAME(p, 97, "args_kwargs:3");
    FAstNode *default_arg_;
    (AST_CONSUME(p, 7, ",")) &&
    (default_arg_ = default_arg(p))
    ? (res = AST_NODE_1(p, default_arg_)) : 0;
    EXIT_FRAME(p);
}

// ',' [kwargs]
RULE(args_kwargs_4) {
    ENTER_FRAME(p, 98, "args_kwargs:4");
    FAstNode *kwargs_;
    (AST_CONSUME(p, 7, ",")) &&
    (kwargs_ = OPTIONAL(kwargs(p)))
    ? (res = AST_NODE_1(p, kwargs_)) : 0;
    EXIT_FRAME(p);
}

// kwargs:
//     | '**' typed_arg [',']
RULE(kwargs) {
    ENTER_FRAME(p, 99, "kwargs");
    FAstNode *typed_arg_, *is_comma_;
    (AST_CONSUME(p, 38, "**")) &&
    (typed_arg_ = typed_arg(p)) &&
    (is_comma_ = OPTIONAL(AST_CONSUME(p, 7, ",")))
    ? (res = AST_NODE_2(p, typed_arg_, is_comma_)) : 0;
    EXIT_FRAME(p);
}

// default_arg:
//     | typed_arg ['=' expr]
RULE(default_arg) {
    ENTER_FRAME(p, 100, "default_arg");
    FAstNode *typed_arg_, *assign_expr_;
    (typed_arg_ = typed_arg(p)) &&
    (assign_expr_ = OPTIONAL(default_arg_2(p)))
    ? (res = AST_NODE_2(p, typed_arg_, assign_expr_)) : 0;
    EXIT_FRAME(p);
}

// '=' expr
RULE(default_arg_2) {
    ENTER_FRAME(p, 101, "default_arg:2");
    FAstNode *expr_;
    (AST_CONSUME(p, 8, "=")) &&
    (expr_ = expr(p))
    ? (res = AST_NODE_1(p, expr_)) : 0;
    EXIT_FRAME(p);
}

// typed_arg:
//     | NAME [':' expr]
RULE(typed_arg) {
    ENTER_FRAME(p, 102, "typed_arg");
    FAstNode *name_, *colon_expr_;
    (name_ = AST_CONSUME(p, 3, "NAME")) &&
    (colon_expr_ = OPTIONAL(typed_arg_2(p)))
    ? (res = AST_NODE_2(p, name_, colon_expr_)) : 0;
    EXIT_FRAME(p);
}

// ':' expr
RULE(typed_arg_2) {
    ENTER_FRAME(p, 103, "typed_arg:2");
    FAstNode *expr_;
    (AST_CONSUME(p, 9, ":")) &&
    (expr_ = expr(p))
    ? (res = AST_NODE_1(p, expr_)) : 0;
    EXIT_FRAME(p);
}

// simple_arg:
//     | NAME ['=' expr]
RULE(simple_arg) {
    ENTER_FRAME(p, 104, "simple_arg");
    FAstNode *name_, *assign_expr_;
    (name_ = AST_CONSUME(p, 3, "NAME")) &&
    (assign_expr_ = OPTIONAL(simple_arg_2(p)))
    ? (res = AST_NODE_2(p, name_, assign_expr_)) : 0;
    EXIT_FRAME(p);
}

// '=' expr
RULE(simple_arg_2) {
    ENTER_FRAME(p, 105, "simple_arg:2");
    FAstNode *expr_;
    (AST_CONSUME(p, 8, "=")) &&
    (expr_ = expr(p))
    ? (res = AST_NODE_1(p, expr_)) : 0;
    EXIT_FRAME(p);
}

// simple_args:
//     | ','.simple_arg+
RULE(simple_args) {
    ENTER_FRAME(p, 106, "simple_args");
    FAstNode *simple_args_;
    (simple_args_ = simple_arg_loop(p))
    ? (res = AST_NODE_1(p, simple_args_)) : 0;
    EXIT_FRAME(p);
}

// builder_hint:
//     | '<' name_list '>'
RULE(builder_hint) {
    ENTER_FRAME(p, 107, "builder_hint");
    FAstNode *name_list_;
    (AST_CONSUME(p, 19, "<")) &&
    (name_list_ = name_list(p)) &&
    (AST_CONSUME(p, 20, ">"))
    ? (res = AST_NODE_1(p, name_list_)) : 0;
    EXIT_FRAME(p);
}

// builder_args:
//     | simple_args
//     | '(' [typed_arg_list] ')'
RULE(builder_args) {
    ENTER_FRAME(p, 108, "builder_args");
    (res = simple_args(p)) ||
    (res = builder_args_2(p));
    EXIT_FRAME(p);
}

// '(' [typed_arg_list] ')'
RULE(builder_args_2) {
    ENTER_FRAME(p, 109, "builder_args:2");
    FAstNode *typed_arg_list_;
    (AST_CONSUME(p, 13, "(")) &&
    (typed_arg_list_ = OPTIONAL(typed_arg_list(p))) &&
    (AST_CONSUME(p, 14, ")"))
    ? (res = AST_NODE_1(p, typed_arg_list_)) : 0;
    EXIT_FRAME(p);
}

// named_expr:
//     | NAME ':=' expr
//     | expr
RULE(named_expr) {
    ENTER_FRAME(p, 110, "named_expr");
    (res = named_expr_1(p)) ||
    (res = expr(p));
    EXIT_FRAME(p);
}

// NAME ':=' expr
RULE(named_expr_1) {
    ENTER_FRAME(p, 111, "named_expr:1");
    FAstNode *name_, *expr_;
    (name_ = AST_CONSUME(p, 3, "NAME")) &&
    (AST_CONSUME(p, 36, ":=")) &&
    (expr_ = expr(p))
    ? (res = AST_NODE_2(p, name_, expr_)) : 0;
    EXIT_FRAME(p);
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
RULE(conditional) {
    ENTER_FRAME(p, 112, "conditional");
    FAstNode *disjunction_, *disjunction_1_, *expr_;
    (AST_CONSUME(p, 56, "if")) &&
    (disjunction_ = disjunction(p)) &&
    (AST_CONSUME(p, 10, "?")) &&
    (disjunction_1_ = disjunction(p)) &&
    (AST_CONSUME(p, 9, ":")) &&
    (expr_ = expr(p))
    ? (res = AST_NODE_3(p, disjunction_, disjunction_1_, expr_)) : 0;
    EXIT_FRAME(p);
}

// expr:
//     | conditional
//     | disjunction
RULE(expr) {
    ENTER_FRAME(p, 113, "expr");
    (res = conditional(p)) ||
    (res = disjunction(p));
    EXIT_FRAME(p);
}

// disjunction:
//     | disjunction 'or' conjunction
//     | conjunction
RULE(disjunction) {
    ENTER_FRAME(p, 114, "disjunction");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (res = disjunction_1(p)) ||
    (res = conjunction(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// disjunction 'or' conjunction
RULE(disjunction_1) {
    ENTER_FRAME(p, 115, "disjunction:1");
    FAstNode *disjunction_, *conjunction_;
    (disjunction_ = disjunction(p)) &&
    (AST_CONSUME(p, 60, "or")) &&
    (conjunction_ = conjunction(p))
    ? (res = AST_NODE_2(p, disjunction_, conjunction_)) : 0;
    EXIT_FRAME(p);
}

// conjunction:
//     | conjunction 'and' inversion
//     | inversion
RULE(conjunction) {
    ENTER_FRAME(p, 116, "conjunction");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (res = conjunction_1(p)) ||
    (res = inversion(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// conjunction 'and' inversion
RULE(conjunction_1) {
    ENTER_FRAME(p, 117, "conjunction:1");
    FAstNode *conjunction_, *inversion_;
    (conjunction_ = conjunction(p)) &&
    (AST_CONSUME(p, 59, "and")) &&
    (inversion_ = inversion(p))
    ? (res = AST_NODE_2(p, conjunction_, inversion_)) : 0;
    EXIT_FRAME(p);
}

// inversion:
//     | 'not' inversion
//     | comparison
RULE(inversion) {
    ENTER_FRAME(p, 118, "inversion");
    (res = inversion_1(p)) ||
    (res = comparison(p));
    EXIT_FRAME(p);
}

// 'not' inversion
RULE(inversion_1) {
    ENTER_FRAME(p, 119, "inversion:1");
    FAstNode *inversion_;
    (AST_CONSUME(p, 61, "not")) &&
    (inversion_ = inversion(p))
    ? (res = AST_NODE_1(p, inversion_)) : 0;
    EXIT_FRAME(p);
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
RULE(comparison) {
    ENTER_FRAME(p, 120, "comparison");
    (res = comparison_1(p)) ||
    (res = bitwise_or(p));
    EXIT_FRAME(p);
}

// bitwise_or (comp_op bitwise_or)+
RULE(comparison_1) {
    ENTER_FRAME(p, 121, "comparison:1");
    FAstNode *bitwise_or_, *comp_op_bitwise_ors_;
    (bitwise_or_ = bitwise_or(p)) &&
    (comp_op_bitwise_ors_ = comparison_1_2_loop(p))
    ? (res = AST_NODE_2(p, bitwise_or_, comp_op_bitwise_ors_)) : 0;
    EXIT_FRAME(p);
}

// comp_op bitwise_or
RULE(comparison_1_2) {
    ENTER_FRAME(p, 122, "comparison:1:2");
    FAstNode *comp_op_, *bitwise_or_;
    (comp_op_ = comp_op(p)) &&
    (bitwise_or_ = bitwise_or(p))
    ? (res = AST_NODE_2(p, comp_op_, bitwise_or_)) : 0;
    EXIT_FRAME(p);
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
RULE(comp_op) {
    ENTER_FRAME(p, 123, "comp_op");
    (res = AST_CONSUME(p, 19, "<")) ||
    (res = AST_CONSUME(p, 20, ">")) ||
    (res = AST_CONSUME(p, 31, "==")) ||
    (res = AST_CONSUME(p, 34, ">=")) ||
    (res = AST_CONSUME(p, 33, "<=")) ||
    (res = AST_CONSUME(p, 32, "!=")) ||
    (res = AST_CONSUME(p, 63, "in")) ||
    (res = comp_op_8(p)) ||
    (res = AST_CONSUME(p, 62, "is")) ||
    (res = comp_op_10(p));
    EXIT_FRAME(p);
}

// 'not' 'in'
RULE(comp_op_8) {
    ENTER_FRAME(p, 124, "comp_op:8");
    (AST_CONSUME(p, 61, "not")) &&
    (AST_CONSUME(p, 63, "in"));
    EXIT_FRAME(p);
}

// 'is' 'not'
RULE(comp_op_10) {
    ENTER_FRAME(p, 125, "comp_op:10");
    (AST_CONSUME(p, 62, "is")) &&
    (AST_CONSUME(p, 61, "not"));
    EXIT_FRAME(p);
}

// bitwise_or:
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
RULE(bitwise_or) {
    ENTER_FRAME(p, 126, "bitwise_or");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (res = bitwise_or_1(p)) ||
    (res = bitwise_xor(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// bitwise_or '|' bitwise_xor
RULE(bitwise_or_1) {
    ENTER_FRAME(p, 127, "bitwise_or:1");
    FAstNode *bitwise_or_, *bitwise_xor_;
    (bitwise_or_ = bitwise_or(p)) &&
    (AST_CONSUME(p, 27, "|")) &&
    (bitwise_xor_ = bitwise_xor(p))
    ? (res = AST_NODE_2(p, bitwise_or_, bitwise_xor_)) : 0;
    EXIT_FRAME(p);
}

// bitwise_xor:
//     | bitwise_xor '^' bitwise_and
//     | bitwise_and
RULE(bitwise_xor) {
    ENTER_FRAME(p, 128, "bitwise_xor");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (res = bitwise_xor_1(p)) ||
    (res = bitwise_and(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// bitwise_xor '^' bitwise_and
RULE(bitwise_xor_1) {
    ENTER_FRAME(p, 129, "bitwise_xor:1");
    FAstNode *bitwise_xor_, *bitwise_and_;
    (bitwise_xor_ = bitwise_xor(p)) &&
    (AST_CONSUME(p, 30, "^")) &&
    (bitwise_and_ = bitwise_and(p))
    ? (res = AST_NODE_2(p, bitwise_xor_, bitwise_and_)) : 0;
    EXIT_FRAME(p);
}

// bitwise_and:
//     | bitwise_and '&' shift_expr
//     | shift_expr
RULE(bitwise_and) {
    ENTER_FRAME(p, 130, "bitwise_and");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (res = bitwise_and_1(p)) ||
    (res = shift_expr(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// bitwise_and '&' shift_expr
RULE(bitwise_and_1) {
    ENTER_FRAME(p, 131, "bitwise_and:1");
    FAstNode *bitwise_and_, *shift_expr_;
    (bitwise_and_ = bitwise_and(p)) &&
    (AST_CONSUME(p, 28, "&")) &&
    (shift_expr_ = shift_expr(p))
    ? (res = AST_NODE_2(p, bitwise_and_, shift_expr_)) : 0;
    EXIT_FRAME(p);
}

// shift_expr:
//     | shift_expr '<<' sum
//     | shift_expr '>>' sum
//     | sum
RULE(shift_expr) {
    ENTER_FRAME(p, 132, "shift_expr");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (res = shift_expr_1(p)) ||
    (res = shift_expr_2(p)) ||
    (res = sum(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// shift_expr '<<' sum
RULE(shift_expr_1) {
    ENTER_FRAME(p, 133, "shift_expr:1");
    FAstNode *shift_expr_, *sum_;
    (shift_expr_ = shift_expr(p)) &&
    (AST_CONSUME(p, 48, "<<")) &&
    (sum_ = sum(p))
    ? (res = AST_NODE_2(p, shift_expr_, sum_)) : 0;
    EXIT_FRAME(p);
}

// shift_expr '>>' sum
RULE(shift_expr_2) {
    ENTER_FRAME(p, 134, "shift_expr:2");
    FAstNode *shift_expr_, *sum_;
    (shift_expr_ = shift_expr(p)) &&
    (AST_CONSUME(p, 49, ">>")) &&
    (sum_ = sum(p))
    ? (res = AST_NODE_2(p, shift_expr_, sum_)) : 0;
    EXIT_FRAME(p);
}

// sum:
//     | sum '+' term
//     | sum '-' term
//     | term
RULE(sum) {
    ENTER_FRAME(p, 135, "sum");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (res = sum_1(p)) ||
    (res = sum_2(p)) ||
    (res = term(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// sum '+' term
RULE(sum_1) {
    ENTER_FRAME(p, 136, "sum:1");
    FAstNode *sum_, *term_;
    (sum_ = sum(p)) &&
    (AST_CONSUME(p, 21, "+")) &&
    (term_ = term(p))
    ? (res = AST_NODE_2(p, sum_, term_)) : 0;
    EXIT_FRAME(p);
}

// sum '-' term
RULE(sum_2) {
    ENTER_FRAME(p, 137, "sum:2");
    FAstNode *sum_, *term_;
    (sum_ = sum(p)) &&
    (AST_CONSUME(p, 22, "-")) &&
    (term_ = term(p))
    ? (res = AST_NODE_2(p, sum_, term_)) : 0;
    EXIT_FRAME(p);
}

// term:
//     | term '*' pipe_expr
//     | term '/' pipe_expr
//     | term '%' pipe_expr
//     | term '//' pipe_expr
//     | term '@' pipe_expr
//     | pipe_expr
RULE(term) {
    ENTER_FRAME(p, 138, "term");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (res = term_1(p)) ||
    (res = term_2(p)) ||
    (res = term_3(p)) ||
    (res = term_4(p)) ||
    (res = term_5(p)) ||
    (res = pipe_expr(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// term '*' pipe_expr
RULE(term_1) {
    ENTER_FRAME(p, 139, "term:1");
    FAstNode *term_, *pipe_expr_;
    (term_ = term(p)) &&
    (AST_CONSUME(p, 23, "*")) &&
    (pipe_expr_ = pipe_expr(p))
    ? (res = AST_NODE_2(p, term_, pipe_expr_)) : 0;
    EXIT_FRAME(p);
}

// term '/' pipe_expr
RULE(term_2) {
    ENTER_FRAME(p, 140, "term:2");
    FAstNode *term_, *pipe_expr_;
    (term_ = term(p)) &&
    (AST_CONSUME(p, 24, "/")) &&
    (pipe_expr_ = pipe_expr(p))
    ? (res = AST_NODE_2(p, term_, pipe_expr_)) : 0;
    EXIT_FRAME(p);
}

// term '%' pipe_expr
RULE(term_3) {
    ENTER_FRAME(p, 141, "term:3");
    FAstNode *term_, *pipe_expr_;
    (term_ = term(p)) &&
    (AST_CONSUME(p, 25, "%")) &&
    (pipe_expr_ = pipe_expr(p))
    ? (res = AST_NODE_2(p, term_, pipe_expr_)) : 0;
    EXIT_FRAME(p);
}

// term '//' pipe_expr
RULE(term_4) {
    ENTER_FRAME(p, 142, "term:4");
    FAstNode *term_, *pipe_expr_;
    (term_ = term(p)) &&
    (AST_CONSUME(p, 37, "//")) &&
    (pipe_expr_ = pipe_expr(p))
    ? (res = AST_NODE_2(p, term_, pipe_expr_)) : 0;
    EXIT_FRAME(p);
}

// term '@' pipe_expr
RULE(term_5) {
    ENTER_FRAME(p, 143, "term:5");
    FAstNode *term_, *pipe_expr_;
    (term_ = term(p)) &&
    (AST_CONSUME(p, 26, "@")) &&
    (pipe_expr_ = pipe_expr(p))
    ? (res = AST_NODE_2(p, term_, pipe_expr_)) : 0;
    EXIT_FRAME(p);
}

// pipe_expr:
//     | pipe_expr '->' factor
//     | factor
RULE(pipe_expr) {
    ENTER_FRAME(p, 144, "pipe_expr");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (res = pipe_expr_1(p)) ||
    (res = factor(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// pipe_expr '->' factor
RULE(pipe_expr_1) {
    ENTER_FRAME(p, 145, "pipe_expr:1");
    FAstNode *pipe_expr_, *factor_;
    (pipe_expr_ = pipe_expr(p)) &&
    (AST_CONSUME(p, 35, "->")) &&
    (factor_ = factor(p))
    ? (res = AST_NODE_2(p, pipe_expr_, factor_)) : 0;
    EXIT_FRAME(p);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
RULE(factor) {
    ENTER_FRAME(p, 146, "factor");
    (res = factor_1(p)) ||
    (res = factor_2(p)) ||
    (res = factor_3(p)) ||
    (res = power(p));
    EXIT_FRAME(p);
}

// '+' factor
RULE(factor_1) {
    ENTER_FRAME(p, 147, "factor:1");
    FAstNode *factor_;
    (AST_CONSUME(p, 21, "+")) &&
    (factor_ = factor(p))
    ? (res = AST_NODE_1(p, factor_)) : 0;
    EXIT_FRAME(p);
}

// '-' factor
RULE(factor_2) {
    ENTER_FRAME(p, 148, "factor:2");
    FAstNode *factor_;
    (AST_CONSUME(p, 22, "-")) &&
    (factor_ = factor(p))
    ? (res = AST_NODE_1(p, factor_)) : 0;
    EXIT_FRAME(p);
}

// '~' factor
RULE(factor_3) {
    ENTER_FRAME(p, 149, "factor:3");
    FAstNode *factor_;
    (AST_CONSUME(p, 29, "~")) &&
    (factor_ = factor(p))
    ? (res = AST_NODE_1(p, factor_)) : 0;
    EXIT_FRAME(p);
}

// power:
//     | primary '**' factor
//     | primary
RULE(power) {
    ENTER_FRAME(p, 150, "power");
    (res = power_1(p)) ||
    (res = primary(p));
    EXIT_FRAME(p);
}

// primary '**' factor
RULE(power_1) {
    ENTER_FRAME(p, 151, "power:1");
    FAstNode *primary_, *factor_;
    (primary_ = primary(p)) &&
    (AST_CONSUME(p, 38, "**")) &&
    (factor_ = factor(p))
    ? (res = AST_NODE_2(p, primary_, factor_)) : 0;
    EXIT_FRAME(p);
}

// primary:
//     | primary '.' NAME
//     | primary invocation
//     | primary subscript
//     | atom
RULE(primary) {
    ENTER_FRAME(p, 152, "primary");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (res = primary_1(p)) ||
    (res = primary_2(p)) ||
    (res = primary_3(p)) ||
    (res = atom(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

// primary '.' NAME
RULE(primary_1) {
    ENTER_FRAME(p, 153, "primary:1");
    FAstNode *primary_, *name_;
    (primary_ = primary(p)) &&
    (AST_CONSUME(p, 6, ".")) &&
    (name_ = AST_CONSUME(p, 3, "NAME"))
    ? (res = AST_NODE_2(p, primary_, name_)) : 0;
    EXIT_FRAME(p);
}

// primary invocation
RULE(primary_2) {
    ENTER_FRAME(p, 154, "primary:2");
    FAstNode *primary_, *invocation_;
    (primary_ = primary(p)) &&
    (invocation_ = invocation(p))
    ? (res = AST_NODE_2(p, primary_, invocation_)) : 0;
    EXIT_FRAME(p);
}

// primary subscript
RULE(primary_3) {
    ENTER_FRAME(p, 155, "primary:3");
    FAstNode *primary_, *subscript_;
    (primary_ = primary(p)) &&
    (subscript_ = subscript(p))
    ? (res = AST_NODE_2(p, primary_, subscript_)) : 0;
    EXIT_FRAME(p);
}

// tuple_atom:
//     | '(' [named_expr_list] ')'
RULE(tuple_atom) {
    ENTER_FRAME(p, 156, "tuple_atom");
    FAstNode *named_expr_list_;
    (AST_CONSUME(p, 13, "(")) &&
    (named_expr_list_ = OPTIONAL(named_expr_list(p))) &&
    (AST_CONSUME(p, 14, ")"))
    ? (res = AST_NODE_1(p, named_expr_list_)) : 0;
    EXIT_FRAME(p);
}

// list_iter:
//     | '[' expr_or_star iterator ']'
RULE(list_iter) {
    ENTER_FRAME(p, 157, "list_iter");
    FAstNode *expr_or_star_, *iterator_;
    (AST_CONSUME(p, 17, "[")) &&
    (expr_or_star_ = expr_or_star(p)) &&
    (iterator_ = iterator(p)) &&
    (AST_CONSUME(p, 18, "]"))
    ? (res = AST_NODE_2(p, expr_or_star_, iterator_)) : 0;
    EXIT_FRAME(p);
}

// list_atom:
//     | '[' [named_expr_list] ']'
RULE(list_atom) {
    ENTER_FRAME(p, 158, "list_atom");
    FAstNode *named_expr_list_;
    (AST_CONSUME(p, 17, "[")) &&
    (named_expr_list_ = OPTIONAL(named_expr_list(p))) &&
    (AST_CONSUME(p, 18, "]"))
    ? (res = AST_NODE_1(p, named_expr_list_)) : 0;
    EXIT_FRAME(p);
}

// set_atom:
//     | '{' [exprlist_star] '}'
RULE(set_atom) {
    ENTER_FRAME(p, 159, "set_atom");
    FAstNode *exprlist_star_;
    (AST_CONSUME(p, 15, "{")) &&
    (exprlist_star_ = OPTIONAL(exprlist_star(p))) &&
    (AST_CONSUME(p, 16, "}"))
    ? (res = AST_NODE_1(p, exprlist_star_)) : 0;
    EXIT_FRAME(p);
}

// dict_iter:
//     | '{' dict_item iterator '}'
RULE(dict_iter) {
    ENTER_FRAME(p, 160, "dict_iter");
    FAstNode *dict_item_, *iterator_;
    (AST_CONSUME(p, 15, "{")) &&
    (dict_item_ = dict_item(p)) &&
    (iterator_ = iterator(p)) &&
    (AST_CONSUME(p, 16, "}"))
    ? (res = AST_NODE_2(p, dict_item_, iterator_)) : 0;
    EXIT_FRAME(p);
}

// dict_atom:
//     | '{' [dict_items] '}'
RULE(dict_atom) {
    ENTER_FRAME(p, 161, "dict_atom");
    FAstNode *dict_items_;
    (AST_CONSUME(p, 15, "{")) &&
    (dict_items_ = OPTIONAL(dict_items(p))) &&
    (AST_CONSUME(p, 16, "}"))
    ? (res = AST_NODE_1(p, dict_items_)) : 0;
    EXIT_FRAME(p);
}

// builder:
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
RULE(builder) {
    ENTER_FRAME(p, 162, "builder");
    (res = builder_1(p)) ||
    (res = builder_2(p));
    EXIT_FRAME(p);
}

// NAME simple_args ':' expr
RULE(builder_1) {
    ENTER_FRAME(p, 163, "builder:1");
    FAstNode *name_, *simple_args_, *expr_;
    (name_ = AST_CONSUME(p, 3, "NAME")) &&
    (simple_args_ = simple_args(p)) &&
    (AST_CONSUME(p, 9, ":")) &&
    (expr_ = expr(p))
    ? (res = AST_NODE_3(p, name_, simple_args_, expr_)) : 0;
    EXIT_FRAME(p);
}

// NAME [builder_hint] [builder_args] block_suite
RULE(builder_2) {
    ENTER_FRAME(p, 164, "builder:2");
    FAstNode *name_, *builder_hint_, *builder_args_, *block_suite_;
    (name_ = AST_CONSUME(p, 3, "NAME")) &&
    (builder_hint_ = OPTIONAL(builder_hint(p))) &&
    (builder_args_ = OPTIONAL(builder_args(p))) &&
    (block_suite_ = block_suite(p))
    ? (res = AST_NODE_4(p, name_, builder_hint_, builder_args_, block_suite_)) : 0;
    EXIT_FRAME(p);
}

// atom:
//     | tuple_atom
//     | list_iter
//     | list_atom
//     | set_atom
//     | dict_iter
//     | dict_atom
//     | builder
//     | NAME
//     | NUMBER
//     | STRING
//     | 'None'
//     | 'True'
//     | 'False'
RULE(atom) {
    ENTER_FRAME(p, 165, "atom");
    (res = tuple_atom(p)) ||
    (res = list_iter(p)) ||
    (res = list_atom(p)) ||
    (res = set_atom(p)) ||
    (res = dict_iter(p)) ||
    (res = dict_atom(p)) ||
    (res = builder(p)) ||
    (res = AST_CONSUME(p, 3, "NAME")) ||
    (res = AST_CONSUME(p, 4, "NUMBER")) ||
    (res = AST_CONSUME(p, 5, "STRING")) ||
    (res = AST_CONSUME(p, 81, "None")) ||
    (res = AST_CONSUME(p, 82, "True")) ||
    (res = AST_CONSUME(p, 83, "False"));
    EXIT_FRAME(p);
}
