#include "include/peg.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"



static char *_ntv_src;
static size_t _ntv_index;
static char _ntv_char;

char *token_nullterm_view(token_t *token) {
    _ntv_src = token->start;
    _ntv_index = token->len;
    _ntv_char = _ntv_src[_ntv_index];
    _ntv_src[_ntv_index] = 0;
    return _ntv_src;
}

void token_nullterm_restore() {
    _ntv_src[_ntv_index] = _ntv_char;
}

char *token_heap_copy(token_t *token) {
    char *dest;
    if (!token) {
        dest = malloc(7 * sizeof(char));
        strcpy(dest, "(null)");
        return dest;
    } else {
        char *view = token_nullterm_view(token);
        dest = malloc((strlen(view) + 1) * sizeof(char));
        strcpy(dest, view);
        token_nullterm_restore();
        return dest;
    }
}



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
    ls->line_to_index = malloc(sizeof(size_t));
    ls->line_to_index[0] = 0;
    ls->lines_size = 1;
    ls->lines_capacity = 1;

    ls->error = NULL;
    ls->endmarker = endmarker;
}

void lexer_add_line_index(lexer_t *ls, size_t i) {
    if (ls->lines_size >= ls->lines_capacity) {
        ls->lines_capacity = ls->lines_capacity << 1u;
        ls->line_to_index = realloc(
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
            ls->tokens = malloc(sizeof(token_t *));
        } else {
            ls->token_capacity = ls->token_capacity << 1u;
            ls->tokens = realloc(ls->tokens, ls->token_capacity * sizeof(token_t *));
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

token_t *parser_fetch_token(parser_t *p, size_t pos) {
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

            ls->next_token = NULL;
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
    char *line_buf = calloc(line_end - line_start + 1, sizeof(char));
    int j = 0;
    for (size_t i = line_start; i < line_end; ++i) {
        line_buf[j] = ls->src[i];
        ++j;
    }

    char *caret_buf = calloc(col + 5, sizeof(char));
    for (size_t i = 0; i < col + 4; ++i) {
        caret_buf[i] = ' ';
    }
    
    size_t max_len = 45 + (line_end - line_start) + col + strlen(error_msg);
    char *err_buf = calloc(max_len, sizeof(char));
    
    sprintf(err_buf, "line %zu:\n    %s\n%s^\nError: %s", 
            lineno + 1, line_buf, caret_buf, error_msg);

    ls->error = err_buf;

    free(line_buf);
    free(caret_buf);
}

token_t *lexer_create_token(lexer_t *ls, int tk_type) {
    token_t *token = malloc(sizeof(token_t));
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
    token->memo = NULL;

    return token;
}

void lexer_free_state(lexer_t *ls) {
    for (int i = 0; i < ls->token_len; ++i) {
        free(ls->tokens[i]);
    }
    free(ls->tokens);
    free(ls->line_to_index);
    if (ls->error) {
        free(ls->error);
    }
}

parser_t *parser_init_state(
        char *src,
        size_t len,
        lexer_func_t lexer_func) {

    if (!src || !lexer_func) {
        return NULL;
    }

    FMemRegion *region = mbregion(REGION_DEFAULT_SIZE);
    if (!region) {
        return NULL;
    }

    parser_t *p = malloc(sizeof(parser_t));
    if (!p) {
        return NULL;
    }

    lexer_init_state(&p->lexer_state, src, len, 1);

    p->lexer_func = lexer_func;
    p->region = region;
    p->pos = 0;
    p->max_reached_pos = 0;
    p->level = 0;
    p->error = 0;

    // Need to scan at least one token to see
    // if there is anything to parse
    _compute_next_token(p);

    return p;
}

void parser_free_state(parser_t *p) {
    lexer_free_state(&p->lexer_state);
    mbpurge(p->region);
    free(p);
}

int parser_advance_frame(parser_t *p) {
    if (p->error || p->lexer_state.error) {
        // Early exit the function when there is already an error
        return 0;
    }

    // Increase recursion depth
    p->level += 1;

    if (p->level > PARSER_MAX_RECURSION) {
        // Do not allow trees that are too deep.
        p->error = "Max recursion depth reached";
        return 0;
    }

    if (!parser_fetch_token(p, p->pos)) {
        // there is no more tokens; no need to test anymore
        // this avoids the infinite recursion problem caused by
        // nonexistent token
        return 0;
    }

    return 1;
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

void parser_memoize(parser_t *p, size_t token_pos, int f_type, void *node) {
    size_t endpos = p->pos;
    token_t *curr_token = parser_fetch_token(p, token_pos);
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

token_memo_t *parser_get_memo(parser_t *p, int f_type) {
    token_t *curr_token = parser_fetch_token(p, p->pos);
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


token_t *parser_consume_token(parser_t *p, int tk_type) {

    token_t *curr_token = parser_fetch_token(p, p->pos);
    if (!curr_token) {
        return NULL;
    }

    // now check for correct type
    if (curr_token->tk_type == tk_type) {
        p->pos += 1;
        return curr_token;
    } else {
        return NULL;
    }
}


ast_list_t *ast_list_new(parser_t *p) {
    ast_list_t *seq = PARSER_ALLOC(p, sizeof(ast_list_t));
    if (!seq) {
        return NULL;
    }
    seq->capacity = 0;
    seq->len = 0;
    seq->items = NULL;
    return seq;
}


void ast_list_append(parser_t *p, ast_list_t *seq, void *item) {
    if (seq->len >= seq->capacity) {
        if (!seq->capacity) {
            seq->capacity = 1;
            seq->len = 0;
            seq->items = PARSER_ALLOC(p, sizeof(void *));
        } else {
            seq->capacity = seq->capacity << 1u;
            // Since realloc isn't available with memory regions,
            // the nodes needs to be copied in a loop
            void **old_items = seq->items;
            seq->items = PARSER_ALLOC(p, seq->capacity * sizeof(void *));
            for (int i = 0; i < seq->len; ++i) {
                seq->items[i] = old_items[i];
            }
        }
    }
    seq->items[seq->len++] = item;
}