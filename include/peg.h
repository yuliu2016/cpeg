
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

void FLexer_set_error(FLexerState *ls, char *error_msg, size_t char_offset);

FToken *FLexer_create_token(FLexerState *ls, unsigned int type, int is_whitespace);

void FLexer_free_state(FLexerState *ls);

typedef FToken *(*FLexerFunc)(FLexerState *);


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


FParser *FPeg_init_new_parser(
        char *src,
        size_t len,
        FLexerFunc lexer_func
);

void FPeg_free_parser(FParser *p);

int FPeg_is_done(FParser *p);

void FPeg_put_memo(FParser *p, size_t token_pos, size_t type, void *node, size_t endpos);

FTokenMemo *FPeg_get_memo(FParser *p, size_t type);

void FPeg_debug_enter(FParser *p, size_t rule_index, const char *rule_name);

void FPeg_debug_exit(FParser *p, void *res, size_t rule_index, const char *rule_name);

void FPeg_debug_memo(FParser *p, FTokenMemo *memo, size_t rule_index, const char *rule_name);


typedef void *(*FRuleFunc)(FParser *);

FToken *get_next_token_to_consume(FParser *p, size_t *ppos); // todo remove private function

void *parse_grammar(FParser *p, int entry_point); // todo where should this go?

void *parse_calc(FParser *p);

#endif //CPEG_PEG_H
