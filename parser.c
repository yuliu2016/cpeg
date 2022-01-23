#include "include/ast.h"
#include "include/internal/static_parser.h"


static ast_list_t *single_input();
static ast_list_t *single_input_3();
static ast_list_t *file_input();
static ast_list_t *eval_input();
static ast_list_t *statement_list();
static ast_list_t *line_statement_loop();
static ast_list_t *line_statement();
static ast_list_t *line_statement_1();
static ast_list_t *line_statement_2();
static ast_list_t *simple_statements();
static ast_list_t *simple_statement_delimited();
static ast_stmt_t *simple_statement();
static ast_stmt_t *simple_statement_6();
static ast_stmt_t *simple_statement_7();
static ast_expr_t *simple_statement_7_3();
static ast_stmt_t *simple_statement_8();
static void *target();
static void *target_1();
static void *target_2();
static ast_primary_t *t_primary();
static ast_primary_t *t_primary_1();
static ast_primary_t *t_primary_2();
static ast_primary_t *t_primary_3();
static ast_primary_t *t_primary_4();
static void *t_lookahead();
static ast_list_t *targets();
static ast_list_t *target_delimited();
static void *assignment();
static void *assignment_1();
static void *assignment_1_4();
static void *assignment_2();
static ast_list_t *assignment_2_1_loop();
static void *assignment_2_1();
static void *assignment_3();
static int augmented_assign();
static void *compound_statement();
static void *if_statement();
static ast_list_t *elif_statement_loop();
static void *elif_statement();
static void *while_statement();
static void *for_statement();
static void *try_statement();
static void *try_statement_3();
static void *with_statement();
static ast_list_t *expression_as_name_delimited();
static void *expression_as_name();
static token_t *expression_as_name_2();
static void *block_suite();
static void *block_suite_1();
static void *block_suite_2();
static void *suite();
static void *suite_1();
static void *else_suite();
static void *finally_suite();
static void *except_clause();
static void *except_suite();
static ast_list_t *except_clause_loop();
static void *invocation();
static void *invocation_2();
static ast_list_t *call_argument_delimited();
static void *call_argument();
static void *call_argument_1();
static void *call_argument_2();
static void *call_argument_3();
static void *call_argument_4();
static ast_list_t *subscript();
static ast_list_t *slice_delimited();
static void *slice();
static void *slice_1();
static void *slice_expression();
static ast_list_t *expressions();
static ast_list_t *expression_delimited();
static ast_expr_t *starred_expression();
static ast_expr_t *maybe_starred();
static ast_list_t *starred_expressions();
static ast_list_t *maybe_starred_delimited();
static ast_named_t *named_expression();
static ast_named_t *named_expression_1();
static ast_expr_t *conditional();
static ast_expr_t *expression();
static ast_expr_t *disjunction();
static ast_expr_t *disjunction_1();
static ast_expr_t *conjunction();
static ast_expr_t *conjunction_1();
static ast_expr_t *inversion();
static ast_expr_t *inversion_1();
static ast_expr_t *comparison();
static ast_expr_t *comparison_1();
static ast_list_t *comparison_1_2_loop();
static ast_expr_t *comparison_1_2();
static int comparator();
static int comparator_8();
static int comparator_10();
static ast_expr_t *bitwise_or();
static ast_expr_t *bitwise_or_1();
static ast_expr_t *bitwise_xor();
static ast_expr_t *bitwise_xor_1();
static ast_expr_t *bitwise_and();
static ast_expr_t *bitwise_and_1();
static ast_expr_t *bitwise_shift();
static ast_expr_t *bitwise_shift_1();
static ast_expr_t *bitwise_shift_2();
static ast_expr_t *sum();
static ast_expr_t *sum_1();
static ast_expr_t *sum_2();
static ast_expr_t *term();
static ast_expr_t *term_1();
static ast_expr_t *term_2();
static ast_expr_t *term_3();
static ast_expr_t *term_4();
static ast_expr_t *term_5();
static ast_expr_t *pipeline();
static ast_expr_t *pipeline_1();
static ast_expr_t *factor();
static ast_expr_t *factor_1();
static ast_expr_t *factor_2();
static ast_expr_t *factor_3();
static ast_expr_t *power();
static ast_expr_t *power_1();
static ast_primary_t *primary();
static ast_primary_t *primary_1();
static ast_primary_t *primary_2();
static ast_primary_t *primary_3();
static void *list_item();
static ast_list_t *list_items();
static ast_list_t *list_item_delimited();
static ast_primary_t *paren_expression();
static ast_primary_t *list_expression();
static void *typed_parameter();
static void *typed_parameter_2();
static void *builder_parameter();
static void *builder_parameter_1();
static void *builder_parameter_1_2();
static void *builder_parameter_2();
static void *builder_parameter_3();
static void *simple_parameter();
static void *simple_parameter_2();
static void *builder_parameters();
static void *builder_parameters_2();
static ast_list_t *builder_parameter_delimited();
static void *builder_generics();
static ast_primary_t *builder_expression();
static ast_primary_t *builder_expression_1();
static ast_primary_t *builder_expression_2();
static ast_list_t *simple_parameter_delimited();
static ast_primary_t *atom();


// Placeholder node
static inline void *node() {
    return palloc(sizeof(char));
}

// Do nothing operation
static ast_stmt_t *ast_nop() {
    return node();
}

// single_input:
//     | NEWLINE
//     | simple_statements
//     | compound_statement NEWLINE
static ast_list_t *single_input() {
    size_t _pos = pos();
    ast_list_t *res_251;
    ast_list_t *_simple_statements;
    ast_list_t *alt_251;
    res_251 = enter_frame(FUNC) && ((
            (consume(2, "NEWLINE")) &&
            (alt_251 = ast_list_of(ast_nop()))
        ) || (
            (_simple_statements = simple_statements()) &&
            (alt_251 = ast_list_of(_simple_statements))
        ) ||
        (alt_251 = single_input_3())
    ) ? alt_251 : 0;
    return exit_frame(_pos, res_251, FUNC);
}

// compound_statement NEWLINE
static ast_list_t *single_input_3() {
    size_t _pos = pos();
    ast_list_t *res_423;
    void *_compound_statement;
    res_423 = enter_frame(FUNC) && (
        (_compound_statement = compound_statement()) &&
        (consume(2, "NEWLINE"))
    ) ? ast_list_of(_compound_statement) : 0;
    return exit_frame(_pos, res_423, FUNC);
}

// file_input:
//     | statement_list
static ast_list_t *file_input() {
    size_t _pos = pos();
    ast_list_t *res_535;
    ast_list_t *_statement_list;
    res_535 = enter_frame(FUNC) && (
        (_statement_list = statement_list())
    ) ? _statement_list : 0;
    return exit_frame(_pos, res_535, FUNC);
}

// eval_input:
//     | expressions [NEWLINE]
static ast_list_t *eval_input() {
    size_t _pos = pos();
    ast_list_t *res_471;
    ast_list_t *_expressions;
    res_471 = enter_frame(FUNC) && (
        (_expressions = expressions()) &&
        (consume(2, "NEWLINE"), 1)
    ) ? _expressions : 0;
    return exit_frame(_pos, res_471, FUNC);
}

// statement_list:
//     | line_statement+
static ast_list_t *statement_list() {
    size_t _pos = pos();
    ast_list_t *res_398;
    ast_list_t *_line_statements;
    res_398 = enter_frame(FUNC) && (
        (_line_statements = line_statement_loop())
    ) ? _line_statements : 0;
    return exit_frame(_pos, res_398, FUNC);
}

static ast_list_t *line_statement_loop() {
    ast_list_t *_line_statement = line_statement();
    if (!_line_statement) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    do {
        ast_list_append(list, _line_statement);
    } while ((_line_statement = line_statement()));
    return list;
}

// line_statement:
//     | simple_statements NEWLINE
//     | compound_statement NEWLINE
static ast_list_t *line_statement() {
    size_t _pos = pos();
    ast_list_t *res_260;
    ast_list_t *alt_260;
    res_260 = enter_frame(FUNC) && (
        (alt_260 = line_statement_1()) ||
        (alt_260 = line_statement_2())
    ) ? alt_260 : 0;
    return exit_frame(_pos, res_260, FUNC);
}

// simple_statements NEWLINE
static ast_list_t *line_statement_1() {
    size_t _pos = pos();
    ast_list_t *res_726;
    ast_list_t *_simple_statements;
    res_726 = enter_frame(FUNC) && (
        (_simple_statements = simple_statements()) &&
        (consume(2, "NEWLINE"))
    ) ? _simple_statements : 0;
    return exit_frame(_pos, res_726, FUNC);
}

