
#ifndef CPEG_PEG_H
#define CPEG_PEG_H

#include "mem.h"


// PEG parse tree implementation
// Source of implementation algorithms:
// https://github.com/python/cpython/blob/master/Grammar/python.gram
// https://medium.com/@gvanrossum_83706/left-recursive-peg-grammars-65dab3c580e1
// https://www.python.org/dev/peps/pep-0617/
// https://github.com/PhilippeSigaud/Pegged/wiki/Left-Recursion


// Memo stored in a linked list, assuming not storing
// too many types at the same position
typedef struct token_memo_t {
    unsigned int type;
    void *node;
    size_t end_pos;
    struct token_memo_t *next;
} FTokenMemo;

typedef struct {
    unsigned int type;
    char *start;
    int len;
    int lineno;
    int column;
    int is_whitespace;
    FTokenMemo *memo;
} FToken;

typedef struct token_array_t {
    int len;
    FToken **tokens;
} FTokenArray;

typedef struct {
    void (*enter_frame)(int level, int pos, int rule_index, const char *rule_name);
    void (*memo_hit)(int level, int pos, int rule_index, const char *rule_name);
    void (*exit_frame)(void *res, int level, int pos, int rule_index, const char *rule_name);
    void (*mark_token)(void *res, int level, int expected, int actual, const char *literal);
} FPegDebugHook;

// Lazily-evaluated tokenizer
typedef struct lexer_state_t {
    // Test source
    char *src_buf;
    size_t src_len;

    // Index of the visitor
    size_t curr_index;

    // Dynamically-growing list of tokens
    FToken **tokens;
    size_t token_len;
    size_t token_capacity;

    // Dynamically-growing list of line indices
    size_t *line_to_index;
    size_t lines;
    size_t line_capacity;

    // end of the last token
    size_t last_end_index;

    char *error;
} FLexerState;

typedef struct parser_state_t {
    // Use to get lazily scan the next token
    FLexerState lexer_state;

    // Use to get the next token
    FToken *(*lexer_func)(FLexerState *);

    // Allocate nodes in the same region so it can be freed all at once
    FMemRegion *region;

    size_t pos;
    size_t max_reached_pos;

    // Use for space-insensitive blocks (like between brackets)
    int ignore_whitespace;

    char *error;

    // Debugging
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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define ASSERT_AST_T(node, t) FAst_node_assert_type(node, t)
#define R_CHECK(node, t) (!((node)->ast_t & 2u) && (node)->ast_t >> 2u == (t))
#define T_CHECK(node, t) ((node)->ast_t & 2u && (node)->ast_t >> 2u == (t))
#define S_CHECK(node) !((node)->ast_t & 1u)

#pragma clang diagnostic pop

typedef unsigned int index_t;

FPegParser *FPeg_new_parser(FMemRegion *region, FTokenArray *a, FPegDebugHook *dh);

char *FPeg_check_state(FPegParser *p);

void FAst_node_assert_type(FAstNode *node, index_t t);

void FPeg_put_memo(FPegParser *p, index_t type, void *node, size_t end);

FTokenMemo *FPeg_get_memo(FPegParser *p, index_t type);

// Macros used in the parser

#define AST_CONSUME(p, type, value) FPeg_consume_token(p, type)
#define AST_NEW_NODE(p, t, nargs, ...) FAst_new_node(p, t, nargs, __VA_ARGS__)
#define SEQ_OR_NONE(p, rule) FPeg_parse_sequece_or_none(p, rule)
#define SEQUENCE(p, rule) FPeg_parse_sequence(p, rule)
#define DELIMITED(p, delimiter, literal, rule) FPeg_parse_delimited(p, delimiter, rule)
#define TOKEN_SEQ_OR_NONE(p, t, v) FPeg_parse_token_sequence_or_none(p, t)
#define TOKEN_SEQUENCE(p, t, v) FPeg_parse_token_sequence(p, t)
#define TOKEN_DELIMITED(p, delimiter, literal, t, v) FPeg_parse_token_delimited(p, delimiter, t)

FAstNode *FPeg_consume_token(FPegParser *p, index_t type);

FAstNode *FAst_new_node(FPegParser *p, index_t t, int nargs, ...);

typedef FAstNode *(*FRuleFunc)(FPegParser *);

FAstNode *FPeg_parse_sequece_or_none(FPegParser *p, FRuleFunc rule);

FAstNode *FPeg_parse_sequence(FPegParser *p, FRuleFunc rule);

FAstNode *FPeg_parse_delimited(FPegParser *p, index_t delimiter, FRuleFunc rule);

FAstNode *FPeg_parse_token_sequence(FPegParser *p, index_t token);

FAstNode *FPeg_parse_token_sequence_or_none(FPegParser *p, index_t token);

FAstNode *FPeg_parse_token_delimited(FPegParser *p, index_t delimiter, index_t token);

#endif //CPEG_PEG_H
