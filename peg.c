#include "include/peg.h"
#include "stdio.h"

void FLexer_init_state(FLexerState *ls, char *src, size_t len, int endmarker) {
    ls->src = src;
    ls->src_len = len;

    ls->curr_index = 0;
    ls->start_index = 0;

    ls->indent = 0;

    ls->tokens = NULL;
    ls->token_len = 0;
    ls->token_capacity = 0;

    ls->next_token = NULL;

    // always non-empty
    ls->line_to_index = FMem_malloc(sizeof(size_t));
    ls->line_to_index[0] = 0;
    ls->lines_size = 1;
    ls->lines_capacity = 1;

    ls->error = NULL;
    ls->endmarker = endmarker;
}

void FLexer_add_index_for_line(FLexerState *ls, size_t i) {
    if (ls->lines_size >= ls->lines_capacity) {
        ls->lines_capacity = ls->lines_capacity << 1u;
        ls->line_to_index = FMem_realloc(
                ls->line_to_index, ls->lines_capacity * sizeof(size_t));
    }
    ls->line_to_index[ls->lines_size] = i;
    ls->lines_size += 1;
}

void FLexer_add_token(FLexerState *ls, FToken *token) {
    if (ls->token_len >= ls->token_capacity) {
        if (!ls->token_capacity) {
            ls->token_capacity = 1;
            ls->token_len = 0;
            ls->tokens = FMem_malloc(sizeof(FToken *));
        } else {
            ls->token_capacity = ls->token_capacity << 1u;
            ls->tokens = FMem_realloc(ls->tokens, ls->token_capacity * sizeof(FToken *));
        }
    }
    ls->tokens[ls->token_len] = token;
    ls->token_len += 1;
}

void lexer_compute_next_token(FParser *p) {
    FLexerState *ls = &p->lexer_state;
    if (ls->curr_index < ls->src_len) {
        FLexerFunc lexer_func = p->lexer_func;
        ls->next_token = lexer_func(ls);
    } else {
        ls->next_token = NULL;
    }
}

FToken *lexer_fetch_token(FParser *p, size_t pos) {
    FLexerState *ls = &p->lexer_state;

    if (pos > ls->token_len) {
        p->error = "Token index too big";
        return NULL;
    }

    // scan the next unknown token
    if (pos == ls->token_len) {
        FToken *this_token = ls->next_token;

        if (this_token) {
            FLexer_add_token(ls, this_token);
            lexer_compute_next_token(p);

            return this_token;
        } else {
            // end of token stream
            return NULL;
        }
    }

    return ls->tokens[pos];
}

// * returns the line end (exclusive) given line number
size_t lexer_get_line_end(FLexerState *ls, size_t lineno) {
    if (lineno < ls->lines_size - 1) {
        return ls->line_to_index[lineno + 1];
    } else if (lineno == ls->lines_size - 1) {
        size_t i = ls->line_to_index[lineno] + 1;
        while (i < ls->src_len)
        {
            char ch = ls->src[i];
            if (ch == '\r' || ch == '\n') {
                break;
            }
            i++;
        }
        return i;
    } else {
        return ls->src_len;
    }
}

void FLexer_set_error(FLexerState *ls, char *error_msg, size_t char_offset) {
    size_t lineno = ls->lines_size - 1;
    size_t line_start = ls->line_to_index[lineno];
    size_t line_end = lexer_get_line_end(ls, lineno);
    size_t col = ls->curr_index - line_start + char_offset;

    // include an extra char for \0
    char *line_buf = FMem_calloc(line_end - line_start + 1, sizeof(char));
    int j = 0;
    for (size_t i = line_start; i < line_end; ++i) {
        line_buf[j] = ls->src[i];
        ++j;
    }

    char *caret_buf = FMem_calloc(col + 5, sizeof(char));
    for (size_t i = 0; i < col + 4; ++i) {
        caret_buf[i] = ' ';
    }
    
    size_t max_len = 45 + (line_end - line_start) + col + strlen(error_msg);
    char *err_buf = FMem_calloc(max_len, sizeof(char));
    
    sprintf(err_buf, "line %zu:\n    %s\n%s^\nError: %s", 
            lineno + 1, line_buf, caret_buf, error_msg);

    ls->error = err_buf;

    FMem_free(line_buf);
    FMem_free(caret_buf);
}

FToken *FLexer_create_token(FLexerState *ls, unsigned int type, int is_whitespace) {
    FToken *token = FMem_malloc(sizeof(FToken));
    if (!token) {
        return NULL;
    }

    size_t line_start = ls->lines_size - 1;
    size_t col_start = ls->start_index - ls->line_to_index[line_start];

    token->lineno = line_start;
    token->column = col_start;
    token->len = ls->curr_index - ls->start_index;
    token->start = ls->src + ls->start_index;
    token->type = type;
    token->is_whitespace = (int) is_whitespace;
    token->memo = NULL;

    return token;
}

void FLexer_free_state(FLexerState *ls) {
    for (int i = 0; i < ls->token_len; ++i) {
        FMem_free(ls->tokens[i]);
    }
    FMem_free(ls->tokens);
    FMem_free(ls->line_to_index);
    if (ls->error) {
        FMem_free(ls->error);
    }
}

FParser *FPeg_init_new_parser(
        char *src,
        size_t len,
        FLexerFunc lexer_func) {

    if (!src || !lexer_func) {
        return NULL;
    }

    FMemRegion *region = FMemRegion_new();
    if (!region) {
        return NULL;
    }

    FParser *p = FMem_malloc(sizeof(FParser));
    if (!p) {
        return NULL;
    }

    FLexer_init_state(&p->lexer_state, src, len, 1);

    p->lexer_func = lexer_func;
    p->region = region;
    p->pos = 0;
    p->max_reached_pos = 0;
    p->ignore_whitespace = 0;
    p->level = 0;
    p->error = 0;

    // Need to scan at least one token to see
    // if there is anything to parse
    lexer_compute_next_token(p);

    return p;
}

