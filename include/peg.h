
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
    size_t type;
    char *start;
    size_t len;
    size_t lineno;
    size_t column;
    int is_whitespace;
    FTokenMemo *memo;
} FToken;

// Lazily-evaluated tokenizer
typedef struct lexer_state_t {
    // Test source
    char *src;
    size_t src_len;

    // Index of the visitor
    size_t curr_index;

    // Index of the start of the token;
    size_t start_index;

    // Indentation level (multiple of 4, in spaces)
    size_t indent;

    // Dynamically-growing list of tokens
    FToken **tokens;
    size_t token_len;
    size_t token_capacity;

    // Stores next token to determine if stream is done
    FToken *next_token;

    // Dynamically-growing list of line indices
    // N.W. it's always non-empty because there is always
    // the first line
    size_t *line_to_index;
    size_t lines_size;
    size_t lines_capacity;

    char *error;
    int endmarker;
} FLexerState;

void FLexer_init_state(FLexerState *ls, char *src, size_t len, int endmarker);

void FLexer_add_index_for_line(FLexerState *ls, size_t i);

void FLexer_add_token(FLexerState *ls, FToken *token);

int FLexer_did_finish(FLexerState *ls, size_t pos);

void FLexer_set_error(FLexerState *ls, char *error_msg, size_t char_offset);

FToken *FLexer_create_token(FLexerState *ls, unsigned int type, int is_whitespace);

void FLexer_free_state(FLexerState *ls);

typedef FToken *(*FLexerFunc)(FLexerState *);

typedef struct ast_node_t FAstNode;

typedef struct parser_state_t {
    // Use to get lazily scan the next token
    FLexerState lexer_state;

    // Use to get the next token
    FLexerFunc lexer_func;

    // Allocate nodes in the same region so it can be freed all at once
    FMemRegion *region;

    size_t pos;
    size_t max_reached_pos;

    // Use for space-insensitive blocks (like between brackets)
    int ignore_whitespace;

    char *error;

    // Debugging
    size_t level;

} FParser;

#define PARSER_ALLOC(p, size) FMemRegion_malloc((p)->region, size)

#define RULE(name) FAstNode *name(FParser *p)

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

FParser *FPeg_init_new_parser(
        char *src,
        size_t len,
        FLexerFunc lexer_func
);

void FPeg_free_parser(FParser *p);

char *FPeg_check_state(FParser *p);

void FPeg_put_memo(FParser *p, size_t type, void *node, size_t end);

FTokenMemo *FPeg_get_memo(FParser *p, size_t type);

void FPeg_debug_enter(FParser *p, size_t rule_index, const char *rule_name);

void FPeg_debug_exit(FParser *p, FAstNode *res, size_t rule_index, const char *rule_name);

void FPeg_debug_memo(FParser *p, FTokenMemo *memo, size_t rule_index, const char *rule_name);

// Macros used in the parser

#define AST_CONSUME(p, type, value) FPeg_consume_token(p, type)
#define AST_NEW_NODE(p, t, nargs, ...) FAst_new_node(p, t, nargs, __VA_ARGS__)

FAstNode *FPeg_consume_token(FParser *p, size_t type);

FAstNode *FAst_new_node(FParser *p, size_t t, int nargs, ...);

typedef FAstNode *(*FRuleFunc)(FParser *);

#define SEQ_OR_NONE(p, rule) \
    FPeg_parse_sequece_or_none(p, rule)

#define SEQUENCE(p, rule) \
    FPeg_parse_sequence(p, rule)

#define DELIMITED(p, delimiter, literal, rule) \
    FPeg_parse_delimited(p, delimiter, rule)

#define TOKEN_SEQ_OR_NONE(p, t, v) \
    FPeg_parse_token_sequence_or_none(p, t)

#define TOKEN_SEQUENCE(p, t, v) \
    FPeg_parse_token_sequence(p, t)

#define TOKEN_DELIMITED(p, delimiter, literal, t, v) \
    FPeg_parse_token_delimited(p, delimiter, t)

FAstNode *FPeg_parse_sequece_or_none(FParser *p, FRuleFunc rule);

FAstNode *FPeg_parse_sequence(FParser *p, FRuleFunc rule);

FAstNode *FPeg_parse_delimited(FParser *p, size_t delimiter, FRuleFunc rule);

FAstNode *FPeg_parse_token_sequence(FParser *p, size_t token);

FAstNode *FPeg_parse_token_sequence_or_none(FParser *p, size_t token);

FAstNode *FPeg_parse_token_delimited(FParser *p, size_t delimiter, size_t token);

#endif //CPEG_PEG_H
