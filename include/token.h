#ifndef CPEG_TOKEN_H
#define CPEG_TOKEN_H

typedef struct token_str_t {
    char *start;
    int len;
} FTokenStr;

typedef struct token_memo_t {
    int type;
    void *node;
    int end_pos;
    struct token_memo_t *next;
} FTokenMemo;

typedef struct token_t {
    int type;
    FTokenStr *str;
    int line_start;
    int line_end;
    int col_start;
    int col_end;
    FTokenMemo *memo;
} FToken;

typedef struct token_array_t {
    int len;
    FToken **tokens;
} FTokenArray;

FTokenStr *FToken_str_from_ptr(char *src);

#endif //CPEG_TOKEN_H
