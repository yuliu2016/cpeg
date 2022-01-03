#include "include/mem.h"
#include "stdint.h"
#include "stdlib.h"


static inline void *mem_align_up(void *ptr, uintptr_t align) {
    uintptr_t aptr = (uintptr_t) (ptr) + (align - 1) & ~(align - 1);
    return (void *) aptr;
}

static inline size_t mem_size_up(size_t s, size_t align) {
    return s + (align - 1) & ~(align - 1);
}

#define ALIGNMENT sizeof(uintptr_t)

FMemBlock *mem_block_new(size_t size) {
    FMemBlock *b = calloc(sizeof(FMemBlock) + size, sizeof(char));
    if (!b) return NULL;

    b->block_size = size;
    b->head_ptr = ((char *) b) + sizeof(FMemBlock);

    char *aligned_addr = mem_align_up(b->head_ptr, ALIGNMENT);
    b->alloc_offset = aligned_addr - (char *) b->head_ptr;
    b->next_block = NULL;

    return b;
}



FMemRegion *mbregion(size_t initial_size) {
    FMemRegion *region = malloc(sizeof(FMemRegion));
    if (!region) return NULL;
    FMemBlock *b = mem_block_new(initial_size);
    if (!b) return NULL;
    region->head_block = b;
    region->cur_block = b;
    return region;
}

void mbpurge(FMemRegion *region) {
    FMemBlock *curr;
    FMemBlock *head = region->head_block;
    while (head) {
        curr = head;
        head = curr->next_block;
        free(curr);
    }
    free(region);
}

void *mballoc(FMemRegion *region, size_t size) {
    FMemBlock *b = region->cur_block;
    size_t avail_size = b->block_size - b->alloc_offset;
    // round up the size needed to multiple of the required alignment
    size = mem_size_up(size, ALIGNMENT);
    if (avail_size < size) {
        // make a block exactly the right size
        FMemBlock *tail = mem_block_new(size);
        if (!tail) return NULL;
        b->next_block = tail;
        region->cur_block = tail;
        return tail->head_ptr;
    } else {
        void *ptr = ((char *) b->head_ptr) + b->alloc_offset;
        b->alloc_offset += size;
        return ptr;
    }
}