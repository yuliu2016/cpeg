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
static void *list_item(parser_t *);
static void *list_items(parser_t *);
static ast_list_t *list_item_delimited(parser_t *);
static void *as_name(parser_t *);
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
static void *list_atom(parser_t *);
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

// list_item:
//     | star_expr
//     | named_expr
static void *list_item(parser_t *p) {
    const frame_t f = {38, p->pos, FUNC};
    void *res_38;
    void *alt_38;
    res_38 = enter_frame(p, &f) && (
        (alt_38 = star_expr(p)) ||
        (alt_38 = named_expr(p))
    ) ? alt_38 : 0;
    return exit_frame(p, &f, res_38);
}

// list_items:
//     | ','.list_item+ [',']
static void *list_items(parser_t *p) {
    const frame_t f = {39, p->pos, FUNC};
    void *res_39;
    ast_list_t *_list_items;
    token_t *_is_comma;
    res_39 = enter_frame(p, &f) && (
        (_list_items = list_item_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_39);
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

// as_name:
//     | 'as' NAME
static void *as_name(parser_t *p) {
    const frame_t f = {40, p->pos, FUNC};
    void *res_40;
    token_t *_name;
    res_40 = enter_frame(p, &f) && (
        (consume(p, 65, "as")) &&
        (_name = consume(p, 3, "NAME"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_40);
}

// assignment:
//     | annassign
//     | augassign
//     | simple_assign
static void *assignment(parser_t *p) {
    const frame_t f = {41, p->pos, FUNC};
    void *res_41;
    void *alt_41;
    res_41 = enter_frame(p, &f) && (
        (alt_41 = annassign(p)) ||
        (alt_41 = augassign(p)) ||
        (alt_41 = simple_assign(p))
    ) ? alt_41 : 0;
    return exit_frame(p, &f, res_41);
}

// annassign:
//     | target ':' expr ['=' exprlist]
static void *annassign(parser_t *p) {
    const frame_t f = {42, p->pos, FUNC};
    void *res_42;
    void *_target;
    ast_expr_t *_expr;
    void *_assign_exprlist;
    res_42 = enter_frame(p, &f) && (
        (_target = target(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p)) &&
        (_assign_exprlist = annassign_4(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_42);
}

static void *annassign_4(parser_t *p) {
    const frame_t f = {43, p->pos, FUNC};
    void *res_43;
    void *_exprlist;
    res_43 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_exprlist = exprlist(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_43);
}

// augassign:
//     | target augassign_op exprlist
static void *augassign(parser_t *p) {
    const frame_t f = {44, p->pos, FUNC};
    void *res_44;
    void *_target;
    int *_augassign_op;
    void *_exprlist;
    res_44 = enter_frame(p, &f) && (
        (_target = target(p)) &&
        (_augassign_op = augassign_op(p)) &&
        (_exprlist = exprlist(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_44);
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
static void *simple_assign(parser_t *p) {
    const frame_t f = {45, p->pos, FUNC};
    void *res_45;
    ast_list_t *_targetlist_assigns;
    void *_exprlist_star;
    res_45 = enter_frame(p, &f) && (
        (_targetlist_assigns = simple_assign_1_loop(p)) &&
        (_exprlist_star = exprlist_star(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_45);
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
    const frame_t f = {46, p->pos, FUNC};
    void *res_46;
    void *_targetlist;
    res_46 = enter_frame(p, &f) && (
        (_targetlist = targetlist(p)) &&
        (consume(p, 8, "="))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_46);
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
    const frame_t f = {47, p->pos, FUNC};
    int *res_47;
    int *alt_47;
    res_47 = enter_frame(p, &f) && ((
            (consume(p, 39, "+=")) &&
            (alt_47 = ast_integer(p, BINOP_PLS))
        ) || (
            (consume(p, 40, "-=")) &&
            (alt_47 = ast_integer(p, BINOP_MIN))
        ) || (
            (consume(p, 41, "*=")) &&
            (alt_47 = ast_integer(p, BINOP_MUL))
        ) || (
            (consume(p, 42, "/=")) &&
            (alt_47 = ast_integer(p, BINOP_DIV))
        ) || (
            (consume(p, 43, "%=")) &&
            (alt_47 = ast_integer(p, BINOP_MOD))
        ) || (
            (consume(p, 44, "@=")) &&
            (alt_47 = ast_integer(p, BINOP_MML))
        ) || (
            (consume(p, 45, "|=")) &&
            (alt_47 = ast_integer(p, BINOP_IOR))
        ) || (
            (consume(p, 46, "&=")) &&
            (alt_47 = ast_integer(p, BINOP_AND))
        ) || (
            (consume(p, 47, "^=")) &&
            (alt_47 = ast_integer(p, BINOP_XOR))
        ) || (
            (consume(p, 50, "//=")) &&
            (alt_47 = ast_integer(p, BINOP_FDV))
        ) || (
            (consume(p, 51, "**=")) &&
            (alt_47 = ast_integer(p, BINOP_POW))
        ) || (
            (consume(p, 52, "<<=")) &&
            (alt_47 = ast_integer(p, BINOP_SHL))
        ) || (
            (consume(p, 53, ">>=")) &&
            (alt_47 = ast_integer(p, BINOP_SHR)))
    ) ? alt_47 : 0;
    return exit_frame(p, &f, res_47);
}

// import_name:
//     | 'import' dotted_as_names
static void *import_name(parser_t *p) {
    const frame_t f = {48, p->pos, FUNC};
    void *res_48;
    void *_dotted_as_names;
    res_48 = enter_frame(p, &f) && (
        (consume(p, 67, "import")) &&
        (_dotted_as_names = dotted_as_names(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_48);
}

// import_from:
//     | 'from' import_from_names 'import' import_from_items
static void *import_from(parser_t *p) {
    const frame_t f = {49, p->pos, FUNC};
    void *res_49;
    void *_import_from_names;
    void *_import_from_items;
    res_49 = enter_frame(p, &f) && (
        (consume(p, 66, "from")) &&
        (_import_from_names = import_from_names(p)) &&
        (consume(p, 67, "import")) &&
        (_import_from_items = import_from_items(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_49);
}

// import_from_names:
//     | dotted_name
//     | '.'+ [dotted_name]
static void *import_from_names(parser_t *p) {
    const frame_t f = {50, p->pos, FUNC};
    void *res_50;
    void *alt_50;
    res_50 = enter_frame(p, &f) && (
        (alt_50 = dotted_name(p)) ||
        (alt_50 = import_from_names_2(p))
    ) ? alt_50 : 0;
    return exit_frame(p, &f, res_50);
}

static void *import_from_names_2(parser_t *p) {
    const frame_t f = {51, p->pos, FUNC};
    void *res_51;
    void *_dotted_name;
    res_51 = enter_frame(p, &f) && (
        (import_from_names_2_loop(p)) &&
        (_dotted_name = dotted_name(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_51);
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
    const frame_t f = {52, p->pos, FUNC};
    void *res_52;
    void *alt_52;
    res_52 = enter_frame(p, &f) && (
        (alt_52 = consume(p, 23, "*")) ||
        (alt_52 = import_as_names_sp(p)) ||
        (alt_52 = import_as_names(p))
    ) ? alt_52 : 0;
    return exit_frame(p, &f, res_52);
}

// import_as_names_sp:
//     | '(' import_as_names [','] ')'
static void *import_as_names_sp(parser_t *p) {
    const frame_t f = {53, p->pos, FUNC};
    void *res_53;
    void *_import_as_names;
    token_t *_is_comma;
    res_53 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_import_as_names = import_as_names(p)) &&
        (_is_comma = consume(p, 7, ","), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_53);
}

// import_as_name:
//     | NAME [as_name]
static void *import_as_name(parser_t *p) {
    const frame_t f = {54, p->pos, FUNC};
    void *res_54;
    token_t *_name;
    void *_as_name;
    res_54 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_as_name = as_name(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_54);
}

// dotted_as_name:
//     | dotted_name [as_name]
static void *dotted_as_name(parser_t *p) {
    const frame_t f = {55, p->pos, FUNC};
    void *res_55;
    void *_dotted_name;
    void *_as_name;
    res_55 = enter_frame(p, &f) && (
        (_dotted_name = dotted_name(p)) &&
        (_as_name = as_name(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_55);
}

// import_as_names:
//     | ','.import_as_name+
static void *import_as_names(parser_t *p) {
    const frame_t f = {56, p->pos, FUNC};
    void *res_56;
    ast_list_t *_import_as_names;
    res_56 = enter_frame(p, &f) && (
        (_import_as_names = import_as_name_delimited(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_56);
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
    const frame_t f = {57, p->pos, FUNC};
    void *res_57;
    ast_list_t *_dotted_as_names;
    res_57 = enter_frame(p, &f) && (
        (_dotted_as_names = dotted_as_name_delimited(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_57);
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
    const frame_t f = {58, p->pos, FUNC};
    void *res_58;
    ast_list_t *_names;
    res_58 = enter_frame(p, &f) && (
        (_names = dotted_name_delimited(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_58);
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
    const frame_t f = {59, p->pos, FUNC};
    void *res_59;
    void *alt_59;
    res_59 = enter_frame(p, &f) && (
        (alt_59 = if_stmt(p)) ||
        (alt_59 = while_stmt(p)) ||
        (alt_59 = for_stmt(p)) ||
        (alt_59 = try_stmt(p)) ||
        (alt_59 = with_stmt(p))
    ) ? alt_59 : 0;
    return exit_frame(p, &f, res_59);
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
static void *if_stmt(parser_t *p) {
    const frame_t f = {60, p->pos, FUNC};
    void *res_60;
    ast_named_t *_named_expr;
    void *_suite;
    ast_list_t *_elif_stmts;
    void *_else_suite;
    res_60 = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (_named_expr = named_expr(p)) &&
        (_suite = suite(p)) &&
        (_elif_stmts = elif_stmt_loop(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_60);
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
    const frame_t f = {61, p->pos, FUNC};
    void *res_61;
    ast_named_t *_named_expr;
    void *_suite;
    res_61 = enter_frame(p, &f) && (
        (consume(p, 57, "elif")) &&
        (_named_expr = named_expr(p)) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_61);
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
static void *while_stmt(parser_t *p) {
    const frame_t f = {62, p->pos, FUNC};
    void *res_62;
    ast_named_t *_named_expr;
    void *_suite;
    void *_else_suite;
    res_62 = enter_frame(p, &f) && (
        (consume(p, 71, "while")) &&
        (_named_expr = named_expr(p)) &&
        (_suite = suite(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_62);
}

// for_stmt:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
static void *for_stmt(parser_t *p) {
    const frame_t f = {63, p->pos, FUNC};
    void *res_63;
    void *_targetlist;
    void *_exprlist;
    void *_suite;
    void *_else_suite;
    res_63 = enter_frame(p, &f) && (
        (consume(p, 72, "for")) &&
        (_targetlist = targetlist(p)) &&
        (consume(p, 63, "in")) &&
        (_exprlist = exprlist(p)) &&
        (_suite = suite(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_63);
}

// try_stmt:
//     | 'try' suite (except_suite | finally_suite)
static void *try_stmt(parser_t *p) {
    const frame_t f = {64, p->pos, FUNC};
    void *res_64;
    void *_suite;
    void *_except_suite_or_finally_suite;
    res_64 = enter_frame(p, &f) && (
        (consume(p, 75, "try")) &&
        (_suite = suite(p)) &&
        (_except_suite_or_finally_suite = try_stmt_3(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_64);
}

static void *try_stmt_3(parser_t *p) {
    const frame_t f = {65, p->pos, FUNC};
    void *res_65;
    void *alt_65;
    res_65 = enter_frame(p, &f) && (
        (alt_65 = except_suite(p)) ||
        (alt_65 = finally_suite(p))
    ) ? alt_65 : 0;
    return exit_frame(p, &f, res_65);
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
static void *with_stmt(parser_t *p) {
    const frame_t f = {66, p->pos, FUNC};
    void *res_66;
    ast_list_t *_expr_as_names;
    void *_suite;
    res_66 = enter_frame(p, &f) && (
        (consume(p, 68, "with")) &&
        (_expr_as_names = expr_as_name_delimited(p)) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_66);
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
    const frame_t f = {67, p->pos, FUNC};
    void *res_67;
    ast_expr_t *_expr;
    void *_as_name;
    res_67 = enter_frame(p, &f) && (
        (_expr = expr(p)) &&
        (_as_name = as_name(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_67);
}

// block_suite:
//     | '{' NEWLINE stmt_list '}'
//     | '{' [simple_stmt] '}'
static void *block_suite(parser_t *p) {
    const frame_t f = {68, p->pos, FUNC};
    void *res_68;
    void *alt_68;
    res_68 = enter_frame(p, &f) && (
        (alt_68 = block_suite_1(p)) ||
        (alt_68 = block_suite_2(p))
    ) ? alt_68 : 0;
    return exit_frame(p, &f, res_68);
}

static void *block_suite_1(parser_t *p) {
    const frame_t f = {69, p->pos, FUNC};
    void *res_69;
    token_t *_newline;
    void *_stmt_list;
    res_69 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_newline = consume(p, 2, "NEWLINE")) &&
        (_stmt_list = stmt_list(p)) &&
        (consume(p, 16, "}"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_69);
}

static void *block_suite_2(parser_t *p) {
    const frame_t f = {70, p->pos, FUNC};
    void *res_70;
    void *_simple_stmt;
    res_70 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_simple_stmt = simple_stmt(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_70);
}

// suite:
//     | ':' simple_stmt
//     | block_suite
static void *suite(parser_t *p) {
    const frame_t f = {71, p->pos, FUNC};
    void *res_71;
    void *alt_71;
    res_71 = enter_frame(p, &f) && (
        (alt_71 = suite_1(p)) ||
        (alt_71 = block_suite(p))
    ) ? alt_71 : 0;
    return exit_frame(p, &f, res_71);
}

static void *suite_1(parser_t *p) {
    const frame_t f = {72, p->pos, FUNC};
    void *res_72;
    void *_simple_stmt;
    res_72 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_simple_stmt = simple_stmt(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_72);
}

// else_suite:
//     | 'else' suite
static void *else_suite(parser_t *p) {
    const frame_t f = {73, p->pos, FUNC};
    void *res_73;
    void *_suite;
    res_73 = enter_frame(p, &f) && (
        (consume(p, 58, "else")) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_73);
}

// finally_suite:
//     | 'finally' suite
static void *finally_suite(parser_t *p) {
    const frame_t f = {74, p->pos, FUNC};
    void *res_74;
    void *_suite;
    res_74 = enter_frame(p, &f) && (
        (consume(p, 77, "finally")) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_74);
}

// except_clause:
//     | 'except' [expr_as_name] suite
static void *except_clause(parser_t *p) {
    const frame_t f = {75, p->pos, FUNC};
    void *res_75;
    void *_expr_as_name;
    void *_suite;
    res_75 = enter_frame(p, &f) && (
        (consume(p, 76, "except")) &&
        (_expr_as_name = expr_as_name(p), 1) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_75);
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
static void *except_suite(parser_t *p) {
    const frame_t f = {76, p->pos, FUNC};
    void *res_76;
    ast_list_t *_except_clauses;
    void *_else_suite;
    void *_finally_suite;
    res_76 = enter_frame(p, &f) && (
        (_except_clauses = except_clause_loop(p)) &&
        (_else_suite = else_suite(p), 1) &&
        (_finally_suite = finally_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_76);
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
    const frame_t f = {77, p->pos, FUNC};
    void *res_77;
    void *_call_arg_list;
    res_77 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_call_arg_list = call_arg_list(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_77);
}

// call_arg_list:
//     | ','.call_arg+ [',']
static void *call_arg_list(parser_t *p) {
    const frame_t f = {78, p->pos, FUNC};
    void *res_78;
    ast_list_t *_call_args;
    token_t *_is_comma;
    res_78 = enter_frame(p, &f) && (
        (_call_args = call_arg_delimited(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_78);
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
    const frame_t f = {79, p->pos, FUNC};
    void *res_79;
    void *alt_79;
    res_79 = enter_frame(p, &f) && (
        (alt_79 = call_arg_1(p)) ||
        (alt_79 = call_arg_2(p)) ||
        (alt_79 = call_arg_3(p)) ||
        (alt_79 = call_arg_4(p)) ||
        (alt_79 = expr(p))
    ) ? alt_79 : 0;
    return exit_frame(p, &f, res_79);
}

static void *call_arg_1(parser_t *p) {
    const frame_t f = {80, p->pos, FUNC};
    void *res_80;
    token_t *_name;
    ast_expr_t *_expr;
    res_80 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_80);
}

static void *call_arg_2(parser_t *p) {
    const frame_t f = {81, p->pos, FUNC};
    void *res_81;
    token_t *_name;
    ast_expr_t *_expr;
    res_81 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 8, "=")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_81);
}

static void *call_arg_3(parser_t *p) {
    const frame_t f = {82, p->pos, FUNC};
    void *res_82;
    ast_expr_t *_expr;
    res_82 = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_82);
}

static void *call_arg_4(parser_t *p) {
    const frame_t f = {83, p->pos, FUNC};
    void *res_83;
    ast_expr_t *_expr;
    res_83 = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_83);
}

// typed_arg_list:
//     | kwargs
//     | args_kwargs
//     | full_arg_list
static void *typed_arg_list(parser_t *p) {
    const frame_t f = {84, p->pos, FUNC};
    void *res_84;
    void *alt_84;
    res_84 = enter_frame(p, &f) && (
        (alt_84 = kwargs(p)) ||
        (alt_84 = args_kwargs(p)) ||
        (alt_84 = full_arg_list(p))
    ) ? alt_84 : 0;
    return exit_frame(p, &f, res_84);
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
static void *full_arg_list(parser_t *p) {
    const frame_t f = {85, p->pos, FUNC};
    void *res_85;
    ast_list_t *_default_args;
    void *_full_arg_list_2;
    res_85 = enter_frame(p, &f) && (
        (_default_args = default_arg_delimited(p)) &&
        (_full_arg_list_2 = full_arg_list_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_85);
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
    const frame_t f = {86, p->pos, FUNC};
    void *res_86;
    void *_kwargs_or_args_kwargs;
    res_86 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_kwargs_or_args_kwargs = full_arg_list_2_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_86);
}

static void *full_arg_list_2_2(parser_t *p) {
    const frame_t f = {87, p->pos, FUNC};
    void *res_87;
    void *alt_87;
    res_87 = enter_frame(p, &f) && (
        (alt_87 = kwargs(p)) ||
        (alt_87 = args_kwargs(p))
    ) ? alt_87 : 0;
    return exit_frame(p, &f, res_87);
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
static void *args_kwargs(parser_t *p) {
    const frame_t f = {88, p->pos, FUNC};
    void *res_88;
    void *_typed_arg;
    ast_list_t *_comma_default_args;
    void *_args_kwargs_4;
    res_88 = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (_typed_arg = typed_arg(p), 1) &&
        (_comma_default_args = args_kwargs_3_loop(p)) &&
        (_args_kwargs_4 = args_kwargs_4(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_88);
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
    const frame_t f = {89, p->pos, FUNC};
    void *res_89;
    void *_default_arg;
    res_89 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_default_arg = default_arg(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_89);
}

static void *args_kwargs_4(parser_t *p) {
    const frame_t f = {90, p->pos, FUNC};
    void *res_90;
    void *_kwargs;
    res_90 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_kwargs = kwargs(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_90);
}

// kwargs:
//     | '**' typed_arg [',']
static void *kwargs(parser_t *p) {
    const frame_t f = {91, p->pos, FUNC};
    void *res_91;
    void *_typed_arg;
    token_t *_is_comma;
    res_91 = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (_typed_arg = typed_arg(p)) &&
        (_is_comma = consume(p, 7, ","), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_91);
}

// default_arg:
//     | typed_arg ['=' expr]
static void *default_arg(parser_t *p) {
    const frame_t f = {92, p->pos, FUNC};
    void *res_92;
    void *_typed_arg;
    void *_assign_expr;
    res_92 = enter_frame(p, &f) && (
        (_typed_arg = typed_arg(p)) &&
        (_assign_expr = default_arg_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_92);
}

static void *default_arg_2(parser_t *p) {
    const frame_t f = {93, p->pos, FUNC};
    void *res_93;
    ast_expr_t *_expr;
    res_93 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_93);
}

// typed_arg:
//     | NAME [':' expr]
static void *typed_arg(parser_t *p) {
    const frame_t f = {94, p->pos, FUNC};
    void *res_94;
    token_t *_name;
    void *_colon_expr;
    res_94 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_colon_expr = typed_arg_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_94);
}

static void *typed_arg_2(parser_t *p) {
    const frame_t f = {95, p->pos, FUNC};
    void *res_95;
    ast_expr_t *_expr;
    res_95 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_95);
}

// simple_arg:
//     | NAME ['=' expr]
static void *simple_arg(parser_t *p) {
    const frame_t f = {96, p->pos, FUNC};
    void *res_96;
    token_t *_name;
    void *_assign_expr;
    res_96 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_assign_expr = simple_arg_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_96);
}

static void *simple_arg_2(parser_t *p) {
    const frame_t f = {97, p->pos, FUNC};
    void *res_97;
    ast_expr_t *_expr;
    res_97 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_97);
}

// simple_args:
//     | ','.simple_arg+
static void *simple_args(parser_t *p) {
    const frame_t f = {98, p->pos, FUNC};
    void *res_98;
    ast_list_t *_simple_args;
    res_98 = enter_frame(p, &f) && (
        (_simple_args = simple_arg_delimited(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_98);
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
    const frame_t f = {99, p->pos, FUNC};
    void *res_99;
    void *_name_list;
    res_99 = enter_frame(p, &f) && (
        (consume(p, 19, "<")) &&
        (_name_list = name_list(p)) &&
        (consume(p, 20, ">"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_99);
}

// builder_args:
//     | simple_args
//     | '(' [typed_arg_list] ')'
static void *builder_args(parser_t *p) {
    const frame_t f = {100, p->pos, FUNC};
    void *res_100;
    void *alt_100;
    res_100 = enter_frame(p, &f) && (
        (alt_100 = simple_args(p)) ||
        (alt_100 = builder_args_2(p))
    ) ? alt_100 : 0;
    return exit_frame(p, &f, res_100);
}

static void *builder_args_2(parser_t *p) {
    const frame_t f = {101, p->pos, FUNC};
    void *res_101;
    void *_typed_arg_list;
    res_101 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_typed_arg_list = typed_arg_list(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_101);
}

// named_expr:
//     | NAME ':=' expr
//     | expr
static ast_named_t *named_expr(parser_t *p) {
    const frame_t f = {102, p->pos, FUNC};
    ast_named_t *res_102;
    ast_expr_t *_expr;
    ast_named_t *alt_102;
    res_102 = enter_frame(p, &f) && (
        (alt_102 = named_expr_1(p)) || (
            (_expr = expr(p)) &&
            (alt_102 = ast_unnamed(p, _expr)))
    ) ? alt_102 : 0;
    return exit_frame(p, &f, res_102);
}

static ast_named_t *named_expr_1(parser_t *p) {
    const frame_t f = {103, p->pos, FUNC};
    ast_named_t *res_103;
    token_t *_name;
    ast_expr_t *_expr;
    res_103 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (_expr = expr(p))
    ) ? ast_named(p, _name, _expr) : 0;
    return exit_frame(p, &f, res_103);
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
static ast_expr_t *conditional(parser_t *p) {
    const frame_t f = {104, p->pos, FUNC};
    ast_expr_t *res_104;
    ast_expr_t *_disjunction;
    ast_expr_t *_disjunction_1;
    ast_expr_t *_expr;
    res_104 = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (_disjunction = disjunction(p)) &&
        (consume(p, 10, "?")) &&
        (_disjunction_1 = disjunction(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? ast_conditional(p, _disjunction, _disjunction_1, _expr) : 0;
    return exit_frame(p, &f, res_104);
}

// expr:
//     | conditional
//     | disjunction
static ast_expr_t *expr(parser_t *p) {
    const frame_t f = {105, p->pos, FUNC};
    ast_expr_t *res_105;
    ast_expr_t *alt_105;
    res_105 = enter_frame(p, &f) && (
        (alt_105 = conditional(p)) ||
        (alt_105 = disjunction(p))
    ) ? alt_105 : 0;
    return exit_frame(p, &f, res_105);
}

// disjunction (left_recursive):
//     | disjunction 'or' conjunction
//     | conjunction
static ast_expr_t *disjunction(parser_t *p) {
    const frame_t f = {106, p->pos, FUNC};
    ast_expr_t *res_106 = 0;
    if (is_memoized(p, &f, (void **) &res_106)) {
        return res_106;
    }
    ast_expr_t *alt_106;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_106;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_106 = (
                (alt_106 = disjunction_1(p)) ||
                (alt_106 = conjunction(p))
            ) ? alt_106 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_106 = max;
    }
    insert_memo(p, &f, res_106);
    return exit_frame(p, &f, res_106);
}

static ast_expr_t *disjunction_1(parser_t *p) {
    const frame_t f = {107, p->pos, FUNC};
    ast_expr_t *res_107;
    ast_expr_t *_disjunction;
    ast_expr_t *_conjunction;
    res_107 = enter_frame(p, &f) && (
        (_disjunction = disjunction(p)) &&
        (consume(p, 60, "or")) &&
        (_conjunction = conjunction(p))
    ) ? ast_binary(p, _disjunction, _conjunction, LOGIC_OR) : 0;
    return exit_frame(p, &f, res_107);
}

// conjunction (left_recursive):
//     | conjunction 'and' inversion
//     | inversion
static ast_expr_t *conjunction(parser_t *p) {
    const frame_t f = {108, p->pos, FUNC};
    ast_expr_t *res_108 = 0;
    if (is_memoized(p, &f, (void **) &res_108)) {
        return res_108;
    }
    ast_expr_t *alt_108;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_108;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_108 = (
                (alt_108 = conjunction_1(p)) ||
                (alt_108 = inversion(p))
            ) ? alt_108 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_108 = max;
    }
    insert_memo(p, &f, res_108);
    return exit_frame(p, &f, res_108);
}

static ast_expr_t *conjunction_1(parser_t *p) {
    const frame_t f = {109, p->pos, FUNC};
    ast_expr_t *res_109;
    ast_expr_t *_conjunction;
    ast_expr_t *_inversion;
    res_109 = enter_frame(p, &f) && (
        (_conjunction = conjunction(p)) &&
        (consume(p, 59, "and")) &&
        (_inversion = inversion(p))
    ) ? ast_binary(p, _conjunction, _inversion, LOGIC_AND) : 0;
    return exit_frame(p, &f, res_109);
}

// inversion:
//     | 'not' inversion
//     | comparison
static ast_expr_t *inversion(parser_t *p) {
    const frame_t f = {110, p->pos, FUNC};
    ast_expr_t *res_110;
    ast_expr_t *alt_110;
    res_110 = enter_frame(p, &f) && (
        (alt_110 = inversion_1(p)) ||
        (alt_110 = comparison(p))
    ) ? alt_110 : 0;
    return exit_frame(p, &f, res_110);
}

static ast_expr_t *inversion_1(parser_t *p) {
    const frame_t f = {111, p->pos, FUNC};
    ast_expr_t *res_111;
    ast_expr_t *_inversion;
    res_111 = enter_frame(p, &f) && (
        (consume(p, 61, "not")) &&
        (_inversion = inversion(p))
    ) ? ast_unary(p, _inversion, LOGIC_NOT) : 0;
    return exit_frame(p, &f, res_111);
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
static ast_expr_t *comparison(parser_t *p) {
    const frame_t f = {112, p->pos, FUNC};
    ast_expr_t *res_112;
    ast_expr_t *alt_112;
    res_112 = enter_frame(p, &f) && (
        (alt_112 = comparison_1(p)) ||
        (alt_112 = bitwise_or(p))
    ) ? alt_112 : 0;
    return exit_frame(p, &f, res_112);
}

static ast_expr_t *comparison_1(parser_t *p) {
    const frame_t f = {113, p->pos, FUNC};
    ast_expr_t *res_113;
    ast_expr_t *_bitwise_or;
    ast_list_t *_comp_op_bitwise_ors;
    res_113 = enter_frame(p, &f) && (
        (_bitwise_or = bitwise_or(p)) &&
        (_comp_op_bitwise_ors = comparison_1_2_loop(p))
    ) ? ast_comparison(p, _bitwise_or, _comp_op_bitwise_ors) : 0;
    return exit_frame(p, &f, res_113);
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
    const frame_t f = {114, p->pos, FUNC};
    ast_expr_t *res_114;
    int *_comp_op;
    ast_expr_t *_bitwise_or;
    res_114 = enter_frame(p, &f) && (
        (_comp_op = comp_op(p)) &&
        (_bitwise_or = bitwise_or(p))
    ) ? ast_comp_term(p, _comp_op, _bitwise_or) : 0;
    return exit_frame(p, &f, res_114);
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
    const frame_t f = {115, p->pos, FUNC};
    int *res_115;
    int *alt_115;
    res_115 = enter_frame(p, &f) && ((
            (consume(p, 19, "<")) &&
            (alt_115 = ast_integer(p, CMP_LT))
        ) || (
            (consume(p, 20, ">")) &&
            (alt_115 = ast_integer(p, CMP_GT))
        ) || (
            (consume(p, 31, "==")) &&
            (alt_115 = ast_integer(p, CMP_EQ))
        ) || (
            (consume(p, 34, ">=")) &&
            (alt_115 = ast_integer(p, CMP_GE))
        ) || (
            (consume(p, 33, "<=")) &&
            (alt_115 = ast_integer(p, CMP_LE))
        ) || (
            (consume(p, 32, "!=")) &&
            (alt_115 = ast_integer(p, CMP_NE))
        ) || (
            (consume(p, 63, "in")) &&
            (alt_115 = ast_integer(p, CMP_IN))
        ) ||
        (alt_115 = comp_op_8(p)) || (
            (consume(p, 62, "is")) &&
            (alt_115 = ast_integer(p, CMP_IS))
        ) ||
        (alt_115 = comp_op_10(p))
    ) ? alt_115 : 0;
    return exit_frame(p, &f, res_115);
}

static int *comp_op_8(parser_t *p) {
    const frame_t f = {116, p->pos, FUNC};
    int *res_116;
    res_116 = enter_frame(p, &f) && (
        (consume(p, 61, "not")) &&
        (consume(p, 63, "in"))
    ) ? ast_integer(p, CMP_NI) : 0;
    return exit_frame(p, &f, res_116);
}

static int *comp_op_10(parser_t *p) {
    const frame_t f = {117, p->pos, FUNC};
    int *res_117;
    res_117 = enter_frame(p, &f) && (
        (consume(p, 62, "is")) &&
        (consume(p, 61, "not"))
    ) ? ast_integer(p, CMP_NS) : 0;
    return exit_frame(p, &f, res_117);
}

// bitwise_or (left_recursive):
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
static ast_expr_t *bitwise_or(parser_t *p) {
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
                (alt_118 = bitwise_or_1(p)) ||
                (alt_118 = bitwise_xor(p))
            ) ? alt_118 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_118 = max;
    }
    insert_memo(p, &f, res_118);
    return exit_frame(p, &f, res_118);
}

static ast_expr_t *bitwise_or_1(parser_t *p) {
    const frame_t f = {119, p->pos, FUNC};
    ast_expr_t *res_119;
    ast_expr_t *_bitwise_or;
    ast_expr_t *_bitwise_xor;
    res_119 = enter_frame(p, &f) && (
        (_bitwise_or = bitwise_or(p)) &&
        (consume(p, 27, "|")) &&
        (_bitwise_xor = bitwise_xor(p))
    ) ? ast_binary(p, _bitwise_or, _bitwise_xor, BINOP_IOR) : 0;
    return exit_frame(p, &f, res_119);
}

// bitwise_xor (left_recursive):
//     | bitwise_xor '^' bitwise_and
//     | bitwise_and
static ast_expr_t *bitwise_xor(parser_t *p) {
    const frame_t f = {120, p->pos, FUNC};
    ast_expr_t *res_120 = 0;
    if (is_memoized(p, &f, (void **) &res_120)) {
        return res_120;
    }
    ast_expr_t *alt_120;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_120;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_120 = (
                (alt_120 = bitwise_xor_1(p)) ||
                (alt_120 = bitwise_and(p))
            ) ? alt_120 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_120 = max;
    }
    insert_memo(p, &f, res_120);
    return exit_frame(p, &f, res_120);
}

static ast_expr_t *bitwise_xor_1(parser_t *p) {
    const frame_t f = {121, p->pos, FUNC};
    ast_expr_t *res_121;
    ast_expr_t *_bitwise_xor;
    ast_expr_t *_bitwise_and;
    res_121 = enter_frame(p, &f) && (
        (_bitwise_xor = bitwise_xor(p)) &&
        (consume(p, 30, "^")) &&
        (_bitwise_and = bitwise_and(p))
    ) ? ast_binary(p, _bitwise_xor, _bitwise_and, BINOP_XOR) : 0;
    return exit_frame(p, &f, res_121);
}

// bitwise_and (left_recursive):
//     | bitwise_and '&' shift_expr
//     | shift_expr
static ast_expr_t *bitwise_and(parser_t *p) {
    const frame_t f = {122, p->pos, FUNC};
    ast_expr_t *res_122 = 0;
    if (is_memoized(p, &f, (void **) &res_122)) {
        return res_122;
    }
    ast_expr_t *alt_122;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_122;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_122 = (
                (alt_122 = bitwise_and_1(p)) ||
                (alt_122 = shift_expr(p))
            ) ? alt_122 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_122 = max;
    }
    insert_memo(p, &f, res_122);
    return exit_frame(p, &f, res_122);
}

static ast_expr_t *bitwise_and_1(parser_t *p) {
    const frame_t f = {123, p->pos, FUNC};
    ast_expr_t *res_123;
    ast_expr_t *_bitwise_and;
    ast_expr_t *_shift_expr;
    res_123 = enter_frame(p, &f) && (
        (_bitwise_and = bitwise_and(p)) &&
        (consume(p, 28, "&")) &&
        (_shift_expr = shift_expr(p))
    ) ? ast_binary(p, _bitwise_and, _shift_expr, BINOP_AND) : 0;
    return exit_frame(p, &f, res_123);
}

// shift_expr (left_recursive):
//     | shift_expr '<<' sum
//     | shift_expr '>>' sum
//     | sum
static ast_expr_t *shift_expr(parser_t *p) {
    const frame_t f = {124, p->pos, FUNC};
    ast_expr_t *res_124 = 0;
    if (is_memoized(p, &f, (void **) &res_124)) {
        return res_124;
    }
    ast_expr_t *alt_124;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_124;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_124 = (
                (alt_124 = shift_expr_1(p)) ||
                (alt_124 = shift_expr_2(p)) ||
                (alt_124 = sum(p))
            ) ? alt_124 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_124 = max;
    }
    insert_memo(p, &f, res_124);
    return exit_frame(p, &f, res_124);
}

static ast_expr_t *shift_expr_1(parser_t *p) {
    const frame_t f = {125, p->pos, FUNC};
    ast_expr_t *res_125;
    ast_expr_t *_shift_expr;
    ast_expr_t *_sum;
    res_125 = enter_frame(p, &f) && (
        (_shift_expr = shift_expr(p)) &&
        (consume(p, 48, "<<")) &&
        (_sum = sum(p))
    ) ? ast_binary(p, _shift_expr, _sum, BINOP_SHL) : 0;
    return exit_frame(p, &f, res_125);
}

static ast_expr_t *shift_expr_2(parser_t *p) {
    const frame_t f = {126, p->pos, FUNC};
    ast_expr_t *res_126;
    ast_expr_t *_shift_expr;
    ast_expr_t *_sum;
    res_126 = enter_frame(p, &f) && (
        (_shift_expr = shift_expr(p)) &&
        (consume(p, 49, ">>")) &&
        (_sum = sum(p))
    ) ? ast_binary(p, _shift_expr, _sum, BINOP_SHR) : 0;
    return exit_frame(p, &f, res_126);
}

// sum (left_recursive):
//     | sum '+' term
//     | sum '-' term
//     | term
static ast_expr_t *sum(parser_t *p) {
    const frame_t f = {127, p->pos, FUNC};
    ast_expr_t *res_127 = 0;
    if (is_memoized(p, &f, (void **) &res_127)) {
        return res_127;
    }
    ast_expr_t *alt_127;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_127;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_127 = (
                (alt_127 = sum_1(p)) ||
                (alt_127 = sum_2(p)) ||
                (alt_127 = term(p))
            ) ? alt_127 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_127 = max;
    }
    insert_memo(p, &f, res_127);
    return exit_frame(p, &f, res_127);
}

static ast_expr_t *sum_1(parser_t *p) {
    const frame_t f = {128, p->pos, FUNC};
    ast_expr_t *res_128;
    ast_expr_t *_sum;
    ast_expr_t *_term;
    res_128 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 21, "+")) &&
        (_term = term(p))
    ) ? ast_binary(p, _sum, _term, BINOP_PLS) : 0;
    return exit_frame(p, &f, res_128);
}

static ast_expr_t *sum_2(parser_t *p) {
    const frame_t f = {129, p->pos, FUNC};
    ast_expr_t *res_129;
    ast_expr_t *_sum;
    ast_expr_t *_term;
    res_129 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 22, "-")) &&
        (_term = term(p))
    ) ? ast_binary(p, _sum, _term, BINOP_MIN) : 0;
    return exit_frame(p, &f, res_129);
}

// term (left_recursive):
//     | term '*' pipe_expr
//     | term '/' pipe_expr
//     | term '%' pipe_expr
//     | term '//' pipe_expr
//     | term '@' pipe_expr
//     | pipe_expr
static ast_expr_t *term(parser_t *p) {
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
                (alt_130 = term_1(p)) ||
                (alt_130 = term_2(p)) ||
                (alt_130 = term_3(p)) ||
                (alt_130 = term_4(p)) ||
                (alt_130 = term_5(p)) ||
                (alt_130 = pipe_expr(p))
            ) ? alt_130 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_130 = max;
    }
    insert_memo(p, &f, res_130);
    return exit_frame(p, &f, res_130);
}

static ast_expr_t *term_1(parser_t *p) {
    const frame_t f = {131, p->pos, FUNC};
    ast_expr_t *res_131;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_131 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 23, "*")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_MUL) : 0;
    return exit_frame(p, &f, res_131);
}

static ast_expr_t *term_2(parser_t *p) {
    const frame_t f = {132, p->pos, FUNC};
    ast_expr_t *res_132;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_132 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 24, "/")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_DIV) : 0;
    return exit_frame(p, &f, res_132);
}

static ast_expr_t *term_3(parser_t *p) {
    const frame_t f = {133, p->pos, FUNC};
    ast_expr_t *res_133;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_133 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 25, "%")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_MOD) : 0;
    return exit_frame(p, &f, res_133);
}

static ast_expr_t *term_4(parser_t *p) {
    const frame_t f = {134, p->pos, FUNC};
    ast_expr_t *res_134;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_134 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 37, "//")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_FDV) : 0;
    return exit_frame(p, &f, res_134);
}

static ast_expr_t *term_5(parser_t *p) {
    const frame_t f = {135, p->pos, FUNC};
    ast_expr_t *res_135;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_135 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 26, "@")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_MML) : 0;
    return exit_frame(p, &f, res_135);
}

// pipe_expr (left_recursive):
//     | pipe_expr '->' factor
//     | factor
static ast_expr_t *pipe_expr(parser_t *p) {
    const frame_t f = {136, p->pos, FUNC};
    ast_expr_t *res_136 = 0;
    if (is_memoized(p, &f, (void **) &res_136)) {
        return res_136;
    }
    ast_expr_t *alt_136;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_136;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_136 = (
                (alt_136 = pipe_expr_1(p)) ||
                (alt_136 = factor(p))
            ) ? alt_136 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_136 = max;
    }
    insert_memo(p, &f, res_136);
    return exit_frame(p, &f, res_136);
}

static ast_expr_t *pipe_expr_1(parser_t *p) {
    const frame_t f = {137, p->pos, FUNC};
    ast_expr_t *res_137;
    ast_expr_t *_pipe_expr;
    ast_expr_t *_factor;
    res_137 = enter_frame(p, &f) && (
        (_pipe_expr = pipe_expr(p)) &&
        (consume(p, 35, "->")) &&
        (_factor = factor(p))
    ) ? ast_binary(p, _pipe_expr, _factor, BINOP_PIP) : 0;
    return exit_frame(p, &f, res_137);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static ast_expr_t *factor(parser_t *p) {
    const frame_t f = {138, p->pos, FUNC};
    ast_expr_t *res_138;
    ast_expr_t *alt_138;
    res_138 = enter_frame(p, &f) && (
        (alt_138 = factor_1(p)) ||
        (alt_138 = factor_2(p)) ||
        (alt_138 = factor_3(p)) ||
        (alt_138 = power(p))
    ) ? alt_138 : 0;
    return exit_frame(p, &f, res_138);
}

static ast_expr_t *factor_1(parser_t *p) {
    const frame_t f = {139, p->pos, FUNC};
    ast_expr_t *res_139;
    ast_expr_t *_factor;
    res_139 = enter_frame(p, &f) && (
        (consume(p, 21, "+")) &&
        (_factor = factor(p))
    ) ? ast_unary(p, _factor, UNARY_PLS) : 0;
    return exit_frame(p, &f, res_139);
}

static ast_expr_t *factor_2(parser_t *p) {
    const frame_t f = {140, p->pos, FUNC};
    ast_expr_t *res_140;
    ast_expr_t *_factor;
    res_140 = enter_frame(p, &f) && (
        (consume(p, 22, "-")) &&
        (_factor = factor(p))
    ) ? ast_unary(p, _factor, UNARY_MIN) : 0;
    return exit_frame(p, &f, res_140);
}

static ast_expr_t *factor_3(parser_t *p) {
    const frame_t f = {141, p->pos, FUNC};
    ast_expr_t *res_141;
    ast_expr_t *_factor;
    res_141 = enter_frame(p, &f) && (
        (consume(p, 29, "~")) &&
        (_factor = factor(p))
    ) ? ast_unary(p, _factor, UNARY_INV) : 0;
    return exit_frame(p, &f, res_141);
}

// power:
//     | primary '**' factor
//     | primary
static ast_expr_t *power(parser_t *p) {
    const frame_t f = {142, p->pos, FUNC};
    ast_expr_t *res_142;
    void *_primary;
    ast_expr_t *alt_142;
    res_142 = enter_frame(p, &f) && (
        (alt_142 = power_1(p)) || (
            (_primary = primary(p)) &&
            (alt_142 = ast_primary_expr(p, _primary)))
    ) ? alt_142 : 0;
    return exit_frame(p, &f, res_142);
}

static ast_expr_t *power_1(parser_t *p) {
    const frame_t f = {143, p->pos, FUNC};
    ast_expr_t *res_143;
    void *_primary;
    ast_expr_t *_factor;
    res_143 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (consume(p, 38, "**")) &&
        (_factor = factor(p))
    ) ? ast_binary(p, _primary, _factor, BINOP_POW) : 0;
    return exit_frame(p, &f, res_143);
}

// primary (left_recursive):
//     | primary '.' NAME
//     | primary invocation
//     | primary subscript
//     | atom
static void *primary(parser_t *p) {
    const frame_t f = {144, p->pos, FUNC};
    void *res_144 = 0;
    if (is_memoized(p, &f, (void **) &res_144)) {
        return res_144;
    }
    void *alt_144;
    size_t maxpos;
    void *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_144;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_144 = (
                (alt_144 = primary_1(p)) ||
                (alt_144 = primary_2(p)) ||
                (alt_144 = primary_3(p)) ||
                (alt_144 = atom(p))
            ) ? alt_144 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_144 = max;
    }
    insert_memo(p, &f, res_144);
    return exit_frame(p, &f, res_144);
}

static void *primary_1(parser_t *p) {
    const frame_t f = {145, p->pos, FUNC};
    void *res_145;
    void *_primary;
    token_t *_name;
    res_145 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (consume(p, 6, ".")) &&
        (_name = consume(p, 3, "NAME"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_145);
}

static void *primary_2(parser_t *p) {
    const frame_t f = {146, p->pos, FUNC};
    void *res_146;
    void *_primary;
    void *_invocation;
    res_146 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (_invocation = invocation(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_146);
}

static void *primary_3(parser_t *p) {
    const frame_t f = {147, p->pos, FUNC};
    void *res_147;
    void *_primary;
    void *_subscript;
    res_147 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (_subscript = subscript(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_147);
}

// tuple_atom:
//     | '(' [list_items] ')'
static void *tuple_atom(parser_t *p) {
    const frame_t f = {148, p->pos, FUNC};
    void *res_148;
    void *_list_items;
    res_148 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_list_items = list_items(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_148);
}

// list_atom:
//     | '[' [list_items] ']'
static void *list_atom(parser_t *p) {
    const frame_t f = {149, p->pos, FUNC};
    void *res_149;
    void *_list_items;
    res_149 = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (_list_items = list_items(p), 1) &&
        (consume(p, 18, "]"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_149);
}

// builder:
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
static void *builder(parser_t *p) {
    const frame_t f = {150, p->pos, FUNC};
    void *res_150;
    void *alt_150;
    res_150 = enter_frame(p, &f) && (
        (alt_150 = builder_1(p)) ||
        (alt_150 = builder_2(p))
    ) ? alt_150 : 0;
    return exit_frame(p, &f, res_150);
}

static void *builder_1(parser_t *p) {
    const frame_t f = {151, p->pos, FUNC};
    void *res_151;
    token_t *_name;
    void *_simple_args;
    ast_expr_t *_expr;
    res_151 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_simple_args = simple_args(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_151);
}

static void *builder_2(parser_t *p) {
    const frame_t f = {152, p->pos, FUNC};
    void *res_152;
    token_t *_name;
    void *_builder_hint;
    void *_builder_args;
    void *_block_suite;
    res_152 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_builder_hint = builder_hint(p), 1) &&
        (_builder_args = builder_args(p), 1) &&
        (_block_suite = block_suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_152);
}

// atom:
//     | tuple_atom
//     | list_atom
//     | builder
//     | NAME
//     | NUMBER
//     | STRING
//     | 'None'
//     | 'True'
//     | 'False'
static void *atom(parser_t *p) {
    const frame_t f = {153, p->pos, FUNC};
    void *res_153;
    void *alt_153;
    res_153 = enter_frame(p, &f) && (
        (alt_153 = tuple_atom(p)) ||
        (alt_153 = list_atom(p)) ||
        (alt_153 = builder(p)) ||
        (alt_153 = consume(p, 3, "NAME")) ||
        (alt_153 = consume(p, 4, "NUMBER")) ||
        (alt_153 = consume(p, 5, "STRING")) ||
        (alt_153 = consume(p, 81, "None")) ||
        (alt_153 = consume(p, 82, "True")) ||
        (alt_153 = consume(p, 83, "False"))
    ) ? alt_153 : 0;
    return exit_frame(p, &f, res_153);
}
