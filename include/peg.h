
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
typedef struct memo {
    int f_type;
    void *node;
    size_t end_pos;
    struct memo *next;
} memo_t;

typedef struct token {
    int tk_type;
    char *start;
    size_t len;
    int lineno;
    int column;
} token_t;

// Token helpers

char *token_nullterm_view(token_t *token);

void token_nullterm_restore();

char *token_heap_copy(token_t *token);


// Lazily-evaluated tokenizer
typedef struct lexer_state {
    // Test source
    char *src;
    size_t src_len;

    // Index of the visitor
    size_t curr_index;

    // Index of the start of the token;
    size_t start_index;

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
} lexer_t;


void lexer_init_state(lexer_t *ls, char *src, size_t len);

void lexer_add_line_index(lexer_t *ls, size_t i);

void lexer_append_token(lexer_t *ls, token_t *token);

void lexer_set_error(lexer_t *ls, char *error_msg, size_t char_offset);

token_t *lexer_create_token(lexer_t *ls, int tk_type);

void lexer_free_state(lexer_t *ls);

typedef void (*lexer_func_t)(lexer_t *);


typedef struct parser_state {
    // Current parser position
    size_t pos;

    // 0 if okay, otherwise an error has occured
    int errorcode;

    // Check if token matches without fetching the token itself
    // Same size & capacity as .lexer_state.tokens
    int *fast_match;

    // Cache the results (enables packrat parsing)
    // Same size & capacity as .lexer_state.tokens
    memo_t **memoized_cache;

    // Allocate nodes in the same region so it can be freed all at once
    mem_region_t *region;

    // Use to get lazily scan the next token
    lexer_t lexer_state;
    lexer_func_t lexer_read_token;

    // Debugging variables
    void *error_object;
    char **tk_indices;
    char *tk_max_attempted;
    size_t level;

} parser_t;


void parser_init_state(parser_t *p, char *src, size_t len, 
        lexer_func_t lexer_next_token, char **tk_indices);

token_t *parser_fetch_token(parser_t *p, size_t pos);

void parser_free_state(parser_t *p);

int parser_advance_frame(parser_t *p);

void parser_memoize(parser_t *p, size_t token_pos, int f_type, void *node);

memo_t *parser_get_memo(parser_t *p, int f_type);

void parser_verify_eof(parser_t *p);

void parser_set_error(parser_t *p, int code, void *object);


// Parser debugging tools

void parser_matched_debug(parser_t *p, const char *literal);

void parser_mismatch_debug(parser_t *p, const char *literal);

void parser_enter_debug(parser_t *p, const char *f_rule);

void parser_exit_debug(parser_t *p, void *res, const char *f_rule);

void parser_memo_debug(parser_t *p, memo_t *memo, const char *f_rule);


// List data structure
typedef mblist_t ast_list_t;


#define PARSER_MAX_RECURSION 500

#ifndef PARSER_NODEBUG
// #define PARSER_DEBUG
#endif

#define FUNC __func__


#endif //CPEG_PEG_H
