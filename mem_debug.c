#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "include/internal/mem_debug.h"


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

void printptr(void *head, int size) {
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
    FMemBlock *block = block_new(256);
    char *dest = block->head_ptr;
    block->alloc_offset += 11;
    strcpy(dest, "HelloWorld");
    dest = ((char *) block->head_ptr) + block->alloc_offset;
    block->alloc_offset += 3;
    strcpy(dest, "Ho");
    printptr(block->head_ptr, 256);
    free(block);
}

void *dbmalloc(size_t size) {
    void *r = malloc(size);
    if (r) {
        printf("Got malloc for size %d\n", size);
    } else {
        printf("malloc returned null\n");
    }
    return r;
}

void *dbcalloc(size_t count, size_t size) {
    void *r = calloc(count, size);
    if (r) {
        printf("Got calloc for size %d and count %d\n", size, count);
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