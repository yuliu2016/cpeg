#include "include/internal/mem_debug.h"
#include "include/internal/debugcli.h"

char *idchptr(char *in) {
    return in;
}

int main() {
    FMem_set_allocator(default_allocator());
    test_region();

    input_loop(">>>", idchptr);
    return 0;
}

