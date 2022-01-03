#ifndef CPEG_MEM_DEBUG_H
#define CPEG_MEM_DEBUG_H

#include "mem_internal.h"

char *memregion_copy(FMemRegion *region);

void print_buf(void *head, int size);

#define PRINT_ADDR(ptr) print_address(ptr, #ptr)

void print_address(void *ptr, const char *name);

void test_block();

void test_region();

#endif //CPEG_MEM_DEBUG_H
