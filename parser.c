#include "include/internal/peg_macros.h"


static FAstNode *single_input(FParser *);
static FAstNode *single_input_4(FParser *);
static FAstNode *file_input(FParser *);
static FAstNode *eval_input(FParser *);
static FAstNode *stmt_list(FParser *);
static FAstNode *stmt(FParser *);
static FAstNode *stmt_1(FParser *);
static FAstNode *simple_stmt(FParser *);
static FAstNode *small_stmt(FParser *);
static FAstNode *del_stmt(FParser *);
static FAstNode *return_stmt(FParser *);
static FAstNode *raise_stmt(FParser *);
static FAstNode *raise_stmt_3(FParser *);
static FAstNode *nonlocal_stmt(FParser *);
static FAstNode *assert_stmt(FParser *);
static FAstNode *assert_stmt_3(FParser *);
static FAstNode *name_list(FParser *);
static FAstNode *star_expr(FParser *);
static FAstNode *exprlist(FParser *);
static FAstNode *target(FParser *);
static FAstNode *target_1(FParser *);
static FAstNode *target_2(FParser *);
static FAstNode *target_4(FParser *);
static FAstNode *targetlist_sp(FParser *);
static FAstNode *t_primary(FParser *);
static FAstNode *t_primary_1(FParser *);
static FAstNode *t_primary_2(FParser *);
static FAstNode *t_primary_3(FParser *);
static FAstNode *t_primary_4(FParser *);
static FAstNode *t_lookahead(FParser *);
static FAstNode *targetlist(FParser *);
static FAstNode *expr_or_star(FParser *);
static FAstNode *exprlist_star(FParser *);
static FAstNode *subscript(FParser *);
static FAstNode *slicelist(FParser *);
static FAstNode *slice(FParser *);
static FAstNode *slice_1(FParser *);
static FAstNode *slice_expr(FParser *);
static FAstNode *dict_item(FParser *);
static FAstNode *dict_item_1(FParser *);
static FAstNode *dict_item_2(FParser *);
static FAstNode *dict_items(FParser *);
static FAstNode *list_item(FParser *);
static FAstNode *list_items(FParser *);
static FAstNode *set_items(FParser *);
static FAstNode *as_name(FParser *);
static FAstNode *iter_for(FParser *);
static FAstNode *iter_if(FParser *);
static FAstNode *iterator(FParser *);
static FAstNode *list_iterator(FParser *);
static FAstNode *dict_iterator(FParser *);
static FAstNode *assignment(FParser *);
static FAstNode *pubassign(FParser *);
static FAstNode *annassign(FParser *);
static FAstNode *annassign_4(FParser *);
static FAstNode *augassign(FParser *);
static FAstNode *simple_assign(FParser *);
static FAstNode *simple_assign_1(FParser *);
static FAstNode *augassign_op(FParser *);
static FAstNode *import_name(FParser *);
static FAstNode *import_from(FParser *);
static FAstNode *import_from_names(FParser *);
static FAstNode *import_from_names_2(FParser *);
static FAstNode *import_from_items(FParser *);
static FAstNode *import_as_names_sp(FParser *);
static FAstNode *import_as_name(FParser *);
static FAstNode *dotted_as_name(FParser *);
static FAstNode *import_as_names(FParser *);
static FAstNode *dotted_as_names(FParser *);
static FAstNode *dotted_name(FParser *);
static FAstNode *compound_stmt(FParser *);
static FAstNode *if_stmt(FParser *);
static FAstNode *elif_stmt(FParser *);
static FAstNode *while_stmt(FParser *);
static FAstNode *for_stmt(FParser *);
static FAstNode *try_stmt(FParser *);
static FAstNode *try_stmt_3(FParser *);
static FAstNode *with_stmt(FParser *);
static FAstNode *expr_as_name(FParser *);
static FAstNode *block_suite(FParser *);
static FAstNode *block_suite_1(FParser *);
static FAstNode *block_suite_2(FParser *);
static FAstNode *suite(FParser *);
static FAstNode *suite_1(FParser *);
static FAstNode *else_suite(FParser *);
static FAstNode *finally_suite(FParser *);
static FAstNode *except_clause(FParser *);
static FAstNode *except_suite(FParser *);
static FAstNode *invocation(FParser *);
static FAstNode *call_arg_list(FParser *);
static FAstNode *call_arg(FParser *);
static FAstNode *call_arg_1(FParser *);
static FAstNode *call_arg_2(FParser *);
static FAstNode *call_arg_3(FParser *);
static FAstNode *call_arg_4(FParser *);
static FAstNode *typed_arg_list(FParser *);
static FAstNode *full_arg_list(FParser *);
static FAstNode *full_arg_list_2(FParser *);
static FAstNode *full_arg_list_2_2(FParser *);
static FAstNode *args_kwargs(FParser *);
static FAstNode *args_kwargs_3(FParser *);
static FAstNode *args_kwargs_4(FParser *);
static FAstNode *kwargs(FParser *);
static FAstNode *default_arg(FParser *);
static FAstNode *default_arg_2(FParser *);
static FAstNode *typed_arg(FParser *);
static FAstNode *typed_arg_2(FParser *);
static FAstNode *simple_arg(FParser *);
static FAstNode *simple_arg_2(FParser *);
static FAstNode *simple_args(FParser *);
static FAstNode *builder_hint(FParser *);
static FAstNode *builder_args(FParser *);
static FAstNode *builder_args_2(FParser *);
static FAstNode *named_expr(FParser *);
static FAstNode *named_expr_1(FParser *);
static FAstNode *conditional(FParser *);
static FAstNode *expr(FParser *);
static FAstNode *disjunction(FParser *);
static FAstNode *disjunction_1(FParser *);
static FAstNode *conjunction(FParser *);
static FAstNode *conjunction_1(FParser *);
static FAstNode *inversion(FParser *);
static FAstNode *inversion_1(FParser *);
static FAstNode *comparison(FParser *);
static FAstNode *comparison_1(FParser *);
static FAstNode *comparison_1_2(FParser *);
static FAstNode *comp_op(FParser *);
static FAstNode *comp_op_8(FParser *);
static FAstNode *comp_op_10(FParser *);
static FAstNode *bitwise_or(FParser *);
static FAstNode *bitwise_or_1(FParser *);
static FAstNode *bitwise_xor(FParser *);
static FAstNode *bitwise_xor_1(FParser *);
static FAstNode *bitwise_and(FParser *);
static FAstNode *bitwise_and_1(FParser *);
static FAstNode *shift_expr(FParser *);
static FAstNode *shift_expr_1(FParser *);
static FAstNode *shift_expr_2(FParser *);
static FAstNode *sum(FParser *);
static FAstNode *sum_1(FParser *);
static FAstNode *sum_2(FParser *);
static FAstNode *term(FParser *);
static FAstNode *term_1(FParser *);
static FAstNode *term_2(FParser *);
static FAstNode *term_3(FParser *);
static FAstNode *term_4(FParser *);
static FAstNode *term_5(FParser *);
static FAstNode *pipe_expr(FParser *);
static FAstNode *pipe_expr_1(FParser *);
static FAstNode *factor(FParser *);
static FAstNode *factor_1(FParser *);
static FAstNode *factor_2(FParser *);
static FAstNode *factor_3(FParser *);
static FAstNode *power(FParser *);
static FAstNode *power_1(FParser *);
static FAstNode *primary(FParser *);
static FAstNode *primary_1(FParser *);
static FAstNode *primary_2(FParser *);
static FAstNode *primary_3(FParser *);
static FAstNode *tuple_atom(FParser *);
static FAstNode *list_iterable(FParser *);
static FAstNode *list_atom(FParser *);
static FAstNode *set_atom(FParser *);
static FAstNode *dict_iterable(FParser *);
static FAstNode *dict_atom(FParser *);
static FAstNode *builder(FParser *);
static FAstNode *builder_1(FParser *);
static FAstNode *builder_2(FParser *);
static FAstNode *atom(FParser *);



