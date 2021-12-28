#include "include/internal/debugcli.h"
#include "include/internal/mem_debug.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "inttypes.h"
#include "include/peg.h"


void input_loop(char *prompt, char *(*func)(char *)) {
    print(prompt);
    char line[1024];
    for (;;) {
        fgets(line, 1024, stdin);
        if (strlen(line) == 0) {
            continue;
        }
        if (strcmp(line, "exit\n") == 0) {
            break;
        }
        // remove the newline character at the end
        line[strlen(line) - 1] = 0;
        char *s = func(line);
        if (!s) {
            break;
        }
        print(s);
        print(prompt);
    }
}

void print(char *s) {
    printf("%s", s);
}

void println(char *s) {
    printf("%s\n", s);
}

char *memregion_copy(FMemRegion *region) {
    size_t s = 0;
    FMemBlock *head = region->head_block;
    while (head) {
        s += head->block_size;
        head = head->next_block;
    }
    char *buf = FMem_malloc(s + 1);
    head = region->head_block;
    int i = 0;
    while (head) {
        char *acc = (char *) head->head_ptr;
        size_t bs = head->block_size;
        size_t offset = head->alloc_offset;
        int j = 0;
        for (; j < bs; ++j) {
            if (j < offset) {
                char ch = acc[j];
                if (ch) {
                    buf[i + j] = ch;
                } else {
                    buf[i + j] = '_';
                }
            } else {
                buf[i + j] = '#';
            }
        }
        i = j;
        head = head->next_block;
    }
    buf[i] = '\0';
    return buf;
}

void print_buf(void *head, int size) {
    char *buf = malloc(size + 1);
    char *acc = head;
    for (int i = 0; i < size; ++i) {
        char ch = acc[i];
        if (ch) {
            buf[i] = ch;
        } else {
            buf[i] = '^';
        }
    }
    buf[size] = '\0';
    printf("%s\n", buf);
}

void test_block() {
    FMem_set_allocator(default_allocator());
    FMemBlock *block = mem_block_new(256);
    char *dest = block->head_ptr;
    block->alloc_offset += 11;
    strcpy(dest, "HelloWorld");
    dest = ((char *) block->head_ptr) + block->alloc_offset;
    block->alloc_offset += 3;
    strcpy(dest, "Ho");
    print_buf(block->head_ptr, 256);
    free(block);
}

void test_region() {
    FMem_set_allocator(default_allocator());
    FMemRegion *reg = FMemRegion_from_size(32);
    PRINT_ADDR(reg);
    PRINT_ADDR(reg->cur_block);
    char *dst = FMemRegion_malloc(reg, 11);
    PRINT_ADDR(dst);
    strcpy(dst, "HelloWorld");
    dst = FMemRegion_malloc(reg, 3);
    PRINT_ADDR(dst);
    strcpy(dst, "Hi");
    dst = NULL;
    printf("%zu\n", sizeof(char *));
    char *x = memregion_copy(reg);
    printf("%s\n", x);
    FMemRegion_free(reg);
    FMem_free(x);
}

void print_address(void *ptr, const char *name) {
    uintptr_t i = (uintptr_t) ptr;
    size_t s = sizeof(uintptr_t) / 4;
    if (s == 1) {
        printf("%-16s = %#08x\n", name, (unsigned int) i);
    } else {
        printf("%-16s = %#016llx\n", name, (unsigned long long) i);
    }
}

void *dbmalloc(size_t size) {
    void *r = malloc(size);
    if (r) {
        printf("Got malloc for size %zu\n", size);
    } else {
        printf("malloc returned null\n");
    }
    return r;
}

void *dbcalloc(size_t count, size_t size) {
    void *r = calloc(count, size);
    if (r) {
        printf("Got calloc for size %zu and count %zu\n", size, count);
    } else {
        printf("calloc returned null\n");
    }
    return r;
}

FMemAllocator dballoc() {
    return (FMemAllocator) {dbmalloc, dbcalloc, realloc, free};
}

FMemAllocator default_allocator() {
    return (FMemAllocator) {malloc, calloc, realloc, free};
}

typedef struct token_kind {
    const char * name;
    const char * style;
    size_t min;
    size_t max;
} TokenKind;

static TokenKind token_kinds[] = {
    {"ENDMARKER", "\033[31m", 1, 2},
    {"NEWLINE", "", 2, 3},
    {"NAME", "\033[35m", 3, 4}, // magenta
    {"NUMBER", "\033[34m", 4, 5}, // blue
    {"STRING", "\033[32m", 5, 6}, // green
    {"OPERATOR", "\033[33m", 6, 54}, // yellow
    {"KEYWORD", "\033[34;1m", 55, 84}, // bright blue
};

FLexerState *FLexer_analyze_all(char *src);

char *tokenizer_repl(char *in) {
    FLexerState *ls = FLexer_analyze_all(in);
    if (ls->error) {
        printf("\033[31mFile <repl>, %s\033[0m", ls->error);
        FLexer_free_state(ls);
        return "\n";
    }

    if (ls->token_len == 0) {
        printf("[Empty Token List]\n");
        FLexer_free_state(ls);
        return "";
    }

    size_t previous_line = -1;
    size_t literal_len = 100;
    char *literal = FMem_malloc(literal_len);

    for (int i = 0; i < ls->token_len; ++i) {
        FToken *token = ls->tokens[i];

        if (token->len > literal_len) {
            literal_len = token->len;
            literal = FMem_realloc(literal, literal_len);
        }

        for (int j = 0; j < literal_len; ++j) {
            literal[j] = 0;
        }
        for (size_t j = 0; j < token->len; ++j) {
            char ch = token->start[j];
            if (ch == '\n') {
                literal[j++] = '\\';
                literal[j] = 'n';
            } else {
                literal[j] = ch;
            }
        }

        size_t line = token->lineno;
        previous_line = line;

        size_t type = token->type;
        TokenKind kind;
        for (int i = 0; i < 7; ++i) {
            kind = token_kinds[i];
            if (type >= kind.min && type < kind.max) {
                break;
            }
        }

        printf("L%zu:%zu\t%-10s%s%s\033[0m\n", line + 1, token->column,
                kind.name, kind.style, literal);
    }

    FMem_free(literal);
    FLexer_free_state(ls);
    return "";
}

char *idchptr(char *in) {
    return in;
}