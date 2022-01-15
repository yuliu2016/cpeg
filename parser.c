#include "include/ast.h"


static ast_list_t *single_input(parser_t *);
static ast_list_t *single_input_3(parser_t *);
static ast_list_t *file_input(parser_t *);
static ast_list_t *eval_input(parser_t *);
static ast_list_t *stmt_list(parser_t *);
static ast_list_t *stmt_loop(parser_t *);
static ast_list_t *stmt(parser_t *);
static ast_list_t *stmt_1(parser_t *);
static ast_list_t *simple_stmt(parser_t *);
static ast_list_t *small_stmt_delimited(parser_t *);
static ast_stmt_t *small_stmt(parser_t *);
static ast_stmt_t *del_stmt(parser_t *);
static ast_stmt_t *return_stmt(parser_t *);
static ast_stmt_t *raise_stmt(parser_t *);
static ast_stmt_t *raise_stmt_3(parser_t *);
static ast_expr_t *star_expr(parser_t *);
static ast_list_t *exprlist(parser_t *);
static ast_list_t *expr_delimited(parser_t *);
static void *target(parser_t *);
static void *target_1(parser_t *);
static void *target_2(parser_t *);
static void *target_4(parser_t *);
static ast_primary_t *t_primary(parser_t *);
static ast_primary_t *t_primary_1(parser_t *);
static ast_primary_t *t_primary_2(parser_t *);
static ast_primary_t *t_primary_3(parser_t *);
static ast_primary_t *t_primary_4(parser_t *);
static void *t_lookahead(parser_t *);
static ast_list_t *targetlist(parser_t *);
static ast_list_t *target_delimited(parser_t *);
static void *expr_or_star(parser_t *);
static ast_list_t *exprlist_star(parser_t *);
static ast_list_t *expr_or_star_delimited(parser_t *);
static ast_list_t *subscript(parser_t *);
static ast_list_t *slice_delimited(parser_t *);
static void *slice(parser_t *);
static void *slice_1(parser_t *);
static void *slice_expr(parser_t *);
static void *list_item(parser_t *);
static ast_list_t *list_items(parser_t *);
static ast_list_t *list_item_delimited(parser_t *);
static void *assignment(parser_t *);
static void *annassign(parser_t *);
static void *annassign_4(parser_t *);
static void *augassign(parser_t *);
static void *simple_assign(parser_t *);
static ast_list_t *simple_assign_1_loop(parser_t *);
static void *simple_assign_1(parser_t *);
static int *augassign_op(parser_t *);
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
static void *expr_as_name_2(parser_t *);
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
static void *invocation_2(parser_t *);
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
static ast_list_t *simple_args(parser_t *);
static ast_list_t *simple_arg_delimited(parser_t *);
static ast_list_t *builder_hint(parser_t *);
static ast_list_t *builder_hint_delimited(parser_t *);
static void *builder_args(parser_t *);
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
static ast_primary_t *primary(parser_t *);
static ast_primary_t *primary_1(parser_t *);
static ast_primary_t *primary_2(parser_t *);
static ast_primary_t *primary_3(parser_t *);
static ast_primary_t *tuple_atom(parser_t *);
static ast_primary_t *list_atom(parser_t *);
static ast_primary_t *builder(parser_t *);
static ast_primary_t *builder_1(parser_t *);
static ast_primary_t *builder_2(parser_t *);
static ast_primary_t *atom(parser_t *);



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
//     | simple_stmt
//     | compound_stmt NEWLINE
static ast_list_t *single_input(parser_t *p) {
    const frame_t f = {251, p->pos, FUNC};
    ast_list_t *res_251;
    ast_list_t *_simple_stmt;
    ast_list_t *alt_251;
    res_251 = enter_frame(p, &f) && ((
            (consume(p, 2, "NEWLINE")) &&
            (alt_251 = ast_list_of(p, ast_nop(p)))
        ) || (
            (_simple_stmt = simple_stmt(p)) &&
            (alt_251 = ast_list_of(p, _simple_stmt))
        ) ||
        (alt_251 = single_input_3(p))
    ) ? alt_251 : 0;
    return exit_frame(p, &f, res_251);
}

static ast_list_t *single_input_3(parser_t *p) {
    const frame_t f = {423, p->pos, FUNC};
    ast_list_t *res_423;
    void *_compound_stmt;
    res_423 = enter_frame(p, &f) && (
        (_compound_stmt = compound_stmt(p)) &&
        (consume(p, 2, "NEWLINE"))
    ) ? ast_list_of(p, _compound_stmt) : 0;
    return exit_frame(p, &f, res_423);
}

// file_input:
//     | stmt_list
static ast_list_t *file_input(parser_t *p) {
    const frame_t f = {535, p->pos, FUNC};
    ast_list_t *res_535;
    ast_list_t *_stmt_list;
    res_535 = enter_frame(p, &f) && (
        (_stmt_list = stmt_list(p))
    ) ? _stmt_list : 0;
    return exit_frame(p, &f, res_535);
}

// eval_input:
//     | exprlist [NEWLINE]
static ast_list_t *eval_input(parser_t *p) {
    const frame_t f = {471, p->pos, FUNC};
    ast_list_t *res_471;
    ast_list_t *_exprlist;
    res_471 = enter_frame(p, &f) && (
        (_exprlist = exprlist(p)) &&
        (consume(p, 2, "NEWLINE"), 1)
    ) ? _exprlist : 0;
    return exit_frame(p, &f, res_471);
}

// stmt_list:
//     | stmt+
static ast_list_t *stmt_list(parser_t *p) {
    const frame_t f = {357, p->pos, FUNC};
    ast_list_t *res_357;
    ast_list_t *_stmts;
    res_357 = enter_frame(p, &f) && (
        (_stmts = stmt_loop(p))
    ) ? _stmts : 0;
    return exit_frame(p, &f, res_357);
}

