#include "include/internal/parser.h"


static void *single_input(parser_t *);
static void *single_input_4(parser_t *);
static void *file_input(parser_t *);
static void *eval_input(parser_t *);
static ast_list_t *eval_input_loop(parser_t *);
static void *stmt_list(parser_t *);
static ast_list_t *stmt_loop(parser_t *);
static void *stmt(parser_t *);
static void *stmt_1(parser_t *);
static void *simple_stmt(parser_t *);
static ast_list_t *small_stmt_delimited(parser_t *);
static void *small_stmt(parser_t *);
static void *del_stmt(parser_t *);
static void *return_stmt(parser_t *);
static void *raise_stmt(parser_t *);
static void *raise_stmt_3(parser_t *);
static void *nonlocal_stmt(parser_t *);
static void *assert_stmt(parser_t *);
static void *assert_stmt_3(parser_t *);
static void *name_list(parser_t *);
static ast_list_t *name_list_delimited(parser_t *);
static void *star_expr(parser_t *);
static void *exprlist(parser_t *);
static ast_list_t *expr_delimited(parser_t *);
static void *target(parser_t *);
static void *target_1(parser_t *);
static void *target_2(parser_t *);
static void *target_4(parser_t *);
static void *targetlist_sp(parser_t *);
static void *t_primary(parser_t *);
static void *t_primary_1(parser_t *);
static void *t_primary_2(parser_t *);
static void *t_primary_3(parser_t *);
static void *t_primary_4(parser_t *);
static void *t_lookahead(parser_t *);
static void *targetlist(parser_t *);
static ast_list_t *target_delimited(parser_t *);
static void *expr_or_star(parser_t *);
static void *exprlist_star(parser_t *);
static ast_list_t *expr_or_star_delimited(parser_t *);
static void *subscript(parser_t *);
static void *slicelist(parser_t *);
static ast_list_t *slice_delimited(parser_t *);
static void *slice(parser_t *);
static void *slice_1(parser_t *);
static void *slice_expr(parser_t *);
static void *dict_item(parser_t *);
static void *dict_item_1(parser_t *);
static void *dict_item_2(parser_t *);
static void *dict_items(parser_t *);
static ast_list_t *dict_item_delimited(parser_t *);
static void *list_item(parser_t *);
static void *list_items(parser_t *);
static ast_list_t *list_item_delimited(parser_t *);
static void *set_items(parser_t *);
static void *as_name(parser_t *);
static void *iter_for(parser_t *);
static void *iter_if(parser_t *);
static void *iterator(parser_t *);
static ast_list_t *iter_for_loop(parser_t *);
static void *list_iterator(parser_t *);
static void *dict_iterator(parser_t *);
static void *assignment(parser_t *);
static void *pubassign(parser_t *);
static void *annassign(parser_t *);
static void *annassign_4(parser_t *);
static void *augassign(parser_t *);
static void *simple_assign(parser_t *);
static ast_list_t *simple_assign_1_loop(parser_t *);
static void *simple_assign_1(parser_t *);
static void *augassign_op(parser_t *);
static void *import_name(parser_t *);
static void *import_from(parser_t *);
static void *import_from_names(parser_t *);
static void *import_from_names_2(parser_t *);
static ast_list_t *import_from_names_2_loop(parser_t *);
static void *import_from_items(parser_t *);
static void *import_as_names_sp(parser_t *);
static void *import_as_name(parser_t *);
static void *dotted_as_name(parser_t *);
static void *import_as_names(parser_t *);
static ast_list_t *import_as_name_delimited(parser_t *);
static void *dotted_as_names(parser_t *);
static ast_list_t *dotted_as_name_delimited(parser_t *);
static void *dotted_name(parser_t *);
static ast_list_t *dotted_name_delimited(parser_t *);
static void *compound_stmt(parser_t *);
static void *if_stmt(parser_t *);
static ast_list_t *elif_stmt_loop(parser_t *);
static void *elif_stmt(parser_t *);
static void *while_stmt(parser_t *);
static void *for_stmt(parser_t *);
static void *try_stmt(parser_t *);
static void *try_stmt_3(parser_t *);
static void *with_stmt(parser_t *);
static ast_list_t *expr_as_name_delimited(parser_t *);
static void *expr_as_name(parser_t *);
static void *block_suite(parser_t *);
static void *block_suite_1(parser_t *);
static void *block_suite_2(parser_t *);
static void *suite(parser_t *);
static void *suite_1(parser_t *);
static void *else_suite(parser_t *);
static void *finally_suite(parser_t *);
static void *except_clause(parser_t *);
static void *except_suite(parser_t *);
static ast_list_t *except_clause_loop(parser_t *);
static void *invocation(parser_t *);
static void *call_arg_list(parser_t *);
static ast_list_t *call_arg_delimited(parser_t *);
static void *call_arg(parser_t *);
static void *call_arg_1(parser_t *);
static void *call_arg_2(parser_t *);
static void *call_arg_3(parser_t *);
static void *call_arg_4(parser_t *);
static void *typed_arg_list(parser_t *);
static void *full_arg_list(parser_t *);
static ast_list_t *default_arg_delimited(parser_t *);
static void *full_arg_list_2(parser_t *);
static void *full_arg_list_2_2(parser_t *);
static void *args_kwargs(parser_t *);
static ast_list_t *args_kwargs_3_loop(parser_t *);
static void *args_kwargs_3(parser_t *);
static void *args_kwargs_4(parser_t *);
static void *kwargs(parser_t *);
static void *default_arg(parser_t *);
static void *default_arg_2(parser_t *);
static void *typed_arg(parser_t *);
static void *typed_arg_2(parser_t *);
static void *simple_arg(parser_t *);
static void *simple_arg_2(parser_t *);
static void *simple_args(parser_t *);
static ast_list_t *simple_arg_delimited(parser_t *);
static void *builder_hint(parser_t *);
static void *builder_args(parser_t *);
static void *builder_args_2(parser_t *);
static void *named_expr(parser_t *);
static void *named_expr_1(parser_t *);
static void *conditional(parser_t *);
static void *expr(parser_t *);
static void *disjunction(parser_t *);
static void *disjunction_1(parser_t *);
static void *conjunction(parser_t *);
static void *conjunction_1(parser_t *);
static void *inversion(parser_t *);
static void *inversion_1(parser_t *);
static void *comparison(parser_t *);
static void *comparison_1(parser_t *);
static ast_list_t *comparison_1_2_loop(parser_t *);
static void *comparison_1_2(parser_t *);
static void *comp_op(parser_t *);
static void *comp_op_8(parser_t *);
static void *comp_op_10(parser_t *);
static void *bitwise_or(parser_t *);
static void *bitwise_or_1(parser_t *);
static void *bitwise_xor(parser_t *);
static void *bitwise_xor_1(parser_t *);
static void *bitwise_and(parser_t *);
static void *bitwise_and_1(parser_t *);
static void *shift_expr(parser_t *);
static void *shift_expr_1(parser_t *);
static void *shift_expr_2(parser_t *);
static void *sum(parser_t *);
static void *sum_1(parser_t *);
static void *sum_2(parser_t *);
static void *term(parser_t *);
static void *term_1(parser_t *);
static void *term_2(parser_t *);
static void *term_3(parser_t *);
static void *term_4(parser_t *);
static void *term_5(parser_t *);
static void *pipe_expr(parser_t *);
static void *pipe_expr_1(parser_t *);
static void *factor(parser_t *);
static void *factor_1(parser_t *);
static void *factor_2(parser_t *);
static void *factor_3(parser_t *);
static void *power(parser_t *);
static void *power_1(parser_t *);
static void *primary(parser_t *);
static void *primary_1(parser_t *);
static void *primary_2(parser_t *);
static void *primary_3(parser_t *);
static void *tuple_atom(parser_t *);
static void *list_iterable(parser_t *);
static void *list_atom(parser_t *);
static void *set_atom(parser_t *);
static void *dict_iterable(parser_t *);
static void *dict_atom(parser_t *);
static void *builder(parser_t *);
static void *builder_1(parser_t *);
static void *builder_2(parser_t *);
static void *atom(parser_t *);



// Parser Entry Point
void *parse_grammar(parser_t *p, int entry_point) {
    switch (entry_point) {
    case 0:
        return single_input(p);
    case 1:
        return file_input(p);
    case 2:
        return eval_input(p);
    default:
        return 0;
    }
}

