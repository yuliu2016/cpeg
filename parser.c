#include "include/parser.h"
#include "include/internal/peg_macros.h"

// single_input:
//     | NEWLINE
//     | simple_stmt
//     | compound_stmt NEWLINE
RULE(single_input) {
    ENTER_FRAME(p, 1);
    (a = TOKEN(p, 2, "NEWLINE")) ||
    (a = simple_stmt(p)) ||
    (a = single_input_3(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(single_input_3) {
    ENTER_FRAME(p, 2);
    (a = compound_stmt(p)) &&
    (b = TOKEN(p, 2, "NEWLINE"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// file_input:
//     | (NEWLINE | stmt)* ENDMARKER
RULE(file_input) {
    ENTER_FRAME(p, 3);
    (a = SEQ_OR_NONE(p, file_input_1)) &&
    (b = TOKEN(p, 1, "ENDMARKER"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(file_input_1) {
    ENTER_FRAME(p, 4);
    (a = TOKEN(p, 2, "NEWLINE")) ||
    (a = stmt(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// eval_input:
//     | exprlist NEWLINE* ENDMARKER
RULE(eval_input) {
    ENTER_FRAME(p, 5);
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
    ENTER_FRAME(p, 6);
    (a = stmt_1(p)) &&
    (b = TOKEN(p, 2, "NEWLINE"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(stmt_1) {
    ENTER_FRAME(p, 7);
    (a = simple_stmt(p)) ||
    (a = compound_stmt(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// simple_stmt:
//     | ';'.small_stmt+ [';']
RULE(simple_stmt) {
    ENTER_FRAME(p, 8);
    (a = DELIMITED(p, 12, ";", small_stmt)) &&
    (b = OPTIONAL(TOKEN(p, 12, ";")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
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
    ENTER_FRAME(p, 9);
    (a = TOKEN(p, 64, "pass")) ||
    (a = TOKEN(p, 74, "break")) ||
    (a = TOKEN(p, 73, "continue")) ||
    (a = return_stmt(p)) ||
    (a = raise_stmt(p)) ||
    (a = del_stmt(p)) ||
    (a = nonlocal_stmt(p)) ||
    (a = assert_stmt(p)) ||
    (a = import_name(p)) ||
    (a = import_from(p)) ||
    (a = assignment(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// del_stmt:
//     | 'del' targetlist
RULE(del_stmt) {
    ENTER_FRAME(p, 10);
    (TOKEN(p, 79, "del")) &&
    (a = targetlist(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// return_stmt:
//     | 'return' [exprlist_star]
RULE(return_stmt) {
    ENTER_FRAME(p, 11);
    (TOKEN(p, 54, "return")) &&
    (a = OPTIONAL(exprlist_star(p)))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// raise_stmt:
//     | 'raise' expr ['from' expr]
RULE(raise_stmt) {
    ENTER_FRAME(p, 12);
    (TOKEN(p, 78, "raise")) &&
    (a = expr(p)) &&
    (b = OPTIONAL(raise_stmt_3(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(raise_stmt_3) {
    ENTER_FRAME(p, 13);
    (TOKEN(p, 66, "from")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// nonlocal_stmt:
//     | 'nonlocal' name_list
RULE(nonlocal_stmt) {
    ENTER_FRAME(p, 14);
    (TOKEN(p, 55, "nonlocal")) &&
    (a = name_list(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// assert_stmt:
//     | 'assert' expr [',' expr]
RULE(assert_stmt) {
    ENTER_FRAME(p, 15);
    (TOKEN(p, 80, "assert")) &&
    (a = expr(p)) &&
    (b = OPTIONAL(assert_stmt_3(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(assert_stmt_3) {
    ENTER_FRAME(p, 16);
    (TOKEN(p, 7, ",")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// name_list:
//     | ','.NAME+
RULE(name_list) {
    ENTER_FRAME(p, 17);
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
            (TOKEN(p, 7, ",")) &&
            (node = TOKEN(p, 3, "NAME")));
    p->pos = pos;
    return seq;
}

// star_expr:
//     | '*' bitwise_or
RULE(star_expr) {
    ENTER_FRAME(p, 18);
    (TOKEN(p, 23, "*")) &&
    (a = bitwise_or(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// exprlist:
//     | ','.expr+ [',']
RULE(exprlist) {
    ENTER_FRAME(p, 19);
    (a = DELIMITED(p, 7, ",", expr)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// target:
//     | t_primary '.' NAME !t_lookahead
//     | t_primary subscript !t_lookahead
//     | NAME
//     | '(' targetlist ')'
RULE(target) {
    ENTER_FRAME(p, 20);
    (a = target_1(p)) ||
    (a = target_2(p)) ||
    (a = TOKEN(p, 3, "NAME")) ||
    (a = target_4(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(target_1) {
    ENTER_FRAME(p, 21);
    (a = t_primary(p)) &&
    (TOKEN(p, 6, ".")) &&
    (b = TOKEN(p, 3, "NAME")) &&
    (!TEST(p, t_lookahead(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(target_2) {
    ENTER_FRAME(p, 22);
    (a = t_primary(p)) &&
    (b = subscript(p)) &&
    (!TEST(p, t_lookahead(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(target_4) {
    ENTER_FRAME(p, 23);
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
    ENTER_FRAME(p, 24);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = t_primary_1(p)) ||
    (a = t_primary_2(p)) ||
    (a = t_primary_3(p)) ||
    (a = t_primary_4(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(t_primary_1) {
    ENTER_FRAME(p, 25);
    (a = t_primary(p)) &&
    (TOKEN(p, 6, ".")) &&
    (b = TOKEN(p, 3, "NAME")) &&
    (TEST(p, t_lookahead(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(t_primary_2) {
    ENTER_FRAME(p, 26);
    (a = t_primary(p)) &&
    (b = invocation(p)) &&
    (TEST(p, t_lookahead(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(t_primary_3) {
    ENTER_FRAME(p, 27);
    (a = t_primary(p)) &&
    (b = subscript(p)) &&
    (TEST(p, t_lookahead(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(t_primary_4) {
    ENTER_FRAME(p, 28);
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
    ENTER_FRAME(p, 29);
    (a = TOKEN(p, 6, ".")) ||
    (a = TOKEN(p, 13, "(")) ||
    (a = TOKEN(p, 17, "["))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// targetlist:
//     | ','.target+ [',']
RULE(targetlist) {
    ENTER_FRAME(p, 30);
    (a = DELIMITED(p, 7, ",", target)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// expr_or_star:
//     | star_expr
//     | expr
RULE(expr_or_star) {
    ENTER_FRAME(p, 31);
    (a = star_expr(p)) ||
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// exprlist_star:
//     | ','.expr_or_star+ [',']
RULE(exprlist_star) {
    ENTER_FRAME(p, 32);
    (a = DELIMITED(p, 7, ",", expr_or_star)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// named_expr_star:
//     | star_expr
//     | named_expr
RULE(named_expr_star) {
    ENTER_FRAME(p, 33);
    (a = star_expr(p)) ||
    (a = named_expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// named_expr_list:
//     | ','.named_expr_star+ [',']
RULE(named_expr_list) {
    ENTER_FRAME(p, 34);
    (a = DELIMITED(p, 7, ",", named_expr_star)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// subscript:
//     | '[' slicelist ']'
RULE(subscript) {
    ENTER_FRAME(p, 35);
    (TOKEN(p, 17, "[")) &&
    (a = slicelist(p)) &&
    (TOKEN(p, 18, "]"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// slicelist:
//     | ','.slice+ [',']
RULE(slicelist) {
    ENTER_FRAME(p, 36);
    (a = DELIMITED(p, 7, ",", slice)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// slice:
//     | [expr] slice_expr [slice_expr]
//     | expr
RULE(slice) {
    ENTER_FRAME(p, 37);
    (a = slice_1(p)) ||
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(slice_1) {
    ENTER_FRAME(p, 38);
    (a = OPTIONAL(expr(p))) &&
    (b = slice_expr(p)) &&
    (c = OPTIONAL(slice_expr(p)))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

// slice_expr:
//     | ':' [expr]
RULE(slice_expr) {
    ENTER_FRAME(p, 39);
    (TOKEN(p, 9, ":")) &&
    (a = OPTIONAL(expr(p)))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// dict_item:
//     | expr ':' expr
//     | '**' bitwise_or
RULE(dict_item) {
    ENTER_FRAME(p, 40);
    (a = dict_item_1(p)) ||
    (a = dict_item_2(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(dict_item_1) {
    ENTER_FRAME(p, 41);
    (a = expr(p)) &&
    (TOKEN(p, 9, ":")) &&
    (b = expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(dict_item_2) {
    ENTER_FRAME(p, 42);
    (TOKEN(p, 38, "**")) &&
    (a = bitwise_or(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// dict_items:
//     | ','.dict_item+ [',']
RULE(dict_items) {
    ENTER_FRAME(p, 43);
    (a = DELIMITED(p, 7, ",", dict_item)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// as_name:
//     | 'as' NAME
RULE(as_name) {
    ENTER_FRAME(p, 44);
    (TOKEN(p, 65, "as")) &&
    (a = TOKEN(p, 3, "NAME"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// iter_for:
//     | 'for' targetlist 'in' disjunction [iter_if]
RULE(iter_for) {
    ENTER_FRAME(p, 45);
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
    ENTER_FRAME(p, 46);
    (TOKEN(p, 56, "if")) &&
    (a = named_expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// iterator:
//     | iter_for* 'for' targetlist [iter_if]
RULE(iterator) {
    ENTER_FRAME(p, 47);
    (a = SEQ_OR_NONE(p, iter_for)) &&
    (TOKEN(p, 72, "for")) &&
    (b = targetlist(p)) &&
    (c = OPTIONAL(iter_if(p)))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

// assignment:
//     | pubassign
//     | annassign
//     | augassign
//     | simple_assign
RULE(assignment) {
    ENTER_FRAME(p, 48);
    (a = pubassign(p)) ||
    (a = annassign(p)) ||
    (a = augassign(p)) ||
    (a = simple_assign(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// pubassign:
//     | '/' NAME '=' exprlist
RULE(pubassign) {
    ENTER_FRAME(p, 49);
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
    ENTER_FRAME(p, 50);
    (a = target(p)) &&
    (TOKEN(p, 9, ":")) &&
    (b = expr(p)) &&
    (c = OPTIONAL(annassign_4(p)))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

RULE(annassign_4) {
    ENTER_FRAME(p, 51);
    (TOKEN(p, 8, "=")) &&
    (a = exprlist(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// augassign:
//     | target augassign_op exprlist
RULE(augassign) {
    ENTER_FRAME(p, 52);
    (a = target(p)) &&
    (b = augassign_op(p)) &&
    (c = exprlist(p))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
RULE(simple_assign) {
    ENTER_FRAME(p, 53);
    (a = SEQ_OR_NONE(p, simple_assign_1)) &&
    (b = exprlist_star(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(simple_assign_1) {
    ENTER_FRAME(p, 54);
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
    ENTER_FRAME(p, 55);
    (a = TOKEN(p, 39, "+=")) ||
    (a = TOKEN(p, 40, "-=")) ||
    (a = TOKEN(p, 41, "*=")) ||
    (a = TOKEN(p, 44, "@=")) ||
    (a = TOKEN(p, 42, "/=")) ||
    (a = TOKEN(p, 43, "%=")) ||
    (a = TOKEN(p, 46, "&=")) ||
    (a = TOKEN(p, 45, "|=")) ||
    (a = TOKEN(p, 47, "^=")) ||
    (a = TOKEN(p, 52, "<<=")) ||
    (a = TOKEN(p, 53, ">>=")) ||
    (a = TOKEN(p, 51, "**=")) ||
    (a = TOKEN(p, 50, "//="))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// import_name:
//     | 'import' dotted_as_names
RULE(import_name) {
    ENTER_FRAME(p, 56);
    (TOKEN(p, 67, "import")) &&
    (a = dotted_as_names(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// import_from:
//     | 'from' import_from_names 'import' import_from_items
RULE(import_from) {
    ENTER_FRAME(p, 57);
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
    ENTER_FRAME(p, 58);
    (a = dotted_name(p)) ||
    (a = import_from_names_2(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(import_from_names_2) {
    ENTER_FRAME(p, 59);
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
    ENTER_FRAME(p, 60);
    (a = TOKEN(p, 23, "*")) ||
    (a = import_from_items_2(p)) ||
    (a = import_as_names(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(import_from_items_2) {
    ENTER_FRAME(p, 61);
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
    ENTER_FRAME(p, 62);
    (a = TOKEN(p, 3, "NAME")) &&
    (b = OPTIONAL(as_name(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// dotted_as_name:
//     | dotted_name [as_name]
RULE(dotted_as_name) {
    ENTER_FRAME(p, 63);
    (a = dotted_name(p)) &&
    (b = OPTIONAL(as_name(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// import_as_names:
//     | ','.import_as_name+
RULE(import_as_names) {
    ENTER_FRAME(p, 64);
    (a = DELIMITED(p, 7, ",", import_as_name))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// dotted_as_names:
//     | ','.dotted_as_name+
RULE(dotted_as_names) {
    ENTER_FRAME(p, 65);
    (a = DELIMITED(p, 7, ",", dotted_as_name))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// dotted_name:
//     | '.'.NAME+
RULE(dotted_name) {
    ENTER_FRAME(p, 66);
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
            (TOKEN(p, 6, ".")) &&
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
    ENTER_FRAME(p, 67);
    (a = if_stmt(p)) ||
    (a = while_stmt(p)) ||
    (a = for_stmt(p)) ||
    (a = try_stmt(p)) ||
    (a = with_stmt(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
RULE(if_stmt) {
    ENTER_FRAME(p, 68);
    (TOKEN(p, 56, "if")) &&
    (a = named_expr(p)) &&
    (b = suite(p)) &&
    (c = SEQ_OR_NONE(p, elif_stmt)) &&
    (d = OPTIONAL(else_suite(p)))
    ? (r = NODE_4(p, a, b, c, d)) : 0;
    EXIT_FRAME(p);
}

// elif_stmt:
//     | 'elif' named_expr suite
RULE(elif_stmt) {
    ENTER_FRAME(p, 69);
    (TOKEN(p, 57, "elif")) &&
    (a = named_expr(p)) &&
    (b = suite(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
RULE(while_stmt) {
    ENTER_FRAME(p, 70);
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
    ENTER_FRAME(p, 71);
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
    ENTER_FRAME(p, 72);
    (TOKEN(p, 75, "try")) &&
    (a = suite(p)) &&
    (b = try_stmt_3(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(try_stmt_3) {
    ENTER_FRAME(p, 73);
    (a = except_suite(p)) ||
    (a = finally_suite(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
RULE(with_stmt) {
    ENTER_FRAME(p, 74);
    (TOKEN(p, 68, "with")) &&
    (a = DELIMITED(p, 7, ",", expr_as_name)) &&
    (b = suite(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// expr_as_name:
//     | expr [as_name]
RULE(expr_as_name) {
    ENTER_FRAME(p, 75);
    (a = expr(p)) &&
    (b = OPTIONAL(as_name(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// block_suite:
//     | '{' NEWLINE stmt+ '}'
//     | '{' '}'
RULE(block_suite) {
    ENTER_FRAME(p, 76);
    (a = block_suite_1(p)) ||
    (a = block_suite_2(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(block_suite_1) {
    ENTER_FRAME(p, 77);
    (TOKEN(p, 15, "{")) &&
    (a = TOKEN(p, 2, "NEWLINE")) &&
    (b = SEQUENCE(p, stmt)) &&
    (TOKEN(p, 16, "}"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(block_suite_2) {
    ENTER_FRAME(p, 78);
    (TOKEN(p, 15, "{")) &&
    (TOKEN(p, 16, "}"));
    EXIT_FRAME(p);
}

// suite:
//     | ':' simple_stmt
//     | block_suite
RULE(suite) {
    ENTER_FRAME(p, 79);
    (a = suite_1(p)) ||
    (a = block_suite(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(suite_1) {
    ENTER_FRAME(p, 80);
    (TOKEN(p, 9, ":")) &&
    (a = simple_stmt(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// else_suite:
//     | 'else' suite
RULE(else_suite) {
    ENTER_FRAME(p, 81);
    (TOKEN(p, 58, "else")) &&
    (a = suite(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// finally_suite:
//     | 'finally' suite
RULE(finally_suite) {
    ENTER_FRAME(p, 82);
    (TOKEN(p, 77, "finally")) &&
    (a = suite(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// except_clause:
//     | 'except' [expr_as_name] suite
RULE(except_clause) {
    ENTER_FRAME(p, 83);
    (TOKEN(p, 76, "except")) &&
    (a = OPTIONAL(expr_as_name(p))) &&
    (b = suite(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
RULE(except_suite) {
    ENTER_FRAME(p, 84);
    (a = SEQUENCE(p, except_clause)) &&
    (b = OPTIONAL(else_suite(p))) &&
    (c = OPTIONAL(finally_suite(p)))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

// invocation:
//     | '(' [call_arg_list] ')'
RULE(invocation) {
    ENTER_FRAME(p, 85);
    (TOKEN(p, 13, "(")) &&
    (a = OPTIONAL(call_arg_list(p))) &&
    (TOKEN(p, 14, ")"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// call_arg_list:
//     | ','.call_arg+ [',']
RULE(call_arg_list) {
    ENTER_FRAME(p, 86);
    (a = DELIMITED(p, 7, ",", call_arg)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// call_arg:
//     | NAME ':=' expr
//     | NAME '=' expr
//     | '**' expr
//     | '*' expr
//     | expr
RULE(call_arg) {
    ENTER_FRAME(p, 87);
    (a = call_arg_1(p)) ||
    (a = call_arg_2(p)) ||
    (a = call_arg_3(p)) ||
    (a = call_arg_4(p)) ||
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(call_arg_1) {
    ENTER_FRAME(p, 88);
    (a = TOKEN(p, 3, "NAME")) &&
    (TOKEN(p, 36, ":=")) &&
    (b = expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(call_arg_2) {
    ENTER_FRAME(p, 89);
    (a = TOKEN(p, 3, "NAME")) &&
    (TOKEN(p, 8, "=")) &&
    (b = expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(call_arg_3) {
    ENTER_FRAME(p, 90);
    (TOKEN(p, 38, "**")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(call_arg_4) {
    ENTER_FRAME(p, 91);
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
    ENTER_FRAME(p, 92);
    (a = kwargs(p)) ||
    (a = args_kwargs(p)) ||
    (a = full_arg_list(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
RULE(full_arg_list) {
    ENTER_FRAME(p, 93);
    (a = DELIMITED(p, 7, ",", default_arg)) &&
    (b = OPTIONAL(full_arg_list_2(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(full_arg_list_2) {
    ENTER_FRAME(p, 94);
    (TOKEN(p, 7, ",")) &&
    (a = OPTIONAL(full_arg_list_2_2(p)))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(full_arg_list_2_2) {
    ENTER_FRAME(p, 95);
    (a = kwargs(p)) ||
    (a = args_kwargs(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
RULE(args_kwargs) {
    ENTER_FRAME(p, 96);
    (TOKEN(p, 23, "*")) &&
    (a = OPTIONAL(typed_arg(p))) &&
    (b = SEQ_OR_NONE(p, args_kwargs_3)) &&
    (c = OPTIONAL(args_kwargs_4(p)))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

RULE(args_kwargs_3) {
    ENTER_FRAME(p, 97);
    (TOKEN(p, 7, ",")) &&
    (a = default_arg(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(args_kwargs_4) {
    ENTER_FRAME(p, 98);
    (TOKEN(p, 7, ",")) &&
    (a = OPTIONAL(kwargs(p)))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// kwargs:
//     | '**' typed_arg [',']
RULE(kwargs) {
    ENTER_FRAME(p, 99);
    (TOKEN(p, 38, "**")) &&
    (a = typed_arg(p)) &&
    (b = OPTIONAL(TOKEN(p, 7, ",")))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// default_arg:
//     | typed_arg ['=' expr]
RULE(default_arg) {
    ENTER_FRAME(p, 100);
    (a = typed_arg(p)) &&
    (b = OPTIONAL(default_arg_2(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(default_arg_2) {
    ENTER_FRAME(p, 101);
    (TOKEN(p, 8, "=")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// typed_arg:
//     | NAME [':' expr]
RULE(typed_arg) {
    ENTER_FRAME(p, 102);
    (a = TOKEN(p, 3, "NAME")) &&
    (b = OPTIONAL(typed_arg_2(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(typed_arg_2) {
    ENTER_FRAME(p, 103);
    (TOKEN(p, 9, ":")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// simple_arg:
//     | NAME ['=' expr]
RULE(simple_arg) {
    ENTER_FRAME(p, 104);
    (a = TOKEN(p, 3, "NAME")) &&
    (b = OPTIONAL(simple_arg_2(p)))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(simple_arg_2) {
    ENTER_FRAME(p, 105);
    (TOKEN(p, 8, "=")) &&
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// simple_args:
//     | ','.simple_arg+
RULE(simple_args) {
    ENTER_FRAME(p, 106);
    (a = DELIMITED(p, 7, ",", simple_arg))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// builder_hint:
//     | '<' name_list '>'
RULE(builder_hint) {
    ENTER_FRAME(p, 107);
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
    ENTER_FRAME(p, 108);
    (a = simple_args(p)) ||
    (a = builder_args_2(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(builder_args_2) {
    ENTER_FRAME(p, 109);
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
    ENTER_FRAME(p, 110);
    (a = named_expr_1(p)) ||
    (a = expr(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(named_expr_1) {
    ENTER_FRAME(p, 111);
    (a = TOKEN(p, 3, "NAME")) &&
    (TOKEN(p, 36, ":=")) &&
    (b = expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
RULE(conditional) {
    ENTER_FRAME(p, 112);
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
    ENTER_FRAME(p, 113);
    (a = conditional(p)) ||
    (a = disjunction(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// disjunction:
//     | disjunction 'or' conjunction
//     | conjunction
RULE(disjunction) {
    ENTER_FRAME(p, 114);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = disjunction_1(p)) ||
    (a = conjunction(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(disjunction_1) {
    ENTER_FRAME(p, 115);
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
    ENTER_FRAME(p, 116);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = conjunction_1(p)) ||
    (a = inversion(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(conjunction_1) {
    ENTER_FRAME(p, 117);
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
    ENTER_FRAME(p, 118);
    (a = inversion_1(p)) ||
    (a = comparison(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(inversion_1) {
    ENTER_FRAME(p, 119);
    (TOKEN(p, 61, "not")) &&
    (a = inversion(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
RULE(comparison) {
    ENTER_FRAME(p, 120);
    (a = comparison_1(p)) ||
    (a = bitwise_or(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(comparison_1) {
    ENTER_FRAME(p, 121);
    (a = bitwise_or(p)) &&
    (b = SEQUENCE(p, comparison_1_2))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(comparison_1_2) {
    ENTER_FRAME(p, 122);
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
    ENTER_FRAME(p, 123);
    (a = TOKEN(p, 19, "<")) ||
    (a = TOKEN(p, 20, ">")) ||
    (a = TOKEN(p, 31, "==")) ||
    (a = TOKEN(p, 34, ">=")) ||
    (a = TOKEN(p, 33, "<=")) ||
    (a = TOKEN(p, 32, "!=")) ||
    (a = TOKEN(p, 63, "in")) ||
    (a = comp_op_8(p)) ||
    (a = TOKEN(p, 62, "is")) ||
    (a = comp_op_10(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(comp_op_8) {
    ENTER_FRAME(p, 124);
    (TOKEN(p, 61, "not")) &&
    (TOKEN(p, 63, "in"));
    EXIT_FRAME(p);
}

RULE(comp_op_10) {
    ENTER_FRAME(p, 125);
    (TOKEN(p, 62, "is")) &&
    (TOKEN(p, 61, "not"));
    EXIT_FRAME(p);
}

// bitwise_or:
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
RULE(bitwise_or) {
    ENTER_FRAME(p, 126);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = bitwise_or_1(p)) ||
    (a = bitwise_xor(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(bitwise_or_1) {
    ENTER_FRAME(p, 127);
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
    ENTER_FRAME(p, 128);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = bitwise_xor_1(p)) ||
    (a = bitwise_and(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(bitwise_xor_1) {
    ENTER_FRAME(p, 129);
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
    ENTER_FRAME(p, 130);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = bitwise_and_1(p)) ||
    (a = shift_expr(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(bitwise_and_1) {
    ENTER_FRAME(p, 131);
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
    ENTER_FRAME(p, 132);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = shift_expr_1(p)) ||
    (a = shift_expr_2(p)) ||
    (a = sum(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(shift_expr_1) {
    ENTER_FRAME(p, 133);
    (a = shift_expr(p)) &&
    (TOKEN(p, 48, "<<")) &&
    (b = sum(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(shift_expr_2) {
    ENTER_FRAME(p, 134);
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
    ENTER_FRAME(p, 135);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = sum_1(p)) ||
    (a = sum_2(p)) ||
    (a = term(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(sum_1) {
    ENTER_FRAME(p, 136);
    (a = sum(p)) &&
    (TOKEN(p, 21, "+")) &&
    (b = term(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(sum_2) {
    ENTER_FRAME(p, 137);
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
    ENTER_FRAME(p, 138);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = term_1(p)) ||
    (a = term_2(p)) ||
    (a = term_3(p)) ||
    (a = term_4(p)) ||
    (a = term_5(p)) ||
    (a = pipe_expr(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(term_1) {
    ENTER_FRAME(p, 139);
    (a = term(p)) &&
    (TOKEN(p, 23, "*")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(term_2) {
    ENTER_FRAME(p, 140);
    (a = term(p)) &&
    (TOKEN(p, 24, "/")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(term_3) {
    ENTER_FRAME(p, 141);
    (a = term(p)) &&
    (TOKEN(p, 25, "%")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(term_4) {
    ENTER_FRAME(p, 142);
    (a = term(p)) &&
    (TOKEN(p, 37, "//")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(term_5) {
    ENTER_FRAME(p, 143);
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
    ENTER_FRAME(p, 144);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = pipe_expr_1(p)) ||
    (a = factor(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(pipe_expr_1) {
    ENTER_FRAME(p, 145);
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
    ENTER_FRAME(p, 146);
    (a = factor_1(p)) ||
    (a = factor_2(p)) ||
    (a = factor_3(p)) ||
    (a = power(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(factor_1) {
    ENTER_FRAME(p, 147);
    (TOKEN(p, 21, "+")) &&
    (a = factor(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(factor_2) {
    ENTER_FRAME(p, 148);
    (TOKEN(p, 22, "-")) &&
    (a = factor(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(factor_3) {
    ENTER_FRAME(p, 149);
    (TOKEN(p, 29, "~")) &&
    (a = factor(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// power:
//     | primary '**' factor
//     | primary
RULE(power) {
    ENTER_FRAME(p, 150);
    (a = power_1(p)) ||
    (a = primary(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(power_1) {
    ENTER_FRAME(p, 151);
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
    ENTER_FRAME(p, 152);
    RETURN_IF_MEMOIZED(p);
    ENTER_LEFT_RECURSION(p);
    (a = primary_1(p)) ||
    (a = primary_2(p)) ||
    (a = primary_3(p)) ||
    (a = atom(p));
    EXIT_LEFT_RECURSION(p);
    EXIT_FRAME(p);
}

RULE(primary_1) {
    ENTER_FRAME(p, 153);
    (a = primary(p)) &&
    (TOKEN(p, 6, ".")) &&
    (b = TOKEN(p, 3, "NAME"))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(primary_2) {
    ENTER_FRAME(p, 154);
    (a = primary(p)) &&
    (b = invocation(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

RULE(primary_3) {
    ENTER_FRAME(p, 155);
    (a = primary(p)) &&
    (b = subscript(p))
    ? (r = NODE_2(p, a, b)) : 0;
    EXIT_FRAME(p);
}

// tuple_atom:
//     | '(' [named_expr_list] ')'
RULE(tuple_atom) {
    ENTER_FRAME(p, 156);
    (TOKEN(p, 13, "(")) &&
    (a = OPTIONAL(named_expr_list(p))) &&
    (TOKEN(p, 14, ")"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// list_iter:
//     | '[' expr_or_star iterator ']'
RULE(list_iter) {
    ENTER_FRAME(p, 157);
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
    ENTER_FRAME(p, 158);
    (TOKEN(p, 17, "[")) &&
    (a = OPTIONAL(named_expr_list(p))) &&
    (TOKEN(p, 18, "]"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// set_atom:
//     | '{' [exprlist_star] '}'
RULE(set_atom) {
    ENTER_FRAME(p, 159);
    (TOKEN(p, 15, "{")) &&
    (a = OPTIONAL(exprlist_star(p))) &&
    (TOKEN(p, 16, "}"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

// dict_iter:
//     | '{' dict_item iterator '}'
RULE(dict_iter) {
    ENTER_FRAME(p, 160);
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
    ENTER_FRAME(p, 161);
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
    ENTER_FRAME(p, 162);
    (a = builder_1(p)) ||
    (a = builder_2(p))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}

RULE(builder_1) {
    ENTER_FRAME(p, 163);
    (a = TOKEN(p, 3, "NAME")) &&
    (b = simple_args(p)) &&
    (TOKEN(p, 9, ":")) &&
    (c = expr(p))
    ? (r = NODE_3(p, a, b, c)) : 0;
    EXIT_FRAME(p);
}

RULE(builder_2) {
    ENTER_FRAME(p, 164);
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
    ENTER_FRAME(p, 165);
    (a = tuple_atom(p)) ||
    (a = list_iter(p)) ||
    (a = list_atom(p)) ||
    (a = set_atom(p)) ||
    (a = dict_iter(p)) ||
    (a = dict_atom(p)) ||
    (a = builder(p)) ||
    (a = TOKEN(p, 3, "NAME")) ||
    (a = TOKEN(p, 4, "NUMBER")) ||
    (a = TOKEN(p, 5, "STRING")) ||
    (a = TOKEN(p, 81, "None")) ||
    (a = TOKEN(p, 82, "True")) ||
    (a = TOKEN(p, 83, "False"))
    ? (r = NODE_1(p, a)) : 0;
    EXIT_FRAME(p);
}
