#ifndef CPEG_MEM_INTERNAL_H
#define CPEG_MEM_INTERNAL_H

#include "../mem.h"

struct block_ {
    size_t block_size;
    size_t alloc_offset;
    void *head_ptr;
    struct block_ *next_block;
};

typedef struct block_ FMemBlock;

struct region_ {
    FMemBlock *head_block;
    FMemBlock *cur_block;
};

FMemBlock *block_new(size_t size);

#endif //CPEG_MEM_INTERNAL_H
