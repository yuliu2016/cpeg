#ifndef CPEG_MEM_H
#define CPEG_MEM_H

#include "stddef.h"

typedef struct mem_region_t FMemRegion;

typedef struct mem_block_t FMemBlock;

struct mem_block_t {
    size_t block_size;
    size_t alloc_offset;
    void *head_ptr;
    FMemBlock *next_block;
};

struct mem_region_t {
    FMemBlock *head_block;
    FMemBlock *cur_block;
};

#define REGION_DEFAULT_SIZE 8192


FMemRegion *mbregion(size_t initial_size);

void mbpurge(FMemRegion *region);

void *mballoc(FMemRegion *region, size_t size);

#endif //CPEG_MEM_H
