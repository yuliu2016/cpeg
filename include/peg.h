
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
    token_memo_t *memo;
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

typedef token_t *(*lexer_func_t)(lexer_t *);


typedef struct parser_state {
    // Use to get lazily scan the next token
    lexer_t lexer_state;

    // Use to get the next token
    lexer_func_t lexer_func;

    // Allocate nodes in the same region so it can be freed all at once
    mem_region_t *region;

    size_t pos;

    // Debugging
    size_t max_reached_pos;
    char **tk_indices;
    char *tk_max_attempted;
    char *error;
    size_t level;

} parser_t;

typedef struct frame {
    const int f_type;
    const size_t f_pos;
    const char *f_rule;
} frame_t;


void parser_init_state(parser_t *p, char *src, size_t len, 
        lexer_func_t lexer_func, char **tk_indices);

token_t *parser_fetch_token(parser_t *p, size_t pos);

void parser_free_state(parser_t *p);

int parser_advance_frame(parser_t *p);

token_t *parser_consume_token(parser_t *p, int tk_type);

void parser_memoize(parser_t *p, size_t token_pos, int f_type, void *node);

token_memo_t *parser_get_memo(parser_t *p, int f_type);

void parser_verify_eof(parser_t *p);

static inline void *parser_alloc(parser_t *p, size_t size) {
    return mballoc(p->region, size);
}


// Parser debugging tools

token_t *parser_consume_debug(parser_t *p, int tk_type, const char *literal);

void parser_enter_debug(parser_t *p, const frame_t *f);

void parser_exit_debug(parser_t *p, void *res, const frame_t *f);

void parser_memo_debug(parser_t *p, token_memo_t *memo, const frame_t *f);


// List data structure
typedef mblist_t ast_list_t;


#define PARSER_MAX_RECURSION 500

#ifndef PARSER_NODEBUG
// #define PARSER_DEBUG
#endif

#define FUNC __func__


#endif //CPEG_PEG_H
