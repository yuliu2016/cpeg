#include "include/parser.h"
#include "include/internal/peg_macros.h"

// single_input:
//     | NEWLINE
//     | ENDMARKER
//     | simple_stmt
//     | compound_stmt NEWLINE
RULE(single_input) {
    ENTER(1);
    (a = TOKEN(2, "NEWLINE")) ||
    (a = TOKEN(1, "ENDMARKER")) ||
    (a = simple_stmt(p)) ||
    (a = single_input_4(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(single_input_4) {
    ENTER(2);
    (a = compound_stmt(p)) &&
    (b = TOKEN(2, "NEWLINE"))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// file_input:
//     | [stmt_list] ENDMARKER
RULE(file_input) {
    ENTER(3);
    (a = OPT(stmt_list(p))) &&
    (b = TOKEN(1, "ENDMARKER"))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// eval_input:
//     | exprlist NEWLINE* ENDMARKER
RULE(eval_input) {
    ENTER(4);
    (a = exprlist(p)) &&
    (b = TOKEN_SEQ_OR_NONE(p, 2, "NEWLINE")) &&
    (c = TOKEN(1, "ENDMARKER"))
    ? (r = NODE_3()) : 0; 
    EXIT();
}

// stmt_list:
//     | stmt+
RULE(stmt_list) {
    ENTER(5);
    (a = SEQUENCE(p, stmt))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// stmt:
//     | (simple_stmt | compound_stmt) NEWLINE
RULE(stmt) {
    ENTER(6);
    (a = stmt_1(p)) &&
    (b = TOKEN(2, "NEWLINE"))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(stmt_1) {
    ENTER(7);
    (a = simple_stmt(p)) ||
    (a = compound_stmt(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

// simple_stmt:
//     | ';'.small_stmt+ [';']
RULE(simple_stmt) {
    ENTER(8);
    (a = DELIMITED(p, 12, ";", small_stmt)) &&
    (b = OPT(TOKEN(12, ";")))
    ? (r = NODE_2()) : 0; 
    EXIT();
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
    ENTER(9);
    (a = TOKEN(64, "pass")) ||
    (a = TOKEN(74, "break")) ||
    (a = TOKEN(73, "continue")) ||
    (a = return_stmt(p)) ||
    (a = raise_stmt(p)) ||
    (a = del_stmt(p)) ||
    (a = nonlocal_stmt(p)) ||
    (a = assert_stmt(p)) ||
    (a = import_name(p)) ||
    (a = import_from(p)) ||
    (a = assignment(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

// del_stmt:
//     | 'del' targetlist
RULE(del_stmt) {
    ENTER(10);
    (TOKEN(79, "del")) &&
    (a = targetlist(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// return_stmt:
//     | 'return' [exprlist_star]
RULE(return_stmt) {
    ENTER(11);
    (TOKEN(54, "return")) &&
    (a = OPT(exprlist_star(p)))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// raise_stmt:
//     | 'raise' expr ['from' expr]
RULE(raise_stmt) {
    ENTER(12);
    (TOKEN(78, "raise")) &&
    (a = expr(p)) &&
    (b = OPT(raise_stmt_3(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(raise_stmt_3) {
    ENTER(13);
    (TOKEN(66, "from")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// nonlocal_stmt:
//     | 'nonlocal' name_list
RULE(nonlocal_stmt) {
    ENTER(14);
    (TOKEN(55, "nonlocal")) &&
    (a = name_list(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// assert_stmt:
//     | 'assert' expr [',' expr]
RULE(assert_stmt) {
    ENTER(15);
    (TOKEN(80, "assert")) &&
    (a = expr(p)) &&
    (b = OPT(assert_stmt_3(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(assert_stmt_3) {
    ENTER(16);
    (TOKEN(7, ",")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// name_list:
//     | ','.NAME+
RULE(name_list) {
    ENTER(17);
    (a = TOKEN_DELIMITED(p, 7, ",", 3, "NAME"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// star_expr:
//     | '*' bitwise_or
RULE(star_expr) {
    ENTER(18);
    (TOKEN(23, "*")) &&
    (a = bitwise_or(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// exprlist:
//     | ','.expr+ [',']
RULE(exprlist) {
    ENTER(19);
    (a = DELIMITED(p, 7, ",", expr)) &&
    (b = OPT(TOKEN(7, ",")))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// target:
//     | t_primary '.' NAME !t_lookahead
//     | t_primary subscript !t_lookahead
//     | NAME
//     | '(' targetlist_sp ')'
RULE(target) {
    ENTER(20);
    (a = target_1(p)) ||
    (a = target_2(p)) ||
    (a = TOKEN(3, "NAME")) ||
    (a = target_4(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(target_1) {
    ENTER(21);
    (a = t_primary(p)) &&
    (TOKEN(6, ".")) &&
    (b = TOKEN(3, "NAME")) &&
    (!TEST(t_lookahead(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(target_2) {
    ENTER(22);
    (a = t_primary(p)) &&
    (b = subscript(p)) &&
    (!TEST(t_lookahead(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(target_4) {
    ENTER(23);
    (TOKEN(13, "(")) &&
    (a = targetlist_sp(p)) &&
    (TOKEN(14, ")"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// targetlist_sp (allow_whitespace=true):
//     | targetlist
RULE(targetlist_sp) {
    ENTER(24);
    WS_PUSH_1();
    (a = targetlist(p))
    ? (r = NODE_1()) : 0; 
    WS_POP();
    EXIT();
}

// t_primary (left_recursive):
//     | t_primary '.' NAME &t_lookahead
//     | t_primary invocation &t_lookahead
//     | t_primary subscript &t_lookahead
//     | atom &t_lookahead
RULE(t_primary) {
    ENTER(25);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = t_primary_1(p)) ||
    (a = t_primary_2(p)) ||
    (a = t_primary_3(p)) ||
    (a = t_primary_4(p));
    EXIT_LEFT_RECURSION();
    EXIT();
}

RULE(t_primary_1) {
    ENTER(26);
    (a = t_primary(p)) &&
    (TOKEN(6, ".")) &&
    (b = TOKEN(3, "NAME")) &&
    (TEST(t_lookahead(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(t_primary_2) {
    ENTER(27);
    (a = t_primary(p)) &&
    (b = invocation(p)) &&
    (TEST(t_lookahead(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(t_primary_3) {
    ENTER(28);
    (a = t_primary(p)) &&
    (b = subscript(p)) &&
    (TEST(t_lookahead(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(t_primary_4) {
    ENTER(29);
    (a = atom(p)) &&
    (TEST(t_lookahead(p)))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// t_lookahead:
//     | '.'
//     | '('
//     | '['
RULE(t_lookahead) {
    ENTER(30);
    (a = TOKEN(6, ".")) ||
    (a = TOKEN(13, "(")) ||
    (a = TOKEN(17, "["))
    ? (r = NODE_1()) : 0;
    EXIT();
}

// targetlist:
//     | ','.target+ [',']
RULE(targetlist) {
    ENTER(31);
    (a = DELIMITED(p, 7, ",", target)) &&
    (b = OPT(TOKEN(7, ",")))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// expr_or_star:
//     | star_expr
//     | expr
RULE(expr_or_star) {
    ENTER(32);
    (a = star_expr(p)) ||
    (a = expr(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

// exprlist_star:
//     | ','.expr_or_star+ [',']
RULE(exprlist_star) {
    ENTER(33);
    (a = DELIMITED(p, 7, ",", expr_or_star)) &&
    (b = OPT(TOKEN(7, ",")))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// subscript:
//     | '[' slicelist ']'
RULE(subscript) {
    ENTER(34);
    (TOKEN(17, "[")) &&
    (a = slicelist(p)) &&
    (TOKEN(18, "]"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// slicelist:
//     | ','.slice+ [',']
RULE(slicelist) {
    ENTER(35);
    (a = DELIMITED(p, 7, ",", slice)) &&
    (b = OPT(TOKEN(7, ",")))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// slice:
//     | [expr] slice_expr [slice_expr]
//     | expr
RULE(slice) {
    ENTER(36);
    (a = slice_1(p)) ||
    (a = expr(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(slice_1) {
    ENTER(37);
    (a = OPT(expr(p))) &&
    (b = slice_expr(p)) &&
    (c = OPT(slice_expr(p)))
    ? (r = NODE_3()) : 0; 
    EXIT();
}

// slice_expr:
//     | ':' [expr]
RULE(slice_expr) {
    ENTER(38);
    (TOKEN(9, ":")) &&
    (a = OPT(expr(p)))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// dict_item:
//     | expr ':' expr
//     | '**' bitwise_or
RULE(dict_item) {
    ENTER(39);
    (a = dict_item_1(p)) ||
    (a = dict_item_2(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(dict_item_1) {
    ENTER(40);
    (a = expr(p)) &&
    (TOKEN(9, ":")) &&
    (b = expr(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(dict_item_2) {
    ENTER(41);
    (TOKEN(38, "**")) &&
    (a = bitwise_or(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// dict_items (allow_whitespace=true):
//     | ','.dict_item+ [',']
RULE(dict_items) {
    ENTER(42);
    WS_PUSH_1();
    (a = DELIMITED(p, 7, ",", dict_item)) &&
    (b = OPT(TOKEN(7, ",")))
    ? (r = NODE_2()) : 0; 
    WS_POP();
    EXIT();
}

// list_item:
//     | star_expr
//     | named_expr
RULE(list_item) {
    ENTER(43);
    (a = star_expr(p)) ||
    (a = named_expr(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

// list_items (allow_whitespace=true):
//     | ','.list_item+ [',']
RULE(list_items) {
    ENTER(44);
    WS_PUSH_1();
    (a = DELIMITED(p, 7, ",", list_item)) &&
    (b = OPT(TOKEN(7, ",")))
    ? (r = NODE_2()) : 0; 
    WS_POP();
    EXIT();
}

// set_items (allow_whitespace=true):
//     | exprlist_star
RULE(set_items) {
    ENTER(45);
    WS_PUSH_1();
    (a = exprlist_star(p))
    ? (r = NODE_1()) : 0; 
    WS_POP();
    EXIT();
}

// as_name:
//     | 'as' NAME
RULE(as_name) {
    ENTER(46);
    (TOKEN(65, "as")) &&
    (a = TOKEN(3, "NAME"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// iter_for:
//     | 'for' targetlist 'in' disjunction [iter_if]
RULE(iter_for) {
    ENTER(47);
    (TOKEN(72, "for")) &&
    (a = targetlist(p)) &&
    (TOKEN(63, "in")) &&
    (b = disjunction(p)) &&
    (c = OPT(iter_if(p)))
    ? (r = NODE_3()) : 0; 
    EXIT();
}

// iter_if:
//     | 'if' named_expr
RULE(iter_if) {
    ENTER(48);
    (TOKEN(56, "if")) &&
    (a = named_expr(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// iterator:
//     | iter_for* 'for' targetlist [iter_if]
RULE(iterator) {
    ENTER(49);
    (a = SEQ_OR_NONE(p, iter_for)) &&
    (TOKEN(72, "for")) &&
    (b = targetlist(p)) &&
    (c = OPT(iter_if(p)))
    ? (r = NODE_3()) : 0; 
    EXIT();
}

// list_iterator (allow_whitespace=true):
//     | expr_or_star iterator
RULE(list_iterator) {
    ENTER(50);
    WS_PUSH_1();
    (a = expr_or_star(p)) &&
    (b = iterator(p))
    ? (r = NODE_2()) : 0; 
    WS_POP();
    EXIT();
}

// dict_iterator (allow_whitespace=true):
//     | dict_item iterator
RULE(dict_iterator) {
    ENTER(51);
    WS_PUSH_1();
    (a = dict_item(p)) &&
    (b = iterator(p))
    ? (r = NODE_2()) : 0; 
    WS_POP();
    EXIT();
}

// assignment:
//     | pubassign
//     | annassign
//     | augassign
//     | simple_assign
RULE(assignment) {
    ENTER(52);
    (a = pubassign(p)) ||
    (a = annassign(p)) ||
    (a = augassign(p)) ||
    (a = simple_assign(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

// pubassign:
//     | '/' NAME '=' exprlist
RULE(pubassign) {
    ENTER(53);
    (TOKEN(24, "/")) &&
    (a = TOKEN(3, "NAME")) &&
    (TOKEN(8, "=")) &&
    (b = exprlist(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// annassign:
//     | target ':' expr ['=' exprlist]
RULE(annassign) {
    ENTER(54);
    (a = target(p)) &&
    (TOKEN(9, ":")) &&
    (b = expr(p)) &&
    (c = OPT(annassign_4(p)))
    ? (r = NODE_3()) : 0; 
    EXIT();
}

RULE(annassign_4) {
    ENTER(55);
    (TOKEN(8, "=")) &&
    (a = exprlist(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// augassign:
//     | target augassign_op exprlist
RULE(augassign) {
    ENTER(56);
    (a = target(p)) &&
    (b = augassign_op(p)) &&
    (c = exprlist(p))
    ? (r = NODE_3()) : 0; 
    EXIT();
}

// simple_assign:
//     | (targetlist '=')* exprlist_star
RULE(simple_assign) {
    ENTER(57);
    (a = SEQ_OR_NONE(p, simple_assign_1)) &&
    (b = exprlist_star(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(simple_assign_1) {
    ENTER(58);
    (a = targetlist(p)) &&
    (TOKEN(8, "="))
    ? (r = NODE_1()) : 0; 
    EXIT();
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
    ENTER(59);
    (a = TOKEN(39, "+=")) ||
    (a = TOKEN(40, "-=")) ||
    (a = TOKEN(41, "*=")) ||
    (a = TOKEN(44, "@=")) ||
    (a = TOKEN(42, "/=")) ||
    (a = TOKEN(43, "%=")) ||
    (a = TOKEN(46, "&=")) ||
    (a = TOKEN(45, "|=")) ||
    (a = TOKEN(47, "^=")) ||
    (a = TOKEN(52, "<<=")) ||
    (a = TOKEN(53, ">>=")) ||
    (a = TOKEN(51, "**=")) ||
    (a = TOKEN(50, "//="))
    ? (r = NODE_1()) : 0;
    EXIT();
}

// import_name:
//     | 'import' dotted_as_names
RULE(import_name) {
    ENTER(60);
    (TOKEN(67, "import")) &&
    (a = dotted_as_names(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// import_from:
//     | 'from' import_from_names 'import' import_from_items
RULE(import_from) {
    ENTER(61);
    (TOKEN(66, "from")) &&
    (a = import_from_names(p)) &&
    (TOKEN(67, "import")) &&
    (b = import_from_items(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// import_from_names:
//     | dotted_name
//     | '.'+ [dotted_name]
RULE(import_from_names) {
    ENTER(62);
    (a = dotted_name(p)) ||
    (a = import_from_names_2(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(import_from_names_2) {
    ENTER(63);
    (TOKEN_SEQUENCE(p, 6, ".")) &&
    (a = OPT(dotted_name(p)))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// import_from_items:
//     | '*'
//     | import_as_names_sp
//     | import_as_names
RULE(import_from_items) {
    ENTER(64);
    (a = TOKEN(23, "*")) ||
    (a = import_as_names_sp(p)) ||
    (a = import_as_names(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

// import_as_names_sp (allow_whitespace=true):
//     | '(' import_as_names [','] ')'
RULE(import_as_names_sp) {
    ENTER(65);
    WS_PUSH_1();
    (TOKEN(13, "(")) &&
    (a = import_as_names(p)) &&
    (b = OPT(TOKEN(7, ","))) &&
    (TOKEN(14, ")"))
    ? (r = NODE_2()) : 0; 
    WS_POP();
    EXIT();
}

// import_as_name:
//     | NAME [as_name]
RULE(import_as_name) {
    ENTER(66);
    (a = TOKEN(3, "NAME")) &&
    (b = OPT(as_name(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// dotted_as_name:
//     | dotted_name [as_name]
RULE(dotted_as_name) {
    ENTER(67);
    (a = dotted_name(p)) &&
    (b = OPT(as_name(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// import_as_names:
//     | ','.import_as_name+
RULE(import_as_names) {
    ENTER(68);
    (a = DELIMITED(p, 7, ",", import_as_name))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// dotted_as_names:
//     | ','.dotted_as_name+
RULE(dotted_as_names) {
    ENTER(69);
    (a = DELIMITED(p, 7, ",", dotted_as_name))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// dotted_name:
//     | '.'.NAME+
RULE(dotted_name) {
    ENTER(70);
    (a = TOKEN_DELIMITED(p, 6, ".", 3, "NAME"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// compound_stmt:
//     | if_stmt
//     | while_stmt
//     | for_stmt
//     | try_stmt
//     | with_stmt
RULE(compound_stmt) {
    ENTER(71);
    (a = if_stmt(p)) ||
    (a = while_stmt(p)) ||
    (a = for_stmt(p)) ||
    (a = try_stmt(p)) ||
    (a = with_stmt(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

// if_stmt:
//     | 'if' named_expr suite elif_stmt* [else_suite]
RULE(if_stmt) {
    ENTER(72);
    (TOKEN(56, "if")) &&
    (a = named_expr(p)) &&
    (b = suite(p)) &&
    (c = SEQ_OR_NONE(p, elif_stmt)) &&
    (d = OPT(else_suite(p)))
    ? (r = NODE_4()) : 0; 
    EXIT();
}

// elif_stmt:
//     | 'elif' named_expr suite
RULE(elif_stmt) {
    ENTER(73);
    (TOKEN(57, "elif")) &&
    (a = named_expr(p)) &&
    (b = suite(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// while_stmt:
//     | 'while' named_expr suite [else_suite]
RULE(while_stmt) {
    ENTER(74);
    (TOKEN(71, "while")) &&
    (a = named_expr(p)) &&
    (b = suite(p)) &&
    (c = OPT(else_suite(p)))
    ? (r = NODE_3()) : 0; 
    EXIT();
}

// for_stmt:
//     | 'for' targetlist 'in' exprlist suite [else_suite]
RULE(for_stmt) {
    ENTER(75);
    (TOKEN(72, "for")) &&
    (a = targetlist(p)) &&
    (TOKEN(63, "in")) &&
    (b = exprlist(p)) &&
    (c = suite(p)) &&
    (d = OPT(else_suite(p)))
    ? (r = NODE_4()) : 0; 
    EXIT();
}

// try_stmt:
//     | 'try' suite (except_suite | finally_suite)
RULE(try_stmt) {
    ENTER(76);
    (TOKEN(75, "try")) &&
    (a = suite(p)) &&
    (b = try_stmt_3(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(try_stmt_3) {
    ENTER(77);
    (a = except_suite(p)) ||
    (a = finally_suite(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

// with_stmt:
//     | 'with' ','.expr_as_name+ suite
RULE(with_stmt) {
    ENTER(78);
    (TOKEN(68, "with")) &&
    (a = DELIMITED(p, 7, ",", expr_as_name)) &&
    (b = suite(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// expr_as_name:
//     | expr [as_name]
RULE(expr_as_name) {
    ENTER(79);
    (a = expr(p)) &&
    (b = OPT(as_name(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// block_suite (allow_whitespace=false):
//     | '{' NEWLINE stmt_list '}'
//     | '{' [simple_stmt] '}'
RULE(block_suite) {
    ENTER(80);
    WS_PUSH_0();
    (a = block_suite_1(p)) ||
    (a = block_suite_2(p))
    ? (r = NODE_1()) : 0;
    WS_POP();
    EXIT();
}

RULE(block_suite_1) {
    ENTER(81);
    (TOKEN(15, "{")) &&
    (a = TOKEN(2, "NEWLINE")) &&
    (b = stmt_list(p)) &&
    (TOKEN(16, "}"))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(block_suite_2) {
    ENTER(82);
    (TOKEN(15, "{")) &&
    (a = OPT(simple_stmt(p))) &&
    (TOKEN(16, "}"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// suite:
//     | ':' simple_stmt
//     | block_suite
RULE(suite) {
    ENTER(83);
    (a = suite_1(p)) ||
    (a = block_suite(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(suite_1) {
    ENTER(84);
    (TOKEN(9, ":")) &&
    (a = simple_stmt(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// else_suite:
//     | 'else' suite
RULE(else_suite) {
    ENTER(85);
    (TOKEN(58, "else")) &&
    (a = suite(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// finally_suite:
//     | 'finally' suite
RULE(finally_suite) {
    ENTER(86);
    (TOKEN(77, "finally")) &&
    (a = suite(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// except_clause:
//     | 'except' [expr_as_name] suite
RULE(except_clause) {
    ENTER(87);
    (TOKEN(76, "except")) &&
    (a = OPT(expr_as_name(p))) &&
    (b = suite(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// except_suite:
//     | except_clause+ [else_suite] [finally_suite]
RULE(except_suite) {
    ENTER(88);
    (a = SEQUENCE(p, except_clause)) &&
    (b = OPT(else_suite(p))) &&
    (c = OPT(finally_suite(p)))
    ? (r = NODE_3()) : 0; 
    EXIT();
}

// invocation:
//     | '(' [call_arg_list] ')'
RULE(invocation) {
    ENTER(89);
    (TOKEN(13, "(")) &&
    (a = OPT(call_arg_list(p))) &&
    (TOKEN(14, ")"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// call_arg_list (allow_whitespace=true):
//     | ','.call_arg+ [',']
RULE(call_arg_list) {
    ENTER(90);
    WS_PUSH_1();
    (a = DELIMITED(p, 7, ",", call_arg)) &&
    (b = OPT(TOKEN(7, ",")))
    ? (r = NODE_2()) : 0; 
    WS_POP();
    EXIT();
}

// call_arg:
//     | NAME ':=' expr
//     | NAME '=' expr
//     | '**' expr
//     | '*' expr
//     | expr
RULE(call_arg) {
    ENTER(91);
    (a = call_arg_1(p)) ||
    (a = call_arg_2(p)) ||
    (a = call_arg_3(p)) ||
    (a = call_arg_4(p)) ||
    (a = expr(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(call_arg_1) {
    ENTER(92);
    (a = TOKEN(3, "NAME")) &&
    (TOKEN(36, ":=")) &&
    (b = expr(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(call_arg_2) {
    ENTER(93);
    (a = TOKEN(3, "NAME")) &&
    (TOKEN(8, "=")) &&
    (b = expr(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(call_arg_3) {
    ENTER(94);
    (TOKEN(38, "**")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

RULE(call_arg_4) {
    ENTER(95);
    (TOKEN(23, "*")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// typed_arg_list (allow_whitespace=true):
//     | kwargs
//     | args_kwargs
//     | full_arg_list
RULE(typed_arg_list) {
    ENTER(96);
    WS_PUSH_1();
    (a = kwargs(p)) ||
    (a = args_kwargs(p)) ||
    (a = full_arg_list(p))
    ? (r = NODE_1()) : 0;
    WS_POP();
    EXIT();
}

// full_arg_list:
//     | ','.default_arg+ [',' [kwargs | args_kwargs]]
RULE(full_arg_list) {
    ENTER(97);
    (a = DELIMITED(p, 7, ",", default_arg)) &&
    (b = OPT(full_arg_list_2(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(full_arg_list_2) {
    ENTER(98);
    (TOKEN(7, ",")) &&
    (a = OPT(full_arg_list_2_2(p)))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

RULE(full_arg_list_2_2) {
    ENTER(99);
    (a = kwargs(p)) ||
    (a = args_kwargs(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

// args_kwargs:
//     | '*' [typed_arg] (',' default_arg)* [',' [kwargs]]
RULE(args_kwargs) {
    ENTER(100);
    (TOKEN(23, "*")) &&
    (a = OPT(typed_arg(p))) &&
    (b = SEQ_OR_NONE(p, args_kwargs_3)) &&
    (c = OPT(args_kwargs_4(p)))
    ? (r = NODE_3()) : 0; 
    EXIT();
}

RULE(args_kwargs_3) {
    ENTER(101);
    (TOKEN(7, ",")) &&
    (a = default_arg(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

RULE(args_kwargs_4) {
    ENTER(102);
    (TOKEN(7, ",")) &&
    (a = OPT(kwargs(p)))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// kwargs:
//     | '**' typed_arg [',']
RULE(kwargs) {
    ENTER(103);
    (TOKEN(38, "**")) &&
    (a = typed_arg(p)) &&
    (b = OPT(TOKEN(7, ",")))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// default_arg:
//     | typed_arg ['=' expr]
RULE(default_arg) {
    ENTER(104);
    (a = typed_arg(p)) &&
    (b = OPT(default_arg_2(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(default_arg_2) {
    ENTER(105);
    (TOKEN(8, "=")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// typed_arg:
//     | NAME [':' expr]
RULE(typed_arg) {
    ENTER(106);
    (a = TOKEN(3, "NAME")) &&
    (b = OPT(typed_arg_2(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(typed_arg_2) {
    ENTER(107);
    (TOKEN(9, ":")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// simple_arg:
//     | NAME ['=' expr]
RULE(simple_arg) {
    ENTER(108);
    (a = TOKEN(3, "NAME")) &&
    (b = OPT(simple_arg_2(p)))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(simple_arg_2) {
    ENTER(109);
    (TOKEN(8, "=")) &&
    (a = expr(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// simple_args:
//     | ','.simple_arg+
RULE(simple_args) {
    ENTER(110);
    (a = DELIMITED(p, 7, ",", simple_arg))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// builder_hint:
//     | '<' name_list '>'
RULE(builder_hint) {
    ENTER(111);
    (TOKEN(19, "<")) &&
    (a = name_list(p)) &&
    (TOKEN(20, ">"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// builder_args:
//     | simple_args
//     | '(' [typed_arg_list] ')'
RULE(builder_args) {
    ENTER(112);
    (a = simple_args(p)) ||
    (a = builder_args_2(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(builder_args_2) {
    ENTER(113);
    (TOKEN(13, "(")) &&
    (a = OPT(typed_arg_list(p))) &&
    (TOKEN(14, ")"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// named_expr:
//     | NAME ':=' expr
//     | expr
RULE(named_expr) {
    ENTER(114);
    (a = named_expr_1(p)) ||
    (a = expr(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(named_expr_1) {
    ENTER(115);
    (a = TOKEN(3, "NAME")) &&
    (TOKEN(36, ":=")) &&
    (b = expr(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// conditional:
//     | 'if' disjunction '?' disjunction ':' expr
RULE(conditional) {
    ENTER(116);
    (TOKEN(56, "if")) &&
    (a = disjunction(p)) &&
    (TOKEN(10, "?")) &&
    (b = disjunction(p)) &&
    (TOKEN(9, ":")) &&
    (c = expr(p))
    ? (r = NODE_3()) : 0; 
    EXIT();
}

// expr:
//     | conditional
//     | disjunction
RULE(expr) {
    ENTER(117);
    (a = conditional(p)) ||
    (a = disjunction(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

// disjunction (left_recursive):
//     | disjunction 'or' conjunction
//     | conjunction
RULE(disjunction) {
    ENTER(118);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = disjunction_1(p)) ||
    (a = conjunction(p));
    EXIT_LEFT_RECURSION();
    EXIT();
}

RULE(disjunction_1) {
    ENTER(119);
    (a = disjunction(p)) &&
    (TOKEN(60, "or")) &&
    (b = conjunction(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// conjunction (left_recursive):
//     | conjunction 'and' inversion
//     | inversion
RULE(conjunction) {
    ENTER(120);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = conjunction_1(p)) ||
    (a = inversion(p));
    EXIT_LEFT_RECURSION();
    EXIT();
}

RULE(conjunction_1) {
    ENTER(121);
    (a = conjunction(p)) &&
    (TOKEN(59, "and")) &&
    (b = inversion(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// inversion:
//     | 'not' inversion
//     | comparison
RULE(inversion) {
    ENTER(122);
    (a = inversion_1(p)) ||
    (a = comparison(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(inversion_1) {
    ENTER(123);
    (TOKEN(61, "not")) &&
    (a = inversion(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// comparison:
//     | bitwise_or (comp_op bitwise_or)+
//     | bitwise_or
RULE(comparison) {
    ENTER(124);
    (a = comparison_1(p)) ||
    (a = bitwise_or(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(comparison_1) {
    ENTER(125);
    (a = bitwise_or(p)) &&
    (b = SEQUENCE(p, comparison_1_2))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(comparison_1_2) {
    ENTER(126);
    (a = comp_op(p)) &&
    (b = bitwise_or(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
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
    ENTER(127);
    (a = TOKEN(19, "<")) ||
    (a = TOKEN(20, ">")) ||
    (a = TOKEN(31, "==")) ||
    (a = TOKEN(34, ">=")) ||
    (a = TOKEN(33, "<=")) ||
    (a = TOKEN(32, "!=")) ||
    (a = TOKEN(63, "in")) ||
    (a = comp_op_8(p)) ||
    (a = TOKEN(62, "is")) ||
    (a = comp_op_10(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(comp_op_8) {
    ENTER(128);
    (TOKEN(61, "not")) &&
    (TOKEN(63, "in"));
    EXIT();
}

RULE(comp_op_10) {
    ENTER(129);
    (TOKEN(62, "is")) &&
    (TOKEN(61, "not"));
    EXIT();
}

// bitwise_or (left_recursive):
//     | bitwise_or '|' bitwise_xor
//     | bitwise_xor
RULE(bitwise_or) {
    ENTER(130);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = bitwise_or_1(p)) ||
    (a = bitwise_xor(p));
    EXIT_LEFT_RECURSION();
    EXIT();
}

RULE(bitwise_or_1) {
    ENTER(131);
    (a = bitwise_or(p)) &&
    (TOKEN(27, "|")) &&
    (b = bitwise_xor(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// bitwise_xor (left_recursive):
//     | bitwise_xor '^' bitwise_and
//     | bitwise_and
RULE(bitwise_xor) {
    ENTER(132);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = bitwise_xor_1(p)) ||
    (a = bitwise_and(p));
    EXIT_LEFT_RECURSION();
    EXIT();
}

RULE(bitwise_xor_1) {
    ENTER(133);
    (a = bitwise_xor(p)) &&
    (TOKEN(30, "^")) &&
    (b = bitwise_and(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// bitwise_and (left_recursive):
//     | bitwise_and '&' shift_expr
//     | shift_expr
RULE(bitwise_and) {
    ENTER(134);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = bitwise_and_1(p)) ||
    (a = shift_expr(p));
    EXIT_LEFT_RECURSION();
    EXIT();
}

RULE(bitwise_and_1) {
    ENTER(135);
    (a = bitwise_and(p)) &&
    (TOKEN(28, "&")) &&
    (b = shift_expr(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// shift_expr (left_recursive):
//     | shift_expr '<<' sum
//     | shift_expr '>>' sum
//     | sum
RULE(shift_expr) {
    ENTER(136);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = shift_expr_1(p)) ||
    (a = shift_expr_2(p)) ||
    (a = sum(p));
    EXIT_LEFT_RECURSION();
    EXIT();
}

RULE(shift_expr_1) {
    ENTER(137);
    (a = shift_expr(p)) &&
    (TOKEN(48, "<<")) &&
    (b = sum(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(shift_expr_2) {
    ENTER(138);
    (a = shift_expr(p)) &&
    (TOKEN(49, ">>")) &&
    (b = sum(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// sum (left_recursive):
//     | sum '+' term
//     | sum '-' term
//     | term
RULE(sum) {
    ENTER(139);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = sum_1(p)) ||
    (a = sum_2(p)) ||
    (a = term(p));
    EXIT_LEFT_RECURSION();
    EXIT();
}

RULE(sum_1) {
    ENTER(140);
    (a = sum(p)) &&
    (TOKEN(21, "+")) &&
    (b = term(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(sum_2) {
    ENTER(141);
    (a = sum(p)) &&
    (TOKEN(22, "-")) &&
    (b = term(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// term (left_recursive):
//     | term '*' pipe_expr
//     | term '/' pipe_expr
//     | term '%' pipe_expr
//     | term '//' pipe_expr
//     | term '@' pipe_expr
//     | pipe_expr
RULE(term) {
    ENTER(142);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = term_1(p)) ||
    (a = term_2(p)) ||
    (a = term_3(p)) ||
    (a = term_4(p)) ||
    (a = term_5(p)) ||
    (a = pipe_expr(p));
    EXIT_LEFT_RECURSION();
    EXIT();
}

RULE(term_1) {
    ENTER(143);
    (a = term(p)) &&
    (TOKEN(23, "*")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(term_2) {
    ENTER(144);
    (a = term(p)) &&
    (TOKEN(24, "/")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(term_3) {
    ENTER(145);
    (a = term(p)) &&
    (TOKEN(25, "%")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(term_4) {
    ENTER(146);
    (a = term(p)) &&
    (TOKEN(37, "//")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(term_5) {
    ENTER(147);
    (a = term(p)) &&
    (TOKEN(26, "@")) &&
    (b = pipe_expr(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// pipe_expr (left_recursive):
//     | pipe_expr '->' factor
//     | factor
RULE(pipe_expr) {
    ENTER(148);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = pipe_expr_1(p)) ||
    (a = factor(p));
    EXIT_LEFT_RECURSION();
    EXIT();
}

RULE(pipe_expr_1) {
    ENTER(149);
    (a = pipe_expr(p)) &&
    (TOKEN(35, "->")) &&
    (b = factor(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// factor:
//     | '+' factor
//     | '-' factor
//     | '~' factor
//     | power
RULE(factor) {
    ENTER(150);
    (a = factor_1(p)) ||
    (a = factor_2(p)) ||
    (a = factor_3(p)) ||
    (a = power(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(factor_1) {
    ENTER(151);
    (TOKEN(21, "+")) &&
    (a = factor(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

RULE(factor_2) {
    ENTER(152);
    (TOKEN(22, "-")) &&
    (a = factor(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

RULE(factor_3) {
    ENTER(153);
    (TOKEN(29, "~")) &&
    (a = factor(p))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// power:
//     | primary '**' factor
//     | primary
RULE(power) {
    ENTER(154);
    (a = power_1(p)) ||
    (a = primary(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(power_1) {
    ENTER(155);
    (a = primary(p)) &&
    (TOKEN(38, "**")) &&
    (b = factor(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// primary (left_recursive):
//     | primary '.' NAME
//     | primary invocation
//     | primary subscript
//     | atom
RULE(primary) {
    ENTER(156);
    RETURN_IF_MEMOIZED();
    ENTER_LEFT_RECURSION();
    (a = primary_1(p)) ||
    (a = primary_2(p)) ||
    (a = primary_3(p)) ||
    (a = atom(p));
    EXIT_LEFT_RECURSION();
    EXIT();
}

RULE(primary_1) {
    ENTER(157);
    (a = primary(p)) &&
    (TOKEN(6, ".")) &&
    (b = TOKEN(3, "NAME"))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(primary_2) {
    ENTER(158);
    (a = primary(p)) &&
    (b = invocation(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

RULE(primary_3) {
    ENTER(159);
    (a = primary(p)) &&
    (b = subscript(p))
    ? (r = NODE_2()) : 0; 
    EXIT();
}

// tuple_atom:
//     | '(' [list_items] ')'
RULE(tuple_atom) {
    ENTER(160);
    (TOKEN(13, "(")) &&
    (a = OPT(list_items(p))) &&
    (TOKEN(14, ")"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// list_iterable:
//     | '[' list_iterator ']'
RULE(list_iterable) {
    ENTER(161);
    (TOKEN(17, "[")) &&
    (a = list_iterator(p)) &&
    (TOKEN(18, "]"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// list_atom:
//     | '[' [list_items] ']'
RULE(list_atom) {
    ENTER(162);
    (TOKEN(17, "[")) &&
    (a = OPT(list_items(p))) &&
    (TOKEN(18, "]"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// set_atom:
//     | '{' [set_items] '}'
RULE(set_atom) {
    ENTER(163);
    (TOKEN(15, "{")) &&
    (a = OPT(set_items(p))) &&
    (TOKEN(16, "}"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// dict_iterable:
//     | '{' dict_iterator '}'
RULE(dict_iterable) {
    ENTER(164);
    (TOKEN(15, "{")) &&
    (a = dict_iterator(p)) &&
    (TOKEN(16, "}"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// dict_atom:
//     | '{' [dict_items] '}'
RULE(dict_atom) {
    ENTER(165);
    (TOKEN(15, "{")) &&
    (a = OPT(dict_items(p))) &&
    (TOKEN(16, "}"))
    ? (r = NODE_1()) : 0; 
    EXIT();
}

// builder:
//     | NAME simple_args ':' expr
//     | NAME [builder_hint] [builder_args] block_suite
RULE(builder) {
    ENTER(166);
    (a = builder_1(p)) ||
    (a = builder_2(p))
    ? (r = NODE_1()) : 0;
    EXIT();
}

RULE(builder_1) {
    ENTER(167);
    (a = TOKEN(3, "NAME")) &&
    (b = simple_args(p)) &&
    (TOKEN(9, ":")) &&
    (c = expr(p))
    ? (r = NODE_3()) : 0; 
    EXIT();
}

RULE(builder_2) {
    ENTER(168);
    (a = TOKEN(3, "NAME")) &&
    (b = OPT(builder_hint(p))) &&
    (c = OPT(builder_args(p))) &&
    (d = block_suite(p))
    ? (r = NODE_4()) : 0; 
    EXIT();
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
RULE(atom) {
    ENTER(169);
    (a = tuple_atom(p)) ||
    (a = list_iterable(p)) ||
    (a = list_atom(p)) ||
    (a = set_atom(p)) ||
    (a = dict_iterable(p)) ||
    (a = dict_atom(p)) ||
    (a = builder(p)) ||
    (a = TOKEN(3, "NAME")) ||
    (a = TOKEN(4, "NUMBER")) ||
    (a = TOKEN(5, "STRING")) ||
    (a = TOKEN(81, "None")) ||
    (a = TOKEN(82, "True")) ||
    (a = TOKEN(83, "False"))
    ? (r = NODE_1()) : 0;
    EXIT();
}
