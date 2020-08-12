#include "include/tokenizer.h"
#include "include/mem.h"

typedef struct {
    FMemRegion *region;
    size_t len;
    size_t capacity;
    FToken **tokens;
    char *src;
    size_t src_len;
    size_t pos;
} FTokenizerState;

FTokenArray *array_from_state(FTokenizerState *ts) {
    FMemRegion *r = ts->region;
    FTokenArray *ta = FMemRegion_malloc(r, sizeof(FTokenArray));
    ta->len = ts->len;
    FToken **tokens = FMemRegion_malloc(r, sizeof(FToken) * ts->len);
    for (int i = 0; i < ts->len; ++i) {
        tokens[i] = ts->tokens[i];
    }
    ta->tokens = tokens;
    FMem_free(ts->tokens);
    FMem_free(ts);
    return ta;
}


FTokenizerState *FTokenizer_create_state() {
    FTokenizerState *ts = FMem_malloc(sizeof(FTokenizerState));
    ts->region = FMemRegion_new();
    ts->capacity = 0;
    ts->len = 0;
    ts->tokens = NULL;
    return ts;
}

void tokenizer_list_resize_double(FTokenizerState *ts) {
    if (!ts->capacity) {
        ts->capacity = 1;
        ts->tokens = FMem_malloc(sizeof(FToken *));
    } else {
        ts->capacity = ts->capacity << 1u;
        ts->tokens = FMem_realloc(ts->tokens, ts->capacity * sizeof(FToken *));
    }
}

void FTokenizer_append_token(FTokenizerState *ts, FToken* tok) {
    int i = ts->len;
    if (i >= ts->capacity) {
        tokenizer_list_resize_double(ts);
    }
    ts->tokens[i] = tok;
    ++ts->len;
}