#include <string.h>
#include "include/internal/mem_debug.h"
#include "include/internal/debugcli.h"

char *idchptr(char * in) {
    return in;
}

int prt() {
    print("hi");
    return 8;
}

int main() {
    FMem_set_allocator(default_allocator());
    FMemRegion *reg = FMemRegion_from_size(32);
    char *dst = FMemRegion_malloc(reg, 11);
    strcpy(dst, "HelloWorld");
    dst = FMemRegion_malloc(reg, 3);
    strcpy(dst, "Hi");
    dst = NULL;

    char *x = memregion_copy(reg);
    println(x);
    FMemRegion_free(reg);
    FMem_free(x);

    input_loop(">>>", idchptr);

    return 0;
}

