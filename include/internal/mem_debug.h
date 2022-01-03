#ifndef CPEG_MEM_DEBUG_H
#define CPEG_MEM_DEBUG_H

#include "../mem.h"

char *memregion_copy(mem_region_t *region);

void print_buf(void *head, int size);

#define PRINT_ADDR(ptr) print_address(ptr, #ptr)

void print_address(void *ptr, const char *name);

void test_block();

void test_region();

#endif //CPEG_MEM_DEBUG_H