// compound_statement NEWLINE
static ast_list_t *line_statement_2() {
    size_t _pos = pos();
    ast_list_t *res_727;
    void *_compound_statement;
    res_727 = enter_frame(FUNC) && (
        (_compound_statement = compound_statement()) &&
        (consume(2, "NEWLINE"))
    ) ? ast_list_of(_compound_statement) : 0;
    return exit_frame(_pos, res_727, FUNC);
}

// simple_statements:
//     | ';'.simple_statement+ [';']
static ast_list_t *simple_statements() {
    size_t _pos = pos();
    ast_list_t *res_129;
    ast_list_t *_simple_statements;
    res_129 = enter_frame(FUNC) && (
        (_simple_statements = simple_statement_delimited()) &&
        (consume(12, ";"), 1)
    ) ? _simple_statements : 0;
    return exit_frame(_pos, res_129, FUNC);
}

static ast_list_t *simple_statement_delimited() {
    ast_stmt_t *_simple_statement = simple_statement();
    if (!_simple_statement) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    size_t _pos;
    do {
        ast_list_append(list, _simple_statement);
        _pos = pos();
    } while (consume(12, ";") &&
            (_simple_statement = simple_statement()));
    restore(_pos);
    return list;
}

static ast_stmt_t *ast_break() {
    return node();
}

static ast_stmt_t *ast_continue() {
    return node();
}

static ast_stmt_t *ast_del(ast_list_t *li) {
    return node();
}

static ast_stmt_t *ast_return(ast_list_t *li) {
    return node();
}

