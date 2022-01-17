#include "include/ast.h"


static ast_list_t *single_input(parser_t *);
static ast_list_t *single_input_3(parser_t *);
static ast_list_t *file_input(parser_t *);
static ast_list_t *eval_input(parser_t *);
static ast_list_t *statement_list(parser_t *);
static ast_list_t *line_statement_loop(parser_t *);
static ast_list_t *line_statement(parser_t *);
static ast_list_t *line_statement_1(parser_t *);
static ast_list_t *line_statement_2(parser_t *);
static ast_list_t *simple_statements(parser_t *);
static ast_list_t *simple_statement_delimited(parser_t *);
static ast_stmt_t *simple_statement(parser_t *);
static ast_stmt_t *simple_statement_4(parser_t *);
static ast_stmt_t *simple_statement_5(parser_t *);
static ast_expr_t *simple_statement_5_3(parser_t *);
static ast_stmt_t *simple_statement_6(parser_t *);
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
static void *assignment_1(parser_t *);
static void *assignment_1_4(parser_t *);
static void *assignment_2(parser_t *);
static void *assignment_3(parser_t *);
static ast_list_t *assignment_3_1_loop(parser_t *);
static void *assignment_3_1(parser_t *);
static int *augmented_assign(parser_t *);
static void *compound_statement(parser_t *);
static void *if_statement(parser_t *);
static ast_list_t *elif_statement_loop(parser_t *);
static void *elif_statement(parser_t *);
static void *while_statement(parser_t *);
static void *for_statement(parser_t *);
static void *try_statement(parser_t *);
static void *try_statement_3(parser_t *);
static void *with_statement(parser_t *);
static ast_list_t *expr_as_name_delimited(parser_t *);
static void *expr_as_name(parser_t *);
static token_t *expr_as_name_2(parser_t *);
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
static ast_named_t *named_expression(parser_t *);
static ast_named_t *named_expression_1(parser_t *);
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
static int *comparator(parser_t *);
static int *comparator_8(parser_t *);
static int *comparator_10(parser_t *);
static ast_expr_t *bitwise_or(parser_t *);
static ast_expr_t *bitwise_or_1(parser_t *);
static ast_expr_t *bitwise_xor(parser_t *);
static ast_expr_t *bitwise_xor_1(parser_t *);
static ast_expr_t *bitwise_and(parser_t *);
static ast_expr_t *bitwise_and_1(parser_t *);
static ast_expr_t *bitwise_shift(parser_t *);
static ast_expr_t *bitwise_shift_1(parser_t *);
static ast_expr_t *bitwise_shift_2(parser_t *);
static ast_expr_t *sum(parser_t *);
static ast_expr_t *sum_1(parser_t *);
static ast_expr_t *sum_2(parser_t *);
static ast_expr_t *term(parser_t *);
static ast_expr_t *term_1(parser_t *);
static ast_expr_t *term_2(parser_t *);
static ast_expr_t *term_3(parser_t *);
static ast_expr_t *term_4(parser_t *);
static ast_expr_t *term_5(parser_t *);
static ast_expr_t *pipeline(parser_t *);
static ast_expr_t *pipeline_1(parser_t *);
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
static ast_primary_t *paren_expression(parser_t *);
static ast_primary_t *list_expression(parser_t *);
static ast_primary_t *builder_expression(parser_t *);
static ast_primary_t *builder_expression_1(parser_t *);
static ast_primary_t *builder_expression_2(parser_t *);
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
//     | simple_statements
//     | compound_statement NEWLINE
static ast_list_t *single_input(parser_t *p) {
    const frame_t f = {251, p->pos, FUNC};
    ast_list_t *res_251;
    ast_list_t *_simple_statements;
    ast_list_t *alt_251;
    res_251 = enter_frame(p, &f) && ((
            (consume(p, 2, "NEWLINE")) &&
            (alt_251 = ast_list_of(p, ast_nop(p)))
        ) || (
            (_simple_statements = simple_statements(p)) &&
            (alt_251 = ast_list_of(p, _simple_statements))
        ) ||
        (alt_251 = single_input_3(p))
    ) ? alt_251 : 0;
    return exit_frame(p, &f, res_251);
}

// compound_statement NEWLINE
static ast_list_t *single_input_3(parser_t *p) {
    const frame_t f = {423, p->pos, FUNC};
    ast_list_t *res_423;
    void *_compound_statement;
    res_423 = enter_frame(p, &f) && (
        (_compound_statement = compound_statement(p)) &&
        (consume(p, 2, "NEWLINE"))
    ) ? ast_list_of(p, _compound_statement) : 0;
    return exit_frame(p, &f, res_423);
}

