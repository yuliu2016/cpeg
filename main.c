#include "include/internal/mem_debug.h"
#include "include/internal/debugcli.h"
#include "include/tokenizer.h"
#include "include/ast.h"

#ifdef WIN32
#include "windows.h"
#endif

#include "stdio.h"
#include "string.h"


char *tokparse(char *in) {
    FParser *p = FPeg_init_new_parser(in, strlen(in), FLexer_get_next_token);
    FAstNode *n = parse_calc(p);
    FLexerState *ls = &p->lexer_state;
    if (p->error) {
        printf("======================\n\033[31;1m");
        printf("parser error: %s\n\033[0m", p->error);
        printf("======================");
    } else if (ls->error) {
        printf("======================\n\033[31;1m");
        printf("lexer error: %s\n\033[0m", ls->error);
        printf("======================");
    } else if (!n) {
        printf("======================\n\033[31;1m");
        printf("Not a valid parse tree\n\033[0m");
        printf("======================");
    } else if (!(p->pos >= ls->token_len && !ls->next_token)) {
        printf("=====================\n\033[31;1m");
        printf("Not all tokens parsed\n\033[0m");
        printf("=====================");
    }
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

    printf(">>>");
    char line[1024];

    fgets(line, 1024, stdin);
    if (strlen(line) == 0) {
        return 1;
    }
    if (strcmp(line, "exit\n") == 0) {
        return 1;
    }
    // remove the newline character at the end
    line[strlen(line) - 1] = 0;
    char *s = tokparse(line);
    if (!s) {
        return 1;
    }
    print(s);

    return 0;
}
