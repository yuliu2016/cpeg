#include "include/peg.h"
#include "stdio.h"

void lexer_init_state(lexer_t *ls, char *src, size_t len, int endmarker) {
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

void lexer_add_line_index(lexer_t *ls, size_t i) {
    if (ls->lines_size >= ls->lines_capacity) {
        ls->lines_capacity = ls->lines_capacity << 1u;
        ls->line_to_index = FMem_realloc(
                ls->line_to_index, ls->lines_capacity * sizeof(size_t));
    }
    ls->line_to_index[ls->lines_size] = i;
    ls->lines_size += 1;
}

void lexer_append_token(lexer_t *ls, token_t *token) {
    if (ls->token_len >= ls->token_capacity) {
        if (!ls->token_capacity) {
            ls->token_capacity = 1;
            ls->token_len = 0;
            ls->tokens = FMem_malloc(sizeof(token_t *));
        } else {
            ls->token_capacity = ls->token_capacity << 1u;
            ls->tokens = FMem_realloc(ls->tokens, ls->token_capacity * sizeof(token_t *));
        }
    }
    ls->tokens[ls->token_len] = token;
    ls->token_len += 1;
}

static void _compute_next_token(parser_t *p) {
    lexer_t *ls = &p->lexer_state;
    if (ls->curr_index < ls->src_len) {
        lexer_func_t lexer_func = p->lexer_func;
        ls->next_token = lexer_func(ls);
    } else {
        ls->next_token = NULL;
    }
}

static token_t *_fetch_token(parser_t *p, size_t pos) {
    lexer_t *ls = &p->lexer_state;

    if (pos > ls->token_len) {
        p->error = "Token index too big";
        return NULL;
    }

    // scan the next unknown token
    if (pos == ls->token_len) {
        token_t *this_token = ls->next_token;

        if (this_token) {
            lexer_append_token(ls, this_token);
            _compute_next_token(p);

            return this_token;
        } else {
            // end of token stream
            return NULL;
        }
    }

    return ls->tokens[pos];
}


static size_t _find_eol_index(lexer_t *ls, size_t lineno) {
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

void lexer_set_error(lexer_t *ls, char *error_msg, size_t char_offset) {
    size_t lineno = ls->lines_size - 1;
    size_t line_start = ls->line_to_index[lineno];
    size_t line_end = _find_eol_index(ls, lineno);
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

token_t *lexer_create_token(lexer_t *ls, int tk_type, int is_whitespace) {
    token_t *token = FMem_malloc(sizeof(token_t));
    if (!token) {
        return NULL;
    }

    size_t line_start = ls->lines_size - 1;
    size_t col_start = ls->start_index - ls->line_to_index[line_start];

    token->lineno = line_start;
    token->column = col_start;
    token->len = ls->curr_index - ls->start_index;
    token->start = ls->src + ls->start_index;
    token->tk_type = tk_type;
    token->is_whitespace = (int) is_whitespace;
    token->memo = NULL;

    return token;
}

void lexer_free_state(lexer_t *ls) {
    for (int i = 0; i < ls->token_len; ++i) {
        FMem_free(ls->tokens[i]);
    }
    FMem_free(ls->tokens);
    FMem_free(ls->line_to_index);
    if (ls->error) {
        FMem_free(ls->error);
    }
}

parser_t *FPeg_init_new_parser(
        char *src,
        size_t len,
        lexer_func_t lexer_func) {

    if (!src || !lexer_func) {
        return NULL;
    }

    FMemRegion *region = FMemRegion_new();
    if (!region) {
        return NULL;
    }

    parser_t *p = FMem_malloc(sizeof(parser_t));
    if (!p) {
        return NULL;
    }

    lexer_init_state(&p->lexer_state, src, len, 1);

    p->lexer_func = lexer_func;
    p->region = region;
    p->pos = 0;
    p->max_reached_pos = 0;
    p->ignore_whitespace = 0;
    p->level = 0;
    p->error = 0;

    // Need to scan at least one token to see
    // if there is anything to parse
    _compute_next_token(p);

    return p;
}

void FPeg_free_parser(parser_t *p) {
    lexer_free_state(&p->lexer_state);
    FMemRegion_free(p->region);
    FMem_free(p);
}

int FPeg_is_done(parser_t *p) {
    if (p->error || p->lexer_state.error) {
        // Early exit the function when there is already an error
        return 1;
    }
    size_t pos = p->pos;

    token_t *curr_token = _fetch_token(p, pos);
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

token_t *get_next_token_to_consume(parser_t *p, size_t *ppos) {
    size_t pos = p->pos;
    token_t *curr_token = _fetch_token(p, pos);
    if (!curr_token) {
        return NULL;
    }

    // the first token that doesn't ignore whitespace
    if (p->ignore_whitespace) {
        lexer_t *ls = &p->lexer_state;
        for(;;) {
            if (!curr_token->is_whitespace) {
                break;
            }
            if (pos + 1 >= ls->token_len && !ls->next_token) {
                break;
            }
            pos += 1;
            curr_token = _fetch_token(p, pos);
            if (!curr_token) {
                return NULL;
            }
        }
    }
    
    *ppos = pos;
    return curr_token;
}

token_memo_t *new_memo(parser_t *p, int f_type, void *node, size_t end) {
    token_memo_t *new_memo = PARSER_ALLOC(p, sizeof(token_memo_t));
    if (!new_memo) {
        return NULL;
    }
    new_memo->f_type = f_type;
    new_memo->node = node;
    new_memo->end_pos = end;
    new_memo->next = NULL;
    return new_memo;
}

void FPeg_put_memo(parser_t *p, size_t token_pos, int f_type, void *node, size_t endpos) {
    token_t *curr_token = _fetch_token(p, token_pos);
    if (!curr_token) {
        return;
    }
    token_memo_t *memo = curr_token->memo;
    if (!memo) {
        // create a "head" memo
        curr_token->memo = new_memo(p, f_type, node, endpos);
        return;
    }
    for(;;) {
        if (memo->f_type == f_type) {
            // Update an existing memo of a certain type
            memo->node = node;
            memo->end_pos = endpos;
            return;
        }
        if (!memo->next) {
            // Add a new memo to the end of the chain
            memo->next = new_memo(p, f_type, node, endpos);
            return;
        }
        memo = memo->next;
    }
}

token_memo_t *FPeg_get_memo(parser_t *p, int f_type) {
    token_t *curr_token = _fetch_token(p, p->pos);
    if (!curr_token) {
        // should never reach here
        p->error = "Attempting to get memo without any more tokens";
        return NULL;
    }
    token_memo_t *memo = curr_token->memo;
    while (memo) {
        if (memo->f_type == f_type) {
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

token_t *FPeg_consume_token(parser_t *p, int tk_type) {
    size_t pos = p->pos;

    token_t *curr_token = get_next_token_to_consume(p, &pos);
    if (!curr_token) {
        return NULL;
    }

    // now check for correct type
    if (curr_token->tk_type == tk_type) {
        p->pos = pos + 1;
        return curr_token;
    } else {
        return NULL;
    }
}

token_t *FPeg_consume_token_and_debug(parser_t *p, int tk_type, const char *literal) {
    size_t pos = p->pos;

    print_indent_level(p->level);
    token_t *curr_token = get_next_token_to_consume(p, &pos);
    if (!curr_token) {
        printf("Mismatch   \033[31;1m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu, \033[31mno more tokens\033[0m)\n",
                literal, p->level, p->pos);
        return NULL;
    }

    // now check for correct type
    if (curr_token->tk_type == tk_type) {
        p->pos = pos + 1;
        printf("Matched    \033[32;1m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[0m)\n",
                literal, p->level, p->pos);
        return curr_token;
    } else {
        char *token_buf;

        token_buf = FMem_calloc(curr_token->len + 1, sizeof(char));
        for (size_t i = 0; i < curr_token->len; ++i) {
            token_buf[i] = curr_token->start[i];
        }

        printf("Mismatch   \033[31;1m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu, \033[31mt='%s'\033[0m)\n",
                literal, p->level, p->pos, token_buf);
        FMem_free(token_buf);
        return NULL;
    }
}


void FPeg_debug_enter(parser_t *p, frame_t *f) {
    print_indent_level(p->level);

    // fetch_token needed over direct access
    token_t *curr_token = _fetch_token(p, p->pos);

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
            f->f_rule, p->level, p->pos, token_buf);

    if (curr_token) {
        FMem_free(token_buf);
    }

    p->level++;
}

void FPeg_debug_exit(parser_t *p, void *res, frame_t *f) {
    if (p->level == 0) {
        p->error = "Negative recursion depth; aborted";
        return;
    }
    p->level--;
    print_indent_level(p->level);
    if (res) {
        printf("Success in \033[32m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[0m)\n", f->f_rule, p->level, p->pos);
    } else {
        printf("Failure in \033[31m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[0m)\n", f->f_rule, p->level, p->pos);
    }
}

void FPeg_debug_memo(parser_t *p, token_memo_t *memo, frame_t *f) {
    if (!memo) {
        return;
    };
    print_indent_level(p->level);
    char *succ;
    if (memo->node) {
        succ = "was a \033[32mSuccess\033[0m";
    } else {
        succ = "was a \033[31mFailure\033[0m";
    }
    printf("Memoized   \033[35m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[0m, %s)\n", 
            f->f_rule, p->level, p->pos, succ);
}