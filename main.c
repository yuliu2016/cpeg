#include "include/internal/mem_debug.h"
#include "include/internal/debugcli.h"
#include "include/tokenizer.h"
#include "include/parser.h"

#ifdef WIN32
#include "windows.h"
#endif

#include "stdio.h"
#include "string.h"

char *tokparse(char *in) {
    FParser *p = FPeg_init_new_parser(in, strlen(in), FLexer_get_next_token);
    single_input(p);
    FPeg_free_parser(p);
    return "\n";
}

int main() {

#ifdef WIN32
    // https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return GetLastError();
    }
#endif

    FMem_set_allocator(default_allocator());

    input_loop(">>>", tokparse);
    return 0;
}
