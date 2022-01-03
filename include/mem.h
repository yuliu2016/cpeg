#ifndef CPEG_MEM_H
#define CPEG_MEM_H

#include "stddef.h"

typedef struct mem_region_t FMemRegion;

FMemRegion *FMemRegion_new();

FMemRegion *FMemRegion_from_size(size_t initial_size);

void FMemRegion_free(FMemRegion *region);

void *FMemRegion_malloc(FMemRegion *region, size_t size);

#endif //CPEG_MEM_H