// single_input:
//     | NEWLINE
//     | ENDMARKER
//     | simple_stmt
//     | compound_stmt NEWLINE
static FAstNode *single_input(FParser *p) {
    frame_t f = enter(p, 1, FUNC);
    ENTER(1);
    (a = consume(p, 2, "NEWLINE")) ||
    (a = consume(p, 1, "ENDMARKER")) ||
    (a = simple_stmt(p)) ||
    (a = single_input_4(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *single_input_4(FParser *p) {
    frame_t f = enter(p, 2, FUNC);
    ENTER(2);
    (a = compound_stmt(p)) &&
    (b = consume(p, 2, "NEWLINE"))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// file_input:
//     | [stmt_list] ENDMARKER
static FAstNode *file_input(FParser *p) {
    frame_t f = enter(p, 3, FUNC);
    ENTER(3);
    (a = stmt_list(p), 1) &&
    (b = consume(p, 1, "ENDMARKER"))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// eval_input:
//     | exprlist NEWLINE* ENDMARKER
static FAstNode *eval_input(FParser *p) {
    frame_t f = enter(p, 4, FUNC);
    ENTER(4);
    (a = exprlist(p)) &&
    (b = TOKEN_SEQ_OR_NONE(p, 2, "NEWLINE")) &&
    (c = consume(p, 1, "ENDMARKER"))
    ? (r = NODE_3()) : 0; 
    return exit(p, &f, r), r;
}

// stmt_list:
//     | stmt+
static FAstNode *stmt_list(FParser *p) {
    frame_t f = enter(p, 5, FUNC);
    ENTER(5);
    (a = sequence(p, stmt, 0))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// stmt:
//     | (simple_stmt | compound_stmt) NEWLINE
static FAstNode *stmt(FParser *p) {
    frame_t f = enter(p, 6, FUNC);
    ENTER(6);
    (a = stmt_1(p)) &&
    (b = consume(p, 2, "NEWLINE"))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *stmt_1(FParser *p) {
    frame_t f = enter(p, 7, FUNC);
    ENTER(7);
    (a = simple_stmt(p)) ||
    (a = compound_stmt(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

// simple_stmt:
//     | ';'.small_stmt+ [';']
static FAstNode *simple_stmt(FParser *p) {
    frame_t f = enter(p, 8, FUNC);
    ENTER(8);
    (a = DELIMITED(p, 12, ";", small_stmt)) &&
    (b = consume(p, 12, ";"), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
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
static FAstNode *small_stmt(FParser *p) {
    frame_t f = enter(p, 9, FUNC);
    ENTER(9);
    (a = consume(p, 64, "pass")) ||
    (a = consume(p, 74, "break")) ||
    (a = consume(p, 73, "continue")) ||
    (a = return_stmt(p)) ||
    (a = raise_stmt(p)) ||
    (a = del_stmt(p)) ||
    (a = nonlocal_stmt(p)) ||
    (a = assert_stmt(p)) ||
    (a = import_name(p)) ||
    (a = import_from(p)) ||
    (a = assignment(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

// del_stmt:
//     | 'del' targetlist
static FAstNode *del_stmt(FParser *p) {
    frame_t f = enter(p, 10, FUNC);
    ENTER(10);
    (consume(p, 79, "del")) &&
    (a = targetlist(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// return_stmt:
//     | 'return' [exprlist_star]
static FAstNode *return_stmt(FParser *p) {
    frame_t f = enter(p, 11, FUNC);
    ENTER(11);
    (consume(p, 54, "return")) &&
    (a = exprlist_star(p), 1)
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// raise_stmt:
//     | 'raise' expr ['from' expr]
static FAstNode *raise_stmt(FParser *p) {
    frame_t f = enter(p, 12, FUNC);
    ENTER(12);
    (consume(p, 78, "raise")) &&
    (a = expr(p)) &&
    (b = raise_stmt_3(p), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *raise_stmt_3(FParser *p) {
    frame_t f = enter(p, 13, FUNC);
    ENTER(13);
    (consume(p, 66, "from")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// nonlocal_stmt:
//     | 'nonlocal' name_list
static FAstNode *nonlocal_stmt(FParser *p) {
    frame_t f = enter(p, 14, FUNC);
    ENTER(14);
    (consume(p, 55, "nonlocal")) &&
    (a = name_list(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// assert_stmt:
//     | 'assert' expr [',' expr]
static FAstNode *assert_stmt(FParser *p) {
    frame_t f = enter(p, 15, FUNC);
    ENTER(15);
    (consume(p, 80, "assert")) &&
    (a = expr(p)) &&
    (b = assert_stmt_3(p), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *assert_stmt_3(FParser *p) {
    frame_t f = enter(p, 16, FUNC);
    ENTER(16);
    (consume(p, 7, ",")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// name_list:
//     | ','.NAME+
static FAstNode *name_list(FParser *p) {
    frame_t f = enter(p, 17, FUNC);
    ENTER(17);
    (a = TOKEN_DELIMITED(p, 7, ",", 3, "NAME"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// star_expr:
//     | '*' bitwise_or
static FAstNode *star_expr(FParser *p) {
    frame_t f = enter(p, 18, FUNC);
    ENTER(18);
    (consume(p, 23, "*")) &&
    (a = bitwise_or(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// exprlist:
//     | ','.expr+ [',']
static FAstNode *exprlist(FParser *p) {
    frame_t f = enter(p, 19, FUNC);
    ENTER(19);
    (a = DELIMITED(p, 7, ",", expr)) &&
    (b = consume(p, 7, ","), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// target:
//     | t_primary '.' NAME !t_lookahead
//     | t_primary subscript !t_lookahead
//     | NAME
//     | '(' targetlist_sp ')'
static FAstNode *target(FParser *p) {
    frame_t f = enter(p, 20, FUNC);
    ENTER(20);
    (a = target_1(p)) ||
    (a = target_2(p)) ||
    (a = consume(p, 3, "NAME")) ||
    (a = target_4(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *target_1(FParser *p) {
    frame_t f = enter(p, 21, FUNC);
    ENTER(21);
    (a = t_primary(p)) &&
    (consume(p, 6, ".")) &&
    (b = consume(p, 3, "NAME")) &&
    (!TEST(t_lookahead(p)))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *target_2(FParser *p) {
    frame_t f = enter(p, 22, FUNC);
    ENTER(22);
    (a = t_primary(p)) &&
    (b = subscript(p)) &&
    (!TEST(t_lookahead(p)))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *target_4(FParser *p) {
    frame_t f = enter(p, 23, FUNC);
    ENTER(23);
    (consume(p, 13, "(")) &&
    (a = targetlist_sp(p)) &&
    (consume(p, 14, ")"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// targetlist_sp (allow_whitespace=true):
//     | targetlist
static FAstNode *targetlist_sp(FParser *p) {
    frame_t f = enter(p, 24, FUNC);
    ENTER(24);
    WS_PUSH_1();
    (a = targetlist(p))
    ? (r = NODE_1()) : 0; 
    WS_POP();
    return exit(p, &f, r), r;
}

// t_primary (left_recursive):
//     | t_primary '.' NAME &t_lookahead
//     | t_primary invocation &t_lookahead
//     | t_primary subscript &t_lookahead
//     | atom &t_lookahead
static FAstNode *t_primary(FParser *p) {
    frame_t f = enter(p, 25, FUNC);
    ENTER(25);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = t_primary_1(p)) ||
    (a = t_primary_2(p)) ||
    (a = t_primary_3(p)) ||
    (a = t_primary_4(p));
    EXIT_LEFT_RECURSION();
    return exit(p, &f, r), r;
}

static FAstNode *t_primary_1(FParser *p) {
    frame_t f = enter(p, 26, FUNC);
    ENTER(26);
    (a = t_primary(p)) &&
    (consume(p, 6, ".")) &&
    (b = consume(p, 3, "NAME")) &&
    (TEST(t_lookahead(p)))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *t_primary_2(FParser *p) {
    frame_t f = enter(p, 27, FUNC);
    ENTER(27);
    (a = t_primary(p)) &&
    (b = invocation(p)) &&
    (TEST(t_lookahead(p)))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *t_primary_3(FParser *p) {
    frame_t f = enter(p, 28, FUNC);
    ENTER(28);
    (a = t_primary(p)) &&
    (b = subscript(p)) &&
    (TEST(t_lookahead(p)))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *t_primary_4(FParser *p) {
    frame_t f = enter(p, 29, FUNC);
    ENTER(29);
    (a = atom(p)) &&
    (TEST(t_lookahead(p)))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// t_lookahead:
//     | '.'
//     | '('
//     | '['
static FAstNode *t_lookahead(FParser *p) {
    frame_t f = enter(p, 30, FUNC);
    ENTER(30);
    (a = consume(p, 6, ".")) ||
    (a = consume(p, 13, "(")) ||
    (a = consume(p, 17, "["))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

// targetlist:
//     | ','.target+ [',']
static FAstNode *targetlist(FParser *p) {
    frame_t f = enter(p, 31, FUNC);
    ENTER(31);
    (a = DELIMITED(p, 7, ",", target)) &&
    (b = consume(p, 7, ","), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// expr_or_star:
//     | star_expr
//     | expr
static FAstNode *expr_or_star(FParser *p) {
    frame_t f = enter(p, 32, FUNC);
    ENTER(32);
    (a = star_expr(p)) ||
    (a = expr(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

// exprlist_star:
//     | ','.expr_or_star+ [',']
static FAstNode *exprlist_star(FParser *p) {
    frame_t f = enter(p, 33, FUNC);
    ENTER(33);
    (a = DELIMITED(p, 7, ",", expr_or_star)) &&
    (b = consume(p, 7, ","), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// subscript:
//     | '[' slicelist ']'
static FAstNode *subscript(FParser *p) {
    frame_t f = enter(p, 34, FUNC);
    ENTER(34);
    (consume(p, 17, "[")) &&
    (a = slicelist(p)) &&
    (consume(p, 18, "]"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// slicelist:
//     | ','.slice+ [',']
static FAstNode *slicelist(FParser *p) {
    frame_t f = enter(p, 35, FUNC);
    ENTER(35);
    (a = DELIMITED(p, 7, ",", slice)) &&
    (b = consume(p, 7, ","), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// slice:
//     | [expr] slice_expr [slice_expr]
//     | expr
static FAstNode *slice(FParser *p) {
    frame_t f = enter(p, 36, FUNC);
    ENTER(36);
    (a = slice_1(p)) ||
    (a = expr(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *slice_1(FParser *p) {
    frame_t f = enter(p, 37, FUNC);
    ENTER(37);
    (a = expr(p), 1) &&
    (b = slice_expr(p)) &&
    (c = slice_expr(p), 1)
    ? (r = NODE_3()) : 0; 
    return exit(p, &f, r), r;
}

// slice_expr:
//     | ':' [expr]
static FAstNode *slice_expr(FParser *p) {
    frame_t f = enter(p, 38, FUNC);
    ENTER(38);
    (consume(p, 9, ":")) &&
    (a = expr(p), 1)
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// dict_item:
//     | expr ':' expr
//     | '**' bitwise_or
static FAstNode *dict_item(FParser *p) {
    frame_t f = enter(p, 39, FUNC);
    ENTER(39);
    (a = dict_item_1(p)) ||
    (a = dict_item_2(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *dict_item_1(FParser *p) {
    frame_t f = enter(p, 40, FUNC);
    ENTER(40);
    (a = expr(p)) &&
    (consume(p, 9, ":")) &&
    (b = expr(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *dict_item_2(FParser *p) {
    frame_t f = enter(p, 41, FUNC);
    ENTER(41);
    (consume(p, 38, "**")) &&
    (a = bitwise_or(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// dict_items (allow_whitespace=true):
//     | ','.dict_item+ [',']
static FAstNode *dict_items(FParser *p) {
    frame_t f = enter(p, 42, FUNC);
    ENTER(42);
    WS_PUSH_1();
    (a = DELIMITED(p, 7, ",", dict_item)) &&
    (b = consume(p, 7, ","), 1)
    ? (r = NODE_2()) : 0; 
    WS_POP();
    return exit(p, &f, r), r;
}

// list_item:
//     | star_expr
//     | named_expr
static FAstNode *list_item(FParser *p) {
    frame_t f = enter(p, 43, FUNC);
    ENTER(43);
    (a = star_expr(p)) ||
    (a = named_expr(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

// list_items (allow_whitespace=true):
//     | ','.list_item+ [',']
static FAstNode *list_items(FParser *p) {
    frame_t f = enter(p, 44, FUNC);
    ENTER(44);
    WS_PUSH_1();
    (a = DELIMITED(p, 7, ",", list_item)) &&
    (b = consume(p, 7, ","), 1)
    ? (r = NODE_2()) : 0; 
    WS_POP();
    return exit(p, &f, r), r;
}

// set_items (allow_whitespace=true):
//     | exprlist_star
static FAstNode *set_items(FParser *p) {
    frame_t f = enter(p, 45, FUNC);
    ENTER(45);
    WS_PUSH_1();
    (a = exprlist_star(p))
    ? (r = NODE_1()) : 0; 
    WS_POP();
    return exit(p, &f, r), r;
}

// as_name:
//     | 'as' NAME
static FAstNode *as_name(FParser *p) {
    frame_t f = enter(p, 46, FUNC);
    ENTER(46);
    (consume(p, 65, "as")) &&
    (a = consume(p, 3, "NAME"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// iter_for:
//     | 'for' targetlist 'in' disjunction [iter_if]
static FAstNode *iter_for(FParser *p) {
    frame_t f = enter(p, 47, FUNC);
    ENTER(47);
    (consume(p, 72, "for")) &&
    (a = targetlist(p)) &&
    (consume(p, 63, "in")) &&
    (b = disjunction(p)) &&
    (c = iter_if(p), 1)
    ? (r = NODE_3()) : 0; 
    return exit(p, &f, r), r;
}

// iter_if:
//     | 'if' named_expr
static FAstNode *iter_if(FParser *p) {
    frame_t f = enter(p, 48, FUNC);
    ENTER(48);
    (consume(p, 56, "if")) &&
    (a = named_expr(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// iterator:
//     | iter_for* 'for' targetlist [iter_if]
static FAstNode *iterator(FParser *p) {
    frame_t f = enter(p, 49, FUNC);
    ENTER(49);
    (a = sequence(p, iter_for, 1)) &&
    (consume(p, 72, "for")) &&
    (b = targetlist(p)) &&
    (c = iter_if(p), 1)
    ? (r = NODE_3()) : 0; 
    return exit(p, &f, r), r;
}

// list_iterator (allow_whitespace=true):
//     | expr_or_star iterator
static FAstNode *list_iterator(FParser *p) {
    frame_t f = enter(p, 50, FUNC);
    ENTER(50);
    WS_PUSH_1();
    (a = expr_or_star(p)) &&
    (b = iterator(p))
    ? (r = NODE_2()) : 0; 
    WS_POP();
    return exit(p, &f, r), r;
}

// dict_iterator (allow_whitespace=true):
//     | dict_item iterator
static FAstNode *dict_iterator(FParser *p) {
    frame_t f = enter(p, 51, FUNC);
    ENTER(51);
    WS_PUSH_1();
    (a = dict_item(p)) &&
    (b = iterator(p))
    ? (r = NODE_2()) : 0; 
    WS_POP();
    return exit(p, &f, r), r;
}

// assignment:
//     | pubassign
//     | annassign
//     | augassign
//     | simple_assign
static FAstNode *assignment(FParser *p) {
    frame_t f = enter(p, 52, FUNC);
    ENTER(52);
    (a = pubassign(p)) ||
    (a = annassign(p)) ||
    (a = augassign(p)) ||
    (a = simple_assign(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

// pubassign:
//     | '/' NAME '=' exprlist
static FAstNode *pubassign(FParser *p) {
    frame_t f = enter(p, 53, FUNC);
    ENTER(53);
    (consume(p, 24, "/")) &&
    (a = consume(p, 3, "NAME")) &&
    (consume(p, 8, "=")) &&
    (b = exprlist(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// annassign:
//     | target ':' expr ['=' exprlist]
static FAstNode *annassign(FParser *p) {
    frame_t f = enter(p, 54, FUNC);
    ENTER(54);
    (a = target(p)) &&
    (consume(p, 9, ":")) &&
    (b = expr(p)) &&
    (c = annassign_4(p), 1)
    ? (r = NODE_3()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *annassign_4(FParser *p) {
    frame_t f = enter(p, 55, FUNC);
    ENTER(55);
    (consume(p, 8, "=")) &&
    (a = exprlist(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// augassign:
//     | target augassign_op exprlist
static FAstNode *augassign(FParser *p) {
    frame_t f = enter(p, 56, FUNC);
    ENTER(56);
    (a = target(p)) &&
    (b = augassign_op(p)) &&
    (c = exprlist(p))
    ? (r = NODE_3()) : 0; 
    return exit(p, &f, r), r;
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
static FAstNode *simple_assign(FParser *p) {
    frame_t f = enter(p, 57, FUNC);
    ENTER(57);
    (a = sequence(p, simple_assign_1, 1)) &&
    (b = exprlist_star(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *simple_assign_1(FParser *p) {
    frame_t f = enter(p, 58, FUNC);
    ENTER(58);
    (a = targetlist(p)) &&
    (consume(p, 8, "="))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
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
static FAstNode *augassign_op(FParser *p) {
    frame_t f = enter(p, 59, FUNC);
    ENTER(59);
    (a = consume(p, 39, "+=")) ||
    (a = consume(p, 40, "-=")) ||
    (a = consume(p, 41, "*=")) ||
    (a = consume(p, 44, "@=")) ||
    (a = consume(p, 42, "/=")) ||
    (a = consume(p, 43, "%=")) ||
    (a = consume(p, 46, "&=")) ||
    (a = consume(p, 45, "|=")) ||
    (a = consume(p, 47, "^=")) ||
    (a = consume(p, 52, "<<=")) ||
    (a = consume(p, 53, ">>=")) ||
    (a = consume(p, 51, "**=")) ||
    (a = consume(p, 50, "//="))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

// import_name:
//     | 'import' dotted_as_names
static FAstNode *import_name(FParser *p) {
    frame_t f = enter(p, 60, FUNC);
    ENTER(60);
    (consume(p, 67, "import")) &&
    (a = dotted_as_names(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// import_from:
//     | 'from' import_from_names 'import' import_from_items
static FAstNode *import_from(FParser *p) {
    frame_t f = enter(p, 61, FUNC);
    ENTER(61);
    (consume(p, 66, "from")) &&
    (a = import_from_names(p)) &&
    (consume(p, 67, "import")) &&
    (b = import_from_items(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// import_from_names:
//     | dotted_name
//     | '.'+ [dotted_name]
static FAstNode *import_from_names(FParser *p) {
    frame_t f = enter(p, 62, FUNC);
    ENTER(62);
    (a = dotted_name(p)) ||
    (a = import_from_names_2(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *import_from_names_2(FParser *p) {
    frame_t f = enter(p, 63, FUNC);
    ENTER(63);
    (TOKEN_SEQUENCE(p, 6, ".")) &&
    (a = dotted_name(p), 1)
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// import_from_items:
//     | '*'
//     | import_as_names_sp
//     | import_as_names
static FAstNode *import_from_items(FParser *p) {
    frame_t f = enter(p, 64, FUNC);
    ENTER(64);
    (a = consume(p, 23, "*")) ||
    (a = import_as_names_sp(p)) ||
    (a = import_as_names(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

// import_as_names_sp (allow_whitespace=true):
//     | '(' import_as_names [','] ')'
static FAstNode *import_as_names_sp(FParser *p) {
    frame_t f = enter(p, 65, FUNC);
    ENTER(65);
    WS_PUSH_1();
    (consume(p, 13, "(")) &&
    (a = import_as_names(p)) &&
    (b = consume(p, 7, ","), 1) &&
    (consume(p, 14, ")"))
    ? (r = NODE_2()) : 0; 
    WS_POP();
    return exit(p, &f, r), r;
}

// import_as_name:
//     | NAME [as_name]
static FAstNode *import_as_name(FParser *p) {
    frame_t f = enter(p, 66, FUNC);
    ENTER(66);
    (a = consume(p, 3, "NAME")) &&
    (b = as_name(p), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// dotted_as_name:
//     | dotted_name [as_name]
static FAstNode *dotted_as_name(FParser *p) {
    frame_t f = enter(p, 67, FUNC);
    ENTER(67);
    (a = dotted_name(p)) &&
    (b = as_name(p), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// import_as_names:
//     | ','.import_as_name+
static FAstNode *import_as_names(FParser *p) {
    frame_t f = enter(p, 68, FUNC);
    ENTER(68);
    (a = DELIMITED(p, 7, ",", import_as_name))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// dotted_as_names:
//     | ','.dotted_as_name+
static FAstNode *dotted_as_names(FParser *p) {
    frame_t f = enter(p, 69, FUNC);
    ENTER(69);
    (a = DELIMITED(p, 7, ",", dotted_as_name))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// dotted_name:
//     | '.'.NAME+
static FAstNode *dotted_name(FParser *p) {
    frame_t f = enter(p, 70, FUNC);
    ENTER(70);
    (a = TOKEN_DELIMITED(p, 6, ".", 3, "NAME"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// compound_stmt:
//     | if_stmt
//     | while_stmt
//     | for_stmt
//     | try_stmt
//     | with_stmt
static FAstNode *compound_stmt(FParser *p) {
    frame_t f = enter(p, 71, FUNC);
    ENTER(71);
    (a = if_stmt(p)) ||
    (a = while_stmt(p)) ||
    (a = for_stmt(p)) ||
    (a = try_stmt(p)) ||
    (a = with_stmt(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
static FAstNode *if_stmt(FParser *p) {
    frame_t f = enter(p, 72, FUNC);
    ENTER(72);
    (consume(p, 56, "if")) &&
    (a = named_expr(p)) &&
    (b = suite(p)) &&
    (c = sequence(p, elif_stmt, 1)) &&
    (d = else_suite(p), 1)
    ? (r = NODE_4()) : 0; 
    return exit(p, &f, r), r;
}

// elif_stmt:
//     | 'elif' named_expr suite
static FAstNode *elif_stmt(FParser *p) {
    frame_t f = enter(p, 73, FUNC);
    ENTER(73);
    (consume(p, 57, "elif")) &&
    (a = named_expr(p)) &&
    (b = suite(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
static FAstNode *while_stmt(FParser *p) {
    frame_t f = enter(p, 74, FUNC);
    ENTER(74);
    (consume(p, 71, "while")) &&
    (a = named_expr(p)) &&
    (b = suite(p)) &&
    (c = else_suite(p), 1)
    ? (r = NODE_3()) : 0; 
    return exit(p, &f, r), r;
}

// for_stmt:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
static FAstNode *for_stmt(FParser *p) {
    frame_t f = enter(p, 75, FUNC);
    ENTER(75);
    (consume(p, 72, "for")) &&
    (a = targetlist(p)) &&
    (consume(p, 63, "in")) &&
    (b = exprlist(p)) &&
    (c = suite(p)) &&
    (d = else_suite(p), 1)
    ? (r = NODE_4()) : 0; 
    return exit(p, &f, r), r;
}

// try_stmt:
//     | 'try' suite (except_suite | finally_suite)
static FAstNode *try_stmt(FParser *p) {
    frame_t f = enter(p, 76, FUNC);
    ENTER(76);
    (consume(p, 75, "try")) &&
    (a = suite(p)) &&
    (b = try_stmt_3(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *try_stmt_3(FParser *p) {
    frame_t f = enter(p, 77, FUNC);
    ENTER(77);
    (a = except_suite(p)) ||
    (a = finally_suite(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
static FAstNode *with_stmt(FParser *p) {
    frame_t f = enter(p, 78, FUNC);
    ENTER(78);
    (consume(p, 68, "with")) &&
    (a = DELIMITED(p, 7, ",", expr_as_name)) &&
    (b = suite(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// expr_as_name:
//     | expr [as_name]
static FAstNode *expr_as_name(FParser *p) {
    frame_t f = enter(p, 79, FUNC);
    ENTER(79);
    (a = expr(p)) &&
    (b = as_name(p), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// block_suite (allow_whitespace=false):
//     | '{' NEWLINE stmt_list '}'
//     | '{' [simple_stmt] '}'
static FAstNode *block_suite(FParser *p) {
    frame_t f = enter(p, 80, FUNC);
    ENTER(80);
    WS_PUSH_0();
    (a = block_suite_1(p)) ||
    (a = block_suite_2(p))
    ? (r = NODE_1()) : 0;
    WS_POP();
    return exit(p, &f, r), r;
}

static FAstNode *block_suite_1(FParser *p) {
    frame_t f = enter(p, 81, FUNC);
    ENTER(81);
    (consume(p, 15, "{")) &&
    (a = consume(p, 2, "NEWLINE")) &&
    (b = stmt_list(p)) &&
    (consume(p, 16, "}"))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *block_suite_2(FParser *p) {
    frame_t f = enter(p, 82, FUNC);
    ENTER(82);
    (consume(p, 15, "{")) &&
    (a = simple_stmt(p), 1) &&
    (consume(p, 16, "}"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// suite:
//     | ':' simple_stmt
//     | block_suite
static FAstNode *suite(FParser *p) {
    frame_t f = enter(p, 83, FUNC);
    ENTER(83);
    (a = suite_1(p)) ||
    (a = block_suite(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *suite_1(FParser *p) {
    frame_t f = enter(p, 84, FUNC);
    ENTER(84);
    (consume(p, 9, ":")) &&
    (a = simple_stmt(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// else_suite:
//     | 'else' suite
static FAstNode *else_suite(FParser *p) {
    frame_t f = enter(p, 85, FUNC);
    ENTER(85);
    (consume(p, 58, "else")) &&
    (a = suite(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// finally_suite:
//     | 'finally' suite
static FAstNode *finally_suite(FParser *p) {
    frame_t f = enter(p, 86, FUNC);
    ENTER(86);
    (consume(p, 77, "finally")) &&
    (a = suite(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// except_clause:
//     | 'except' [expr_as_name] suite
static FAstNode *except_clause(FParser *p) {
    frame_t f = enter(p, 87, FUNC);
    ENTER(87);
    (consume(p, 76, "except")) &&
    (a = expr_as_name(p), 1) &&
    (b = suite(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
static FAstNode *except_suite(FParser *p) {
    frame_t f = enter(p, 88, FUNC);
    ENTER(88);
    (a = sequence(p, except_clause, 0)) &&
    (b = else_suite(p), 1) &&
    (c = finally_suite(p), 1)
    ? (r = NODE_3()) : 0; 
    return exit(p, &f, r), r;
}

// invocation:
//     | '(' [call_arg_list] ')'
static FAstNode *invocation(FParser *p) {
    frame_t f = enter(p, 89, FUNC);
    ENTER(89);
    (consume(p, 13, "(")) &&
    (a = call_arg_list(p), 1) &&
    (consume(p, 14, ")"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// call_arg_list (allow_whitespace=true):
//     | ','.call_arg+ [',']
static FAstNode *call_arg_list(FParser *p) {
    frame_t f = enter(p, 90, FUNC);
    ENTER(90);
    WS_PUSH_1();
    (a = DELIMITED(p, 7, ",", call_arg)) &&
    (b = consume(p, 7, ","), 1)
    ? (r = NODE_2()) : 0; 
    WS_POP();
    return exit(p, &f, r), r;
}

// call_arg:
//     | NAME ':=' expr
//     | NAME '=' expr
//     | '**' expr
//     | '*' expr
//     | expr
static FAstNode *call_arg(FParser *p) {
    frame_t f = enter(p, 91, FUNC);
    ENTER(91);
    (a = call_arg_1(p)) ||
    (a = call_arg_2(p)) ||
    (a = call_arg_3(p)) ||
    (a = call_arg_4(p)) ||
    (a = expr(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *call_arg_1(FParser *p) {
    frame_t f = enter(p, 92, FUNC);
    ENTER(92);
    (a = consume(p, 3, "NAME")) &&
    (consume(p, 36, ":=")) &&
    (b = expr(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *call_arg_2(FParser *p) {
    frame_t f = enter(p, 93, FUNC);
    ENTER(93);
    (a = consume(p, 3, "NAME")) &&
    (consume(p, 8, "=")) &&
    (b = expr(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *call_arg_3(FParser *p) {
    frame_t f = enter(p, 94, FUNC);
    ENTER(94);
    (consume(p, 38, "**")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *call_arg_4(FParser *p) {
    frame_t f = enter(p, 95, FUNC);
    ENTER(95);
    (consume(p, 23, "*")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// typed_arg_list (allow_whitespace=true):
//     | kwargs
//     | args_kwargs
//     | full_arg_list
static FAstNode *typed_arg_list(FParser *p) {
    frame_t f = enter(p, 96, FUNC);
    ENTER(96);
    WS_PUSH_1();
    (a = kwargs(p)) ||
    (a = args_kwargs(p)) ||
    (a = full_arg_list(p))
    ? (r = NODE_1()) : 0;
    WS_POP();
    return exit(p, &f, r), r;
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
static FAstNode *full_arg_list(FParser *p) {
    frame_t f = enter(p, 97, FUNC);
    ENTER(97);
    (a = DELIMITED(p, 7, ",", default_arg)) &&
    (b = full_arg_list_2(p), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *full_arg_list_2(FParser *p) {
    frame_t f = enter(p, 98, FUNC);
    ENTER(98);
    (consume(p, 7, ",")) &&
    (a = full_arg_list_2_2(p), 1)
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *full_arg_list_2_2(FParser *p) {
    frame_t f = enter(p, 99, FUNC);
    ENTER(99);
    (a = kwargs(p)) ||
    (a = args_kwargs(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
static FAstNode *args_kwargs(FParser *p) {
    frame_t f = enter(p, 100, FUNC);
    ENTER(100);
    (consume(p, 23, "*")) &&
    (a = typed_arg(p), 1) &&
    (b = sequence(p, args_kwargs_3, 1)) &&
    (c = args_kwargs_4(p), 1)
    ? (r = NODE_3()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *args_kwargs_3(FParser *p) {
    frame_t f = enter(p, 101, FUNC);
    ENTER(101);
    (consume(p, 7, ",")) &&
    (a = default_arg(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *args_kwargs_4(FParser *p) {
    frame_t f = enter(p, 102, FUNC);
    ENTER(102);
    (consume(p, 7, ",")) &&
    (a = kwargs(p), 1)
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// kwargs:
//     | '**' typed_arg [',']
static FAstNode *kwargs(FParser *p) {
    frame_t f = enter(p, 103, FUNC);
    ENTER(103);
    (consume(p, 38, "**")) &&
    (a = typed_arg(p)) &&
    (b = consume(p, 7, ","), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// default_arg:
//     | typed_arg ['=' expr]
static FAstNode *default_arg(FParser *p) {
    frame_t f = enter(p, 104, FUNC);
    ENTER(104);
    (a = typed_arg(p)) &&
    (b = default_arg_2(p), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *default_arg_2(FParser *p) {
    frame_t f = enter(p, 105, FUNC);
    ENTER(105);
    (consume(p, 8, "=")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// typed_arg:
//     | NAME [':' expr]
static FAstNode *typed_arg(FParser *p) {
    frame_t f = enter(p, 106, FUNC);
    ENTER(106);
    (a = consume(p, 3, "NAME")) &&
    (b = typed_arg_2(p), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *typed_arg_2(FParser *p) {
    frame_t f = enter(p, 107, FUNC);
    ENTER(107);
    (consume(p, 9, ":")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// simple_arg:
//     | NAME ['=' expr]
static FAstNode *simple_arg(FParser *p) {
    frame_t f = enter(p, 108, FUNC);
    ENTER(108);
    (a = consume(p, 3, "NAME")) &&
    (b = simple_arg_2(p), 1)
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *simple_arg_2(FParser *p) {
    frame_t f = enter(p, 109, FUNC);
    ENTER(109);
    (consume(p, 8, "=")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// simple_args:
//     | ','.simple_arg+
static FAstNode *simple_args(FParser *p) {
    frame_t f = enter(p, 110, FUNC);
    ENTER(110);
    (a = DELIMITED(p, 7, ",", simple_arg))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// builder_hint:
//     | '<' name_list '>'
static FAstNode *builder_hint(FParser *p) {
    frame_t f = enter(p, 111, FUNC);
    ENTER(111);
    (consume(p, 19, "<")) &&
    (a = name_list(p)) &&
    (consume(p, 20, ">"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// builder_args:
//     | simple_args
//     | '(' [typed_arg_list] ')'
static FAstNode *builder_args(FParser *p) {
    frame_t f = enter(p, 112, FUNC);
    ENTER(112);
    (a = simple_args(p)) ||
    (a = builder_args_2(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *builder_args_2(FParser *p) {
    frame_t f = enter(p, 113, FUNC);
    ENTER(113);
    (consume(p, 13, "(")) &&
    (a = typed_arg_list(p), 1) &&
    (consume(p, 14, ")"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// named_expr:
//     | NAME ':=' expr
//     | expr
static FAstNode *named_expr(FParser *p) {
    frame_t f = enter(p, 114, FUNC);
    ENTER(114);
    (a = named_expr_1(p)) ||
    (a = expr(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *named_expr_1(FParser *p) {
    frame_t f = enter(p, 115, FUNC);
    ENTER(115);
    (a = consume(p, 3, "NAME")) &&
    (consume(p, 36, ":=")) &&
    (b = expr(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
static FAstNode *conditional(FParser *p) {
    frame_t f = enter(p, 116, FUNC);
    ENTER(116);
    (consume(p, 56, "if")) &&
    (a = disjunction(p)) &&
    (consume(p, 10, "?")) &&
    (b = disjunction(p)) &&
    (consume(p, 9, ":")) &&
    (c = expr(p))
    ? (r = NODE_3()) : 0; 
    return exit(p, &f, r), r;
}

// expr:
//     | conditional
//     | disjunction
static FAstNode *expr(FParser *p) {
    frame_t f = enter(p, 117, FUNC);
    ENTER(117);
    (a = conditional(p)) ||
    (a = disjunction(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

// disjunction (left_recursive):
//     | disjunction 'or' conjunction
//     | conjunction
static FAstNode *disjunction(FParser *p) {
    frame_t f = enter(p, 118, FUNC);
    ENTER(118);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = disjunction_1(p)) ||
    (a = conjunction(p));
    EXIT_LEFT_RECURSION();
    return exit(p, &f, r), r;
}

static FAstNode *disjunction_1(FParser *p) {
    frame_t f = enter(p, 119, FUNC);
    ENTER(119);
    (a = disjunction(p)) &&
    (consume(p, 60, "or")) &&
    (b = conjunction(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// conjunction (left_recursive):
//     | conjunction 'and' inversion
//     | inversion
static FAstNode *conjunction(FParser *p) {
    frame_t f = enter(p, 120, FUNC);
    ENTER(120);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = conjunction_1(p)) ||
    (a = inversion(p));
    EXIT_LEFT_RECURSION();
    return exit(p, &f, r), r;
}

static FAstNode *conjunction_1(FParser *p) {
    frame_t f = enter(p, 121, FUNC);
    ENTER(121);
    (a = conjunction(p)) &&
    (consume(p, 59, "and")) &&
    (b = inversion(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// inversion:
//     | 'not' inversion
//     | comparison
static FAstNode *inversion(FParser *p) {
    frame_t f = enter(p, 122, FUNC);
    ENTER(122);
    (a = inversion_1(p)) ||
    (a = comparison(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *inversion_1(FParser *p) {
    frame_t f = enter(p, 123, FUNC);
    ENTER(123);
    (consume(p, 61, "not")) &&
    (a = inversion(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
static FAstNode *comparison(FParser *p) {
    frame_t f = enter(p, 124, FUNC);
    ENTER(124);
    (a = comparison_1(p)) ||
    (a = bitwise_or(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *comparison_1(FParser *p) {
    frame_t f = enter(p, 125, FUNC);
    ENTER(125);
    (a = bitwise_or(p)) &&
    (b = sequence(p, comparison_1_2, 0))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *comparison_1_2(FParser *p) {
    frame_t f = enter(p, 126, FUNC);
    ENTER(126);
    (a = comp_op(p)) &&
    (b = bitwise_or(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
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
static FAstNode *comp_op(FParser *p) {
    frame_t f = enter(p, 127, FUNC);
    ENTER(127);
    (a = consume(p, 19, "<")) ||
    (a = consume(p, 20, ">")) ||
    (a = consume(p, 31, "==")) ||
    (a = consume(p, 34, ">=")) ||
    (a = consume(p, 33, "<=")) ||
    (a = consume(p, 32, "!=")) ||
    (a = consume(p, 63, "in")) ||
    (a = comp_op_8(p)) ||
    (a = consume(p, 62, "is")) ||
    (a = comp_op_10(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *comp_op_8(FParser *p) {
    frame_t f = enter(p, 128, FUNC);
    ENTER(128);
    (consume(p, 61, "not")) &&
    (consume(p, 63, "in"));
    return exit(p, &f, r), r;
}

static FAstNode *comp_op_10(FParser *p) {
    frame_t f = enter(p, 129, FUNC);
    ENTER(129);
    (consume(p, 62, "is")) &&
    (consume(p, 61, "not"));
    return exit(p, &f, r), r;
}

// bitwise_or (left_recursive):
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
static FAstNode *bitwise_or(FParser *p) {
    frame_t f = enter(p, 130, FUNC);
    ENTER(130);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = bitwise_or_1(p)) ||
    (a = bitwise_xor(p));
    EXIT_LEFT_RECURSION();
    return exit(p, &f, r), r;
}

static FAstNode *bitwise_or_1(FParser *p) {
    frame_t f = enter(p, 131, FUNC);
    ENTER(131);
    (a = bitwise_or(p)) &&
    (consume(p, 27, "|")) &&
    (b = bitwise_xor(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// bitwise_xor (left_recursive):
//     | bitwise_xor '^' bitwise_and
//     | bitwise_and
static FAstNode *bitwise_xor(FParser *p) {
    frame_t f = enter(p, 132, FUNC);
    ENTER(132);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = bitwise_xor_1(p)) ||
    (a = bitwise_and(p));
    EXIT_LEFT_RECURSION();
    return exit(p, &f, r), r;
}

static FAstNode *bitwise_xor_1(FParser *p) {
    frame_t f = enter(p, 133, FUNC);
    ENTER(133);
    (a = bitwise_xor(p)) &&
    (consume(p, 30, "^")) &&
    (b = bitwise_and(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// bitwise_and (left_recursive):
//     | bitwise_and '&' shift_expr
//     | shift_expr
static FAstNode *bitwise_and(FParser *p) {
    frame_t f = enter(p, 134, FUNC);
    ENTER(134);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = bitwise_and_1(p)) ||
    (a = shift_expr(p));
    EXIT_LEFT_RECURSION();
    return exit(p, &f, r), r;
}

static FAstNode *bitwise_and_1(FParser *p) {
    frame_t f = enter(p, 135, FUNC);
    ENTER(135);
    (a = bitwise_and(p)) &&
    (consume(p, 28, "&")) &&
    (b = shift_expr(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// shift_expr (left_recursive):
//     | shift_expr '<<' sum
//     | shift_expr '>>' sum
//     | sum
static FAstNode *shift_expr(FParser *p) {
    frame_t f = enter(p, 136, FUNC);
    ENTER(136);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = shift_expr_1(p)) ||
    (a = shift_expr_2(p)) ||
    (a = sum(p));
    EXIT_LEFT_RECURSION();
    return exit(p, &f, r), r;
}

static FAstNode *shift_expr_1(FParser *p) {
    frame_t f = enter(p, 137, FUNC);
    ENTER(137);
    (a = shift_expr(p)) &&
    (consume(p, 48, "<<")) &&
    (b = sum(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *shift_expr_2(FParser *p) {
    frame_t f = enter(p, 138, FUNC);
    ENTER(138);
    (a = shift_expr(p)) &&
    (consume(p, 49, ">>")) &&
    (b = sum(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// sum (left_recursive):
//     | sum '+' term
//     | sum '-' term
//     | term
static FAstNode *sum(FParser *p) {
    frame_t f = enter(p, 139, FUNC);
    ENTER(139);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = sum_1(p)) ||
    (a = sum_2(p)) ||
    (a = term(p));
    EXIT_LEFT_RECURSION();
    return exit(p, &f, r), r;
}

static FAstNode *sum_1(FParser *p) {
    frame_t f = enter(p, 140, FUNC);
    ENTER(140);
    (a = sum(p)) &&
    (consume(p, 21, "+")) &&
    (b = term(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *sum_2(FParser *p) {
    frame_t f = enter(p, 141, FUNC);
    ENTER(141);
    (a = sum(p)) &&
    (consume(p, 22, "-")) &&
    (b = term(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// term (left_recursive):
//     | term '*' pipe_expr
//     | term '/' pipe_expr
//     | term '%' pipe_expr
//     | term '//' pipe_expr
//     | term '@' pipe_expr
//     | pipe_expr
static FAstNode *term(FParser *p) {
    frame_t f = enter(p, 142, FUNC);
    ENTER(142);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = term_1(p)) ||
    (a = term_2(p)) ||
    (a = term_3(p)) ||
    (a = term_4(p)) ||
    (a = term_5(p)) ||
    (a = pipe_expr(p));
    EXIT_LEFT_RECURSION();
    return exit(p, &f, r), r;
}

static FAstNode *term_1(FParser *p) {
    frame_t f = enter(p, 143, FUNC);
    ENTER(143);
    (a = term(p)) &&
    (consume(p, 23, "*")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *term_2(FParser *p) {
    frame_t f = enter(p, 144, FUNC);
    ENTER(144);
    (a = term(p)) &&
    (consume(p, 24, "/")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *term_3(FParser *p) {
    frame_t f = enter(p, 145, FUNC);
    ENTER(145);
    (a = term(p)) &&
    (consume(p, 25, "%")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *term_4(FParser *p) {
    frame_t f = enter(p, 146, FUNC);
    ENTER(146);
    (a = term(p)) &&
    (consume(p, 37, "//")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *term_5(FParser *p) {
    frame_t f = enter(p, 147, FUNC);
    ENTER(147);
    (a = term(p)) &&
    (consume(p, 26, "@")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// pipe_expr (left_recursive):
//     | pipe_expr '->' factor
//     | factor
static FAstNode *pipe_expr(FParser *p) {
    frame_t f = enter(p, 148, FUNC);
    ENTER(148);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = pipe_expr_1(p)) ||
    (a = factor(p));
    EXIT_LEFT_RECURSION();
    return exit(p, &f, r), r;
}

static FAstNode *pipe_expr_1(FParser *p) {
    frame_t f = enter(p, 149, FUNC);
    ENTER(149);
    (a = pipe_expr(p)) &&
    (consume(p, 35, "->")) &&
    (b = factor(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static FAstNode *factor(FParser *p) {
    frame_t f = enter(p, 150, FUNC);
    ENTER(150);
    (a = factor_1(p)) ||
    (a = factor_2(p)) ||
    (a = factor_3(p)) ||
    (a = power(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *factor_1(FParser *p) {
    frame_t f = enter(p, 151, FUNC);
    ENTER(151);
    (consume(p, 21, "+")) &&
    (a = factor(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *factor_2(FParser *p) {
    frame_t f = enter(p, 152, FUNC);
    ENTER(152);
    (consume(p, 22, "-")) &&
    (a = factor(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *factor_3(FParser *p) {
    frame_t f = enter(p, 153, FUNC);
    ENTER(153);
    (consume(p, 29, "~")) &&
    (a = factor(p))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// power:
//     | primary '**' factor
//     | primary
static FAstNode *power(FParser *p) {
    frame_t f = enter(p, 154, FUNC);
    ENTER(154);
    (a = power_1(p)) ||
    (a = primary(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *power_1(FParser *p) {
    frame_t f = enter(p, 155, FUNC);
    ENTER(155);
    (a = primary(p)) &&
    (consume(p, 38, "**")) &&
    (b = factor(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// primary (left_recursive):
//     | primary '.' NAME
//     | primary invocation
//     | primary subscript
//     | atom
static FAstNode *primary(FParser *p) {
    frame_t f = enter(p, 156, FUNC);
    ENTER(156);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = primary_1(p)) ||
    (a = primary_2(p)) ||
    (a = primary_3(p)) ||
    (a = atom(p));
    EXIT_LEFT_RECURSION();
    return exit(p, &f, r), r;
}

static FAstNode *primary_1(FParser *p) {
    frame_t f = enter(p, 157, FUNC);
    ENTER(157);
    (a = primary(p)) &&
    (consume(p, 6, ".")) &&
    (b = consume(p, 3, "NAME"))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *primary_2(FParser *p) {
    frame_t f = enter(p, 158, FUNC);
    ENTER(158);
    (a = primary(p)) &&
    (b = invocation(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *primary_3(FParser *p) {
    frame_t f = enter(p, 159, FUNC);
    ENTER(159);
    (a = primary(p)) &&
    (b = subscript(p))
    ? (r = NODE_2()) : 0; 
    return exit(p, &f, r), r;
}

// tuple_atom:
//     | '(' [list_items] ')'
static FAstNode *tuple_atom(FParser *p) {
    frame_t f = enter(p, 160, FUNC);
    ENTER(160);
    (consume(p, 13, "(")) &&
    (a = list_items(p), 1) &&
    (consume(p, 14, ")"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// list_iterable:
//     | '[' list_iterator ']'
static FAstNode *list_iterable(FParser *p) {
    frame_t f = enter(p, 161, FUNC);
    ENTER(161);
    (consume(p, 17, "[")) &&
    (a = list_iterator(p)) &&
    (consume(p, 18, "]"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// list_atom:
//     | '[' [list_items] ']'
static FAstNode *list_atom(FParser *p) {
    frame_t f = enter(p, 162, FUNC);
    ENTER(162);
    (consume(p, 17, "[")) &&
    (a = list_items(p), 1) &&
    (consume(p, 18, "]"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// set_atom:
//     | '{' [set_items] '}'
static FAstNode *set_atom(FParser *p) {
    frame_t f = enter(p, 163, FUNC);
    ENTER(163);
    (consume(p, 15, "{")) &&
    (a = set_items(p), 1) &&
    (consume(p, 16, "}"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// dict_iterable:
//     | '{' dict_iterator '}'
static FAstNode *dict_iterable(FParser *p) {
    frame_t f = enter(p, 164, FUNC);
    ENTER(164);
    (consume(p, 15, "{")) &&
    (a = dict_iterator(p)) &&
    (consume(p, 16, "}"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// dict_atom:
//     | '{' [dict_items] '}'
static FAstNode *dict_atom(FParser *p) {
    frame_t f = enter(p, 165, FUNC);
    ENTER(165);
    (consume(p, 15, "{")) &&
    (a = dict_items(p), 1) &&
    (consume(p, 16, "}"))
    ? (r = NODE_1()) : 0; 
    return exit(p, &f, r), r;
}

// builder:
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
static FAstNode *builder(FParser *p) {
    frame_t f = enter(p, 166, FUNC);
    ENTER(166);
    (a = builder_1(p)) ||
    (a = builder_2(p))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}

static FAstNode *builder_1(FParser *p) {
    frame_t f = enter(p, 167, FUNC);
    ENTER(167);
    (a = consume(p, 3, "NAME")) &&
    (b = simple_args(p)) &&
    (consume(p, 9, ":")) &&
    (c = expr(p))
    ? (r = NODE_3()) : 0; 
    return exit(p, &f, r), r;
}

static FAstNode *builder_2(FParser *p) {
    frame_t f = enter(p, 168, FUNC);
    ENTER(168);
    (a = consume(p, 3, "NAME")) &&
    (b = builder_hint(p), 1) &&
    (c = builder_args(p), 1) &&
    (d = block_suite(p))
    ? (r = NODE_4()) : 0; 
    return exit(p, &f, r), r;
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
static FAstNode *atom(FParser *p) {
    frame_t f = enter(p, 169, FUNC);
    ENTER(169);
    (a = tuple_atom(p)) ||
    (a = list_iterable(p)) ||
    (a = list_atom(p)) ||
    (a = set_atom(p)) ||
    (a = dict_iterable(p)) ||
    (a = dict_atom(p)) ||
    (a = builder(p)) ||
    (a = consume(p, 3, "NAME")) ||
    (a = consume(p, 4, "NUMBER")) ||
    (a = consume(p, 5, "STRING")) ||
    (a = consume(p, 81, "None")) ||
    (a = consume(p, 82, "True")) ||
    (a = consume(p, 83, "False"))
    ? (r = NODE_1()) : 0;
    return exit(p, &f, r), r;
}
