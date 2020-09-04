#include "include/peg.h"

void lexer_add_line_index(FLexerState *ls, size_t i) {
    if (ls->lines_size >= ls->lines_capacity) {
        if (!ls->lines_capacity) {
            ls->lines_capacity = 1;
            ls->lines_size = 0;
            ls->line_to_index = FMem_malloc(sizeof(size_t));
        } else {
            ls->lines_capacity = ls->lines_capacity << 1u;
            ls->line_to_index = FMem_realloc(
                    ls->line_to_index, ls->lines_capacity * sizeof(size_t));
        }
    }
    ls->line_to_index[ls->lines_size] = i;
    ls->lines_size += 1;
}

FToken *tokenizer_new_token(
        FLexerState *ls,
        unsigned int type,
        size_t beginIndex,
        size_t endIndex,
        int is_whitespace) {

    // token being empty means that it would equal to last_end_index
    if (beginIndex >= endIndex || endIndex > ls->src_len) {
        ls->error = "new token - Out of bounds";
        return NULL;
    }

    FToken *token = FMem_malloc(sizeof(FToken));
    if (!token) {
        return NULL;
    }

    size_t line_start = ls->lines_size - 1;
    size_t col_start = beginIndex - ls->line_to_index[line_start];

    for (size_t i = ls->last_end_index; i < endIndex; i++) {

        char ch1 = ls->src[i];
        char ch2;
        if (i < ls->src_len - 1) {
            ch2 = ls->src[i + 1];
        } else {
            ch2 = 0;
        }
        if (ch1 == '\r' && ch2 == '\n') {
            i++;
            lexer_add_line_index(ls, i + 2);
        } else if (ch1 == '\n') {
            lexer_add_line_index(ls, i + 1);
        }
    }

    token->lineno = line_start;
    token->column = col_start;
    token->len = endIndex - beginIndex;
    token->start = ls->src + beginIndex;

    token->type = type;
    token->is_whitespace = is_whitespace;

    return token;
}