// file_input:
//     | statement_list
static ast_list_t *file_input(parser_t *p) {
    const frame_t f = {535, p->pos, FUNC};
    ast_list_t *res_535;
    ast_list_t *_statement_list;
    res_535 = enter_frame(p, &f) && (
        (_statement_list = statement_list(p))
    ) ? _statement_list : 0;
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

// statement_list:
//     | line_statement+
static ast_list_t *statement_list(parser_t *p) {
    const frame_t f = {398, p->pos, FUNC};
    ast_list_t *res_398;
    ast_list_t *_line_statements;
    res_398 = enter_frame(p, &f) && (
        (_line_statements = line_statement_loop(p))
    ) ? _line_statements : 0;
    return exit_frame(p, &f, res_398);
}

static ast_list_t *line_statement_loop(parser_t *p) {
    ast_list_t *_line_statement = line_statement(p);
    if (!_line_statement) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    do {
        ast_list_append(p, list, _line_statement);
    } while ((_line_statement = line_statement(p)));
    return list;
}

// line_statement:
//     | simple_statements NEWLINE
//     | compound_statement NEWLINE
static ast_list_t *line_statement(parser_t *p) {
    const frame_t f = {260, p->pos, FUNC};
    ast_list_t *res_260;
    ast_list_t *alt_260;
    res_260 = enter_frame(p, &f) && (
        (alt_260 = line_statement_1(p)) ||
        (alt_260 = line_statement_2(p))
    ) ? alt_260 : 0;
    return exit_frame(p, &f, res_260);
}

// simple_statements NEWLINE
static ast_list_t *line_statement_1(parser_t *p) {
    const frame_t f = {726, p->pos, FUNC};
    ast_list_t *res_726;
    ast_list_t *_simple_statements;
    res_726 = enter_frame(p, &f) && (
        (_simple_statements = simple_statements(p)) &&
        (consume(p, 2, "NEWLINE"))
    ) ? _simple_statements : 0;
    return exit_frame(p, &f, res_726);
}

// compound_statement NEWLINE
static ast_list_t *line_statement_2(parser_t *p) {
    const frame_t f = {727, p->pos, FUNC};
    ast_list_t *res_727;
    void *_compound_statement;
    res_727 = enter_frame(p, &f) && (
        (_compound_statement = compound_statement(p)) &&
        (consume(p, 2, "NEWLINE"))
    ) ? ast_list_of(p, _compound_statement) : 0;
    return exit_frame(p, &f, res_727);
}

// simple_statements:
//     | ';'.simple_statement+ [';']
static ast_list_t *simple_statements(parser_t *p) {
    const frame_t f = {129, p->pos, FUNC};
    ast_list_t *res_129;
    ast_list_t *_simple_statements;
    res_129 = enter_frame(p, &f) && (
        (_simple_statements = simple_statement_delimited(p)) &&
        (consume(p, 12, ";"), 1)
    ) ? _simple_statements : 0;
    return exit_frame(p, &f, res_129);
}

static ast_list_t *simple_statement_delimited(parser_t *p) {
    ast_stmt_t *_simple_statement = simple_statement(p);
    if (!_simple_statement) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _simple_statement);
        pos = p->pos;
    } while (consume(p, 12, ";") &&
            (_simple_statement = simple_statement(p)));
    p->pos = pos;
    return list;
}

// simple_statement:
//     | 'pass'
//     | 'break'
//     | 'continue'
//     | 'return' [exprlist_star]
//     | 'raise' expr ['from' expr]
//     | 'del' targetlist
//     | assignment
static ast_stmt_t *simple_statement(parser_t *p) {
    const frame_t f = {930, p->pos, FUNC};
    ast_stmt_t *res_930;
    ast_stmt_t *alt_930;
    res_930 = enter_frame(p, &f) && ((
            (consume(p, 64, "pass")) &&
            (alt_930 = ast_nop(p))
        ) || (
            (consume(p, 74, "break")) &&
            (alt_930 = ast_break(p))
        ) || (
            (consume(p, 73, "continue")) &&
            (alt_930 = ast_continue(p))
        ) ||
        (alt_930 = simple_statement_4(p)) ||
        (alt_930 = simple_statement_5(p)) ||
        (alt_930 = simple_statement_6(p)) ||
        (alt_930 = assignment(p))
    ) ? alt_930 : 0;
    return exit_frame(p, &f, res_930);
}

// 'return' [exprlist_star]
static ast_stmt_t *simple_statement_4(parser_t *p) {
    const frame_t f = {391, p->pos, FUNC};
    ast_stmt_t *res_391;
    ast_list_t *_exprlist_star;
    res_391 = enter_frame(p, &f) && (
        (consume(p, 54, "return")) &&
        (_exprlist_star = exprlist_star(p), 1)
    ) ? ast_return(p, _exprlist_star) : 0;
    return exit_frame(p, &f, res_391);
}

// 'raise' expr ['from' expr]
static ast_stmt_t *simple_statement_5(parser_t *p) {
    const frame_t f = {392, p->pos, FUNC};
    ast_stmt_t *res_392;
    res_392 = enter_frame(p, &f) && (
        (consume(p, 78, "raise")) &&
        (expr(p)) &&
        (simple_statement_5_3(p), 1)
    ) ? ast_nop(p) : 0;
    return exit_frame(p, &f, res_392);
}

