#include "include/ast.h"


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
static void *annassign(parser_t *);
static void *annassign_4(parser_t *);
static void *augassign(parser_t *);
static void *simple_assign(parser_t *);
static ast_list_t *simple_assign_1_loop(parser_t *);
static void *simple_assign_1(parser_t *);
static int *augassign_op(parser_t *);
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
static ast_named_t *named_expr(parser_t *);
static ast_named_t *named_expr_1(parser_t *);
static ast_expr_t *conditional(parser_t *);
static ast_expr_t *expr(parser_t *);
static ast_expr_t *disjunction(parser_t *);
static ast_expr_t *disjunction_1(parser_t *);
static ast_expr_t *conjunction(parser_t *);
static ast_expr_t *conjunction_1(parser_t *);
static ast_expr_t *inversion(parser_t *);
static ast_expr_t *inversion_1(parser_t *);
static ast_expr_t *comparison(parser_t *);
static ast_expr_t *comparison_1(parser_t *);
static ast_list_t *comparison_1_2_loop(parser_t *);
static ast_expr_t *comparison_1_2(parser_t *);
static int *comp_op(parser_t *);
static int *comp_op_8(parser_t *);
static int *comp_op_10(parser_t *);
static ast_expr_t *bitwise_or(parser_t *);
static ast_expr_t *bitwise_or_1(parser_t *);
static ast_expr_t *bitwise_xor(parser_t *);
static ast_expr_t *bitwise_xor_1(parser_t *);
static ast_expr_t *bitwise_and(parser_t *);
static ast_expr_t *bitwise_and_1(parser_t *);
static ast_expr_t *shift_expr(parser_t *);
static ast_expr_t *shift_expr_1(parser_t *);
static ast_expr_t *shift_expr_2(parser_t *);
static ast_expr_t *sum(parser_t *);
static ast_expr_t *sum_1(parser_t *);
static ast_expr_t *sum_2(parser_t *);
static ast_expr_t *term(parser_t *);
static ast_expr_t *term_1(parser_t *);
static ast_expr_t *term_2(parser_t *);
static ast_expr_t *term_3(parser_t *);
static ast_expr_t *term_4(parser_t *);
static ast_expr_t *term_5(parser_t *);
static ast_expr_t *pipe_expr(parser_t *);
static ast_expr_t *pipe_expr_1(parser_t *);
static ast_expr_t *factor(parser_t *);
static ast_expr_t *factor_1(parser_t *);
static ast_expr_t *factor_2(parser_t *);
static ast_expr_t *factor_3(parser_t *);
static ast_expr_t *power(parser_t *);
static ast_expr_t *power_1(parser_t *);
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
    const frame_t f = {1, p->pos, FUNC};
    void *res_1;
    void *alt_1;
    res_1 = enter_frame(p, &f) && (
        (alt_1 = consume(p, 2, "NEWLINE")) ||
        (alt_1 = consume(p, 1, "ENDMARKER")) ||
        (alt_1 = simple_stmt(p)) ||
        (alt_1 = single_input_4(p))
    ) ? alt_1 : 0;
    return exit_frame(p, &f, res_1);
}

