#ifndef CPEG_AST_H
#define CPEG_AST_H

#include "mem.h"
#include "peg.h"

typedef struct ast_node_t FAstNode;


#define AST_NODE_MAX_FIELD 4

struct ast_node_t {
    // type layout:
    // - bit 1: set for non-sequence type
    // - bit 2: set for token type
    // - other bits: token index if bit 2 set,
    //   rule index otherwise
    unsigned int ast_t;
    union ast_v {
        FToken *token;
        FAstNode *fields[AST_NODE_MAX_FIELD];
    } ast_v;
};

#define R_CHECK(node, t) (!((node)->ast_t & 2u) && (node)->ast_t >> 2u == (t))
#define T_CHECK(node, t) ((node)->ast_t & 2u && (node)->ast_t >> 2u == (t))
#define S_CHECK(node) !((node)->ast_t & 1u)

typedef struct ast_list_t {
    size_t len;
    size_t capacity;
    void **items;
} ast_list;


FAstNode *FPeg_consume_token(FParser *p, size_t type);

FAstNode *FPeg_consume_token_and_debug(FParser *p, size_t type, const char *literal);

FAstNode *FAst_new_node(FParser *p, size_t t, int nargs, ...);

ast_list *ast_list_new(FParser *p);

void ast_list_append(FParser *p, ast_list *seq, void *item);

#endif //CPEG_AST_H
