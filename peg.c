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

FToken *FPeg_consume_token(FPegParser *p, int type) {
    if (p->pos >= p->token_len) {
        return NULL;
    }
    FToken *curr_token = GET_CURR_TOKEN(p);
    FToken *res = NULL;
    if (curr_token->type == type) {
        res = curr_token;
    }
    return res;
}

FToken *FPeg_consume_token_debug(FPegParser *p, int type, char *literal) {
    if (p->pos >= p->token_len) {
        return NULL;
    }
    FToken *curr_token = GET_CURR_TOKEN(p);
    FToken *res = NULL;
    if (curr_token->type == type) {
        res = curr_token;
    }
    p->debug_hook->mark_token(res, p->level, type, curr_token->type, literal);
    return res;
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
            return memo;
        }
        memo = memo->next;
    }
    return NULL;
}

FPegList *FPeg_new_list() {
    FPegList *seq = FMem_malloc(sizeof(FPegList));
    seq->capacity = 0;
    seq->len = 0;
    seq->items = NULL;
    return seq;
}

void peg_list_resize_double(FPegList *list) {
    if (!list->capacity) {
        list->capacity = 1;
        list->items = FMem_malloc(sizeof(void *));
    } else {
        list->capacity = list->capacity << 1u;
        list->items = FMem_realloc(list->items, list->capacity * sizeof(void *));
    }
}

void FPeg_list_append(FPegList *list, void *item) {
    int i = list->len;
    if (i >= list->capacity) {
        peg_list_resize_double(list);
    }
    list->items[i] = item;
    ++list->len;
}