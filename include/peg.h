
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
typedef struct token_memo {
    int f_type;
    void *node;
    size_t end_pos;
    struct token_memo *next;
} token_memo_t;

typedef struct token {
    int tk_type;
    char *start;
    size_t len;
    int lineno;
    int column;
    int is_whitespace;
    token_memo_t *memo;
} token_t;


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


void lexer_init_state(lexer_t *ls, char *src, size_t len, int endmarker);

void lexer_add_line_index(lexer_t *ls, size_t i);

void lexer_append_token(lexer_t *ls, token_t *token);

void lexer_set_error(lexer_t *ls, char *error_msg, size_t char_offset);

token_t *lexer_create_token(lexer_t *ls, int tk_type, int is_whitespace);

void lexer_free_state(lexer_t *ls);

typedef token_t *(*lexer_func_t)(lexer_t *);


typedef struct parser_state {
    // Use to get lazily scan the next token
    lexer_t lexer_state;

    // Use to get the next token
    lexer_func_t lexer_func;

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

typedef struct frame {
    int f_type;
    size_t f_pos;
    const char *f_rule;
    void *memo;
    int memoize;
} frame_t;


parser_t *FPeg_init_new_parser(char *src, size_t len, lexer_func_t lexer_func);

void FPeg_free_parser(parser_t *p);

int FPeg_is_done(parser_t *p);

token_t *FPeg_consume_token(parser_t *p, int tk_type);

token_t *FPeg_consume_token_and_debug(parser_t *p, int tk_type, const char *literal);

void FPeg_put_memo(parser_t *p, size_t token_pos, int f_type, void *node, size_t endpos);

token_memo_t *FPeg_get_memo(parser_t *p, int f_type);

void FPeg_debug_enter(parser_t *p, frame_t *f);

void FPeg_debug_exit(parser_t *p, void *res, frame_t *f);

void FPeg_debug_memo(parser_t *p, token_memo_t *memo, frame_t *f);


#endif //CPEG_PEG_H