// 'from' expr
static ast_expr_t *simple_statement_5_3(parser_t *p) {
    const frame_t f = {276, p->pos, FUNC};
    ast_expr_t *res_276;
    ast_expr_t *_expr;
    res_276 = enter_frame(p, &f) && (
        (consume(p, 66, "from")) &&
        (_expr = expr(p))
    ) ? _expr : 0;
    return exit_frame(p, &f, res_276);
}

// 'del' targetlist
static ast_stmt_t *simple_statement_6(parser_t *p) {
    const frame_t f = {393, p->pos, FUNC};
    ast_stmt_t *res_393;
    ast_list_t *_targetlist;
    res_393 = enter_frame(p, &f) && (
        (consume(p, 79, "del")) &&
        (_targetlist = targetlist(p))
    ) ? ast_del(p, _targetlist) : 0;
    return exit_frame(p, &f, res_393);
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

// target (memo):
//     | t_primary '.' NAME !t_lookahead
//     | t_primary subscript !t_lookahead
//     | NAME
//     | '(' targetlist ')'
static void *target(parser_t *p) {
    const frame_t f = {161, p->pos, FUNC};
    void *res_161;
    if (is_memoized(p, &f, (void **) &res_161)) {
        return res_161;
    }
    void *alt_161;
    res_161 = enter_frame(p, &f) && (
        (alt_161 = target_1(p)) ||
        (alt_161 = target_2(p)) ||
        (alt_161 = consume(p, 3, "NAME")) ||
        (alt_161 = target_4(p))
    ) ? alt_161 : 0;
    insert_memo(p, &f, res_161);
    return exit_frame(p, &f, res_161);
}

// t_primary '.' NAME !t_lookahead
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

// t_primary subscript !t_lookahead
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

// '(' targetlist ')'
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

// t_primary '.' NAME &t_lookahead
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

// t_primary invocation &t_lookahead
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

// t_primary subscript &t_lookahead
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

// atom &t_lookahead
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

// [expr] slice_expr [slice_expr]
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
    ) ? _expr : 0;
    return exit_frame(p, &f, res_210);
}

