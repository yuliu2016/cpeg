#ifndef CPEG_MEM_DEBUG_H
#define CPEG_MEM_DEBUG_H

#include "mem_internal.h"

char *memregion_copy(FMemRegion *region);

void printptr(void *head, int size);

void test_block();

FMemAllocator dballoc();

FMemAllocator default_allocator();

#endif //CPEG_MEM_DEBUG_H
