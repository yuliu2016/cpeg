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
static ast_stmt_t *simple_statement_6(parser_t *);
static ast_stmt_t *simple_statement_7(parser_t *);
static ast_expr_t *simple_statement_7_3(parser_t *);
static ast_stmt_t *simple_statement_8(parser_t *);
static void *target(parser_t *);
static void *target_1(parser_t *);
static void *target_2(parser_t *);
static ast_primary_t *t_primary(parser_t *);
static ast_primary_t *t_primary_1(parser_t *);
static ast_primary_t *t_primary_2(parser_t *);
static ast_primary_t *t_primary_3(parser_t *);
static ast_primary_t *t_primary_4(parser_t *);
static void *t_lookahead(parser_t *);
static ast_list_t *targets(parser_t *);
static ast_list_t *target_delimited(parser_t *);
static void *assignment(parser_t *);
static void *assignment_1(parser_t *);
static void *assignment_1_4(parser_t *);
static void *assignment_2(parser_t *);
static ast_list_t *assignment_2_1_loop(parser_t *);
static void *assignment_2_1(parser_t *);
static void *assignment_3(parser_t *);
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
static ast_list_t *expression_as_name_delimited(parser_t *);
static void *expression_as_name(parser_t *);
static token_t *expression_as_name_2(parser_t *);
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
static ast_list_t *call_argument_delimited(parser_t *);
static void *call_argument(parser_t *);
static void *call_argument_1(parser_t *);
static void *call_argument_2(parser_t *);
static void *call_argument_3(parser_t *);
static void *call_argument_4(parser_t *);
static ast_list_t *subscript(parser_t *);
static ast_list_t *slice_delimited(parser_t *);
static void *slice(parser_t *);
static void *slice_1(parser_t *);
static void *slice_expression(parser_t *);
static ast_list_t *expressions(parser_t *);
static ast_list_t *expression_delimited(parser_t *);
static ast_expr_t *starred_expression(parser_t *);
static ast_expr_t *maybe_starred(parser_t *);
static ast_list_t *starred_expressions(parser_t *);
static ast_list_t *maybe_starred_delimited(parser_t *);
static ast_named_t *named_expression(parser_t *);
static ast_named_t *named_expression_1(parser_t *);
static ast_expr_t *conditional(parser_t *);
static ast_expr_t *expression(parser_t *);
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
static void *list_item(parser_t *);
static ast_list_t *list_items(parser_t *);
static ast_list_t *list_item_delimited(parser_t *);
static ast_primary_t *paren_expression(parser_t *);
static ast_primary_t *list_expression(parser_t *);
static void *typed_parameter(parser_t *);
static void *typed_parameter_2(parser_t *);
static void *builder_parameter(parser_t *);
static void *builder_parameter_1(parser_t *);
static void *builder_parameter_1_2(parser_t *);
static void *builder_parameter_2(parser_t *);
static void *builder_parameter_3(parser_t *);
static void *simple_parameter(parser_t *);
static void *simple_parameter_2(parser_t *);
static void *builder_parameters(parser_t *);
static void *builder_parameters_2(parser_t *);
static ast_list_t *builder_parameter_delimited(parser_t *);
static void *builder_generics(parser_t *);
static ast_primary_t *builder_expression(parser_t *);
static ast_primary_t *builder_expression_1(parser_t *);
static ast_primary_t *builder_expression_2(parser_t *);
static ast_list_t *simple_parameter_delimited(parser_t *);
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
//     | expressions [NEWLINE]
static ast_list_t *eval_input(parser_t *p) {
    const frame_t f = {471, p->pos, FUNC};
    ast_list_t *res_471;
    ast_list_t *_expressions;
    res_471 = enter_frame(p, &f) && (
        (_expressions = expressions(p)) &&
        (consume(p, 2, "NEWLINE"), 1)
    ) ? _expressions : 0;
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
//     | assignment
//     | starred_expressions
//     | 'pass'
//     | 'break'
//     | 'continue'
//     | 'return' [starred_expressions]
//     | 'raise' expression ['from' expression]
//     | 'del' targets
static ast_stmt_t *simple_statement(parser_t *p) {
    const frame_t f = {930, p->pos, FUNC};
    ast_stmt_t *res_930;
    ast_stmt_t *alt_930;
    res_930 = enter_frame(p, &f) && (
        (alt_930 = assignment(p)) || (
            (starred_expressions(p)) &&
            (alt_930 = node(p))
        ) || (
            (consume(p, 64, "pass")) &&
            (alt_930 = ast_nop(p))
        ) || (
            (consume(p, 74, "break")) &&
            (alt_930 = ast_break(p))
        ) || (
            (consume(p, 73, "continue")) &&
            (alt_930 = ast_continue(p))
        ) ||
        (alt_930 = simple_statement_6(p)) ||
        (alt_930 = simple_statement_7(p)) ||
        (alt_930 = simple_statement_8(p))
    ) ? alt_930 : 0;
    return exit_frame(p, &f, res_930);
}

// 'return' [starred_expressions]
static ast_stmt_t *simple_statement_6(parser_t *p) {
    size_t pos = p->pos;
    ast_list_t *_starred_expressions;
    return (
        (consume(p, 54, "return")) &&
        (_starred_expressions = starred_expressions(p), 1)
    ) ? ast_return(p, _starred_expressions) :
        (p->pos = pos, NULL);
}

// 'raise' expression ['from' expression]
static ast_stmt_t *simple_statement_7(parser_t *p) {
    size_t pos = p->pos;
    return (
        (consume(p, 78, "raise")) &&
        (expression(p)) &&
        (simple_statement_7_3(p), 1)
    ) ? ast_nop(p) : (p->pos = pos, NULL);
}

// 'from' expression
static ast_expr_t *simple_statement_7_3(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_expression;
    return (
        (consume(p, 66, "from")) &&
        (_expression = expression(p))
    ) ? _expression : (p->pos = pos, NULL);
}

// 'del' targets
static ast_stmt_t *simple_statement_8(parser_t *p) {
    size_t pos = p->pos;
    ast_list_t *_targets;
    return (
        (consume(p, 79, "del")) &&
        (_targets = targets(p))
    ) ? ast_del(p, _targets) : (p->pos = pos, NULL);
}

// target (memo):
//     | t_primary '.' NAME !t_lookahead
//     | t_primary subscript !t_lookahead
//     | NAME
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
        (alt_161 = consume(p, 3, "NAME"))
    ) ? alt_161 : 0;
    insert_memo(p, &f, res_161);
    return exit_frame(p, &f, res_161);
}

