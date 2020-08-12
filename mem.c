#include "include/internal/mem_internal.h"

static FMemAllocator allocator_;

void FMem_set_allocator(FMemAllocator alloc) {
    allocator_ = alloc;
}

void *FMem_malloc(size_t size) {
    return allocator_.malloc(size);
}

void *FMem_calloc(size_t count, size_t size) {
    return allocator_.calloc(count, size);
}

void *FMem_realloc(void *ptr, size_t size) {
    return allocator_.realloc(ptr, size);
}

void FMem_free(void *ptr) {
    allocator_.free(ptr);
}

FMemBlock *block_new(size_t size) {
    void *ptr = FMem_malloc(sizeof(FMemBlock) + size);
    FMemBlock *block_ptr = ptr;
    block_ptr->block_size = size;
    block_ptr->head_ptr = ((char *) ptr) + sizeof(FMemBlock);
    block_ptr->alloc_offset = 0;
    block_ptr->next_block = NULL;
    return block_ptr;
}

#define DEFAULT_BLOCK_SIZE 8192

FMemRegion *FMemRegion_new() {
    return FMemRegion_from_size(DEFAULT_BLOCK_SIZE);
}

size_t round2x(size_t v) {
    v--;
    v |= v >> 1u;
    v |= v >> 2u;
    v |= v >> 4u;
    v |= v >> 8u;
    v |= v >> 16u;
    v++;
    return v;
}

FMemRegion *FMemRegion_from_size(size_t initial_size) {
    FMemBlock *block = block_new(round2x(initial_size));
    FMemRegion *region = FMem_malloc(sizeof(FMemRegion));
    region->head_block = block;
    region->cur_block = block;
    return region;
}

void FMemRegion_free(FMemRegion *region) {
    FMemBlock *curr;
    FMemBlock *head = region->head_block;
    while (head) {
        curr = head;
        head = curr->next_block;
        FMem_free(curr);
    }
    FMem_free(region);
}

void *FMemRegion_malloc(FMemRegion *region, size_t size) {
    FMemBlock *b = region->cur_block;
    size_t avail_size = b->block_size - b->alloc_offset;
    if (avail_size < size) {
        // make a block exactly the right size
        FMemBlock *tail = block_new(size);
        b->next_block = tail;
        region->cur_block = tail;
        return tail->head_ptr;
    } else {
        void *ptr = ((char *) b->head_ptr) + b->alloc_offset;
        b->alloc_offset += size;
        return ptr;
    }
}