void FPeg_free_parser(FParser *p) {
    FLexer_free_state(&p->lexer_state);
    FMemRegion_free(p->region);
    FMem_free(p);
}

int FPeg_is_done(FParser *p) {
    if (p->error || p->lexer_state.error) {
        // Early exit the function when there is already an error
        return 1;
    }
    size_t pos = p->pos;

    FToken *curr_token = lexer_fetch_token(p, pos);
    if (!curr_token) {
        // there is no more tokens; no need to test anymore
        // this avoids the infinite recursion problem caused by
        // nonexistent token
        return 1;
    }

    if (pos > p->max_reached_pos) {
        p->max_reached_pos = pos;
    }

    return 0;
}

FToken *get_next_token_to_consume(FParser *p, size_t *ppos) {
    size_t pos = p->pos;
    FToken *curr_token = lexer_fetch_token(p, pos);
    if (!curr_token) {
        return NULL;
    }

    // the first token that doesn't ignore whitespace
    if (p->ignore_whitespace) {
        FLexerState *ls = &p->lexer_state;
        for(;;) {
            if (!curr_token->is_whitespace) {
                break;
            }
            if (pos + 1 >= ls->token_len && !ls->next_token) {
                break;
            }
            pos += 1;
            curr_token = lexer_fetch_token(p, pos);
            if (!curr_token) {
                return NULL;
            }
        }
    }
    
    *ppos = pos;
    return curr_token;
}

FTokenMemo *new_memo(FParser *p, size_t type, void *node, size_t end) {
    FTokenMemo *new_memo = PARSER_ALLOC(p, sizeof(FTokenMemo));
    if (!new_memo) {
        return NULL;
    }
    new_memo->type = type;
    new_memo->node = node;
    new_memo->end_pos = end;
    new_memo->next = NULL;
    return new_memo;
}

void FPeg_put_memo(FParser *p, size_t token_pos, size_t type, void *node, size_t endpos) {
    FToken *curr_token = lexer_fetch_token(p, token_pos);
    if (!curr_token) {
        return;
    }
    FTokenMemo *memo = curr_token->memo;
    if (!memo) {
        // create a "head" memo
        curr_token->memo = new_memo(p, type, node, endpos);
        return;
    }
    for(;;) {
        if (memo->type == type) {
            // Update an existing memo of a certain type
            memo->node = node;
            memo->end_pos = endpos;
            return;
        }
        if (!memo->next) {
            // Add a new memo to the end of the chain
            memo->next = new_memo(p, type, node, endpos);
            return;
        }
        memo = memo->next;
    }
}

FTokenMemo *FPeg_get_memo(FParser *p, size_t type) {
    FToken *curr_token = lexer_fetch_token(p, p->pos);
    if (!curr_token) {
        // should never reach here
        p->error = "Attempting to get memo without any more tokens";
        return NULL;
    }
    FTokenMemo *memo = curr_token->memo;
    while (memo) {
        if (memo->type == type) {
            if (memo->node) {
                // reset the parser's position to the memo
                // if it was previously successful
                p->pos = memo->end_pos;
            }
            return memo;
        }
        memo = memo->next;
    }
    return NULL;
}

void print_indent_level(size_t s) {
    if (s > 40) {
        s = s % 40u;
    }
    char *b = FMem_malloc(sizeof(char) * (s * 2 + 1));
    if (!b) {
        return;
    }
    for (size_t i = 0; i < s; ++i) {
        if (i && i % 2 == 0) {
            b[i * 2] = '|';
        } else {
            b[i * 2] = ' ';
        }
        b[i * 2 + 1] = ' ';
    }
    b[s * 2] = '\0';
    printf("%s", b);
    FMem_free(b);
}

void FPeg_debug_enter(FParser *p, size_t rule_index, const char *rule_name) {
    print_indent_level(p->level);

    // fetch_token needed over direct access
    FToken *curr_token = lexer_fetch_token(p, p->pos);

    char *token_buf;
    if (!curr_token) {
        token_buf = "(null)";
    } else {
        token_buf = FMem_calloc(curr_token->len + 1, sizeof(char));
        for (size_t i = 0; i < curr_token->len; ++i) {
            token_buf[i] = curr_token->start[i];
        }
    }

    printf("Checking   \033[36m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[36m t='%s'\033[0m)\n",
            rule_name, p->level, p->pos, token_buf);

    if (curr_token) {
        FMem_free(token_buf);
    }

    p->level++;
}

void FPeg_debug_exit(FParser *p, void *res, size_t rule_index, const char *rule_name) {
    if (p->level == 0) {
        p->error = "Negative recursion depth; aborted";
        return;
    }
    p->level--;
    print_indent_level(p->level);
    if (res) {
        printf("Success in \033[32m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[0m)\n", rule_name, p->level, p->pos);
    } else {
        printf("Failure in \033[31m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[0m)\n", rule_name, p->level, p->pos);
    }
}

void FPeg_debug_memo(FParser *p, FTokenMemo *memo, size_t rule_index, const char *rule_name) {
    if (!memo) {
        return;
    };
    p->level--;
    print_indent_level(p->level);
    char *succ;
    if (memo->node) {
        succ = "was a \033[32mSuccess\033[0m";
    } else {
        succ = "was a \033[31mFailure\033[0m";
    }
    printf("Memoized   \033[35m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[0m, %s)\n", 
            rule_name, p->level, p->pos, succ);
}