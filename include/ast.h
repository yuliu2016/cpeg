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


static inline FAstNode *node_0(FParser *p, void *f) {
    return FAst_new_node(p, 0, 0);
}

static inline FAstNode *node_1(FParser *p, void *f, FAstNode *a) {
    return FAst_new_node(p, 0, 1, a);
}

static inline FAstNode *node_2(FParser *p, void *f, FAstNode *a , FAstNode *b) {
    return FAst_new_node(p, 0, 2, a, b);
}

static inline FAstNode *node_3(FParser *p, void *f, FAstNode *a, FAstNode *b, FAstNode *c) {
    return FAst_new_node(p, 0, 3, a, b, c);
}

static inline FAstNode *node_4(FParser *p, void *f, FAstNode *a, FAstNode *b, FAstNode *c, FAstNode *d) {
    return FAst_new_node(p, 0, 4, a, b, c, d);
}

#endif //CPEG_AST_H
