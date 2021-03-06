#include "include/internal/mem_internal.h"
#include "stdint.h"

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

void *mem_align_up(void *ptr, uintptr_t align) {
    uintptr_t aptr = (uintptr_t) (ptr) + (align - 1) & ~(align - 1);
    return (void *) aptr;
}

size_t mem_size_up(size_t s, size_t align) {
    return s + (align - 1) & ~(align - 1);
}

#define ALIGNMENT sizeof(uintptr_t)

FMemBlock *mem_block_new(size_t size) {
    FMemBlock *b = FMem_calloc(sizeof(FMemBlock) + size, sizeof(char));
    if (!b) return NULL;

    b->block_size = size;
    b->head_ptr = ((char *) b) + sizeof(FMemBlock);

    char *aligned_addr = mem_align_up(b->head_ptr, ALIGNMENT);
    b->alloc_offset = aligned_addr - (char *) b->head_ptr;
    b->next_block = NULL;

    return b;
}

#define DEFAULT_BLOCK_SIZE 8192

FMemRegion *FMemRegion_new() {
    return FMemRegion_from_size(DEFAULT_BLOCK_SIZE);
}

FMemRegion *FMemRegion_from_size(size_t initial_size) {
    FMemRegion *region = FMem_malloc(sizeof(FMemRegion));
    if (!region) return NULL;
    FMemBlock *b = mem_block_new(initial_size);
    if (!b) return NULL;
    region->head_block = b;
    region->cur_block = b;
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