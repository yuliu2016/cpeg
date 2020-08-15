#include "include/internal/mem_debug.h"
#include "include/internal/debugcli.h"

char *idchptr(char * in) {
    return in;
}

int main() {
    test_region();

    input_loop(">>>", idchptr);
    return 0;
}