static ast_list_t *stmt_loop(parser_t *p) {
    ast_list_t *_stmt = stmt(p);
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
static ast_list_t *stmt(parser_t *p) {
    const frame_t f = {936, p->pos, FUNC};
    ast_list_t *res_936;
    ast_list_t *_simple_stmt_or_compound_stmt;
    res_936 = enter_frame(p, &f) && (
        (_simple_stmt_or_compound_stmt = stmt_1(p)) &&
        (consume(p, 2, "NEWLINE"))
    ) ? _simple_stmt_or_compound_stmt : 0;
    return exit_frame(p, &f, res_936);
}

static ast_list_t *stmt_1(parser_t *p) {
    const frame_t f = {194, p->pos, FUNC};
    ast_list_t *res_194;
    void *_compound_stmt;
    ast_list_t *alt_194;
    res_194 = enter_frame(p, &f) && (
        (alt_194 = simple_stmt(p)) || (
            (_compound_stmt = compound_stmt(p)) &&
            (alt_194 = ast_list_of(p, _compound_stmt)))
    ) ? alt_194 : 0;
    return exit_frame(p, &f, res_194);
}

// simple_stmt:
//     | ';'.small_stmt+ [';']
static ast_list_t *simple_stmt(parser_t *p) {
    const frame_t f = {853, p->pos, FUNC};
    ast_list_t *res_853;
    ast_list_t *_small_stmts;
    res_853 = enter_frame(p, &f) && (
        (_small_stmts = small_stmt_delimited(p)) &&
        (consume(p, 12, ";"), 1)
    ) ? _small_stmts : 0;
    return exit_frame(p, &f, res_853);
}

static ast_list_t *small_stmt_delimited(parser_t *p) {
    ast_stmt_t *_small_stmt = small_stmt(p);
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
//     | assignment
static ast_stmt_t *small_stmt(parser_t *p) {
    const frame_t f = {984, p->pos, FUNC};
    ast_stmt_t *res_984;
    ast_stmt_t *alt_984;
    res_984 = enter_frame(p, &f) && ((
            (consume(p, 64, "pass")) &&
            (alt_984 = ast_nop(p))
        ) || (
            (consume(p, 74, "break")) &&
            (alt_984 = ast_break(p))
        ) || (
            (consume(p, 73, "continue")) &&
            (alt_984 = ast_continue(p))
        ) ||
        (alt_984 = return_stmt(p)) ||
        (alt_984 = raise_stmt(p)) ||
        (alt_984 = del_stmt(p)) ||
        (alt_984 = assignment(p))
    ) ? alt_984 : 0;
    return exit_frame(p, &f, res_984);
}

// del_stmt:
//     | 'del' targetlist
static ast_stmt_t *del_stmt(parser_t *p) {
    const frame_t f = {668, p->pos, FUNC};
    ast_stmt_t *res_668;
    ast_list_t *_targetlist;
    res_668 = enter_frame(p, &f) && (
        (consume(p, 79, "del")) &&
        (_targetlist = targetlist(p))
    ) ? ast_del(p, _targetlist) : 0;
    return exit_frame(p, &f, res_668);
}

// return_stmt:
//     | 'return' [exprlist_star]
static ast_stmt_t *return_stmt(parser_t *p) {
    const frame_t f = {815, p->pos, FUNC};
    ast_stmt_t *res_815;
    ast_list_t *_exprlist_star;
    res_815 = enter_frame(p, &f) && (
        (consume(p, 54, "return")) &&
        (_exprlist_star = exprlist_star(p), 1)
    ) ? ast_return(p, _exprlist_star) : 0;
    return exit_frame(p, &f, res_815);
}

// raise_stmt:
//     | 'raise' expr ['from' expr]
static ast_stmt_t *raise_stmt(parser_t *p) {
    const frame_t f = {475, p->pos, FUNC};
    ast_stmt_t *res_475;
    ast_expr_t *_expr;
    ast_stmt_t *_from_expr;
    res_475 = enter_frame(p, &f) && (
        (consume(p, 78, "raise")) &&
        (_expr = expr(p)) &&
        (_from_expr = raise_stmt_3(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_475);
}

static ast_stmt_t *raise_stmt_3(parser_t *p) {
    const frame_t f = {479, p->pos, FUNC};
    ast_stmt_t *res_479;
    ast_expr_t *_expr;
    res_479 = enter_frame(p, &f) && (
        (consume(p, 66, "from")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_479);
}

// star_expr:
//     | '*' bitwise_or
static ast_expr_t *star_expr(parser_t *p) {
    const frame_t f = {554, p->pos, FUNC};
    ast_expr_t *res_554;
    ast_expr_t *_bitwise_or;
    res_554 = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (_bitwise_or = bitwise_or(p))
    ) ? _bitwise_or : 0;
    return exit_frame(p, &f, res_554);
}

// exprlist:
//     | ','.expr+ [',']
static ast_list_t *exprlist(parser_t *p) {
    const frame_t f = {43, p->pos, FUNC};
    ast_list_t *res_43;
    ast_list_t *_exprs;
    res_43 = enter_frame(p, &f) && (
        (_exprs = expr_delimited(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _exprs : 0;
    return exit_frame(p, &f, res_43);
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
    const frame_t f = {161, p->pos, FUNC};
    void *res_161;
    void *alt_161;
    res_161 = enter_frame(p, &f) && (
        (alt_161 = target_1(p)) ||
        (alt_161 = target_2(p)) ||
        (alt_161 = consume(p, 3, "NAME")) ||
        (alt_161 = target_4(p))
    ) ? alt_161 : 0;
    return exit_frame(p, &f, res_161);
}

static void *target_1(parser_t *p) {
    const frame_t f = {27, p->pos, FUNC};
    void *res_27;
    ast_primary_t *_t_primary;
    token_t *_name;
    res_27 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (consume(p, 6, ".")) &&
        (_name = consume(p, 3, "NAME")) &&
        (!test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_27);
}

static void *target_2(parser_t *p) {
    const frame_t f = {28, p->pos, FUNC};
    void *res_28;
    ast_primary_t *_t_primary;
    ast_list_t *_subscript;
    res_28 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (_subscript = subscript(p)) &&
        (!test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_28);
}

static void *target_4(parser_t *p) {
    const frame_t f = {30, p->pos, FUNC};
    void *res_30;
    ast_list_t *_targetlist;
    res_30 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_targetlist = targetlist(p)) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_30);
}

// t_primary (left_recursive):
//     | t_primary '.' NAME &t_lookahead
//     | t_primary invocation &t_lookahead
//     | t_primary subscript &t_lookahead
//     | atom &t_lookahead
static ast_primary_t *t_primary(parser_t *p) {
    const frame_t f = {255, p->pos, FUNC};
    ast_primary_t *res_255 = 0;
    if (is_memoized(p, &f, (void **) &res_255)) {
        return res_255;
    }
    ast_primary_t *alt_255;
    size_t maxpos;
    ast_primary_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_255;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_255 = (
                (alt_255 = t_primary_1(p)) ||
                (alt_255 = t_primary_2(p)) ||
                (alt_255 = t_primary_3(p)) ||
                (alt_255 = t_primary_4(p))
            ) ? alt_255 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_255 = max;
    }
    insert_memo(p, &f, res_255);
    return exit_frame(p, &f, res_255);
}

static ast_primary_t *t_primary_1(parser_t *p) {
    const frame_t f = {841, p->pos, FUNC};
    ast_primary_t *res_841;
    ast_primary_t *_t_primary;
    token_t *_name;
    res_841 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (consume(p, 6, ".")) &&
        (_name = consume(p, 3, "NAME")) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_841);
}

static ast_primary_t *t_primary_2(parser_t *p) {
    const frame_t f = {842, p->pos, FUNC};
    ast_primary_t *res_842;
    ast_primary_t *_t_primary;
    void *_invocation;
    res_842 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (_invocation = invocation(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_842);
}

static ast_primary_t *t_primary_3(parser_t *p) {
    const frame_t f = {843, p->pos, FUNC};
    ast_primary_t *res_843;
    ast_primary_t *_t_primary;
    ast_list_t *_subscript;
    res_843 = enter_frame(p, &f) && (
        (_t_primary = t_primary(p)) &&
        (_subscript = subscript(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_843);
}

static ast_primary_t *t_primary_4(parser_t *p) {
    const frame_t f = {844, p->pos, FUNC};
    ast_primary_t *res_844;
    ast_primary_t *_atom;
    res_844 = enter_frame(p, &f) && (
        (_atom = atom(p)) &&
        (test_and_reset(p, &f, t_lookahead(p)))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_844);
}

// t_lookahead:
//     | '.'
//     | '('
//     | '['
static void *t_lookahead(parser_t *p) {
    const frame_t f = {159, p->pos, FUNC};
    void *res_159;
    void *alt_159;
    res_159 = enter_frame(p, &f) && (
        (alt_159 = consume(p, 6, ".")) ||
        (alt_159 = consume(p, 13, "(")) ||
        (alt_159 = consume(p, 17, "["))
    ) ? alt_159 : 0;
    return exit_frame(p, &f, res_159);
}

// targetlist:
//     | ','.target+ [',']
static ast_list_t *targetlist(parser_t *p) {
    const frame_t f = {31, p->pos, FUNC};
    ast_list_t *res_31;
    ast_list_t *_targets;
    res_31 = enter_frame(p, &f) && (
        (_targets = target_delimited(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _targets : 0;
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
    const frame_t f = {132, p->pos, FUNC};
    void *res_132;
    void *alt_132;
    res_132 = enter_frame(p, &f) && (
        (alt_132 = star_expr(p)) ||
        (alt_132 = expr(p))
    ) ? alt_132 : 0;
    return exit_frame(p, &f, res_132);
}

// exprlist_star:
//     | ','.expr_or_star+ [',']
static ast_list_t *exprlist_star(parser_t *p) {
    const frame_t f = {918, p->pos, FUNC};
    ast_list_t *res_918;
    ast_list_t *_expr_or_stars;
    res_918 = enter_frame(p, &f) && (
        (_expr_or_stars = expr_or_star_delimited(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _expr_or_stars : 0;
    return exit_frame(p, &f, res_918);
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
//     | '[' ','.slice+ [','] ']'
static ast_list_t *subscript(parser_t *p) {
    const frame_t f = {379, p->pos, FUNC};
    ast_list_t *res_379;
    ast_list_t *_slices;
    res_379 = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (_slices = slice_delimited(p)) &&
        (consume(p, 7, ","), 1) &&
        (consume(p, 18, "]"))
    ) ? _slices : 0;
    return exit_frame(p, &f, res_379);
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
    const frame_t f = {418, p->pos, FUNC};
    void *res_418;
    void *alt_418;
    res_418 = enter_frame(p, &f) && (
        (alt_418 = slice_1(p)) ||
        (alt_418 = expr(p))
    ) ? alt_418 : 0;
    return exit_frame(p, &f, res_418);
}

static void *slice_1(parser_t *p) {
    const frame_t f = {292, p->pos, FUNC};
    void *res_292;
    ast_expr_t *_expr;
    void *_slice_expr;
    void *_slice_expr_1;
    res_292 = enter_frame(p, &f) && (
        (_expr = expr(p), 1) &&
        (_slice_expr = slice_expr(p)) &&
        (_slice_expr_1 = slice_expr(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_292);
}

// slice_expr:
//     | ':' [expr]
static void *slice_expr(parser_t *p) {
    const frame_t f = {210, p->pos, FUNC};
    void *res_210;
    ast_expr_t *_expr;
    res_210 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_expr = expr(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_210);
}

// list_item:
//     | star_expr
//     | named_expr
static void *list_item(parser_t *p) {
    const frame_t f = {756, p->pos, FUNC};
    void *res_756;
    void *alt_756;
    res_756 = enter_frame(p, &f) && (
        (alt_756 = star_expr(p)) ||
        (alt_756 = named_expr(p))
    ) ? alt_756 : 0;
    return exit_frame(p, &f, res_756);
}

// list_items:
//     | ','.list_item+ [',']
static ast_list_t *list_items(parser_t *p) {
    const frame_t f = {215, p->pos, FUNC};
    ast_list_t *res_215;
    ast_list_t *_list_items;
    res_215 = enter_frame(p, &f) && (
        (_list_items = list_item_delimited(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _list_items : 0;
    return exit_frame(p, &f, res_215);
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

// assignment:
//     | annassign
//     | augassign
//     | simple_assign
static void *assignment(parser_t *p) {
    const frame_t f = {733, p->pos, FUNC};
    void *res_733;
    void *alt_733;
    res_733 = enter_frame(p, &f) && (
        (alt_733 = annassign(p)) ||
        (alt_733 = augassign(p)) ||
        (alt_733 = simple_assign(p))
    ) ? alt_733 : 0;
    return exit_frame(p, &f, res_733);
}

// annassign:
//     | target ':' expr ['=' exprlist]
static void *annassign(parser_t *p) {
    const frame_t f = {592, p->pos, FUNC};
    void *res_592;
    void *_target;
    ast_expr_t *_expr;
    void *_assign_exprlist;
    res_592 = enter_frame(p, &f) && (
        (_target = target(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p)) &&
        (_assign_exprlist = annassign_4(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_592);
}

static void *annassign_4(parser_t *p) {
    const frame_t f = {45, p->pos, FUNC};
    void *res_45;
    ast_list_t *_exprlist;
    res_45 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_exprlist = exprlist(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_45);
}

// augassign:
//     | target augassign_op exprlist
static void *augassign(parser_t *p) {
    const frame_t f = {578, p->pos, FUNC};
    void *res_578;
    void *_target;
    int *_augassign_op;
    ast_list_t *_exprlist;
    res_578 = enter_frame(p, &f) && (
        (_target = target(p)) &&
        (_augassign_op = augassign_op(p)) &&
        (_exprlist = exprlist(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_578);
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
static void *simple_assign(parser_t *p) {
    const frame_t f = {100, p->pos, FUNC};
    void *res_100;
    ast_list_t *_targetlist_assigns;
    ast_list_t *_exprlist_star;
    res_100 = enter_frame(p, &f) && (
        (_targetlist_assigns = simple_assign_1_loop(p)) &&
        (_exprlist_star = exprlist_star(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_100);
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
    const frame_t f = {62, p->pos, FUNC};
    void *res_62;
    ast_list_t *_targetlist;
    res_62 = enter_frame(p, &f) && (
        (_targetlist = targetlist(p)) &&
        (consume(p, 8, "="))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_62);
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
    const frame_t f = {950, p->pos, FUNC};
    int *res_950;
    int *alt_950;
    res_950 = enter_frame(p, &f) && ((
            (consume(p, 39, "+=")) &&
            (alt_950 = ast_integer(p, BINOP_PLS))
        ) || (
            (consume(p, 40, "-=")) &&
            (alt_950 = ast_integer(p, BINOP_MIN))
        ) || (
            (consume(p, 41, "*=")) &&
            (alt_950 = ast_integer(p, BINOP_MUL))
        ) || (
            (consume(p, 42, "/=")) &&
            (alt_950 = ast_integer(p, BINOP_DIV))
        ) || (
            (consume(p, 43, "%=")) &&
            (alt_950 = ast_integer(p, BINOP_MOD))
        ) || (
            (consume(p, 44, "@=")) &&
            (alt_950 = ast_integer(p, BINOP_MML))
        ) || (
            (consume(p, 45, "|=")) &&
            (alt_950 = ast_integer(p, BINOP_IOR))
        ) || (
            (consume(p, 46, "&=")) &&
            (alt_950 = ast_integer(p, BINOP_AND))
        ) || (
            (consume(p, 47, "^=")) &&
            (alt_950 = ast_integer(p, BINOP_XOR))
        ) || (
            (consume(p, 50, "//=")) &&
            (alt_950 = ast_integer(p, BINOP_FDV))
        ) || (
            (consume(p, 51, "**=")) &&
            (alt_950 = ast_integer(p, BINOP_POW))
        ) || (
            (consume(p, 52, "<<=")) &&
            (alt_950 = ast_integer(p, BINOP_SHL))
        ) || (
            (consume(p, 53, ">>=")) &&
            (alt_950 = ast_integer(p, BINOP_SHR)))
    ) ? alt_950 : 0;
    return exit_frame(p, &f, res_950);
}

// compound_stmt:
//     | if_stmt
//     | while_stmt
//     | for_stmt
//     | try_stmt
//     | with_stmt
static void *compound_stmt(parser_t *p) {
    const frame_t f = {548, p->pos, FUNC};
    void *res_548;
    void *alt_548;
    res_548 = enter_frame(p, &f) && (
        (alt_548 = if_stmt(p)) ||
        (alt_548 = while_stmt(p)) ||
        (alt_548 = for_stmt(p)) ||
        (alt_548 = try_stmt(p)) ||
        (alt_548 = with_stmt(p))
    ) ? alt_548 : 0;
    return exit_frame(p, &f, res_548);
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
static void *if_stmt(parser_t *p) {
    const frame_t f = {826, p->pos, FUNC};
    void *res_826;
    ast_named_t *_named_expr;
    void *_suite;
    ast_list_t *_elif_stmts;
    void *_else_suite;
    res_826 = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (_named_expr = named_expr(p)) &&
        (_suite = suite(p)) &&
        (_elif_stmts = elif_stmt_loop(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_826);
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
    const frame_t f = {651, p->pos, FUNC};
    void *res_651;
    ast_named_t *_named_expr;
    void *_suite;
    res_651 = enter_frame(p, &f) && (
        (consume(p, 57, "elif")) &&
        (_named_expr = named_expr(p)) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_651);
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
static void *while_stmt(parser_t *p) {
    const frame_t f = {422, p->pos, FUNC};
    void *res_422;
    ast_named_t *_named_expr;
    void *_suite;
    void *_else_suite;
    res_422 = enter_frame(p, &f) && (
        (consume(p, 71, "while")) &&
        (_named_expr = named_expr(p)) &&
        (_suite = suite(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_422);
}

// for_stmt:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
static void *for_stmt(parser_t *p) {
    const frame_t f = {166, p->pos, FUNC};
    void *res_166;
    ast_list_t *_targetlist;
    ast_list_t *_exprlist;
    void *_suite;
    void *_else_suite;
    res_166 = enter_frame(p, &f) && (
        (consume(p, 72, "for")) &&
        (_targetlist = targetlist(p)) &&
        (consume(p, 63, "in")) &&
        (_exprlist = exprlist(p)) &&
        (_suite = suite(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_166);
}

// try_stmt:
//     | 'try' suite (except_suite | finally_suite)
static void *try_stmt(parser_t *p) {
    const frame_t f = {180, p->pos, FUNC};
    void *res_180;
    void *_suite;
    void *_except_suite_or_finally_suite;
    res_180 = enter_frame(p, &f) && (
        (consume(p, 75, "try")) &&
        (_suite = suite(p)) &&
        (_except_suite_or_finally_suite = try_stmt_3(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_180);
}

static void *try_stmt_3(parser_t *p) {
    const frame_t f = {624, p->pos, FUNC};
    void *res_624;
    void *alt_624;
    res_624 = enter_frame(p, &f) && (
        (alt_624 = except_suite(p)) ||
        (alt_624 = finally_suite(p))
    ) ? alt_624 : 0;
    return exit_frame(p, &f, res_624);
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
static void *with_stmt(parser_t *p) {
    const frame_t f = {177, p->pos, FUNC};
    void *res_177;
    ast_list_t *_expr_as_names;
    void *_suite;
    res_177 = enter_frame(p, &f) && (
        (consume(p, 68, "with")) &&
        (_expr_as_names = expr_as_name_delimited(p)) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_177);
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
//     | expr ['as' NAME]
static void *expr_as_name(parser_t *p) {
    const frame_t f = {782, p->pos, FUNC};
    void *res_782;
    ast_expr_t *_expr;
    void *_as_name;
    res_782 = enter_frame(p, &f) && (
        (_expr = expr(p)) &&
        (_as_name = expr_as_name_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_782);
}

static void *expr_as_name_2(parser_t *p) {
    const frame_t f = {121, p->pos, FUNC};
    void *res_121;
    token_t *_name;
    res_121 = enter_frame(p, &f) && (
        (consume(p, 65, "as")) &&
        (_name = consume(p, 3, "NAME"))
    ) ? _name : 0;
    return exit_frame(p, &f, res_121);
}

// block_suite:
//     | '{' NEWLINE stmt_list '}'
//     | '{' [simple_stmt] '}'
static void *block_suite(parser_t *p) {
    const frame_t f = {206, p->pos, FUNC};
    void *res_206;
    void *alt_206;
    res_206 = enter_frame(p, &f) && (
        (alt_206 = block_suite_1(p)) ||
        (alt_206 = block_suite_2(p))
    ) ? alt_206 : 0;
    return exit_frame(p, &f, res_206);
}

static void *block_suite_1(parser_t *p) {
    const frame_t f = {560, p->pos, FUNC};
    void *res_560;
    token_t *_newline;
    ast_list_t *_stmt_list;
    res_560 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_newline = consume(p, 2, "NEWLINE")) &&
        (_stmt_list = stmt_list(p)) &&
        (consume(p, 16, "}"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_560);
}

static void *block_suite_2(parser_t *p) {
    const frame_t f = {561, p->pos, FUNC};
    void *res_561;
    ast_list_t *_simple_stmt;
    res_561 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_simple_stmt = simple_stmt(p), 1) &&
        (consume(p, 16, "}"))
    ) ? _simple_stmt : 0;
    return exit_frame(p, &f, res_561);
}

// suite:
//     | ':' simple_stmt
//     | block_suite
static void *suite(parser_t *p) {
    const frame_t f = {64, p->pos, FUNC};
    void *res_64;
    void *alt_64;
    res_64 = enter_frame(p, &f) && (
        (alt_64 = suite_1(p)) ||
        (alt_64 = block_suite(p))
    ) ? alt_64 : 0;
    return exit_frame(p, &f, res_64);
}

static void *suite_1(parser_t *p) {
    const frame_t f = {98, p->pos, FUNC};
    void *res_98;
    ast_list_t *_simple_stmt;
    res_98 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_simple_stmt = simple_stmt(p))
    ) ? _simple_stmt : 0;
    return exit_frame(p, &f, res_98);
}

// else_suite:
//     | 'else' suite
static void *else_suite(parser_t *p) {
    const frame_t f = {378, p->pos, FUNC};
    void *res_378;
    void *_suite;
    res_378 = enter_frame(p, &f) && (
        (consume(p, 58, "else")) &&
        (_suite = suite(p))
    ) ? _suite : 0;
    return exit_frame(p, &f, res_378);
}

// finally_suite:
//     | 'finally' suite
static void *finally_suite(parser_t *p) {
    const frame_t f = {172, p->pos, FUNC};
    void *res_172;
    void *_suite;
    res_172 = enter_frame(p, &f) && (
        (consume(p, 77, "finally")) &&
        (_suite = suite(p))
    ) ? _suite : 0;
    return exit_frame(p, &f, res_172);
}

// except_clause:
//     | 'except' [expr_as_name] suite
static void *except_clause(parser_t *p) {
    const frame_t f = {358, p->pos, FUNC};
    void *res_358;
    void *_expr_as_name;
    void *_suite;
    res_358 = enter_frame(p, &f) && (
        (consume(p, 76, "except")) &&
        (_expr_as_name = expr_as_name(p), 1) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_358);
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
static void *except_suite(parser_t *p) {
    const frame_t f = {810, p->pos, FUNC};
    void *res_810;
    ast_list_t *_except_clauses;
    void *_else_suite;
    void *_finally_suite;
    res_810 = enter_frame(p, &f) && (
        (_except_clauses = except_clause_loop(p)) &&
        (_else_suite = else_suite(p), 1) &&
        (_finally_suite = finally_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_810);
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
//     | '(' [','.call_arg+ [',']] ')'
static void *invocation(parser_t *p) {
    const frame_t f = {944, p->pos, FUNC};
    void *res_944;
    void *_invocation_2;
    res_944 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_invocation_2 = invocation_2(p), 1) &&
        (consume(p, 14, ")"))
    ) ? _invocation_2 : 0;
    return exit_frame(p, &f, res_944);
}

static void *invocation_2(parser_t *p) {
    const frame_t f = {35, p->pos, FUNC};
    void *res_35;
    ast_list_t *_call_args;
    res_35 = enter_frame(p, &f) && (
        (_call_args = call_arg_delimited(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _call_args : 0;
    return exit_frame(p, &f, res_35);
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
    const frame_t f = {741, p->pos, FUNC};
    void *res_741;
    void *alt_741;
    res_741 = enter_frame(p, &f) && (
        (alt_741 = call_arg_1(p)) ||
        (alt_741 = call_arg_2(p)) ||
        (alt_741 = call_arg_3(p)) ||
        (alt_741 = call_arg_4(p)) ||
        (alt_741 = expr(p))
    ) ? alt_741 : 0;
    return exit_frame(p, &f, res_741);
}

static void *call_arg_1(parser_t *p) {
    const frame_t f = {639, p->pos, FUNC};
    void *res_639;
    token_t *_name;
    ast_expr_t *_expr;
    res_639 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_639);
}

static void *call_arg_2(parser_t *p) {
    const frame_t f = {640, p->pos, FUNC};
    void *res_640;
    token_t *_name;
    ast_expr_t *_expr;
    res_640 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 8, "=")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_640);
}

static void *call_arg_3(parser_t *p) {
    const frame_t f = {641, p->pos, FUNC};
    void *res_641;
    ast_expr_t *_expr;
    res_641 = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_641);
}

static void *call_arg_4(parser_t *p) {
    const frame_t f = {642, p->pos, FUNC};
    void *res_642;
    ast_expr_t *_expr;
    res_642 = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_642);
}

// typed_arg_list:
//     | kwargs
//     | args_kwargs
//     | full_arg_list
static void *typed_arg_list(parser_t *p) {
    const frame_t f = {60, p->pos, FUNC};
    void *res_60;
    void *alt_60;
    res_60 = enter_frame(p, &f) && (
        (alt_60 = kwargs(p)) ||
        (alt_60 = args_kwargs(p)) ||
        (alt_60 = full_arg_list(p))
    ) ? alt_60 : 0;
    return exit_frame(p, &f, res_60);
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
static void *full_arg_list(parser_t *p) {
    const frame_t f = {183, p->pos, FUNC};
    void *res_183;
    ast_list_t *_default_args;
    void *_full_arg_list_2;
    res_183 = enter_frame(p, &f) && (
        (_default_args = default_arg_delimited(p)) &&
        (_full_arg_list_2 = full_arg_list_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_183);
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
    const frame_t f = {618, p->pos, FUNC};
    void *res_618;
    void *_kwargs_or_args_kwargs;
    res_618 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_kwargs_or_args_kwargs = full_arg_list_2_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_618);
}

static void *full_arg_list_2_2(parser_t *p) {
    const frame_t f = {941, p->pos, FUNC};
    void *res_941;
    void *alt_941;
    res_941 = enter_frame(p, &f) && (
        (alt_941 = kwargs(p)) ||
        (alt_941 = args_kwargs(p))
    ) ? alt_941 : 0;
    return exit_frame(p, &f, res_941);
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
static void *args_kwargs(parser_t *p) {
    const frame_t f = {395, p->pos, FUNC};
    void *res_395;
    void *_typed_arg;
    ast_list_t *_comma_default_args;
    void *_args_kwargs_4;
    res_395 = enter_frame(p, &f) && (
        (consume(p, 23, "*")) &&
        (_typed_arg = typed_arg(p), 1) &&
        (_comma_default_args = args_kwargs_3_loop(p)) &&
        (_args_kwargs_4 = args_kwargs_4(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_395);
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
    const frame_t f = {967, p->pos, FUNC};
    void *res_967;
    void *_default_arg;
    res_967 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_default_arg = default_arg(p))
    ) ? _default_arg : 0;
    return exit_frame(p, &f, res_967);
}

static void *args_kwargs_4(parser_t *p) {
    const frame_t f = {968, p->pos, FUNC};
    void *res_968;
    void *_kwargs;
    res_968 = enter_frame(p, &f) && (
        (consume(p, 7, ",")) &&
        (_kwargs = kwargs(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_968);
}

// kwargs:
//     | '**' typed_arg [',']
static void *kwargs(parser_t *p) {
    const frame_t f = {449, p->pos, FUNC};
    void *res_449;
    void *_typed_arg;
    res_449 = enter_frame(p, &f) && (
        (consume(p, 38, "**")) &&
        (_typed_arg = typed_arg(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _typed_arg : 0;
    return exit_frame(p, &f, res_449);
}

// default_arg:
//     | typed_arg ['=' expr]
static void *default_arg(parser_t *p) {
    const frame_t f = {184, p->pos, FUNC};
    void *res_184;
    void *_typed_arg;
    void *_assign_expr;
    res_184 = enter_frame(p, &f) && (
        (_typed_arg = typed_arg(p)) &&
        (_assign_expr = default_arg_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_184);
}

static void *default_arg_2(parser_t *p) {
    const frame_t f = {827, p->pos, FUNC};
    void *res_827;
    ast_expr_t *_expr;
    res_827 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_expr = expr(p))
    ) ? _expr : 0;
    return exit_frame(p, &f, res_827);
}

// typed_arg:
//     | NAME [':' expr]
static void *typed_arg(parser_t *p) {
    const frame_t f = {345, p->pos, FUNC};
    void *res_345;
    token_t *_name;
    void *_colon_expr;
    res_345 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_colon_expr = typed_arg_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_345);
}

static void *typed_arg_2(parser_t *p) {
    const frame_t f = {908, p->pos, FUNC};
    void *res_908;
    ast_expr_t *_expr;
    res_908 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? _expr : 0;
    return exit_frame(p, &f, res_908);
}

// simple_arg:
//     | NAME ['=' expr]
static void *simple_arg(parser_t *p) {
    const frame_t f = {401, p->pos, FUNC};
    void *res_401;
    token_t *_name;
    void *_assign_expr;
    res_401 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_assign_expr = simple_arg_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_401);
}

static void *simple_arg_2(parser_t *p) {
    const frame_t f = {76, p->pos, FUNC};
    void *res_76;
    ast_expr_t *_expr;
    res_76 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_expr = expr(p))
    ) ? _expr : 0;
    return exit_frame(p, &f, res_76);
}

// simple_args:
//     | ','.simple_arg+
static ast_list_t *simple_args(parser_t *p) {
    const frame_t f = {506, p->pos, FUNC};
    ast_list_t *res_506;
    ast_list_t *_simple_args;
    res_506 = enter_frame(p, &f) && (
        (_simple_args = simple_arg_delimited(p))
    ) ? _simple_args : 0;
    return exit_frame(p, &f, res_506);
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
//     | '<' ','.NAME+ '>'
static ast_list_t *builder_hint(parser_t *p) {
    const frame_t f = {179, p->pos, FUNC};
    ast_list_t *res_179;
    ast_list_t *_names;
    res_179 = enter_frame(p, &f) && (
        (consume(p, 19, "<")) &&
        (_names = builder_hint_delimited(p)) &&
        (consume(p, 20, ">"))
    ) ? _names : 0;
    return exit_frame(p, &f, res_179);
}

static ast_list_t *builder_hint_delimited(parser_t *p) {
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

// builder_args:
//     | '(' [typed_arg_list] ')'
static void *builder_args(parser_t *p) {
    const frame_t f = {73, p->pos, FUNC};
    void *res_73;
    void *_typed_arg_list;
    res_73 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_typed_arg_list = typed_arg_list(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_73);
}

// named_expr:
//     | NAME ':=' expr
//     | expr
static ast_named_t *named_expr(parser_t *p) {
    const frame_t f = {307, p->pos, FUNC};
    ast_named_t *res_307;
    ast_expr_t *_expr;
    ast_named_t *alt_307;
    res_307 = enter_frame(p, &f) && (
        (alt_307 = named_expr_1(p)) || (
            (_expr = expr(p)) &&
            (alt_307 = ast_unnamed(p, _expr)))
    ) ? alt_307 : 0;
    return exit_frame(p, &f, res_307);
}

static ast_named_t *named_expr_1(parser_t *p) {
    const frame_t f = {669, p->pos, FUNC};
    ast_named_t *res_669;
    token_t *_name;
    ast_expr_t *_expr;
    res_669 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (_expr = expr(p))
    ) ? ast_named(p, _name, _expr) : 0;
    return exit_frame(p, &f, res_669);
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
static ast_expr_t *conditional(parser_t *p) {
    const frame_t f = {207, p->pos, FUNC};
    ast_expr_t *res_207;
    ast_expr_t *_disjunction;
    ast_expr_t *_disjunction_1;
    ast_expr_t *_expr;
    res_207 = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (_disjunction = disjunction(p)) &&
        (consume(p, 10, "?")) &&
        (_disjunction_1 = disjunction(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? ast_conditional(p, _disjunction, _disjunction_1, _expr) : 0;
    return exit_frame(p, &f, res_207);
}

// expr:
//     | conditional
//     | disjunction
static ast_expr_t *expr(parser_t *p) {
    const frame_t f = {797, p->pos, FUNC};
    ast_expr_t *res_797;
    ast_expr_t *alt_797;
    res_797 = enter_frame(p, &f) && (
        (alt_797 = conditional(p)) ||
        (alt_797 = disjunction(p))
    ) ? alt_797 : 0;
    return exit_frame(p, &f, res_797);
}

// disjunction (left_recursive):
//     | disjunction 'or' conjunction
//     | conjunction
static ast_expr_t *disjunction(parser_t *p) {
    const frame_t f = {410, p->pos, FUNC};
    ast_expr_t *res_410 = 0;
    if (is_memoized(p, &f, (void **) &res_410)) {
        return res_410;
    }
    ast_expr_t *alt_410;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_410;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_410 = (
                (alt_410 = disjunction_1(p)) ||
                (alt_410 = conjunction(p))
            ) ? alt_410 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_410 = max;
    }
    insert_memo(p, &f, res_410);
    return exit_frame(p, &f, res_410);
}

static ast_expr_t *disjunction_1(parser_t *p) {
    const frame_t f = {644, p->pos, FUNC};
    ast_expr_t *res_644;
    ast_expr_t *_disjunction;
    ast_expr_t *_conjunction;
    res_644 = enter_frame(p, &f) && (
        (_disjunction = disjunction(p)) &&
        (consume(p, 60, "or")) &&
        (_conjunction = conjunction(p))
    ) ? ast_binary(p, _disjunction, _conjunction, LOGIC_OR) : 0;
    return exit_frame(p, &f, res_644);
}

// conjunction (left_recursive):
//     | conjunction 'and' inversion
//     | inversion
static ast_expr_t *conjunction(parser_t *p) {
    const frame_t f = {462, p->pos, FUNC};
    ast_expr_t *res_462 = 0;
    if (is_memoized(p, &f, (void **) &res_462)) {
        return res_462;
    }
    ast_expr_t *alt_462;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_462;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_462 = (
                (alt_462 = conjunction_1(p)) ||
                (alt_462 = inversion(p))
            ) ? alt_462 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_462 = max;
    }
    insert_memo(p, &f, res_462);
    return exit_frame(p, &f, res_462);
}

static ast_expr_t *conjunction_1(parser_t *p) {
    const frame_t f = {168, p->pos, FUNC};
    ast_expr_t *res_168;
    ast_expr_t *_conjunction;
    ast_expr_t *_inversion;
    res_168 = enter_frame(p, &f) && (
        (_conjunction = conjunction(p)) &&
        (consume(p, 59, "and")) &&
        (_inversion = inversion(p))
    ) ? ast_binary(p, _conjunction, _inversion, LOGIC_AND) : 0;
    return exit_frame(p, &f, res_168);
}

// inversion:
//     | 'not' inversion
//     | comparison
static ast_expr_t *inversion(parser_t *p) {
    const frame_t f = {963, p->pos, FUNC};
    ast_expr_t *res_963;
    ast_expr_t *alt_963;
    res_963 = enter_frame(p, &f) && (
        (alt_963 = inversion_1(p)) ||
        (alt_963 = comparison(p))
    ) ? alt_963 : 0;
    return exit_frame(p, &f, res_963);
}

static ast_expr_t *inversion_1(parser_t *p) {
    const frame_t f = {933, p->pos, FUNC};
    ast_expr_t *res_933;
    ast_expr_t *_inversion;
    res_933 = enter_frame(p, &f) && (
        (consume(p, 61, "not")) &&
        (_inversion = inversion(p))
    ) ? ast_unary(p, _inversion, LOGIC_NOT) : 0;
    return exit_frame(p, &f, res_933);
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
static ast_expr_t *comparison(parser_t *p) {
    const frame_t f = {529, p->pos, FUNC};
    ast_expr_t *res_529;
    ast_expr_t *alt_529;
    res_529 = enter_frame(p, &f) && (
        (alt_529 = comparison_1(p)) ||
        (alt_529 = bitwise_or(p))
    ) ? alt_529 : 0;
    return exit_frame(p, &f, res_529);
}

static ast_expr_t *comparison_1(parser_t *p) {
    const frame_t f = {308, p->pos, FUNC};
    ast_expr_t *res_308;
    ast_expr_t *_bitwise_or;
    ast_list_t *_comp_op_bitwise_ors;
    res_308 = enter_frame(p, &f) && (
        (_bitwise_or = bitwise_or(p)) &&
        (_comp_op_bitwise_ors = comparison_1_2_loop(p))
    ) ? ast_comparison(p, _bitwise_or, _comp_op_bitwise_ors) : 0;
    return exit_frame(p, &f, res_308);
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
    const frame_t f = {742, p->pos, FUNC};
    ast_expr_t *res_742;
    int *_comp_op;
    ast_expr_t *_bitwise_or;
    res_742 = enter_frame(p, &f) && (
        (_comp_op = comp_op(p)) &&
        (_bitwise_or = bitwise_or(p))
    ) ? ast_comp_term(p, _comp_op, _bitwise_or) : 0;
    return exit_frame(p, &f, res_742);
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
    const frame_t f = {193, p->pos, FUNC};
    int *res_193;
    int *alt_193;
    res_193 = enter_frame(p, &f) && ((
            (consume(p, 19, "<")) &&
            (alt_193 = ast_integer(p, CMP_LT))
        ) || (
            (consume(p, 20, ">")) &&
            (alt_193 = ast_integer(p, CMP_GT))
        ) || (
            (consume(p, 31, "==")) &&
            (alt_193 = ast_integer(p, CMP_EQ))
        ) || (
            (consume(p, 34, ">=")) &&
            (alt_193 = ast_integer(p, CMP_GE))
        ) || (
            (consume(p, 33, "<=")) &&
            (alt_193 = ast_integer(p, CMP_LE))
        ) || (
            (consume(p, 32, "!=")) &&
            (alt_193 = ast_integer(p, CMP_NE))
        ) || (
            (consume(p, 63, "in")) &&
            (alt_193 = ast_integer(p, CMP_IN))
        ) ||
        (alt_193 = comp_op_8(p)) || (
            (consume(p, 62, "is")) &&
            (alt_193 = ast_integer(p, CMP_IS))
        ) ||
        (alt_193 = comp_op_10(p))
    ) ? alt_193 : 0;
    return exit_frame(p, &f, res_193);
}

static int *comp_op_8(parser_t *p) {
    const frame_t f = {426, p->pos, FUNC};
    int *res_426;
    res_426 = enter_frame(p, &f) && (
        (consume(p, 61, "not")) &&
        (consume(p, 63, "in"))
    ) ? ast_integer(p, CMP_NI) : 0;
    return exit_frame(p, &f, res_426);
}

static int *comp_op_10(parser_t *p) {
    const frame_t f = {997, p->pos, FUNC};
    int *res_997;
    res_997 = enter_frame(p, &f) && (
        (consume(p, 62, "is")) &&
        (consume(p, 61, "not"))
    ) ? ast_integer(p, CMP_NS) : 0;
    return exit_frame(p, &f, res_997);
}

// bitwise_or (left_recursive):
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
static ast_expr_t *bitwise_or(parser_t *p) {
    const frame_t f = {201, p->pos, FUNC};
    ast_expr_t *res_201 = 0;
    if (is_memoized(p, &f, (void **) &res_201)) {
        return res_201;
    }
    ast_expr_t *alt_201;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_201;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_201 = (
                (alt_201 = bitwise_or_1(p)) ||
                (alt_201 = bitwise_xor(p))
            ) ? alt_201 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_201 = max;
    }
    insert_memo(p, &f, res_201);
    return exit_frame(p, &f, res_201);
}

static ast_expr_t *bitwise_or_1(parser_t *p) {
    const frame_t f = {259, p->pos, FUNC};
    ast_expr_t *res_259;
    ast_expr_t *_bitwise_or;
    ast_expr_t *_bitwise_xor;
    res_259 = enter_frame(p, &f) && (
        (_bitwise_or = bitwise_or(p)) &&
        (consume(p, 27, "|")) &&
        (_bitwise_xor = bitwise_xor(p))
    ) ? ast_binary(p, _bitwise_or, _bitwise_xor, BINOP_IOR) : 0;
    return exit_frame(p, &f, res_259);
}

// bitwise_xor (left_recursive):
//     | bitwise_xor '^' bitwise_and
//     | bitwise_and
static ast_expr_t *bitwise_xor(parser_t *p) {
    const frame_t f = {565, p->pos, FUNC};
    ast_expr_t *res_565 = 0;
    if (is_memoized(p, &f, (void **) &res_565)) {
        return res_565;
    }
    ast_expr_t *alt_565;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_565;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_565 = (
                (alt_565 = bitwise_xor_1(p)) ||
                (alt_565 = bitwise_and(p))
            ) ? alt_565 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_565 = max;
    }
    insert_memo(p, &f, res_565);
    return exit_frame(p, &f, res_565);
}

static ast_expr_t *bitwise_xor_1(parser_t *p) {
    const frame_t f = {39, p->pos, FUNC};
    ast_expr_t *res_39;
    ast_expr_t *_bitwise_xor;
    ast_expr_t *_bitwise_and;
    res_39 = enter_frame(p, &f) && (
        (_bitwise_xor = bitwise_xor(p)) &&
        (consume(p, 30, "^")) &&
        (_bitwise_and = bitwise_and(p))
    ) ? ast_binary(p, _bitwise_xor, _bitwise_and, BINOP_XOR) : 0;
    return exit_frame(p, &f, res_39);
}

// bitwise_and (left_recursive):
//     | bitwise_and '&' shift_expr
//     | shift_expr
static ast_expr_t *bitwise_and(parser_t *p) {
    const frame_t f = {417, p->pos, FUNC};
    ast_expr_t *res_417 = 0;
    if (is_memoized(p, &f, (void **) &res_417)) {
        return res_417;
    }
    ast_expr_t *alt_417;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_417;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_417 = (
                (alt_417 = bitwise_and_1(p)) ||
                (alt_417 = shift_expr(p))
            ) ? alt_417 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_417 = max;
    }
    insert_memo(p, &f, res_417);
    return exit_frame(p, &f, res_417);
}

static ast_expr_t *bitwise_and_1(parser_t *p) {
    const frame_t f = {811, p->pos, FUNC};
    ast_expr_t *res_811;
    ast_expr_t *_bitwise_and;
    ast_expr_t *_shift_expr;
    res_811 = enter_frame(p, &f) && (
        (_bitwise_and = bitwise_and(p)) &&
        (consume(p, 28, "&")) &&
        (_shift_expr = shift_expr(p))
    ) ? ast_binary(p, _bitwise_and, _shift_expr, BINOP_AND) : 0;
    return exit_frame(p, &f, res_811);
}

// shift_expr (left_recursive):
//     | shift_expr '<<' sum
//     | shift_expr '>>' sum
//     | sum
static ast_expr_t *shift_expr(parser_t *p) {
    const frame_t f = {778, p->pos, FUNC};
    ast_expr_t *res_778 = 0;
    if (is_memoized(p, &f, (void **) &res_778)) {
        return res_778;
    }
    ast_expr_t *alt_778;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_778;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_778 = (
                (alt_778 = shift_expr_1(p)) ||
                (alt_778 = shift_expr_2(p)) ||
                (alt_778 = sum(p))
            ) ? alt_778 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_778 = max;
    }
    insert_memo(p, &f, res_778);
    return exit_frame(p, &f, res_778);
}

static ast_expr_t *shift_expr_1(parser_t *p) {
    const frame_t f = {484, p->pos, FUNC};
    ast_expr_t *res_484;
    ast_expr_t *_shift_expr;
    ast_expr_t *_sum;
    res_484 = enter_frame(p, &f) && (
        (_shift_expr = shift_expr(p)) &&
        (consume(p, 48, "<<")) &&
        (_sum = sum(p))
    ) ? ast_binary(p, _shift_expr, _sum, BINOP_SHL) : 0;
    return exit_frame(p, &f, res_484);
}

static ast_expr_t *shift_expr_2(parser_t *p) {
    const frame_t f = {485, p->pos, FUNC};
    ast_expr_t *res_485;
    ast_expr_t *_shift_expr;
    ast_expr_t *_sum;
    res_485 = enter_frame(p, &f) && (
        (_shift_expr = shift_expr(p)) &&
        (consume(p, 49, ">>")) &&
        (_sum = sum(p))
    ) ? ast_binary(p, _shift_expr, _sum, BINOP_SHR) : 0;
    return exit_frame(p, &f, res_485);
}

// sum (left_recursive):
//     | sum '+' term
//     | sum '-' term
//     | term
static ast_expr_t *sum(parser_t *p) {
    const frame_t f = {252, p->pos, FUNC};
    ast_expr_t *res_252 = 0;
    if (is_memoized(p, &f, (void **) &res_252)) {
        return res_252;
    }
    ast_expr_t *alt_252;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_252;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_252 = (
                (alt_252 = sum_1(p)) ||
                (alt_252 = sum_2(p)) ||
                (alt_252 = term(p))
            ) ? alt_252 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_252 = max;
    }
    insert_memo(p, &f, res_252);
    return exit_frame(p, &f, res_252);
}

static ast_expr_t *sum_1(parser_t *p) {
    const frame_t f = {205, p->pos, FUNC};
    ast_expr_t *res_205;
    ast_expr_t *_sum;
    ast_expr_t *_term;
    res_205 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 21, "+")) &&
        (_term = term(p))
    ) ? ast_binary(p, _sum, _term, BINOP_PLS) : 0;
    return exit_frame(p, &f, res_205);
}

static ast_expr_t *sum_2(parser_t *p) {
    const frame_t f = {208, p->pos, FUNC};
    ast_expr_t *res_208;
    ast_expr_t *_sum;
    ast_expr_t *_term;
    res_208 = enter_frame(p, &f) && (
        (_sum = sum(p)) &&
        (consume(p, 22, "-")) &&
        (_term = term(p))
    ) ? ast_binary(p, _sum, _term, BINOP_MIN) : 0;
    return exit_frame(p, &f, res_208);
}

// term (left_recursive):
//     | term '*' pipe_expr
//     | term '/' pipe_expr
//     | term '%' pipe_expr
//     | term '//' pipe_expr
//     | term '@' pipe_expr
//     | pipe_expr
static ast_expr_t *term(parser_t *p) {
    const frame_t f = {460, p->pos, FUNC};
    ast_expr_t *res_460 = 0;
    if (is_memoized(p, &f, (void **) &res_460)) {
        return res_460;
    }
    ast_expr_t *alt_460;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_460;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_460 = (
                (alt_460 = term_1(p)) ||
                (alt_460 = term_2(p)) ||
                (alt_460 = term_3(p)) ||
                (alt_460 = term_4(p)) ||
                (alt_460 = term_5(p)) ||
                (alt_460 = pipe_expr(p))
            ) ? alt_460 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_460 = max;
    }
    insert_memo(p, &f, res_460);
    return exit_frame(p, &f, res_460);
}

static ast_expr_t *term_1(parser_t *p) {
    const frame_t f = {758, p->pos, FUNC};
    ast_expr_t *res_758;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_758 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 23, "*")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_MUL) : 0;
    return exit_frame(p, &f, res_758);
}

static ast_expr_t *term_2(parser_t *p) {
    const frame_t f = {759, p->pos, FUNC};
    ast_expr_t *res_759;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_759 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 24, "/")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_DIV) : 0;
    return exit_frame(p, &f, res_759);
}

static ast_expr_t *term_3(parser_t *p) {
    const frame_t f = {760, p->pos, FUNC};
    ast_expr_t *res_760;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_760 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 25, "%")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_MOD) : 0;
    return exit_frame(p, &f, res_760);
}

static ast_expr_t *term_4(parser_t *p) {
    const frame_t f = {761, p->pos, FUNC};
    ast_expr_t *res_761;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_761 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 37, "//")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_FDV) : 0;
    return exit_frame(p, &f, res_761);
}

static ast_expr_t *term_5(parser_t *p) {
    const frame_t f = {762, p->pos, FUNC};
    ast_expr_t *res_762;
    ast_expr_t *_term;
    ast_expr_t *_pipe_expr;
    res_762 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 26, "@")) &&
        (_pipe_expr = pipe_expr(p))
    ) ? ast_binary(p, _term, _pipe_expr, BINOP_MML) : 0;
    return exit_frame(p, &f, res_762);
}

// pipe_expr (left_recursive):
//     | pipe_expr '->' factor
//     | factor
static ast_expr_t *pipe_expr(parser_t *p) {
    const frame_t f = {510, p->pos, FUNC};
    ast_expr_t *res_510 = 0;
    if (is_memoized(p, &f, (void **) &res_510)) {
        return res_510;
    }
    ast_expr_t *alt_510;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_510;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_510 = (
                (alt_510 = pipe_expr_1(p)) ||
                (alt_510 = factor(p))
            ) ? alt_510 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_510 = max;
    }
    insert_memo(p, &f, res_510);
    return exit_frame(p, &f, res_510);
}

static ast_expr_t *pipe_expr_1(parser_t *p) {
    const frame_t f = {304, p->pos, FUNC};
    ast_expr_t *res_304;
    ast_expr_t *_pipe_expr;
    ast_expr_t *_factor;
    res_304 = enter_frame(p, &f) && (
        (_pipe_expr = pipe_expr(p)) &&
        (consume(p, 35, "->")) &&
        (_factor = factor(p))
    ) ? ast_binary(p, _pipe_expr, _factor, BINOP_PIP) : 0;
    return exit_frame(p, &f, res_304);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static ast_expr_t *factor(parser_t *p) {
    const frame_t f = {983, p->pos, FUNC};
    ast_expr_t *res_983;
    ast_expr_t *alt_983;
    res_983 = enter_frame(p, &f) && (
        (alt_983 = factor_1(p)) ||
        (alt_983 = factor_2(p)) ||
        (alt_983 = factor_3(p)) ||
        (alt_983 = power(p))
    ) ? alt_983 : 0;
    return exit_frame(p, &f, res_983);
}

static ast_expr_t *factor_1(parser_t *p) {
    const frame_t f = {609, p->pos, FUNC};
    ast_expr_t *res_609;
    ast_expr_t *_factor;
    res_609 = enter_frame(p, &f) && (
        (consume(p, 21, "+")) &&
        (_factor = factor(p))
    ) ? ast_unary(p, _factor, UNARY_PLS) : 0;
    return exit_frame(p, &f, res_609);
}

static ast_expr_t *factor_2(parser_t *p) {
    const frame_t f = {610, p->pos, FUNC};
    ast_expr_t *res_610;
    ast_expr_t *_factor;
    res_610 = enter_frame(p, &f) && (
        (consume(p, 22, "-")) &&
        (_factor = factor(p))
    ) ? ast_unary(p, _factor, UNARY_MIN) : 0;
    return exit_frame(p, &f, res_610);
}

static ast_expr_t *factor_3(parser_t *p) {
    const frame_t f = {611, p->pos, FUNC};
    ast_expr_t *res_611;
    ast_expr_t *_factor;
    res_611 = enter_frame(p, &f) && (
        (consume(p, 29, "~")) &&
        (_factor = factor(p))
    ) ? ast_unary(p, _factor, UNARY_INV) : 0;
    return exit_frame(p, &f, res_611);
}

// power:
//     | primary '**' factor
//     | primary
static ast_expr_t *power(parser_t *p) {
    const frame_t f = {757, p->pos, FUNC};
    ast_expr_t *res_757;
    ast_primary_t *_primary;
    ast_expr_t *alt_757;
    res_757 = enter_frame(p, &f) && (
        (alt_757 = power_1(p)) || (
            (_primary = primary(p)) &&
            (alt_757 = ast_primary_expr(p, _primary)))
    ) ? alt_757 : 0;
    return exit_frame(p, &f, res_757);
}

static ast_expr_t *power_1(parser_t *p) {
    const frame_t f = {367, p->pos, FUNC};
    ast_expr_t *res_367;
    ast_primary_t *_primary;
    ast_expr_t *_factor;
    res_367 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (consume(p, 38, "**")) &&
        (_factor = factor(p))
    ) ? ast_binary(p, ast_primary_expr(p, _primary), _factor, BINOP_POW) : 0;
    return exit_frame(p, &f, res_367);
}

// primary (left_recursive):
//     | primary '.' NAME
//     | primary invocation
//     | primary subscript
//     | atom
static ast_primary_t *primary(parser_t *p) {
    const frame_t f = {178, p->pos, FUNC};
    ast_primary_t *res_178 = 0;
    if (is_memoized(p, &f, (void **) &res_178)) {
        return res_178;
    }
    ast_primary_t *alt_178;
    size_t maxpos;
    ast_primary_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_178;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_178 = (
                (alt_178 = primary_1(p)) ||
                (alt_178 = primary_2(p)) ||
                (alt_178 = primary_3(p)) ||
                (alt_178 = atom(p))
            ) ? alt_178 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_178 = max;
    }
    insert_memo(p, &f, res_178);
    return exit_frame(p, &f, res_178);
}

static ast_primary_t *primary_1(parser_t *p) {
    const frame_t f = {772, p->pos, FUNC};
    ast_primary_t *res_772;
    ast_primary_t *_primary;
    token_t *_name;
    res_772 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (consume(p, 6, ".")) &&
        (_name = consume(p, 3, "NAME"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_772);
}

static ast_primary_t *primary_2(parser_t *p) {
    const frame_t f = {773, p->pos, FUNC};
    ast_primary_t *res_773;
    ast_primary_t *_primary;
    void *_invocation;
    res_773 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (_invocation = invocation(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_773);
}

static ast_primary_t *primary_3(parser_t *p) {
    const frame_t f = {774, p->pos, FUNC};
    ast_primary_t *res_774;
    ast_primary_t *_primary;
    ast_list_t *_subscript;
    res_774 = enter_frame(p, &f) && (
        (_primary = primary(p)) &&
        (_subscript = subscript(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_774);
}

// tuple_atom:
//     | '(' [list_items] ')'
static ast_primary_t *tuple_atom(parser_t *p) {
    const frame_t f = {672, p->pos, FUNC};
    ast_primary_t *res_672;
    ast_list_t *_list_items;
    res_672 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_list_items = list_items(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_672);
}

// list_atom:
//     | '[' [list_items] ']'
static ast_primary_t *list_atom(parser_t *p) {
    const frame_t f = {738, p->pos, FUNC};
    ast_primary_t *res_738;
    ast_list_t *_list_items;
    res_738 = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (_list_items = list_items(p), 1) &&
        (consume(p, 18, "]"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_738);
}

// builder:
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
static ast_primary_t *builder(parser_t *p) {
    const frame_t f = {667, p->pos, FUNC};
    ast_primary_t *res_667;
    ast_primary_t *alt_667;
    res_667 = enter_frame(p, &f) && (
        (alt_667 = builder_1(p)) ||
        (alt_667 = builder_2(p))
    ) ? alt_667 : 0;
    return exit_frame(p, &f, res_667);
}

static ast_primary_t *builder_1(parser_t *p) {
    const frame_t f = {589, p->pos, FUNC};
    ast_primary_t *res_589;
    token_t *_name;
    ast_list_t *_simple_args;
    ast_expr_t *_expr;
    res_589 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_simple_args = simple_args(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_589);
}

static ast_primary_t *builder_2(parser_t *p) {
    const frame_t f = {590, p->pos, FUNC};
    ast_primary_t *res_590;
    token_t *_name;
    ast_list_t *_builder_hint;
    void *_builder_args;
    void *_block_suite;
    res_590 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_builder_hint = builder_hint(p), 1) &&
        (_builder_args = builder_args(p), 1) &&
        (_block_suite = block_suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_590);
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
static ast_primary_t *atom(parser_t *p) {
    const frame_t f = {753, p->pos, FUNC};
    ast_primary_t *res_753;
    token_t *_name;
    token_t *_number;
    token_t *_string;
    ast_primary_t *alt_753;
    res_753 = enter_frame(p, &f) && (
        (alt_753 = tuple_atom(p)) ||
        (alt_753 = list_atom(p)) ||
        (alt_753 = builder(p)) || (
            (_name = consume(p, 3, "NAME")) &&
            (alt_753 = ast_name_atom(p, _name))
        ) || (
            (_number = consume(p, 4, "NUMBER")) &&
            (alt_753 = ast_number_atom(p, _number))
        ) || (
            (_string = consume(p, 5, "STRING")) &&
            (alt_753 = ast_string_atom(p, _string))
        ) || (
            (consume(p, 81, "None")) &&
            (alt_753 = ast_none(p))
        ) || (
            (consume(p, 82, "True")) &&
            (alt_753 = ast_true(p))
        ) || (
            (consume(p, 83, "False")) &&
            (alt_753 = ast_false(p)))
    ) ? alt_753 : 0;
    return exit_frame(p, &f, res_753);
}
