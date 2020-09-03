#include "include/peg.h"
#include "stdarg.h"
#include "stdio.h"

FPegParser *FPeg_new_parser(FMemRegion *region, FTokenArray *a, FPegDebugHook *dh) {
    FPegParser *p = FMemRegion_malloc(region, sizeof(FPegParser));
    p->pos = 0;
    p->max_reached_pos = 0;
    p->level = 0;
    p->dh = dh;
    p->region = region;
    p->token_len = a->len;
    p->tokens = a->tokens;
    p->ignore_whitespace = 0;
    return p;
}

char *FPeg_check_state(FPegParser *p) {
    if (p->dh) {
        return 0;
    }
    if (p->level != 0) {
        return "p->level is not 0";
    }
    if (p->pos < p->token_len) {
        return "Finished AST without all tokens";
    }
    return 0;
}

void FAst_node_assert_type(FAstNode *node, index_t t) {
    if (node->ast_t != t) {
        printf("Node type %d expected, but is actually %d", t, node->ast_t);
    }
}

FAstNode *FPeg_consume_token(FPegParser *p, index_t type) {
    size_t pos = p->pos;

    FToken *curr_token = p->tokens[pos];

    // the first token that doesn't ignore whitespace
    if (p->ignore_whitespace) {
        while (curr_token->is_whitespace && (pos + 1) < p->token_len) {
            pos += 1;
            curr_token = p->tokens[pos];
        }
    }

    // now check for correct type
    if (curr_token->type == type) {
        p->pos = pos + 1;
        FAstNode *node = PARSER_ALLOC(p, sizeof(FAstNode));
        // not sequence -> | 1u
        // is token -> | 2u
        node->ast_t = type << 2u | 1u | 2u;
        node->ast_v.token = curr_token;
        return node;
    } else {
        return NULL;
    }
}

FTokenMemo *new_memo(FPegParser *p, index_t type, void *node, size_t end) {
    FTokenMemo *new_memo = PARSER_ALLOC(p, sizeof(FTokenMemo));
    if (!new_memo) return NULL;
    new_memo->type = type;
    new_memo->node = node;
    new_memo->end_pos = end;
    new_memo->next = NULL;
    return new_memo;
}

void FPeg_put_memo(FPegParser *p, index_t type, void *node, size_t end) {
    FToken *curr_token = p->tokens[p->pos];
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

FTokenMemo *FPeg_get_memo(FPegParser *p, index_t type) {
    FToken *curr_token = p->tokens[p->pos];
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

FAstNode *seq_new(FPegParser *p) {
    FAstNode *node = PARSER_ALLOC(p, sizeof(FAstNode));
    // sequence type has a t of 0
    node->ast_t = 0;
    FAstSequence *seq = &node->ast_v.sequence;
    seq->capacity = 0;
    seq->len = 0;
    seq->items = NULL;
    return node;
}

void seq_append(FPegParser *p, FAstNode *node, void *item) {
    FAstSequence *seq = &node->ast_v.sequence;
    if (seq->len >= seq->capacity) {
        if (!seq->capacity) {
            seq->capacity = 1;
            seq->len = 0;
            seq->items = PARSER_ALLOC(p, sizeof(FAstNode *));
        } else {
            seq->capacity = seq->capacity << 1u;
            FAstNode **old_items = seq->items;
            seq->items = PARSER_ALLOC(p, seq->capacity * sizeof(FAstNode *));
            for (int i = 0; i < seq->len; ++i) {
                seq->items[i] = old_items[i];
            }
        }
    }
    seq->items[seq->len] = item;
    ++seq->len;
}

FAstNode *FAst_new_node(FPegParser *p, index_t t, int nargs, ...) {
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

FAstNode *FPeg_parse_sequece_or_none(FPegParser *p, rule_func rule) {
    FAstNode *node, *seq = seq_new(p);
    while ((node = rule(p))) {
        seq_append(p, seq, node);
    }
    return seq;
}

FAstNode *FPeg_parse_sequence(FPegParser *p, rule_func rule) {
    FAstNode *node, *seq;
    if (!(node = rule(p))) return 0;
    seq = seq_new(p);
    do {
        seq_append(p, seq, node);
    } while ((node = rule(p)));
    return seq;
}

FAstNode *FPeg_parse_delimited(FPegParser *p, index_t delimiter, rule_func rule) {
    FAstNode *node, *seq;
    if (!(node = rule(p))) return 0;
    seq = seq_new(p);
    size_t pos;
    while (1) {
        seq_append(p, seq, node);
        pos = p->pos;
        if (!(FPeg_consume_token(p, delimiter) && rule(p))) {
            break;
        }
    }
    p->pos = pos;
    return seq;
}

FAstNode *FPeg_parse_token_sequence(FPegParser *p, index_t token) {
    FAstNode *node, *seq;
    if (!(node = FPeg_consume_token(p, token))) return 0;
    seq = seq_new(p);
    do {
        seq_append(p, seq, node);
    } while ((node = FPeg_consume_token(p, token)));
    return seq;
}

FAstNode *FPeg_parse_token_sequence_or_none(FPegParser *p, index_t token) {
    FAstNode *node, *seq = seq_new(p);
    while ((node = FPeg_consume_token(p, token))) {
        seq_append(p, seq, node);
    }
    return seq;
}

FAstNode *FPeg_parse_token_delimited(FPegParser *p, index_t delimiter, index_t token) {
    FAstNode *node, *seq;
    if (!(node = FPeg_consume_token(p, token))) return 0;
    seq = seq_new(p);
    size_t pos;
    while (1) {
        seq_append(p, seq, node);
        pos = p->pos;
        if (!(FPeg_consume_token(p, delimiter) && FPeg_consume_token(p, token))) {
            break;
        }
    }
    p->pos = pos;
    return seq;
}