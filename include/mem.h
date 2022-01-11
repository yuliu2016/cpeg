#ifndef CPEG_MEM_H
#define CPEG_MEM_H

#include "stddef.h"

typedef struct mem_region mem_region_t;

typedef struct mem_block mem_block_t;

struct mem_block {
    size_t block_size;
    size_t alloc_offset;
    void *head_ptr;
    mem_block_t *next_block;
};

struct mem_region {
    mem_block_t *head_block;
    mem_block_t *cur_block;
    size_t increment_size;
};

#define REGION_DEFAULT_SIZE 8192

mem_region_t *mbregion(size_t initial_size, size_t increment_size);

void mbpurge(mem_region_t *region);

void *mballoc(mem_region_t *region, size_t size);

typedef struct mblist {
    size_t len;
    size_t capacity;
    void **items;
} mblist_t;

mblist_t *mblist_new(mem_region_t *region, size_t initial_size);

void mblist_append(mem_region_t *region, mblist_t *seq, void *item);


#endif //CPEG_MEM_H
