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
    frame_t f = {1, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = consume(p, 2, "NEWLINE")) ||
        (a = consume(p, 1, "ENDMARKER")) ||
        (a = simple_stmt(p)) ||
        (a = single_input_4(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *single_input_4(FParser *p) {
    frame_t f = {2, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = compound_stmt(p)) &&
        (b = consume(p, 2, "NEWLINE"))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// file_input:
//     | [stmt_list] ENDMARKER
static FAstNode *file_input(FParser *p) {
    frame_t f = {3, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = stmt_list(p), 1) &&
        (b = consume(p, 1, "ENDMARKER"))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// eval_input:
//     | exprlist NEWLINE* ENDMARKER
static FAstNode *eval_input(FParser *p) {
    frame_t f = {4, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *r;
    r = enter(p, &f) && (
        (a = exprlist(p)) &&
        (b = t_sequence(p, 2, "NEWLINE", 1)) &&
        (c = consume(p, 1, "ENDMARKER"))
    ) ? node_3(p, &f, a, b, c) : 0;
    return exit(p, &f, r);
}

// stmt_list:
//     | stmt+
static FAstNode *stmt_list(FParser *p) {
    frame_t f = {5, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = sequence(p, stmt, 0))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// stmt:
//     | (simple_stmt | compound_stmt) NEWLINE
static FAstNode *stmt(FParser *p) {
    frame_t f = {6, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = stmt_1(p)) &&
        (b = consume(p, 2, "NEWLINE"))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *stmt_1(FParser *p) {
    frame_t f = {7, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = simple_stmt(p)) ||
        (a = compound_stmt(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// simple_stmt:
//     | ';'.small_stmt+ [';']
static FAstNode *simple_stmt(FParser *p) {
    frame_t f = {8, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 12, ";", small_stmt)) &&
        (b = consume(p, 12, ";"), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
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
    frame_t f = {9, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
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
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// del_stmt:
//     | 'del' targetlist
static FAstNode *del_stmt(FParser *p) {
    frame_t f = {10, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 79, "del")) &&
        (a = targetlist(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// return_stmt:
//     | 'return' [exprlist_star]
static FAstNode *return_stmt(FParser *p) {
    frame_t f = {11, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 54, "return")) &&
        (a = exprlist_star(p), 1)
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// raise_stmt:
//     | 'raise' expr ['from' expr]
static FAstNode *raise_stmt(FParser *p) {
    frame_t f = {12, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (consume(p, 78, "raise")) &&
        (a = expr(p)) &&
        (b = raise_stmt_3(p), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *raise_stmt_3(FParser *p) {
    frame_t f = {13, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 66, "from")) &&
        (a = expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// nonlocal_stmt:
//     | 'nonlocal' name_list
static FAstNode *nonlocal_stmt(FParser *p) {
    frame_t f = {14, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 55, "nonlocal")) &&
        (a = name_list(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// assert_stmt:
//     | 'assert' expr [',' expr]
static FAstNode *assert_stmt(FParser *p) {
    frame_t f = {15, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (consume(p, 80, "assert")) &&
        (a = expr(p)) &&
        (b = assert_stmt_3(p), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *assert_stmt_3(FParser *p) {
    frame_t f = {16, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 7, ",")) &&
        (a = expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// name_list:
//     | ','.NAME+
static FAstNode *name_list(FParser *p) {
    frame_t f = {17, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = t_delimited(p, 7, ",", 3, "NAME"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// star_expr:
//     | '*' bitwise_or
static FAstNode *star_expr(FParser *p) {
    frame_t f = {18, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 23, "*")) &&
        (a = bitwise_or(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// exprlist:
//     | ','.expr+ [',']
static FAstNode *exprlist(FParser *p) {
    frame_t f = {19, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 7, ",", expr)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// target:
//     | t_primary '.' NAME !t_lookahead
//     | t_primary subscript !t_lookahead
//     | NAME
//     | '(' targetlist_sp ')'
static FAstNode *target(FParser *p) {
    frame_t f = {20, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = target_1(p)) ||
        (a = target_2(p)) ||
        (a = consume(p, 3, "NAME")) ||
        (a = target_4(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *target_1(FParser *p) {
    frame_t f = {21, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = t_primary(p)) &&
        (consume(p, 6, ".")) &&
        (b = consume(p, 3, "NAME")) &&
        (!test_and_reset(p, &f, t_lookahead(p)))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *target_2(FParser *p) {
    frame_t f = {22, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = t_primary(p)) &&
        (b = subscript(p)) &&
        (!test_and_reset(p, &f, t_lookahead(p)))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *target_4(FParser *p) {
    frame_t f = {23, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = targetlist_sp(p)) &&
        (consume(p, 14, ")"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// targetlist_sp (allow_whitespace=true):
//     | targetlist
static FAstNode *targetlist_sp(FParser *p) {
    frame_t f = {24, p->pos, FUNC, 0, F_ALLOW_SPACES};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = targetlist(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// t_primary (left_recursive):
//     | t_primary '.' NAME &t_lookahead
//     | t_primary invocation &t_lookahead
//     | t_primary subscript &t_lookahead
//     | atom &t_lookahead
static FAstNode *t_primary(FParser *p) {
    frame_t f = {25, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = t_primary_1(p)) ||
        (a = t_primary_2(p)) ||
        (a = t_primary_3(p)) ||
        (a = t_primary_4(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *t_primary_1(FParser *p) {
    frame_t f = {26, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = t_primary(p)) &&
        (consume(p, 6, ".")) &&
        (b = consume(p, 3, "NAME")) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *t_primary_2(FParser *p) {
    frame_t f = {27, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = t_primary(p)) &&
        (b = invocation(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *t_primary_3(FParser *p) {
    frame_t f = {28, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = t_primary(p)) &&
        (b = subscript(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *t_primary_4(FParser *p) {
    frame_t f = {29, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = atom(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// t_lookahead:
//     | '.'
//     | '('
//     | '['
static FAstNode *t_lookahead(FParser *p) {
    frame_t f = {30, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = consume(p, 6, ".")) ||
        (a = consume(p, 13, "(")) ||
        (a = consume(p, 17, "["))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// targetlist:
//     | ','.target+ [',']
static FAstNode *targetlist(FParser *p) {
    frame_t f = {31, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 7, ",", target)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// expr_or_star:
//     | star_expr
//     | expr
static FAstNode *expr_or_star(FParser *p) {
    frame_t f = {32, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = star_expr(p)) ||
        (a = expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// exprlist_star:
//     | ','.expr_or_star+ [',']
static FAstNode *exprlist_star(FParser *p) {
    frame_t f = {33, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 7, ",", expr_or_star)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// subscript:
//     | '[' slicelist ']'
static FAstNode *subscript(FParser *p) {
    frame_t f = {34, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 17, "[")) &&
        (a = slicelist(p)) &&
        (consume(p, 18, "]"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// slicelist:
//     | ','.slice+ [',']
static FAstNode *slicelist(FParser *p) {
    frame_t f = {35, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 7, ",", slice)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// slice:
//     | [expr] slice_expr [slice_expr]
//     | expr
static FAstNode *slice(FParser *p) {
    frame_t f = {36, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = slice_1(p)) ||
        (a = expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *slice_1(FParser *p) {
    frame_t f = {37, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *r;
    r = enter(p, &f) && (
        (a = expr(p), 1) &&
        (b = slice_expr(p)) &&
        (c = slice_expr(p), 1)
    ) ? node_3(p, &f, a, b, c) : 0;
    return exit(p, &f, r);
}

// slice_expr:
//     | ':' [expr]
static FAstNode *slice_expr(FParser *p) {
    frame_t f = {38, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 9, ":")) &&
        (a = expr(p), 1)
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// dict_item:
//     | expr ':' expr
//     | '**' bitwise_or
static FAstNode *dict_item(FParser *p) {
    frame_t f = {39, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = dict_item_1(p)) ||
        (a = dict_item_2(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *dict_item_1(FParser *p) {
    frame_t f = {40, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = expr(p)) &&
        (consume(p, 9, ":")) &&
        (b = expr(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *dict_item_2(FParser *p) {
    frame_t f = {41, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 38, "**")) &&
        (a = bitwise_or(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// dict_items (allow_whitespace=true):
//     | ','.dict_item+ [',']
static FAstNode *dict_items(FParser *p) {
    frame_t f = {42, p->pos, FUNC, 0, F_ALLOW_SPACES};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 7, ",", dict_item)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// list_item:
//     | star_expr
//     | named_expr
static FAstNode *list_item(FParser *p) {
    frame_t f = {43, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = star_expr(p)) ||
        (a = named_expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// list_items (allow_whitespace=true):
//     | ','.list_item+ [',']
static FAstNode *list_items(FParser *p) {
    frame_t f = {44, p->pos, FUNC, 0, F_ALLOW_SPACES};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 7, ",", list_item)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// set_items (allow_whitespace=true):
//     | exprlist_star
static FAstNode *set_items(FParser *p) {
    frame_t f = {45, p->pos, FUNC, 0, F_ALLOW_SPACES};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = exprlist_star(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// as_name:
//     | 'as' NAME
static FAstNode *as_name(FParser *p) {
    frame_t f = {46, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 65, "as")) &&
        (a = consume(p, 3, "NAME"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// iter_for:
//     | 'for' targetlist 'in' disjunction [iter_if]
static FAstNode *iter_for(FParser *p) {
    frame_t f = {47, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *r;
    r = enter(p, &f) && (
        (consume(p, 72, "for")) &&
        (a = targetlist(p)) &&
        (consume(p, 63, "in")) &&
        (b = disjunction(p)) &&
        (c = iter_if(p), 1)
    ) ? node_3(p, &f, a, b, c) : 0;
    return exit(p, &f, r);
}

// iter_if:
//     | 'if' named_expr
static FAstNode *iter_if(FParser *p) {
    frame_t f = {48, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 56, "if")) &&
        (a = named_expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// iterator:
//     | iter_for* 'for' targetlist [iter_if]
static FAstNode *iterator(FParser *p) {
    frame_t f = {49, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *r;
    r = enter(p, &f) && (
        (a = sequence(p, iter_for, 1)) &&
        (consume(p, 72, "for")) &&
        (b = targetlist(p)) &&
        (c = iter_if(p), 1)
    ) ? node_3(p, &f, a, b, c) : 0;
    return exit(p, &f, r);
}

// list_iterator (allow_whitespace=true):
//     | expr_or_star iterator
static FAstNode *list_iterator(FParser *p) {
    frame_t f = {50, p->pos, FUNC, 0, F_ALLOW_SPACES};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = expr_or_star(p)) &&
        (b = iterator(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// dict_iterator (allow_whitespace=true):
//     | dict_item iterator
static FAstNode *dict_iterator(FParser *p) {
    frame_t f = {51, p->pos, FUNC, 0, F_ALLOW_SPACES};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = dict_item(p)) &&
        (b = iterator(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// assignment:
//     | pubassign
//     | annassign
//     | augassign
//     | simple_assign
static FAstNode *assignment(FParser *p) {
    frame_t f = {52, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = pubassign(p)) ||
        (a = annassign(p)) ||
        (a = augassign(p)) ||
        (a = simple_assign(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// pubassign:
//     | '/' NAME '=' exprlist
static FAstNode *pubassign(FParser *p) {
    frame_t f = {53, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (consume(p, 24, "/")) &&
        (a = consume(p, 3, "NAME")) &&
        (consume(p, 8, "=")) &&
        (b = exprlist(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// annassign:
//     | target ':' expr ['=' exprlist]
static FAstNode *annassign(FParser *p) {
    frame_t f = {54, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *r;
    r = enter(p, &f) && (
        (a = target(p)) &&
        (consume(p, 9, ":")) &&
        (b = expr(p)) &&
        (c = annassign_4(p), 1)
    ) ? node_3(p, &f, a, b, c) : 0;
    return exit(p, &f, r);
}

static FAstNode *annassign_4(FParser *p) {
    frame_t f = {55, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 8, "=")) &&
        (a = exprlist(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// augassign:
//     | target augassign_op exprlist
static FAstNode *augassign(FParser *p) {
    frame_t f = {56, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *r;
    r = enter(p, &f) && (
        (a = target(p)) &&
        (b = augassign_op(p)) &&
        (c = exprlist(p))
    ) ? node_3(p, &f, a, b, c) : 0;
    return exit(p, &f, r);
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
static FAstNode *simple_assign(FParser *p) {
    frame_t f = {57, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = sequence(p, simple_assign_1, 1)) &&
        (b = exprlist_star(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *simple_assign_1(FParser *p) {
    frame_t f = {58, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = targetlist(p)) &&
        (consume(p, 8, "="))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
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
    frame_t f = {59, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
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
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// import_name:
//     | 'import' dotted_as_names
static FAstNode *import_name(FParser *p) {
    frame_t f = {60, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 67, "import")) &&
        (a = dotted_as_names(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// import_from:
//     | 'from' import_from_names 'import' import_from_items
static FAstNode *import_from(FParser *p) {
    frame_t f = {61, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (consume(p, 66, "from")) &&
        (a = import_from_names(p)) &&
        (consume(p, 67, "import")) &&
        (b = import_from_items(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// import_from_names:
//     | dotted_name
//     | '.'+ [dotted_name]
static FAstNode *import_from_names(FParser *p) {
    frame_t f = {62, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = dotted_name(p)) ||
        (a = import_from_names_2(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *import_from_names_2(FParser *p) {
    frame_t f = {63, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (t_sequence(p, 6, ".", 0)) &&
        (a = dotted_name(p), 1)
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// import_from_items:
//     | '*'
//     | import_as_names_sp
//     | import_as_names
static FAstNode *import_from_items(FParser *p) {
    frame_t f = {64, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = consume(p, 23, "*")) ||
        (a = import_as_names_sp(p)) ||
        (a = import_as_names(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// import_as_names_sp (allow_whitespace=true):
//     | '(' import_as_names [','] ')'
static FAstNode *import_as_names_sp(FParser *p) {
    frame_t f = {65, p->pos, FUNC, 0, F_ALLOW_SPACES};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = import_as_names(p)) &&
        (b = consume(p, 7, ","), 1) &&
        (consume(p, 14, ")"))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// import_as_name:
//     | NAME [as_name]
static FAstNode *import_as_name(FParser *p) {
    frame_t f = {66, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (b = as_name(p), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// dotted_as_name:
//     | dotted_name [as_name]
static FAstNode *dotted_as_name(FParser *p) {
    frame_t f = {67, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = dotted_name(p)) &&
        (b = as_name(p), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// import_as_names:
//     | ','.import_as_name+
static FAstNode *import_as_names(FParser *p) {
    frame_t f = {68, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 7, ",", import_as_name))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// dotted_as_names:
//     | ','.dotted_as_name+
static FAstNode *dotted_as_names(FParser *p) {
    frame_t f = {69, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 7, ",", dotted_as_name))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// dotted_name:
//     | '.'.NAME+
static FAstNode *dotted_name(FParser *p) {
    frame_t f = {70, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = t_delimited(p, 6, ".", 3, "NAME"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// compound_stmt:
//     | if_stmt
//     | while_stmt
//     | for_stmt
//     | try_stmt
//     | with_stmt
static FAstNode *compound_stmt(FParser *p) {
    frame_t f = {71, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = if_stmt(p)) ||
        (a = while_stmt(p)) ||
        (a = for_stmt(p)) ||
        (a = try_stmt(p)) ||
        (a = with_stmt(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
static FAstNode *if_stmt(FParser *p) {
    frame_t f = {72, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *d, *r;
    r = enter(p, &f) && (
        (consume(p, 56, "if")) &&
        (a = named_expr(p)) &&
        (b = suite(p)) &&
        (c = sequence(p, elif_stmt, 1)) &&
        (d = else_suite(p), 1)
    ) ? node_4(p, &f, a, b, c, d) : 0;
    return exit(p, &f, r);
}

// elif_stmt:
//     | 'elif' named_expr suite
static FAstNode *elif_stmt(FParser *p) {
    frame_t f = {73, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (consume(p, 57, "elif")) &&
        (a = named_expr(p)) &&
        (b = suite(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
static FAstNode *while_stmt(FParser *p) {
    frame_t f = {74, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *r;
    r = enter(p, &f) && (
        (consume(p, 71, "while")) &&
        (a = named_expr(p)) &&
        (b = suite(p)) &&
        (c = else_suite(p), 1)
    ) ? node_3(p, &f, a, b, c) : 0;
    return exit(p, &f, r);
}

// for_stmt:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
static FAstNode *for_stmt(FParser *p) {
    frame_t f = {75, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *d, *r;
    r = enter(p, &f) && (
        (consume(p, 72, "for")) &&
        (a = targetlist(p)) &&
        (consume(p, 63, "in")) &&
        (b = exprlist(p)) &&
        (c = suite(p)) &&
        (d = else_suite(p), 1)
    ) ? node_4(p, &f, a, b, c, d) : 0;
    return exit(p, &f, r);
}

// try_stmt:
//     | 'try' suite (except_suite | finally_suite)
static FAstNode *try_stmt(FParser *p) {
    frame_t f = {76, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (consume(p, 75, "try")) &&
        (a = suite(p)) &&
        (b = try_stmt_3(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *try_stmt_3(FParser *p) {
    frame_t f = {77, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = except_suite(p)) ||
        (a = finally_suite(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
static FAstNode *with_stmt(FParser *p) {
    frame_t f = {78, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (consume(p, 68, "with")) &&
        (a = delimited(p, 7, ",", expr_as_name)) &&
        (b = suite(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// expr_as_name:
//     | expr [as_name]
static FAstNode *expr_as_name(FParser *p) {
    frame_t f = {79, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = expr(p)) &&
        (b = as_name(p), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// block_suite (allow_whitespace=false):
//     | '{' NEWLINE stmt_list '}'
//     | '{' [simple_stmt] '}'
static FAstNode *block_suite(FParser *p) {
    frame_t f = {80, p->pos, FUNC, 0, F_DISALLOW_SPACES};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = block_suite_1(p)) ||
        (a = block_suite_2(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *block_suite_1(FParser *p) {
    frame_t f = {81, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (consume(p, 15, "{")) &&
        (a = consume(p, 2, "NEWLINE")) &&
        (b = stmt_list(p)) &&
        (consume(p, 16, "}"))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *block_suite_2(FParser *p) {
    frame_t f = {82, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 15, "{")) &&
        (a = simple_stmt(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// suite:
//     | ':' simple_stmt
//     | block_suite
static FAstNode *suite(FParser *p) {
    frame_t f = {83, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = suite_1(p)) ||
        (a = block_suite(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *suite_1(FParser *p) {
    frame_t f = {84, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 9, ":")) &&
        (a = simple_stmt(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// else_suite:
//     | 'else' suite
static FAstNode *else_suite(FParser *p) {
    frame_t f = {85, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 58, "else")) &&
        (a = suite(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// finally_suite:
//     | 'finally' suite
static FAstNode *finally_suite(FParser *p) {
    frame_t f = {86, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 77, "finally")) &&
        (a = suite(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// except_clause:
//     | 'except' [expr_as_name] suite
static FAstNode *except_clause(FParser *p) {
    frame_t f = {87, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (consume(p, 76, "except")) &&
        (a = expr_as_name(p), 1) &&
        (b = suite(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
static FAstNode *except_suite(FParser *p) {
    frame_t f = {88, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *r;
    r = enter(p, &f) && (
        (a = sequence(p, except_clause, 0)) &&
        (b = else_suite(p), 1) &&
        (c = finally_suite(p), 1)
    ) ? node_3(p, &f, a, b, c) : 0;
    return exit(p, &f, r);
}

// invocation:
//     | '(' [call_arg_list] ')'
static FAstNode *invocation(FParser *p) {
    frame_t f = {89, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = call_arg_list(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// call_arg_list (allow_whitespace=true):
//     | ','.call_arg+ [',']
static FAstNode *call_arg_list(FParser *p) {
    frame_t f = {90, p->pos, FUNC, 0, F_ALLOW_SPACES};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 7, ",", call_arg)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// call_arg:
//     | NAME ':=' expr
//     | NAME '=' expr
//     | '**' expr
//     | '*' expr
//     | expr
static FAstNode *call_arg(FParser *p) {
    frame_t f = {91, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = call_arg_1(p)) ||
        (a = call_arg_2(p)) ||
        (a = call_arg_3(p)) ||
        (a = call_arg_4(p)) ||
        (a = expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *call_arg_1(FParser *p) {
    frame_t f = {92, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (b = expr(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *call_arg_2(FParser *p) {
    frame_t f = {93, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (consume(p, 8, "=")) &&
        (b = expr(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *call_arg_3(FParser *p) {
    frame_t f = {94, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 38, "**")) &&
        (a = expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *call_arg_4(FParser *p) {
    frame_t f = {95, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 23, "*")) &&
        (a = expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// typed_arg_list (allow_whitespace=true):
//     | kwargs
//     | args_kwargs
//     | full_arg_list
static FAstNode *typed_arg_list(FParser *p) {
    frame_t f = {96, p->pos, FUNC, 0, F_ALLOW_SPACES};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = kwargs(p)) ||
        (a = args_kwargs(p)) ||
        (a = full_arg_list(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
static FAstNode *full_arg_list(FParser *p) {
    frame_t f = {97, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 7, ",", default_arg)) &&
        (b = full_arg_list_2(p), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *full_arg_list_2(FParser *p) {
    frame_t f = {98, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 7, ",")) &&
        (a = full_arg_list_2_2(p), 1)
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *full_arg_list_2_2(FParser *p) {
    frame_t f = {99, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = kwargs(p)) ||
        (a = args_kwargs(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
static FAstNode *args_kwargs(FParser *p) {
    frame_t f = {100, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *r;
    r = enter(p, &f) && (
        (consume(p, 23, "*")) &&
        (a = typed_arg(p), 1) &&
        (b = sequence(p, args_kwargs_3, 1)) &&
        (c = args_kwargs_4(p), 1)
    ) ? node_3(p, &f, a, b, c) : 0;
    return exit(p, &f, r);
}

static FAstNode *args_kwargs_3(FParser *p) {
    frame_t f = {101, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 7, ",")) &&
        (a = default_arg(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *args_kwargs_4(FParser *p) {
    frame_t f = {102, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 7, ",")) &&
        (a = kwargs(p), 1)
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// kwargs:
//     | '**' typed_arg [',']
static FAstNode *kwargs(FParser *p) {
    frame_t f = {103, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (consume(p, 38, "**")) &&
        (a = typed_arg(p)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// default_arg:
//     | typed_arg ['=' expr]
static FAstNode *default_arg(FParser *p) {
    frame_t f = {104, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = typed_arg(p)) &&
        (b = default_arg_2(p), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *default_arg_2(FParser *p) {
    frame_t f = {105, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 8, "=")) &&
        (a = expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// typed_arg:
//     | NAME [':' expr]
static FAstNode *typed_arg(FParser *p) {
    frame_t f = {106, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (b = typed_arg_2(p), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *typed_arg_2(FParser *p) {
    frame_t f = {107, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 9, ":")) &&
        (a = expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// simple_arg:
//     | NAME ['=' expr]
static FAstNode *simple_arg(FParser *p) {
    frame_t f = {108, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (b = simple_arg_2(p), 1)
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *simple_arg_2(FParser *p) {
    frame_t f = {109, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 8, "=")) &&
        (a = expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// simple_args:
//     | ','.simple_arg+
static FAstNode *simple_args(FParser *p) {
    frame_t f = {110, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = delimited(p, 7, ",", simple_arg))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// builder_hint:
//     | '<' name_list '>'
static FAstNode *builder_hint(FParser *p) {
    frame_t f = {111, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 19, "<")) &&
        (a = name_list(p)) &&
        (consume(p, 20, ">"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// builder_args:
//     | simple_args
//     | '(' [typed_arg_list] ')'
static FAstNode *builder_args(FParser *p) {
    frame_t f = {112, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = simple_args(p)) ||
        (a = builder_args_2(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *builder_args_2(FParser *p) {
    frame_t f = {113, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = typed_arg_list(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// named_expr:
//     | NAME ':=' expr
//     | expr
static FAstNode *named_expr(FParser *p) {
    frame_t f = {114, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = named_expr_1(p)) ||
        (a = expr(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *named_expr_1(FParser *p) {
    frame_t f = {115, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (b = expr(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
static FAstNode *conditional(FParser *p) {
    frame_t f = {116, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *r;
    r = enter(p, &f) && (
        (consume(p, 56, "if")) &&
        (a = disjunction(p)) &&
        (consume(p, 10, "?")) &&
        (b = disjunction(p)) &&
        (consume(p, 9, ":")) &&
        (c = expr(p))
    ) ? node_3(p, &f, a, b, c) : 0;
    return exit(p, &f, r);
}

// expr:
//     | conditional
//     | disjunction
static FAstNode *expr(FParser *p) {
    frame_t f = {117, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = conditional(p)) ||
        (a = disjunction(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// disjunction (left_recursive):
//     | disjunction 'or' conjunction
//     | conjunction
static FAstNode *disjunction(FParser *p) {
    frame_t f = {118, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = disjunction_1(p)) ||
        (a = conjunction(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *disjunction_1(FParser *p) {
    frame_t f = {119, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = disjunction(p)) &&
        (consume(p, 60, "or")) &&
        (b = conjunction(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// conjunction (left_recursive):
//     | conjunction 'and' inversion
//     | inversion
static FAstNode *conjunction(FParser *p) {
    frame_t f = {120, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = conjunction_1(p)) ||
        (a = inversion(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *conjunction_1(FParser *p) {
    frame_t f = {121, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = conjunction(p)) &&
        (consume(p, 59, "and")) &&
        (b = inversion(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// inversion:
//     | 'not' inversion
//     | comparison
static FAstNode *inversion(FParser *p) {
    frame_t f = {122, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = inversion_1(p)) ||
        (a = comparison(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *inversion_1(FParser *p) {
    frame_t f = {123, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 61, "not")) &&
        (a = inversion(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
static FAstNode *comparison(FParser *p) {
    frame_t f = {124, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = comparison_1(p)) ||
        (a = bitwise_or(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *comparison_1(FParser *p) {
    frame_t f = {125, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = bitwise_or(p)) &&
        (b = sequence(p, comparison_1_2, 0))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *comparison_1_2(FParser *p) {
    frame_t f = {126, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = comp_op(p)) &&
        (b = bitwise_or(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
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
    frame_t f = {127, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
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
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *comp_op_8(FParser *p) {
    frame_t f = {128, p->pos, FUNC, 0, 0};
    FAstNode *r;
    r = enter(p, &f) && (
        (consume(p, 61, "not")) &&
        (consume(p, 63, "in"))
    ) ? node_0(p, &f) : 0;
    return exit(p, &f, r);
}

static FAstNode *comp_op_10(FParser *p) {
    frame_t f = {129, p->pos, FUNC, 0, 0};
    FAstNode *r;
    r = enter(p, &f) && (
        (consume(p, 62, "is")) &&
        (consume(p, 61, "not"))
    ) ? node_0(p, &f) : 0;
    return exit(p, &f, r);
}

// bitwise_or (left_recursive):
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
static FAstNode *bitwise_or(FParser *p) {
    frame_t f = {130, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = bitwise_or_1(p)) ||
        (a = bitwise_xor(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *bitwise_or_1(FParser *p) {
    frame_t f = {131, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = bitwise_or(p)) &&
        (consume(p, 27, "|")) &&
        (b = bitwise_xor(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// bitwise_xor (left_recursive):
//     | bitwise_xor '^' bitwise_and
//     | bitwise_and
static FAstNode *bitwise_xor(FParser *p) {
    frame_t f = {132, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = bitwise_xor_1(p)) ||
        (a = bitwise_and(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *bitwise_xor_1(FParser *p) {
    frame_t f = {133, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = bitwise_xor(p)) &&
        (consume(p, 30, "^")) &&
        (b = bitwise_and(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// bitwise_and (left_recursive):
//     | bitwise_and '&' shift_expr
//     | shift_expr
static FAstNode *bitwise_and(FParser *p) {
    frame_t f = {134, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = bitwise_and_1(p)) ||
        (a = shift_expr(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *bitwise_and_1(FParser *p) {
    frame_t f = {135, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = bitwise_and(p)) &&
        (consume(p, 28, "&")) &&
        (b = shift_expr(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// shift_expr (left_recursive):
//     | shift_expr '<<' sum
//     | shift_expr '>>' sum
//     | sum
static FAstNode *shift_expr(FParser *p) {
    frame_t f = {136, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = shift_expr_1(p)) ||
        (a = shift_expr_2(p)) ||
        (a = sum(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *shift_expr_1(FParser *p) {
    frame_t f = {137, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = shift_expr(p)) &&
        (consume(p, 48, "<<")) &&
        (b = sum(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *shift_expr_2(FParser *p) {
    frame_t f = {138, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = shift_expr(p)) &&
        (consume(p, 49, ">>")) &&
        (b = sum(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// sum (left_recursive):
//     | sum '+' term
//     | sum '-' term
//     | term
static FAstNode *sum(FParser *p) {
    frame_t f = {139, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = sum_1(p)) ||
        (a = sum_2(p)) ||
        (a = term(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *sum_1(FParser *p) {
    frame_t f = {140, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = sum(p)) &&
        (consume(p, 21, "+")) &&
        (b = term(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *sum_2(FParser *p) {
    frame_t f = {141, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = sum(p)) &&
        (consume(p, 22, "-")) &&
        (b = term(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// term (left_recursive):
//     | term '*' pipe_expr
//     | term '/' pipe_expr
//     | term '%' pipe_expr
//     | term '//' pipe_expr
//     | term '@' pipe_expr
//     | pipe_expr
static FAstNode *term(FParser *p) {
    frame_t f = {142, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = term_1(p)) ||
        (a = term_2(p)) ||
        (a = term_3(p)) ||
        (a = term_4(p)) ||
        (a = term_5(p)) ||
        (a = pipe_expr(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *term_1(FParser *p) {
    frame_t f = {143, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = term(p)) &&
        (consume(p, 23, "*")) &&
        (b = pipe_expr(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *term_2(FParser *p) {
    frame_t f = {144, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = term(p)) &&
        (consume(p, 24, "/")) &&
        (b = pipe_expr(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *term_3(FParser *p) {
    frame_t f = {145, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = term(p)) &&
        (consume(p, 25, "%")) &&
        (b = pipe_expr(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *term_4(FParser *p) {
    frame_t f = {146, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = term(p)) &&
        (consume(p, 37, "//")) &&
        (b = pipe_expr(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *term_5(FParser *p) {
    frame_t f = {147, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = term(p)) &&
        (consume(p, 26, "@")) &&
        (b = pipe_expr(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// pipe_expr (left_recursive):
//     | pipe_expr '->' factor
//     | factor
static FAstNode *pipe_expr(FParser *p) {
    frame_t f = {148, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = pipe_expr_1(p)) ||
        (a = factor(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *pipe_expr_1(FParser *p) {
    frame_t f = {149, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = pipe_expr(p)) &&
        (consume(p, 35, "->")) &&
        (b = factor(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static FAstNode *factor(FParser *p) {
    frame_t f = {150, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = factor_1(p)) ||
        (a = factor_2(p)) ||
        (a = factor_3(p)) ||
        (a = power(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *factor_1(FParser *p) {
    frame_t f = {151, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 21, "+")) &&
        (a = factor(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *factor_2(FParser *p) {
    frame_t f = {152, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 22, "-")) &&
        (a = factor(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *factor_3(FParser *p) {
    frame_t f = {153, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 29, "~")) &&
        (a = factor(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// power:
//     | primary '**' factor
//     | primary
static FAstNode *power(FParser *p) {
    frame_t f = {154, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = power_1(p)) ||
        (a = primary(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *power_1(FParser *p) {
    frame_t f = {155, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = primary(p)) &&
        (consume(p, 38, "**")) &&
        (b = factor(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// primary (left_recursive):
//     | primary '.' NAME
//     | primary invocation
//     | primary subscript
//     | atom
static FAstNode *primary(FParser *p) {
    frame_t f = {156, p->pos, FUNC, 0, F_LR};
    FAstNode *a = 0, *r = 0, *m = 0;
    if (!enter(p, &f)) goto exit;
    size_t i = f.f_pos;
    while(1) {
        memoize(p, &f, m, i);
        p->pos = f.f_pos;
        (a = primary_1(p)) ||
        (a = primary_2(p)) ||
        (a = primary_3(p)) ||
        (a = atom(p));
        if (p->pos <= i) break;
        m = a, i = p->pos;
    }
    p->pos = i;
    r = m ? node_1(p, &f, m) : 0;
exit:
    return exit(p, &f, r);
}

static FAstNode *primary_1(FParser *p) {
    frame_t f = {157, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = primary(p)) &&
        (consume(p, 6, ".")) &&
        (b = consume(p, 3, "NAME"))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *primary_2(FParser *p) {
    frame_t f = {158, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = primary(p)) &&
        (b = invocation(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

static FAstNode *primary_3(FParser *p) {
    frame_t f = {159, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *r;
    r = enter(p, &f) && (
        (a = primary(p)) &&
        (b = subscript(p))
    ) ? node_2(p, &f, a, b) : 0;
    return exit(p, &f, r);
}

// tuple_atom:
//     | '(' [list_items] ')'
static FAstNode *tuple_atom(FParser *p) {
    frame_t f = {160, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = list_items(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// list_iterable:
//     | '[' list_iterator ']'
static FAstNode *list_iterable(FParser *p) {
    frame_t f = {161, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 17, "[")) &&
        (a = list_iterator(p)) &&
        (consume(p, 18, "]"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// list_atom:
//     | '[' [list_items] ']'
static FAstNode *list_atom(FParser *p) {
    frame_t f = {162, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 17, "[")) &&
        (a = list_items(p), 1) &&
        (consume(p, 18, "]"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// set_atom:
//     | '{' [set_items] '}'
static FAstNode *set_atom(FParser *p) {
    frame_t f = {163, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 15, "{")) &&
        (a = set_items(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// dict_iterable:
//     | '{' dict_iterator '}'
static FAstNode *dict_iterable(FParser *p) {
    frame_t f = {164, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 15, "{")) &&
        (a = dict_iterator(p)) &&
        (consume(p, 16, "}"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// dict_atom:
//     | '{' [dict_items] '}'
static FAstNode *dict_atom(FParser *p) {
    frame_t f = {165, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (consume(p, 15, "{")) &&
        (a = dict_items(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

// builder:
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
static FAstNode *builder(FParser *p) {
    frame_t f = {166, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
        (a = builder_1(p)) ||
        (a = builder_2(p))
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}

static FAstNode *builder_1(FParser *p) {
    frame_t f = {167, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *r;
    r = enter(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (b = simple_args(p)) &&
        (consume(p, 9, ":")) &&
        (c = expr(p))
    ) ? node_3(p, &f, a, b, c) : 0;
    return exit(p, &f, r);
}

static FAstNode *builder_2(FParser *p) {
    frame_t f = {168, p->pos, FUNC, 0, 0};
    FAstNode *a, *b, *c, *d, *r;
    r = enter(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (b = builder_hint(p), 1) &&
        (c = builder_args(p), 1) &&
        (d = block_suite(p))
    ) ? node_4(p, &f, a, b, c, d) : 0;
    return exit(p, &f, r);
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
    frame_t f = {169, p->pos, FUNC, 0, 0};
    FAstNode *a, *r;
    r = enter(p, &f) && (
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
    ) ? node_1(p, &f, a) : 0;
    return exit(p, &f, r);
}
