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

mem_block_t *mem_block_new(size_t size) {
    mem_block_t *b = calloc(sizeof(mem_block_t) + size, sizeof(char));
    if (!b) return NULL;

    b->block_size = size;
    b->head_ptr = ((char *) b) + sizeof(mem_block_t);

    char *aligned_addr = mem_align_up(b->head_ptr, ALIGNMENT);
    b->alloc_offset = aligned_addr - (char *) b->head_ptr;
    b->next_block = NULL;

    return b;
}



mem_region_t *mbregion(size_t initial_size, size_t increment_size) {
    mem_region_t *region = malloc(sizeof(mem_region_t));
    if (!region) return NULL;
    mem_block_t *b = mem_block_new(initial_size);
    if (!b) return NULL;
    region->head_block = b;
    region->cur_block = b;
    region->increment_size = increment_size;
    return region;
}

void mbpurge(mem_region_t *region) {
    mem_block_t *curr;
    mem_block_t *head = region->head_block;
    while (head) {
        curr = head;
        head = curr->next_block;
        free(curr);
    }
    free(region);
}

void *mballoc(mem_region_t *region, size_t size) {
    mem_block_t *b = region->cur_block;
    size_t avail_size = b->block_size - b->alloc_offset;
    // round up the size needed to multiple of the required alignment
    size = mem_size_up(size, ALIGNMENT);
    if (avail_size < size) {
        mem_block_t *tail;
        if (region->increment_size != 0) {
            tail = mem_block_new(region->increment_size);
        } else {
            tail = mem_block_new(size);
        }
        if (!tail) {
            return NULL;
        }
        b->next_block = tail;
        region->cur_block = tail;
        return ((char *) tail->head_ptr) + tail->alloc_offset;
    } else {
        void *ptr = ((char *) b->head_ptr) + b->alloc_offset;
        b->alloc_offset += size;
        return ptr;
    }
}


mblist_t *mblist_new(mem_region_t *region, size_t initial_size) {
    mblist_t *seq = mballoc(region, sizeof(mblist_t));
    if (!seq) {
        return NULL;
    }

    size_t capacity;
    if (!initial_size) {
        capacity = 0;
    } else {
        capacity = 1;
        while (capacity < initial_size)
            capacity *= 2;
    }

    seq->capacity = capacity;
    seq->len = 0;

    if (!capacity) {
        seq->items = NULL;
    } else {
        void** items = mballoc(region, capacity * sizeof(void *));
        if (!items) {
            return NULL;
        }
        seq->items = items;
    }
    return seq;
}

void mblist_append(mem_region_t *region, mblist_t *seq, void *item) {
    if (seq->len >= seq->capacity) {
        if (!seq->capacity) {
            seq->capacity = 1;
            seq->len = 0;
            seq->items = mballoc(region, sizeof(void *));
            if (!seq->items) return;
        } else {
            seq->capacity = seq->capacity << 1u;
            void **old_items = seq->items;
            seq->items = mballoc(region, seq->capacity * sizeof(void *));
            if (!seq->items) return;
            for (int i = 0; i < seq->len; ++i) {
                seq->items[i] = old_items[i];
            }
        }
    }
    seq->items[seq->len++] = item;
}