// list_item:
//     | star_expr
//     | named_expression
static void *list_item(parser_t *p) {
    const frame_t f = {756, p->pos, FUNC};
    void *res_756;
    void *alt_756;
    res_756 = enter_frame(p, &f) && (
        (alt_756 = star_expr(p)) ||
        (alt_756 = named_expression(p))
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
//     | target ':' expr ['=' exprlist]
//     | target augmented_assign exprlist
//     | (targetlist '=')* exprlist_star
static void *assignment(parser_t *p) {
    const frame_t f = {733, p->pos, FUNC};
    void *res_733;
    void *alt_733;
    res_733 = enter_frame(p, &f) && (
        (alt_733 = assignment_1(p)) ||
        (alt_733 = assignment_2(p)) ||
        (alt_733 = assignment_3(p))
    ) ? alt_733 : 0;
    return exit_frame(p, &f, res_733);
}

// target ':' expr ['=' exprlist]
static void *assignment_1(parser_t *p) {
    const frame_t f = {327, p->pos, FUNC};
    void *res_327;
    void *_target;
    ast_expr_t *_expr;
    void *_assign_exprlist;
    res_327 = enter_frame(p, &f) && (
        (_target = target(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p)) &&
        (_assign_exprlist = assignment_1_4(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_327);
}

// '=' exprlist
static void *assignment_1_4(parser_t *p) {
    const frame_t f = {508, p->pos, FUNC};
    void *res_508;
    ast_list_t *_exprlist;
    res_508 = enter_frame(p, &f) && (
        (consume(p, 8, "=")) &&
        (_exprlist = exprlist(p))
    ) ? _exprlist : 0;
    return exit_frame(p, &f, res_508);
}

// target augmented_assign exprlist
static void *assignment_2(parser_t *p) {
    const frame_t f = {328, p->pos, FUNC};
    void *res_328;
    void *_target;
    int *_augmented_assign;
    ast_list_t *_exprlist;
    res_328 = enter_frame(p, &f) && (
        (_target = target(p)) &&
        (_augmented_assign = augmented_assign(p)) &&
        (_exprlist = exprlist(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_328);
}

// (targetlist '=')* exprlist_star
static void *assignment_3(parser_t *p) {
    const frame_t f = {329, p->pos, FUNC};
    void *res_329;
    ast_list_t *_targetlist_assigns;
    ast_list_t *_exprlist_star;
    res_329 = enter_frame(p, &f) && (
        (_targetlist_assigns = assignment_3_1_loop(p)) &&
        (_exprlist_star = exprlist_star(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_329);
}

static ast_list_t *assignment_3_1_loop(parser_t *p) {
    ast_list_t *list = ast_list_new(p);
    void *_targetlist_assign;
    while ((_targetlist_assign = assignment_3_1(p))) {
        ast_list_append(p, list, _targetlist_assign);
    }
    return list;
}

// targetlist '='
static void *assignment_3_1(parser_t *p) {
    const frame_t f = {427, p->pos, FUNC};
    void *res_427;
    ast_list_t *_targetlist;
    res_427 = enter_frame(p, &f) && (
        (_targetlist = targetlist(p)) &&
        (consume(p, 8, "="))
    ) ? _targetlist : 0;
    return exit_frame(p, &f, res_427);
}

// augmented_assign:
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
static int *augmented_assign(parser_t *p) {
    const frame_t f = {982, p->pos, FUNC};
    int *res_982;
    int *alt_982;
    res_982 = enter_frame(p, &f) && ((
            (consume(p, 39, "+=")) &&
            (alt_982 = ast_integer(p, BINOP_PLS))
        ) || (
            (consume(p, 40, "-=")) &&
            (alt_982 = ast_integer(p, BINOP_MIN))
        ) || (
            (consume(p, 41, "*=")) &&
            (alt_982 = ast_integer(p, BINOP_MUL))
        ) || (
            (consume(p, 42, "/=")) &&
            (alt_982 = ast_integer(p, BINOP_DIV))
        ) || (
            (consume(p, 43, "%=")) &&
            (alt_982 = ast_integer(p, BINOP_MOD))
        ) || (
            (consume(p, 44, "@=")) &&
            (alt_982 = ast_integer(p, BINOP_MML))
        ) || (
            (consume(p, 45, "|=")) &&
            (alt_982 = ast_integer(p, BINOP_IOR))
        ) || (
            (consume(p, 46, "&=")) &&
            (alt_982 = ast_integer(p, BINOP_AND))
        ) || (
            (consume(p, 47, "^=")) &&
            (alt_982 = ast_integer(p, BINOP_XOR))
        ) || (
            (consume(p, 50, "//=")) &&
            (alt_982 = ast_integer(p, BINOP_FDV))
        ) || (
            (consume(p, 51, "**=")) &&
            (alt_982 = ast_integer(p, BINOP_POW))
        ) || (
            (consume(p, 52, "<<=")) &&
            (alt_982 = ast_integer(p, BINOP_SHL))
        ) || (
            (consume(p, 53, ">>=")) &&
            (alt_982 = ast_integer(p, BINOP_SHR)))
    ) ? alt_982 : 0;
    return exit_frame(p, &f, res_982);
}

// compound_statement:
//     | if_statement
//     | while_statement
//     | for_statement
//     | try_statement
//     | with_statement
static void *compound_statement(parser_t *p) {
    const frame_t f = {147, p->pos, FUNC};
    void *res_147;
    void *alt_147;
    res_147 = enter_frame(p, &f) && (
        (alt_147 = if_statement(p)) ||
        (alt_147 = while_statement(p)) ||
        (alt_147 = for_statement(p)) ||
        (alt_147 = try_statement(p)) ||
        (alt_147 = with_statement(p))
    ) ? alt_147 : 0;
    return exit_frame(p, &f, res_147);
}

// if_statement (inline):
//     | 'if' named_expression suite elif_statement* [else_suite]
static void *if_statement(parser_t *p) {
    const frame_t f = {621, p->pos, FUNC};
    void *res_621;
    ast_named_t *_named_expression;
    void *_suite;
    ast_list_t *_elif_statements;
    void *_else_suite;
    res_621 = enter_frame(p, &f) && (
        (consume(p, 56, "if")) &&
        (_named_expression = named_expression(p)) &&
        (_suite = suite(p)) &&
        (_elif_statements = elif_statement_loop(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_621);
}

static ast_list_t *elif_statement_loop(parser_t *p) {
    ast_list_t *list = ast_list_new(p);
    void *_elif_statement;
    while ((_elif_statement = elif_statement(p))) {
        ast_list_append(p, list, _elif_statement);
    }
    return list;
}

// elif_statement:
//     | 'elif' named_expression suite
static void *elif_statement(parser_t *p) {
    const frame_t f = {660, p->pos, FUNC};
    void *res_660;
    ast_named_t *_named_expression;
    void *_suite;
    res_660 = enter_frame(p, &f) && (
        (consume(p, 57, "elif")) &&
        (_named_expression = named_expression(p)) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_660);
}

// while_statement:
//     | 'while' named_expression suite [else_suite]
static void *while_statement(parser_t *p) {
    const frame_t f = {865, p->pos, FUNC};
    void *res_865;
    ast_named_t *_named_expression;
    void *_suite;
    void *_else_suite;
    res_865 = enter_frame(p, &f) && (
        (consume(p, 71, "while")) &&
        (_named_expression = named_expression(p)) &&
        (_suite = suite(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_865);
}

// for_statement:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
static void *for_statement(parser_t *p) {
    const frame_t f = {465, p->pos, FUNC};
    void *res_465;
    ast_list_t *_targetlist;
    ast_list_t *_exprlist;
    void *_suite;
    void *_else_suite;
    res_465 = enter_frame(p, &f) && (
        (consume(p, 72, "for")) &&
        (_targetlist = targetlist(p)) &&
        (consume(p, 63, "in")) &&
        (_exprlist = exprlist(p)) &&
        (_suite = suite(p)) &&
        (_else_suite = else_suite(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_465);
}

// try_statement:
//     | 'try' suite (except_suite | finally_suite)
static void *try_statement(parser_t *p) {
    const frame_t f = {195, p->pos, FUNC};
    void *res_195;
    void *_suite;
    void *_except_suite_or_finally_suite;
    res_195 = enter_frame(p, &f) && (
        (consume(p, 75, "try")) &&
        (_suite = suite(p)) &&
        (_except_suite_or_finally_suite = try_statement_3(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_195);
}

// except_suite | finally_suite
static void *try_statement_3(parser_t *p) {
    const frame_t f = {663, p->pos, FUNC};
    void *res_663;
    void *alt_663;
    res_663 = enter_frame(p, &f) && (
        (alt_663 = except_suite(p)) ||
        (alt_663 = finally_suite(p))
    ) ? alt_663 : 0;
    return exit_frame(p, &f, res_663);
}

// with_statement:
//     | 'with' ','.expr_as_name+ suite
static void *with_statement(parser_t *p) {
    const frame_t f = {214, p->pos, FUNC};
    void *res_214;
    ast_list_t *_expr_as_names;
    void *_suite;
    res_214 = enter_frame(p, &f) && (
        (consume(p, 68, "with")) &&
        (_expr_as_names = expr_as_name_delimited(p)) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_214);
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
    token_t *_as_name;
    res_782 = enter_frame(p, &f) && (
        (_expr = expr(p)) &&
        (_as_name = expr_as_name_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_782);
}

// 'as' NAME
static token_t *expr_as_name_2(parser_t *p) {
    const frame_t f = {121, p->pos, FUNC};
    token_t *res_121;
    token_t *_name;
    res_121 = enter_frame(p, &f) && (
        (consume(p, 65, "as")) &&
        (_name = consume(p, 3, "NAME"))
    ) ? _name : 0;
    return exit_frame(p, &f, res_121);
}

// block_suite:
//     | '{' NEWLINE statement_list '}'
//     | '{' [simple_statements] '}'
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

// '{' NEWLINE statement_list '}'
static void *block_suite_1(parser_t *p) {
    const frame_t f = {560, p->pos, FUNC};
    void *res_560;
    token_t *_newline;
    ast_list_t *_statement_list;
    res_560 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_newline = consume(p, 2, "NEWLINE")) &&
        (_statement_list = statement_list(p)) &&
        (consume(p, 16, "}"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_560);
}

// '{' [simple_statements] '}'
static void *block_suite_2(parser_t *p) {
    const frame_t f = {561, p->pos, FUNC};
    void *res_561;
    ast_list_t *_simple_statements;
    res_561 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (_simple_statements = simple_statements(p), 1) &&
        (consume(p, 16, "}"))
    ) ? _simple_statements : 0;
    return exit_frame(p, &f, res_561);
}

// suite:
//     | ':' simple_statements
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

// ':' simple_statements
static void *suite_1(parser_t *p) {
    const frame_t f = {98, p->pos, FUNC};
    void *res_98;
    ast_list_t *_simple_statements;
    res_98 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_simple_statements = simple_statements(p))
    ) ? _simple_statements : 0;
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
    const frame_t f = {357, p->pos, FUNC};
    void *res_357;
    void *_expr_as_name;
    void *_suite;
    res_357 = enter_frame(p, &f) && (
        (consume(p, 76, "except")) &&
        (_expr_as_name = expr_as_name(p), 1) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_357);
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

// ','.call_arg+ [',']
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

// NAME ':=' expr
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

// NAME '=' expr
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

// '**' expr
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

// '*' expr
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

// ',' [kwargs | args_kwargs]
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

// kwargs | args_kwargs
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

// ',' default_arg
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

// ',' [kwargs]
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

// '=' expr
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

// ':' expr
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

// '=' expr
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

// named_expression:
//     | NAME ':=' expr
//     | expr
static ast_named_t *named_expression(parser_t *p) {
    const frame_t f = {358, p->pos, FUNC};
    ast_named_t *res_358;
    ast_expr_t *_expr;
    ast_named_t *alt_358;
    res_358 = enter_frame(p, &f) && (
        (alt_358 = named_expression_1(p)) || (
            (_expr = expr(p)) &&
            (alt_358 = ast_unnamed(p, _expr)))
    ) ? alt_358 : 0;
    return exit_frame(p, &f, res_358);
}

// NAME ':=' expr
static ast_named_t *named_expression_1(parser_t *p) {
    const frame_t f = {352, p->pos, FUNC};
    ast_named_t *res_352;
    token_t *_name;
    ast_expr_t *_expr;
    res_352 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (_expr = expr(p))
    ) ? ast_named(p, _name, _expr) : 0;
    return exit_frame(p, &f, res_352);
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

// disjunction 'or' conjunction
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

// conjunction 'and' inversion
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

// 'not' inversion
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
//     | bitwise_or (comparator bitwise_or)+
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

// bitwise_or (comparator bitwise_or)+
static ast_expr_t *comparison_1(parser_t *p) {
    const frame_t f = {307, p->pos, FUNC};
    ast_expr_t *res_307;
    ast_expr_t *_bitwise_or;
    ast_list_t *_comparator_bitwise_ors;
    res_307 = enter_frame(p, &f) && (
        (_bitwise_or = bitwise_or(p)) &&
        (_comparator_bitwise_ors = comparison_1_2_loop(p))
    ) ? ast_comparison(p, _bitwise_or, _comparator_bitwise_ors) : 0;
    return exit_frame(p, &f, res_307);
}

static ast_list_t *comparison_1_2_loop(parser_t *p) {
    ast_expr_t *_comparator_bitwise_or = comparison_1_2(p);
    if (!_comparator_bitwise_or) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    do {
        ast_list_append(p, list, _comparator_bitwise_or);
    } while ((_comparator_bitwise_or = comparison_1_2(p)));
    return list;
}

// comparator bitwise_or
static ast_expr_t *comparison_1_2(parser_t *p) {
    const frame_t f = {742, p->pos, FUNC};
    ast_expr_t *res_742;
    int *_comparator;
    ast_expr_t *_bitwise_or;
    res_742 = enter_frame(p, &f) && (
        (_comparator = comparator(p)) &&
        (_bitwise_or = bitwise_or(p))
    ) ? ast_comp_term(p, _comparator, _bitwise_or) : 0;
    return exit_frame(p, &f, res_742);
}

// comparator:
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
static int *comparator(parser_t *p) {
    const frame_t f = {166, p->pos, FUNC};
    int *res_166;
    int *alt_166;
    res_166 = enter_frame(p, &f) && ((
            (consume(p, 19, "<")) &&
            (alt_166 = ast_integer(p, CMP_LT))
        ) || (
            (consume(p, 20, ">")) &&
            (alt_166 = ast_integer(p, CMP_GT))
        ) || (
            (consume(p, 31, "==")) &&
            (alt_166 = ast_integer(p, CMP_EQ))
        ) || (
            (consume(p, 34, ">=")) &&
            (alt_166 = ast_integer(p, CMP_GE))
        ) || (
            (consume(p, 33, "<=")) &&
            (alt_166 = ast_integer(p, CMP_LE))
        ) || (
            (consume(p, 32, "!=")) &&
            (alt_166 = ast_integer(p, CMP_NE))
        ) || (
            (consume(p, 63, "in")) &&
            (alt_166 = ast_integer(p, CMP_IN))
        ) ||
        (alt_166 = comparator_8(p)) || (
            (consume(p, 62, "is")) &&
            (alt_166 = ast_integer(p, CMP_IS))
        ) ||
        (alt_166 = comparator_10(p))
    ) ? alt_166 : 0;
    return exit_frame(p, &f, res_166);
}

// 'not' 'in'
static int *comparator_8(parser_t *p) {
    const frame_t f = {472, p->pos, FUNC};
    int *res_472;
    res_472 = enter_frame(p, &f) && (
        (consume(p, 61, "not")) &&
        (consume(p, 63, "in"))
    ) ? ast_integer(p, CMP_NI) : 0;
    return exit_frame(p, &f, res_472);
}

// 'is' 'not'
static int *comparator_10(parser_t *p) {
    const frame_t f = {432, p->pos, FUNC};
    int *res_432;
    res_432 = enter_frame(p, &f) && (
        (consume(p, 62, "is")) &&
        (consume(p, 61, "not"))
    ) ? ast_integer(p, CMP_NS) : 0;
    return exit_frame(p, &f, res_432);
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

// bitwise_or '|' bitwise_xor
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

// bitwise_xor '^' bitwise_and
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
//     | bitwise_and '&' bitwise_shift
//     | bitwise_shift
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
                (alt_417 = bitwise_shift(p))
            ) ? alt_417 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_417 = max;
    }
    insert_memo(p, &f, res_417);
    return exit_frame(p, &f, res_417);
}

// bitwise_and '&' bitwise_shift
static ast_expr_t *bitwise_and_1(parser_t *p) {
    const frame_t f = {811, p->pos, FUNC};
    ast_expr_t *res_811;
    ast_expr_t *_bitwise_and;
    ast_expr_t *_bitwise_shift;
    res_811 = enter_frame(p, &f) && (
        (_bitwise_and = bitwise_and(p)) &&
        (consume(p, 28, "&")) &&
        (_bitwise_shift = bitwise_shift(p))
    ) ? ast_binary(p, _bitwise_and, _bitwise_shift, BINOP_AND) : 0;
    return exit_frame(p, &f, res_811);
}

// bitwise_shift (left_recursive):
//     | bitwise_shift '<<' sum
//     | bitwise_shift '>>' sum
//     | sum
static ast_expr_t *bitwise_shift(parser_t *p) {
    const frame_t f = {532, p->pos, FUNC};
    ast_expr_t *res_532 = 0;
    if (is_memoized(p, &f, (void **) &res_532)) {
        return res_532;
    }
    ast_expr_t *alt_532;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_532;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_532 = (
                (alt_532 = bitwise_shift_1(p)) ||
                (alt_532 = bitwise_shift_2(p)) ||
                (alt_532 = sum(p))
            ) ? alt_532 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_532 = max;
    }
    insert_memo(p, &f, res_532);
    return exit_frame(p, &f, res_532);
}

// bitwise_shift '<<' sum
static ast_expr_t *bitwise_shift_1(parser_t *p) {
    const frame_t f = {830, p->pos, FUNC};
    ast_expr_t *res_830;
    ast_expr_t *_bitwise_shift;
    ast_expr_t *_sum;
    res_830 = enter_frame(p, &f) && (
        (_bitwise_shift = bitwise_shift(p)) &&
        (consume(p, 48, "<<")) &&
        (_sum = sum(p))
    ) ? ast_binary(p, _bitwise_shift, _sum, BINOP_SHL) : 0;
    return exit_frame(p, &f, res_830);
}

// bitwise_shift '>>' sum
static ast_expr_t *bitwise_shift_2(parser_t *p) {
    const frame_t f = {831, p->pos, FUNC};
    ast_expr_t *res_831;
    ast_expr_t *_bitwise_shift;
    ast_expr_t *_sum;
    res_831 = enter_frame(p, &f) && (
        (_bitwise_shift = bitwise_shift(p)) &&
        (consume(p, 49, ">>")) &&
        (_sum = sum(p))
    ) ? ast_binary(p, _bitwise_shift, _sum, BINOP_SHR) : 0;
    return exit_frame(p, &f, res_831);
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

// sum '+' term
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

// sum '-' term
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
//     | term '*' pipeline
//     | term '/' pipeline
//     | term '%' pipeline
//     | term '//' pipeline
//     | term '@' pipeline
//     | pipeline
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
                (alt_460 = pipeline(p))
            ) ? alt_460 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_460 = max;
    }
    insert_memo(p, &f, res_460);
    return exit_frame(p, &f, res_460);
}

// term '*' pipeline
static ast_expr_t *term_1(parser_t *p) {
    const frame_t f = {758, p->pos, FUNC};
    ast_expr_t *res_758;
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    res_758 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 23, "*")) &&
        (_pipeline = pipeline(p))
    ) ? ast_binary(p, _term, _pipeline, BINOP_MUL) : 0;
    return exit_frame(p, &f, res_758);
}

// term '/' pipeline
static ast_expr_t *term_2(parser_t *p) {
    const frame_t f = {759, p->pos, FUNC};
    ast_expr_t *res_759;
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    res_759 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 24, "/")) &&
        (_pipeline = pipeline(p))
    ) ? ast_binary(p, _term, _pipeline, BINOP_DIV) : 0;
    return exit_frame(p, &f, res_759);
}

// term '%' pipeline
static ast_expr_t *term_3(parser_t *p) {
    const frame_t f = {760, p->pos, FUNC};
    ast_expr_t *res_760;
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    res_760 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 25, "%")) &&
        (_pipeline = pipeline(p))
    ) ? ast_binary(p, _term, _pipeline, BINOP_MOD) : 0;
    return exit_frame(p, &f, res_760);
}

// term '//' pipeline
static ast_expr_t *term_4(parser_t *p) {
    const frame_t f = {761, p->pos, FUNC};
    ast_expr_t *res_761;
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    res_761 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 37, "//")) &&
        (_pipeline = pipeline(p))
    ) ? ast_binary(p, _term, _pipeline, BINOP_FDV) : 0;
    return exit_frame(p, &f, res_761);
}

