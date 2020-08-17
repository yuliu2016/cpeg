#include "include/peg.h"

#define GET_CURR_TOKEN(p) p->tokens[p->pos]

#define NEW_NODE(p) PARSER_ALLOC(p, sizeof(FAstNode))

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
        FAstNode *node = NEW_NODE(p);
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
    FToken *curr_token = GET_CURR_TOKEN(p);
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
    FToken *curr_token = GET_CURR_TOKEN(p);
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
    FToken *curr_token = GET_CURR_TOKEN(p);
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

FAstNode *FAst_new_sequence() {
    FAstNode *node = FMem_malloc(sizeof(FAstNode));
    node->ast_t = 2;
    FAstSequence *seq = &node->ast_v.sequence;
    seq->capacity = 0;
    seq->len = 0;
    seq->items = NULL;
    return node;
}

void FAst_seq_append(FAstNode *node, void *item) {
    FAstSequence *seq = &node->ast_v.sequence;
    int i = seq->len;
    if (i >= seq->capacity) {
        if (!seq->capacity) {
            seq->capacity = 1;
            seq->items = FMem_malloc(sizeof(void *));
        } else {
            seq->capacity = seq->capacity << 1u;
            seq->items = FMem_realloc(seq->items, seq->capacity * sizeof(void *));
        }
    }
    seq->items[i] = item;
    ++seq->len;
}

FAstNode *FAst_node_1(FPegParser *p, int t, FAstNode *a) {
    FAstNode *res = NEW_NODE(p);
    res->ast_t = t;
    res->ast_v.fields[0] = a;
    return res;
}

FAstNode *FAst_node_2(FPegParser *p, int t, FAstNode *a, FAstNode *b) {
    FAstNode *res = NEW_NODE(p);
    res->ast_t = t;
    res->ast_v.fields[0] = a;
    res->ast_v.fields[1] = b;
    return res;
}