static ast_named_t *ast_named(token_t *name, ast_expr_t *expr) {
    return node();
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
static ast_stmt_t *simple_statement() {
    size_t _pos = pos();
    ast_stmt_t *res_930;
    ast_stmt_t *alt_930;
    res_930 = enter_frame(FUNC) && (
        (alt_930 = assignment()) || (
            (starred_expressions()) &&
            (alt_930 = node())
        ) || (
            (consume(64, "pass")) &&
            (alt_930 = ast_nop())
        ) || (
            (consume(74, "break")) &&
            (alt_930 = ast_break())
        ) || (
            (consume(73, "continue")) &&
            (alt_930 = ast_continue())
        ) ||
        (alt_930 = simple_statement_6()) ||
        (alt_930 = simple_statement_7()) ||
        (alt_930 = simple_statement_8())
    ) ? alt_930 : 0;
    return exit_frame(_pos, res_930, FUNC);
}

// 'return' [starred_expressions]
static ast_stmt_t *simple_statement_6() {
    size_t _pos = pos();
    ast_list_t *_starred_expressions;
    return (
        (consume(54, "return")) &&
        (_starred_expressions = starred_expressions(), 1)
    ) ? ast_return(_starred_expressions) :
        (restore(_pos), NULL);
}

// 'raise' expression ['from' expression]
static ast_stmt_t *simple_statement_7() {
    size_t _pos = pos();
    return (
        (consume(78, "raise")) &&
        (expression()) &&
        (simple_statement_7_3(), 1)
    ) ? ast_nop() : (restore(_pos), NULL);
}

// 'from' expression
static ast_expr_t *simple_statement_7_3() {
    size_t _pos = pos();
    ast_expr_t *_expression;
    return (
        (consume(66, "from")) &&
        (_expression = expression())
    ) ? _expression : (restore(_pos), NULL);
}

// 'del' targets
static ast_stmt_t *simple_statement_8() {
    size_t _pos = pos();
    ast_list_t *_targets;
    return (
        (consume(79, "del")) &&
        (_targets = targets())
    ) ? ast_del(_targets) : (restore(_pos), NULL);
}

// target (memo):
//     | t_primary '.' NAME !t_lookahead
//     | t_primary subscript !t_lookahead
//     | NAME
static void *target() {
    size_t _pos = pos();
    void *res_161;
    memo_t *memo = fetch_memo(161, FUNC);
    if (memo) {
        return memo->node;
    }
    void *alt_161;
    res_161 = enter_frame(FUNC) && (
        (alt_161 = target_1()) ||
        (alt_161 = target_2()) ||
        (alt_161 = consume(3, "NAME"))
    ) ? alt_161 : 0;
    insert_memo(_pos, 161, res_161);
    return exit_frame(_pos, res_161, FUNC);
}

// t_primary '.' NAME !t_lookahead
static void *target_1() {
    size_t _pos = pos();
    return (
        (t_primary()) &&
        (consume(6, ".")) &&
        (consume(3, "NAME")) &&
        (!test_and_reset(_pos, t_lookahead()))
    ) ? node() : (restore(_pos), NULL);
}

// t_primary subscript !t_lookahead
static void *target_2() {
    size_t _pos = pos();
    return (
        (t_primary()) &&
        (subscript()) &&
        (!test_and_reset(_pos, t_lookahead()))
    ) ? node() : (restore(_pos), NULL);
}

// t_primary (left_recursive):
//     | t_primary '.' NAME &t_lookahead
//     | t_primary invocation &t_lookahead
//     | t_primary subscript &t_lookahead
//     | atom &t_lookahead
static ast_primary_t *t_primary() {
    size_t _pos = pos();
    ast_primary_t *res_255 = 0;
    memo_t *memo = fetch_memo(255, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_primary_t *alt_255;
    size_t maxpos;
    ast_primary_t *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_255;
        insert_memo(_pos, 255, max);
        restore(_pos);
        res_255 = (
            (alt_255 = t_primary_1()) ||
            (alt_255 = t_primary_2()) ||
            (alt_255 = t_primary_3()) ||
            (alt_255 = t_primary_4())
        ) ? alt_255 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_255 = max;
    insert_memo(_pos, 255, res_255);
    return exit_frame(_pos, res_255, FUNC);
}

// t_primary '.' NAME &t_lookahead
static ast_primary_t *t_primary_1() {
    size_t _pos = pos();
    return (
        (t_primary()) &&
        (consume(6, ".")) &&
        (consume(3, "NAME")) &&
        (test_and_reset(_pos, t_lookahead()))
    ) ? node() : (restore(_pos), NULL);
}

// t_primary invocation &t_lookahead
static ast_primary_t *t_primary_2() {
    size_t _pos = pos();
    return (
        (t_primary()) &&
        (invocation()) &&
        (test_and_reset(_pos, t_lookahead()))
    ) ? node() : (restore(_pos), NULL);
}

// t_primary subscript &t_lookahead
static ast_primary_t *t_primary_3() {
    size_t _pos = pos();
    return (
        (t_primary()) &&
        (subscript()) &&
        (test_and_reset(_pos, t_lookahead()))
    ) ? node() : (restore(_pos), NULL);
}

// atom &t_lookahead
static ast_primary_t *t_primary_4() {
    size_t _pos = pos();
    ast_primary_t *_atom;
    return (
        (_atom = atom()) &&
        (test_and_reset(_pos, t_lookahead()))
    ) ? _atom : (restore(_pos), NULL);
}

// t_lookahead (inline):
//     | '.'
//     | '('
//     | '['
static void *t_lookahead() {
    size_t _pos = pos();
    void *alt;
    return (
        (alt = consume(6, ".")) ||
        (alt = consume(13, "(")) ||
        (alt = consume(17, "["))
    ) ? alt : (restore(_pos), NULL);
}

// targets:
//     | ','.target+ [',']
static ast_list_t *targets() {
    size_t _pos = pos();
    ast_list_t *res_882;
    ast_list_t *_targets;
    res_882 = enter_frame(FUNC) && (
        (_targets = target_delimited()) &&
        (consume(7, ","), 1)
    ) ? _targets : 0;
    return exit_frame(_pos, res_882, FUNC);
}

static ast_list_t *target_delimited() {
    void *_target = target();
    if (!_target) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    size_t _pos;
    do {
        ast_list_append(list, _target);
        _pos = pos();
    } while (consume(7, ",") &&
            (_target = target()));
    restore(_pos);
    return list;
}

// assignment:
//     | target ':' expression ['=' expressions]
//     | (targets '=')+ starred_expressions
//     | target augmented_assign expressions
static void *assignment() {
    size_t _pos = pos();
    void *res_733;
    void *alt_733;
    res_733 = enter_frame(FUNC) && (
        (alt_733 = assignment_1()) ||
        (alt_733 = assignment_2()) ||
        (alt_733 = assignment_3())
    ) ? alt_733 : 0;
    return exit_frame(_pos, res_733, FUNC);
}

// target ':' expression ['=' expressions]
static void *assignment_1() {
    size_t _pos = pos();
    return (
        (target()) &&
        (consume(9, ":")) &&
        (expression()) &&
        (assignment_1_4(), 1)
    ) ? node() : (restore(_pos), NULL);
}

// '=' expressions
static void *assignment_1_4() {
    size_t _pos = pos();
    ast_list_t *_expressions;
    return (
        (consume(8, "=")) &&
        (_expressions = expressions())
    ) ? _expressions : (restore(_pos), NULL);
}

// (targets '=')+ starred_expressions
static void *assignment_2() {
    size_t _pos = pos();
    return (
        (assignment_2_1_loop()) &&
        (starred_expressions())
    ) ? node() : (restore(_pos), NULL);
}

static ast_list_t *assignment_2_1_loop() {
    void *_targets_assign = assignment_2_1();
    if (!_targets_assign) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    do {
        ast_list_append(list, _targets_assign);
    } while ((_targets_assign = assignment_2_1()));
    return list;
}

// targets '='
static void *assignment_2_1() {
    size_t _pos = pos();
    ast_list_t *_targets;
    return (
        (_targets = targets()) &&
        (consume(8, "="))
    ) ? _targets : (restore(_pos), NULL);
}

// target augmented_assign expressions
static void *assignment_3() {
    size_t _pos = pos();
    return (
        (target()) &&
        (augmented_assign()) &&
        (expressions())
    ) ? node() : (restore(_pos), NULL);
}

// augmented_assign (inline):
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
static int augmented_assign() {
    size_t _pos = pos();
    int alt;
    return ((
            (consume(39, "+=")) &&
            (alt = BINOP_PLS)
        ) || (
            (consume(40, "-=")) &&
            (alt = BINOP_MIN)
        ) || (
            (consume(41, "*=")) &&
            (alt = BINOP_MUL)
        ) || (
            (consume(42, "/=")) &&
            (alt = BINOP_DIV)
        ) || (
            (consume(43, "%=")) &&
            (alt = BINOP_MOD)
        ) || (
            (consume(44, "@=")) &&
            (alt = BINOP_MML)
        ) || (
            (consume(45, "|=")) &&
            (alt = BINOP_IOR)
        ) || (
            (consume(46, "&=")) &&
            (alt = BINOP_AND)
        ) || (
            (consume(47, "^=")) &&
            (alt = BINOP_XOR)
        ) || (
            (consume(50, "//=")) &&
            (alt = BINOP_FDV)
        ) || (
            (consume(51, "**=")) &&
            (alt = BINOP_POW)
        ) || (
            (consume(52, "<<=")) &&
            (alt = BINOP_SHL)
        ) || (
            (consume(53, ">>=")) &&
            (alt = BINOP_SHR))
    ) ? alt : (restore(_pos), 0);
}

// compound_statement:
//     | if_statement
//     | while_statement
//     | for_statement
//     | try_statement
//     | with_statement
static void *compound_statement() {
    size_t _pos = pos();
    void *res_147;
    void *alt_147;
    res_147 = enter_frame(FUNC) && (
        (alt_147 = if_statement()) ||
        (alt_147 = while_statement()) ||
        (alt_147 = for_statement()) ||
        (alt_147 = try_statement()) ||
        (alt_147 = with_statement())
    ) ? alt_147 : 0;
    return exit_frame(_pos, res_147, FUNC);
}

// if_statement:
//     | 'if' named_expression suite elif_statement* [else_suite]
static void *if_statement() {
    size_t _pos = pos();
    void *res_621;
    ast_named_t *_named_expression;
    void *_suite;
    ast_list_t *_elif_statements;
    void *_else_suite;
    res_621 = enter_frame(FUNC) && (
        (consume(56, "if")) &&
        (_named_expression = named_expression()) &&
        (_suite = suite()) &&
        (_elif_statements = elif_statement_loop()) &&
        (_else_suite = else_suite(), 1)
    ) ? node() : 0;
    return exit_frame(_pos, res_621, FUNC);
}

static ast_list_t *elif_statement_loop() {
    ast_list_t *list = ast_list_new();
    void *_elif_statement;
    while ((_elif_statement = elif_statement())) {
        ast_list_append(list, _elif_statement);
    }
    return list;
}

// elif_statement:
//     | 'elif' named_expression suite
static void *elif_statement() {
    size_t _pos = pos();
    void *res_660;
    ast_named_t *_named_expression;
    void *_suite;
    res_660 = enter_frame(FUNC) && (
        (consume(57, "elif")) &&
        (_named_expression = named_expression()) &&
        (_suite = suite())
    ) ? node() : 0;
    return exit_frame(_pos, res_660, FUNC);
}

// while_statement:
//     | 'while' named_expression suite [else_suite]
static void *while_statement() {
    size_t _pos = pos();
    void *res_865;
    ast_named_t *_named_expression;
    void *_suite;
    void *_else_suite;
    res_865 = enter_frame(FUNC) && (
        (consume(71, "while")) &&
        (_named_expression = named_expression()) &&
        (_suite = suite()) &&
        (_else_suite = else_suite(), 1)
    ) ? node() : 0;
    return exit_frame(_pos, res_865, FUNC);
}

// for_statement:
//     | 'for' targets 'in' expressions suite [else_suite]
static void *for_statement() {
    size_t _pos = pos();
    void *res_465;
    ast_list_t *_targets;
    ast_list_t *_expressions;
    void *_suite;
    void *_else_suite;
    res_465 = enter_frame(FUNC) && (
        (consume(72, "for")) &&
        (_targets = targets()) &&
        (consume(63, "in")) &&
        (_expressions = expressions()) &&
        (_suite = suite()) &&
        (_else_suite = else_suite(), 1)
    ) ? node() : 0;
    return exit_frame(_pos, res_465, FUNC);
}

// try_statement:
//     | 'try' suite (except_suite | finally_suite)
static void *try_statement() {
    size_t _pos = pos();
    void *res_195;
    void *_suite;
    void *_except_suite_or_finally_suite;
    res_195 = enter_frame(FUNC) && (
        (consume(75, "try")) &&
        (_suite = suite()) &&
        (_except_suite_or_finally_suite = try_statement_3())
    ) ? node() : 0;
    return exit_frame(_pos, res_195, FUNC);
}

// except_suite | finally_suite
static void *try_statement_3() {
    size_t _pos = pos();
    void *res_663;
    void *alt_663;
    res_663 = enter_frame(FUNC) && (
        (alt_663 = except_suite()) ||
        (alt_663 = finally_suite())
    ) ? alt_663 : 0;
    return exit_frame(_pos, res_663, FUNC);
}

// with_statement:
//     | 'with' ','.expression_as_name+ suite
static void *with_statement() {
    size_t _pos = pos();
    void *res_214;
    ast_list_t *_expression_as_names;
    void *_suite;
    res_214 = enter_frame(FUNC) && (
        (consume(68, "with")) &&
        (_expression_as_names = expression_as_name_delimited()) &&
        (_suite = suite())
    ) ? node() : 0;
    return exit_frame(_pos, res_214, FUNC);
}

static ast_list_t *expression_as_name_delimited() {
    void *_expression_as_name = expression_as_name();
    if (!_expression_as_name) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    size_t _pos;
    do {
        ast_list_append(list, _expression_as_name);
        _pos = pos();
    } while (consume(7, ",") &&
            (_expression_as_name = expression_as_name()));
    restore(_pos);
    return list;
}

// expression_as_name:
//     | expression ['as' NAME]
static void *expression_as_name() {
    size_t _pos = pos();
    void *res_169;
    ast_expr_t *_expression;
    token_t *_as_name;
    res_169 = enter_frame(FUNC) && (
        (_expression = expression()) &&
        (_as_name = expression_as_name_2(), 1)
    ) ? node() : 0;
    return exit_frame(_pos, res_169, FUNC);
}

// 'as' NAME
static token_t *expression_as_name_2() {
    size_t _pos = pos();
    token_t *_name;
    return (
        (consume(65, "as")) &&
        (_name = consume(3, "NAME"))
    ) ? _name : (restore(_pos), NULL);
}

// block_suite:
//     | '{' NEWLINE statement_list '}'
//     | '{' [simple_statements] '}'
static void *block_suite() {
    size_t _pos = pos();
    void *res_206;
    void *alt_206;
    res_206 = enter_frame(FUNC) && (
        (alt_206 = block_suite_1()) ||
        (alt_206 = block_suite_2())
    ) ? alt_206 : 0;
    return exit_frame(_pos, res_206, FUNC);
}

// '{' NEWLINE statement_list '}'
static void *block_suite_1() {
    size_t _pos = pos();
    void *res_560;
    ast_list_t *_statement_list;
    res_560 = enter_frame(FUNC) && (
        (consume(15, "{")) &&
        (consume(2, "NEWLINE")) &&
        (_statement_list = statement_list()) &&
        (consume(16, "}"))
    ) ? _statement_list : 0;
    return exit_frame(_pos, res_560, FUNC);
}

// '{' [simple_statements] '}'
static void *block_suite_2() {
    size_t _pos = pos();
    void *res_561;
    ast_list_t *_simple_statements;
    res_561 = enter_frame(FUNC) && (
        (consume(15, "{")) &&
        (_simple_statements = simple_statements(), 1) &&
        (consume(16, "}"))
    ) ? _simple_statements : 0;
    return exit_frame(_pos, res_561, FUNC);
}

// suite:
//     | ':' simple_statements
//     | block_suite
static void *suite() {
    size_t _pos = pos();
    void *res_64;
    void *alt_64;
    res_64 = enter_frame(FUNC) && (
        (alt_64 = suite_1()) ||
        (alt_64 = block_suite())
    ) ? alt_64 : 0;
    return exit_frame(_pos, res_64, FUNC);
}

// ':' simple_statements
static void *suite_1() {
    size_t _pos = pos();
    void *res_98;
    ast_list_t *_simple_statements;
    res_98 = enter_frame(FUNC) && (
        (consume(9, ":")) &&
        (_simple_statements = simple_statements())
    ) ? _simple_statements : 0;
    return exit_frame(_pos, res_98, FUNC);
}

// else_suite (inline):
//     | 'else' suite
static void *else_suite() {
    size_t _pos = pos();
    void *_suite;
    return (
        (consume(58, "else")) &&
        (_suite = suite())
    ) ? _suite : (restore(_pos), NULL);
}

// finally_suite (inline):
//     | 'finally' suite
static void *finally_suite() {
    size_t _pos = pos();
    void *_suite;
    return (
        (consume(77, "finally")) &&
        (_suite = suite())
    ) ? _suite : (restore(_pos), NULL);
}

// except_clause:
//     | 'except' [expression_as_name] suite
static void *except_clause() {
    size_t _pos = pos();
    void *res_357;
    void *_expression_as_name;
    void *_suite;
    res_357 = enter_frame(FUNC) && (
        (consume(76, "except")) &&
        (_expression_as_name = expression_as_name(), 1) &&
        (_suite = suite())
    ) ? node() : 0;
    return exit_frame(_pos, res_357, FUNC);
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
static void *except_suite() {
    size_t _pos = pos();
    void *res_810;
    ast_list_t *_except_clauses;
    void *_else_suite;
    void *_finally_suite;
    res_810 = enter_frame(FUNC) && (
        (_except_clauses = except_clause_loop()) &&
        (_else_suite = else_suite(), 1) &&
        (_finally_suite = finally_suite(), 1)
    ) ? node() : 0;
    return exit_frame(_pos, res_810, FUNC);
}

static ast_list_t *except_clause_loop() {
    void *_except_clause = except_clause();
    if (!_except_clause) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    do {
        ast_list_append(list, _except_clause);
    } while ((_except_clause = except_clause()));
    return list;
}

// invocation:
//     | '(' [','.call_argument+ [',']] ')'
static void *invocation() {
    size_t _pos = pos();
    void *res_944;
    void *_invocation_2;
    res_944 = enter_frame(FUNC) && (
        (consume(13, "(")) &&
        (_invocation_2 = invocation_2(), 1) &&
        (consume(14, ")"))
    ) ? _invocation_2 : 0;
    return exit_frame(_pos, res_944, FUNC);
}

// ','.call_argument+ [',']
static void *invocation_2() {
    size_t _pos = pos();
    void *res_35;
    ast_list_t *_call_arguments;
    res_35 = enter_frame(FUNC) && (
        (_call_arguments = call_argument_delimited()) &&
        (consume(7, ","), 1)
    ) ? _call_arguments : 0;
    return exit_frame(_pos, res_35, FUNC);
}

static ast_list_t *call_argument_delimited() {
    void *_call_argument = call_argument();
    if (!_call_argument) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    size_t _pos;
    do {
        ast_list_append(list, _call_argument);
        _pos = pos();
    } while (consume(7, ",") &&
            (_call_argument = call_argument()));
    restore(_pos);
    return list;
}

// call_argument:
//     | NAME ':=' expression
//     | NAME '=' expression
//     | '**' expression
//     | '*' expression
//     | expression
static void *call_argument() {
    size_t _pos = pos();
    void *res_78;
    void *alt_78;
    res_78 = enter_frame(FUNC) && (
        (alt_78 = call_argument_1()) ||
        (alt_78 = call_argument_2()) ||
        (alt_78 = call_argument_3()) ||
        (alt_78 = call_argument_4()) ||
        (alt_78 = expression())
    ) ? alt_78 : 0;
    return exit_frame(_pos, res_78, FUNC);
}

// NAME ':=' expression
static void *call_argument_1() {
    size_t _pos = pos();
    token_t *_name;
    ast_expr_t *_expression;
    return (
        (_name = consume(3, "NAME")) &&
        (consume(36, ":=")) &&
        (_expression = expression())
    ) ? ast_named(_name, _expression) :
        (restore(_pos), NULL);
}

// NAME '=' expression
static void *call_argument_2() {
    size_t _pos = pos();
    token_t *_name;
    ast_expr_t *_expression;
    return (
        (_name = consume(3, "NAME")) &&
        (consume(8, "=")) &&
        (_expression = expression())
    ) ? ast_named(_name, _expression) :
        (restore(_pos), NULL);
}

// '**' expression
static void *call_argument_3() {
    size_t _pos = pos();
    ast_expr_t *_expression;
    return (
        (consume(38, "**")) &&
        (_expression = expression())
    ) ? _expression : (restore(_pos), NULL);
}

// '*' expression
static void *call_argument_4() {
    size_t _pos = pos();
    ast_expr_t *_expression;
    return (
        (consume(23, "*")) &&
        (_expression = expression())
    ) ? _expression : (restore(_pos), NULL);
}

// subscript:
//     | '[' ','.slice+ [','] ']'
static ast_list_t *subscript() {
    size_t _pos = pos();
    ast_list_t *res_379;
    ast_list_t *_slices;
    res_379 = enter_frame(FUNC) && (
        (consume(17, "[")) &&
        (_slices = slice_delimited()) &&
        (consume(7, ","), 1) &&
        (consume(18, "]"))
    ) ? _slices : 0;
    return exit_frame(_pos, res_379, FUNC);
}

static ast_list_t *slice_delimited() {
    void *_slice = slice();
    if (!_slice) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    size_t _pos;
    do {
        ast_list_append(list, _slice);
        _pos = pos();
    } while (consume(7, ",") &&
            (_slice = slice()));
    restore(_pos);
    return list;
}

// slice:
//     | [expression] slice_expression [slice_expression]
//     | expression
static void *slice() {
    size_t _pos = pos();
    void *res_418;
    void *alt_418;
    res_418 = enter_frame(FUNC) && (
        (alt_418 = slice_1()) ||
        (alt_418 = expression())
    ) ? alt_418 : 0;
    return exit_frame(_pos, res_418, FUNC);
}

// [expression] slice_expression [slice_expression]
static void *slice_1() {
    size_t _pos = pos();
    void *res_292;
    ast_expr_t *_expression;
    void *_slice_expression;
    void *_slice_expression_1;
    res_292 = enter_frame(FUNC) && (
        (_expression = expression(), 1) &&
        (_slice_expression = slice_expression()) &&
        (_slice_expression_1 = slice_expression(), 1)
    ) ? node() : 0;
    return exit_frame(_pos, res_292, FUNC);
}

// slice_expression:
//     | ':' [expression]
static void *slice_expression() {
    size_t _pos = pos();
    void *res_421;
    ast_expr_t *_expression;
    res_421 = enter_frame(FUNC) && (
        (consume(9, ":")) &&
        (_expression = expression(), 1)
    ) ? _expression : 0;
    return exit_frame(_pos, res_421, FUNC);
}

// expressions:
//     | ','.expression+ [',']
static ast_list_t *expressions() {
    size_t _pos = pos();
    ast_list_t *res_779;
    ast_list_t *_expressions;
    res_779 = enter_frame(FUNC) && (
        (_expressions = expression_delimited()) &&
        (consume(7, ","), 1)
    ) ? _expressions : 0;
    return exit_frame(_pos, res_779, FUNC);
}

static ast_list_t *expression_delimited() {
    ast_expr_t *_expression = expression();
    if (!_expression) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    size_t _pos;
    do {
        ast_list_append(list, _expression);
        _pos = pos();
    } while (consume(7, ",") &&
            (_expression = expression()));
    restore(_pos);
    return list;
}

// starred_expression (inline):
//     | '*' bitwise_or
static ast_expr_t *starred_expression() {
    size_t _pos = pos();
    ast_expr_t *_bitwise_or;
    return (
        (consume(23, "*")) &&
        (_bitwise_or = bitwise_or())
    ) ? _bitwise_or : (restore(_pos), NULL);
}

// maybe_starred:
//     | starred_expression
//     | expression
static ast_expr_t *maybe_starred() {
    size_t _pos = pos();
    ast_expr_t *res_984;
    ast_expr_t *alt_984;
    res_984 = enter_frame(FUNC) && (
        (alt_984 = starred_expression()) ||
        (alt_984 = expression())
    ) ? alt_984 : 0;
    return exit_frame(_pos, res_984, FUNC);
}

// starred_expressions:
//     | ','.maybe_starred+ [',']
static ast_list_t *starred_expressions() {
    size_t _pos = pos();
    ast_list_t *res_171;
    ast_list_t *_maybe_starreds;
    res_171 = enter_frame(FUNC) && (
        (_maybe_starreds = maybe_starred_delimited()) &&
        (consume(7, ","), 1)
    ) ? _maybe_starreds : 0;
    return exit_frame(_pos, res_171, FUNC);
}

static ast_list_t *maybe_starred_delimited() {
    ast_expr_t *_maybe_starred = maybe_starred();
    if (!_maybe_starred) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    size_t _pos;
    do {
        ast_list_append(list, _maybe_starred);
        _pos = pos();
    } while (consume(7, ",") &&
            (_maybe_starred = maybe_starred()));
    restore(_pos);
    return list;
}

static ast_expr_t *ast_conditional(
        ast_expr_t *cond, ast_expr_t *a, ast_expr_t *b) {
    return node();
}

static ast_named_t *ast_unnamed(ast_expr_t *expr) {
    return ast_named(NULL, expr);
}

static ast_expr_t *ast_comp_term(
        int comp_op, ast_expr_t *operand) {
    return node();
}

static ast_expr_t *ast_comparison(
        ast_expr_t *first, ast_list_t *terms) {
    return node();
}

// named_expression:
//     | NAME ':=' expression
//     | expression
static ast_named_t *named_expression() {
    size_t _pos = pos();
    ast_named_t *res_358;
    ast_expr_t *_expression;
    ast_named_t *alt_358;
    res_358 = enter_frame(FUNC) && (
        (alt_358 = named_expression_1()) || (
            (_expression = expression()) &&
            (alt_358 = ast_unnamed(_expression)))
    ) ? alt_358 : 0;
    return exit_frame(_pos, res_358, FUNC);
}

// NAME ':=' expression
static ast_named_t *named_expression_1() {
    size_t _pos = pos();
    token_t *_name;
    ast_expr_t *_expression;
    return (
        (_name = consume(3, "NAME")) &&
        (consume(36, ":=")) &&
        (_expression = expression())
    ) ? ast_named(_name, _expression) :
        (restore(_pos), NULL);
}

// conditional (inline):
//     | 'if' disjunction '?' disjunction ':' expression
static ast_expr_t *conditional() {
    size_t _pos = pos();
    ast_expr_t *_disjunction;
    ast_expr_t *_disjunction_1;
    ast_expr_t *_expression;
    return (
        (consume(56, "if")) &&
        (_disjunction = disjunction()) &&
        (consume(10, "?")) &&
        (_disjunction_1 = disjunction()) &&
        (consume(9, ":")) &&
        (_expression = expression())
    ) ? ast_conditional(_disjunction, _disjunction_1, _expression) :
        (restore(_pos), NULL);
}

// expression:
//     | conditional
//     | disjunction
static ast_expr_t *expression() {
    size_t _pos = pos();
    ast_expr_t *res_736;
    ast_expr_t *alt_736;
    res_736 = enter_frame(FUNC) && (
        (alt_736 = conditional()) ||
        (alt_736 = disjunction())
    ) ? alt_736 : 0;
    return exit_frame(_pos, res_736, FUNC);
}

// Construct a binary operation
static ast_expr_t *ast_binary(ast_expr_t *left,
        ast_expr_t *right, enum expr_opcode binop_code) {
    ast_expr_t *r = palloc(sizeof(ast_expr_t));
    r->opcode = binop_code;
    r->left = left;
    r->right.expr = right;
    return r;
}

// Construct a unary operation
static ast_expr_t *ast_unary(ast_expr_t *expr,
        enum expr_opcode unary_opcode) {
    return ast_binary(expr, NULL, unary_opcode);
}

// disjunction (left_recursive):
//     | disjunction 'or' conjunction
//     | conjunction
static ast_expr_t *disjunction() {
    size_t _pos = pos();
    ast_expr_t *res_410 = 0;
    memo_t *memo = fetch_memo(410, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_expr_t *alt_410;
    size_t maxpos;
    ast_expr_t *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_410;
        insert_memo(_pos, 410, max);
        restore(_pos);
        res_410 = (
            (alt_410 = disjunction_1()) ||
            (alt_410 = conjunction())
        ) ? alt_410 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_410 = max;
    insert_memo(_pos, 410, res_410);
    return exit_frame(_pos, res_410, FUNC);
}

// disjunction 'or' conjunction
static ast_expr_t *disjunction_1() {
    size_t _pos = pos();
    ast_expr_t *_disjunction;
    ast_expr_t *_conjunction;
    return (
        (_disjunction = disjunction()) &&
        (consume(60, "or")) &&
        (_conjunction = conjunction())
    ) ? ast_binary(_disjunction, _conjunction, LOGIC_OR) :
        (restore(_pos), NULL);
}

// conjunction (left_recursive):
//     | conjunction 'and' inversion
//     | inversion
static ast_expr_t *conjunction() {
    size_t _pos = pos();
    ast_expr_t *res_462 = 0;
    memo_t *memo = fetch_memo(462, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_expr_t *alt_462;
    size_t maxpos;
    ast_expr_t *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_462;
        insert_memo(_pos, 462, max);
        restore(_pos);
        res_462 = (
            (alt_462 = conjunction_1()) ||
            (alt_462 = inversion())
        ) ? alt_462 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_462 = max;
    insert_memo(_pos, 462, res_462);
    return exit_frame(_pos, res_462, FUNC);
}

// conjunction 'and' inversion
static ast_expr_t *conjunction_1() {
    size_t _pos = pos();
    ast_expr_t *_conjunction;
    ast_expr_t *_inversion;
    return (
        (_conjunction = conjunction()) &&
        (consume(59, "and")) &&
        (_inversion = inversion())
    ) ? ast_binary(_conjunction, _inversion, LOGIC_AND) :
        (restore(_pos), NULL);
}

// inversion:
//     | 'not' inversion
//     | comparison
static ast_expr_t *inversion() {
    size_t _pos = pos();
    ast_expr_t *res_963;
    ast_expr_t *alt_963;
    res_963 = enter_frame(FUNC) && (
        (alt_963 = inversion_1()) ||
        (alt_963 = comparison())
    ) ? alt_963 : 0;
    return exit_frame(_pos, res_963, FUNC);
}

// 'not' inversion
static ast_expr_t *inversion_1() {
    size_t _pos = pos();
    ast_expr_t *_inversion;
    return (
        (consume(61, "not")) &&
        (_inversion = inversion())
    ) ? ast_unary(_inversion, LOGIC_NOT) :
        (restore(_pos), NULL);
}

// comparison:
//     | bitwise_or (comparator bitwise_or)+
//     | bitwise_or
static ast_expr_t *comparison() {
    size_t _pos = pos();
    ast_expr_t *res_529;
    ast_expr_t *alt_529;
    res_529 = enter_frame(FUNC) && (
        (alt_529 = comparison_1()) ||
        (alt_529 = bitwise_or())
    ) ? alt_529 : 0;
    return exit_frame(_pos, res_529, FUNC);
}

// bitwise_or (comparator bitwise_or)+
static ast_expr_t *comparison_1() {
    size_t _pos = pos();
    ast_expr_t *_bitwise_or;
    ast_list_t *_comparator_bitwise_ors;
    return (
        (_bitwise_or = bitwise_or()) &&
        (_comparator_bitwise_ors = comparison_1_2_loop())
    ) ? ast_comparison(_bitwise_or, _comparator_bitwise_ors) :
        (restore(_pos), NULL);
}

static ast_list_t *comparison_1_2_loop() {
    ast_expr_t *_comparator_bitwise_or = comparison_1_2();
    if (!_comparator_bitwise_or) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    do {
        ast_list_append(list, _comparator_bitwise_or);
    } while ((_comparator_bitwise_or = comparison_1_2()));
    return list;
}

// comparator bitwise_or
static ast_expr_t *comparison_1_2() {
    size_t _pos = pos();
    int _comparator;
    ast_expr_t *_bitwise_or;
    return (
        (_comparator = comparator()) &&
        (_bitwise_or = bitwise_or())
    ) ? ast_comp_term(_comparator, _bitwise_or) :
        (restore(_pos), NULL);
}

// comparator (inline):
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
static int comparator() {
    size_t _pos = pos();
    int alt;
    return ((
            (consume(19, "<")) &&
            (alt = CMP_LT)
        ) || (
            (consume(20, ">")) &&
            (alt = CMP_GT)
        ) || (
            (consume(31, "==")) &&
            (alt = CMP_EQ)
        ) || (
            (consume(34, ">=")) &&
            (alt = CMP_GE)
        ) || (
            (consume(33, "<=")) &&
            (alt = CMP_LE)
        ) || (
            (consume(32, "!=")) &&
            (alt = CMP_NE)
        ) || (
            (consume(63, "in")) &&
            (alt = CMP_IN)
        ) ||
        (alt = comparator_8()) || (
            (consume(62, "is")) &&
            (alt = CMP_IS)
        ) ||
        (alt = comparator_10())
    ) ? alt : (restore(_pos), 0);
}

// 'not' 'in'
static int comparator_8() {
    size_t _pos = pos();
    return (
        (consume(61, "not")) &&
        (consume(63, "in"))
    ) ? CMP_NI : (restore(_pos), 0);
}

// 'is' 'not'
static int comparator_10() {
    size_t _pos = pos();
    return (
        (consume(62, "is")) &&
        (consume(61, "not"))
    ) ? CMP_NS : (restore(_pos), 0);
}

// bitwise_or (left_recursive):
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
static ast_expr_t *bitwise_or() {
    size_t _pos = pos();
    ast_expr_t *res_201 = 0;
    memo_t *memo = fetch_memo(201, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_expr_t *alt_201;
    size_t maxpos;
    ast_expr_t *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_201;
        insert_memo(_pos, 201, max);
        restore(_pos);
        res_201 = (
            (alt_201 = bitwise_or_1()) ||
            (alt_201 = bitwise_xor())
        ) ? alt_201 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_201 = max;
    insert_memo(_pos, 201, res_201);
    return exit_frame(_pos, res_201, FUNC);
}

// bitwise_or '|' bitwise_xor
static ast_expr_t *bitwise_or_1() {
    size_t _pos = pos();
    ast_expr_t *_bitwise_or;
    ast_expr_t *_bitwise_xor;
    return (
        (_bitwise_or = bitwise_or()) &&
        (consume(27, "|")) &&
        (_bitwise_xor = bitwise_xor())
    ) ? ast_binary(_bitwise_or, _bitwise_xor, BINOP_IOR) :
        (restore(_pos), NULL);
}

// bitwise_xor (left_recursive):
//     | bitwise_xor '^' bitwise_and
//     | bitwise_and
static ast_expr_t *bitwise_xor() {
    size_t _pos = pos();
    ast_expr_t *res_565 = 0;
    memo_t *memo = fetch_memo(565, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_expr_t *alt_565;
    size_t maxpos;
    ast_expr_t *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_565;
        insert_memo(_pos, 565, max);
        restore(_pos);
        res_565 = (
            (alt_565 = bitwise_xor_1()) ||
            (alt_565 = bitwise_and())
        ) ? alt_565 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_565 = max;
    insert_memo(_pos, 565, res_565);
    return exit_frame(_pos, res_565, FUNC);
}

// bitwise_xor '^' bitwise_and
static ast_expr_t *bitwise_xor_1() {
    size_t _pos = pos();
    ast_expr_t *_bitwise_xor;
    ast_expr_t *_bitwise_and;
    return (
        (_bitwise_xor = bitwise_xor()) &&
        (consume(30, "^")) &&
        (_bitwise_and = bitwise_and())
    ) ? ast_binary(_bitwise_xor, _bitwise_and, BINOP_XOR) :
        (restore(_pos), NULL);
}

// bitwise_and (left_recursive):
//     | bitwise_and '&' bitwise_shift
//     | bitwise_shift
static ast_expr_t *bitwise_and() {
    size_t _pos = pos();
    ast_expr_t *res_417 = 0;
    memo_t *memo = fetch_memo(417, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_expr_t *alt_417;
    size_t maxpos;
    ast_expr_t *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_417;
        insert_memo(_pos, 417, max);
        restore(_pos);
        res_417 = (
            (alt_417 = bitwise_and_1()) ||
            (alt_417 = bitwise_shift())
        ) ? alt_417 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_417 = max;
    insert_memo(_pos, 417, res_417);
    return exit_frame(_pos, res_417, FUNC);
}

// bitwise_and '&' bitwise_shift
static ast_expr_t *bitwise_and_1() {
    size_t _pos = pos();
    ast_expr_t *_bitwise_and;
    ast_expr_t *_bitwise_shift;
    return (
        (_bitwise_and = bitwise_and()) &&
        (consume(28, "&")) &&
        (_bitwise_shift = bitwise_shift())
    ) ? ast_binary(_bitwise_and, _bitwise_shift, BINOP_AND) :
        (restore(_pos), NULL);
}

// bitwise_shift (left_recursive):
//     | bitwise_shift '<<' sum
//     | bitwise_shift '>>' sum
//     | sum
static ast_expr_t *bitwise_shift() {
    size_t _pos = pos();
    ast_expr_t *res_532 = 0;
    memo_t *memo = fetch_memo(532, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_expr_t *alt_532;
    size_t maxpos;
    ast_expr_t *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_532;
        insert_memo(_pos, 532, max);
        restore(_pos);
        res_532 = (
            (alt_532 = bitwise_shift_1()) ||
            (alt_532 = bitwise_shift_2()) ||
            (alt_532 = sum())
        ) ? alt_532 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_532 = max;
    insert_memo(_pos, 532, res_532);
    return exit_frame(_pos, res_532, FUNC);
}

// bitwise_shift '<<' sum
static ast_expr_t *bitwise_shift_1() {
    size_t _pos = pos();
    ast_expr_t *_bitwise_shift;
    ast_expr_t *_sum;
    return (
        (_bitwise_shift = bitwise_shift()) &&
        (consume(48, "<<")) &&
        (_sum = sum())
    ) ? ast_binary(_bitwise_shift, _sum, BINOP_SHL) :
        (restore(_pos), NULL);
}

// bitwise_shift '>>' sum
static ast_expr_t *bitwise_shift_2() {
    size_t _pos = pos();
    ast_expr_t *_bitwise_shift;
    ast_expr_t *_sum;
    return (
        (_bitwise_shift = bitwise_shift()) &&
        (consume(49, ">>")) &&
        (_sum = sum())
    ) ? ast_binary(_bitwise_shift, _sum, BINOP_SHR) :
        (restore(_pos), NULL);
}

// sum (left_recursive):
//     | sum '+' term
//     | sum '-' term
//     | term
static ast_expr_t *sum() {
    size_t _pos = pos();
    ast_expr_t *res_252 = 0;
    memo_t *memo = fetch_memo(252, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_expr_t *alt_252;
    size_t maxpos;
    ast_expr_t *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_252;
        insert_memo(_pos, 252, max);
        restore(_pos);
        res_252 = (
            (alt_252 = sum_1()) ||
            (alt_252 = sum_2()) ||
            (alt_252 = term())
        ) ? alt_252 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_252 = max;
    insert_memo(_pos, 252, res_252);
    return exit_frame(_pos, res_252, FUNC);
}

// sum '+' term
static ast_expr_t *sum_1() {
    size_t _pos = pos();
    ast_expr_t *_sum;
    ast_expr_t *_term;
    return (
        (_sum = sum()) &&
        (consume(21, "+")) &&
        (_term = term())
    ) ? ast_binary(_sum, _term, BINOP_PLS) :
        (restore(_pos), NULL);
}

// sum '-' term
static ast_expr_t *sum_2() {
    size_t _pos = pos();
    ast_expr_t *_sum;
    ast_expr_t *_term;
    return (
        (_sum = sum()) &&
        (consume(22, "-")) &&
        (_term = term())
    ) ? ast_binary(_sum, _term, BINOP_MIN) :
        (restore(_pos), NULL);
}

// term (left_recursive):
//     | term '*' pipeline
//     | term '/' pipeline
//     | term '%' pipeline
//     | term '//' pipeline
//     | term '@' pipeline
//     | pipeline
static ast_expr_t *term() {
    size_t _pos = pos();
    ast_expr_t *res_460 = 0;
    memo_t *memo = fetch_memo(460, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_expr_t *alt_460;
    size_t maxpos;
    ast_expr_t *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_460;
        insert_memo(_pos, 460, max);
        restore(_pos);
        res_460 = (
            (alt_460 = term_1()) ||
            (alt_460 = term_2()) ||
            (alt_460 = term_3()) ||
            (alt_460 = term_4()) ||
            (alt_460 = term_5()) ||
            (alt_460 = pipeline())
        ) ? alt_460 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_460 = max;
    insert_memo(_pos, 460, res_460);
    return exit_frame(_pos, res_460, FUNC);
}

// term '*' pipeline
static ast_expr_t *term_1() {
    size_t _pos = pos();
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    return (
        (_term = term()) &&
        (consume(23, "*")) &&
        (_pipeline = pipeline())
    ) ? ast_binary(_term, _pipeline, BINOP_MUL) :
        (restore(_pos), NULL);
}

// term '/' pipeline
static ast_expr_t *term_2() {
    size_t _pos = pos();
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    return (
        (_term = term()) &&
        (consume(24, "/")) &&
        (_pipeline = pipeline())
    ) ? ast_binary(_term, _pipeline, BINOP_DIV) :
        (restore(_pos), NULL);
}

// term '%' pipeline
static ast_expr_t *term_3() {
    size_t _pos = pos();
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    return (
        (_term = term()) &&
        (consume(25, "%")) &&
        (_pipeline = pipeline())
    ) ? ast_binary(_term, _pipeline, BINOP_MOD) :
        (restore(_pos), NULL);
}

// term '//' pipeline
static ast_expr_t *term_4() {
    size_t _pos = pos();
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    return (
        (_term = term()) &&
        (consume(37, "//")) &&
        (_pipeline = pipeline())
    ) ? ast_binary(_term, _pipeline, BINOP_FDV) :
        (restore(_pos), NULL);
}

// term '@' pipeline
static ast_expr_t *term_5() {
    size_t _pos = pos();
    ast_expr_t *_term;
    ast_expr_t *_pipeline;
    return (
        (_term = term()) &&
        (consume(26, "@")) &&
        (_pipeline = pipeline())
    ) ? ast_binary(_term, _pipeline, BINOP_MML) :
        (restore(_pos), NULL);
}

// pipeline (left_recursive):
//     | pipeline '->' factor
//     | factor
static ast_expr_t *pipeline() {
    size_t _pos = pos();
    ast_expr_t *res_274 = 0;
    memo_t *memo = fetch_memo(274, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_expr_t *alt_274;
    size_t maxpos;
    ast_expr_t *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_274;
        insert_memo(_pos, 274, max);
        restore(_pos);
        res_274 = (
            (alt_274 = pipeline_1()) ||
            (alt_274 = factor())
        ) ? alt_274 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_274 = max;
    insert_memo(_pos, 274, res_274);
    return exit_frame(_pos, res_274, FUNC);
}

// pipeline '->' factor
static ast_expr_t *pipeline_1() {
    size_t _pos = pos();
    ast_expr_t *_pipeline;
    ast_expr_t *_factor;
    return (
        (_pipeline = pipeline()) &&
        (consume(35, "->")) &&
        (_factor = factor())
    ) ? ast_binary(_pipeline, _factor, BINOP_PIP) :
        (restore(_pos), NULL);
}

// factor (memo):
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
static ast_expr_t *factor() {
    size_t _pos = pos();
    ast_expr_t *res_983;
    memo_t *memo = fetch_memo(983, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_expr_t *alt_983;
    res_983 = enter_frame(FUNC) && (
        (alt_983 = factor_1()) ||
        (alt_983 = factor_2()) ||
        (alt_983 = factor_3()) ||
        (alt_983 = power())
    ) ? alt_983 : 0;
    insert_memo(_pos, 983, res_983);
    return exit_frame(_pos, res_983, FUNC);
}

// '+' factor
static ast_expr_t *factor_1() {
    size_t _pos = pos();
    ast_expr_t *_factor;
    return (
        (consume(21, "+")) &&
        (_factor = factor())
    ) ? ast_unary(_factor, UNARY_PLS) :
        (restore(_pos), NULL);
}

// '-' factor
static ast_expr_t *factor_2() {
    size_t _pos = pos();
    ast_expr_t *_factor;
    return (
        (consume(22, "-")) &&
        (_factor = factor())
    ) ? ast_unary(_factor, UNARY_MIN) :
        (restore(_pos), NULL);
}

// '~' factor
static ast_expr_t *factor_3() {
    size_t _pos = pos();
    ast_expr_t *_factor;
    return (
        (consume(29, "~")) &&
        (_factor = factor())
    ) ? ast_unary(_factor, UNARY_INV) :
        (restore(_pos), NULL);
}

// Convert a primary to an expression
static ast_expr_t *ast_primary_expr(void *primary) {
    ast_expr_t *r = palloc(sizeof(ast_expr_t));
    r->opcode = BINOP_PRIMARY;
    r->left = NULL;
    r->right.primary = primary;
    return r;
}

// power (memo):
//     | primary '**' factor
//     | primary
static ast_expr_t *power() {
    size_t _pos = pos();
    ast_expr_t *res_757;
    memo_t *memo = fetch_memo(757, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_primary_t *_primary;
    ast_expr_t *alt_757;
    res_757 = enter_frame(FUNC) && (
        (alt_757 = power_1()) || (
            (_primary = primary()) &&
            (alt_757 = ast_primary_expr(_primary)))
    ) ? alt_757 : 0;
    insert_memo(_pos, 757, res_757);
    return exit_frame(_pos, res_757, FUNC);
}

// primary '**' factor
static ast_expr_t *power_1() {
    size_t _pos = pos();
    ast_primary_t *_primary;
    ast_expr_t *_factor;
    return (
        (_primary = primary()) &&
        (consume(38, "**")) &&
        (_factor = factor())
    ) ? ast_binary(ast_primary_expr(_primary), _factor, BINOP_POW) :
        (restore(_pos), NULL);
}

// primary (left_recursive):
//     | primary '.' NAME
//     | primary invocation
//     | primary subscript
//     | atom
static ast_primary_t *primary() {
    size_t _pos = pos();
    ast_primary_t *res_178 = 0;
    memo_t *memo = fetch_memo(178, FUNC);
    if (memo) {
        return memo->node;
    }
    ast_primary_t *alt_178;
    size_t maxpos;
    ast_primary_t *max;
    if (errorcode()) return NULL;
    enter_frame(FUNC);
    do {
        maxpos = pos();
        max = res_178;
        insert_memo(_pos, 178, max);
        restore(_pos);
        res_178 = (
            (alt_178 = primary_1()) ||
            (alt_178 = primary_2()) ||
            (alt_178 = primary_3()) ||
            (alt_178 = atom())
        ) ? alt_178 : 0;
    } while (pos() > maxpos);
    restore(maxpos);
    res_178 = max;
    insert_memo(_pos, 178, res_178);
    return exit_frame(_pos, res_178, FUNC);
}

// primary '.' NAME
static ast_primary_t *primary_1() {
    size_t _pos = pos();
    return (
        (primary()) &&
        (consume(6, ".")) &&
        (consume(3, "NAME"))
    ) ? node() : (restore(_pos), NULL);
}

// primary invocation
static ast_primary_t *primary_2() {
    size_t _pos = pos();
    return (
        (primary()) &&
        (invocation())
    ) ? node() : (restore(_pos), NULL);
}

// primary subscript
static ast_primary_t *primary_3() {
    size_t _pos = pos();
    return (
        (primary()) &&
        (subscript())
    ) ? node() : (restore(_pos), NULL);
}

// list_item:
//     | starred_expression
//     | named_expression
static void *list_item() {
    size_t _pos = pos();
    void *res_756;
    void *alt_756;
    res_756 = enter_frame(FUNC) && (
        (alt_756 = starred_expression()) ||
        (alt_756 = named_expression())
    ) ? alt_756 : 0;
    return exit_frame(_pos, res_756, FUNC);
}

// list_items:
//     | ','.list_item+ [',']
static ast_list_t *list_items() {
    size_t _pos = pos();
    ast_list_t *res_215;
    ast_list_t *_list_items;
    res_215 = enter_frame(FUNC) && (
        (_list_items = list_item_delimited()) &&
        (consume(7, ","), 1)
    ) ? _list_items : 0;
    return exit_frame(_pos, res_215, FUNC);
}

static ast_list_t *list_item_delimited() {
    void *_list_item = list_item();
    if (!_list_item) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    size_t _pos;
    do {
        ast_list_append(list, _list_item);
        _pos = pos();
    } while (consume(7, ",") &&
            (_list_item = list_item()));
    restore(_pos);
    return list;
}

// paren_expression (inline):
//     | '(' [list_items] ')'
static ast_primary_t *paren_expression() {
    size_t _pos = pos();
    ast_list_t *_list_items;
    return (
        (consume(13, "(")) &&
        (_list_items = list_items(), 1) &&
        (consume(14, ")"))
    ) ? node() : (restore(_pos), NULL);
}

// list_expression (inline):
//     | '[' [list_items] ']'
static ast_primary_t *list_expression() {
    size_t _pos = pos();
    ast_list_t *_list_items;
    return (
        (consume(17, "[")) &&
        (_list_items = list_items(), 1) &&
        (consume(18, "]"))
    ) ? node() : (restore(_pos), NULL);
}

// typed_parameter:
//     | NAME [':' expression]
static void *typed_parameter() {
    size_t _pos = pos();
    void *res_868;
    token_t *_name;
    void *_colon_expression;
    res_868 = enter_frame(FUNC) && (
        (_name = consume(3, "NAME")) &&
        (_colon_expression = typed_parameter_2(), 1)
    ) ? node() : 0;
    return exit_frame(_pos, res_868, FUNC);
}

// ':' expression
static void *typed_parameter_2() {
    size_t _pos = pos();
    ast_expr_t *_expression;
    return (
        (consume(9, ":")) &&
        (_expression = expression())
    ) ? _expression : (restore(_pos), NULL);
}

// builder_parameter:
//     | typed_parameter ['=' expression]
//     | '*' typed_parameter
//     | '**' typed_parameter
static void *builder_parameter() {
    size_t _pos = pos();
    void *res_789;
    void *alt_789;
    res_789 = enter_frame(FUNC) && (
        (alt_789 = builder_parameter_1()) ||
        (alt_789 = builder_parameter_2()) ||
        (alt_789 = builder_parameter_3())
    ) ? alt_789 : 0;
    return exit_frame(_pos, res_789, FUNC);
}

// typed_parameter ['=' expression]
static void *builder_parameter_1() {
    size_t _pos = pos();
    void *res_887;
    void *_typed_parameter;
    void *_assign_expression;
    res_887 = enter_frame(FUNC) && (
        (_typed_parameter = typed_parameter()) &&
        (_assign_expression = builder_parameter_1_2(), 1)
    ) ? node() : 0;
    return exit_frame(_pos, res_887, FUNC);
}

// '=' expression
static void *builder_parameter_1_2() {
    size_t _pos = pos();
    ast_expr_t *_expression;
    return (
        (consume(8, "=")) &&
        (_expression = expression())
    ) ? _expression : (restore(_pos), NULL);
}

// '*' typed_parameter
static void *builder_parameter_2() {
    size_t _pos = pos();
    void *_typed_parameter;
    return (
        (consume(23, "*")) &&
        (_typed_parameter = typed_parameter())
    ) ? _typed_parameter : (restore(_pos), NULL);
}

// '**' typed_parameter
static void *builder_parameter_3() {
    size_t _pos = pos();
    void *_typed_parameter;
    return (
        (consume(38, "**")) &&
        (_typed_parameter = typed_parameter())
    ) ? _typed_parameter : (restore(_pos), NULL);
}

// simple_parameter:
//     | NAME ['=' expression]
static void *simple_parameter() {
    size_t _pos = pos();
    void *res_524;
    token_t *_name;
    void *_assign_expression;
    res_524 = enter_frame(FUNC) && (
        (_name = consume(3, "NAME")) &&
        (_assign_expression = simple_parameter_2(), 1)
    ) ? node() : 0;
    return exit_frame(_pos, res_524, FUNC);
}

// '=' expression
static void *simple_parameter_2() {
    size_t _pos = pos();
    ast_expr_t *_expression;
    return (
        (consume(8, "=")) &&
        (_expression = expression())
    ) ? _expression : (restore(_pos), NULL);
}

// builder_parameters (inline):
//     | '(' [','.builder_parameter+ [',']] ')'
static void *builder_parameters() {
    size_t _pos = pos();
    void *_builder_parameters_2;
    return (
        (consume(13, "(")) &&
        (_builder_parameters_2 = builder_parameters_2(), 1) &&
        (consume(14, ")"))
    ) ? _builder_parameters_2 :
        (restore(_pos), NULL);
}

// ','.builder_parameter+ [',']
static void *builder_parameters_2() {
    size_t _pos = pos();
    ast_list_t *_builder_parameters;
    return (
        (_builder_parameters = builder_parameter_delimited()) &&
        (consume(7, ","), 1)
    ) ? _builder_parameters : (restore(_pos), NULL);
}

static ast_list_t *builder_parameter_delimited() {
    void *_builder_parameter = builder_parameter();
    if (!_builder_parameter) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    size_t _pos;
    do {
        ast_list_append(list, _builder_parameter);
        _pos = pos();
    } while (consume(7, ",") &&
            (_builder_parameter = builder_parameter()));
    restore(_pos);
    return list;
}

// builder_generics (inline):
//     | '[' expressions ']'
static void *builder_generics() {
    size_t _pos = pos();
    ast_list_t *_expressions;
    return (
        (consume(17, "[")) &&
        (_expressions = expressions()) &&
        (consume(18, "]"))
    ) ? _expressions : (restore(_pos), NULL);
}

// builder_expression (inline):
//     | NAME [builder_generics] [builder_parameters] block_suite
//     | NAME ','.simple_parameter+ ':' expression
static ast_primary_t *builder_expression() {
    size_t _pos = pos();
    ast_primary_t *alt;
    return (
        (alt = builder_expression_1()) ||
        (alt = builder_expression_2())
    ) ? alt : (restore(_pos), NULL);
}

// NAME [builder_generics] [builder_parameters] block_suite
static ast_primary_t *builder_expression_1() {
    size_t _pos = pos();
    ast_primary_t *res_254;
    token_t *_name;
    void *_builder_generics;
    void *_builder_parameters;
    void *_block_suite;
    res_254 = enter_frame(FUNC) && (
        (_name = consume(3, "NAME")) &&
        (_builder_generics = builder_generics(), 1) &&
        (_builder_parameters = builder_parameters(), 1) &&
        (_block_suite = block_suite())
    ) ? node() : 0;
    return exit_frame(_pos, res_254, FUNC);
}

// NAME ','.simple_parameter+ ':' expression
static ast_primary_t *builder_expression_2() {
    size_t _pos = pos();
    ast_primary_t *res_256;
    token_t *_name;
    ast_list_t *_simple_parameters;
    ast_expr_t *_expression;
    res_256 = enter_frame(FUNC) && (
        (_name = consume(3, "NAME")) &&
        (_simple_parameters = simple_parameter_delimited()) &&
        (consume(9, ":")) &&
        (_expression = expression())
    ) ? node() : 0;
    return exit_frame(_pos, res_256, FUNC);
}

static ast_list_t *simple_parameter_delimited() {
    void *_simple_parameter = simple_parameter();
    if (!_simple_parameter) {
        return 0;
    }
    ast_list_t *list = ast_list_new();
    size_t _pos;
    do {
        ast_list_append(list, _simple_parameter);
        _pos = pos();
    } while (consume(7, ",") &&
            (_simple_parameter = simple_parameter()));
    restore(_pos);
    return list;
}

static ast_primary_t *ast_name_atom( token_t *name) {
    return node();
}

static ast_primary_t *ast_number_atom(token_t *number) {
    return node();
}

static ast_primary_t *ast_string_atom(token_t *string) {
    return node();
}

static ast_primary_t *ast_none() {
    return node();
}

static ast_primary_t *ast_true() {
    return node();
}

static ast_primary_t *ast_false() {
    return node();
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
static ast_primary_t *atom() {
    size_t _pos = pos();
    ast_primary_t *res_753;
    memo_t *memo = fetch_memo(753, FUNC);
    if (memo) {
        return memo->node;
    }
    token_t *_name;
    token_t *_number;
    token_t *_string;
    ast_primary_t *alt_753;
    res_753 = enter_frame(FUNC) && (
        (alt_753 = paren_expression()) ||
        (alt_753 = list_expression()) ||
        (alt_753 = builder_expression()) || (
            (_name = consume(3, "NAME")) &&
            (alt_753 = ast_name_atom(_name))
        ) || (
            (_number = consume(4, "NUMBER")) &&
            (alt_753 = ast_number_atom(_number))
        ) || (
            (_string = consume(5, "STRING")) &&
            (alt_753 = ast_string_atom(_string))
        ) || (
            (consume(81, "None")) &&
            (alt_753 = ast_none())
        ) || (
            (consume(82, "True")) &&
            (alt_753 = ast_true())
        ) || (
            (consume(83, "False")) &&
            (alt_753 = ast_false()))
    ) ? alt_753 : 0;
    insert_memo(_pos, 753, res_753);
    return exit_frame(_pos, res_753, FUNC);
}


// Provide the static parser struct
parser_t *get_static_parser() {
    return &__parser;
}

// Parser Entry Point
void *parse_grammar(int entry_point) {
    switch (entry_point) {
    case 0:
        return single_input();
    case 1:
        return file_input();
    case 2:
        return eval_input();
    default:
        return 0;
    }
}