// single_input:
//     | NEWLINE
//     | ENDMARKER
//     | simple_stmt
//     | compound_stmt NEWLINE
static void *single_input(parser_t *p) {
    frame_t f = {1, p->pos, FUNC, 0, 0};
    token_t *_newline;
    token_t *_endmarker;
    void *_simple_stmt;
    void *_compound_stmt_newline;
    void *a;
    void *res_1;
    res_1 = enter_frame(p, &f) && (
        (a = consume(p, 2, "NEWLINE")) ||
        (a = consume(p, 1, "ENDMARKER")) ||
        (a = simple_stmt(p)) ||
        (a = single_input_4(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_1);
}

static void *single_input_4(parser_t *p) {
    frame_t f = {2, p->pos, FUNC, 0, 0};
    void *_compound_stmt;
    token_t *_newline;
    void *res_2;
    res_2 = enter_frame(p, &f) && (
        (_compound_stmt = compound_stmt(p)) &&
        (_newline = consume(p, 2, "NEWLINE"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_2);
}

// file_input:
//     | [stmt_list] ENDMARKER
static void *file_input(parser_t *p) {
    frame_t f = {3, p->pos, FUNC, 0, 0};
    void *_stmt_list;
    token_t *_endmarker;
    void *res_3;
    res_3 = enter_frame(p, &f) && (
        (_stmt_list = stmt_list(p), 1) &&
        (_endmarker = consume(p, 1, "ENDMARKER"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_3);
}

// eval_input:
//     | exprlist NEWLINE* ENDMARKER
static void *eval_input(parser_t *p) {
    frame_t f = {4, p->pos, FUNC, 0, 0};
    void *_exprlist;
    ast_list_t *_newlines;
    token_t *_endmarker;
    void *res_4;
    res_4 = enter_frame(p, &f) && (
        (_exprlist = exprlist(p)) &&
        (_newlines = eval_input_loop(p)) &&
        (_endmarker = consume(p, 1, "ENDMARKER"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_4);
}

static ast_list_t *eval_input_loop(parser_t *p) {
    ast_list_t *list = ast_list_new(p);
    token_t *_newline;
    while ((_newline = consume(p, 2, "NEWLINE"))) {
        ast_list_append(p, list, _newline);
    }
    return list;
}

// stmt_list:
//     | stmt+
static void *stmt_list(parser_t *p) {
    frame_t f = {5, p->pos, FUNC, 0, 0};
    ast_list_t *_stmts;
    void *res_5;
    res_5 = enter_frame(p, &f) && (
        (_stmts = stmt_loop(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_5);
}

static ast_list_t *stmt_loop(parser_t *p) {
    void *_stmt = stmt(p);
    if (!_stmt) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    do {
        ast_list_append(p, list, _stmt);
    } while ((_stmt = stmt(p)));
    return list;
}

// stmt:
//     | (simple_stmt | compound_stmt) NEWLINE
static void *stmt(parser_t *p) {
    frame_t f = {6, p->pos, FUNC, 0, 0};
    void *_simple_stmt_or_compound_stmt;
    token_t *_newline;
    void *res_6;
    res_6 = enter_frame(p, &f) && (
        (_simple_stmt_or_compound_stmt = stmt_1(p)) &&
        (_newline = consume(p, 2, "NEWLINE"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_6);
}

static void *stmt_1(parser_t *p) {
    frame_t f = {7, p->pos, FUNC, 0, 0};
    void *_simple_stmt;
    void *_compound_stmt;
    void *a;
    void *res_7;
    res_7 = enter_frame(p, &f) && (
        (a = simple_stmt(p)) ||
        (a = compound_stmt(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_7);
}

// simple_stmt:
//     | ';'.small_stmt+ [';']
static void *simple_stmt(parser_t *p) {
    frame_t f = {8, p->pos, FUNC, 0, 0};
    ast_list_t *_small_stmts;
    token_t *_is_semicolon;
    void *res_8;
    res_8 = enter_frame(p, &f) && (
        (_small_stmts = small_stmt_delimited(p)) &&
        (_is_semicolon = consume(p, 12, ";"), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_8);
}

static ast_list_t *small_stmt_delimited(parser_t *p) {
    void *_small_stmt = small_stmt(p);
    if (!_small_stmt) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _small_stmt);
        pos = p->pos;
    } while (consume(p, 12, ";") &&
            (_small_stmt = small_stmt(p)));
    p->pos = pos;
    return list;
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
static void *small_stmt(parser_t *p) {
    frame_t f = {9, p->pos, FUNC, 0, 0};
    token_t *_is_pass;
    token_t *_is_break;
    token_t *_is_continue;
    void *_return_stmt;
    void *_raise_stmt;
    void *_del_stmt;
    void *_nonlocal_stmt;
    void *_assert_stmt;
    void *_import_name;
    void *_import_from;
    void *_assignment;
    void *a;
    void *res_9;
    res_9 = enter_frame(p, &f) && (
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
    ) ? a : 0;
    return exit_frame(p, &f, res_9);
}

// del_stmt:
//     | 'del' targetlist
static void *del_stmt(parser_t *p) {
    frame_t f = {10, p->pos, FUNC, 0, 0};
    void *_targetlist;
    void *res_10;
    res_10 = enter_frame(p, &f) && (
        (consume(p, 79, "del")) &&
        (_targetlist = targetlist(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_10);
}

// return_stmt:
//     | 'return' [exprlist_star]
static void *return_stmt(parser_t *p) {
    frame_t f = {11, p->pos, FUNC, 0, 0};
    void *_exprlist_star;
    void *res_11;
    res_11 = enter_frame(p, &f) && (
        (consume(p, 54, "return")) &&
        (_exprlist_star = exprlist_star(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_11);
}

// raise_stmt:
//     | 'raise' expr ['from' expr]
static void *raise_stmt(parser_t *p) {
    frame_t f = {12, p->pos, FUNC, 0, 0};
    void *_expr;
    void *_from_expr;
    void *res_12;
    res_12 = enter_frame(p, &f) && (
        (consume(p, 78, "raise")) &&
        (_expr = expr(p)) &&
        (_from_expr = raise_stmt_3(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_12);
}

static void *raise_stmt_3(parser_t *p) {
    frame_t f = {13, p->pos, FUNC, 0, 0};
    void *_expr;
    void *res_13;
    res_13 = enter_frame(p, &f) && (
        (consume(p, 66, "from")) &&
        (_expr = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_13);
}

// nonlocal_stmt:
//     | 'nonlocal' name_list
static void *nonlocal_stmt(parser_t *p) {
    frame_t f = {14, p->pos, FUNC, 0, 0};
    void *_name_list;
    void *res_14;
    res_14 = enter_frame(p, &f) && (
        (consume(p, 55, "nonlocal")) &&
        (_name_list = name_list(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_14);
}

// assert_stmt:
//     | 'assert' expr [',' expr]
static void *assert_stmt(parser_t *p) {
    frame_t f = {15, p->pos, FUNC, 0, 0};
    void *_expr;
    void *_comma_expr;
    void *res_15;
    res_15 = enter_frame(p, &f) && (
        (consume(p, 80, "assert")) &&
        (_expr = expr(p)) &&
        (_comma_expr = assert_stmt_3(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_15);
}

static void *assert_stmt_3(parser_t *p) {
    frame_t f = {16, p->pos, FUNC, 0, 0};
    void *_expr;
    void *res_16;
    res_16 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_expr = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_16);
}

// name_list:
//     | ','.NAME+
static void *name_list(parser_t *p) {
    frame_t f = {17, p->pos, FUNC, 0, 0};
    ast_list_t *_names;
    void *res_17;
    res_17 = enter_frame(p, &f) && (
        (_names = name_list_delimited(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_17);
}

static ast_list_t *name_list_delimited(parser_t *p) {
    token_t *_name = consume(p, 3, "NAME");
    if (!_name) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _name);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_name = consume(p, 3, "NAME")));
    p->pos = pos;
    return list;
}

// star_expr:
//     | '*' bitwise_or
static void *star_expr(parser_t *p) {
    frame_t f = {18, p->pos, FUNC, 0, 0};
    void *_bitwise_or;
    void *res_18;
    res_18 = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (_bitwise_or = bitwise_or(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_18);
}

// exprlist:
//     | ','.expr+ [',']
static void *exprlist(parser_t *p) {
    frame_t f = {19, p->pos, FUNC, 0, 0};
    ast_list_t *_exprs;
    token_t *_is_comma;
    void *res_19;
    res_19 = enter_frame(p, &f) && (
        (_exprs = expr_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_19);
}

static ast_list_t *expr_delimited(parser_t *p) {
    void *_expr = expr(p);
    if (!_expr) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _expr);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_expr = expr(p)));
    p->pos = pos;
    return list;
}

// target:
//     | t_primary '.' NAME !t_lookahead
//     | t_primary subscript !t_lookahead
//     | NAME
//     | '(' targetlist_sp ')'
static void *target(parser_t *p) {
    frame_t f = {20, p->pos, FUNC, 0, 0};
    void *_target_1;
    void *_target_2;
    token_t *_name;
    void *_lpar_targetlist_sp_rpar;
    void *a;
    void *res_20;
    res_20 = enter_frame(p, &f) && (
        (a = target_1(p)) ||
        (a = target_2(p)) ||
        (a = consume(p, 3, "NAME")) ||
        (a = target_4(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_20);
}

static void *target_1(parser_t *p) {
    frame_t f = {21, p->pos, FUNC, 0, 0};
    void *_t_primary;
    token_t *_name;
    void *res_21;
    res_21 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (consume(p, 6, ".")) &&
        (_name = consume(p, 3, "NAME")) &&
        (!test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_21);
}

static void *target_2(parser_t *p) {
    frame_t f = {22, p->pos, FUNC, 0, 0};
    void *_t_primary;
    void *_subscript;
    void *res_22;
    res_22 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (_subscript = subscript(p)) &&
        (!test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_22);
}

static void *target_4(parser_t *p) {
    frame_t f = {23, p->pos, FUNC, 0, 0};
    void *_targetlist_sp;
    void *res_23;
    res_23 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_targetlist_sp = targetlist_sp(p)) &&
        (consume(p, 14, ")"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_23);
}

// targetlist_sp (allow_whitespace=true):
//     | targetlist
static void *targetlist_sp(parser_t *p) {
    frame_t f = {24, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    void *_targetlist;
    void *res_24;
    res_24 = enter_frame(p, &f) && (
        (_targetlist = targetlist(p))
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, res_24);
}

// t_primary (left_recursive):
//     | t_primary '.' NAME &t_lookahead
//     | t_primary invocation &t_lookahead
//     | t_primary subscript &t_lookahead
//     | atom &t_lookahead
static void *t_primary(parser_t *p) {
    frame_t f = {25, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    void *a = 0;
    void *res_25 = 0;
    void *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = t_primary_1(p)) ||
        (a = t_primary_2(p)) ||
        (a = t_primary_3(p)) ||
        (a = t_primary_4(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_25 = max;
    return exit_frame(p, &f, res_25);
}

static void *t_primary_1(parser_t *p) {
    frame_t f = {26, p->pos, FUNC, 0, 0};
    void *_t_primary;
    token_t *_name;
    void *res_26;
    res_26 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (consume(p, 6, ".")) &&
        (_name = consume(p, 3, "NAME")) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_26);
}

static void *t_primary_2(parser_t *p) {
    frame_t f = {27, p->pos, FUNC, 0, 0};
    void *_t_primary;
    void *_invocation;
    void *res_27;
    res_27 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (_invocation = invocation(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_27);
}

static void *t_primary_3(parser_t *p) {
    frame_t f = {28, p->pos, FUNC, 0, 0};
    void *_t_primary;
    void *_subscript;
    void *res_28;
    res_28 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (_subscript = subscript(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_28);
}

static void *t_primary_4(parser_t *p) {
    frame_t f = {29, p->pos, FUNC, 0, 0};
    void *_atom;
    void *res_29;
    res_29 = enter_frame(p, &f) && (
        (_atom = atom(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_29);
}

// t_lookahead:
//     | '.'
//     | '('
//     | '['
static void *t_lookahead(parser_t *p) {
    frame_t f = {30, p->pos, FUNC, 0, 0};
    token_t *_is_dot;
    token_t *_is_lpar;
    token_t *_is_lsqb;
    void *a;
    void *res_30;
    res_30 = enter_frame(p, &f) && (
        (a = consume(p, 6, ".")) ||
        (a = consume(p, 13, "(")) ||
        (a = consume(p, 17, "["))
    ) ? a : 0;
    return exit_frame(p, &f, res_30);
}

// targetlist:
//     | ','.target+ [',']
static void *targetlist(parser_t *p) {
    frame_t f = {31, p->pos, FUNC, 0, 0};
    ast_list_t *_targets;
    token_t *_is_comma;
    void *res_31;
    res_31 = enter_frame(p, &f) && (
        (_targets = target_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_31);
}

static ast_list_t *target_delimited(parser_t *p) {
    void *_target = target(p);
    if (!_target) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _target);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_target = target(p)));
    p->pos = pos;
    return list;
}

// expr_or_star:
//     | star_expr
//     | expr
static void *expr_or_star(parser_t *p) {
    frame_t f = {32, p->pos, FUNC, 0, 0};
    void *_star_expr;
    void *_expr;
    void *a;
    void *res_32;
    res_32 = enter_frame(p, &f) && (
        (a = star_expr(p)) ||
        (a = expr(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_32);
}

// exprlist_star:
//     | ','.expr_or_star+ [',']
static void *exprlist_star(parser_t *p) {
    frame_t f = {33, p->pos, FUNC, 0, 0};
    ast_list_t *_expr_or_stars;
    token_t *_is_comma;
    void *res_33;
    res_33 = enter_frame(p, &f) && (
        (_expr_or_stars = expr_or_star_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_33);
}

static ast_list_t *expr_or_star_delimited(parser_t *p) {
    void *_expr_or_star = expr_or_star(p);
    if (!_expr_or_star) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _expr_or_star);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_expr_or_star = expr_or_star(p)));
    p->pos = pos;
    return list;
}

// subscript:
//     | '[' slicelist ']'
static void *subscript(parser_t *p) {
    frame_t f = {34, p->pos, FUNC, 0, 0};
    void *_slicelist;
    void *res_34;
    res_34 = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (_slicelist = slicelist(p)) &&
        (consume(p, 18, "]"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_34);
}

// slicelist:
//     | ','.slice+ [',']
static void *slicelist(parser_t *p) {
    frame_t f = {35, p->pos, FUNC, 0, 0};
    ast_list_t *_slices;
    token_t *_is_comma;
    void *res_35;
    res_35 = enter_frame(p, &f) && (
        (_slices = slice_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_35);
}

static ast_list_t *slice_delimited(parser_t *p) {
    void *_slice = slice(p);
    if (!_slice) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _slice);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_slice = slice(p)));
    p->pos = pos;
    return list;
}

// slice:
//     | [expr] slice_expr [slice_expr]
//     | expr
static void *slice(parser_t *p) {
    frame_t f = {36, p->pos, FUNC, 0, 0};
    void *_slice_1;
    void *_expr;
    void *a;
    void *res_36;
    res_36 = enter_frame(p, &f) && (
        (a = slice_1(p)) ||
        (a = expr(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_36);
}

static void *slice_1(parser_t *p) {
    frame_t f = {37, p->pos, FUNC, 0, 0};
    void *_expr;
    void *_slice_expr;
    void *_slice_expr_1;
    void *res_37;
    res_37 = enter_frame(p, &f) && (
        (_expr = expr(p), 1) &&
        (_slice_expr = slice_expr(p)) &&
        (_slice_expr_1 = slice_expr(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_37);
}

// slice_expr:
//     | ':' [expr]
static void *slice_expr(parser_t *p) {
    frame_t f = {38, p->pos, FUNC, 0, 0};
    void *_expr;
    void *res_38;
    res_38 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_expr = expr(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_38);
}

// dict_item:
//     | expr ':' expr
//     | '**' bitwise_or
static void *dict_item(parser_t *p) {
    frame_t f = {39, p->pos, FUNC, 0, 0};
    void *_expr_colon_expr;
    void *_power_bitwise_or;
    void *a;
    void *res_39;
    res_39 = enter_frame(p, &f) && (
        (a = dict_item_1(p)) ||
        (a = dict_item_2(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_39);
}

static void *dict_item_1(parser_t *p) {
    frame_t f = {40, p->pos, FUNC, 0, 0};
    void *_expr;
    void *_expr_1;
    void *res_40;
    res_40 = enter_frame(p, &f) && (
        (_expr = expr(p)) &&
        (consume(p, 9, ":")) &&
        (_expr_1 = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_40);
}

static void *dict_item_2(parser_t *p) {
    frame_t f = {41, p->pos, FUNC, 0, 0};
    void *_bitwise_or;
    void *res_41;
    res_41 = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (_bitwise_or = bitwise_or(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_41);
}

// dict_items (allow_whitespace=true):
//     | ','.dict_item+ [',']
static void *dict_items(parser_t *p) {
    frame_t f = {42, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    ast_list_t *_dict_items;
    token_t *_is_comma;
    void *res_42;
    res_42 = enter_frame(p, &f) && (
        (_dict_items = dict_item_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, res_42);
}

static ast_list_t *dict_item_delimited(parser_t *p) {
    void *_dict_item = dict_item(p);
    if (!_dict_item) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _dict_item);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_dict_item = dict_item(p)));
    p->pos = pos;
    return list;
}

// list_item:
//     | star_expr
//     | named_expr
static void *list_item(parser_t *p) {
    frame_t f = {43, p->pos, FUNC, 0, 0};
    void *_star_expr;
    void *_named_expr;
    void *a;
    void *res_43;
    res_43 = enter_frame(p, &f) && (
        (a = star_expr(p)) ||
        (a = named_expr(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_43);
}

// list_items (allow_whitespace=true):
//     | ','.list_item+ [',']
static void *list_items(parser_t *p) {
    frame_t f = {44, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    ast_list_t *_list_items;
    token_t *_is_comma;
    void *res_44;
    res_44 = enter_frame(p, &f) && (
        (_list_items = list_item_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, res_44);
}

static ast_list_t *list_item_delimited(parser_t *p) {
    void *_list_item = list_item(p);
    if (!_list_item) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _list_item);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_list_item = list_item(p)));
    p->pos = pos;
    return list;
}

// set_items (allow_whitespace=true):
//     | exprlist_star
static void *set_items(parser_t *p) {
    frame_t f = {45, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    void *_exprlist_star;
    void *res_45;
    res_45 = enter_frame(p, &f) && (
        (_exprlist_star = exprlist_star(p))
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, res_45);
}

// as_name:
//     | 'as' NAME
static void *as_name(parser_t *p) {
    frame_t f = {46, p->pos, FUNC, 0, 0};
    token_t *_name;
    void *res_46;
    res_46 = enter_frame(p, &f) && (
        (consume(p, 65, "as")) &&
        (_name = consume(p, 3, "NAME"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_46);
}

// iter_for:
//     | 'for' targetlist 'in' disjunction [iter_if]
static void *iter_for(parser_t *p) {
    frame_t f = {47, p->pos, FUNC, 0, 0};
    void *_targetlist;
    void *_disjunction;
    void *_iter_if;
    void *res_47;
    res_47 = enter_frame(p, &f) && (
        (consume(p, 72, "for")) &&
        (_targetlist = targetlist(p)) &&
        (consume(p, 63, "in")) &&
        (_disjunction = disjunction(p)) &&
        (_iter_if = iter_if(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_47);
}

// iter_if:
//     | 'if' named_expr
static void *iter_if(parser_t *p) {
    frame_t f = {48, p->pos, FUNC, 0, 0};
    void *_named_expr;
    void *res_48;
    res_48 = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (_named_expr = named_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_48);
}

// iterator:
//     | iter_for* 'for' targetlist [iter_if]
static void *iterator(parser_t *p) {
    frame_t f = {49, p->pos, FUNC, 0, 0};
    ast_list_t *_iter_fors;
    void *_targetlist;
    void *_iter_if;
    void *res_49;
    res_49 = enter_frame(p, &f) && (
        (_iter_fors = iter_for_loop(p)) &&
        (consume(p, 72, "for")) &&
        (_targetlist = targetlist(p)) &&
        (_iter_if = iter_if(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_49);
}

static ast_list_t *iter_for_loop(parser_t *p) {
    ast_list_t *list = ast_list_new(p);
    void *_iter_for;
    while ((_iter_for = iter_for(p))) {
        ast_list_append(p, list, _iter_for);
    }
    return list;
}

// list_iterator (allow_whitespace=true):
//     | expr_or_star iterator
static void *list_iterator(parser_t *p) {
    frame_t f = {50, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    void *_expr_or_star;
    void *_iterator;
    void *res_50;
    res_50 = enter_frame(p, &f) && (
        (_expr_or_star = expr_or_star(p)) &&
        (_iterator = iterator(p))
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, res_50);
}

// dict_iterator (allow_whitespace=true):
//     | dict_item iterator
static void *dict_iterator(parser_t *p) {
    frame_t f = {51, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    void *_dict_item;
    void *_iterator;
    void *res_51;
    res_51 = enter_frame(p, &f) && (
        (_dict_item = dict_item(p)) &&
        (_iterator = iterator(p))
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, res_51);
}

// assignment:
//     | pubassign
//     | annassign
//     | augassign
//     | simple_assign
static void *assignment(parser_t *p) {
    frame_t f = {52, p->pos, FUNC, 0, 0};
    void *_pubassign;
    void *_annassign;
    void *_augassign;
    void *_simple_assign;
    void *a;
    void *res_52;
    res_52 = enter_frame(p, &f) && (
        (a = pubassign(p)) ||
        (a = annassign(p)) ||
        (a = augassign(p)) ||
        (a = simple_assign(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_52);
}

// pubassign:
//     | '/' NAME '=' exprlist
static void *pubassign(parser_t *p) {
    frame_t f = {53, p->pos, FUNC, 0, 0};
    token_t *_name;
    void *_exprlist;
    void *res_53;
    res_53 = enter_frame(p, &f) && (
        (consume(p, 24, "/")) &&
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 8, "=")) &&
        (_exprlist = exprlist(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_53);
}

// annassign:
//     | target ':' expr ['=' exprlist]
static void *annassign(parser_t *p) {
    frame_t f = {54, p->pos, FUNC, 0, 0};
    void *_target;
    void *_expr;
    void *_assign_exprlist;
    void *res_54;
    res_54 = enter_frame(p, &f) && (
        (_target = target(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p)) &&
        (_assign_exprlist = annassign_4(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_54);
}

static void *annassign_4(parser_t *p) {
    frame_t f = {55, p->pos, FUNC, 0, 0};
    void *_exprlist;
    void *res_55;
    res_55 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_exprlist = exprlist(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_55);
}

// augassign:
//     | target augassign_op exprlist
static void *augassign(parser_t *p) {
    frame_t f = {56, p->pos, FUNC, 0, 0};
    void *_target;
    void *_augassign_op;
    void *_exprlist;
    void *res_56;
    res_56 = enter_frame(p, &f) && (
        (_target = target(p)) &&
        (_augassign_op = augassign_op(p)) &&
        (_exprlist = exprlist(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_56);
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
static void *simple_assign(parser_t *p) {
    frame_t f = {57, p->pos, FUNC, 0, 0};
    ast_list_t *_targetlist_assigns;
    void *_exprlist_star;
    void *res_57;
    res_57 = enter_frame(p, &f) && (
        (_targetlist_assigns = simple_assign_1_loop(p)) &&
        (_exprlist_star = exprlist_star(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_57);
}

static ast_list_t *simple_assign_1_loop(parser_t *p) {
    ast_list_t *list = ast_list_new(p);
    void *_targetlist_assign;
    while ((_targetlist_assign = simple_assign_1(p))) {
        ast_list_append(p, list, _targetlist_assign);
    }
    return list;
}

static void *simple_assign_1(parser_t *p) {
    frame_t f = {58, p->pos, FUNC, 0, 0};
    void *_targetlist;
    void *res_58;
    res_58 = enter_frame(p, &f) && (
        (_targetlist = targetlist(p)) &&
        (consume(p, 8, "="))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_58);
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
static void *augassign_op(parser_t *p) {
    frame_t f = {59, p->pos, FUNC, 0, 0};
    token_t *_is_plus_assign;
    token_t *_is_minus_assign;
    token_t *_is_times_assign;
    token_t *_is_matrix_times_assign;
    token_t *_is_div_assign;
    token_t *_is_modulus_assign;
    token_t *_is_bit_and_assign;
    token_t *_is_bit_or_assign;
    token_t *_is_bit_xor_assign;
    token_t *_is_lshift_assign;
    token_t *_is_rshift_assign;
    token_t *_is_power_assign;
    token_t *_is_floor_div_assign;
    void *a;
    void *res_59;
    res_59 = enter_frame(p, &f) && (
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
    ) ? a : 0;
    return exit_frame(p, &f, res_59);
}

// import_name:
//     | 'import' dotted_as_names
static void *import_name(parser_t *p) {
    frame_t f = {60, p->pos, FUNC, 0, 0};
    void *_dotted_as_names;
    void *res_60;
    res_60 = enter_frame(p, &f) && (
        (consume(p, 67, "import")) &&
        (_dotted_as_names = dotted_as_names(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_60);
}

// import_from:
//     | 'from' import_from_names 'import' import_from_items
static void *import_from(parser_t *p) {
    frame_t f = {61, p->pos, FUNC, 0, 0};
    void *_import_from_names;
    void *_import_from_items;
    void *res_61;
    res_61 = enter_frame(p, &f) && (
        (consume(p, 66, "from")) &&
        (_import_from_names = import_from_names(p)) &&
        (consume(p, 67, "import")) &&
        (_import_from_items = import_from_items(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_61);
}

// import_from_names:
//     | dotted_name
//     | '.'+ [dotted_name]
static void *import_from_names(parser_t *p) {
    frame_t f = {62, p->pos, FUNC, 0, 0};
    void *_dotted_name;
    void *_import_from_names_2;
    void *a;
    void *res_62;
    res_62 = enter_frame(p, &f) && (
        (a = dotted_name(p)) ||
        (a = import_from_names_2(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_62);
}

static void *import_from_names_2(parser_t *p) {
    frame_t f = {63, p->pos, FUNC, 0, 0};
    void *_dotted_name;
    void *res_63;
    res_63 = enter_frame(p, &f) && (
        (import_from_names_2_loop(p)) &&
        (_dotted_name = dotted_name(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_63);
}

static ast_list_t *import_from_names_2_loop(parser_t *p) {
    token_t *_is_dot = consume(p, 6, ".");
    if (!_is_dot) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    do {
        ast_list_append(p, list, _is_dot);
    } while ((_is_dot = consume(p, 6, ".")));
    return list;
}

// import_from_items:
//     | '*'
//     | import_as_names_sp
//     | import_as_names
static void *import_from_items(parser_t *p) {
    frame_t f = {64, p->pos, FUNC, 0, 0};
    token_t *_is_times;
    void *_import_as_names_sp;
    void *_import_as_names;
    void *a;
    void *res_64;
    res_64 = enter_frame(p, &f) && (
        (a = consume(p, 23, "*")) ||
        (a = import_as_names_sp(p)) ||
        (a = import_as_names(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_64);
}

// import_as_names_sp (allow_whitespace=true):
//     | '(' import_as_names [','] ')'
static void *import_as_names_sp(parser_t *p) {
    frame_t f = {65, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    void *_import_as_names;
    token_t *_is_comma;
    void *res_65;
    res_65 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_import_as_names = import_as_names(p)) &&
        (_is_comma = consume(p, 7, ","), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, res_65);
}

// import_as_name:
//     | NAME [as_name]
static void *import_as_name(parser_t *p) {
    frame_t f = {66, p->pos, FUNC, 0, 0};
    token_t *_name;
    void *_as_name;
    void *res_66;
    res_66 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_as_name = as_name(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_66);
}

// dotted_as_name:
//     | dotted_name [as_name]
static void *dotted_as_name(parser_t *p) {
    frame_t f = {67, p->pos, FUNC, 0, 0};
    void *_dotted_name;
    void *_as_name;
    void *res_67;
    res_67 = enter_frame(p, &f) && (
        (_dotted_name = dotted_name(p)) &&
        (_as_name = as_name(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_67);
}

// import_as_names:
//     | ','.import_as_name+
static void *import_as_names(parser_t *p) {
    frame_t f = {68, p->pos, FUNC, 0, 0};
    ast_list_t *_import_as_names;
    void *res_68;
    res_68 = enter_frame(p, &f) && (
        (_import_as_names = import_as_name_delimited(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_68);
}

static ast_list_t *import_as_name_delimited(parser_t *p) {
    void *_import_as_name = import_as_name(p);
    if (!_import_as_name) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _import_as_name);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_import_as_name = import_as_name(p)));
    p->pos = pos;
    return list;
}

// dotted_as_names:
//     | ','.dotted_as_name+
static void *dotted_as_names(parser_t *p) {
    frame_t f = {69, p->pos, FUNC, 0, 0};
    ast_list_t *_dotted_as_names;
    void *res_69;
    res_69 = enter_frame(p, &f) && (
        (_dotted_as_names = dotted_as_name_delimited(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_69);
}

static ast_list_t *dotted_as_name_delimited(parser_t *p) {
    void *_dotted_as_name = dotted_as_name(p);
    if (!_dotted_as_name) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _dotted_as_name);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_dotted_as_name = dotted_as_name(p)));
    p->pos = pos;
    return list;
}

// dotted_name:
//     | '.'.NAME+
static void *dotted_name(parser_t *p) {
    frame_t f = {70, p->pos, FUNC, 0, 0};
    ast_list_t *_names;
    void *res_70;
    res_70 = enter_frame(p, &f) && (
        (_names = dotted_name_delimited(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_70);
}

static ast_list_t *dotted_name_delimited(parser_t *p) {
    token_t *_name = consume(p, 3, "NAME");
    if (!_name) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _name);
        pos = p->pos;
    } while (consume(p, 6, ".") &&
            (_name = consume(p, 3, "NAME")));
    p->pos = pos;
    return list;
}

// compound_stmt:
//     | if_stmt
//     | while_stmt
//     | for_stmt
//     | try_stmt
//     | with_stmt
static void *compound_stmt(parser_t *p) {
    frame_t f = {71, p->pos, FUNC, 0, 0};
    void *_if_stmt;
    void *_while_stmt;
    void *_for_stmt;
    void *_try_stmt;
    void *_with_stmt;
    void *a;
    void *res_71;
    res_71 = enter_frame(p, &f) && (
        (a = if_stmt(p)) ||
        (a = while_stmt(p)) ||
        (a = for_stmt(p)) ||
        (a = try_stmt(p)) ||
        (a = with_stmt(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_71);
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
static void *if_stmt(parser_t *p) {
    frame_t f = {72, p->pos, FUNC, 0, 0};
    void *_named_expr;
    void *_suite;
    ast_list_t *_elif_stmts;
    void *_else_suite;
    void *res_72;
    res_72 = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (_named_expr = named_expr(p)) &&
        (_suite = suite(p)) &&
        (_elif_stmts = elif_stmt_loop(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_72);
}

static ast_list_t *elif_stmt_loop(parser_t *p) {
    ast_list_t *list = ast_list_new(p);
    void *_elif_stmt;
    while ((_elif_stmt = elif_stmt(p))) {
        ast_list_append(p, list, _elif_stmt);
    }
    return list;
}

// elif_stmt:
//     | 'elif' named_expr suite
static void *elif_stmt(parser_t *p) {
    frame_t f = {73, p->pos, FUNC, 0, 0};
    void *_named_expr;
    void *_suite;
    void *res_73;
    res_73 = enter_frame(p, &f) && (
        (consume(p, 57, "elif")) &&
        (_named_expr = named_expr(p)) &&
        (_suite = suite(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_73);
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
static void *while_stmt(parser_t *p) {
    frame_t f = {74, p->pos, FUNC, 0, 0};
    void *_named_expr;
    void *_suite;
    void *_else_suite;
    void *res_74;
    res_74 = enter_frame(p, &f) && (
        (consume(p, 71, "while")) &&
        (_named_expr = named_expr(p)) &&
        (_suite = suite(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_74);
}

// for_stmt:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
static void *for_stmt(parser_t *p) {
    frame_t f = {75, p->pos, FUNC, 0, 0};
    void *_targetlist;
    void *_exprlist;
    void *_suite;
    void *_else_suite;
    void *res_75;
    res_75 = enter_frame(p, &f) && (
        (consume(p, 72, "for")) &&
        (_targetlist = targetlist(p)) &&
        (consume(p, 63, "in")) &&
        (_exprlist = exprlist(p)) &&
        (_suite = suite(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_75);
}

// try_stmt:
//     | 'try' suite (except_suite | finally_suite)
static void *try_stmt(parser_t *p) {
    frame_t f = {76, p->pos, FUNC, 0, 0};
    void *_suite;
    void *_except_suite_or_finally_suite;
    void *res_76;
    res_76 = enter_frame(p, &f) && (
        (consume(p, 75, "try")) &&
        (_suite = suite(p)) &&
        (_except_suite_or_finally_suite = try_stmt_3(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_76);
}

static void *try_stmt_3(parser_t *p) {
    frame_t f = {77, p->pos, FUNC, 0, 0};
    void *_except_suite;
    void *_finally_suite;
    void *a;
    void *res_77;
    res_77 = enter_frame(p, &f) && (
        (a = except_suite(p)) ||
        (a = finally_suite(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_77);
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
static void *with_stmt(parser_t *p) {
    frame_t f = {78, p->pos, FUNC, 0, 0};
    ast_list_t *_expr_as_names;
    void *_suite;
    void *res_78;
    res_78 = enter_frame(p, &f) && (
        (consume(p, 68, "with")) &&
        (_expr_as_names = expr_as_name_delimited(p)) &&
        (_suite = suite(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_78);
}

static ast_list_t *expr_as_name_delimited(parser_t *p) {
    void *_expr_as_name = expr_as_name(p);
    if (!_expr_as_name) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _expr_as_name);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_expr_as_name = expr_as_name(p)));
    p->pos = pos;
    return list;
}

// expr_as_name:
//     | expr [as_name]
static void *expr_as_name(parser_t *p) {
    frame_t f = {79, p->pos, FUNC, 0, 0};
    void *_expr;
    void *_as_name;
    void *res_79;
    res_79 = enter_frame(p, &f) && (
        (_expr = expr(p)) &&
        (_as_name = as_name(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_79);
}

// block_suite (allow_whitespace=false):
//     | '{' NEWLINE stmt_list '}'
//     | '{' [simple_stmt] '}'
static void *block_suite(parser_t *p) {
    frame_t f = {80, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace=0;
    void *_block_suite_1;
    void *_block_suite_2;
    void *a;
    void *res_80;
    res_80 = enter_frame(p, &f) && (
        (a = block_suite_1(p)) ||
        (a = block_suite_2(p))
    ) ? a : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, res_80);
}

static void *block_suite_1(parser_t *p) {
    frame_t f = {81, p->pos, FUNC, 0, 0};
    token_t *_newline;
    void *_stmt_list;
    void *res_81;
    res_81 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_newline = consume(p, 2, "NEWLINE")) &&
        (_stmt_list = stmt_list(p)) &&
        (consume(p, 16, "}"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_81);
}

static void *block_suite_2(parser_t *p) {
    frame_t f = {82, p->pos, FUNC, 0, 0};
    void *_simple_stmt;
    void *res_82;
    res_82 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_simple_stmt = simple_stmt(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_82);
}

// suite:
//     | ':' simple_stmt
//     | block_suite
static void *suite(parser_t *p) {
    frame_t f = {83, p->pos, FUNC, 0, 0};
    void *_colon_simple_stmt;
    void *_block_suite;
    void *a;
    void *res_83;
    res_83 = enter_frame(p, &f) && (
        (a = suite_1(p)) ||
        (a = block_suite(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_83);
}

static void *suite_1(parser_t *p) {
    frame_t f = {84, p->pos, FUNC, 0, 0};
    void *_simple_stmt;
    void *res_84;
    res_84 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_simple_stmt = simple_stmt(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_84);
}

// else_suite:
//     | 'else' suite
static void *else_suite(parser_t *p) {
    frame_t f = {85, p->pos, FUNC, 0, 0};
    void *_suite;
    void *res_85;
    res_85 = enter_frame(p, &f) && (
        (consume(p, 58, "else")) &&
        (_suite = suite(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_85);
}

// finally_suite:
//     | 'finally' suite
static void *finally_suite(parser_t *p) {
    frame_t f = {86, p->pos, FUNC, 0, 0};
    void *_suite;
    void *res_86;
    res_86 = enter_frame(p, &f) && (
        (consume(p, 77, "finally")) &&
        (_suite = suite(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_86);
}

// except_clause:
//     | 'except' [expr_as_name] suite
static void *except_clause(parser_t *p) {
    frame_t f = {87, p->pos, FUNC, 0, 0};
    void *_expr_as_name;
    void *_suite;
    void *res_87;
    res_87 = enter_frame(p, &f) && (
        (consume(p, 76, "except")) &&
        (_expr_as_name = expr_as_name(p), 1) &&
        (_suite = suite(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_87);
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
static void *except_suite(parser_t *p) {
    frame_t f = {88, p->pos, FUNC, 0, 0};
    ast_list_t *_except_clauses;
    void *_else_suite;
    void *_finally_suite;
    void *res_88;
    res_88 = enter_frame(p, &f) && (
        (_except_clauses = except_clause_loop(p)) &&
        (_else_suite = else_suite(p), 1) &&
        (_finally_suite = finally_suite(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_88);
}

static ast_list_t *except_clause_loop(parser_t *p) {
    void *_except_clause = except_clause(p);
    if (!_except_clause) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    do {
        ast_list_append(p, list, _except_clause);
    } while ((_except_clause = except_clause(p)));
    return list;
}

// invocation:
//     | '(' [call_arg_list] ')'
static void *invocation(parser_t *p) {
    frame_t f = {89, p->pos, FUNC, 0, 0};
    void *_call_arg_list;
    void *res_89;
    res_89 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_call_arg_list = call_arg_list(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_89);
}

// call_arg_list (allow_whitespace=true):
//     | ','.call_arg+ [',']
static void *call_arg_list(parser_t *p) {
    frame_t f = {90, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    ast_list_t *_call_args;
    token_t *_is_comma;
    void *res_90;
    res_90 = enter_frame(p, &f) && (
        (_call_args = call_arg_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, res_90);
}

static ast_list_t *call_arg_delimited(parser_t *p) {
    void *_call_arg = call_arg(p);
    if (!_call_arg) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _call_arg);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_call_arg = call_arg(p)));
    p->pos = pos;
    return list;
}

// call_arg:
//     | NAME ':=' expr
//     | NAME '=' expr
//     | '**' expr
//     | '*' expr
//     | expr
static void *call_arg(parser_t *p) {
    frame_t f = {91, p->pos, FUNC, 0, 0};
    void *_name_asgn_expr_expr;
    void *_name_assign_expr;
    void *_power_expr;
    void *_times_expr;
    void *_expr;
    void *a;
    void *res_91;
    res_91 = enter_frame(p, &f) && (
        (a = call_arg_1(p)) ||
        (a = call_arg_2(p)) ||
        (a = call_arg_3(p)) ||
        (a = call_arg_4(p)) ||
        (a = expr(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_91);
}

static void *call_arg_1(parser_t *p) {
    frame_t f = {92, p->pos, FUNC, 0, 0};
    token_t *_name;
    void *_expr;
    void *res_92;
    res_92 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (_expr = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_92);
}

static void *call_arg_2(parser_t *p) {
    frame_t f = {93, p->pos, FUNC, 0, 0};
    token_t *_name;
    void *_expr;
    void *res_93;
    res_93 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 8, "=")) &&
        (_expr = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_93);
}

static void *call_arg_3(parser_t *p) {
    frame_t f = {94, p->pos, FUNC, 0, 0};
    void *_expr;
    void *res_94;
    res_94 = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (_expr = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_94);
}

static void *call_arg_4(parser_t *p) {
    frame_t f = {95, p->pos, FUNC, 0, 0};
    void *_expr;
    void *res_95;
    res_95 = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (_expr = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_95);
}

// typed_arg_list (allow_whitespace=true):
//     | kwargs
//     | args_kwargs
//     | full_arg_list
static void *typed_arg_list(parser_t *p) {
    frame_t f = {96, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    void *_kwargs;
    void *_args_kwargs;
    void *_full_arg_list;
    void *a;
    void *res_96;
    res_96 = enter_frame(p, &f) && (
        (a = kwargs(p)) ||
        (a = args_kwargs(p)) ||
        (a = full_arg_list(p))
    ) ? a : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, res_96);
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
static void *full_arg_list(parser_t *p) {
    frame_t f = {97, p->pos, FUNC, 0, 0};
    ast_list_t *_default_args;
    void *_full_arg_list_2;
    void *res_97;
    res_97 = enter_frame(p, &f) && (
        (_default_args = default_arg_delimited(p)) &&
        (_full_arg_list_2 = full_arg_list_2(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_97);
}

static ast_list_t *default_arg_delimited(parser_t *p) {
    void *_default_arg = default_arg(p);
    if (!_default_arg) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _default_arg);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_default_arg = default_arg(p)));
    p->pos = pos;
    return list;
}

static void *full_arg_list_2(parser_t *p) {
    frame_t f = {98, p->pos, FUNC, 0, 0};
    void *_kwargs_or_args_kwargs;
    void *res_98;
    res_98 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_kwargs_or_args_kwargs = full_arg_list_2_2(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_98);
}

static void *full_arg_list_2_2(parser_t *p) {
    frame_t f = {99, p->pos, FUNC, 0, 0};
    void *_kwargs;
    void *_args_kwargs;
    void *a;
    void *res_99;
    res_99 = enter_frame(p, &f) && (
        (a = kwargs(p)) ||
        (a = args_kwargs(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_99);
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
static void *args_kwargs(parser_t *p) {
    frame_t f = {100, p->pos, FUNC, 0, 0};
    void *_typed_arg;
    ast_list_t *_comma_default_args;
    void *_args_kwargs_4;
    void *res_100;
    res_100 = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (_typed_arg = typed_arg(p), 1) &&
        (_comma_default_args = args_kwargs_3_loop(p)) &&
        (_args_kwargs_4 = args_kwargs_4(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_100);
}

static ast_list_t *args_kwargs_3_loop(parser_t *p) {
    ast_list_t *list = ast_list_new(p);
    void *_comma_default_arg;
    while ((_comma_default_arg = args_kwargs_3(p))) {
        ast_list_append(p, list, _comma_default_arg);
    }
    return list;
}

static void *args_kwargs_3(parser_t *p) {
    frame_t f = {101, p->pos, FUNC, 0, 0};
    void *_default_arg;
    void *res_101;
    res_101 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_default_arg = default_arg(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_101);
}

static void *args_kwargs_4(parser_t *p) {
    frame_t f = {102, p->pos, FUNC, 0, 0};
    void *_kwargs;
    void *res_102;
    res_102 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_kwargs = kwargs(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_102);
}

// kwargs:
//     | '**' typed_arg [',']
static void *kwargs(parser_t *p) {
    frame_t f = {103, p->pos, FUNC, 0, 0};
    void *_typed_arg;
    token_t *_is_comma;
    void *res_103;
    res_103 = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (_typed_arg = typed_arg(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_103);
}

// default_arg:
//     | typed_arg ['=' expr]
static void *default_arg(parser_t *p) {
    frame_t f = {104, p->pos, FUNC, 0, 0};
    void *_typed_arg;
    void *_assign_expr;
    void *res_104;
    res_104 = enter_frame(p, &f) && (
        (_typed_arg = typed_arg(p)) &&
        (_assign_expr = default_arg_2(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_104);
}

static void *default_arg_2(parser_t *p) {
    frame_t f = {105, p->pos, FUNC, 0, 0};
    void *_expr;
    void *res_105;
    res_105 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_expr = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_105);
}

// typed_arg:
//     | NAME [':' expr]
static void *typed_arg(parser_t *p) {
    frame_t f = {106, p->pos, FUNC, 0, 0};
    token_t *_name;
    void *_colon_expr;
    void *res_106;
    res_106 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_colon_expr = typed_arg_2(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_106);
}

static void *typed_arg_2(parser_t *p) {
    frame_t f = {107, p->pos, FUNC, 0, 0};
    void *_expr;
    void *res_107;
    res_107 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_107);
}

// simple_arg:
//     | NAME ['=' expr]
static void *simple_arg(parser_t *p) {
    frame_t f = {108, p->pos, FUNC, 0, 0};
    token_t *_name;
    void *_assign_expr;
    void *res_108;
    res_108 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_assign_expr = simple_arg_2(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_108);
}

static void *simple_arg_2(parser_t *p) {
    frame_t f = {109, p->pos, FUNC, 0, 0};
    void *_expr;
    void *res_109;
    res_109 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_expr = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_109);
}

// simple_args:
//     | ','.simple_arg+
static void *simple_args(parser_t *p) {
    frame_t f = {110, p->pos, FUNC, 0, 0};
    ast_list_t *_simple_args;
    void *res_110;
    res_110 = enter_frame(p, &f) && (
        (_simple_args = simple_arg_delimited(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_110);
}

static ast_list_t *simple_arg_delimited(parser_t *p) {
    void *_simple_arg = simple_arg(p);
    if (!_simple_arg) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _simple_arg);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_simple_arg = simple_arg(p)));
    p->pos = pos;
    return list;
}

// builder_hint:
//     | '<' name_list '>'
static void *builder_hint(parser_t *p) {
    frame_t f = {111, p->pos, FUNC, 0, 0};
    void *_name_list;
    void *res_111;
    res_111 = enter_frame(p, &f) && (
        (consume(p, 19, "<")) &&
        (_name_list = name_list(p)) &&
        (consume(p, 20, ">"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_111);
}

// builder_args:
//     | simple_args
//     | '(' [typed_arg_list] ')'
static void *builder_args(parser_t *p) {
    frame_t f = {112, p->pos, FUNC, 0, 0};
    void *_simple_args;
    void *_builder_args_2;
    void *a;
    void *res_112;
    res_112 = enter_frame(p, &f) && (
        (a = simple_args(p)) ||
        (a = builder_args_2(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_112);
}

static void *builder_args_2(parser_t *p) {
    frame_t f = {113, p->pos, FUNC, 0, 0};
    void *_typed_arg_list;
    void *res_113;
    res_113 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_typed_arg_list = typed_arg_list(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_113);
}

// named_expr:
//     | NAME ':=' expr
//     | expr
static void *named_expr(parser_t *p) {
    frame_t f = {114, p->pos, FUNC, 0, 0};
    void *_name_asgn_expr_expr;
    void *_expr;
    void *a;
    void *res_114;
    res_114 = enter_frame(p, &f) && (
        (a = named_expr_1(p)) ||
        (a = expr(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_114);
}

static void *named_expr_1(parser_t *p) {
    frame_t f = {115, p->pos, FUNC, 0, 0};
    token_t *_name;
    void *_expr;
    void *res_115;
    res_115 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (_expr = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_115);
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
static void *conditional(parser_t *p) {
    frame_t f = {116, p->pos, FUNC, 0, 0};
    void *_disjunction;
    void *_disjunction_1;
    void *_expr;
    void *res_116;
    res_116 = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (_disjunction = disjunction(p)) &&
        (consume(p, 10, "?")) &&
        (_disjunction_1 = disjunction(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_116);
}

// expr:
//     | conditional
//     | disjunction
static void *expr(parser_t *p) {
    frame_t f = {117, p->pos, FUNC, 0, 0};
    void *_conditional;
    void *_disjunction;
    void *a;
    void *res_117;
    res_117 = enter_frame(p, &f) && (
        (a = conditional(p)) ||
        (a = disjunction(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_117);
}

// disjunction (left_recursive):
//     | disjunction 'or' conjunction
//     | conjunction
static void *disjunction(parser_t *p) {
    frame_t f = {118, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    void *a = 0;
    void *res_118 = 0;
    void *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = disjunction_1(p)) ||
        (a = conjunction(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_118 = max;
    return exit_frame(p, &f, res_118);
}

static void *disjunction_1(parser_t *p) {
    frame_t f = {119, p->pos, FUNC, 0, 0};
    void *_disjunction;
    void *_conjunction;
    void *res_119;
    res_119 = enter_frame(p, &f) && (
        (_disjunction = disjunction(p)) &&
        (consume(p, 60, "or")) &&
        (_conjunction = conjunction(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_119);
}

// conjunction (left_recursive):
//     | conjunction 'and' inversion
//     | inversion
static void *conjunction(parser_t *p) {
    frame_t f = {120, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    void *a = 0;
    void *res_120 = 0;
    void *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = conjunction_1(p)) ||
        (a = inversion(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_120 = max;
    return exit_frame(p, &f, res_120);
}

static void *conjunction_1(parser_t *p) {
    frame_t f = {121, p->pos, FUNC, 0, 0};
    void *_conjunction;
    void *_inversion;
    void *res_121;
    res_121 = enter_frame(p, &f) && (
        (_conjunction = conjunction(p)) &&
        (consume(p, 59, "and")) &&
        (_inversion = inversion(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_121);
}

// inversion:
//     | 'not' inversion
//     | comparison
static void *inversion(parser_t *p) {
    frame_t f = {122, p->pos, FUNC, 0, 0};
    void *_not_inversion;
    void *_comparison;
    void *a;
    void *res_122;
    res_122 = enter_frame(p, &f) && (
        (a = inversion_1(p)) ||
        (a = comparison(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_122);
}

static void *inversion_1(parser_t *p) {
    frame_t f = {123, p->pos, FUNC, 0, 0};
    void *_inversion;
    void *res_123;
    res_123 = enter_frame(p, &f) && (
        (consume(p, 61, "not")) &&
        (_inversion = inversion(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_123);
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
static void *comparison(parser_t *p) {
    frame_t f = {124, p->pos, FUNC, 0, 0};
    void *_comparison_1;
    void *_bitwise_or;
    void *a;
    void *res_124;
    res_124 = enter_frame(p, &f) && (
        (a = comparison_1(p)) ||
        (a = bitwise_or(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_124);
}

static void *comparison_1(parser_t *p) {
    frame_t f = {125, p->pos, FUNC, 0, 0};
    void *_bitwise_or;
    ast_list_t *_comp_op_bitwise_ors;
    void *res_125;
    res_125 = enter_frame(p, &f) && (
        (_bitwise_or = bitwise_or(p)) &&
        (_comp_op_bitwise_ors = comparison_1_2_loop(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_125);
}

static ast_list_t *comparison_1_2_loop(parser_t *p) {
    void *_comp_op_bitwise_or = comparison_1_2(p);
    if (!_comp_op_bitwise_or) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    do {
        ast_list_append(p, list, _comp_op_bitwise_or);
    } while ((_comp_op_bitwise_or = comparison_1_2(p)));
    return list;
}

static void *comparison_1_2(parser_t *p) {
    frame_t f = {126, p->pos, FUNC, 0, 0};
    void *_comp_op;
    void *_bitwise_or;
    void *res_126;
    res_126 = enter_frame(p, &f) && (
        (_comp_op = comp_op(p)) &&
        (_bitwise_or = bitwise_or(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_126);
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
static void *comp_op(parser_t *p) {
    frame_t f = {127, p->pos, FUNC, 0, 0};
    token_t *_is_less;
    token_t *_is_greater;
    token_t *_is_equal;
    token_t *_is_more_equal;
    token_t *_is_less_equal;
    token_t *_is_nequal;
    token_t *_is_in;
    void *_not_in;
    token_t *_is_is;
    void *_is_not;
    void *a;
    void *res_127;
    res_127 = enter_frame(p, &f) && (
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
    ) ? a : 0;
    return exit_frame(p, &f, res_127);
}

static void *comp_op_8(parser_t *p) {
    frame_t f = {128, p->pos, FUNC, 0, 0};
    void *res_128;
    res_128 = enter_frame(p, &f) && (
        (consume(p, 61, "not")) &&
        (consume(p, 63, "in"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_128);
}

static void *comp_op_10(parser_t *p) {
    frame_t f = {129, p->pos, FUNC, 0, 0};
    void *res_129;
    res_129 = enter_frame(p, &f) && (
        (consume(p, 62, "is")) &&
        (consume(p, 61, "not"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_129);
}

// bitwise_or (left_recursive):
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
static void *bitwise_or(parser_t *p) {
    frame_t f = {130, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    void *a = 0;
    void *res_130 = 0;
    void *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = bitwise_or_1(p)) ||
        (a = bitwise_xor(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_130 = max;
    return exit_frame(p, &f, res_130);
}

static void *bitwise_or_1(parser_t *p) {
    frame_t f = {131, p->pos, FUNC, 0, 0};
    void *_bitwise_or;
    void *_bitwise_xor;
    void *res_131;
    res_131 = enter_frame(p, &f) && (
        (_bitwise_or = bitwise_or(p)) &&
        (consume(p, 27, "|")) &&
        (_bitwise_xor = bitwise_xor(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_131);
}

// bitwise_xor (left_recursive):
//     | bitwise_xor '^' bitwise_and
//     | bitwise_and
static void *bitwise_xor(parser_t *p) {
    frame_t f = {132, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    void *a = 0;
    void *res_132 = 0;
    void *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = bitwise_xor_1(p)) ||
        (a = bitwise_and(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_132 = max;
    return exit_frame(p, &f, res_132);
}

static void *bitwise_xor_1(parser_t *p) {
    frame_t f = {133, p->pos, FUNC, 0, 0};
    void *_bitwise_xor;
    void *_bitwise_and;
    void *res_133;
    res_133 = enter_frame(p, &f) && (
        (_bitwise_xor = bitwise_xor(p)) &&
        (consume(p, 30, "^")) &&
        (_bitwise_and = bitwise_and(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_133);
}

// bitwise_and (left_recursive):
//     | bitwise_and '&' shift_expr
//     | shift_expr
static void *bitwise_and(parser_t *p) {
    frame_t f = {134, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    void *a = 0;
    void *res_134 = 0;
    void *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = bitwise_and_1(p)) ||
        (a = shift_expr(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_134 = max;
    return exit_frame(p, &f, res_134);
}

static void *bitwise_and_1(parser_t *p) {
    frame_t f = {135, p->pos, FUNC, 0, 0};
    void *_bitwise_and;
    void *_shift_expr;
    void *res_135;
    res_135 = enter_frame(p, &f) && (
        (_bitwise_and = bitwise_and(p)) &&
        (consume(p, 28, "&")) &&
        (_shift_expr = shift_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_135);
}

// shift_expr (left_recursive):
//     | shift_expr '<<' sum
//     | shift_expr '>>' sum
//     | sum
static void *shift_expr(parser_t *p) {
    frame_t f = {136, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    void *a = 0;
    void *res_136 = 0;
    void *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = shift_expr_1(p)) ||
        (a = shift_expr_2(p)) ||
        (a = sum(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_136 = max;
    return exit_frame(p, &f, res_136);
}

static void *shift_expr_1(parser_t *p) {
    frame_t f = {137, p->pos, FUNC, 0, 0};
    void *_shift_expr;
    void *_sum;
    void *res_137;
    res_137 = enter_frame(p, &f) && (
        (_shift_expr = shift_expr(p)) &&
        (consume(p, 48, "<<")) &&
        (_sum = sum(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_137);
}

static void *shift_expr_2(parser_t *p) {
    frame_t f = {138, p->pos, FUNC, 0, 0};
    void *_shift_expr;
    void *_sum;
    void *res_138;
    res_138 = enter_frame(p, &f) && (
        (_shift_expr = shift_expr(p)) &&
        (consume(p, 49, ">>")) &&
        (_sum = sum(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_138);
}

// sum (left_recursive):
//     | sum '+' term
//     | sum '-' term
//     | term
static void *sum(parser_t *p) {
    frame_t f = {139, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    void *a = 0;
    void *res_139 = 0;
    void *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = sum_1(p)) ||
        (a = sum_2(p)) ||
        (a = term(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_139 = max;
    return exit_frame(p, &f, res_139);
}

static void *sum_1(parser_t *p) {
    frame_t f = {140, p->pos, FUNC, 0, 0};
    void *_sum;
    void *_term;
    void *res_140;
    res_140 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 21, "+")) &&
        (_term = term(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_140);
}

static void *sum_2(parser_t *p) {
    frame_t f = {141, p->pos, FUNC, 0, 0};
    void *_sum;
    void *_term;
    void *res_141;
    res_141 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 22, "-")) &&
        (_term = term(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_141);
}

// term (left_recursive):
//     | term '*' pipe_expr
//     | term '/' pipe_expr
//     | term '%' pipe_expr
//     | term '//' pipe_expr
//     | term '@' pipe_expr
//     | pipe_expr
static void *term(parser_t *p) {
    frame_t f = {142, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    void *a = 0;
    void *res_142 = 0;
    void *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = term_1(p)) ||
        (a = term_2(p)) ||
        (a = term_3(p)) ||
        (a = term_4(p)) ||
        (a = term_5(p)) ||
        (a = pipe_expr(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_142 = max;
    return exit_frame(p, &f, res_142);
}

static void *term_1(parser_t *p) {
    frame_t f = {143, p->pos, FUNC, 0, 0};
    void *_term;
    void *_pipe_expr;
    void *res_143;
    res_143 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 23, "*")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_143);
}

static void *term_2(parser_t *p) {
    frame_t f = {144, p->pos, FUNC, 0, 0};
    void *_term;
    void *_pipe_expr;
    void *res_144;
    res_144 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 24, "/")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_144);
}

static void *term_3(parser_t *p) {
    frame_t f = {145, p->pos, FUNC, 0, 0};
    void *_term;
    void *_pipe_expr;
    void *res_145;
    res_145 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 25, "%")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_145);
}

static void *term_4(parser_t *p) {
    frame_t f = {146, p->pos, FUNC, 0, 0};
    void *_term;
    void *_pipe_expr;
    void *res_146;
    res_146 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 37, "//")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_146);
}

static void *term_5(parser_t *p) {
    frame_t f = {147, p->pos, FUNC, 0, 0};
    void *_term;
    void *_pipe_expr;
    void *res_147;
    res_147 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 26, "@")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_147);
}

// pipe_expr (left_recursive):
//     | pipe_expr '->' factor
//     | factor
static void *pipe_expr(parser_t *p) {
    frame_t f = {148, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    void *a = 0;
    void *res_148 = 0;
    void *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = pipe_expr_1(p)) ||
        (a = factor(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_148 = max;
    return exit_frame(p, &f, res_148);
}

static void *pipe_expr_1(parser_t *p) {
    frame_t f = {149, p->pos, FUNC, 0, 0};
    void *_pipe_expr;
    void *_factor;
    void *res_149;
    res_149 = enter_frame(p, &f) && (
        (_pipe_expr = pipe_expr(p)) &&
        (consume(p, 35, "->")) &&
        (_factor = factor(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_149);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static void *factor(parser_t *p) {
    frame_t f = {150, p->pos, FUNC, 0, 0};
    void *_plus_factor;
    void *_minus_factor;
    void *_bit_not_factor;
    void *_power;
    void *a;
    void *res_150;
    res_150 = enter_frame(p, &f) && (
        (a = factor_1(p)) ||
        (a = factor_2(p)) ||
        (a = factor_3(p)) ||
        (a = power(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_150);
}

static void *factor_1(parser_t *p) {
    frame_t f = {151, p->pos, FUNC, 0, 0};
    void *_factor;
    void *res_151;
    res_151 = enter_frame(p, &f) && (
        (consume(p, 21, "+")) &&
        (_factor = factor(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_151);
}

static void *factor_2(parser_t *p) {
    frame_t f = {152, p->pos, FUNC, 0, 0};
    void *_factor;
    void *res_152;
    res_152 = enter_frame(p, &f) && (
        (consume(p, 22, "-")) &&
        (_factor = factor(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_152);
}

static void *factor_3(parser_t *p) {
    frame_t f = {153, p->pos, FUNC, 0, 0};
    void *_factor;
    void *res_153;
    res_153 = enter_frame(p, &f) && (
        (consume(p, 29, "~")) &&
        (_factor = factor(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_153);
}

// power:
//     | primary '**' factor
//     | primary
static void *power(parser_t *p) {
    frame_t f = {154, p->pos, FUNC, 0, 0};
    void *_primary_power_factor;
    void *_primary;
    void *a;
    void *res_154;
    res_154 = enter_frame(p, &f) && (
        (a = power_1(p)) ||
        (a = primary(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_154);
}

static void *power_1(parser_t *p) {
    frame_t f = {155, p->pos, FUNC, 0, 0};
    void *_primary;
    void *_factor;
    void *res_155;
    res_155 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (consume(p, 38, "**")) &&
        (_factor = factor(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_155);
}

// primary (left_recursive):
//     | primary '.' NAME
//     | primary invocation
//     | primary subscript
//     | atom
static void *primary(parser_t *p) {
    frame_t f = {156, p->pos, FUNC, 0, 1};
    if (!enter_frame(p, &f)) {
        return exit_frame(p, &f, 0);
    }
    void *a = 0;
    void *res_156 = 0;
    void *max = 0;
    size_t maxpos;
    do {
        maxpos = p->pos;
        max = a;
        memoize(p, &f, max, maxpos);
        p->pos = f.f_pos;
        (a = primary_1(p)) ||
        (a = primary_2(p)) ||
        (a = primary_3(p)) ||
        (a = atom(p));
    } while (p->pos > maxpos);
    p->pos = maxpos;
    res_156 = max;
    return exit_frame(p, &f, res_156);
}

static void *primary_1(parser_t *p) {
    frame_t f = {157, p->pos, FUNC, 0, 0};
    void *_primary;
    token_t *_name;
    void *res_157;
    res_157 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (consume(p, 6, ".")) &&
        (_name = consume(p, 3, "NAME"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_157);
}

static void *primary_2(parser_t *p) {
    frame_t f = {158, p->pos, FUNC, 0, 0};
    void *_primary;
    void *_invocation;
    void *res_158;
    res_158 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (_invocation = invocation(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_158);
}

static void *primary_3(parser_t *p) {
    frame_t f = {159, p->pos, FUNC, 0, 0};
    void *_primary;
    void *_subscript;
    void *res_159;
    res_159 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (_subscript = subscript(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_159);
}

// tuple_atom:
//     | '(' [list_items] ')'
static void *tuple_atom(parser_t *p) {
    frame_t f = {160, p->pos, FUNC, 0, 0};
    void *_list_items;
    void *res_160;
    res_160 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_list_items = list_items(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_160);
}

// list_iterable:
//     | '[' list_iterator ']'
static void *list_iterable(parser_t *p) {
    frame_t f = {161, p->pos, FUNC, 0, 0};
    void *_list_iterator;
    void *res_161;
    res_161 = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (_list_iterator = list_iterator(p)) &&
        (consume(p, 18, "]"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_161);
}

// list_atom:
//     | '[' [list_items] ']'
static void *list_atom(parser_t *p) {
    frame_t f = {162, p->pos, FUNC, 0, 0};
    void *_list_items;
    void *res_162;
    res_162 = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (_list_items = list_items(p), 1) &&
        (consume(p, 18, "]"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_162);
}

// set_atom:
//     | '{' [set_items] '}'
static void *set_atom(parser_t *p) {
    frame_t f = {163, p->pos, FUNC, 0, 0};
    void *_set_items;
    void *res_163;
    res_163 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_set_items = set_items(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_163);
}

// dict_iterable:
//     | '{' dict_iterator '}'
static void *dict_iterable(parser_t *p) {
    frame_t f = {164, p->pos, FUNC, 0, 0};
    void *_dict_iterator;
    void *res_164;
    res_164 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_dict_iterator = dict_iterator(p)) &&
        (consume(p, 16, "}"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_164);
}

// dict_atom:
//     | '{' [dict_items] '}'
static void *dict_atom(parser_t *p) {
    frame_t f = {165, p->pos, FUNC, 0, 0};
    void *_dict_items;
    void *res_165;
    res_165 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_dict_items = dict_items(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_165);
}

// builder:
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
static void *builder(parser_t *p) {
    frame_t f = {166, p->pos, FUNC, 0, 0};
    void *_builder_1;
    void *_builder_2;
    void *a;
    void *res_166;
    res_166 = enter_frame(p, &f) && (
        (a = builder_1(p)) ||
        (a = builder_2(p))
    ) ? a : 0;
    return exit_frame(p, &f, res_166);
}

static void *builder_1(parser_t *p) {
    frame_t f = {167, p->pos, FUNC, 0, 0};
    token_t *_name;
    void *_simple_args;
    void *_expr;
    void *res_167;
    res_167 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_simple_args = simple_args(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_167);
}

static void *builder_2(parser_t *p) {
    frame_t f = {168, p->pos, FUNC, 0, 0};
    token_t *_name;
    void *_builder_hint;
    void *_builder_args;
    void *_block_suite;
    void *res_168;
    res_168 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_builder_hint = builder_hint(p), 1) &&
        (_builder_args = builder_args(p), 1) &&
        (_block_suite = block_suite(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, res_168);
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
static void *atom(parser_t *p) {
    frame_t f = {169, p->pos, FUNC, 0, 0};
    void *_tuple_atom;
    void *_list_iterable;
    void *_list_atom;
    void *_set_atom;
    void *_dict_iterable;
    void *_dict_atom;
    void *_builder;
    token_t *_name;
    token_t *_number;
    token_t *_string;
    token_t *_is_none;
    token_t *_is_true;
    token_t *_is_false;
    void *a;
    void *res_169;
    res_169 = enter_frame(p, &f) && (
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
    ) ? a : 0;
    return exit_frame(p, &f, res_169);
}
