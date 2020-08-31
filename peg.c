#include "include/peg.h"
#include "stdarg.h"

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

FAstNode *FPeg_consume_token(FPegParser *p, int type) {
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
        node->ast_t = 1;
        node->ast_v.token = curr_token;
        return node;
    } else {
        return NULL;
    }
}

FTokenMemo *FPeg_new_memo(FPegParser *p, int type, void *node, int end) {
    FTokenMemo *new_memo = PARSER_ALLOC(p, sizeof(FTokenMemo));
    if (!new_memo) return NULL;
    new_memo->type = type;
    new_memo->node = node;
    new_memo->end_pos = end;
    new_memo->next = NULL;
    return new_memo;
}

void FPeg_put_memo(FPegParser *p, int type, void *node, int end) {
    FToken *curr_token = p->tokens[p->pos];
    FTokenMemo *memo = curr_token->memo;
    if (!memo) {
        curr_token->memo = FPeg_new_memo(p, type, node, end);
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
    memo->next = FPeg_new_memo(p, type, node, end);
}

FTokenMemo *FPeg_get_memo(FPegParser *p, int type) {
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

FAstNode *FAst_new_sequence(FPegParser *p) {
    FAstNode *node = PARSER_ALLOC(p, sizeof(FAstNode));
    node->ast_t = 2;
    FAstSequence *seq = &node->ast_v.sequence;
    seq->capacity = 0;
    seq->len = 0;
    seq->items = NULL;
    return node;
}

void FAst_seq_append(FPegParser *p, FAstNode *node, void *item) {
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

FAstNode *FAst_new_node(FPegParser *p, unsigned int t, int nargs, ...) {
    va_list valist;
    if (nargs > AST_NODE_MAX_FIELD) {
        return NULL;
    }
            va_start(valist, nargs);

    FAstNode *res = PARSER_ALLOC(p, sizeof(FAstNode));
    res->ast_t = t;
    for (int i = 0; i < nargs; ++i) {
        res->ast_v.fields[i] = va_arg(valist, FAstNode *);
    }

            va_end(valist);
    return res;
}

FAstNode *FPeg_parse_sequece_or_none(FPegParser *p, FAstNode *(*rule)(FPegParser *)) {
    FAstNode *node, *seq = FAst_new_sequence(p);
    while ((node = rule(p))) {
        FAst_seq_append(p, seq, node);
    }
    return seq;
}

FAstNode *FPeg_parse_sequence(FPegParser *p, FAstNode *(*rule)(FPegParser *)) {
    FAstNode *node, *seq;
    if (!(node = rule(p))) return 0;
    seq = FAst_new_sequence(p);
    do {
        FAst_seq_append(p, seq, node);
    } while ((node = rule(p)));
    return seq;
}

FAstNode *FPeg_parse_delimited(FPegParser *p, int delimiter, FAstNode *(*rule)(FPegParser *)) {
    FAstNode *node, *seq;
    if (!(node = rule(p))) return 0;
    seq = FAst_new_sequence(p);
    size_t pos;
    while (1) {
        FAst_seq_append(p, seq, node);
        pos = p->pos;
        if (!(FPeg_consume_token(p, delimiter) && rule(p))) {
            break;
        }
    }
    p->pos = pos;
    return seq;
}