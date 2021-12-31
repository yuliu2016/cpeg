#include "include/ast.h"

ast_expr_t *ast_binary(parser_t *p, ast_expr_t *left, 
        ast_expr_t *right, enum expr_opcode binop_code) {
    ast_expr_t *r = PARSER_ALLOC(p, sizeof(ast_expr_t));
    r->opcode = binop_code;
    r->left.expr = left;
    r->right = right;
    return r;
}

ast_expr_t *ast_unary(parser_t *p, ast_expr_t *expr, enum expr_opcode unary_opcode) {
    return ast_binary(p, expr, NULL, unary_opcode);
}

ast_expr_t *ast_primary_expr(parser_t *p, void *primary) {
    ast_expr_t *r = PARSER_ALLOC(p, sizeof(ast_expr_t));
    r->opcode = BINOP_PRIMARY;
    r->left.primary = primary;
    r->right = NULL;
    return r;
}