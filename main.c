#include "include/internal/mem_debug.h"
#include "include/internal/debugcli.h"
#include "include/ast.h"

#ifdef WIN32
#include "windows.h"
#endif

#include "stdio.h"
#include "string.h"


void *parse_grammar(parser_t *p, int entry_point);

double *parse_calc(parser_t *p);

token_t *lexer_get_next_token(lexer_t *ls);


char *tokparse(char *in) {
    parser_t *p = parser_init_state(in, strlen(in), lexer_get_next_token);
    double *n = parse_calc(p);
    lexer_t *ls = &p->lexer_state;
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
    } else {
        printf("Result: %lf\n", *n);
    }
    parser_free_state(p);
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

#define MAIN_LOOP
#ifdef MAIN_LOOP
    input_loop(">>>", tokparse);
#else

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
#endif

    return 0;
}
