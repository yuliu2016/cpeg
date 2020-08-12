#ifndef CPEG_MEM_H
#define CPEG_MEM_H

#include "stddef.h"

typedef struct {
    void *(*malloc)(size_t size);

    void *(*calloc)(size_t count, size_t size);

    void *(*realloc)(void *ptr, size_t size);

    void (*free)(void *ptr);
} FMemAllocator;

void FMem_set_allocator(FMemAllocator alloc);

void *FMem_malloc(size_t size);

void *FMem_calloc(size_t count, size_t size);

void *FMem_realloc(void *ptr, size_t size);

void FMem_free(void *ptr);

typedef struct region_ FMemRegion;

FMemRegion *FMemRegion_new();

FMemRegion *FMemRegion_from_size(size_t initial_size);

void FMemRegion_free(FMemRegion *region);

void *FMemRegion_malloc(FMemRegion *region, size_t size);

#endif //CPEG_MEM_H
