#include "include/parser.h"
#include "include/internal/peg_macros.h"

// single_input:
//     | NEWLINE
//     | simple_stmt
//     | compound_stmt NEWLINE
RULE(single_input) {
    ENTER_FRAME(p, 1, "single_input");
    (r = TOKEN(p, 2, "NEWLINE")) ||
    (r = simple_stmt(p)) ||
    (r = single_input_3(p));
    EXIT_FRAME(p);
}

RULE(single_input_3) {
    ENTER_FRAME(p, 2, "single_input:3");
    FAstNode *a, *b;
    (a = compound_stmt(p)) &&
    (b = TOKEN(p, 2, "NEWLINE"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// file_input:
//     | (NEWLINE | stmt)* ENDMARKER
RULE(file_input) {
    ENTER_FRAME(p, 3, "file_input");
    FAstNode *a, *b;
    (a = file_input_1_loop(p)) &&
    (b = TOKEN(p, 1, "ENDMARKER"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(file_input_1_loop) {
    FAstNode *node, *seq = AST_SEQ_NEW(p);
    while ((node = file_input_1(p))) {
        AST_SEQ_APPEND(p, seq, node);
    }
    return seq;
}

RULE(file_input_1) {
    ENTER_FRAME(p, 4, "file_input:1");
    (r = TOKEN(p, 2, "NEWLINE")) ||
    (r = stmt(p));
    EXIT_FRAME(p);
}

// eval_input:
//     | exprlist NEWLINE* ENDMARKER
RULE(eval_input) {
    ENTER_FRAME(p, 5, "eval_input");
    FAstNode *a, *b, *c;
    (a = exprlist(p)) &&
    (b = eval_input_loop(p)) &&
    (c = TOKEN(p, 1, "ENDMARKER"))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

RULE(eval_input_loop) {
    FAstNode *node, *seq = AST_SEQ_NEW(p);
    while ((node = TOKEN(p, 2, "NEWLINE"))) {
        AST_SEQ_APPEND(p, seq, node);
    }
    return seq;
}

// stmt:
//     | (simple_stmt | compound_stmt) NEWLINE
RULE(stmt) {
    ENTER_FRAME(p, 6, "stmt");
    FAstNode *a, *b;
    (a = stmt_1(p)) &&
    (b = TOKEN(p, 2, "NEWLINE"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(stmt_1) {
    ENTER_FRAME(p, 7, "stmt:1");
    (r = simple_stmt(p)) ||
    (r = compound_stmt(p));
    EXIT_FRAME(p);
}

// simple_stmt:
//     | ';'.small_stmt+ [';']
RULE(simple_stmt) {
    ENTER_FRAME(p, 8, "simple_stmt");
    FAstNode *a, *b;
    (a = small_stmt_loop(p)) &&
    (b = OPTIONAL(TOKEN(p, 12, ";")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(small_stmt_loop) {
    FAstNode *node, *seq;
    if (!(node = small_stmt(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 12, ";")) &&
            (node = small_stmt(p)));
    p->pos = pos;
    return seq;
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
RULE(small_stmt) {
    ENTER_FRAME(p, 9, "small_stmt");
    (r = TOKEN(p, 64, "pass")) ||
    (r = TOKEN(p, 74, "break")) ||
    (r = TOKEN(p, 73, "continue")) ||
    (r = return_stmt(p)) ||
    (r = raise_stmt(p)) ||
    (r = del_stmt(p)) ||
    (r = nonlocal_stmt(p)) ||
    (r = assert_stmt(p)) ||
    (r = import_name(p)) ||
    (r = import_from(p)) ||
    (r = assignment(p));
    EXIT_FRAME(p);
}

// del_stmt:
//     | 'del' targetlist
RULE(del_stmt) {
    ENTER_FRAME(p, 10, "del_stmt");
    FAstNode *a;
    (TOKEN(p, 79, "del")) &&
    (a = targetlist(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// return_stmt:
//     | 'return' [exprlist_star]
RULE(return_stmt) {
    ENTER_FRAME(p, 11, "return_stmt");
    FAstNode *a;
    (TOKEN(p, 54, "return")) &&
    (a = OPTIONAL(exprlist_star(p)))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// raise_stmt:
//     | 'raise' expr ['from' expr]
RULE(raise_stmt) {
    ENTER_FRAME(p, 12, "raise_stmt");
    FAstNode *a, *b;
    (TOKEN(p, 78, "raise")) &&
    (a = expr(p)) &&
    (b = OPTIONAL(raise_stmt_3(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(raise_stmt_3) {
    ENTER_FRAME(p, 13, "raise_stmt:3");
    FAstNode *a;
    (TOKEN(p, 66, "from")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// nonlocal_stmt:
//     | 'nonlocal' name_list
RULE(nonlocal_stmt) {
    ENTER_FRAME(p, 14, "nonlocal_stmt");
    FAstNode *a;
    (TOKEN(p, 55, "nonlocal")) &&
    (a = name_list(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// assert_stmt:
//     | 'assert' expr [',' expr]
RULE(assert_stmt) {
    ENTER_FRAME(p, 15, "assert_stmt");
    FAstNode *a, *b;
    (TOKEN(p, 80, "assert")) &&
    (a = expr(p)) &&
    (b = OPTIONAL(assert_stmt_3(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(assert_stmt_3) {
    ENTER_FRAME(p, 16, "assert_stmt:3");
    FAstNode *a;
    (TOKEN(p, 7, ",")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// name_list:
//     | ','.NAME+
RULE(name_list) {
    ENTER_FRAME(p, 17, "name_list");
    FAstNode *a;
    (a = name_list_loop(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(name_list_loop) {
    FAstNode *node, *seq;
    if (!(node = TOKEN(p, 3, "NAME"))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = TOKEN(p, 3, "NAME")));
    p->pos = pos;
    return seq;
}

// star_expr:
//     | '*' bitwise_or
RULE(star_expr) {
    ENTER_FRAME(p, 18, "star_expr");
    FAstNode *a;
    (TOKEN(p, 23, "*")) &&
    (a = bitwise_or(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// exprlist:
//     | ','.expr+ [',']
RULE(exprlist) {
    ENTER_FRAME(p, 19, "exprlist");
    FAstNode *a, *b;
    (a = expr_loop(p)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(expr_loop) {
    FAstNode *node, *seq;
    if (!(node = expr(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = expr(p)));
    p->pos = pos;
    return seq;
}

// target:
//     | t_primary '.' NAME !t_lookahead
//     | t_primary subscript !t_lookahead
//     | NAME
//     | '(' targetlist ')'
RULE(target) {
    ENTER_FRAME(p, 20, "target");
    (r = target_1(p)) ||
    (r = target_2(p)) ||
    (r = TOKEN(p, 3, "NAME")) ||
    (r = target_4(p));
    EXIT_FRAME(p);
}

RULE(target_1) {
    ENTER_FRAME(p, 21, "target:1");
    FAstNode *a, *b;
    (a = t_primary(p)) &&
    (TOKEN(p, 6, ".")) &&
    (b = TOKEN(p, 3, "NAME")) &&
    (!TEST(p, t_lookahead(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(target_2) {
    ENTER_FRAME(p, 22, "target:2");
    FAstNode *a, *b;
    (a = t_primary(p)) &&
    (b = subscript(p)) &&
    (!TEST(p, t_lookahead(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(target_4) {
    ENTER_FRAME(p, 23, "target:4");
    FAstNode *a;
    (TOKEN(p, 13, "(")) &&
    (a = targetlist(p)) &&
    (TOKEN(p, 14, ")"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// t_primary:
//     | t_primary '.' NAME &t_lookahead
//     | t_primary invocation &t_lookahead
//     | t_primary subscript &t_lookahead
//     | atom &t_lookahead
RULE(t_primary) {
    ENTER_FRAME(p, 24, "t_primary");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (r = t_primary_1(p)) ||
    (r = t_primary_2(p)) ||
    (r = t_primary_3(p)) ||
    (r = t_primary_4(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(t_primary_1) {
    ENTER_FRAME(p, 25, "t_primary:1");
    FAstNode *a, *b;
    (a = t_primary(p)) &&
    (TOKEN(p, 6, ".")) &&
    (b = TOKEN(p, 3, "NAME")) &&
    (TEST(p, t_lookahead(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(t_primary_2) {
    ENTER_FRAME(p, 26, "t_primary:2");
    FAstNode *a, *b;
    (a = t_primary(p)) &&
    (b = invocation(p)) &&
    (TEST(p, t_lookahead(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(t_primary_3) {
    ENTER_FRAME(p, 27, "t_primary:3");
    FAstNode *a, *b;
    (a = t_primary(p)) &&
    (b = subscript(p)) &&
    (TEST(p, t_lookahead(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(t_primary_4) {
    ENTER_FRAME(p, 28, "t_primary:4");
    FAstNode *a;
    (a = atom(p)) &&
    (TEST(p, t_lookahead(p)))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// t_lookahead:
//     | '.'
//     | '('
//     | '['
RULE(t_lookahead) {
    ENTER_FRAME(p, 29, "t_lookahead");
    (r = TOKEN(p, 6, ".")) ||
    (r = TOKEN(p, 13, "(")) ||
    (r = TOKEN(p, 17, "["));
    EXIT_FRAME(p);
}

// targetlist:
//     | ','.target+ [',']
RULE(targetlist) {
    ENTER_FRAME(p, 30, "targetlist");
    FAstNode *a, *b;
    (a = target_loop(p)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(target_loop) {
    FAstNode *node, *seq;
    if (!(node = target(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = target(p)));
    p->pos = pos;
    return seq;
}

// expr_or_star:
//     | star_expr
//     | expr
RULE(expr_or_star) {
    ENTER_FRAME(p, 31, "expr_or_star");
    (r = star_expr(p)) ||
    (r = expr(p));
    EXIT_FRAME(p);
}

// exprlist_star:
//     | ','.expr_or_star+ [',']
RULE(exprlist_star) {
    ENTER_FRAME(p, 32, "exprlist_star");
    FAstNode *a, *b;
    (a = expr_or_star_loop(p)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(expr_or_star_loop) {
    FAstNode *node, *seq;
    if (!(node = expr_or_star(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = expr_or_star(p)));
    p->pos = pos;
    return seq;
}

// named_expr_star:
//     | star_expr
//     | named_expr
RULE(named_expr_star) {
    ENTER_FRAME(p, 33, "named_expr_star");
    (r = star_expr(p)) ||
    (r = named_expr(p));
    EXIT_FRAME(p);
}

// named_expr_list:
//     | ','.named_expr_star+ [',']
RULE(named_expr_list) {
    ENTER_FRAME(p, 34, "named_expr_list");
    FAstNode *a, *b;
    (a = named_expr_star_loop(p)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(named_expr_star_loop) {
    FAstNode *node, *seq;
    if (!(node = named_expr_star(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = named_expr_star(p)));
    p->pos = pos;
    return seq;
}

// subscript:
//     | '[' slicelist ']'
RULE(subscript) {
    ENTER_FRAME(p, 35, "subscript");
    FAstNode *a;
    (TOKEN(p, 17, "[")) &&
    (a = slicelist(p)) &&
    (TOKEN(p, 18, "]"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// slicelist:
//     | ','.slice+ [',']
RULE(slicelist) {
    ENTER_FRAME(p, 36, "slicelist");
    FAstNode *a, *b;
    (a = slice_loop(p)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(slice_loop) {
    FAstNode *node, *seq;
    if (!(node = slice(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = slice(p)));
    p->pos = pos;
    return seq;
}

// slice:
//     | [expr] slice_expr [slice_expr]
//     | expr
RULE(slice) {
    ENTER_FRAME(p, 37, "slice");
    (r = slice_1(p)) ||
    (r = expr(p));
    EXIT_FRAME(p);
}

RULE(slice_1) {
    ENTER_FRAME(p, 38, "slice:1");
    FAstNode *a, *b, *c;
    (a = OPTIONAL(expr(p))) &&
    (b = slice_expr(p)) &&
    (c = OPTIONAL(slice_expr(p)))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

// slice_expr:
//     | ':' [expr]
RULE(slice_expr) {
    ENTER_FRAME(p, 39, "slice_expr");
    FAstNode *a;
    (TOKEN(p, 9, ":")) &&
    (a = OPTIONAL(expr(p)))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// dict_item:
//     | expr ':' expr
//     | '**' bitwise_or
RULE(dict_item) {
    ENTER_FRAME(p, 40, "dict_item");
    (r = dict_item_1(p)) ||
    (r = dict_item_2(p));
    EXIT_FRAME(p);
}

RULE(dict_item_1) {
    ENTER_FRAME(p, 41, "dict_item:1");
    FAstNode *a, *b;
    (a = expr(p)) &&
    (TOKEN(p, 9, ":")) &&
    (b = expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(dict_item_2) {
    ENTER_FRAME(p, 42, "dict_item:2");
    FAstNode *a;
    (TOKEN(p, 38, "**")) &&
    (a = bitwise_or(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// dict_items:
//     | ','.dict_item+ [',']
RULE(dict_items) {
    ENTER_FRAME(p, 43, "dict_items");
    FAstNode *a, *b;
    (a = dict_item_loop(p)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(dict_item_loop) {
    FAstNode *node, *seq;
    if (!(node = dict_item(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = dict_item(p)));
    p->pos = pos;
    return seq;
}

// as_name:
//     | 'as' NAME
RULE(as_name) {
    ENTER_FRAME(p, 44, "as_name");
    FAstNode *a;
    (TOKEN(p, 65, "as")) &&
    (a = TOKEN(p, 3, "NAME"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// iter_for:
//     | 'for' targetlist 'in' disjunction [iter_if]
RULE(iter_for) {
    ENTER_FRAME(p, 45, "iter_for");
    FAstNode *a, *b, *c;
    (TOKEN(p, 72, "for")) &&
    (a = targetlist(p)) &&
    (TOKEN(p, 63, "in")) &&
    (b = disjunction(p)) &&
    (c = OPTIONAL(iter_if(p)))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

// iter_if:
//     | 'if' named_expr
RULE(iter_if) {
    ENTER_FRAME(p, 46, "iter_if");
    FAstNode *a;
    (TOKEN(p, 56, "if")) &&
    (a = named_expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// iterator:
//     | iter_for* 'for' targetlist [iter_if]
RULE(iterator) {
    ENTER_FRAME(p, 47, "iterator");
    FAstNode *a, *b, *c;
    (a = iter_for_loop(p)) &&
    (TOKEN(p, 72, "for")) &&
    (b = targetlist(p)) &&
    (c = OPTIONAL(iter_if(p)))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

RULE(iter_for_loop) {
    FAstNode *node, *seq = AST_SEQ_NEW(p);
    while ((node = iter_for(p))) {
        AST_SEQ_APPEND(p, seq, node);
    }
    return seq;
}

// assignment:
//     | pubassign
//     | annassign
//     | augassign
//     | simple_assign
RULE(assignment) {
    ENTER_FRAME(p, 48, "assignment");
    (r = pubassign(p)) ||
    (r = annassign(p)) ||
    (r = augassign(p)) ||
    (r = simple_assign(p));
    EXIT_FRAME(p);
}

// pubassign:
//     | '/' NAME '=' exprlist
RULE(pubassign) {
    ENTER_FRAME(p, 49, "pubassign");
    FAstNode *a, *b;
    (TOKEN(p, 24, "/")) &&
    (a = TOKEN(p, 3, "NAME")) &&
    (TOKEN(p, 8, "=")) &&
    (b = exprlist(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// annassign:
//     | target ':' expr ['=' exprlist]
RULE(annassign) {
    ENTER_FRAME(p, 50, "annassign");
    FAstNode *a, *b, *c;
    (a = target(p)) &&
    (TOKEN(p, 9, ":")) &&
    (b = expr(p)) &&
    (c = OPTIONAL(annassign_4(p)))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

RULE(annassign_4) {
    ENTER_FRAME(p, 51, "annassign:4");
    FAstNode *a;
    (TOKEN(p, 8, "=")) &&
    (a = exprlist(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// augassign:
//     | target augassign_op exprlist
RULE(augassign) {
    ENTER_FRAME(p, 52, "augassign");
    FAstNode *a, *b, *c;
    (a = target(p)) &&
    (b = augassign_op(p)) &&
    (c = exprlist(p))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
RULE(simple_assign) {
    ENTER_FRAME(p, 53, "simple_assign");
    FAstNode *a, *b;
    (a = simple_assign_1_loop(p)) &&
    (b = exprlist_star(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(simple_assign_1_loop) {
    FAstNode *node, *seq = AST_SEQ_NEW(p);
    while ((node = simple_assign_1(p))) {
        AST_SEQ_APPEND(p, seq, node);
    }
    return seq;
}

RULE(simple_assign_1) {
    ENTER_FRAME(p, 54, "simple_assign:1");
    FAstNode *a;
    (a = targetlist(p)) &&
    (TOKEN(p, 8, "="))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
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
RULE(augassign_op) {
    ENTER_FRAME(p, 55, "augassign_op");
    (r = TOKEN(p, 39, "+=")) ||
    (r = TOKEN(p, 40, "-=")) ||
    (r = TOKEN(p, 41, "*=")) ||
    (r = TOKEN(p, 44, "@=")) ||
    (r = TOKEN(p, 42, "/=")) ||
    (r = TOKEN(p, 43, "%=")) ||
    (r = TOKEN(p, 46, "&=")) ||
    (r = TOKEN(p, 45, "|=")) ||
    (r = TOKEN(p, 47, "^=")) ||
    (r = TOKEN(p, 52, "<<=")) ||
    (r = TOKEN(p, 53, ">>=")) ||
    (r = TOKEN(p, 51, "**=")) ||
    (r = TOKEN(p, 50, "//="));
    EXIT_FRAME(p);
}

// import_name:
//     | 'import' dotted_as_names
RULE(import_name) {
    ENTER_FRAME(p, 56, "import_name");
    FAstNode *a;
    (TOKEN(p, 67, "import")) &&
    (a = dotted_as_names(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// import_from:
//     | 'from' import_from_names 'import' import_from_items
RULE(import_from) {
    ENTER_FRAME(p, 57, "import_from");
    FAstNode *a, *b;
    (TOKEN(p, 66, "from")) &&
    (a = import_from_names(p)) &&
    (TOKEN(p, 67, "import")) &&
    (b = import_from_items(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// import_from_names:
//     | dotted_name
//     | '.'+ [dotted_name]
RULE(import_from_names) {
    ENTER_FRAME(p, 58, "import_from_names");
    (r = dotted_name(p)) ||
    (r = import_from_names_2(p));
    EXIT_FRAME(p);
}

RULE(import_from_names_2) {
    ENTER_FRAME(p, 59, "import_from_names:2");
    FAstNode *a;
    (import_from_names_2_loop(p)) &&
    (a = OPTIONAL(dotted_name(p)))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(import_from_names_2_loop) {
    FAstNode *node, *seq;
    if (!(node = TOKEN(p, 6, "."))) { return 0; }
    seq = AST_SEQ_NEW(p);
    do { AST_SEQ_APPEND(p, seq, node); }
    while ((node = TOKEN(p, 6, ".")));
    return seq;
}

// import_from_items:
//     | '*'
//     | '(' import_as_names [','] ')'
//     | import_as_names
RULE(import_from_items) {
    ENTER_FRAME(p, 60, "import_from_items");
    (r = TOKEN(p, 23, "*")) ||
    (r = import_from_items_2(p)) ||
    (r = import_as_names(p));
    EXIT_FRAME(p);
}

RULE(import_from_items_2) {
    ENTER_FRAME(p, 61, "import_from_items:2");
    FAstNode *a, *b;
    (TOKEN(p, 13, "(")) &&
    (a = import_as_names(p)) &&
    (b = OPTIONAL(TOKEN(p, 7, ","))) &&
    (TOKEN(p, 14, ")"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// import_as_name:
//     | NAME [as_name]
RULE(import_as_name) {
    ENTER_FRAME(p, 62, "import_as_name");
    FAstNode *a, *b;
    (a = TOKEN(p, 3, "NAME")) &&
    (b = OPTIONAL(as_name(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// dotted_as_name:
//     | dotted_name [as_name]
RULE(dotted_as_name) {
    ENTER_FRAME(p, 63, "dotted_as_name");
    FAstNode *a, *b;
    (a = dotted_name(p)) &&
    (b = OPTIONAL(as_name(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// import_as_names:
//     | ','.import_as_name+
RULE(import_as_names) {
    ENTER_FRAME(p, 64, "import_as_names");
    FAstNode *a;
    (a = import_as_name_loop(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(import_as_name_loop) {
    FAstNode *node, *seq;
    if (!(node = import_as_name(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = import_as_name(p)));
    p->pos = pos;
    return seq;
}

// dotted_as_names:
//     | ','.dotted_as_name+
RULE(dotted_as_names) {
    ENTER_FRAME(p, 65, "dotted_as_names");
    FAstNode *a;
    (a = dotted_as_name_loop(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(dotted_as_name_loop) {
    FAstNode *node, *seq;
    if (!(node = dotted_as_name(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = dotted_as_name(p)));
    p->pos = pos;
    return seq;
}

// dotted_name:
//     | '.'.NAME+
RULE(dotted_name) {
    ENTER_FRAME(p, 66, "dotted_name");
    FAstNode *a;
    (a = dotted_name_loop(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(dotted_name_loop) {
    FAstNode *node, *seq;
    if (!(node = TOKEN(p, 3, "NAME"))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 6, ".")) &&
            (node = TOKEN(p, 3, "NAME")));
    p->pos = pos;
    return seq;
}

// compound_stmt:
//     | if_stmt
//     | while_stmt
//     | for_stmt
//     | try_stmt
//     | with_stmt
RULE(compound_stmt) {
    ENTER_FRAME(p, 67, "compound_stmt");
    (r = if_stmt(p)) ||
    (r = while_stmt(p)) ||
    (r = for_stmt(p)) ||
    (r = try_stmt(p)) ||
    (r = with_stmt(p));
    EXIT_FRAME(p);
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
RULE(if_stmt) {
    ENTER_FRAME(p, 68, "if_stmt");
    FAstNode *a, *b, *c, *d;
    (TOKEN(p, 56, "if")) &&
    (a = named_expr(p)) &&
    (b = suite(p)) &&
    (c = elif_stmt_loop(p)) &&
    (d = OPTIONAL(else_suite(p)))
    ? (r = NODE_4(p, a, b, c, d)) : 0;
    EXIT_FRAME(p);
}

RULE(elif_stmt_loop) {
    FAstNode *node, *seq = AST_SEQ_NEW(p);
    while ((node = elif_stmt(p))) {
        AST_SEQ_APPEND(p, seq, node);
    }
    return seq;
}

// elif_stmt:
//     | 'elif' named_expr suite
RULE(elif_stmt) {
    ENTER_FRAME(p, 69, "elif_stmt");
    FAstNode *a, *b;
    (TOKEN(p, 57, "elif")) &&
    (a = named_expr(p)) &&
    (b = suite(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
RULE(while_stmt) {
    ENTER_FRAME(p, 70, "while_stmt");
    FAstNode *a, *b, *c;
    (TOKEN(p, 71, "while")) &&
    (a = named_expr(p)) &&
    (b = suite(p)) &&
    (c = OPTIONAL(else_suite(p)))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

// for_stmt:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
RULE(for_stmt) {
    ENTER_FRAME(p, 71, "for_stmt");
    FAstNode *a, *b, *c, *d;
    (TOKEN(p, 72, "for")) &&
    (a = targetlist(p)) &&
    (TOKEN(p, 63, "in")) &&
    (b = exprlist(p)) &&
    (c = suite(p)) &&
    (d = OPTIONAL(else_suite(p)))
    ? (r = NODE_4(p, a, b, c, d)) : 0;
    EXIT_FRAME(p);
}

// try_stmt:
//     | 'try' suite (except_suite | finally_suite)
RULE(try_stmt) {
    ENTER_FRAME(p, 72, "try_stmt");
    FAstNode *a, *b;
    (TOKEN(p, 75, "try")) &&
    (a = suite(p)) &&
    (b = try_stmt_3(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(try_stmt_3) {
    ENTER_FRAME(p, 73, "try_stmt:3");
    (r = except_suite(p)) ||
    (r = finally_suite(p));
    EXIT_FRAME(p);
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
RULE(with_stmt) {
    ENTER_FRAME(p, 74, "with_stmt");
    FAstNode *a, *b;
    (TOKEN(p, 68, "with")) &&
    (a = expr_as_name_loop(p)) &&
    (b = suite(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(expr_as_name_loop) {
    FAstNode *node, *seq;
    if (!(node = expr_as_name(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = expr_as_name(p)));
    p->pos = pos;
    return seq;
}

// expr_as_name:
//     | expr [as_name]
RULE(expr_as_name) {
    ENTER_FRAME(p, 75, "expr_as_name");
    FAstNode *a, *b;
    (a = expr(p)) &&
    (b = OPTIONAL(as_name(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// block_suite:
//     | '{' NEWLINE stmt+ '}'
//     | '{' '}'
RULE(block_suite) {
    ENTER_FRAME(p, 76, "block_suite");
    (r = block_suite_1(p)) ||
    (r = block_suite_2(p));
    EXIT_FRAME(p);
}

RULE(block_suite_1) {
    ENTER_FRAME(p, 77, "block_suite:1");
    FAstNode *a, *b;
    (TOKEN(p, 15, "{")) &&
    (a = TOKEN(p, 2, "NEWLINE")) &&
    (b = stmt_loop(p)) &&
    (TOKEN(p, 16, "}"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(stmt_loop) {
    FAstNode *node, *seq;
    if (!(node = stmt(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    do { AST_SEQ_APPEND(p, seq, node); }
    while ((node = stmt(p)));
    return seq;
}

RULE(block_suite_2) {
    ENTER_FRAME(p, 78, "block_suite:2");
    (TOKEN(p, 15, "{")) &&
    (TOKEN(p, 16, "}"));
    EXIT_FRAME(p);
}

// suite:
//     | ':' simple_stmt
//     | block_suite
RULE(suite) {
    ENTER_FRAME(p, 79, "suite");
    (r = suite_1(p)) ||
    (r = block_suite(p));
    EXIT_FRAME(p);
}

RULE(suite_1) {
    ENTER_FRAME(p, 80, "suite:1");
    FAstNode *a;
    (TOKEN(p, 9, ":")) &&
    (a = simple_stmt(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// else_suite:
//     | 'else' suite
RULE(else_suite) {
    ENTER_FRAME(p, 81, "else_suite");
    FAstNode *a;
    (TOKEN(p, 58, "else")) &&
    (a = suite(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// finally_suite:
//     | 'finally' suite
RULE(finally_suite) {
    ENTER_FRAME(p, 82, "finally_suite");
    FAstNode *a;
    (TOKEN(p, 77, "finally")) &&
    (a = suite(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// except_clause:
//     | 'except' [expr_as_name] suite
RULE(except_clause) {
    ENTER_FRAME(p, 83, "except_clause");
    FAstNode *a, *b;
    (TOKEN(p, 76, "except")) &&
    (a = OPTIONAL(expr_as_name(p))) &&
    (b = suite(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
RULE(except_suite) {
    ENTER_FRAME(p, 84, "except_suite");
    FAstNode *a, *b, *c;
    (a = except_clause_loop(p)) &&
    (b = OPTIONAL(else_suite(p))) &&
    (c = OPTIONAL(finally_suite(p)))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

RULE(except_clause_loop) {
    FAstNode *node, *seq;
    if (!(node = except_clause(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    do { AST_SEQ_APPEND(p, seq, node); }
    while ((node = except_clause(p)));
    return seq;
}

// invocation:
//     | '(' [call_arg_list] ')'
RULE(invocation) {
    ENTER_FRAME(p, 85, "invocation");
    FAstNode *a;
    (TOKEN(p, 13, "(")) &&
    (a = OPTIONAL(call_arg_list(p))) &&
    (TOKEN(p, 14, ")"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// call_arg_list:
//     | ','.call_arg+ [',']
RULE(call_arg_list) {
    ENTER_FRAME(p, 86, "call_arg_list");
    FAstNode *a, *b;
    (a = call_arg_loop(p)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(call_arg_loop) {
    FAstNode *node, *seq;
    if (!(node = call_arg(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = call_arg(p)));
    p->pos = pos;
    return seq;
}

// call_arg:
//     | NAME ':=' expr
//     | NAME '=' expr
//     | '**' expr
//     | '*' expr
//     | expr
RULE(call_arg) {
    ENTER_FRAME(p, 87, "call_arg");
    (r = call_arg_1(p)) ||
    (r = call_arg_2(p)) ||
    (r = call_arg_3(p)) ||
    (r = call_arg_4(p)) ||
    (r = expr(p));
    EXIT_FRAME(p);
}

RULE(call_arg_1) {
    ENTER_FRAME(p, 88, "call_arg:1");
    FAstNode *a, *b;
    (a = TOKEN(p, 3, "NAME")) &&
    (TOKEN(p, 36, ":=")) &&
    (b = expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(call_arg_2) {
    ENTER_FRAME(p, 89, "call_arg:2");
    FAstNode *a, *b;
    (a = TOKEN(p, 3, "NAME")) &&
    (TOKEN(p, 8, "=")) &&
    (b = expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(call_arg_3) {
    ENTER_FRAME(p, 90, "call_arg:3");
    FAstNode *a;
    (TOKEN(p, 38, "**")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(call_arg_4) {
    ENTER_FRAME(p, 91, "call_arg:4");
    FAstNode *a;
    (TOKEN(p, 23, "*")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// typed_arg_list:
//     | kwargs
//     | args_kwargs
//     | full_arg_list
RULE(typed_arg_list) {
    ENTER_FRAME(p, 92, "typed_arg_list");
    (r = kwargs(p)) ||
    (r = args_kwargs(p)) ||
    (r = full_arg_list(p));
    EXIT_FRAME(p);
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
RULE(full_arg_list) {
    ENTER_FRAME(p, 93, "full_arg_list");
    FAstNode *a, *b;
    (a = default_arg_loop(p)) &&
    (b = OPTIONAL(full_arg_list_2(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(default_arg_loop) {
    FAstNode *node, *seq;
    if (!(node = default_arg(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = default_arg(p)));
    p->pos = pos;
    return seq;
}

RULE(full_arg_list_2) {
    ENTER_FRAME(p, 94, "full_arg_list:2");
    FAstNode *a;
    (TOKEN(p, 7, ",")) &&
    (a = OPTIONAL(full_arg_list_2_2(p)))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(full_arg_list_2_2) {
    ENTER_FRAME(p, 95, "full_arg_list:2:2");
    (r = kwargs(p)) ||
    (r = args_kwargs(p));
    EXIT_FRAME(p);
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
RULE(args_kwargs) {
    ENTER_FRAME(p, 96, "args_kwargs");
    FAstNode *a, *b, *c;
    (TOKEN(p, 23, "*")) &&
    (a = OPTIONAL(typed_arg(p))) &&
    (b = args_kwargs_3_loop(p)) &&
    (c = OPTIONAL(args_kwargs_4(p)))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

RULE(args_kwargs_3_loop) {
    FAstNode *node, *seq = AST_SEQ_NEW(p);
    while ((node = args_kwargs_3(p))) {
        AST_SEQ_APPEND(p, seq, node);
    }
    return seq;
}

RULE(args_kwargs_3) {
    ENTER_FRAME(p, 97, "args_kwargs:3");
    FAstNode *a;
    (TOKEN(p, 7, ",")) &&
    (a = default_arg(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(args_kwargs_4) {
    ENTER_FRAME(p, 98, "args_kwargs:4");
    FAstNode *a;
    (TOKEN(p, 7, ",")) &&
    (a = OPTIONAL(kwargs(p)))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// kwargs:
//     | '**' typed_arg [',']
RULE(kwargs) {
    ENTER_FRAME(p, 99, "kwargs");
    FAstNode *a, *b;
    (TOKEN(p, 38, "**")) &&
    (a = typed_arg(p)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// default_arg:
//     | typed_arg ['=' expr]
RULE(default_arg) {
    ENTER_FRAME(p, 100, "default_arg");
    FAstNode *a, *b;
    (a = typed_arg(p)) &&
    (b = OPTIONAL(default_arg_2(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(default_arg_2) {
    ENTER_FRAME(p, 101, "default_arg:2");
    FAstNode *a;
    (TOKEN(p, 8, "=")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// typed_arg:
//     | NAME [':' expr]
RULE(typed_arg) {
    ENTER_FRAME(p, 102, "typed_arg");
    FAstNode *a, *b;
    (a = TOKEN(p, 3, "NAME")) &&
    (b = OPTIONAL(typed_arg_2(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(typed_arg_2) {
    ENTER_FRAME(p, 103, "typed_arg:2");
    FAstNode *a;
    (TOKEN(p, 9, ":")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// simple_arg:
//     | NAME ['=' expr]
RULE(simple_arg) {
    ENTER_FRAME(p, 104, "simple_arg");
    FAstNode *a, *b;
    (a = TOKEN(p, 3, "NAME")) &&
    (b = OPTIONAL(simple_arg_2(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(simple_arg_2) {
    ENTER_FRAME(p, 105, "simple_arg:2");
    FAstNode *a;
    (TOKEN(p, 8, "=")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// simple_args:
//     | ','.simple_arg+
RULE(simple_args) {
    ENTER_FRAME(p, 106, "simple_args");
    FAstNode *a;
    (a = simple_arg_loop(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(simple_arg_loop) {
    FAstNode *node, *seq;
    if (!(node = simple_arg(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    size_t pos;
    do { AST_SEQ_APPEND(p, seq, node); }
    while (pos = p->pos,
            (AST_CONSUME(p, 7, ",")) &&
            (node = simple_arg(p)));
    p->pos = pos;
    return seq;
}

// builder_hint:
//     | '<' name_list '>'
RULE(builder_hint) {
    ENTER_FRAME(p, 107, "builder_hint");
    FAstNode *a;
    (TOKEN(p, 19, "<")) &&
    (a = name_list(p)) &&
    (TOKEN(p, 20, ">"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// builder_args:
//     | simple_args
//     | '(' [typed_arg_list] ')'
RULE(builder_args) {
    ENTER_FRAME(p, 108, "builder_args");
    (r = simple_args(p)) ||
    (r = builder_args_2(p));
    EXIT_FRAME(p);
}

RULE(builder_args_2) {
    ENTER_FRAME(p, 109, "builder_args:2");
    FAstNode *a;
    (TOKEN(p, 13, "(")) &&
    (a = OPTIONAL(typed_arg_list(p))) &&
    (TOKEN(p, 14, ")"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// named_expr:
//     | NAME ':=' expr
//     | expr
RULE(named_expr) {
    ENTER_FRAME(p, 110, "named_expr");
    (r = named_expr_1(p)) ||
    (r = expr(p));
    EXIT_FRAME(p);
}

RULE(named_expr_1) {
    ENTER_FRAME(p, 111, "named_expr:1");
    FAstNode *a, *b;
    (a = TOKEN(p, 3, "NAME")) &&
    (TOKEN(p, 36, ":=")) &&
    (b = expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
RULE(conditional) {
    ENTER_FRAME(p, 112, "conditional");
    FAstNode *a, *b, *c;
    (TOKEN(p, 56, "if")) &&
    (a = disjunction(p)) &&
    (TOKEN(p, 10, "?")) &&
    (b = disjunction(p)) &&
    (TOKEN(p, 9, ":")) &&
    (c = expr(p))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

// expr:
//     | conditional
//     | disjunction
RULE(expr) {
    ENTER_FRAME(p, 113, "expr");
    (r = conditional(p)) ||
    (r = disjunction(p));
    EXIT_FRAME(p);
}

// disjunction:
//     | disjunction 'or' conjunction
//     | conjunction
RULE(disjunction) {
    ENTER_FRAME(p, 114, "disjunction");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (r = disjunction_1(p)) ||
    (r = conjunction(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(disjunction_1) {
    ENTER_FRAME(p, 115, "disjunction:1");
    FAstNode *a, *b;
    (a = disjunction(p)) &&
    (TOKEN(p, 60, "or")) &&
    (b = conjunction(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// conjunction:
//     | conjunction 'and' inversion
//     | inversion
RULE(conjunction) {
    ENTER_FRAME(p, 116, "conjunction");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (r = conjunction_1(p)) ||
    (r = inversion(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(conjunction_1) {
    ENTER_FRAME(p, 117, "conjunction:1");
    FAstNode *a, *b;
    (a = conjunction(p)) &&
    (TOKEN(p, 59, "and")) &&
    (b = inversion(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// inversion:
//     | 'not' inversion
//     | comparison
RULE(inversion) {
    ENTER_FRAME(p, 118, "inversion");
    (r = inversion_1(p)) ||
    (r = comparison(p));
    EXIT_FRAME(p);
}

RULE(inversion_1) {
    ENTER_FRAME(p, 119, "inversion:1");
    FAstNode *a;
    (TOKEN(p, 61, "not")) &&
    (a = inversion(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
RULE(comparison) {
    ENTER_FRAME(p, 120, "comparison");
    (r = comparison_1(p)) ||
    (r = bitwise_or(p));
    EXIT_FRAME(p);
}

RULE(comparison_1) {
    ENTER_FRAME(p, 121, "comparison:1");
    FAstNode *a, *b;
    (a = bitwise_or(p)) &&
    (b = comparison_1_2_loop(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(comparison_1_2_loop) {
    FAstNode *node, *seq;
    if (!(node = comparison_1_2(p))) { return 0; }
    seq = AST_SEQ_NEW(p);
    do { AST_SEQ_APPEND(p, seq, node); }
    while ((node = comparison_1_2(p)));
    return seq;
}

RULE(comparison_1_2) {
    ENTER_FRAME(p, 122, "comparison:1:2");
    FAstNode *a, *b;
    (a = comp_op(p)) &&
    (b = bitwise_or(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
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
RULE(comp_op) {
    ENTER_FRAME(p, 123, "comp_op");
    (r = TOKEN(p, 19, "<")) ||
    (r = TOKEN(p, 20, ">")) ||
    (r = TOKEN(p, 31, "==")) ||
    (r = TOKEN(p, 34, ">=")) ||
    (r = TOKEN(p, 33, "<=")) ||
    (r = TOKEN(p, 32, "!=")) ||
    (r = TOKEN(p, 63, "in")) ||
    (r = comp_op_8(p)) ||
    (r = TOKEN(p, 62, "is")) ||
    (r = comp_op_10(p));
    EXIT_FRAME(p);
}

RULE(comp_op_8) {
    ENTER_FRAME(p, 124, "comp_op:8");
    (TOKEN(p, 61, "not")) &&
    (TOKEN(p, 63, "in"));
    EXIT_FRAME(p);
}

RULE(comp_op_10) {
    ENTER_FRAME(p, 125, "comp_op:10");
    (TOKEN(p, 62, "is")) &&
    (TOKEN(p, 61, "not"));
    EXIT_FRAME(p);
}

// bitwise_or:
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
RULE(bitwise_or) {
    ENTER_FRAME(p, 126, "bitwise_or");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (r = bitwise_or_1(p)) ||
    (r = bitwise_xor(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(bitwise_or_1) {
    ENTER_FRAME(p, 127, "bitwise_or:1");
    FAstNode *a, *b;
    (a = bitwise_or(p)) &&
    (TOKEN(p, 27, "|")) &&
    (b = bitwise_xor(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// bitwise_xor:
//     | bitwise_xor '^' bitwise_and
//     | bitwise_and
RULE(bitwise_xor) {
    ENTER_FRAME(p, 128, "bitwise_xor");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (r = bitwise_xor_1(p)) ||
    (r = bitwise_and(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(bitwise_xor_1) {
    ENTER_FRAME(p, 129, "bitwise_xor:1");
    FAstNode *a, *b;
    (a = bitwise_xor(p)) &&
    (TOKEN(p, 30, "^")) &&
    (b = bitwise_and(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// bitwise_and:
//     | bitwise_and '&' shift_expr
//     | shift_expr
RULE(bitwise_and) {
    ENTER_FRAME(p, 130, "bitwise_and");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (r = bitwise_and_1(p)) ||
    (r = shift_expr(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(bitwise_and_1) {
    ENTER_FRAME(p, 131, "bitwise_and:1");
    FAstNode *a, *b;
    (a = bitwise_and(p)) &&
    (TOKEN(p, 28, "&")) &&
    (b = shift_expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// shift_expr:
//     | shift_expr '<<' sum
//     | shift_expr '>>' sum
//     | sum
RULE(shift_expr) {
    ENTER_FRAME(p, 132, "shift_expr");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (r = shift_expr_1(p)) ||
    (r = shift_expr_2(p)) ||
    (r = sum(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(shift_expr_1) {
    ENTER_FRAME(p, 133, "shift_expr:1");
    FAstNode *a, *b;
    (a = shift_expr(p)) &&
    (TOKEN(p, 48, "<<")) &&
    (b = sum(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(shift_expr_2) {
    ENTER_FRAME(p, 134, "shift_expr:2");
    FAstNode *a, *b;
    (a = shift_expr(p)) &&
    (TOKEN(p, 49, ">>")) &&
    (b = sum(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// sum:
//     | sum '+' term
//     | sum '-' term
//     | term
RULE(sum) {
    ENTER_FRAME(p, 135, "sum");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (r = sum_1(p)) ||
    (r = sum_2(p)) ||
    (r = term(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(sum_1) {
    ENTER_FRAME(p, 136, "sum:1");
    FAstNode *a, *b;
    (a = sum(p)) &&
    (TOKEN(p, 21, "+")) &&
    (b = term(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(sum_2) {
    ENTER_FRAME(p, 137, "sum:2");
    FAstNode *a, *b;
    (a = sum(p)) &&
    (TOKEN(p, 22, "-")) &&
    (b = term(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// term:
//     | term '*' pipe_expr
//     | term '/' pipe_expr
//     | term '%' pipe_expr
//     | term '//' pipe_expr
//     | term '@' pipe_expr
//     | pipe_expr
RULE(term) {
    ENTER_FRAME(p, 138, "term");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (r = term_1(p)) ||
    (r = term_2(p)) ||
    (r = term_3(p)) ||
    (r = term_4(p)) ||
    (r = term_5(p)) ||
    (r = pipe_expr(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(term_1) {
    ENTER_FRAME(p, 139, "term:1");
    FAstNode *a, *b;
    (a = term(p)) &&
    (TOKEN(p, 23, "*")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(term_2) {
    ENTER_FRAME(p, 140, "term:2");
    FAstNode *a, *b;
    (a = term(p)) &&
    (TOKEN(p, 24, "/")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(term_3) {
    ENTER_FRAME(p, 141, "term:3");
    FAstNode *a, *b;
    (a = term(p)) &&
    (TOKEN(p, 25, "%")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(term_4) {
    ENTER_FRAME(p, 142, "term:4");
    FAstNode *a, *b;
    (a = term(p)) &&
    (TOKEN(p, 37, "//")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(term_5) {
    ENTER_FRAME(p, 143, "term:5");
    FAstNode *a, *b;
    (a = term(p)) &&
    (TOKEN(p, 26, "@")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// pipe_expr:
//     | pipe_expr '->' factor
//     | factor
RULE(pipe_expr) {
    ENTER_FRAME(p, 144, "pipe_expr");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (r = pipe_expr_1(p)) ||
    (r = factor(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(pipe_expr_1) {
    ENTER_FRAME(p, 145, "pipe_expr:1");
    FAstNode *a, *b;
    (a = pipe_expr(p)) &&
    (TOKEN(p, 35, "->")) &&
    (b = factor(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
RULE(factor) {
    ENTER_FRAME(p, 146, "factor");
    (r = factor_1(p)) ||
    (r = factor_2(p)) ||
    (r = factor_3(p)) ||
    (r = power(p));
    EXIT_FRAME(p);
}

RULE(factor_1) {
    ENTER_FRAME(p, 147, "factor:1");
    FAstNode *a;
    (TOKEN(p, 21, "+")) &&
    (a = factor(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(factor_2) {
    ENTER_FRAME(p, 148, "factor:2");
    FAstNode *a;
    (TOKEN(p, 22, "-")) &&
    (a = factor(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(factor_3) {
    ENTER_FRAME(p, 149, "factor:3");
    FAstNode *a;
    (TOKEN(p, 29, "~")) &&
    (a = factor(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// power:
//     | primary '**' factor
//     | primary
RULE(power) {
    ENTER_FRAME(p, 150, "power");
    (r = power_1(p)) ||
    (r = primary(p));
    EXIT_FRAME(p);
}

RULE(power_1) {
    ENTER_FRAME(p, 151, "power:1");
    FAstNode *a, *b;
    (a = primary(p)) &&
    (TOKEN(p, 38, "**")) &&
    (b = factor(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// primary:
//     | primary '.' NAME
//     | primary invocation
//     | primary subscript
//     | atom
RULE(primary) {
    ENTER_FRAME(p, 152, "primary");
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (r = primary_1(p)) ||
    (r = primary_2(p)) ||
    (r = primary_3(p)) ||
    (r = atom(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(primary_1) {
    ENTER_FRAME(p, 153, "primary:1");
    FAstNode *a, *b;
    (a = primary(p)) &&
    (TOKEN(p, 6, ".")) &&
    (b = TOKEN(p, 3, "NAME"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(primary_2) {
    ENTER_FRAME(p, 154, "primary:2");
    FAstNode *a, *b;
    (a = primary(p)) &&
    (b = invocation(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(primary_3) {
    ENTER_FRAME(p, 155, "primary:3");
    FAstNode *a, *b;
    (a = primary(p)) &&
    (b = subscript(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// tuple_atom:
//     | '(' [named_expr_list] ')'
RULE(tuple_atom) {
    ENTER_FRAME(p, 156, "tuple_atom");
    FAstNode *a;
    (TOKEN(p, 13, "(")) &&
    (a = OPTIONAL(named_expr_list(p))) &&
    (TOKEN(p, 14, ")"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// list_iter:
//     | '[' expr_or_star iterator ']'
RULE(list_iter) {
    ENTER_FRAME(p, 157, "list_iter");
    FAstNode *a, *b;
    (TOKEN(p, 17, "[")) &&
    (a = expr_or_star(p)) &&
    (b = iterator(p)) &&
    (TOKEN(p, 18, "]"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// list_atom:
//     | '[' [named_expr_list] ']'
RULE(list_atom) {
    ENTER_FRAME(p, 158, "list_atom");
    FAstNode *a;
    (TOKEN(p, 17, "[")) &&
    (a = OPTIONAL(named_expr_list(p))) &&
    (TOKEN(p, 18, "]"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// set_atom:
//     | '{' [exprlist_star] '}'
RULE(set_atom) {
    ENTER_FRAME(p, 159, "set_atom");
    FAstNode *a;
    (TOKEN(p, 15, "{")) &&
    (a = OPTIONAL(exprlist_star(p))) &&
    (TOKEN(p, 16, "}"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// dict_iter:
//     | '{' dict_item iterator '}'
RULE(dict_iter) {
    ENTER_FRAME(p, 160, "dict_iter");
    FAstNode *a, *b;
    (TOKEN(p, 15, "{")) &&
    (a = dict_item(p)) &&
    (b = iterator(p)) &&
    (TOKEN(p, 16, "}"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// dict_atom:
//     | '{' [dict_items] '}'
RULE(dict_atom) {
    ENTER_FRAME(p, 161, "dict_atom");
    FAstNode *a;
    (TOKEN(p, 15, "{")) &&
    (a = OPTIONAL(dict_items(p))) &&
    (TOKEN(p, 16, "}"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// builder:
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
RULE(builder) {
    ENTER_FRAME(p, 162, "builder");
    (r = builder_1(p)) ||
    (r = builder_2(p));
    EXIT_FRAME(p);
}

RULE(builder_1) {
    ENTER_FRAME(p, 163, "builder:1");
    FAstNode *a, *b, *c;
    (a = TOKEN(p, 3, "NAME")) &&
    (b = simple_args(p)) &&
    (TOKEN(p, 9, ":")) &&
    (c = expr(p))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

RULE(builder_2) {
    ENTER_FRAME(p, 164, "builder:2");
    FAstNode *a, *b, *c, *d;
    (a = TOKEN(p, 3, "NAME")) &&
    (b = OPTIONAL(builder_hint(p))) &&
    (c = OPTIONAL(builder_args(p))) &&
    (d = block_suite(p))
    ? (r = NODE_4(p, a, b, c, d)) : 0;
    EXIT_FRAME(p);
}

// atom:
//     | tuple_atom
//     | list_iter
//     | list_atom
//     | set_atom
//     | dict_iter
//     | dict_atom
//     | builder
//     | NAME
//     | NUMBER
//     | STRING
//     | 'None'
//     | 'True'
//     | 'False'
RULE(atom) {
    ENTER_FRAME(p, 165, "atom");
    (r = tuple_atom(p)) ||
    (r = list_iter(p)) ||
    (r = list_atom(p)) ||
    (r = set_atom(p)) ||
    (r = dict_iter(p)) ||
    (r = dict_atom(p)) ||
    (r = builder(p)) ||
    (r = TOKEN(p, 3, "NAME")) ||
    (r = TOKEN(p, 4, "NUMBER")) ||
    (r = TOKEN(p, 5, "STRING")) ||
    (r = TOKEN(p, 81, "None")) ||
    (r = TOKEN(p, 82, "True")) ||
    (r = TOKEN(p, 83, "False"));
    EXIT_FRAME(p);
}
