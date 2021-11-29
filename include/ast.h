#ifndef CPEG_AST_H
#define CPEG_AST_H

#include "mem.h"
#include "peg.h"

typedef struct ast_node_t FAstNode;

typedef struct ast_sequence_t {
    size_t len;
    size_t capacity;
    FAstNode **items;
} FAstSequence;

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
        FAstSequence sequence;
        FAstNode *fields[AST_NODE_MAX_FIELD];
    } ast_v;
};

#define R_CHECK(node, t) (!((node)->ast_t & 2u) && (node)->ast_t >> 2u == (t))
#define T_CHECK(node, t) ((node)->ast_t & 2u && (node)->ast_t >> 2u == (t))
#define S_CHECK(node) !((node)->ast_t & 1u)


FAstNode *FPeg_consume_token(FParser *p, size_t type);

FAstNode *FPeg_consume_token_and_debug(FParser *p, size_t type, const char *literal);

FAstNode *FAst_new_node(FParser *p, size_t t, int nargs, ...);

FAstNode *FPeg_parse_sequece_or_none(FParser *p, FRuleFunc rule);

FAstNode *FPeg_parse_sequence(FParser *p, FRuleFunc rule);

FAstNode *FPeg_parse_delimited(FParser *p, size_t delimiter, FRuleFunc rule);

FAstNode *FPeg_parse_token_sequence(FParser *p, size_t token);

FAstNode *FPeg_parse_token_sequence_or_none(FParser *p, size_t token);

FAstNode *FPeg_parse_token_delimited(FParser *p, size_t delimiter, size_t token);

#endif //CPEG_AST_H
