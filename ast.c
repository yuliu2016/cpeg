#include "include/ast.h"

ast_expr_t *ast_binary(parser_t *p, ast_expr_t *left, 
        ast_expr_t *right, enum expr_opcode binop_code) {
    ast_expr_t *r = parser_alloc(p, sizeof(ast_expr_t));
    r->opcode = binop_code;
    r->left = left;
    r->right.expr = right;
    return r;
}

ast_expr_t *ast_unary(parser_t *p, ast_expr_t *expr, enum expr_opcode unary_opcode) {
    return ast_binary(p, expr, NULL, unary_opcode);
}

ast_expr_t *ast_primary_expr(parser_t *p, void *primary) {
    ast_expr_t *r = parser_alloc(p, sizeof(ast_expr_t));
    r->opcode = BINOP_PRIMARY;
    r->left = NULL;
    r->right.primary = primary;
    return r;
}

int *ast_integer(parser_t *p, int i) {
    int *r = parser_alloc(p, sizeof(int));
    *r = i;
    return r;
}

ast_expr_t *ast_conditional(parser_t *p, ast_expr_t *cond, ast_expr_t *a, ast_expr_t *b) {
    return node(p);
}

ast_named_t *ast_named(parser_t *p, token_t *name, ast_expr_t *expr) {
    return node(p);
}

ast_named_t *ast_unnamed(parser_t *p, ast_expr_t *expr) {
    return ast_named(p, NULL, expr);
}

ast_expr_t *ast_comp_term(parser_t *p, int *comp_op, ast_expr_t *operand) {
    return node(p);
}

ast_expr_t *ast_comparison(parser_t *p, ast_expr_t *first, ast_list_t *terms) {
    return node(p);
}

ast_stmt_t *ast_nop(parser_t *p) {
    return node(p);
}

ast_stmt_t *ast_break(parser_t *p) {
    return node(p);
}

ast_stmt_t *ast_continue(parser_t *p) {
    return node(p);
}

ast_primary_t *ast_name_atom(parser_t *p, token_t *name) {
    return  node(p);
}

ast_primary_t *ast_number_atom(parser_t *p, token_t *name) {
    return node(p);
}

ast_primary_t *ast_string_atom(parser_t *p, token_t *name) {
    return  node(p);
}

ast_primary_t *ast_none(parser_t *p) {
    return node(p);
}

ast_primary_t *ast_true(parser_t *p) {
    return node(p);
}

ast_primary_t *ast_false(parser_t *p) {
    return  node(p);
}