// term '@' pipeline
static ast_expr_t *term_5(parser_t *p) {
    const frame_t f = {762, p->pos, FUNC};
    ast_expr_t *res_762;
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    res_762 = enter_frame(p, &f) && (
        (_term = term(p)) &&
        (consume(p, 26, "@")) &&
        (_pipeline = pipeline(p))
    ) ? ast_binary(p, _term, _pipeline, BINOP_MML) : 0;
    return exit_frame(p, &f, res_762);
}

// pipeline (left_recursive):
//     | pipeline '->' factor
//     | factor
static ast_expr_t *pipeline(parser_t *p) {
    const frame_t f = {274, p->pos, FUNC};
    ast_expr_t *res_274 = 0;
    if (is_memoized(p, &f, (void **) &res_274)) {
        return res_274;
    }
    ast_expr_t *alt_274;
    size_t maxpos;
    ast_expr_t *max;
    if (enter_frame(p, &f)) {
        do {
            maxpos = p->pos;
            max = res_274;
            insert_memo(p, &f, max);
            p->pos = f.f_pos;
            res_274 = (
                (alt_274 = pipeline_1(p)) ||
                (alt_274 = factor(p))
            ) ? alt_274 : 0;
        } while (p->pos > maxpos);
        p->pos = maxpos;
        res_274 = max;
    }
    insert_memo(p, &f, res_274);
    return exit_frame(p, &f, res_274);
}

