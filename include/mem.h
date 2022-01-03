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
};

#define REGION_DEFAULT_SIZE 8192


mem_region_t *mbregion(size_t initial_size);

void mem_region_t_free(mem_region_t *region);

void *mballoc(mem_region_t *region, size_t size);

#endif //CPEG_MEM_H