// t_primary '.' NAME !t_lookahead
static void *target_1(parser_t *p) {
    size_t pos = p->pos;
    return (
        (t_primary(p)) &&
        (consume(p, 6, ".")) &&
        (consume(p, 3, "NAME")) &&
        (!test_and_reset(p, pos, t_lookahead(p)))
    ) ? node(p) : (p->pos = pos, NULL);
}

// t_primary subscript !t_lookahead
static void *target_2(parser_t *p) {
    size_t pos = p->pos;
    return (
        (t_primary(p)) &&
        (subscript(p)) &&
        (!test_and_reset(p, pos, t_lookahead(p)))
    ) ? node(p) : (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    return (
        (t_primary(p)) &&
        (consume(p, 6, ".")) &&
        (consume(p, 3, "NAME")) &&
        (test_and_reset(p, pos, t_lookahead(p)))
    ) ? node(p) : (p->pos = pos, NULL);
}

// t_primary invocation &t_lookahead
static ast_primary_t *t_primary_2(parser_t *p) {
    size_t pos = p->pos;
    return (
        (t_primary(p)) &&
        (invocation(p)) &&
        (test_and_reset(p, pos, t_lookahead(p)))
    ) ? node(p) : (p->pos = pos, NULL);
}

// t_primary subscript &t_lookahead
static ast_primary_t *t_primary_3(parser_t *p) {
    size_t pos = p->pos;
    return (
        (t_primary(p)) &&
        (subscript(p)) &&
        (test_and_reset(p, pos, t_lookahead(p)))
    ) ? node(p) : (p->pos = pos, NULL);
}

// atom &t_lookahead
static ast_primary_t *t_primary_4(parser_t *p) {
    size_t pos = p->pos;
    ast_primary_t *_atom;
    return (
        (_atom = atom(p)) &&
        (test_and_reset(p, pos, t_lookahead(p)))
    ) ? _atom : (p->pos = pos, NULL);
}

// t_lookahead (inline):
//     | '.'
//     | '('
//     | '['
static void *t_lookahead(parser_t *p) {
    size_t pos = p->pos;
    void *alt;
    return (
        (alt = consume(p, 6, ".")) ||
        (alt = consume(p, 13, "(")) ||
        (alt = consume(p, 17, "["))
    ) ? alt : (p->pos = pos, NULL);
}

// targets:
//     | ','.target+ [',']
static ast_list_t *targets(parser_t *p) {
    const frame_t f = {882, p->pos, FUNC};
    ast_list_t *res_882;
    ast_list_t *_targets;
    res_882 = enter_frame(p, &f) && (
        (_targets = target_delimited(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _targets : 0;
    return exit_frame(p, &f, res_882);
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

// assignment:
//     | target ':' expression ['=' expressions]
//     | (targets '=')+ starred_expressions
//     | target augmented_assign expressions
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

// target ':' expression ['=' expressions]
static void *assignment_1(parser_t *p) {
    size_t pos = p->pos;
    return (
        (target(p)) &&
        (consume(p, 9, ":")) &&
        (expression(p)) &&
        (assignment_1_4(p), 1)
    ) ? node(p) : (p->pos = pos, NULL);
}

// '=' expressions
static void *assignment_1_4(parser_t *p) {
    size_t pos = p->pos;
    ast_list_t *_expressions;
    return (
        (consume(p, 8, "=")) &&
        (_expressions = expressions(p))
    ) ? _expressions : (p->pos = pos, NULL);
}

// (targets '=')+ starred_expressions
static void *assignment_2(parser_t *p) {
    size_t pos = p->pos;
    return (
        (assignment_2_1_loop(p)) &&
        (starred_expressions(p))
    ) ? node(p) : (p->pos = pos, NULL);
}

static ast_list_t *assignment_2_1_loop(parser_t *p) {
    void *_targets_assign = assignment_2_1(p);
    if (!_targets_assign) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    do {
        ast_list_append(p, list, _targets_assign);
    } while ((_targets_assign = assignment_2_1(p)));
    return list;
}

// targets '='
static void *assignment_2_1(parser_t *p) {
    size_t pos = p->pos;
    ast_list_t *_targets;
    return (
        (_targets = targets(p)) &&
        (consume(p, 8, "="))
    ) ? _targets : (p->pos = pos, NULL);
}

// target augmented_assign expressions
static void *assignment_3(parser_t *p) {
    size_t pos = p->pos;
    return (
        (target(p)) &&
        (augmented_assign(p)) &&
        (expressions(p))
    ) ? node(p) : (p->pos = pos, NULL);
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

// if_statement:
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
//     | 'for' targets 'in' expressions suite [else_suite]
static void *for_statement(parser_t *p) {
    const frame_t f = {465, p->pos, FUNC};
    void *res_465;
    ast_list_t *_targets;
    ast_list_t *_expressions;
    void *_suite;
    void *_else_suite;
    res_465 = enter_frame(p, &f) && (
        (consume(p, 72, "for")) &&
        (_targets = targets(p)) &&
        (consume(p, 63, "in")) &&
        (_expressions = expressions(p)) &&
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
//     | 'with' ','.expression_as_name+ suite
static void *with_statement(parser_t *p) {
    const frame_t f = {214, p->pos, FUNC};
    void *res_214;
    ast_list_t *_expression_as_names;
    void *_suite;
    res_214 = enter_frame(p, &f) && (
        (consume(p, 68, "with")) &&
        (_expression_as_names = expression_as_name_delimited(p)) &&
        (_suite = suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_214);
}

static ast_list_t *expression_as_name_delimited(parser_t *p) {
    void *_expression_as_name = expression_as_name(p);
    if (!_expression_as_name) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _expression_as_name);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_expression_as_name = expression_as_name(p)));
    p->pos = pos;
    return list;
}

// expression_as_name:
//     | expression ['as' NAME]
static void *expression_as_name(parser_t *p) {
    const frame_t f = {169, p->pos, FUNC};
    void *res_169;
    ast_expr_t *_expression;
    token_t *_as_name;
    res_169 = enter_frame(p, &f) && (
        (_expression = expression(p)) &&
        (_as_name = expression_as_name_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_169);
}

// 'as' NAME
static token_t *expression_as_name_2(parser_t *p) {
    size_t pos = p->pos;
    token_t *_name;
    return (
        (consume(p, 65, "as")) &&
        (_name = consume(p, 3, "NAME"))
    ) ? _name : (p->pos = pos, NULL);
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
    ast_list_t *_statement_list;
    res_560 = enter_frame(p, &f) && (
        (consume(p, 15, "{")) &&
        (consume(p, 2, "NEWLINE")) &&
        (_statement_list = statement_list(p)) &&
        (consume(p, 16, "}"))
    ) ? _statement_list : 0;
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

// else_suite (inline):
//     | 'else' suite
static void *else_suite(parser_t *p) {
    size_t pos = p->pos;
    void *_suite;
    return (
        (consume(p, 58, "else")) &&
        (_suite = suite(p))
    ) ? _suite : (p->pos = pos, NULL);
}

// finally_suite (inline):
//     | 'finally' suite
static void *finally_suite(parser_t *p) {
    size_t pos = p->pos;
    void *_suite;
    return (
        (consume(p, 77, "finally")) &&
        (_suite = suite(p))
    ) ? _suite : (p->pos = pos, NULL);
}

// except_clause:
//     | 'except' [expression_as_name] suite
static void *except_clause(parser_t *p) {
    const frame_t f = {357, p->pos, FUNC};
    void *res_357;
    void *_expression_as_name;
    void *_suite;
    res_357 = enter_frame(p, &f) && (
        (consume(p, 76, "except")) &&
        (_expression_as_name = expression_as_name(p), 1) &&
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
//     | '(' [','.call_argument+ [',']] ')'
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

// ','.call_argument+ [',']
static void *invocation_2(parser_t *p) {
    const frame_t f = {35, p->pos, FUNC};
    void *res_35;
    ast_list_t *_call_arguments;
    res_35 = enter_frame(p, &f) && (
        (_call_arguments = call_argument_delimited(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _call_arguments : 0;
    return exit_frame(p, &f, res_35);
}

static ast_list_t *call_argument_delimited(parser_t *p) {
    void *_call_argument = call_argument(p);
    if (!_call_argument) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _call_argument);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_call_argument = call_argument(p)));
    p->pos = pos;
    return list;
}

// call_argument:
//     | NAME ':=' expression
//     | NAME '=' expression
//     | '**' expression
//     | '*' expression
//     | expression
static void *call_argument(parser_t *p) {
    const frame_t f = {78, p->pos, FUNC};
    void *res_78;
    void *alt_78;
    res_78 = enter_frame(p, &f) && (
        (alt_78 = call_argument_1(p)) ||
        (alt_78 = call_argument_2(p)) ||
        (alt_78 = call_argument_3(p)) ||
        (alt_78 = call_argument_4(p)) ||
        (alt_78 = expression(p))
    ) ? alt_78 : 0;
    return exit_frame(p, &f, res_78);
}

// NAME ':=' expression
static void *call_argument_1(parser_t *p) {
    size_t pos = p->pos;
    token_t *_name;
    ast_expr_t *_expression;
    return (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (_expression = expression(p))
    ) ? ast_named(p, _name, _expression) :
        (p->pos = pos, NULL);
}

// NAME '=' expression
static void *call_argument_2(parser_t *p) {
    size_t pos = p->pos;
    token_t *_name;
    ast_expr_t *_expression;
    return (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 8, "=")) &&
        (_expression = expression(p))
    ) ? ast_named(p, _name, _expression) :
        (p->pos = pos, NULL);
}

// '**' expression
static void *call_argument_3(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_expression;
    return (
        (consume(p, 38, "**")) &&
        (_expression = expression(p))
    ) ? _expression : (p->pos = pos, NULL);
}

// '*' expression
static void *call_argument_4(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_expression;
    return (
        (consume(p, 23, "*")) &&
        (_expression = expression(p))
    ) ? _expression : (p->pos = pos, NULL);
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
//     | [expression] slice_expression [slice_expression]
//     | expression
static void *slice(parser_t *p) {
    const frame_t f = {418, p->pos, FUNC};
    void *res_418;
    void *alt_418;
    res_418 = enter_frame(p, &f) && (
        (alt_418 = slice_1(p)) ||
        (alt_418 = expression(p))
    ) ? alt_418 : 0;
    return exit_frame(p, &f, res_418);
}

// [expression] slice_expression [slice_expression]
static void *slice_1(parser_t *p) {
    const frame_t f = {292, p->pos, FUNC};
    void *res_292;
    ast_expr_t *_expression;
    void *_slice_expression;
    void *_slice_expression_1;
    res_292 = enter_frame(p, &f) && (
        (_expression = expression(p), 1) &&
        (_slice_expression = slice_expression(p)) &&
        (_slice_expression_1 = slice_expression(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_292);
}

// slice_expression:
//     | ':' [expression]
static void *slice_expression(parser_t *p) {
    const frame_t f = {421, p->pos, FUNC};
    void *res_421;
    ast_expr_t *_expression;
    res_421 = enter_frame(p, &f) && (
        (consume(p, 9, ":")) &&
        (_expression = expression(p), 1)
    ) ? _expression : 0;
    return exit_frame(p, &f, res_421);
}

// expressions:
//     | ','.expression+ [',']
static ast_list_t *expressions(parser_t *p) {
    const frame_t f = {779, p->pos, FUNC};
    ast_list_t *res_779;
    ast_list_t *_expressions;
    res_779 = enter_frame(p, &f) && (
        (_expressions = expression_delimited(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _expressions : 0;
    return exit_frame(p, &f, res_779);
}

static ast_list_t *expression_delimited(parser_t *p) {
    ast_expr_t *_expression = expression(p);
    if (!_expression) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _expression);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_expression = expression(p)));
    p->pos = pos;
    return list;
}

// starred_expression (inline):
//     | '*' bitwise_or
static ast_expr_t *starred_expression(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_bitwise_or;
    return (
        (consume(p, 23, "*")) &&
        (_bitwise_or = bitwise_or(p))
    ) ? _bitwise_or : (p->pos = pos, NULL);
}

// maybe_starred:
//     | starred_expression
//     | expression
static ast_expr_t *maybe_starred(parser_t *p) {
    const frame_t f = {984, p->pos, FUNC};
    ast_expr_t *res_984;
    ast_expr_t *alt_984;
    res_984 = enter_frame(p, &f) && (
        (alt_984 = starred_expression(p)) ||
        (alt_984 = expression(p))
    ) ? alt_984 : 0;
    return exit_frame(p, &f, res_984);
}

// starred_expressions:
//     | ','.maybe_starred+ [',']
static ast_list_t *starred_expressions(parser_t *p) {
    const frame_t f = {171, p->pos, FUNC};
    ast_list_t *res_171;
    ast_list_t *_maybe_starreds;
    res_171 = enter_frame(p, &f) && (
        (_maybe_starreds = maybe_starred_delimited(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _maybe_starreds : 0;
    return exit_frame(p, &f, res_171);
}

static ast_list_t *maybe_starred_delimited(parser_t *p) {
    ast_expr_t *_maybe_starred = maybe_starred(p);
    if (!_maybe_starred) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _maybe_starred);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_maybe_starred = maybe_starred(p)));
    p->pos = pos;
    return list;
}

// named_expression:
//     | NAME ':=' expression
//     | expression
static ast_named_t *named_expression(parser_t *p) {
    const frame_t f = {358, p->pos, FUNC};
    ast_named_t *res_358;
    ast_expr_t *_expression;
    ast_named_t *alt_358;
    res_358 = enter_frame(p, &f) && (
        (alt_358 = named_expression_1(p)) || (
            (_expression = expression(p)) &&
            (alt_358 = ast_unnamed(p, _expression)))
    ) ? alt_358 : 0;
    return exit_frame(p, &f, res_358);
}

// NAME ':=' expression
static ast_named_t *named_expression_1(parser_t *p) {
    size_t pos = p->pos;
    token_t *_name;
    ast_expr_t *_expression;
    return (
        (_name = consume(p, 3, "NAME")) &&
        (consume(p, 36, ":=")) &&
        (_expression = expression(p))
    ) ? ast_named(p, _name, _expression) :
        (p->pos = pos, NULL);
}

// conditional (inline):
//     | 'if' disjunction '?' disjunction ':' expression
static ast_expr_t *conditional(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_disjunction;
    ast_expr_t *_disjunction_1;
    ast_expr_t *_expression;
    return (
        (consume(p, 56, "if")) &&
        (_disjunction = disjunction(p)) &&
        (consume(p, 10, "?")) &&
        (_disjunction_1 = disjunction(p)) &&
        (consume(p, 9, ":")) &&
        (_expression = expression(p))
    ) ? ast_conditional(p, _disjunction, _disjunction_1, _expression) :
        (p->pos = pos, NULL);
}

// expression:
//     | conditional
//     | disjunction
static ast_expr_t *expression(parser_t *p) {
    const frame_t f = {736, p->pos, FUNC};
    ast_expr_t *res_736;
    ast_expr_t *alt_736;
    res_736 = enter_frame(p, &f) && (
        (alt_736 = conditional(p)) ||
        (alt_736 = disjunction(p))
    ) ? alt_736 : 0;
    return exit_frame(p, &f, res_736);
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
    size_t pos = p->pos;
    ast_expr_t *_disjunction;
    ast_expr_t *_conjunction;
    return (
        (_disjunction = disjunction(p)) &&
        (consume(p, 60, "or")) &&
        (_conjunction = conjunction(p))
    ) ? ast_binary(p, _disjunction, _conjunction, LOGIC_OR) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    ast_expr_t *_conjunction;
    ast_expr_t *_inversion;
    return (
        (_conjunction = conjunction(p)) &&
        (consume(p, 59, "and")) &&
        (_inversion = inversion(p))
    ) ? ast_binary(p, _conjunction, _inversion, LOGIC_AND) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    ast_expr_t *_inversion;
    return (
        (consume(p, 61, "not")) &&
        (_inversion = inversion(p))
    ) ? ast_unary(p, _inversion, LOGIC_NOT) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    ast_expr_t *_bitwise_or;
    ast_list_t *_comparator_bitwise_ors;
    return (
        (_bitwise_or = bitwise_or(p)) &&
        (_comparator_bitwise_ors = comparison_1_2_loop(p))
    ) ? ast_comparison(p, _bitwise_or, _comparator_bitwise_ors) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    int *_comparator;
    ast_expr_t *_bitwise_or;
    return (
        (_comparator = comparator(p)) &&
        (_bitwise_or = bitwise_or(p))
    ) ? ast_comp_term(p, _comparator, _bitwise_or) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    return (
        (consume(p, 61, "not")) &&
        (consume(p, 63, "in"))
    ) ? ast_integer(p, CMP_NI) :
        (p->pos = pos, NULL);
}

// 'is' 'not'
static int *comparator_10(parser_t *p) {
    size_t pos = p->pos;
    return (
        (consume(p, 62, "is")) &&
        (consume(p, 61, "not"))
    ) ? ast_integer(p, CMP_NS) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    ast_expr_t *_bitwise_or;
    ast_expr_t *_bitwise_xor;
    return (
        (_bitwise_or = bitwise_or(p)) &&
        (consume(p, 27, "|")) &&
        (_bitwise_xor = bitwise_xor(p))
    ) ? ast_binary(p, _bitwise_or, _bitwise_xor, BINOP_IOR) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    ast_expr_t *_bitwise_xor;
    ast_expr_t *_bitwise_and;
    return (
        (_bitwise_xor = bitwise_xor(p)) &&
        (consume(p, 30, "^")) &&
        (_bitwise_and = bitwise_and(p))
    ) ? ast_binary(p, _bitwise_xor, _bitwise_and, BINOP_XOR) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    ast_expr_t *_bitwise_and;
    ast_expr_t *_bitwise_shift;
    return (
        (_bitwise_and = bitwise_and(p)) &&
        (consume(p, 28, "&")) &&
        (_bitwise_shift = bitwise_shift(p))
    ) ? ast_binary(p, _bitwise_and, _bitwise_shift, BINOP_AND) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    ast_expr_t *_bitwise_shift;
    ast_expr_t *_sum;
    return (
        (_bitwise_shift = bitwise_shift(p)) &&
        (consume(p, 48, "<<")) &&
        (_sum = sum(p))
    ) ? ast_binary(p, _bitwise_shift, _sum, BINOP_SHL) :
        (p->pos = pos, NULL);
}

// bitwise_shift '>>' sum
static ast_expr_t *bitwise_shift_2(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_bitwise_shift;
    ast_expr_t *_sum;
    return (
        (_bitwise_shift = bitwise_shift(p)) &&
        (consume(p, 49, ">>")) &&
        (_sum = sum(p))
    ) ? ast_binary(p, _bitwise_shift, _sum, BINOP_SHR) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    ast_expr_t *_sum;
    ast_expr_t *_term;
    return (
        (_sum = sum(p)) &&
        (consume(p, 21, "+")) &&
        (_term = term(p))
    ) ? ast_binary(p, _sum, _term, BINOP_PLS) :
        (p->pos = pos, NULL);
}

// sum '-' term
static ast_expr_t *sum_2(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_sum;
    ast_expr_t *_term;
    return (
        (_sum = sum(p)) &&
        (consume(p, 22, "-")) &&
        (_term = term(p))
    ) ? ast_binary(p, _sum, _term, BINOP_MIN) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    return (
        (_term = term(p)) &&
        (consume(p, 23, "*")) &&
        (_pipeline = pipeline(p))
    ) ? ast_binary(p, _term, _pipeline, BINOP_MUL) :
        (p->pos = pos, NULL);
}

// term '/' pipeline
static ast_expr_t *term_2(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    return (
        (_term = term(p)) &&
        (consume(p, 24, "/")) &&
        (_pipeline = pipeline(p))
    ) ? ast_binary(p, _term, _pipeline, BINOP_DIV) :
        (p->pos = pos, NULL);
}

// term '%' pipeline
static ast_expr_t *term_3(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    return (
        (_term = term(p)) &&
        (consume(p, 25, "%")) &&
        (_pipeline = pipeline(p))
    ) ? ast_binary(p, _term, _pipeline, BINOP_MOD) :
        (p->pos = pos, NULL);
}

// term '//' pipeline
static ast_expr_t *term_4(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    return (
        (_term = term(p)) &&
        (consume(p, 37, "//")) &&
        (_pipeline = pipeline(p))
    ) ? ast_binary(p, _term, _pipeline, BINOP_FDV) :
        (p->pos = pos, NULL);
}

// term '@' pipeline
static ast_expr_t *term_5(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    return (
        (_term = term(p)) &&
        (consume(p, 26, "@")) &&
        (_pipeline = pipeline(p))
    ) ? ast_binary(p, _term, _pipeline, BINOP_MML) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    ast_expr_t *_pipeline;
    ast_expr_t *_factor;
    return (
        (_pipeline = pipeline(p)) &&
        (consume(p, 35, "->")) &&
        (_factor = factor(p))
    ) ? ast_binary(p, _pipeline, _factor, BINOP_PIP) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    ast_expr_t *_factor;
    return (
        (consume(p, 21, "+")) &&
        (_factor = factor(p))
    ) ? ast_unary(p, _factor, UNARY_PLS) :
        (p->pos = pos, NULL);
}

// '-' factor
static ast_expr_t *factor_2(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_factor;
    return (
        (consume(p, 22, "-")) &&
        (_factor = factor(p))
    ) ? ast_unary(p, _factor, UNARY_MIN) :
        (p->pos = pos, NULL);
}

// '~' factor
static ast_expr_t *factor_3(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_factor;
    return (
        (consume(p, 29, "~")) &&
        (_factor = factor(p))
    ) ? ast_unary(p, _factor, UNARY_INV) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    ast_primary_t *_primary;
    ast_expr_t *_factor;
    return (
        (_primary = primary(p)) &&
        (consume(p, 38, "**")) &&
        (_factor = factor(p))
    ) ? ast_binary(p, ast_primary_expr(p, _primary), _factor, BINOP_POW) :
        (p->pos = pos, NULL);
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
    size_t pos = p->pos;
    return (
        (primary(p)) &&
        (consume(p, 6, ".")) &&
        (consume(p, 3, "NAME"))
    ) ? node(p) : (p->pos = pos, NULL);
}

// primary invocation
static ast_primary_t *primary_2(parser_t *p) {
    size_t pos = p->pos;
    return (
        (primary(p)) &&
        (invocation(p))
    ) ? node(p) : (p->pos = pos, NULL);
}

// primary subscript
static ast_primary_t *primary_3(parser_t *p) {
    size_t pos = p->pos;
    return (
        (primary(p)) &&
        (subscript(p))
    ) ? node(p) : (p->pos = pos, NULL);
}

// list_item:
//     | starred_expression
//     | named_expression
static void *list_item(parser_t *p) {
    const frame_t f = {756, p->pos, FUNC};
    void *res_756;
    void *alt_756;
    res_756 = enter_frame(p, &f) && (
        (alt_756 = starred_expression(p)) ||
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

// paren_expression (inline):
//     | '(' [list_items] ')'
static ast_primary_t *paren_expression(parser_t *p) {
    size_t pos = p->pos;
    ast_list_t *_list_items;
    return (
        (consume(p, 13, "(")) &&
        (_list_items = list_items(p), 1) &&
        (consume(p, 14, ")"))
    ) ? node(p) : (p->pos = pos, NULL);
}

// list_expression (inline):
//     | '[' [list_items] ']'
static ast_primary_t *list_expression(parser_t *p) {
    size_t pos = p->pos;
    ast_list_t *_list_items;
    return (
        (consume(p, 17, "[")) &&
        (_list_items = list_items(p), 1) &&
        (consume(p, 18, "]"))
    ) ? node(p) : (p->pos = pos, NULL);
}

// typed_parameter:
//     | NAME [':' expression]
static void *typed_parameter(parser_t *p) {
    const frame_t f = {868, p->pos, FUNC};
    void *res_868;
    token_t *_name;
    void *_colon_expression;
    res_868 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_colon_expression = typed_parameter_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_868);
}

// ':' expression
static void *typed_parameter_2(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_expression;
    return (
        (consume(p, 9, ":")) &&
        (_expression = expression(p))
    ) ? _expression : (p->pos = pos, NULL);
}

// builder_parameter:
//     | typed_parameter ['=' expression]
//     | '*' typed_parameter
//     | '**' typed_parameter
static void *builder_parameter(parser_t *p) {
    const frame_t f = {789, p->pos, FUNC};
    void *res_789;
    void *alt_789;
    res_789 = enter_frame(p, &f) && (
        (alt_789 = builder_parameter_1(p)) ||
        (alt_789 = builder_parameter_2(p)) ||
        (alt_789 = builder_parameter_3(p))
    ) ? alt_789 : 0;
    return exit_frame(p, &f, res_789);
}

// typed_parameter ['=' expression]
static void *builder_parameter_1(parser_t *p) {
    const frame_t f = {887, p->pos, FUNC};
    void *res_887;
    void *_typed_parameter;
    void *_assign_expression;
    res_887 = enter_frame(p, &f) && (
        (_typed_parameter = typed_parameter(p)) &&
        (_assign_expression = builder_parameter_1_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_887);
}

// '=' expression
static void *builder_parameter_1_2(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_expression;
    return (
        (consume(p, 8, "=")) &&
        (_expression = expression(p))
    ) ? _expression : (p->pos = pos, NULL);
}

// '*' typed_parameter
static void *builder_parameter_2(parser_t *p) {
    size_t pos = p->pos;
    void *_typed_parameter;
    return (
        (consume(p, 23, "*")) &&
        (_typed_parameter = typed_parameter(p))
    ) ? _typed_parameter : (p->pos = pos, NULL);
}

// '**' typed_parameter
static void *builder_parameter_3(parser_t *p) {
    size_t pos = p->pos;
    void *_typed_parameter;
    return (
        (consume(p, 38, "**")) &&
        (_typed_parameter = typed_parameter(p))
    ) ? _typed_parameter : (p->pos = pos, NULL);
}

// simple_parameter:
//     | NAME ['=' expression]
static void *simple_parameter(parser_t *p) {
    const frame_t f = {524, p->pos, FUNC};
    void *res_524;
    token_t *_name;
    void *_assign_expression;
    res_524 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_assign_expression = simple_parameter_2(p), 1)
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_524);
}

// '=' expression
static void *simple_parameter_2(parser_t *p) {
    size_t pos = p->pos;
    ast_expr_t *_expression;
    return (
        (consume(p, 8, "=")) &&
        (_expression = expression(p))
    ) ? _expression : (p->pos = pos, NULL);
}

// builder_parameters (inline):
//     | '(' [','.builder_parameter+ [',']] ')'
static void *builder_parameters(parser_t *p) {
    size_t pos = p->pos;
    void *_builder_parameters_2;
    return (
        (consume(p, 13, "(")) &&
        (_builder_parameters_2 = builder_parameters_2(p), 1) &&
        (consume(p, 14, ")"))
    ) ? _builder_parameters_2 :
        (p->pos = pos, NULL);
}

// ','.builder_parameter+ [',']
static void *builder_parameters_2(parser_t *p) {
    size_t pos = p->pos;
    ast_list_t *_builder_parameters;
    return (
        (_builder_parameters = builder_parameter_delimited(p)) &&
        (consume(p, 7, ","), 1)
    ) ? _builder_parameters : (p->pos = pos, NULL);
}

static ast_list_t *builder_parameter_delimited(parser_t *p) {
    void *_builder_parameter = builder_parameter(p);
    if (!_builder_parameter) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _builder_parameter);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_builder_parameter = builder_parameter(p)));
    p->pos = pos;
    return list;
}

// builder_generics (inline):
//     | '[' expressions ']'
static void *builder_generics(parser_t *p) {
    size_t pos = p->pos;
    ast_list_t *_expressions;
    return (
        (consume(p, 17, "[")) &&
        (_expressions = expressions(p)) &&
        (consume(p, 18, "]"))
    ) ? _expressions : (p->pos = pos, NULL);
}

// builder_expression (inline):
//     | NAME [builder_generics] [builder_parameters] block_suite
//     | NAME ','.simple_parameter+ ':' expression
static ast_primary_t *builder_expression(parser_t *p) {
    size_t pos = p->pos;
    ast_primary_t *alt;
    return (
        (alt = builder_expression_1(p)) ||
        (alt = builder_expression_2(p))
    ) ? alt : (p->pos = pos, NULL);
}

// NAME [builder_generics] [builder_parameters] block_suite
static ast_primary_t *builder_expression_1(parser_t *p) {
    const frame_t f = {254, p->pos, FUNC};
    ast_primary_t *res_254;
    token_t *_name;
    void *_builder_generics;
    void *_builder_parameters;
    void *_block_suite;
    res_254 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_builder_generics = builder_generics(p), 1) &&
        (_builder_parameters = builder_parameters(p), 1) &&
        (_block_suite = block_suite(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_254);
}

// NAME ','.simple_parameter+ ':' expression
static ast_primary_t *builder_expression_2(parser_t *p) {
    const frame_t f = {256, p->pos, FUNC};
    ast_primary_t *res_256;
    token_t *_name;
    ast_list_t *_simple_parameters;
    ast_expr_t *_expression;
    res_256 = enter_frame(p, &f) && (
        (_name = consume(p, 3, "NAME")) &&
        (_simple_parameters = simple_parameter_delimited(p)) &&
        (consume(p, 9, ":")) &&
        (_expression = expression(p))
    ) ? node(p) : 0;
    return exit_frame(p, &f, res_256);
}

static ast_list_t *simple_parameter_delimited(parser_t *p) {
    void *_simple_parameter = simple_parameter(p);
    if (!_simple_parameter) {
        return 0;
    }
    ast_list_t *list = ast_list_new(p);
    size_t pos;
    do {
        ast_list_append(p, list, _simple_parameter);
        pos = p->pos;
    } while (consume(p, 7, ",") &&
            (_simple_parameter = simple_parameter(p)));
    p->pos = pos;
    return list;
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
