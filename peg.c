#include "include/peg.h"
#include "stdarg.h"
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

FAstNode *ast_node_from_token(FParser *p, size_t type, FToken *curr_token) {
    FAstNode *node = PARSER_ALLOC(p, sizeof(FAstNode));
    if (!node) {
        return NULL;
    }

    // not sequence -> | 1u
    // is token -> | 2u
    node->ast_t = type << 2u | 1u | 2u;
    node->ast_v.token = curr_token;
    return node;
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

void FPeg_debug_exit(FParser *p, FAstNode *res, size_t rule_index, const char *rule_name) {
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


FAstNode *FPeg_consume_token(FParser *p, size_t type) {
    size_t pos = p->pos;

    FToken *curr_token = get_next_token_to_consume(p, &pos);
    if (!curr_token) {
        return NULL;
    }

    // now check for correct type
    if (curr_token->type == type) {
        p->pos = pos + 1;
        return ast_node_from_token(p, type, curr_token);
    } else {
        return NULL;
    }
}

FAstNode *FPeg_consume_token_and_debug(FParser *p, size_t type, const char *literal) {
    size_t pos = p->pos;

    print_indent_level(p->level);
    FToken *curr_token = get_next_token_to_consume(p, &pos);
    if (!curr_token) {
        printf("Mismatch   \033[31;1m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu, \033[31mno more tokens\033[0m)\n",
                literal, p->level, p->pos);
        return NULL;
    }

    // now check for correct type
    if (curr_token->type == type) {
        p->pos = pos + 1;
        printf("Matched    \033[32;1m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[0m)\n",
                literal, p->level, p->pos);
        return ast_node_from_token(p, type, curr_token);
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

FAstNode *seq_new(FParser *p) {
    FAstNode *node = PARSER_ALLOC(p, sizeof(FAstNode));
    if (!node) {
        return NULL;
    }
    // sequence type has a t of 0
    node->ast_t = 0;
    FAstSequence *seq = &node->ast_v.sequence;
    seq->capacity = 0;
    seq->len = 0;
    seq->items = NULL;
    return node;
}

void seq_append(FParser *p, FAstNode *node, void *item) {
    FAstSequence *seq = &node->ast_v.sequence;
    if (seq->len >= seq->capacity) {
        if (!seq->capacity) {
            seq->capacity = 1;
            seq->len = 0;
            seq->items = PARSER_ALLOC(p, sizeof(FAstNode *));
        } else {
            seq->capacity = seq->capacity << 1u;
            // Since realloc isn't available with memory regions,
            // the nodes needs to be copied in a loop
            FAstNode **old_items = seq->items;
            seq->items = PARSER_ALLOC(p, seq->capacity * sizeof(FAstNode *));
            for (int i = 0; i < seq->len; ++i) {
                seq->items[i] = old_items[i];
            }
        }
    }
    seq->items[seq->len] = item;
    seq->len += 1;
}

FAstNode *FAst_new_node(FParser *p, size_t t, int nargs, ...) {
    va_list valist;
    if (nargs > AST_NODE_MAX_FIELD) {
        return NULL;
    }
    va_start(valist, nargs);

    FAstNode *res = PARSER_ALLOC(p, sizeof(FAstNode));
    // a field-node, shift by 2 and mark as non-sequence
    res->ast_t = t << 2u | 1u;
    for (int i = 0; i < nargs; ++i) {
        res->ast_v.fields[i] = va_arg(valist, FAstNode *);
    }
    
    va_end(valist);
    return res;
}

FAstNode *FPeg_parse_sequece_or_none(FParser *p, FRuleFunc rule) {
    FAstNode *node, *seq = seq_new(p);
    while ((node = rule(p))) {
        seq_append(p, seq, node);
    }
    return seq;
}

FAstNode *FPeg_parse_sequence(FParser *p, FRuleFunc rule) {
    FAstNode *node, *seq;
    if (!(node = rule(p))) return 0;
    seq = seq_new(p);

    do {
        seq_append(p, seq, node);
    } while ((node = rule(p)));

    return seq;
}

FAstNode *FPeg_parse_delimited(FParser *p, size_t delimiter, FRuleFunc rule) {
    FAstNode *node, *seq;
    if (!(node = rule(p))) return 0;
    seq = seq_new(p);
    size_t pos;

    do {
        seq_append(p, seq, node);
        pos = p->pos;
    } while (FPeg_consume_token(p, delimiter) && rule(p));

    p->pos = pos;
    return seq;
}

FAstNode *FPeg_parse_token_sequence(FParser *p, size_t token) {
    FAstNode *node, *seq;
    if (!(node = FPeg_consume_token(p, token))) return 0;
    seq = seq_new(p);

    do {
        seq_append(p, seq, node);
    } while ((node = FPeg_consume_token(p, token)));

    return seq;
}

FAstNode *FPeg_parse_token_sequence_or_none(FParser *p, size_t token) {
    FAstNode *node, *seq = seq_new(p);
    while ((node = FPeg_consume_token(p, token))) {
        seq_append(p, seq, node);
    }
    return seq;
}

FAstNode *FPeg_parse_token_delimited(FParser *p, size_t delimiter, size_t token) {
    FAstNode *node, *seq;
    if (!(node = FPeg_consume_token(p, token))) return 0;
    seq = seq_new(p);
    size_t pos;

    do {
        seq_append(p, seq, node);
        pos = p->pos;
    } while (FPeg_consume_token(p, delimiter) && FPeg_consume_token(p, token));

    p->pos = pos;
    return seq;
}