// pipeline '->' factor
static ast_expr_t *pipeline_1(parser_t *p) {
    const frame_t f = {876, p->pos, FUNC};
    ast_expr_t *res_876;
    ast_expr_t *_pipeline;
    ast_expr_t *_factor;
    res_876 = enter_frame(p, &f) && (
        (_pipeline = pipeline(p)) &&
        (consume(p, 35, "->")) &&
        (_factor = factor(p))
    ) ? ast_binary(p, _pipeline, _factor, BINOP_PIP) : 0;
    return exit_frame(p, &f, res_876);
}

// factor (memo):
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static ast_expr_t *factor(parser_t *p) {
    const frame_t f = {983, p->pos, FUNC};
    ast_expr_t *res_983;
    if (is_memoized(p, &f, (void **) &res_983)) {
        return res_983;
    }
    ast_expr_t *alt_983;
    res_983 = enter_frame(p, &f) && (
        (alt_983 = factor_1(p)) ||
        (alt_983 = factor_2(p)) ||
        (alt_983 = factor_3(p)) ||
        (alt_983 = power(p))
    ) ? alt_983 : 0;
    insert_memo(p, &f, res_983);
    return exit_frame(p, &f, res_983);
}

// '+' factor
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

// '-' factor
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

// '~' factor
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

