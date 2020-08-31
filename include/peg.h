
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

typedef struct {
    void (*enter_frame)(int level, int pos, int rule_index, const char *rule_name);

    void (*memo_hit)(int level, int pos, int rule_index, const char *rule_name);

    void (*exit_frame)(void *res, int level, int pos, int rule_index, const char *rule_name);

    void (*mark_token)(void *res, int level, int expected, int actual, const char *literal);
} FPegDebugHook;

typedef struct peg_parser_t {
    size_t pos;
    size_t max_reached_pos;
    size_t token_len;
    FToken **tokens;
    FMemRegion *region;
    int ignore_whitespace;
    size_t level;
    FPegDebugHook *dh;
} FPegParser;

#define PARSER_ALLOC(p, size) FMemRegion_malloc((p)->region, size)

typedef struct ast_node_t FAstNode;

#define RULE(name) FAstNode *name(FPegParser *p)

typedef struct ast_sequence_t {
    size_t len;
    size_t capacity;
    FAstNode **items;
} FAstSequence;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define AST_IS_TOKEN(node) node->ast_t & 1 // NOLINT(bugprone-macro-parentheses)
#define AST_IS_SEQUENCE(node) node->ast_t & 2 // NOLINT(bugprone-macro-parentheses)
#define AST_GET_RULE(node) node->ast_t >> 2
#define AST_GET_TOKEN(node) node->ast_v.token
#define AST_GET_SEQUENCE(node) node->ast_v.sequence

#pragma clang diagnostic pop

#define AST_NODE_MAX_FIELD 4

struct ast_node_t {
    unsigned int ast_t;
    union ast_v {
        FToken *token;
        FAstSequence sequence;
        FAstNode *fields[AST_NODE_MAX_FIELD];
    } ast_v;
};

FPegParser *FPeg_new_parser(FMemRegion *region, FTokenArray *a, FPegDebugHook *dh);

char *FPeg_check_state(FPegParser *p);

FTokenMemo *FPeg_new_memo(FPegParser *p, int type, void *node, int end);

void FPeg_put_memo(FPegParser *p, int type, void *node, int end);

FTokenMemo *FPeg_get_memo(FPegParser *p, int type);

#define AST_CONSUME(p, type, value) FPeg_consume_token(p, type)

FAstNode *FPeg_consume_token(FPegParser *p, int type);

#define AST_SEQ_NEW(p) FAst_new_sequence(p)

FAstNode *FAst_new_sequence(FPegParser *p);

#define AST_SEQ_APPEND(p, list, item) FAst_seq_append(p, list, item)

void FAst_seq_append(FPegParser *p, FAstNode *seq, void *item);

#define AST_NEW_NODE(p, t, nargs, ...) FAst_new_node(p, t, nargs, __VA_ARGS__)

FAstNode *FAst_new_node(FPegParser *p, unsigned int t, int nargs, ...);

#define SEQ_OR_NONE(p, rule) FPeg_parse_sequece_or_none(p, rule)

FAstNode *FPeg_parse_sequece_or_none(FPegParser *p, FAstNode *(*rule)(FPegParser *));

#define SEQUENCE(p, rule) FPeg_parse_sequence(p, rule)

FAstNode *FPeg_parse_sequence(FPegParser *p, FAstNode *(*rule)(FPegParser *));

#define DELIMITED(p, delimiter, literal, rule) FPeg_parse_delimited(p, delimiter, rule)

FAstNode *FPeg_parse_delimited(FPegParser *p, int delimiter, FAstNode *(*rule)(FPegParser *));

#endif //CPEG_PEG_H
