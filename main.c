#include "include/internal/mem_debug.h"
#include "include/ast.h"

#ifdef WIN32
#include "windows.h"
#endif

#include "stdio.h"
#include "string.h"
#include "time.h"


void *parse_grammar(parser_t *p, int entry_point);

double *parse_calc(parser_t *p);

token_t *lexer_get_next_token(lexer_t *ls);

void input_loop(char *prompt, char *(*func)(char *), int times);

void print(char *s);

void println(char *s);

char *tokenizer_repl(char *in);


static char *tokparse(char *in) {
    parser_t *p = parser_init_state(in, strlen(in), lexer_get_next_token);
    double *n = parse_calc(p);
    lexer_t *ls = &p->lexer_state;
    parser_verify_eof(p);

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
    } else {
        printf("Result: %lf\n", *n);
    }
    parser_free_state(p);
    return "\n";
}

static DWORD init_console() {
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
    printf("1 - parser\n0 - tokenizer\nMode:");
    char mode[10];
    fgets(mode, 10, stdin);
    return mode[0];
}

int main() {
    srand(time(NULL));
    init_console();
    int m = getmode();
    if (m == '1')
        input_loop(">>>", tokparse, -1);
    else if (m == '0')
        input_loop(">>>", tokenizer_repl, -1);
    else
        printf("Invalid mode\n");
    return 0;
}
