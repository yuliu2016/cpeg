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
    void *a;
    void *_single_input;
    _single_input = enter_frame(p, &f) && (
        (a = consume(p, 2, "NEWLINE")) ||
        (a = consume(p, 1, "ENDMARKER")) ||
        (a = simple_stmt(p)) ||
        (a = single_input_4(p))
    ) ? a : 0;
    return exit_frame(p, &f, _single_input);
}

static void *single_input_4(parser_t *p) {
    frame_t f = {2, p->pos, FUNC, 0, 0};
    void *a;
    token_t *b;
    void *_single_input_4;
    _single_input_4 = enter_frame(p, &f) && (
        (a = compound_stmt(p)) &&
        (b = consume(p, 2, "NEWLINE"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _single_input_4);
}

// file_input:
//     | [stmt_list] ENDMARKER
static void *file_input(parser_t *p) {
    frame_t f = {3, p->pos, FUNC, 0, 0};
    void *a;
    token_t *b;
    void *_file_input;
    _file_input = enter_frame(p, &f) && (
        (a = stmt_list(p), 1) &&
        (b = consume(p, 1, "ENDMARKER"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _file_input);
}

// eval_input:
//     | exprlist NEWLINE* ENDMARKER
static void *eval_input(parser_t *p) {
    frame_t f = {4, p->pos, FUNC, 0, 0};
    void *a;
    ast_list_t *b;
    token_t *c;
    void *_eval_input;
    _eval_input = enter_frame(p, &f) && (
        (a = exprlist(p)) &&
        (b = eval_input_loop(p)) &&
        (c = consume(p, 1, "ENDMARKER"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _eval_input);
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
    ast_list_t *a;
    void *_stmt_list;
    _stmt_list = enter_frame(p, &f) && (
        (a = stmt_loop(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _stmt_list);
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
    void *a;
    token_t *b;
    void *_stmt;
    _stmt = enter_frame(p, &f) && (
        (a = stmt_1(p)) &&
        (b = consume(p, 2, "NEWLINE"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _stmt);
}

static void *stmt_1(parser_t *p) {
    frame_t f = {7, p->pos, FUNC, 0, 0};
    void *a;
    void *_stmt_1;
    _stmt_1 = enter_frame(p, &f) && (
        (a = simple_stmt(p)) ||
        (a = compound_stmt(p))
    ) ? a : 0;
    return exit_frame(p, &f, _stmt_1);
}

// simple_stmt:
//     | ';'.small_stmt+ [';']
static void *simple_stmt(parser_t *p) {
    frame_t f = {8, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    token_t *b;
    void *_simple_stmt;
    _simple_stmt = enter_frame(p, &f) && (
        (a = small_stmt_delimited(p)) &&
        (b = consume(p, 12, ";"), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _simple_stmt);
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
    void *a;
    void *_small_stmt;
    _small_stmt = enter_frame(p, &f) && (
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
    return exit_frame(p, &f, _small_stmt);
}

// del_stmt:
//     | 'del' targetlist
static void *del_stmt(parser_t *p) {
    frame_t f = {10, p->pos, FUNC, 0, 0};
    void *a;
    void *_del_stmt;
    _del_stmt = enter_frame(p, &f) && (
        (consume(p, 79, "del")) &&
        (a = targetlist(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _del_stmt);
}

// return_stmt:
//     | 'return' [exprlist_star]
static void *return_stmt(parser_t *p) {
    frame_t f = {11, p->pos, FUNC, 0, 0};
    void *a;
    void *_return_stmt;
    _return_stmt = enter_frame(p, &f) && (
        (consume(p, 54, "return")) &&
        (a = exprlist_star(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _return_stmt);
}

// raise_stmt:
//     | 'raise' expr ['from' expr]
static void *raise_stmt(parser_t *p) {
    frame_t f = {12, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_raise_stmt;
    _raise_stmt = enter_frame(p, &f) && (
        (consume(p, 78, "raise")) &&
        (a = expr(p)) &&
        (b = raise_stmt_3(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _raise_stmt);
}

static void *raise_stmt_3(parser_t *p) {
    frame_t f = {13, p->pos, FUNC, 0, 0};
    void *a;
    void *_raise_stmt_3;
    _raise_stmt_3 = enter_frame(p, &f) && (
        (consume(p, 66, "from")) &&
        (a = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _raise_stmt_3);
}

// nonlocal_stmt:
//     | 'nonlocal' name_list
static void *nonlocal_stmt(parser_t *p) {
    frame_t f = {14, p->pos, FUNC, 0, 0};
    void *a;
    void *_nonlocal_stmt;
    _nonlocal_stmt = enter_frame(p, &f) && (
        (consume(p, 55, "nonlocal")) &&
        (a = name_list(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _nonlocal_stmt);
}

// assert_stmt:
//     | 'assert' expr [',' expr]
static void *assert_stmt(parser_t *p) {
    frame_t f = {15, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_assert_stmt;
    _assert_stmt = enter_frame(p, &f) && (
        (consume(p, 80, "assert")) &&
        (a = expr(p)) &&
        (b = assert_stmt_3(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _assert_stmt);
}

static void *assert_stmt_3(parser_t *p) {
    frame_t f = {16, p->pos, FUNC, 0, 0};
    void *a;
    void *_assert_stmt_3;
    _assert_stmt_3 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (a = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _assert_stmt_3);
}

// name_list:
//     | ','.NAME+
static void *name_list(parser_t *p) {
    frame_t f = {17, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    void *_name_list;
    _name_list = enter_frame(p, &f) && (
        (a = name_list_delimited(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _name_list);
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
    void *a;
    void *_star_expr;
    _star_expr = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (a = bitwise_or(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _star_expr);
}

// exprlist:
//     | ','.expr+ [',']
static void *exprlist(parser_t *p) {
    frame_t f = {19, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    token_t *b;
    void *_exprlist;
    _exprlist = enter_frame(p, &f) && (
        (a = expr_delimited(p)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _exprlist);
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
    void *a;
    void *_target;
    _target = enter_frame(p, &f) && (
        (a = target_1(p)) ||
        (a = target_2(p)) ||
        (a = consume(p, 3, "NAME")) ||
        (a = target_4(p))
    ) ? a : 0;
    return exit_frame(p, &f, _target);
}

static void *target_1(parser_t *p) {
    frame_t f = {21, p->pos, FUNC, 0, 0};
    void *a;
    token_t *b;
    void *_target_1;
    _target_1 = enter_frame(p, &f) && (
        (a = t_primary(p)) &&
        (consume(p, 6, ".")) &&
        (b = consume(p, 3, "NAME")) &&
        (!test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _target_1);
}

static void *target_2(parser_t *p) {
    frame_t f = {22, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_target_2;
    _target_2 = enter_frame(p, &f) && (
        (a = t_primary(p)) &&
        (b = subscript(p)) &&
        (!test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _target_2);
}

static void *target_4(parser_t *p) {
    frame_t f = {23, p->pos, FUNC, 0, 0};
    void *a;
    void *_target_4;
    _target_4 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = targetlist_sp(p)) &&
        (consume(p, 14, ")"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _target_4);
}

// targetlist_sp (allow_whitespace=true):
//     | targetlist
static void *targetlist_sp(parser_t *p) {
    frame_t f = {24, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    void *a;
    void *_targetlist_sp;
    _targetlist_sp = enter_frame(p, &f) && (
        (a = targetlist(p))
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, _targetlist_sp);
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
    void *_t_primary = 0;
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
    _t_primary = max;
    return exit_frame(p, &f, _t_primary);
}

static void *t_primary_1(parser_t *p) {
    frame_t f = {26, p->pos, FUNC, 0, 0};
    void *a;
    token_t *b;
    void *_t_primary_1;
    _t_primary_1 = enter_frame(p, &f) && (
        (a = t_primary(p)) &&
        (consume(p, 6, ".")) &&
        (b = consume(p, 3, "NAME")) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _t_primary_1);
}

static void *t_primary_2(parser_t *p) {
    frame_t f = {27, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_t_primary_2;
    _t_primary_2 = enter_frame(p, &f) && (
        (a = t_primary(p)) &&
        (b = invocation(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _t_primary_2);
}

static void *t_primary_3(parser_t *p) {
    frame_t f = {28, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_t_primary_3;
    _t_primary_3 = enter_frame(p, &f) && (
        (a = t_primary(p)) &&
        (b = subscript(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _t_primary_3);
}

static void *t_primary_4(parser_t *p) {
    frame_t f = {29, p->pos, FUNC, 0, 0};
    void *a;
    void *_t_primary_4;
    _t_primary_4 = enter_frame(p, &f) && (
        (a = atom(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _t_primary_4);
}

// t_lookahead:
//     | '.'
//     | '('
//     | '['
static void *t_lookahead(parser_t *p) {
    frame_t f = {30, p->pos, FUNC, 0, 0};
    void *a;
    void *_t_lookahead;
    _t_lookahead = enter_frame(p, &f) && (
        (a = consume(p, 6, ".")) ||
        (a = consume(p, 13, "(")) ||
        (a = consume(p, 17, "["))
    ) ? a : 0;
    return exit_frame(p, &f, _t_lookahead);
}

// targetlist:
//     | ','.target+ [',']
static void *targetlist(parser_t *p) {
    frame_t f = {31, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    token_t *b;
    void *_targetlist;
    _targetlist = enter_frame(p, &f) && (
        (a = target_delimited(p)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _targetlist);
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
    void *a;
    void *_expr_or_star;
    _expr_or_star = enter_frame(p, &f) && (
        (a = star_expr(p)) ||
        (a = expr(p))
    ) ? a : 0;
    return exit_frame(p, &f, _expr_or_star);
}

// exprlist_star:
//     | ','.expr_or_star+ [',']
static void *exprlist_star(parser_t *p) {
    frame_t f = {33, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    token_t *b;
    void *_exprlist_star;
    _exprlist_star = enter_frame(p, &f) && (
        (a = expr_or_star_delimited(p)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _exprlist_star);
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
    void *a;
    void *_subscript;
    _subscript = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (a = slicelist(p)) &&
        (consume(p, 18, "]"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _subscript);
}

// slicelist:
//     | ','.slice+ [',']
static void *slicelist(parser_t *p) {
    frame_t f = {35, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    token_t *b;
    void *_slicelist;
    _slicelist = enter_frame(p, &f) && (
        (a = slice_delimited(p)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _slicelist);
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
    void *a;
    void *_slice;
    _slice = enter_frame(p, &f) && (
        (a = slice_1(p)) ||
        (a = expr(p))
    ) ? a : 0;
    return exit_frame(p, &f, _slice);
}

static void *slice_1(parser_t *p) {
    frame_t f = {37, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *c;
    void *_slice_1;
    _slice_1 = enter_frame(p, &f) && (
        (a = expr(p), 1) &&
        (b = slice_expr(p)) &&
        (c = slice_expr(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _slice_1);
}

// slice_expr:
//     | ':' [expr]
static void *slice_expr(parser_t *p) {
    frame_t f = {38, p->pos, FUNC, 0, 0};
    void *a;
    void *_slice_expr;
    _slice_expr = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (a = expr(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _slice_expr);
}

// dict_item:
//     | expr ':' expr
//     | '**' bitwise_or
static void *dict_item(parser_t *p) {
    frame_t f = {39, p->pos, FUNC, 0, 0};
    void *a;
    void *_dict_item;
    _dict_item = enter_frame(p, &f) && (
        (a = dict_item_1(p)) ||
        (a = dict_item_2(p))
    ) ? a : 0;
    return exit_frame(p, &f, _dict_item);
}

static void *dict_item_1(parser_t *p) {
    frame_t f = {40, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_dict_item_1;
    _dict_item_1 = enter_frame(p, &f) && (
        (a = expr(p)) &&
        (consume(p, 9, ":")) &&
        (b = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _dict_item_1);
}

static void *dict_item_2(parser_t *p) {
    frame_t f = {41, p->pos, FUNC, 0, 0};
    void *a;
    void *_dict_item_2;
    _dict_item_2 = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (a = bitwise_or(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _dict_item_2);
}

// dict_items (allow_whitespace=true):
//     | ','.dict_item+ [',']
static void *dict_items(parser_t *p) {
    frame_t f = {42, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    ast_list_t *a;
    token_t *b;
    void *_dict_items;
    _dict_items = enter_frame(p, &f) && (
        (a = dict_item_delimited(p)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, _dict_items);
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
    void *a;
    void *_list_item;
    _list_item = enter_frame(p, &f) && (
        (a = star_expr(p)) ||
        (a = named_expr(p))
    ) ? a : 0;
    return exit_frame(p, &f, _list_item);
}

// list_items (allow_whitespace=true):
//     | ','.list_item+ [',']
static void *list_items(parser_t *p) {
    frame_t f = {44, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    ast_list_t *a;
    token_t *b;
    void *_list_items;
    _list_items = enter_frame(p, &f) && (
        (a = list_item_delimited(p)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, _list_items);
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
    void *a;
    void *_set_items;
    _set_items = enter_frame(p, &f) && (
        (a = exprlist_star(p))
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, _set_items);
}

// as_name:
//     | 'as' NAME
static void *as_name(parser_t *p) {
    frame_t f = {46, p->pos, FUNC, 0, 0};
    token_t *a;
    void *_as_name;
    _as_name = enter_frame(p, &f) && (
        (consume(p, 65, "as")) &&
        (a = consume(p, 3, "NAME"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _as_name);
}

// iter_for:
//     | 'for' targetlist 'in' disjunction [iter_if]
static void *iter_for(parser_t *p) {
    frame_t f = {47, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *c;
    void *_iter_for;
    _iter_for = enter_frame(p, &f) && (
        (consume(p, 72, "for")) &&
        (a = targetlist(p)) &&
        (consume(p, 63, "in")) &&
        (b = disjunction(p)) &&
        (c = iter_if(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _iter_for);
}

// iter_if:
//     | 'if' named_expr
static void *iter_if(parser_t *p) {
    frame_t f = {48, p->pos, FUNC, 0, 0};
    void *a;
    void *_iter_if;
    _iter_if = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (a = named_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _iter_if);
}

// iterator:
//     | iter_for* 'for' targetlist [iter_if]
static void *iterator(parser_t *p) {
    frame_t f = {49, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    void *b;
    void *c;
    void *_iterator;
    _iterator = enter_frame(p, &f) && (
        (a = iter_for_loop(p)) &&
        (consume(p, 72, "for")) &&
        (b = targetlist(p)) &&
        (c = iter_if(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _iterator);
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
    void *a;
    void *b;
    void *_list_iterator;
    _list_iterator = enter_frame(p, &f) && (
        (a = expr_or_star(p)) &&
        (b = iterator(p))
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, _list_iterator);
}

// dict_iterator (allow_whitespace=true):
//     | dict_item iterator
static void *dict_iterator(parser_t *p) {
    frame_t f = {51, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    void *a;
    void *b;
    void *_dict_iterator;
    _dict_iterator = enter_frame(p, &f) && (
        (a = dict_item(p)) &&
        (b = iterator(p))
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, _dict_iterator);
}

// assignment:
//     | pubassign
//     | annassign
//     | augassign
//     | simple_assign
static void *assignment(parser_t *p) {
    frame_t f = {52, p->pos, FUNC, 0, 0};
    void *a;
    void *_assignment;
    _assignment = enter_frame(p, &f) && (
        (a = pubassign(p)) ||
        (a = annassign(p)) ||
        (a = augassign(p)) ||
        (a = simple_assign(p))
    ) ? a : 0;
    return exit_frame(p, &f, _assignment);
}

// pubassign:
//     | '/' NAME '=' exprlist
static void *pubassign(parser_t *p) {
    frame_t f = {53, p->pos, FUNC, 0, 0};
    token_t *a;
    void *b;
    void *_pubassign;
    _pubassign = enter_frame(p, &f) && (
        (consume(p, 24, "/")) &&
        (a = consume(p, 3, "NAME")) &&
        (consume(p, 8, "=")) &&
        (b = exprlist(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _pubassign);
}

// annassign:
//     | target ':' expr ['=' exprlist]
static void *annassign(parser_t *p) {
    frame_t f = {54, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *c;
    void *_annassign;
    _annassign = enter_frame(p, &f) && (
        (a = target(p)) &&
        (consume(p, 9, ":")) &&
        (b = expr(p)) &&
        (c = annassign_4(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _annassign);
}

static void *annassign_4(parser_t *p) {
    frame_t f = {55, p->pos, FUNC, 0, 0};
    void *a;
    void *_annassign_4;
    _annassign_4 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (a = exprlist(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _annassign_4);
}

// augassign:
//     | target augassign_op exprlist
static void *augassign(parser_t *p) {
    frame_t f = {56, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *c;
    void *_augassign;
    _augassign = enter_frame(p, &f) && (
        (a = target(p)) &&
        (b = augassign_op(p)) &&
        (c = exprlist(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _augassign);
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
static void *simple_assign(parser_t *p) {
    frame_t f = {57, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    void *b;
    void *_simple_assign;
    _simple_assign = enter_frame(p, &f) && (
        (a = simple_assign_1_loop(p)) &&
        (b = exprlist_star(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _simple_assign);
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
    void *a;
    void *_simple_assign_1;
    _simple_assign_1 = enter_frame(p, &f) && (
        (a = targetlist(p)) &&
        (consume(p, 8, "="))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _simple_assign_1);
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
    void *a;
    void *_augassign_op;
    _augassign_op = enter_frame(p, &f) && (
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
    return exit_frame(p, &f, _augassign_op);
}

// import_name:
//     | 'import' dotted_as_names
static void *import_name(parser_t *p) {
    frame_t f = {60, p->pos, FUNC, 0, 0};
    void *a;
    void *_import_name;
    _import_name = enter_frame(p, &f) && (
        (consume(p, 67, "import")) &&
        (a = dotted_as_names(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _import_name);
}

// import_from:
//     | 'from' import_from_names 'import' import_from_items
static void *import_from(parser_t *p) {
    frame_t f = {61, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_import_from;
    _import_from = enter_frame(p, &f) && (
        (consume(p, 66, "from")) &&
        (a = import_from_names(p)) &&
        (consume(p, 67, "import")) &&
        (b = import_from_items(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _import_from);
}

// import_from_names:
//     | dotted_name
//     | '.'+ [dotted_name]
static void *import_from_names(parser_t *p) {
    frame_t f = {62, p->pos, FUNC, 0, 0};
    void *a;
    void *_import_from_names;
    _import_from_names = enter_frame(p, &f) && (
        (a = dotted_name(p)) ||
        (a = import_from_names_2(p))
    ) ? a : 0;
    return exit_frame(p, &f, _import_from_names);
}

static void *import_from_names_2(parser_t *p) {
    frame_t f = {63, p->pos, FUNC, 0, 0};
    void *a;
    void *_import_from_names_2;
    _import_from_names_2 = enter_frame(p, &f) && (
        (import_from_names_2_loop(p)) &&
        (a = dotted_name(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _import_from_names_2);
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
    void *a;
    void *_import_from_items;
    _import_from_items = enter_frame(p, &f) && (
        (a = consume(p, 23, "*")) ||
        (a = import_as_names_sp(p)) ||
        (a = import_as_names(p))
    ) ? a : 0;
    return exit_frame(p, &f, _import_from_items);
}

// import_as_names_sp (allow_whitespace=true):
//     | '(' import_as_names [','] ')'
static void *import_as_names_sp(parser_t *p) {
    frame_t f = {65, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    void *a;
    token_t *b;
    void *_import_as_names_sp;
    _import_as_names_sp = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = import_as_names(p)) &&
        (b = consume(p, 7, ","), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, _import_as_names_sp);
}

// import_as_name:
//     | NAME [as_name]
static void *import_as_name(parser_t *p) {
    frame_t f = {66, p->pos, FUNC, 0, 0};
    token_t *a;
    void *b;
    void *_import_as_name;
    _import_as_name = enter_frame(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (b = as_name(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _import_as_name);
}

// dotted_as_name:
//     | dotted_name [as_name]
static void *dotted_as_name(parser_t *p) {
    frame_t f = {67, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_dotted_as_name;
    _dotted_as_name = enter_frame(p, &f) && (
        (a = dotted_name(p)) &&
        (b = as_name(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _dotted_as_name);
}

// import_as_names:
//     | ','.import_as_name+
static void *import_as_names(parser_t *p) {
    frame_t f = {68, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    void *_import_as_names;
    _import_as_names = enter_frame(p, &f) && (
        (a = import_as_name_delimited(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _import_as_names);
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
    ast_list_t *a;
    void *_dotted_as_names;
    _dotted_as_names = enter_frame(p, &f) && (
        (a = dotted_as_name_delimited(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _dotted_as_names);
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
    ast_list_t *a;
    void *_dotted_name;
    _dotted_name = enter_frame(p, &f) && (
        (a = dotted_name_delimited(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _dotted_name);
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
    void *a;
    void *_compound_stmt;
    _compound_stmt = enter_frame(p, &f) && (
        (a = if_stmt(p)) ||
        (a = while_stmt(p)) ||
        (a = for_stmt(p)) ||
        (a = try_stmt(p)) ||
        (a = with_stmt(p))
    ) ? a : 0;
    return exit_frame(p, &f, _compound_stmt);
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
static void *if_stmt(parser_t *p) {
    frame_t f = {72, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    ast_list_t *c;
    void *d;
    void *_if_stmt;
    _if_stmt = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (a = named_expr(p)) &&
        (b = suite(p)) &&
        (c = elif_stmt_loop(p)) &&
        (d = else_suite(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _if_stmt);
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
    void *a;
    void *b;
    void *_elif_stmt;
    _elif_stmt = enter_frame(p, &f) && (
        (consume(p, 57, "elif")) &&
        (a = named_expr(p)) &&
        (b = suite(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _elif_stmt);
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
static void *while_stmt(parser_t *p) {
    frame_t f = {74, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *c;
    void *_while_stmt;
    _while_stmt = enter_frame(p, &f) && (
        (consume(p, 71, "while")) &&
        (a = named_expr(p)) &&
        (b = suite(p)) &&
        (c = else_suite(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _while_stmt);
}

// for_stmt:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
static void *for_stmt(parser_t *p) {
    frame_t f = {75, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *c;
    void *d;
    void *_for_stmt;
    _for_stmt = enter_frame(p, &f) && (
        (consume(p, 72, "for")) &&
        (a = targetlist(p)) &&
        (consume(p, 63, "in")) &&
        (b = exprlist(p)) &&
        (c = suite(p)) &&
        (d = else_suite(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _for_stmt);
}

// try_stmt:
//     | 'try' suite (except_suite | finally_suite)
static void *try_stmt(parser_t *p) {
    frame_t f = {76, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_try_stmt;
    _try_stmt = enter_frame(p, &f) && (
        (consume(p, 75, "try")) &&
        (a = suite(p)) &&
        (b = try_stmt_3(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _try_stmt);
}

static void *try_stmt_3(parser_t *p) {
    frame_t f = {77, p->pos, FUNC, 0, 0};
    void *a;
    void *_try_stmt_3;
    _try_stmt_3 = enter_frame(p, &f) && (
        (a = except_suite(p)) ||
        (a = finally_suite(p))
    ) ? a : 0;
    return exit_frame(p, &f, _try_stmt_3);
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
static void *with_stmt(parser_t *p) {
    frame_t f = {78, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    void *b;
    void *_with_stmt;
    _with_stmt = enter_frame(p, &f) && (
        (consume(p, 68, "with")) &&
        (a = expr_as_name_delimited(p)) &&
        (b = suite(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _with_stmt);
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
    void *a;
    void *b;
    void *_expr_as_name;
    _expr_as_name = enter_frame(p, &f) && (
        (a = expr(p)) &&
        (b = as_name(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _expr_as_name);
}

// block_suite (allow_whitespace=false):
//     | '{' NEWLINE stmt_list '}'
//     | '{' [simple_stmt] '}'
static void *block_suite(parser_t *p) {
    frame_t f = {80, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace=0;
    void *a;
    void *_block_suite;
    _block_suite = enter_frame(p, &f) && (
        (a = block_suite_1(p)) ||
        (a = block_suite_2(p))
    ) ? a : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, _block_suite);
}

static void *block_suite_1(parser_t *p) {
    frame_t f = {81, p->pos, FUNC, 0, 0};
    token_t *a;
    void *b;
    void *_block_suite_1;
    _block_suite_1 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (a = consume(p, 2, "NEWLINE")) &&
        (b = stmt_list(p)) &&
        (consume(p, 16, "}"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _block_suite_1);
}

static void *block_suite_2(parser_t *p) {
    frame_t f = {82, p->pos, FUNC, 0, 0};
    void *a;
    void *_block_suite_2;
    _block_suite_2 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (a = simple_stmt(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _block_suite_2);
}

// suite:
//     | ':' simple_stmt
//     | block_suite
static void *suite(parser_t *p) {
    frame_t f = {83, p->pos, FUNC, 0, 0};
    void *a;
    void *_suite;
    _suite = enter_frame(p, &f) && (
        (a = suite_1(p)) ||
        (a = block_suite(p))
    ) ? a : 0;
    return exit_frame(p, &f, _suite);
}

static void *suite_1(parser_t *p) {
    frame_t f = {84, p->pos, FUNC, 0, 0};
    void *a;
    void *_suite_1;
    _suite_1 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (a = simple_stmt(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _suite_1);
}

// else_suite:
//     | 'else' suite
static void *else_suite(parser_t *p) {
    frame_t f = {85, p->pos, FUNC, 0, 0};
    void *a;
    void *_else_suite;
    _else_suite = enter_frame(p, &f) && (
        (consume(p, 58, "else")) &&
        (a = suite(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _else_suite);
}

// finally_suite:
//     | 'finally' suite
static void *finally_suite(parser_t *p) {
    frame_t f = {86, p->pos, FUNC, 0, 0};
    void *a;
    void *_finally_suite;
    _finally_suite = enter_frame(p, &f) && (
        (consume(p, 77, "finally")) &&
        (a = suite(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _finally_suite);
}

// except_clause:
//     | 'except' [expr_as_name] suite
static void *except_clause(parser_t *p) {
    frame_t f = {87, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_except_clause;
    _except_clause = enter_frame(p, &f) && (
        (consume(p, 76, "except")) &&
        (a = expr_as_name(p), 1) &&
        (b = suite(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _except_clause);
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
static void *except_suite(parser_t *p) {
    frame_t f = {88, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    void *b;
    void *c;
    void *_except_suite;
    _except_suite = enter_frame(p, &f) && (
        (a = except_clause_loop(p)) &&
        (b = else_suite(p), 1) &&
        (c = finally_suite(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _except_suite);
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
    void *a;
    void *_invocation;
    _invocation = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = call_arg_list(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _invocation);
}

// call_arg_list (allow_whitespace=true):
//     | ','.call_arg+ [',']
static void *call_arg_list(parser_t *p) {
    frame_t f = {90, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    ast_list_t *a;
    token_t *b;
    void *_call_arg_list;
    _call_arg_list = enter_frame(p, &f) && (
        (a = call_arg_delimited(p)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, _call_arg_list);
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
    void *a;
    void *_call_arg;
    _call_arg = enter_frame(p, &f) && (
        (a = call_arg_1(p)) ||
        (a = call_arg_2(p)) ||
        (a = call_arg_3(p)) ||
        (a = call_arg_4(p)) ||
        (a = expr(p))
    ) ? a : 0;
    return exit_frame(p, &f, _call_arg);
}

static void *call_arg_1(parser_t *p) {
    frame_t f = {92, p->pos, FUNC, 0, 0};
    token_t *a;
    void *b;
    void *_call_arg_1;
    _call_arg_1 = enter_frame(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (b = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _call_arg_1);
}

static void *call_arg_2(parser_t *p) {
    frame_t f = {93, p->pos, FUNC, 0, 0};
    token_t *a;
    void *b;
    void *_call_arg_2;
    _call_arg_2 = enter_frame(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (consume(p, 8, "=")) &&
        (b = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _call_arg_2);
}

static void *call_arg_3(parser_t *p) {
    frame_t f = {94, p->pos, FUNC, 0, 0};
    void *a;
    void *_call_arg_3;
    _call_arg_3 = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (a = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _call_arg_3);
}

static void *call_arg_4(parser_t *p) {
    frame_t f = {95, p->pos, FUNC, 0, 0};
    void *a;
    void *_call_arg_4;
    _call_arg_4 = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (a = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _call_arg_4);
}

// typed_arg_list (allow_whitespace=true):
//     | kwargs
//     | args_kwargs
//     | full_arg_list
static void *typed_arg_list(parser_t *p) {
    frame_t f = {96, p->pos, FUNC, 0, 0};
    int ws = p->ignore_whitespace;
    p->ignore_whitespace = 1;
    void *a;
    void *_typed_arg_list;
    _typed_arg_list = enter_frame(p, &f) && (
        (a = kwargs(p)) ||
        (a = args_kwargs(p)) ||
        (a = full_arg_list(p))
    ) ? a : 0;
    p->ignore_whitespace = ws;
    return exit_frame(p, &f, _typed_arg_list);
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
static void *full_arg_list(parser_t *p) {
    frame_t f = {97, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    void *b;
    void *_full_arg_list;
    _full_arg_list = enter_frame(p, &f) && (
        (a = default_arg_delimited(p)) &&
        (b = full_arg_list_2(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _full_arg_list);
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
    void *a;
    void *_full_arg_list_2;
    _full_arg_list_2 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (a = full_arg_list_2_2(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _full_arg_list_2);
}

static void *full_arg_list_2_2(parser_t *p) {
    frame_t f = {99, p->pos, FUNC, 0, 0};
    void *a;
    void *_full_arg_list_2_2;
    _full_arg_list_2_2 = enter_frame(p, &f) && (
        (a = kwargs(p)) ||
        (a = args_kwargs(p))
    ) ? a : 0;
    return exit_frame(p, &f, _full_arg_list_2_2);
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
static void *args_kwargs(parser_t *p) {
    frame_t f = {100, p->pos, FUNC, 0, 0};
    void *a;
    ast_list_t *b;
    void *c;
    void *_args_kwargs;
    _args_kwargs = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (a = typed_arg(p), 1) &&
        (b = args_kwargs_3_loop(p)) &&
        (c = args_kwargs_4(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _args_kwargs);
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
    void *a;
    void *_args_kwargs_3;
    _args_kwargs_3 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (a = default_arg(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _args_kwargs_3);
}

static void *args_kwargs_4(parser_t *p) {
    frame_t f = {102, p->pos, FUNC, 0, 0};
    void *a;
    void *_args_kwargs_4;
    _args_kwargs_4 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (a = kwargs(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _args_kwargs_4);
}

// kwargs:
//     | '**' typed_arg [',']
static void *kwargs(parser_t *p) {
    frame_t f = {103, p->pos, FUNC, 0, 0};
    void *a;
    token_t *b;
    void *_kwargs;
    _kwargs = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (a = typed_arg(p)) &&
        (b = consume(p, 7, ","), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _kwargs);
}

// default_arg:
//     | typed_arg ['=' expr]
static void *default_arg(parser_t *p) {
    frame_t f = {104, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_default_arg;
    _default_arg = enter_frame(p, &f) && (
        (a = typed_arg(p)) &&
        (b = default_arg_2(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _default_arg);
}

static void *default_arg_2(parser_t *p) {
    frame_t f = {105, p->pos, FUNC, 0, 0};
    void *a;
    void *_default_arg_2;
    _default_arg_2 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (a = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _default_arg_2);
}

// typed_arg:
//     | NAME [':' expr]
static void *typed_arg(parser_t *p) {
    frame_t f = {106, p->pos, FUNC, 0, 0};
    token_t *a;
    void *b;
    void *_typed_arg;
    _typed_arg = enter_frame(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (b = typed_arg_2(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _typed_arg);
}

static void *typed_arg_2(parser_t *p) {
    frame_t f = {107, p->pos, FUNC, 0, 0};
    void *a;
    void *_typed_arg_2;
    _typed_arg_2 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (a = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _typed_arg_2);
}

// simple_arg:
//     | NAME ['=' expr]
static void *simple_arg(parser_t *p) {
    frame_t f = {108, p->pos, FUNC, 0, 0};
    token_t *a;
    void *b;
    void *_simple_arg;
    _simple_arg = enter_frame(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (b = simple_arg_2(p), 1)
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _simple_arg);
}

static void *simple_arg_2(parser_t *p) {
    frame_t f = {109, p->pos, FUNC, 0, 0};
    void *a;
    void *_simple_arg_2;
    _simple_arg_2 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (a = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _simple_arg_2);
}

// simple_args:
//     | ','.simple_arg+
static void *simple_args(parser_t *p) {
    frame_t f = {110, p->pos, FUNC, 0, 0};
    ast_list_t *a;
    void *_simple_args;
    _simple_args = enter_frame(p, &f) && (
        (a = simple_arg_delimited(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _simple_args);
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
    void *a;
    void *_builder_hint;
    _builder_hint = enter_frame(p, &f) && (
        (consume(p, 19, "<")) &&
        (a = name_list(p)) &&
        (consume(p, 20, ">"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _builder_hint);
}

// builder_args:
//     | simple_args
//     | '(' [typed_arg_list] ')'
static void *builder_args(parser_t *p) {
    frame_t f = {112, p->pos, FUNC, 0, 0};
    void *a;
    void *_builder_args;
    _builder_args = enter_frame(p, &f) && (
        (a = simple_args(p)) ||
        (a = builder_args_2(p))
    ) ? a : 0;
    return exit_frame(p, &f, _builder_args);
}

static void *builder_args_2(parser_t *p) {
    frame_t f = {113, p->pos, FUNC, 0, 0};
    void *a;
    void *_builder_args_2;
    _builder_args_2 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = typed_arg_list(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _builder_args_2);
}

// named_expr:
//     | NAME ':=' expr
//     | expr
static void *named_expr(parser_t *p) {
    frame_t f = {114, p->pos, FUNC, 0, 0};
    void *a;
    void *_named_expr;
    _named_expr = enter_frame(p, &f) && (
        (a = named_expr_1(p)) ||
        (a = expr(p))
    ) ? a : 0;
    return exit_frame(p, &f, _named_expr);
}

static void *named_expr_1(parser_t *p) {
    frame_t f = {115, p->pos, FUNC, 0, 0};
    token_t *a;
    void *b;
    void *_named_expr_1;
    _named_expr_1 = enter_frame(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (b = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _named_expr_1);
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
static void *conditional(parser_t *p) {
    frame_t f = {116, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *c;
    void *_conditional;
    _conditional = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (a = disjunction(p)) &&
        (consume(p, 10, "?")) &&
        (b = disjunction(p)) &&
        (consume(p, 9, ":")) &&
        (c = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _conditional);
}

// expr:
//     | conditional
//     | disjunction
static void *expr(parser_t *p) {
    frame_t f = {117, p->pos, FUNC, 0, 0};
    void *a;
    void *_expr;
    _expr = enter_frame(p, &f) && (
        (a = conditional(p)) ||
        (a = disjunction(p))
    ) ? a : 0;
    return exit_frame(p, &f, _expr);
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
    void *_disjunction = 0;
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
    _disjunction = max;
    return exit_frame(p, &f, _disjunction);
}

static void *disjunction_1(parser_t *p) {
    frame_t f = {119, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_disjunction_1;
    _disjunction_1 = enter_frame(p, &f) && (
        (a = disjunction(p)) &&
        (consume(p, 60, "or")) &&
        (b = conjunction(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _disjunction_1);
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
    void *_conjunction = 0;
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
    _conjunction = max;
    return exit_frame(p, &f, _conjunction);
}

static void *conjunction_1(parser_t *p) {
    frame_t f = {121, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_conjunction_1;
    _conjunction_1 = enter_frame(p, &f) && (
        (a = conjunction(p)) &&
        (consume(p, 59, "and")) &&
        (b = inversion(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _conjunction_1);
}

// inversion:
//     | 'not' inversion
//     | comparison
static void *inversion(parser_t *p) {
    frame_t f = {122, p->pos, FUNC, 0, 0};
    void *a;
    void *_inversion;
    _inversion = enter_frame(p, &f) && (
        (a = inversion_1(p)) ||
        (a = comparison(p))
    ) ? a : 0;
    return exit_frame(p, &f, _inversion);
}

static void *inversion_1(parser_t *p) {
    frame_t f = {123, p->pos, FUNC, 0, 0};
    void *a;
    void *_inversion_1;
    _inversion_1 = enter_frame(p, &f) && (
        (consume(p, 61, "not")) &&
        (a = inversion(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _inversion_1);
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
static void *comparison(parser_t *p) {
    frame_t f = {124, p->pos, FUNC, 0, 0};
    void *a;
    void *_comparison;
    _comparison = enter_frame(p, &f) && (
        (a = comparison_1(p)) ||
        (a = bitwise_or(p))
    ) ? a : 0;
    return exit_frame(p, &f, _comparison);
}

static void *comparison_1(parser_t *p) {
    frame_t f = {125, p->pos, FUNC, 0, 0};
    void *a;
    ast_list_t *b;
    void *_comparison_1;
    _comparison_1 = enter_frame(p, &f) && (
        (a = bitwise_or(p)) &&
        (b = comparison_1_2_loop(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _comparison_1);
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
    void *a;
    void *b;
    void *_comparison_1_2;
    _comparison_1_2 = enter_frame(p, &f) && (
        (a = comp_op(p)) &&
        (b = bitwise_or(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _comparison_1_2);
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
    void *a;
    void *_comp_op;
    _comp_op = enter_frame(p, &f) && (
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
    return exit_frame(p, &f, _comp_op);
}

static void *comp_op_8(parser_t *p) {
    frame_t f = {128, p->pos, FUNC, 0, 0};
    void *_comp_op_8;
    _comp_op_8 = enter_frame(p, &f) && (
        (consume(p, 61, "not")) &&
        (consume(p, 63, "in"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _comp_op_8);
}

static void *comp_op_10(parser_t *p) {
    frame_t f = {129, p->pos, FUNC, 0, 0};
    void *_comp_op_10;
    _comp_op_10 = enter_frame(p, &f) && (
        (consume(p, 62, "is")) &&
        (consume(p, 61, "not"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _comp_op_10);
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
    void *_bitwise_or = 0;
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
    _bitwise_or = max;
    return exit_frame(p, &f, _bitwise_or);
}

static void *bitwise_or_1(parser_t *p) {
    frame_t f = {131, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_bitwise_or_1;
    _bitwise_or_1 = enter_frame(p, &f) && (
        (a = bitwise_or(p)) &&
        (consume(p, 27, "|")) &&
        (b = bitwise_xor(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _bitwise_or_1);
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
    void *_bitwise_xor = 0;
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
    _bitwise_xor = max;
    return exit_frame(p, &f, _bitwise_xor);
}

static void *bitwise_xor_1(parser_t *p) {
    frame_t f = {133, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_bitwise_xor_1;
    _bitwise_xor_1 = enter_frame(p, &f) && (
        (a = bitwise_xor(p)) &&
        (consume(p, 30, "^")) &&
        (b = bitwise_and(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _bitwise_xor_1);
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
    void *_bitwise_and = 0;
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
    _bitwise_and = max;
    return exit_frame(p, &f, _bitwise_and);
}

static void *bitwise_and_1(parser_t *p) {
    frame_t f = {135, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_bitwise_and_1;
    _bitwise_and_1 = enter_frame(p, &f) && (
        (a = bitwise_and(p)) &&
        (consume(p, 28, "&")) &&
        (b = shift_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _bitwise_and_1);
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
    void *_shift_expr = 0;
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
    _shift_expr = max;
    return exit_frame(p, &f, _shift_expr);
}

static void *shift_expr_1(parser_t *p) {
    frame_t f = {137, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_shift_expr_1;
    _shift_expr_1 = enter_frame(p, &f) && (
        (a = shift_expr(p)) &&
        (consume(p, 48, "<<")) &&
        (b = sum(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _shift_expr_1);
}

static void *shift_expr_2(parser_t *p) {
    frame_t f = {138, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_shift_expr_2;
    _shift_expr_2 = enter_frame(p, &f) && (
        (a = shift_expr(p)) &&
        (consume(p, 49, ">>")) &&
        (b = sum(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _shift_expr_2);
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
    void *_sum = 0;
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
    _sum = max;
    return exit_frame(p, &f, _sum);
}

static void *sum_1(parser_t *p) {
    frame_t f = {140, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_sum_1;
    _sum_1 = enter_frame(p, &f) && (
        (a = sum(p)) &&
        (consume(p, 21, "+")) &&
        (b = term(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _sum_1);
}

static void *sum_2(parser_t *p) {
    frame_t f = {141, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_sum_2;
    _sum_2 = enter_frame(p, &f) && (
        (a = sum(p)) &&
        (consume(p, 22, "-")) &&
        (b = term(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _sum_2);
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
    void *_term = 0;
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
    _term = max;
    return exit_frame(p, &f, _term);
}

static void *term_1(parser_t *p) {
    frame_t f = {143, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_term_1;
    _term_1 = enter_frame(p, &f) && (
        (a = term(p)) &&
        (consume(p, 23, "*")) &&
        (b = pipe_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _term_1);
}

static void *term_2(parser_t *p) {
    frame_t f = {144, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_term_2;
    _term_2 = enter_frame(p, &f) && (
        (a = term(p)) &&
        (consume(p, 24, "/")) &&
        (b = pipe_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _term_2);
}

static void *term_3(parser_t *p) {
    frame_t f = {145, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_term_3;
    _term_3 = enter_frame(p, &f) && (
        (a = term(p)) &&
        (consume(p, 25, "%")) &&
        (b = pipe_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _term_3);
}

static void *term_4(parser_t *p) {
    frame_t f = {146, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_term_4;
    _term_4 = enter_frame(p, &f) && (
        (a = term(p)) &&
        (consume(p, 37, "//")) &&
        (b = pipe_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _term_4);
}

static void *term_5(parser_t *p) {
    frame_t f = {147, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_term_5;
    _term_5 = enter_frame(p, &f) && (
        (a = term(p)) &&
        (consume(p, 26, "@")) &&
        (b = pipe_expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _term_5);
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
    void *_pipe_expr = 0;
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
    _pipe_expr = max;
    return exit_frame(p, &f, _pipe_expr);
}

static void *pipe_expr_1(parser_t *p) {
    frame_t f = {149, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_pipe_expr_1;
    _pipe_expr_1 = enter_frame(p, &f) && (
        (a = pipe_expr(p)) &&
        (consume(p, 35, "->")) &&
        (b = factor(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _pipe_expr_1);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static void *factor(parser_t *p) {
    frame_t f = {150, p->pos, FUNC, 0, 0};
    void *a;
    void *_factor;
    _factor = enter_frame(p, &f) && (
        (a = factor_1(p)) ||
        (a = factor_2(p)) ||
        (a = factor_3(p)) ||
        (a = power(p))
    ) ? a : 0;
    return exit_frame(p, &f, _factor);
}

static void *factor_1(parser_t *p) {
    frame_t f = {151, p->pos, FUNC, 0, 0};
    void *a;
    void *_factor_1;
    _factor_1 = enter_frame(p, &f) && (
        (consume(p, 21, "+")) &&
        (a = factor(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _factor_1);
}

static void *factor_2(parser_t *p) {
    frame_t f = {152, p->pos, FUNC, 0, 0};
    void *a;
    void *_factor_2;
    _factor_2 = enter_frame(p, &f) && (
        (consume(p, 22, "-")) &&
        (a = factor(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _factor_2);
}

static void *factor_3(parser_t *p) {
    frame_t f = {153, p->pos, FUNC, 0, 0};
    void *a;
    void *_factor_3;
    _factor_3 = enter_frame(p, &f) && (
        (consume(p, 29, "~")) &&
        (a = factor(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _factor_3);
}

// power:
//     | primary '**' factor
//     | primary
static void *power(parser_t *p) {
    frame_t f = {154, p->pos, FUNC, 0, 0};
    void *a;
    void *_power;
    _power = enter_frame(p, &f) && (
        (a = power_1(p)) ||
        (a = primary(p))
    ) ? a : 0;
    return exit_frame(p, &f, _power);
}

static void *power_1(parser_t *p) {
    frame_t f = {155, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_power_1;
    _power_1 = enter_frame(p, &f) && (
        (a = primary(p)) &&
        (consume(p, 38, "**")) &&
        (b = factor(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _power_1);
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
    void *_primary = 0;
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
    _primary = max;
    return exit_frame(p, &f, _primary);
}

static void *primary_1(parser_t *p) {
    frame_t f = {157, p->pos, FUNC, 0, 0};
    void *a;
    token_t *b;
    void *_primary_1;
    _primary_1 = enter_frame(p, &f) && (
        (a = primary(p)) &&
        (consume(p, 6, ".")) &&
        (b = consume(p, 3, "NAME"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _primary_1);
}

static void *primary_2(parser_t *p) {
    frame_t f = {158, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_primary_2;
    _primary_2 = enter_frame(p, &f) && (
        (a = primary(p)) &&
        (b = invocation(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _primary_2);
}

static void *primary_3(parser_t *p) {
    frame_t f = {159, p->pos, FUNC, 0, 0};
    void *a;
    void *b;
    void *_primary_3;
    _primary_3 = enter_frame(p, &f) && (
        (a = primary(p)) &&
        (b = subscript(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _primary_3);
}

// tuple_atom:
//     | '(' [list_items] ')'
static void *tuple_atom(parser_t *p) {
    frame_t f = {160, p->pos, FUNC, 0, 0};
    void *a;
    void *_tuple_atom;
    _tuple_atom = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (a = list_items(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _tuple_atom);
}

// list_iterable:
//     | '[' list_iterator ']'
static void *list_iterable(parser_t *p) {
    frame_t f = {161, p->pos, FUNC, 0, 0};
    void *a;
    void *_list_iterable;
    _list_iterable = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (a = list_iterator(p)) &&
        (consume(p, 18, "]"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _list_iterable);
}

// list_atom:
//     | '[' [list_items] ']'
static void *list_atom(parser_t *p) {
    frame_t f = {162, p->pos, FUNC, 0, 0};
    void *a;
    void *_list_atom;
    _list_atom = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (a = list_items(p), 1) &&
        (consume(p, 18, "]"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _list_atom);
}

// set_atom:
//     | '{' [set_items] '}'
static void *set_atom(parser_t *p) {
    frame_t f = {163, p->pos, FUNC, 0, 0};
    void *a;
    void *_set_atom;
    _set_atom = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (a = set_items(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _set_atom);
}

// dict_iterable:
//     | '{' dict_iterator '}'
static void *dict_iterable(parser_t *p) {
    frame_t f = {164, p->pos, FUNC, 0, 0};
    void *a;
    void *_dict_iterable;
    _dict_iterable = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (a = dict_iterator(p)) &&
        (consume(p, 16, "}"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _dict_iterable);
}

// dict_atom:
//     | '{' [dict_items] '}'
static void *dict_atom(parser_t *p) {
    frame_t f = {165, p->pos, FUNC, 0, 0};
    void *a;
    void *_dict_atom;
    _dict_atom = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (a = dict_items(p), 1) &&
        (consume(p, 16, "}"))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _dict_atom);
}

// builder:
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
static void *builder(parser_t *p) {
    frame_t f = {166, p->pos, FUNC, 0, 0};
    void *a;
    void *_builder;
    _builder = enter_frame(p, &f) && (
        (a = builder_1(p)) ||
        (a = builder_2(p))
    ) ? a : 0;
    return exit_frame(p, &f, _builder);
}

static void *builder_1(parser_t *p) {
    frame_t f = {167, p->pos, FUNC, 0, 0};
    token_t *a;
    void *b;
    void *c;
    void *_builder_1;
    _builder_1 = enter_frame(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (b = simple_args(p)) &&
        (consume(p, 9, ":")) &&
        (c = expr(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _builder_1);
}

static void *builder_2(parser_t *p) {
    frame_t f = {168, p->pos, FUNC, 0, 0};
    token_t *a;
    void *b;
    void *c;
    void *d;
    void *_builder_2;
    _builder_2 = enter_frame(p, &f) && (
        (a = consume(p, 3, "NAME")) &&
        (b = builder_hint(p), 1) &&
        (c = builder_args(p), 1) &&
        (d = block_suite(p))
    ) ? node(p, &f) : 0;
    return exit_frame(p, &f, _builder_2);
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
    void *a;
    void *_atom;
    _atom = enter_frame(p, &f) && (
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
    return exit_frame(p, &f, _atom);
}
