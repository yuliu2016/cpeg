#include "include/peg.h"

FPegParser *FPeg_new_parser(FMemRegion *region, FTokenArray *a, FPegDebugHook *dh) {
    FPegParser *p = FMemRegion_malloc(region, sizeof(FPegParser));
    p->pos = 0;
    p->max_reached_pos = 0;
    p->level = 0;
    p->debug_hook = dh;
    p->region = region;
    p->token_len = a->len;
    p->tokens = a->tokens;
    return p;
}

FAstNode *ast_node_from_token(FPegParser *p, FToken *token) {
    if (token) {
        FAstNode *node = PARSER_ALLOC(p, sizeof(FAstNode));
        node->ast_t = 1;
        node->ast_v.token = token;
        return node;
    }
    return NULL;
}

FAstNode *FPeg_consume_token(FPegParser *p, int type) {
    if (p->pos >= p->token_len) {
        return NULL;
    }
    FToken *curr_token = p->tokens[p->pos];
    FToken *res = NULL;
    if (curr_token->type == type) {
        res = curr_token;
    }
    return ast_node_from_token(p, res);
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

FAstNode *FAst_node_1(FPegParser *p, int t, FAstNode *a) {
    FAstNode *res = PARSER_ALLOC(p, sizeof(FAstNode));
    res->ast_t = t;
    res->ast_v.fields[0] = a;
    return res;
}

FAstNode *FAst_node_2(FPegParser *p, int t, FAstNode *a, FAstNode *b) {
    FAstNode *res = PARSER_ALLOC(p, sizeof(FAstNode));
    res->ast_t = t;
    res->ast_v.fields[0] = a;
    res->ast_v.fields[1] = b;
    return res;
}