static void *single_input_4(parser_t *p) {
    const frame_t f = {2, p->pos, FUNC};
    void *res_2;
    void *_compound_stmt;
    token_t *_newline;
    res_2 = enter_frame(p, &f) && (
        (_compound_stmt = compound_stmt(p)) &&
        (_newline = consume(p, 2, "NEWLINE"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_2);
}

// file_input:
//     | [stmt_list] ENDMARKER
static void *file_input(parser_t *p) {
    const frame_t f = {3, p->pos, FUNC};
    void *res_3;
    void *_stmt_list;
    token_t *_endmarker;
    res_3 = enter_frame(p, &f) && (
        (_stmt_list = stmt_list(p), 1) &&
        (_endmarker = consume(p, 1, "ENDMARKER"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_3);
}

// eval_input:
//     | exprlist NEWLINE* ENDMARKER
static void *eval_input(parser_t *p) {
    const frame_t f = {4, p->pos, FUNC};
    void *res_4;
    void *_exprlist;
    ast_list_t *_newlines;
    token_t *_endmarker;
    res_4 = enter_frame(p, &f) && (
        (_exprlist = exprlist(p)) &&
        (_newlines = eval_input_loop(p)) &&
        (_endmarker = consume(p, 1, "ENDMARKER"))
    ) ? node(p) : 0;
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
    const frame_t f = {5, p->pos, FUNC};
    void *res_5;
    ast_list_t *_stmts;
    res_5 = enter_frame(p, &f) && (
        (_stmts = stmt_loop(p))
    ) ? node(p) : 0;
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
    const frame_t f = {6, p->pos, FUNC};
    void *res_6;
    void *_simple_stmt_or_compound_stmt;
    token_t *_newline;
    res_6 = enter_frame(p, &f) && (
        (_simple_stmt_or_compound_stmt = stmt_1(p)) &&
        (_newline = consume(p, 2, "NEWLINE"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_6);
}

static void *stmt_1(parser_t *p) {
    const frame_t f = {7, p->pos, FUNC};
    void *res_7;
    void *alt_7;
    res_7 = enter_frame(p, &f) && (
        (alt_7 = simple_stmt(p)) ||
        (alt_7 = compound_stmt(p))
    ) ? alt_7 : 0;
    return exit_frame(p, &f, res_7);
}

// simple_stmt:
//     | ';'.small_stmt+ [';']
static void *simple_stmt(parser_t *p) {
    const frame_t f = {8, p->pos, FUNC};
    void *res_8;
    ast_list_t *_small_stmts;
    token_t *_is_semicolon;
    res_8 = enter_frame(p, &f) && (
        (_small_stmts = small_stmt_delimited(p)) &&
        (_is_semicolon = consume(p, 12, ";"), 1)
    ) ? node(p) : 0;
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
    const frame_t f = {9, p->pos, FUNC};
    void *res_9;
    void *alt_9;
    res_9 = enter_frame(p, &f) && (
        (alt_9 = consume(p, 64, "pass")) ||
        (alt_9 = consume(p, 74, "break")) ||
        (alt_9 = consume(p, 73, "continue")) ||
        (alt_9 = return_stmt(p)) ||
        (alt_9 = raise_stmt(p)) ||
        (alt_9 = del_stmt(p)) ||
        (alt_9 = nonlocal_stmt(p)) ||
        (alt_9 = assert_stmt(p)) ||
        (alt_9 = import_name(p)) ||
        (alt_9 = import_from(p)) ||
        (alt_9 = assignment(p))
    ) ? alt_9 : 0;
    return exit_frame(p, &f, res_9);
}

// del_stmt:
//     | 'del' targetlist
static void *del_stmt(parser_t *p) {
    const frame_t f = {10, p->pos, FUNC};
    void *res_10;
    void *_targetlist;
    res_10 = enter_frame(p, &f) && (
        (consume(p, 79, "del")) &&
        (_targetlist = targetlist(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_10);
}

// return_stmt:
//     | 'return' [exprlist_star]
static void *return_stmt(parser_t *p) {
    const frame_t f = {11, p->pos, FUNC};
    void *res_11;
    void *_exprlist_star;
    res_11 = enter_frame(p, &f) && (
        (consume(p, 54, "return")) &&
        (_exprlist_star = exprlist_star(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_11);
}

// raise_stmt:
//     | 'raise' expr ['from' expr]
static void *raise_stmt(parser_t *p) {
    const frame_t f = {12, p->pos, FUNC};
    void *res_12;
    ast_expr_t *_expr;
    void *_from_expr;
    res_12 = enter_frame(p, &f) && (
        (consume(p, 78, "raise")) &&
        (_expr = expr(p)) &&
        (_from_expr = raise_stmt_3(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_12);
}

static void *raise_stmt_3(parser_t *p) {
    const frame_t f = {13, p->pos, FUNC};
    void *res_13;
    ast_expr_t *_expr;
    res_13 = enter_frame(p, &f) && (
        (consume(p, 66, "from")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_13);
}

// nonlocal_stmt:
//     | 'nonlocal' name_list
static void *nonlocal_stmt(parser_t *p) {
    const frame_t f = {14, p->pos, FUNC};
    void *res_14;
    void *_name_list;
    res_14 = enter_frame(p, &f) && (
        (consume(p, 55, "nonlocal")) &&
        (_name_list = name_list(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_14);
}

// assert_stmt:
//     | 'assert' expr [',' expr]
static void *assert_stmt(parser_t *p) {
    const frame_t f = {15, p->pos, FUNC};
    void *res_15;
    ast_expr_t *_expr;
    void *_comma_expr;
    res_15 = enter_frame(p, &f) && (
        (consume(p, 80, "assert")) &&
        (_expr = expr(p)) &&
        (_comma_expr = assert_stmt_3(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_15);
}

static void *assert_stmt_3(parser_t *p) {
    const frame_t f = {16, p->pos, FUNC};
    void *res_16;
    ast_expr_t *_expr;
    res_16 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_16);
}

// name_list:
//     | ','.NAME+
static void *name_list(parser_t *p) {
    const frame_t f = {17, p->pos, FUNC};
    void *res_17;
    ast_list_t *_names;
    res_17 = enter_frame(p, &f) && (
        (_names = name_list_delimited(p))
    ) ? node(p) : 0;
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
    const frame_t f = {18, p->pos, FUNC};
    void *res_18;
    ast_expr_t *_bitwise_or;
    res_18 = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (_bitwise_or = bitwise_or(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_18);
}

// exprlist:
//     | ','.expr+ [',']
static void *exprlist(parser_t *p) {
    const frame_t f = {19, p->pos, FUNC};
    void *res_19;
    ast_list_t *_exprs;
    token_t *_is_comma;
    res_19 = enter_frame(p, &f) && (
        (_exprs = expr_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_19);
}

static ast_list_t *expr_delimited(parser_t *p) {
    ast_expr_t *_expr = expr(p);
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
//     | '(' targetlist ')'
static void *target(parser_t *p) {
    const frame_t f = {20, p->pos, FUNC};
    void *res_20;
    void *alt_20;
    res_20 = enter_frame(p, &f) && (
        (alt_20 = target_1(p)) ||
        (alt_20 = target_2(p)) ||
        (alt_20 = consume(p, 3, "NAME")) ||
        (alt_20 = target_4(p))
    ) ? alt_20 : 0;
    return exit_frame(p, &f, res_20);
}

static void *target_1(parser_t *p) {
    const frame_t f = {21, p->pos, FUNC};
    void *res_21;
    void *_t_primary;
    token_t *_name;
    res_21 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (consume(p, 6, ".")) &&
        (_name = consume(p, 3, "NAME")) &&
        (!test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_21);
}

static void *target_2(parser_t *p) {
    const frame_t f = {22, p->pos, FUNC};
    void *res_22;
    void *_t_primary;
    void *_subscript;
    res_22 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (_subscript = subscript(p)) &&
        (!test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_22);
}

static void *target_4(parser_t *p) {
    const frame_t f = {23, p->pos, FUNC};
    void *res_23;
    void *_targetlist;
    res_23 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_targetlist = targetlist(p)) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_23);
}

// t_primary (left_recursive):
//     | t_primary '.' NAME &t_lookahead
//     | t_primary invocation &t_lookahead
//     | t_primary subscript &t_lookahead
//     | atom &t_lookahead
static void *t_primary(parser_t *p) {
    const frame_t f = {24, p->pos, FUNC};
    void *res_24 = 0;
    if (is_memoized(p, &f, (void **) &res_24)) {
        return res_24;
    }
    void *alt_24;
    size_t maxpos;
    void *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_24;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_24 = (
                (alt_24 = t_primary_1(p)) ||
                (alt_24 = t_primary_2(p)) ||
                (alt_24 = t_primary_3(p)) ||
                (alt_24 = t_primary_4(p))
            ) ? alt_24 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_24 = max;
    }
    insert_memo(p, &f, res_24);
    return exit_frame(p, &f, res_24);
}

static void *t_primary_1(parser_t *p) {
    const frame_t f = {25, p->pos, FUNC};
    void *res_25;
    void *_t_primary;
    token_t *_name;
    res_25 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (consume(p, 6, ".")) &&
        (_name = consume(p, 3, "NAME")) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_25);
}

static void *t_primary_2(parser_t *p) {
    const frame_t f = {26, p->pos, FUNC};
    void *res_26;
    void *_t_primary;
    void *_invocation;
    res_26 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (_invocation = invocation(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_26);
}

static void *t_primary_3(parser_t *p) {
    const frame_t f = {27, p->pos, FUNC};
    void *res_27;
    void *_t_primary;
    void *_subscript;
    res_27 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (_subscript = subscript(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_27);
}

static void *t_primary_4(parser_t *p) {
    const frame_t f = {28, p->pos, FUNC};
    void *res_28;
    void *_atom;
    res_28 = enter_frame(p, &f) && (
        (_atom = atom(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_28);
}

// t_lookahead:
//     | '.'
//     | '('
//     | '['
static void *t_lookahead(parser_t *p) {
    const frame_t f = {29, p->pos, FUNC};
    void *res_29;
    void *alt_29;
    res_29 = enter_frame(p, &f) && (
        (alt_29 = consume(p, 6, ".")) ||
        (alt_29 = consume(p, 13, "(")) ||
        (alt_29 = consume(p, 17, "["))
    ) ? alt_29 : 0;
    return exit_frame(p, &f, res_29);
}

// targetlist:
//     | ','.target+ [',']
static void *targetlist(parser_t *p) {
    const frame_t f = {30, p->pos, FUNC};
    void *res_30;
    ast_list_t *_targets;
    token_t *_is_comma;
    res_30 = enter_frame(p, &f) && (
        (_targets = target_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_30);
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
    const frame_t f = {31, p->pos, FUNC};
    void *res_31;
    void *alt_31;
    res_31 = enter_frame(p, &f) && (
        (alt_31 = star_expr(p)) ||
        (alt_31 = expr(p))
    ) ? alt_31 : 0;
    return exit_frame(p, &f, res_31);
}

// exprlist_star:
//     | ','.expr_or_star+ [',']
static void *exprlist_star(parser_t *p) {
    const frame_t f = {32, p->pos, FUNC};
    void *res_32;
    ast_list_t *_expr_or_stars;
    token_t *_is_comma;
    res_32 = enter_frame(p, &f) && (
        (_expr_or_stars = expr_or_star_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_32);
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
    const frame_t f = {33, p->pos, FUNC};
    void *res_33;
    void *_slicelist;
    res_33 = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (_slicelist = slicelist(p)) &&
        (consume(p, 18, "]"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_33);
}

// slicelist:
//     | ','.slice+ [',']
static void *slicelist(parser_t *p) {
    const frame_t f = {34, p->pos, FUNC};
    void *res_34;
    ast_list_t *_slices;
    token_t *_is_comma;
    res_34 = enter_frame(p, &f) && (
        (_slices = slice_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_34);
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
    const frame_t f = {35, p->pos, FUNC};
    void *res_35;
    void *alt_35;
    res_35 = enter_frame(p, &f) && (
        (alt_35 = slice_1(p)) ||
        (alt_35 = expr(p))
    ) ? alt_35 : 0;
    return exit_frame(p, &f, res_35);
}

static void *slice_1(parser_t *p) {
    const frame_t f = {36, p->pos, FUNC};
    void *res_36;
    ast_expr_t *_expr;
    void *_slice_expr;
    void *_slice_expr_1;
    res_36 = enter_frame(p, &f) && (
        (_expr = expr(p), 1) &&
        (_slice_expr = slice_expr(p)) &&
        (_slice_expr_1 = slice_expr(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_36);
}

// slice_expr:
//     | ':' [expr]
static void *slice_expr(parser_t *p) {
    const frame_t f = {37, p->pos, FUNC};
    void *res_37;
    ast_expr_t *_expr;
    res_37 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_expr = expr(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_37);
}

// dict_item:
//     | expr ':' expr
//     | '**' bitwise_or
static void *dict_item(parser_t *p) {
    const frame_t f = {38, p->pos, FUNC};
    void *res_38;
    void *alt_38;
    res_38 = enter_frame(p, &f) && (
        (alt_38 = dict_item_1(p)) ||
        (alt_38 = dict_item_2(p))
    ) ? alt_38 : 0;
    return exit_frame(p, &f, res_38);
}

static void *dict_item_1(parser_t *p) {
    const frame_t f = {39, p->pos, FUNC};
    void *res_39;
    ast_expr_t *_expr;
    ast_expr_t *_expr_1;
    res_39 = enter_frame(p, &f) && (
        (_expr = expr(p)) &&
        (consume(p, 9, ":")) &&
        (_expr_1 = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_39);
}

static void *dict_item_2(parser_t *p) {
    const frame_t f = {40, p->pos, FUNC};
    void *res_40;
    ast_expr_t *_bitwise_or;
    res_40 = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (_bitwise_or = bitwise_or(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_40);
}

// dict_items:
//     | ','.dict_item+ [',']
static void *dict_items(parser_t *p) {
    const frame_t f = {41, p->pos, FUNC};
    void *res_41;
    ast_list_t *_dict_items;
    token_t *_is_comma;
    res_41 = enter_frame(p, &f) && (
        (_dict_items = dict_item_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_41);
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
    const frame_t f = {42, p->pos, FUNC};
    void *res_42;
    void *alt_42;
    res_42 = enter_frame(p, &f) && (
        (alt_42 = star_expr(p)) ||
        (alt_42 = named_expr(p))
    ) ? alt_42 : 0;
    return exit_frame(p, &f, res_42);
}

// list_items:
//     | ','.list_item+ [',']
static void *list_items(parser_t *p) {
    const frame_t f = {43, p->pos, FUNC};
    void *res_43;
    ast_list_t *_list_items;
    token_t *_is_comma;
    res_43 = enter_frame(p, &f) && (
        (_list_items = list_item_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_43);
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

// set_items:
//     | exprlist_star
static void *set_items(parser_t *p) {
    const frame_t f = {44, p->pos, FUNC};
    void *res_44;
    void *_exprlist_star;
    res_44 = enter_frame(p, &f) && (
        (_exprlist_star = exprlist_star(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_44);
}

// as_name:
//     | 'as' NAME
static void *as_name(parser_t *p) {
    const frame_t f = {45, p->pos, FUNC};
    void *res_45;
    token_t *_name;
    res_45 = enter_frame(p, &f) && (
        (consume(p, 65, "as")) &&
        (_name = consume(p, 3, "NAME"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_45);
}

// iter_for:
//     | 'for' targetlist 'in' disjunction [iter_if]
static void *iter_for(parser_t *p) {
    const frame_t f = {46, p->pos, FUNC};
    void *res_46;
    void *_targetlist;
    ast_expr_t *_disjunction;
    void *_iter_if;
    res_46 = enter_frame(p, &f) && (
        (consume(p, 72, "for")) &&
        (_targetlist = targetlist(p)) &&
        (consume(p, 63, "in")) &&
        (_disjunction = disjunction(p)) &&
        (_iter_if = iter_if(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_46);
}

// iter_if:
//     | 'if' named_expr
static void *iter_if(parser_t *p) {
    const frame_t f = {47, p->pos, FUNC};
    void *res_47;
    ast_named_t *_named_expr;
    res_47 = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (_named_expr = named_expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_47);
}

// iterator:
//     | iter_for* 'for' targetlist [iter_if]
static void *iterator(parser_t *p) {
    const frame_t f = {48, p->pos, FUNC};
    void *res_48;
    ast_list_t *_iter_fors;
    void *_targetlist;
    void *_iter_if;
    res_48 = enter_frame(p, &f) && (
        (_iter_fors = iter_for_loop(p)) &&
        (consume(p, 72, "for")) &&
        (_targetlist = targetlist(p)) &&
        (_iter_if = iter_if(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_48);
}

static ast_list_t *iter_for_loop(parser_t *p) {
    ast_list_t *list = ast_list_new(p);
    void *_iter_for;
    while ((_iter_for = iter_for(p))) {
        ast_list_append(p, list, _iter_for);
    }
    return list;
}

// list_iterator:
//     | expr_or_star iterator
static void *list_iterator(parser_t *p) {
    const frame_t f = {49, p->pos, FUNC};
    void *res_49;
    void *_expr_or_star;
    void *_iterator;
    res_49 = enter_frame(p, &f) && (
        (_expr_or_star = expr_or_star(p)) &&
        (_iterator = iterator(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_49);
}

// dict_iterator:
//     | dict_item iterator
static void *dict_iterator(parser_t *p) {
    const frame_t f = {50, p->pos, FUNC};
    void *res_50;
    void *_dict_item;
    void *_iterator;
    res_50 = enter_frame(p, &f) && (
        (_dict_item = dict_item(p)) &&
        (_iterator = iterator(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_50);
}

// assignment:
//     | annassign
//     | augassign
//     | simple_assign
static void *assignment(parser_t *p) {
    const frame_t f = {51, p->pos, FUNC};
    void *res_51;
    void *alt_51;
    res_51 = enter_frame(p, &f) && (
        (alt_51 = annassign(p)) ||
        (alt_51 = augassign(p)) ||
        (alt_51 = simple_assign(p))
    ) ? alt_51 : 0;
    return exit_frame(p, &f, res_51);
}

// annassign:
//     | target ':' expr ['=' exprlist]
static void *annassign(parser_t *p) {
    const frame_t f = {52, p->pos, FUNC};
    void *res_52;
    void *_target;
    ast_expr_t *_expr;
    void *_assign_exprlist;
    res_52 = enter_frame(p, &f) && (
        (_target = target(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p)) &&
        (_assign_exprlist = annassign_4(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_52);
}

static void *annassign_4(parser_t *p) {
    const frame_t f = {53, p->pos, FUNC};
    void *res_53;
    void *_exprlist;
    res_53 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_exprlist = exprlist(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_53);
}

// augassign:
//     | target augassign_op exprlist
static void *augassign(parser_t *p) {
    const frame_t f = {54, p->pos, FUNC};
    void *res_54;
    void *_target;
    int *_augassign_op;
    void *_exprlist;
    res_54 = enter_frame(p, &f) && (
        (_target = target(p)) &&
        (_augassign_op = augassign_op(p)) &&
        (_exprlist = exprlist(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_54);
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
static void *simple_assign(parser_t *p) {
    const frame_t f = {55, p->pos, FUNC};
    void *res_55;
    ast_list_t *_targetlist_assigns;
    void *_exprlist_star;
    res_55 = enter_frame(p, &f) && (
        (_targetlist_assigns = simple_assign_1_loop(p)) &&
        (_exprlist_star = exprlist_star(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_55);
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
    const frame_t f = {56, p->pos, FUNC};
    void *res_56;
    void *_targetlist;
    res_56 = enter_frame(p, &f) && (
        (_targetlist = targetlist(p)) &&
        (consume(p, 8, "="))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_56);
}

// augassign_op:
//     | '+='
//     | '-='
//     | '*='
//     | '/='
//     | '%='
//     | '@='
//     | '|='
//     | '&='
//     | '^='
//     | '//='
//     | '**='
//     | '<<='
//     | '>>='
static int *augassign_op(parser_t *p) {
    const frame_t f = {57, p->pos, FUNC};
    int *res_57;
    int *alt_57;
    res_57 = enter_frame(p, &f) && ((
            (consume(p, 39, "+=")) &&
            (alt_57 = ast_integer(p, BINOP_PLS))
        ) || (
            (consume(p, 40, "-=")) &&
            (alt_57 = ast_integer(p, BINOP_MIN))
        ) || (
            (consume(p, 41, "*=")) &&
            (alt_57 = ast_integer(p, BINOP_MUL))
        ) || (
            (consume(p, 42, "/=")) &&
            (alt_57 = ast_integer(p, BINOP_DIV))
        ) || (
            (consume(p, 43, "%=")) &&
            (alt_57 = ast_integer(p, BINOP_MOD))
        ) || (
            (consume(p, 44, "@=")) &&
            (alt_57 = ast_integer(p, BINOP_MML))
        ) || (
            (consume(p, 45, "|=")) &&
            (alt_57 = ast_integer(p, BINOP_IOR))
        ) || (
            (consume(p, 46, "&=")) &&
            (alt_57 = ast_integer(p, BINOP_AND))
        ) || (
            (consume(p, 47, "^=")) &&
            (alt_57 = ast_integer(p, BINOP_XOR))
        ) || (
            (consume(p, 50, "//=")) &&
            (alt_57 = ast_integer(p, BINOP_FDV))
        ) || (
            (consume(p, 51, "**=")) &&
            (alt_57 = ast_integer(p, BINOP_POW))
        ) || (
            (consume(p, 52, "<<=")) &&
            (alt_57 = ast_integer(p, BINOP_SHL))
        ) || (
            (consume(p, 53, ">>=")) &&
            (alt_57 = ast_integer(p, BINOP_SHR)))
    ) ? alt_57 : 0;
    return exit_frame(p, &f, res_57);
}

// import_name:
//     | 'import' dotted_as_names
static void *import_name(parser_t *p) {
    const frame_t f = {58, p->pos, FUNC};
    void *res_58;
    void *_dotted_as_names;
    res_58 = enter_frame(p, &f) && (
        (consume(p, 67, "import")) &&
        (_dotted_as_names = dotted_as_names(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_58);
}

// import_from:
//     | 'from' import_from_names 'import' import_from_items
static void *import_from(parser_t *p) {
    const frame_t f = {59, p->pos, FUNC};
    void *res_59;
    void *_import_from_names;
    void *_import_from_items;
    res_59 = enter_frame(p, &f) && (
        (consume(p, 66, "from")) &&
        (_import_from_names = import_from_names(p)) &&
        (consume(p, 67, "import")) &&
        (_import_from_items = import_from_items(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_59);
}

// import_from_names:
//     | dotted_name
//     | '.'+ [dotted_name]
static void *import_from_names(parser_t *p) {
    const frame_t f = {60, p->pos, FUNC};
    void *res_60;
    void *alt_60;
    res_60 = enter_frame(p, &f) && (
        (alt_60 = dotted_name(p)) ||
        (alt_60 = import_from_names_2(p))
    ) ? alt_60 : 0;
    return exit_frame(p, &f, res_60);
}

static void *import_from_names_2(parser_t *p) {
    const frame_t f = {61, p->pos, FUNC};
    void *res_61;
    void *_dotted_name;
    res_61 = enter_frame(p, &f) && (
        (import_from_names_2_loop(p)) &&
        (_dotted_name = dotted_name(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_61);
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
    const frame_t f = {62, p->pos, FUNC};
    void *res_62;
    void *alt_62;
    res_62 = enter_frame(p, &f) && (
        (alt_62 = consume(p, 23, "*")) ||
        (alt_62 = import_as_names_sp(p)) ||
        (alt_62 = import_as_names(p))
    ) ? alt_62 : 0;
    return exit_frame(p, &f, res_62);
}

// import_as_names_sp:
//     | '(' import_as_names [','] ')'
static void *import_as_names_sp(parser_t *p) {
    const frame_t f = {63, p->pos, FUNC};
    void *res_63;
    void *_import_as_names;
    token_t *_is_comma;
    res_63 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_import_as_names = import_as_names(p)) &&
        (_is_comma = consume(p, 7, ","), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_63);
}

// import_as_name:
//     | NAME [as_name]
static void *import_as_name(parser_t *p) {
    const frame_t f = {64, p->pos, FUNC};
    void *res_64;
    token_t *_name;
    void *_as_name;
    res_64 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_as_name = as_name(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_64);
}

// dotted_as_name:
//     | dotted_name [as_name]
static void *dotted_as_name(parser_t *p) {
    const frame_t f = {65, p->pos, FUNC};
    void *res_65;
    void *_dotted_name;
    void *_as_name;
    res_65 = enter_frame(p, &f) && (
        (_dotted_name = dotted_name(p)) &&
        (_as_name = as_name(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_65);
}

// import_as_names:
//     | ','.import_as_name+
static void *import_as_names(parser_t *p) {
    const frame_t f = {66, p->pos, FUNC};
    void *res_66;
    ast_list_t *_import_as_names;
    res_66 = enter_frame(p, &f) && (
        (_import_as_names = import_as_name_delimited(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_66);
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
    const frame_t f = {67, p->pos, FUNC};
    void *res_67;
    ast_list_t *_dotted_as_names;
    res_67 = enter_frame(p, &f) && (
        (_dotted_as_names = dotted_as_name_delimited(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_67);
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
    const frame_t f = {68, p->pos, FUNC};
    void *res_68;
    ast_list_t *_names;
    res_68 = enter_frame(p, &f) && (
        (_names = dotted_name_delimited(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_68);
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
    const frame_t f = {69, p->pos, FUNC};
    void *res_69;
    void *alt_69;
    res_69 = enter_frame(p, &f) && (
        (alt_69 = if_stmt(p)) ||
        (alt_69 = while_stmt(p)) ||
        (alt_69 = for_stmt(p)) ||
        (alt_69 = try_stmt(p)) ||
        (alt_69 = with_stmt(p))
    ) ? alt_69 : 0;
    return exit_frame(p, &f, res_69);
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
static void *if_stmt(parser_t *p) {
    const frame_t f = {70, p->pos, FUNC};
    void *res_70;
    ast_named_t *_named_expr;
    void *_suite;
    ast_list_t *_elif_stmts;
    void *_else_suite;
    res_70 = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (_named_expr = named_expr(p)) &&
        (_suite = suite(p)) &&
        (_elif_stmts = elif_stmt_loop(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_70);
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
    const frame_t f = {71, p->pos, FUNC};
    void *res_71;
    ast_named_t *_named_expr;
    void *_suite;
    res_71 = enter_frame(p, &f) && (
        (consume(p, 57, "elif")) &&
        (_named_expr = named_expr(p)) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_71);
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
static void *while_stmt(parser_t *p) {
    const frame_t f = {72, p->pos, FUNC};
    void *res_72;
    ast_named_t *_named_expr;
    void *_suite;
    void *_else_suite;
    res_72 = enter_frame(p, &f) && (
        (consume(p, 71, "while")) &&
        (_named_expr = named_expr(p)) &&
        (_suite = suite(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_72);
}

// for_stmt:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
static void *for_stmt(parser_t *p) {
    const frame_t f = {73, p->pos, FUNC};
    void *res_73;
    void *_targetlist;
    void *_exprlist;
    void *_suite;
    void *_else_suite;
    res_73 = enter_frame(p, &f) && (
        (consume(p, 72, "for")) &&
        (_targetlist = targetlist(p)) &&
        (consume(p, 63, "in")) &&
        (_exprlist = exprlist(p)) &&
        (_suite = suite(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_73);
}

// try_stmt:
//     | 'try' suite (except_suite | finally_suite)
static void *try_stmt(parser_t *p) {
    const frame_t f = {74, p->pos, FUNC};
    void *res_74;
    void *_suite;
    void *_except_suite_or_finally_suite;
    res_74 = enter_frame(p, &f) && (
        (consume(p, 75, "try")) &&
        (_suite = suite(p)) &&
        (_except_suite_or_finally_suite = try_stmt_3(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_74);
}

static void *try_stmt_3(parser_t *p) {
    const frame_t f = {75, p->pos, FUNC};
    void *res_75;
    void *alt_75;
    res_75 = enter_frame(p, &f) && (
        (alt_75 = except_suite(p)) ||
        (alt_75 = finally_suite(p))
    ) ? alt_75 : 0;
    return exit_frame(p, &f, res_75);
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
static void *with_stmt(parser_t *p) {
    const frame_t f = {76, p->pos, FUNC};
    void *res_76;
    ast_list_t *_expr_as_names;
    void *_suite;
    res_76 = enter_frame(p, &f) && (
        (consume(p, 68, "with")) &&
        (_expr_as_names = expr_as_name_delimited(p)) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_76);
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
    const frame_t f = {77, p->pos, FUNC};
    void *res_77;
    ast_expr_t *_expr;
    void *_as_name;
    res_77 = enter_frame(p, &f) && (
        (_expr = expr(p)) &&
        (_as_name = as_name(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_77);
}

// block_suite:
//     | '{' NEWLINE stmt_list '}'
//     | '{' [simple_stmt] '}'
static void *block_suite(parser_t *p) {
    const frame_t f = {78, p->pos, FUNC};
    void *res_78;
    void *alt_78;
    res_78 = enter_frame(p, &f) && (
        (alt_78 = block_suite_1(p)) ||
        (alt_78 = block_suite_2(p))
    ) ? alt_78 : 0;
    return exit_frame(p, &f, res_78);
}

static void *block_suite_1(parser_t *p) {
    const frame_t f = {79, p->pos, FUNC};
    void *res_79;
    token_t *_newline;
    void *_stmt_list;
    res_79 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_newline = consume(p, 2, "NEWLINE")) &&
        (_stmt_list = stmt_list(p)) &&
        (consume(p, 16, "}"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_79);
}

static void *block_suite_2(parser_t *p) {
    const frame_t f = {80, p->pos, FUNC};
    void *res_80;
    void *_simple_stmt;
    res_80 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_simple_stmt = simple_stmt(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_80);
}

// suite:
//     | ':' simple_stmt
//     | block_suite
static void *suite(parser_t *p) {
    const frame_t f = {81, p->pos, FUNC};
    void *res_81;
    void *alt_81;
    res_81 = enter_frame(p, &f) && (
        (alt_81 = suite_1(p)) ||
        (alt_81 = block_suite(p))
    ) ? alt_81 : 0;
    return exit_frame(p, &f, res_81);
}

static void *suite_1(parser_t *p) {
    const frame_t f = {82, p->pos, FUNC};
    void *res_82;
    void *_simple_stmt;
    res_82 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_simple_stmt = simple_stmt(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_82);
}

// else_suite:
//     | 'else' suite
static void *else_suite(parser_t *p) {
    const frame_t f = {83, p->pos, FUNC};
    void *res_83;
    void *_suite;
    res_83 = enter_frame(p, &f) && (
        (consume(p, 58, "else")) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_83);
}

// finally_suite:
//     | 'finally' suite
static void *finally_suite(parser_t *p) {
    const frame_t f = {84, p->pos, FUNC};
    void *res_84;
    void *_suite;
    res_84 = enter_frame(p, &f) && (
        (consume(p, 77, "finally")) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_84);
}

// except_clause:
//     | 'except' [expr_as_name] suite
static void *except_clause(parser_t *p) {
    const frame_t f = {85, p->pos, FUNC};
    void *res_85;
    void *_expr_as_name;
    void *_suite;
    res_85 = enter_frame(p, &f) && (
        (consume(p, 76, "except")) &&
        (_expr_as_name = expr_as_name(p), 1) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_85);
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
static void *except_suite(parser_t *p) {
    const frame_t f = {86, p->pos, FUNC};
    void *res_86;
    ast_list_t *_except_clauses;
    void *_else_suite;
    void *_finally_suite;
    res_86 = enter_frame(p, &f) && (
        (_except_clauses = except_clause_loop(p)) &&
        (_else_suite = else_suite(p), 1) &&
        (_finally_suite = finally_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_86);
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
    const frame_t f = {87, p->pos, FUNC};
    void *res_87;
    void *_call_arg_list;
    res_87 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_call_arg_list = call_arg_list(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_87);
}

// call_arg_list:
//     | ','.call_arg+ [',']
static void *call_arg_list(parser_t *p) {
    const frame_t f = {88, p->pos, FUNC};
    void *res_88;
    ast_list_t *_call_args;
    token_t *_is_comma;
    res_88 = enter_frame(p, &f) && (
        (_call_args = call_arg_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_88);
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
    const frame_t f = {89, p->pos, FUNC};
    void *res_89;
    void *alt_89;
    res_89 = enter_frame(p, &f) && (
        (alt_89 = call_arg_1(p)) ||
        (alt_89 = call_arg_2(p)) ||
        (alt_89 = call_arg_3(p)) ||
        (alt_89 = call_arg_4(p)) ||
        (alt_89 = expr(p))
    ) ? alt_89 : 0;
    return exit_frame(p, &f, res_89);
}

static void *call_arg_1(parser_t *p) {
    const frame_t f = {90, p->pos, FUNC};
    void *res_90;
    token_t *_name;
    ast_expr_t *_expr;
    res_90 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_90);
}

static void *call_arg_2(parser_t *p) {
    const frame_t f = {91, p->pos, FUNC};
    void *res_91;
    token_t *_name;
    ast_expr_t *_expr;
    res_91 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 8, "=")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_91);
}

static void *call_arg_3(parser_t *p) {
    const frame_t f = {92, p->pos, FUNC};
    void *res_92;
    ast_expr_t *_expr;
    res_92 = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_92);
}

static void *call_arg_4(parser_t *p) {
    const frame_t f = {93, p->pos, FUNC};
    void *res_93;
    ast_expr_t *_expr;
    res_93 = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_93);
}

// typed_arg_list:
//     | kwargs
//     | args_kwargs
//     | full_arg_list
static void *typed_arg_list(parser_t *p) {
    const frame_t f = {94, p->pos, FUNC};
    void *res_94;
    void *alt_94;
    res_94 = enter_frame(p, &f) && (
        (alt_94 = kwargs(p)) ||
        (alt_94 = args_kwargs(p)) ||
        (alt_94 = full_arg_list(p))
    ) ? alt_94 : 0;
    return exit_frame(p, &f, res_94);
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
static void *full_arg_list(parser_t *p) {
    const frame_t f = {95, p->pos, FUNC};
    void *res_95;
    ast_list_t *_default_args;
    void *_full_arg_list_2;
    res_95 = enter_frame(p, &f) && (
        (_default_args = default_arg_delimited(p)) &&
        (_full_arg_list_2 = full_arg_list_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_95);
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
    const frame_t f = {96, p->pos, FUNC};
    void *res_96;
    void *_kwargs_or_args_kwargs;
    res_96 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_kwargs_or_args_kwargs = full_arg_list_2_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_96);
}

static void *full_arg_list_2_2(parser_t *p) {
    const frame_t f = {97, p->pos, FUNC};
    void *res_97;
    void *alt_97;
    res_97 = enter_frame(p, &f) && (
        (alt_97 = kwargs(p)) ||
        (alt_97 = args_kwargs(p))
    ) ? alt_97 : 0;
    return exit_frame(p, &f, res_97);
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
static void *args_kwargs(parser_t *p) {
    const frame_t f = {98, p->pos, FUNC};
    void *res_98;
    void *_typed_arg;
    ast_list_t *_comma_default_args;
    void *_args_kwargs_4;
    res_98 = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (_typed_arg = typed_arg(p), 1) &&
        (_comma_default_args = args_kwargs_3_loop(p)) &&
        (_args_kwargs_4 = args_kwargs_4(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_98);
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
    const frame_t f = {99, p->pos, FUNC};
    void *res_99;
    void *_default_arg;
    res_99 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_default_arg = default_arg(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_99);
}

static void *args_kwargs_4(parser_t *p) {
    const frame_t f = {100, p->pos, FUNC};
    void *res_100;
    void *_kwargs;
    res_100 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_kwargs = kwargs(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_100);
}

// kwargs:
//     | '**' typed_arg [',']
static void *kwargs(parser_t *p) {
    const frame_t f = {101, p->pos, FUNC};
    void *res_101;
    void *_typed_arg;
    token_t *_is_comma;
    res_101 = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (_typed_arg = typed_arg(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_101);
}

// default_arg:
//     | typed_arg ['=' expr]
static void *default_arg(parser_t *p) {
    const frame_t f = {102, p->pos, FUNC};
    void *res_102;
    void *_typed_arg;
    void *_assign_expr;
    res_102 = enter_frame(p, &f) && (
        (_typed_arg = typed_arg(p)) &&
        (_assign_expr = default_arg_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_102);
}

static void *default_arg_2(parser_t *p) {
    const frame_t f = {103, p->pos, FUNC};
    void *res_103;
    ast_expr_t *_expr;
    res_103 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_103);
}

// typed_arg:
//     | NAME [':' expr]
static void *typed_arg(parser_t *p) {
    const frame_t f = {104, p->pos, FUNC};
    void *res_104;
    token_t *_name;
    void *_colon_expr;
    res_104 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_colon_expr = typed_arg_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_104);
}

static void *typed_arg_2(parser_t *p) {
    const frame_t f = {105, p->pos, FUNC};
    void *res_105;
    ast_expr_t *_expr;
    res_105 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_105);
}

// simple_arg:
//     | NAME ['=' expr]
static void *simple_arg(parser_t *p) {
    const frame_t f = {106, p->pos, FUNC};
    void *res_106;
    token_t *_name;
    void *_assign_expr;
    res_106 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_assign_expr = simple_arg_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_106);
}

static void *simple_arg_2(parser_t *p) {
    const frame_t f = {107, p->pos, FUNC};
    void *res_107;
    ast_expr_t *_expr;
    res_107 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_107);
}

// simple_args:
//     | ','.simple_arg+
static void *simple_args(parser_t *p) {
    const frame_t f = {108, p->pos, FUNC};
    void *res_108;
    ast_list_t *_simple_args;
    res_108 = enter_frame(p, &f) && (
        (_simple_args = simple_arg_delimited(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_108);
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
    const frame_t f = {109, p->pos, FUNC};
    void *res_109;
    void *_name_list;
    res_109 = enter_frame(p, &f) && (
        (consume(p, 19, "<")) &&
        (_name_list = name_list(p)) &&
        (consume(p, 20, ">"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_109);
}

// builder_args:
//     | simple_args
//     | '(' [typed_arg_list] ')'
static void *builder_args(parser_t *p) {
    const frame_t f = {110, p->pos, FUNC};
    void *res_110;
    void *alt_110;
    res_110 = enter_frame(p, &f) && (
        (alt_110 = simple_args(p)) ||
        (alt_110 = builder_args_2(p))
    ) ? alt_110 : 0;
    return exit_frame(p, &f, res_110);
}

static void *builder_args_2(parser_t *p) {
    const frame_t f = {111, p->pos, FUNC};
    void *res_111;
    void *_typed_arg_list;
    res_111 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_typed_arg_list = typed_arg_list(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_111);
}

// named_expr:
//     | NAME ':=' expr
//     | expr
static ast_named_t *named_expr(parser_t *p) {
    const frame_t f = {112, p->pos, FUNC};
    ast_named_t *res_112;
    ast_expr_t *_expr;
    ast_named_t *alt_112;
    res_112 = enter_frame(p, &f) && (
        (alt_112 = named_expr_1(p)) || (
            (_expr = expr(p)) &&
            (alt_112 = ast_unnamed(_expr)))
    ) ? alt_112 : 0;
    return exit_frame(p, &f, res_112);
}

static ast_named_t *named_expr_1(parser_t *p) {
    const frame_t f = {113, p->pos, FUNC};
    ast_named_t *res_113;
    token_t *_name;
    res_113 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (expr(p))
    ) ? ast_named(_name) : 0;
    return exit_frame(p, &f, res_113);
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
static ast_expr_t *conditional(parser_t *p) {
    const frame_t f = {114, p->pos, FUNC};
    ast_expr_t *res_114;
    ast_expr_t *_disjunction;
    ast_expr_t *_disjunction_1;
    ast_expr_t *_expr;
    res_114 = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (_disjunction = disjunction(p)) &&
        (consume(p, 10, "?")) &&
        (_disjunction_1 = disjunction(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? ast_conditional(p, _disjunction, _disjunction_1, _expr) : 0;
    return exit_frame(p, &f, res_114);
}

// expr:
//     | conditional
//     | disjunction
static ast_expr_t *expr(parser_t *p) {
    const frame_t f = {115, p->pos, FUNC};
    ast_expr_t *res_115;
    ast_expr_t *alt_115;
    res_115 = enter_frame(p, &f) && (
        (alt_115 = conditional(p)) ||
        (alt_115 = disjunction(p))
    ) ? alt_115 : 0;
    return exit_frame(p, &f, res_115);
}

// disjunction (left_recursive):
//     | disjunction 'or' conjunction
//     | conjunction
static ast_expr_t *disjunction(parser_t *p) {
    const frame_t f = {116, p->pos, FUNC};
    ast_expr_t *res_116 = 0;
    if (is_memoized(p, &f, (void **) &res_116)) {
        return res_116;
    }
    ast_expr_t *alt_116;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_116;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_116 = (
                (alt_116 = disjunction_1(p)) ||
                (alt_116 = conjunction(p))
            ) ? alt_116 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_116 = max;
    }
    insert_memo(p, &f, res_116);
    return exit_frame(p, &f, res_116);
}

static ast_expr_t *disjunction_1(parser_t *p) {
    const frame_t f = {117, p->pos, FUNC};
    ast_expr_t *res_117;
    ast_expr_t *_disjunction;
    ast_expr_t *_conjunction;
    res_117 = enter_frame(p, &f) && (
        (_disjunction = disjunction(p)) &&
        (consume(p, 60, "or")) &&
        (_conjunction = conjunction(p))
    ) ? ast_binary(p, _disjunction, _conjunction, LOGIC_OR) : 0;
    return exit_frame(p, &f, res_117);
}

// conjunction (left_recursive):
//     | conjunction 'and' inversion
//     | inversion
static ast_expr_t *conjunction(parser_t *p) {
    const frame_t f = {118, p->pos, FUNC};
    ast_expr_t *res_118 = 0;
    if (is_memoized(p, &f, (void **) &res_118)) {
        return res_118;
    }
    ast_expr_t *alt_118;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_118;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_118 = (
                (alt_118 = conjunction_1(p)) ||
                (alt_118 = inversion(p))
            ) ? alt_118 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_118 = max;
    }
    insert_memo(p, &f, res_118);
    return exit_frame(p, &f, res_118);
}

static ast_expr_t *conjunction_1(parser_t *p) {
    const frame_t f = {119, p->pos, FUNC};
    ast_expr_t *res_119;
    ast_expr_t *_conjunction;
    ast_expr_t *_inversion;
    res_119 = enter_frame(p, &f) && (
        (_conjunction = conjunction(p)) &&
        (consume(p, 59, "and")) &&
        (_inversion = inversion(p))
    ) ? ast_binary(p, _conjunction, _inversion, LOGIC_AND) : 0;
    return exit_frame(p, &f, res_119);
}

// inversion:
//     | 'not' inversion
//     | comparison
static ast_expr_t *inversion(parser_t *p) {
    const frame_t f = {120, p->pos, FUNC};
    ast_expr_t *res_120;
    ast_expr_t *alt_120;
    res_120 = enter_frame(p, &f) && (
        (alt_120 = inversion_1(p)) ||
        (alt_120 = comparison(p))
    ) ? alt_120 : 0;
    return exit_frame(p, &f, res_120);
}

static ast_expr_t *inversion_1(parser_t *p) {
    const frame_t f = {121, p->pos, FUNC};
    ast_expr_t *res_121;
    ast_expr_t *_inversion;
    res_121 = enter_frame(p, &f) && (
        (consume(p, 61, "not")) &&
        (_inversion = inversion(p))
    ) ? ast_unary(p, _inversion, LOGIC_NOT) : 0;
    return exit_frame(p, &f, res_121);
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
static ast_expr_t *comparison(parser_t *p) {
    const frame_t f = {122, p->pos, FUNC};
    ast_expr_t *res_122;
    ast_expr_t *alt_122;
    res_122 = enter_frame(p, &f) && (
        (alt_122 = comparison_1(p)) ||
        (alt_122 = bitwise_or(p))
    ) ? alt_122 : 0;
    return exit_frame(p, &f, res_122);
}

static ast_expr_t *comparison_1(parser_t *p) {
    const frame_t f = {123, p->pos, FUNC};
    ast_expr_t *res_123;
    ast_expr_t *_bitwise_or;
    ast_list_t *_comp_op_bitwise_ors;
    res_123 = enter_frame(p, &f) && (
        (_bitwise_or = bitwise_or(p)) &&
        (_comp_op_bitwise_ors = comparison_1_2_loop(p))
    ) ? ast_comparison(p, _bitwise_or, _comp_op_bitwise_ors) : 0;
    return exit_frame(p, &f, res_123);
}

static ast_list_t *comparison_1_2_loop(parser_t *p) {
    ast_expr_t *_comp_op_bitwise_or = comparison_1_2(p);
    if (!_comp_op_bitwise_or) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    do {
        ast_list_append(p, list, _comp_op_bitwise_or);
    } while ((_comp_op_bitwise_or = comparison_1_2(p)));
    return list;
}

static ast_expr_t *comparison_1_2(parser_t *p) {
    const frame_t f = {124, p->pos, FUNC};
    ast_expr_t *res_124;
    int *_comp_op;
    ast_expr_t *_bitwise_or;
    res_124 = enter_frame(p, &f) && (
        (_comp_op = comp_op(p)) &&
        (_bitwise_or = bitwise_or(p))
    ) ? ast_comp_term(p, _comp_op, _bitwise_or) : 0;
    return exit_frame(p, &f, res_124);
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
static int *comp_op(parser_t *p) {
    const frame_t f = {125, p->pos, FUNC};
    int *res_125;
    int *alt_125;
    res_125 = enter_frame(p, &f) && ((
            (consume(p, 19, "<")) &&
            (alt_125 = ast_integer(p, CMP_LT))
        ) || (
            (consume(p, 20, ">")) &&
            (alt_125 = ast_integer(p, CMP_GT))
        ) || (
            (consume(p, 31, "==")) &&
            (alt_125 = ast_integer(p, CMP_EQ))
        ) || (
            (consume(p, 34, ">=")) &&
            (alt_125 = ast_integer(p, CMP_GE))
        ) || (
            (consume(p, 33, "<=")) &&
            (alt_125 = ast_integer(p, CMP_LE))
        ) || (
            (consume(p, 32, "!=")) &&
            (alt_125 = ast_integer(p, CMP_NE))
        ) || (
            (consume(p, 63, "in")) &&
            (alt_125 = ast_integer(p, CMP_IN))
        ) ||
        (alt_125 = comp_op_8(p)) || (
            (consume(p, 62, "is")) &&
            (alt_125 = ast_integer(p, CMP_IS))
        ) ||
        (alt_125 = comp_op_10(p))
    ) ? alt_125 : 0;
    return exit_frame(p, &f, res_125);
}

static int *comp_op_8(parser_t *p) {
    const frame_t f = {126, p->pos, FUNC};
    int *res_126;
    res_126 = enter_frame(p, &f) && (
        (consume(p, 61, "not")) &&
        (consume(p, 63, "in"))
    ) ? ast_integer(p, CMP_NI) : 0;
    return exit_frame(p, &f, res_126);
}

static int *comp_op_10(parser_t *p) {
    const frame_t f = {127, p->pos, FUNC};
    int *res_127;
    res_127 = enter_frame(p, &f) && (
        (consume(p, 62, "is")) &&
        (consume(p, 61, "not"))
    ) ? ast_integer(p, CMP_NS) : 0;
    return exit_frame(p, &f, res_127);
}

// bitwise_or (left_recursive):
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
static ast_expr_t *bitwise_or(parser_t *p) {
    const frame_t f = {128, p->pos, FUNC};
    ast_expr_t *res_128 = 0;
    if (is_memoized(p, &f, (void **) &res_128)) {
        return res_128;
    }
    ast_expr_t *alt_128;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_128;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_128 = (
                (alt_128 = bitwise_or_1(p)) ||
                (alt_128 = bitwise_xor(p))
            ) ? alt_128 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_128 = max;
    }
    insert_memo(p, &f, res_128);
    return exit_frame(p, &f, res_128);
}

static ast_expr_t *bitwise_or_1(parser_t *p) {
    const frame_t f = {129, p->pos, FUNC};
    ast_expr_t *res_129;
    ast_expr_t *_bitwise_or;
    ast_expr_t *_bitwise_xor;
    res_129 = enter_frame(p, &f) && (
        (_bitwise_or = bitwise_or(p)) &&
        (consume(p, 27, "|")) &&
        (_bitwise_xor = bitwise_xor(p))
    ) ? ast_binary(p, _bitwise_or, _bitwise_xor, BINOP_IOR) : 0;
    return exit_frame(p, &f, res_129);
}

// bitwise_xor (left_recursive):
//     | bitwise_xor '^' bitwise_and
//     | bitwise_and
static ast_expr_t *bitwise_xor(parser_t *p) {
    const frame_t f = {130, p->pos, FUNC};
    ast_expr_t *res_130 = 0;
    if (is_memoized(p, &f, (void **) &res_130)) {
        return res_130;
    }
    ast_expr_t *alt_130;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_130;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_130 = (
                (alt_130 = bitwise_xor_1(p)) ||
                (alt_130 = bitwise_and(p))
            ) ? alt_130 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_130 = max;
    }
    insert_memo(p, &f, res_130);
    return exit_frame(p, &f, res_130);
}

static ast_expr_t *bitwise_xor_1(parser_t *p) {
    const frame_t f = {131, p->pos, FUNC};
    ast_expr_t *res_131;
    ast_expr_t *_bitwise_xor;
    ast_expr_t *_bitwise_and;
    res_131 = enter_frame(p, &f) && (
        (_bitwise_xor = bitwise_xor(p)) &&
        (consume(p, 30, "^")) &&
        (_bitwise_and = bitwise_and(p))
    ) ? ast_binary(p, _bitwise_xor, _bitwise_and, BINOP_XOR) : 0;
    return exit_frame(p, &f, res_131);
}

// bitwise_and (left_recursive):
//     | bitwise_and '&' shift_expr
//     | shift_expr
static ast_expr_t *bitwise_and(parser_t *p) {
    const frame_t f = {132, p->pos, FUNC};
    ast_expr_t *res_132 = 0;
    if (is_memoized(p, &f, (void **) &res_132)) {
        return res_132;
    }
    ast_expr_t *alt_132;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_132;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_132 = (
                (alt_132 = bitwise_and_1(p)) ||
                (alt_132 = shift_expr(p))
            ) ? alt_132 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_132 = max;
    }
    insert_memo(p, &f, res_132);
    return exit_frame(p, &f, res_132);
}

static ast_expr_t *bitwise_and_1(parser_t *p) {
    const frame_t f = {133, p->pos, FUNC};
    ast_expr_t *res_133;
    ast_expr_t *_bitwise_and;
    ast_expr_t *_shift_expr;
    res_133 = enter_frame(p, &f) && (
        (_bitwise_and = bitwise_and(p)) &&
        (consume(p, 28, "&")) &&
        (_shift_expr = shift_expr(p))
    ) ? ast_binary(p, _bitwise_and, _shift_expr, BINOP_AND) : 0;
    return exit_frame(p, &f, res_133);
}

// shift_expr (left_recursive):
//     | shift_expr '<<' sum
//     | shift_expr '>>' sum
//     | sum
static ast_expr_t *shift_expr(parser_t *p) {
    const frame_t f = {134, p->pos, FUNC};
    ast_expr_t *res_134 = 0;
    if (is_memoized(p, &f, (void **) &res_134)) {
        return res_134;
    }
    ast_expr_t *alt_134;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_134;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_134 = (
                (alt_134 = shift_expr_1(p)) ||
                (alt_134 = shift_expr_2(p)) ||
                (alt_134 = sum(p))
            ) ? alt_134 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_134 = max;
    }
    insert_memo(p, &f, res_134);
    return exit_frame(p, &f, res_134);
}

static ast_expr_t *shift_expr_1(parser_t *p) {
    const frame_t f = {135, p->pos, FUNC};
    ast_expr_t *res_135;
    ast_expr_t *_shift_expr;
    ast_expr_t *_sum;
    res_135 = enter_frame(p, &f) && (
        (_shift_expr = shift_expr(p)) &&
        (consume(p, 48, "<<")) &&
        (_sum = sum(p))
    ) ? ast_binary(p, _shift_expr, _sum, BINOP_SHL) : 0;
    return exit_frame(p, &f, res_135);
}

static ast_expr_t *shift_expr_2(parser_t *p) {
    const frame_t f = {136, p->pos, FUNC};
    ast_expr_t *res_136;
    ast_expr_t *_shift_expr;
    ast_expr_t *_sum;
    res_136 = enter_frame(p, &f) && (
        (_shift_expr = shift_expr(p)) &&
        (consume(p, 49, ">>")) &&
        (_sum = sum(p))
    ) ? ast_binary(p, _shift_expr, _sum, BINOP_SHR) : 0;
    return exit_frame(p, &f, res_136);
}

// sum (left_recursive):
//     | sum '+' term
//     | sum '-' term
//     | term
static ast_expr_t *sum(parser_t *p) {
    const frame_t f = {137, p->pos, FUNC};
    ast_expr_t *res_137 = 0;
    if (is_memoized(p, &f, (void **) &res_137)) {
        return res_137;
    }
    ast_expr_t *alt_137;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_137;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_137 = (
                (alt_137 = sum_1(p)) ||
                (alt_137 = sum_2(p)) ||
                (alt_137 = term(p))
            ) ? alt_137 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_137 = max;
    }
    insert_memo(p, &f, res_137);
    return exit_frame(p, &f, res_137);
}

static ast_expr_t *sum_1(parser_t *p) {
    const frame_t f = {138, p->pos, FUNC};
    ast_expr_t *res_138;
    ast_expr_t *_sum;
    ast_expr_t *_term;
    res_138 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 21, "+")) &&
        (_term = term(p))
    ) ? ast_binary(p, _sum, _term, BINOP_PLS) : 0;
    return exit_frame(p, &f, res_138);
}

static ast_expr_t *sum_2(parser_t *p) {
    const frame_t f = {139, p->pos, FUNC};
    ast_expr_t *res_139;
    ast_expr_t *_sum;
    ast_expr_t *_term;
    res_139 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 22, "-")) &&
        (_term = term(p))
    ) ? ast_binary(p, _sum, _term, BINOP_MIN) : 0;
    return exit_frame(p, &f, res_139);
}

// term (left_recursive):
//     | term '*' pipe_expr
//     | term '/' pipe_expr
//     | term '%' pipe_expr
//     | term '//' pipe_expr
//     | term '@' pipe_expr
//     | pipe_expr
static ast_expr_t *term(parser_t *p) {
    const frame_t f = {140, p->pos, FUNC};
    ast_expr_t *res_140 = 0;
    if (is_memoized(p, &f, (void **) &res_140)) {
        return res_140;
    }
    ast_expr_t *alt_140;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_140;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_140 = (
                (alt_140 = term_1(p)) ||
                (alt_140 = term_2(p)) ||
                (alt_140 = term_3(p)) ||
                (alt_140 = term_4(p)) ||
                (alt_140 = term_5(p)) ||
                (alt_140 = pipe_expr(p))
            ) ? alt_140 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_140 = max;
    }
    insert_memo(p, &f, res_140);
    return exit_frame(p, &f, res_140);
}

static ast_expr_t *term_1(parser_t *p) {
    const frame_t f = {141, p->pos, FUNC};
    ast_expr_t *res_141;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_141 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 23, "*")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_MUL) : 0;
    return exit_frame(p, &f, res_141);
}

static ast_expr_t *term_2(parser_t *p) {
    const frame_t f = {142, p->pos, FUNC};
    ast_expr_t *res_142;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_142 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 24, "/")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_DIV) : 0;
    return exit_frame(p, &f, res_142);
}

static ast_expr_t *term_3(parser_t *p) {
    const frame_t f = {143, p->pos, FUNC};
    ast_expr_t *res_143;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_143 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 25, "%")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_MOD) : 0;
    return exit_frame(p, &f, res_143);
}

static ast_expr_t *term_4(parser_t *p) {
    const frame_t f = {144, p->pos, FUNC};
    ast_expr_t *res_144;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_144 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 37, "//")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_FDV) : 0;
    return exit_frame(p, &f, res_144);
}

static ast_expr_t *term_5(parser_t *p) {
    const frame_t f = {145, p->pos, FUNC};
    ast_expr_t *res_145;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_145 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 26, "@")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_MML) : 0;
    return exit_frame(p, &f, res_145);
}

// pipe_expr (left_recursive):
//     | pipe_expr '->' factor
//     | factor
static ast_expr_t *pipe_expr(parser_t *p) {
    const frame_t f = {146, p->pos, FUNC};
    ast_expr_t *res_146 = 0;
    if (is_memoized(p, &f, (void **) &res_146)) {
        return res_146;
    }
    ast_expr_t *alt_146;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_146;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_146 = (
                (alt_146 = pipe_expr_1(p)) ||
                (alt_146 = factor(p))
            ) ? alt_146 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_146 = max;
    }
    insert_memo(p, &f, res_146);
    return exit_frame(p, &f, res_146);
}

static ast_expr_t *pipe_expr_1(parser_t *p) {
    const frame_t f = {147, p->pos, FUNC};
    ast_expr_t *res_147;
    ast_expr_t *_pipe_expr;
    ast_expr_t *_factor;
    res_147 = enter_frame(p, &f) && (
        (_pipe_expr = pipe_expr(p)) &&
        (consume(p, 35, "->")) &&
        (_factor = factor(p))
    ) ? ast_binary(p, _pipe_expr, _factor, BINOP_PIP) : 0;
    return exit_frame(p, &f, res_147);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static ast_expr_t *factor(parser_t *p) {
    const frame_t f = {148, p->pos, FUNC};
    ast_expr_t *res_148;
    ast_expr_t *alt_148;
    res_148 = enter_frame(p, &f) && (
        (alt_148 = factor_1(p)) ||
        (alt_148 = factor_2(p)) ||
        (alt_148 = factor_3(p)) ||
        (alt_148 = power(p))
    ) ? alt_148 : 0;
    return exit_frame(p, &f, res_148);
}

static ast_expr_t *factor_1(parser_t *p) {
    const frame_t f = {149, p->pos, FUNC};
    ast_expr_t *res_149;
    ast_expr_t *_factor;
    res_149 = enter_frame(p, &f) && (
        (consume(p, 21, "+")) &&
        (_factor = factor(p))
    ) ? ast_unary(p, _factor, UNARY_PLS) : 0;
    return exit_frame(p, &f, res_149);
}

static ast_expr_t *factor_2(parser_t *p) {
    const frame_t f = {150, p->pos, FUNC};
    ast_expr_t *res_150;
    ast_expr_t *_factor;
    res_150 = enter_frame(p, &f) && (
        (consume(p, 22, "-")) &&
        (_factor = factor(p))
    ) ? ast_unary(p, _factor, UNARY_MIN) : 0;
    return exit_frame(p, &f, res_150);
}

static ast_expr_t *factor_3(parser_t *p) {
    const frame_t f = {151, p->pos, FUNC};
    ast_expr_t *res_151;
    ast_expr_t *_factor;
    res_151 = enter_frame(p, &f) && (
        (consume(p, 29, "~")) &&
        (_factor = factor(p))
    ) ? ast_unary(p, _factor, UNARY_INV) : 0;
    return exit_frame(p, &f, res_151);
}

// power:
//     | primary '**' factor
//     | primary
static ast_expr_t *power(parser_t *p) {
    const frame_t f = {152, p->pos, FUNC};
    ast_expr_t *res_152;
    void *_primary;
    ast_expr_t *alt_152;
    res_152 = enter_frame(p, &f) && (
        (alt_152 = power_1(p)) || (
            (_primary = primary(p)) &&
            (alt_152 = ast_primary_expr(p, _primary)))
    ) ? alt_152 : 0;
    return exit_frame(p, &f, res_152);
}

static ast_expr_t *power_1(parser_t *p) {
    const frame_t f = {153, p->pos, FUNC};
    ast_expr_t *res_153;
    void *_primary;
    ast_expr_t *_factor;
    res_153 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (consume(p, 38, "**")) &&
        (_factor = factor(p))
    ) ? ast_binary(p, _primary, _factor, BINOP_POW) : 0;
    return exit_frame(p, &f, res_153);
}

// primary (left_recursive):
//     | primary '.' NAME
//     | primary invocation
//     | primary subscript
//     | atom
static void *primary(parser_t *p) {
    const frame_t f = {154, p->pos, FUNC};
    void *res_154 = 0;
    if (is_memoized(p, &f, (void **) &res_154)) {
        return res_154;
    }
    void *alt_154;
    size_t maxpos;
    void *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_154;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_154 = (
                (alt_154 = primary_1(p)) ||
                (alt_154 = primary_2(p)) ||
                (alt_154 = primary_3(p)) ||
                (alt_154 = atom(p))
            ) ? alt_154 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_154 = max;
    }
    insert_memo(p, &f, res_154);
    return exit_frame(p, &f, res_154);
}

static void *primary_1(parser_t *p) {
    const frame_t f = {155, p->pos, FUNC};
    void *res_155;
    void *_primary;
    token_t *_name;
    res_155 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (consume(p, 6, ".")) &&
        (_name = consume(p, 3, "NAME"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_155);
}

static void *primary_2(parser_t *p) {
    const frame_t f = {156, p->pos, FUNC};
    void *res_156;
    void *_primary;
    void *_invocation;
    res_156 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (_invocation = invocation(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_156);
}

static void *primary_3(parser_t *p) {
    const frame_t f = {157, p->pos, FUNC};
    void *res_157;
    void *_primary;
    void *_subscript;
    res_157 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (_subscript = subscript(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_157);
}

// tuple_atom:
//     | '(' [list_items] ')'
static void *tuple_atom(parser_t *p) {
    const frame_t f = {158, p->pos, FUNC};
    void *res_158;
    void *_list_items;
    res_158 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_list_items = list_items(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_158);
}

// list_iterable:
//     | '[' list_iterator ']'
static void *list_iterable(parser_t *p) {
    const frame_t f = {159, p->pos, FUNC};
    void *res_159;
    void *_list_iterator;
    res_159 = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (_list_iterator = list_iterator(p)) &&
        (consume(p, 18, "]"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_159);
}

// list_atom:
//     | '[' [list_items] ']'
static void *list_atom(parser_t *p) {
    const frame_t f = {160, p->pos, FUNC};
    void *res_160;
    void *_list_items;
    res_160 = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (_list_items = list_items(p), 1) &&
        (consume(p, 18, "]"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_160);
}

// set_atom:
//     | '{' [set_items] '}'
static void *set_atom(parser_t *p) {
    const frame_t f = {161, p->pos, FUNC};
    void *res_161;
    void *_set_items;
    res_161 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_set_items = set_items(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_161);
}

// dict_iterable:
//     | '{' dict_iterator '}'
static void *dict_iterable(parser_t *p) {
    const frame_t f = {162, p->pos, FUNC};
    void *res_162;
    void *_dict_iterator;
    res_162 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_dict_iterator = dict_iterator(p)) &&
        (consume(p, 16, "}"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_162);
}

// dict_atom:
//     | '{' [dict_items] '}'
static void *dict_atom(parser_t *p) {
    const frame_t f = {163, p->pos, FUNC};
    void *res_163;
    void *_dict_items;
    res_163 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_dict_items = dict_items(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_163);
}

// builder:
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
static void *builder(parser_t *p) {
    const frame_t f = {164, p->pos, FUNC};
    void *res_164;
    void *alt_164;
    res_164 = enter_frame(p, &f) && (
        (alt_164 = builder_1(p)) ||
        (alt_164 = builder_2(p))
    ) ? alt_164 : 0;
    return exit_frame(p, &f, res_164);
}

static void *builder_1(parser_t *p) {
    const frame_t f = {165, p->pos, FUNC};
    void *res_165;
    token_t *_name;
    void *_simple_args;
    ast_expr_t *_expr;
    res_165 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_simple_args = simple_args(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_165);
}

static void *builder_2(parser_t *p) {
    const frame_t f = {166, p->pos, FUNC};
    void *res_166;
    token_t *_name;
    void *_builder_hint;
    void *_builder_args;
    void *_block_suite;
    res_166 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_builder_hint = builder_hint(p), 1) &&
        (_builder_args = builder_args(p), 1) &&
        (_block_suite = block_suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_166);
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
    const frame_t f = {167, p->pos, FUNC};
    void *res_167;
    void *alt_167;
    res_167 = enter_frame(p, &f) && (
        (alt_167 = tuple_atom(p)) ||
        (alt_167 = list_iterable(p)) ||
        (alt_167 = list_atom(p)) ||
        (alt_167 = set_atom(p)) ||
        (alt_167 = dict_iterable(p)) ||
        (alt_167 = dict_atom(p)) ||
        (alt_167 = builder(p)) ||
        (alt_167 = consume(p, 3, "NAME")) ||
        (alt_167 = consume(p, 4, "NUMBER")) ||
        (alt_167 = consume(p, 5, "STRING")) ||
        (alt_167 = consume(p, 81, "None")) ||
        (alt_167 = consume(p, 82, "True")) ||
        (alt_167 = consume(p, 83, "False"))
    ) ? alt_167 : 0;
    return exit_frame(p, &f, res_167);
}
