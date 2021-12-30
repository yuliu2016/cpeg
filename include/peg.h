
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
    size_t type;
    void *node;
    size_t end_pos;
    struct token_memo_t *next;
} FTokenMemo;

typedef struct token {
    size_t type;
    char *start;
    size_t len;
    size_t lineno;
    size_t column;
    int is_whitespace;
    FTokenMemo *memo;
} token_t;

typedef token_t FToken;

// Lazily-evaluated tokenizer
typedef struct lexer_state {
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
    token_t **tokens;
    size_t token_len;
    size_t token_capacity;

    // Stores next token to determine if stream is done
    token_t *next_token;

    // Dynamically-growing list of line indices
    // N.W. it's always non-empty because there is always
    // the first line
    size_t *line_to_index;
    size_t lines_size;
    size_t lines_capacity;

    char *error;
    int endmarker;
} lexer_t;

typedef lexer_t FLexerState;

void lexer_init_state(lexer_t *ls, char *src, size_t len, int endmarker);

void lexer_add_line_index(lexer_t *ls, size_t i);

void lexer_append_token(lexer_t *ls, token_t *token);

void lexer_set_error(lexer_t *ls, char *error_msg, size_t char_offset);

token_t *lexer_create_token(lexer_t *ls, unsigned int type, int is_whitespace);

void lexer_free_state(lexer_t *ls);

typedef token_t *(*FLexerFunc)(lexer_t *);


typedef struct parser_state {
    // Use to get lazily scan the next token
    lexer_t lexer_state;

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

} parser_t;

#define PARSER_ALLOC(p, size) FMemRegion_malloc((p)->region, size)


parser_t *FPeg_init_new_parser(char *src, size_t len, FLexerFunc lexer_func);

void FPeg_free_parser(parser_t *p);

int FPeg_is_done(parser_t *p);

FToken *FPeg_consume_token(parser_t *p, size_t type);

FToken *FPeg_consume_token_and_debug(parser_t *p, size_t type, const char *literal);

void FPeg_put_memo(parser_t *p, size_t token_pos, size_t type, void *node, size_t endpos);

FTokenMemo *FPeg_get_memo(parser_t *p, size_t type);

void FPeg_debug_enter(parser_t *p, size_t rule_index, const char *rule_name);

void FPeg_debug_exit(parser_t *p, void *res, size_t rule_index, const char *rule_name);

void FPeg_debug_memo(parser_t *p, FTokenMemo *memo, size_t rule_index, const char *rule_name);


#endif //CPEG_PEG_H
