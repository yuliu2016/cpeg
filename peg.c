#include "include/peg.h"
#include "stdarg.h"

void FLexer_init_state(FLexerState *ls, char *src, size_t len) {
    ls->src = src;
    ls->src_len = len;

    ls->curr_index = 0;

    ls->tokens = 0;
    ls->token_len = 0;
    ls->token_capacity = 0;

    ls->line_to_index = 0;
    ls->lines_size = 0;
    ls->lines_capacity = 0;

    ls->start_index = 0;
    ls->error = 0;
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

FToken *lexer_get_token(FParser *p, size_t pos) {
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
            p->error = "attempting to get token when stream has finished";
            return NULL;
        }
    }

    return ls->tokens[pos];
}

int FLexer_did_finish(FLexerState *ls, size_t pos) {
    return pos >= ls->token_len
           && ls->next_token == NULL;
}

void FLexer_free_state(FLexerState *ls) {
    for (int i = 0; i < ls->token_len; ++i) {
        FMem_free(ls->tokens[i]);
    }
    FMem_free(ls->tokens);
    FMem_free(ls->line_to_index);
}

FParser *FPeg_init_new_parser(
        char *src,
        size_t len,
        FLexerFunc lexer_func,
        FPegDebugHook *dh) {

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

    FLexer_init_state(&p->lexer_state, src, len);

    p->lexer_func = lexer_func;
    p->region = region;
    p->pos = 0;
    p->max_reached_pos = 0;
    p->ignore_whitespace = 0;
    p->level = 0;
    p->dh = dh;
    p->error = 0;

    // Need to scan at least one token to see
    // if there is anything to parse
    lexer_compute_next_token(p);

    return p;
}

void FPeg_free_parser(FParser *p) {
    FLexer_free_state(&p->lexer_state);
    FMem_free(p);
}

char *FPeg_check_state(FParser *p) {
    if (p->dh) {
        return 0;
    }
    if (p->level != 0) {
        return "p->level is not 0";
    }
    if (p->pos < p->lexer_state.token_len) {
        return "Finished AST without all tokens";
    }
    if (p->error) {
        return p->error;
    }
    return 0;
}

FAstNode *FPeg_consume_token(FParser *p, size_t type) {
    size_t pos = p->pos;

    FToken *curr_token = lexer_get_token(p, pos);

    // the first token that doesn't ignore whitespace
    if (p->ignore_whitespace) {
        while (curr_token->is_whitespace &&
               !FLexer_did_finish(&p->lexer_state, pos + 1)) {
            pos += 1;
            curr_token = lexer_get_token(p, pos);
        }
    }

    // now check for correct type
    if (curr_token->type == type) {
        p->pos = pos + 1;
        FAstNode *node = PARSER_ALLOC(p, sizeof(FAstNode));
        if (!node) {
            return NULL;
        }
        // not sequence -> | 1u
        // is token -> | 2u
        node->ast_t = type << 2u | 1u | 2u;
        node->ast_v.token = curr_token;
        return node;
    } else {
        return NULL;
    }
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

void FPeg_put_memo(FParser *p, size_t type, void *node, size_t end) {
    FToken *curr_token = p->lexer_state.tokens[p->pos];
    FTokenMemo *memo = curr_token->memo;
    if (!memo) {
        curr_token->memo = new_memo(p, type, node, end);
        return;
    }
    while (memo->next) {
        if (memo->type == type) {
            memo->node = node;
            memo->end_pos = end;
            return;
        }
        memo = memo->next;
    }
    memo->next = new_memo(p, type, node, end);
}

FTokenMemo *FPeg_get_memo(FParser *p, size_t type) {
    FToken *curr_token = p->lexer_state.tokens[p->pos];
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