// power (memo):
//     | primary '**' factor
//     | primary
static ast_expr_t *power(parser_t *p) {
    const frame_t f = {757, p->pos, FUNC};
    ast_expr_t *res_757;
    if (is_memoized(p, &f, (void **) &res_757)) {
        return res_757;
    }
    ast_primary_t *_primary;
    ast_expr_t *alt_757;
    res_757 = enter_frame(p, &f) && (
        (alt_757 = power_1(p)) || (
            (_primary = primary(p)) &&
            (alt_757 = ast_primary_expr(p, _primary)))
    ) ? alt_757 : 0;
    insert_memo(p, &f, res_757);
    return exit_frame(p, &f, res_757);
}

// primary '**' factor
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

// primary '.' NAME
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

// primary invocation
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

// primary subscript
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

// paren_expression (inline):
//     | '(' [list_items] ')'
static ast_primary_t *paren_expression(parser_t *p) {
    const frame_t f = {69, p->pos, FUNC};
    ast_primary_t *res_69;
    ast_list_t *_list_items;
    res_69 = enter_frame(p, &f) && (
        (consume(p, 13, "(")) &&
        (_list_items = list_items(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_69);
}

// list_expression (inline):
//     | '[' [list_items] ']'
static ast_primary_t *list_expression(parser_t *p) {
    const frame_t f = {601, p->pos, FUNC};
    ast_primary_t *res_601;
    ast_list_t *_list_items;
    res_601 = enter_frame(p, &f) && (
        (consume(p, 17, "[")) &&
        (_list_items = list_items(p), 1) &&
        (consume(p, 18, "]"))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_601);
}

// builder_expression (inline):
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
static ast_primary_t *builder_expression(parser_t *p) {
    const frame_t f = {868, p->pos, FUNC};
    ast_primary_t *res_868;
    ast_primary_t *alt_868;
    res_868 = enter_frame(p, &f) && (
        (alt_868 = builder_expression_1(p)) ||
        (alt_868 = builder_expression_2(p))
    ) ? alt_868 : 0;
    return exit_frame(p, &f, res_868);
}

// NAME simple_args ':' expr
static ast_primary_t *builder_expression_1(parser_t *p) {
    const frame_t f = {254, p->pos, FUNC};
    ast_primary_t *res_254;
    token_t *_name;
    ast_list_t *_simple_args;
    ast_expr_t *_expr;
    res_254 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_simple_args = simple_args(p)) &&
        (consume(p, 9, ":")) &&
        (_expr = expr(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_254);
}

// NAME [builder_hint] [builder_args] block_suite
static ast_primary_t *builder_expression_2(parser_t *p) {
    const frame_t f = {256, p->pos, FUNC};
    ast_primary_t *res_256;
    token_t *_name;
    ast_list_t *_builder_hint;
    void *_builder_args;
    void *_block_suite;
    res_256 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_builder_hint = builder_hint(p), 1) &&
        (_builder_args = builder_args(p), 1) &&
        (_block_suite = block_suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_256);
}

// atom (memo):
//     | paren_expression
//     | list_expression
//     | builder_expression
//     | NAME
//     | NUMBER
//     | STRING
//     | 'None'
//     | 'True'
//     | 'False'
static ast_primary_t *atom(parser_t *p) {
    const frame_t f = {753, p->pos, FUNC};
    ast_primary_t *res_753;
    if (is_memoized(p, &f, (void **) &res_753)) {
        return res_753;
    }
    token_t *_name;
    token_t *_number;
    token_t *_string;
    ast_primary_t *alt_753;
    res_753 = enter_frame(p, &f) && (
        (alt_753 = paren_expression(p)) ||
        (alt_753 = list_expression(p)) ||
        (alt_753 = builder_expression(p)) || (
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
    insert_memo(p, &f, res_753);
    return exit_frame(p, &f, res_753);
}
