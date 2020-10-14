#include "include/internal/debugcli.h"
#include "include/internal/mem_debug.h"
#include "include/internal/peg_debug.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "inttypes.h"


void input_loop(char *prompt, char *(*func)(char *)) {
    print(prompt);
    char line[1024];
    for (;;) {
        fgets(line, 1024, stdin);
        if (strcmp(line, "exit\n") == 0) {
            break;
        }
        // remove the newline character at the end
        for (int i = 0; i < 1024; ++i) {
            if (i && !line[i]) {
                line[i - 1] = 0;
            }
        }
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


void print_indent_level(size_t s) {
    char *b = FMem_malloc(sizeof(char) * (s + 1));
    if (!b) {
        return;
    }
    for (size_t i = 0; i < s; ++i) {
        b[i] = ' ';
    }
    b[s] = '\0';
    printf("%s", b);
    FMem_free(b);
}

void enter_frame(size_t level, size_t pos, size_t rule_index, const char *rule_name) {
    print_indent_level(level);
    printf("Entering frame %zu:%s at pos %zu", rule_index, rule_name, pos);
}

void memo_hit(size_t level, size_t pos, size_t rule_index, const char *rule_name) {
    print_indent_level(level);
    printf("Memo found in frame %zu:%s at pos %zu", rule_index, rule_name, pos);
}

void exit_frame(FAstNode *res, size_t level, size_t pos, size_t rule_index, const char *rule_name) {
    print_indent_level(level);
    if (res) {
        printf("Success in frame %zu:%s at pos %zu", rule_index, rule_name, pos);
    } else {
        printf("Failure in frame %zu:%s at pos %zu", rule_index, rule_name, pos);
    }
}

FPegDebugHook FPeg_print_debug_hook() {
    return (FPegDebugHook) {enter_frame, memo_hit, exit_frame};
}