#include "include/internal/mem_debug.h"
#include "include/ast.h"

#ifdef WIN32
#include "windows.h"
#endif

#include "stdio.h"
#include "string.h"
#include "time.h"


void input_loop(char *prompt, char *(*func)(char *), int times);

char *tokenizer_repl(char *in);

char *calc_repl(char *in);


static unsigned long init_console() {
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
    return 0;
}

int getmode() {
    printf("\033[32mcpeg (%s, %s)\033[0m\n", __DATE__, __TIME__);
    printf("1 - parser\n0 - tokenizer\nMode: ");
    char mode[10];
    fgets(mode, 10, stdin);
    return mode[0];
}

int main() {
    srand(time(NULL));
    init_console();
    int m = getmode();
    if (m == '1')
        input_loop(">>> ", calc_repl, -1);
    else if (m == '0')
        input_loop(">>> ", tokenizer_repl, -1);
    else
        printf("Invalid mode\n");
    return 0;
}
