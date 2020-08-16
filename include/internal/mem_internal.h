#ifndef CPEG_MEM_INTERNAL_H
#define CPEG_MEM_INTERNAL_H

#include "../mem.h"

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

FMemBlock *mem_block_new(size_t size);

#endif //CPEG_MEM_INTERNAL_H
