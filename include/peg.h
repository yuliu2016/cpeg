
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
    const int f_type;
    const size_t f_pos;
    const char *f_rule;
    token_memo_t *f_memo;
    const int f_memoize;
} frame_t;


parser_t *parser_init_state(char *src, size_t len, lexer_func_t lexer_func);

void parser_free_state(parser_t *p);

int parser_advance_frame(parser_t *p);

token_t *parser_consume_token(parser_t *p, int tk_type);

token_t *parser_consume_debug(parser_t *p, int tk_type, const char *literal);

void parser_memoize(parser_t *p, size_t token_pos, int f_type, void *node, size_t endpos);

token_memo_t *parser_get_memo(parser_t *p, int f_type);

void parser_enter_debug(parser_t *p, frame_t *f);

void parser_exit_debug(parser_t *p, void *res, frame_t *f);

void parser_memo_debug(parser_t *p, token_memo_t *memo, frame_t *f);



typedef struct ast_list {
    size_t len;
    size_t capacity;
    void **items;
} ast_list_t;

ast_list_t *ast_list_new(parser_t *p);

void ast_list_append(parser_t *p, ast_list_t *seq, void *item);


#define PARSER_MAX_RECURSION 500

#ifndef PARSER_NODEBUG
#define PARSER_DEBUG
#endif


#define FUNC __func__


static inline int enter_frame(parser_t *p, frame_t *f) {

    if (f->f_memoize) {
        token_memo_t *memo = parser_get_memo(p, f->f_type);

        #ifdef PARSER_DEBUG
            parser_memo_debug(p, memo, f);
        #endif

        if (memo) {
            f->f_memo = memo;
            // return zero because the frame can be skipped
            return 0;
        }
    }

    #ifdef PARSER_DEBUG
        parser_enter_debug(p, f);
    #endif

    // increment recursion depth
    p->level += 1;

    if (parser_advance_frame(p)) {
        // continue with parsing the frame
        return 1;
    } else {
        // the parser is finished or there is an error
        return 0;
    }
}


static inline void *exit_frame(parser_t *p, frame_t *f, void *result) {

    if (f->f_memoize) {
        if (f->f_memo) {
            // Return the previously memoized result
            if (f->f_memo->node) {
                // Reset the parser position to the memo result
                p->pos = f->f_memo->end_pos;
            }
            return f->f_memo->node;
        } else {
            // Memoize the current result
            parser_memoize(p, f->f_pos, f->f_type, result, p->pos);
        }
    }

    #ifdef PARSER_DEBUG
        if (p->level == 0) {
            p->error = "Negative recursion depth reached";
            return 0;
        }
    #endif

    p->level -= 1;

    #ifdef PARSER_DEBUG
        parser_exit_debug(p, result, f);
    #endif


    if (!result) { 
        // Frame did not parse successfully; reset position.
        p->pos = f->f_pos;
    }
    return result;
}

static inline void memoize(parser_t *p, frame_t *f, void *node, size_t endpos) {
    parser_memoize(p, f->f_pos, f->f_type, node, endpos);
}

static inline int test_and_reset(parser_t *p, frame_t *f, void *node) {
    return node && (p->pos = f->f_pos, 1);
}


static inline token_t *consume(parser_t *p, int tk_type, const char *literal) {
    #ifdef PARSER_DEBUG
        return parser_consume_debug(p, tk_type, literal);
    #else
        return parser_consume_token(p, tk_type);
    #endif
}

#endif //CPEG_PEG_H
