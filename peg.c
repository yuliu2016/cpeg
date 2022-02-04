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

#define TK_CAPACITY 32

void lexer_init_state(lexer_t *ls, char *src, size_t len) {
    ls->src = src;
    ls->src_len = len;

    ls->curr_index = 0;
    ls->start_index = 0;

    if (!(ls->tokens = malloc(
            TK_CAPACITY * sizeof(token_t *)))) return;
    ls->token_len = 0;
    ls->token_capacity = TK_CAPACITY;

    ls->next_token = NULL;

    // always non-empty
    if (!(ls->line_to_index = malloc(sizeof(size_t)))) return;
    ls->line_to_index[0] = 0;
    ls->lines_size = 1;
    ls->lines_capacity = 1;

    ls->error = NULL;;
}

void lexer_add_line_index(lexer_t *ls, size_t i) {
    if (ls->lines_size >= ls->lines_capacity) {
        ls->lines_capacity = ls->lines_capacity << 1;
        ls->line_to_index = realloc(
                ls->line_to_index, ls->lines_capacity * sizeof(size_t));
    }
    ls->line_to_index[ls->lines_size] = i;
    ls->lines_size += 1;
}

void lexer_append_token(lexer_t *ls, token_t *token) {
    if (ls->token_len >= ls->token_capacity) {
        ls->token_capacity = ls->token_capacity << 1;
        ls->tokens = realloc(ls->tokens, ls->token_capacity * sizeof(token_t *));
    }
    ls->tokens[ls->token_len] = token;
    ls->token_len += 1;
}


static void parser_append_token(parser_t *p) {
    lexer_t *ls = &p->lexer_state;
    if (ls->token_len >= ls->token_capacity) {
        size_t cap = ls->token_capacity << 1;
        p->fast_match = realloc(p->fast_match,
                cap * sizeof(int));
        p->memoized_cache = realloc(p->memoized_cache,
                cap * sizeof(memo_t *));
    }
    token_t *token = ls->next_token;
    p->fast_match[ls->token_len] = token->tk_type;
    p->memoized_cache[ls->token_len] = NULL;
    lexer_append_token(ls, token);

}

token_t *parser_fetch_token(parser_t *p, size_t pos) {
    lexer_t *ls = &p->lexer_state;

    if (pos == ls->token_len - 1) {
        p->lexer_read_token(ls);
        if (ls->next_token) {
            parser_append_token(p);
        } else if (ls->error) {
            parser_set_error(p, 1, ls->error);
            // prevent freeing pointer twice
            ls->error = NULL;
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

void parser_init_state(
        parser_t *p, 
        char *src,
        size_t len,
        lexer_func_t lexer_read_token,
        char **tk_indices) {

    if (!src || !lexer_read_token) {
        return;
    }

    mem_region_t *region = mbregion(REGION_DEFAULT_SIZE, REGION_DEFAULT_SIZE);
    if (!region) {
        return;
    }

    lexer_t *ls = &p->lexer_state;
    lexer_init_state(ls, src, len);

    p->lexer_read_token = lexer_read_token;
    p->region = region;
    p->pos = 0;
    p->level = 0;
    p->error_object = 0;
    p->tk_indices = tk_indices;
    p->errorcode = 0;

    
    if (!(p->fast_match = calloc(
        TK_CAPACITY, sizeof(int)))) return;
    if (!(p->memoized_cache = calloc(
        TK_CAPACITY, sizeof(memo_t *)))) return;    

    // Need to scan at least one token to see
    // if there is anything to parse
    p->lexer_read_token(ls);
    if (ls->next_token) {
        ls->tokens[0] = ls->next_token;
        ls->token_len = 1;
        p->fast_match[0] = ls->next_token->tk_type;
    }
}

void parser_free_state(parser_t *p) {
    lexer_free_state(&p->lexer_state);
    if (p->errorcode == 1) {
        free(p->error_object);
    }
    mbpurge(p->region);
}


memo_t *new_memo(parser_t *p, int f_type, void *node, size_t end) {
    memo_t *new_memo = mballoc(p->region, sizeof(memo_t));
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

    if (p->fast_match[token_pos] == 0) {
        return;
    }

    memo_t *memo = p->memoized_cache[token_pos];
    if (!memo) {
        // create a "head" memo
        p->memoized_cache[token_pos] = new_memo(p, f_type, node, endpos);
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

static memo_t __failed_memo = {0, NULL, 0, NULL};

memo_t *parser_get_memo(parser_t *p, int f_type) {
    if (p->fast_match[p->pos] == 0) {
        // Act as if memoized a failure. The token stream
        // has finished already: returning NULL here will
        // cause an infinite loop with left recursion.
        return &__failed_memo;
    }
    memo_t *memo = p->memoized_cache[p->pos];
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


void parser_set_error(parser_t *p, int code, void *object) {
    if (p->errorcode) {
        fprintf(stderr, "fatal: parser error code not reset");
        exit(EXIT_FAILURE);
    }
    p->errorcode = code;
    p->error_object = object;
}


void parser_verify_eof(parser_t *p) {
    lexer_t *ls = &p->lexer_state;
    if (p->pos >= ls->token_len && !ls->next_token) {
        // Everything is parsed; No problem.
        return;
    }
    
    // There are more unparsed tokens; produce an error
    size_t pos = ls->token_len - 2;

    token_t *tok;
    size_t col_start;
    size_t col_end;
    
    if (pos == ls->token_len - 1) {
        // Last token: Move caret to just 
        tok = ls->tokens[pos];
        col_start = tok->column + tok->len;
        col_end = col_start + 1;
    } else {
        // Highlight the next token
        tok = ls->tokens[pos + 1];
        col_start = tok->column;
        col_end = col_start + tok->len;
    }

    size_t lineno = tok->lineno;
    size_t line_start = ls->line_to_index[lineno];
    size_t line_end = _find_eol_index(ls, lineno);

    // include an extra char for \0
    char *line_buf = calloc(line_end - line_start + 1, sizeof(char));
    int j = 0;
    for (size_t i = line_start; i < line_end; ++i) {
        line_buf[j] = ls->src[i];
        ++j;
    }

    char *highlight = calloc(col_end + 5, sizeof(char));
    for (size_t i = 0; i < col_start + 4; ++i) {
        highlight[i] = ' ';
    }
    for (size_t i = col_start; i < col_end; ++i) {
        highlight[i+4] = '^';
    }

    char *error_msg = "Invalid Syntax";
    
    size_t max_len = 45 + (line_end - line_start) + col_end + strlen(error_msg);
    char *err_buf = calloc(max_len, sizeof(char));
    
    sprintf(err_buf, "line %zu\n    %s\n%s\nError: %s", 
            lineno + 1, line_buf, highlight, error_msg);

    parser_set_error(p, 1, err_buf);

    free(line_buf);
    free(highlight);
}