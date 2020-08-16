
#ifndef CPEG_PEG_H
#define CPEG_PEG_H

#include "mem.h"
#include "token.h"

/**
 * PEG parse tree implementation
 * Source of implementation algorithms:
 * https://github.com/python/cpython/blob/master/Grammar/python.gram
 * https://medium.com/@gvanrossum_83706/left-recursive-peg-grammars-65dab3c580e1
 * https://www.python.org/dev/peps/pep-0617/
 * https://github.com/PhilippeSigaud/Pegged/wiki/Left-Recursion
 */

typedef struct peg_debug_hook_t {
    void (*enter_frame)(int level, int pos, int rule_index, const char *rule_name);

    void (*memo_hit)(int level, int pos, int rule_index, const char *rule_name);

    void (*exit_frame)(void *res, int level, int pos, int rule_index, const char *rule_name);

    void (*mark_token)(void *res, int level, int expected, int actual, const char *literal);
} FPegDebugHook;

typedef struct peg_parser_t {
    size_t pos;
    size_t max_reached_pos;
    size_t level;
    FToken **tokens;
    size_t token_len;
    FPegDebugHook *debug_hook;
    FMemRegion *region;
} FPegParser;

#define GET_CURR_TOKEN(p) p->tokens[p->pos]

#define PARSER_ALLOC(p, size) FMemRegion_malloc(p->region, size)

typedef struct ast_node_t FAstNode;

typedef struct ast_list_t {
    size_t len;
    size_t capacity;
    void **items;
} FAstList;

typedef struct ast_sequence_t {
    size_t len;
    FAstNode **items;
} FAstSequence;

#define AST_IS_TOKEN(node) node->ast_t & 1
#define AST_IS_SEQUENCE(node) node->ast_t & 2
#define AST_GET_RULE(node) node->ast_t >> 2
#define AST_GET_TOKEN(node) node->ast_v.token
#define AST_GET_SEQUENCE(node) node->ast_v.sequence

struct ast_node_t {
    unsigned int ast_t;
    union ast_v {
        FToken *token;
        FAstSequence sequence;
        FAstNode *fields[4];
    } ast_v;
};

FPegParser *FPeg_new_parser(FMemRegion *region, FTokenArray *a, FPegDebugHook *dh);

FToken *FPeg_consume_token(FPegParser *p, int type);

FToken *FPeg_consume_token_debug(FPegParser *p, int type, char *literal);

FTokenMemo *FPeg_new_memo(FPegParser *p, int type, void *node, int end);

void FPeg_put_memo(FPegParser *p, int type, void *node, int end);

FTokenMemo *FPeg_get_memo(FPegParser *p, int type);

FAstList *FPeg_new_list();

void FPeg_list_append(FAstList *list, void *item);


#endif //CPEG_PEG_H
