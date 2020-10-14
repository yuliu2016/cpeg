#include "include/internal/mem_debug.h"
#include "include/internal/debugcli.h"
#include "include/tokenizer.h"
#include "include/parser.h"

#ifdef WIN32
#include "windows.h"
#endif

char *idchptr(char *in) {
    return in;
}

void *parse() {
    FParser *p = FPeg_init_new_parser(0, 0, FLexer_get_next_token, 0);
    return single_input(p);
}

#include "stdio.h"

char *tokenizer_repl(char *in) {
    FLexerState *ls = FLexer_analyze_all(in);
    if (ls->error) {
        printf("\033[31mFile <repl>, %s\033[0m", ls->error);
        FLexer_free_state(ls);
        return "\n";
    }

    printf("# of tokens: %zu\n", ls->token_len);
    for (int i = 0; i < ls->token_len; ++i) {
        FToken *token = ls->tokens[i];
        char literal[100];
        for (int j = 0; j < 100; ++j) {
            literal[j] = 0;
        }
        for (size_t j = 0; j < token->len; ++j) {
            char ch = token->start[j];
            if (ch == '\n') {
                literal[j++] = '\\';
                literal[j] = 'n';
            } else {
                literal[j] = ch;
            }
        }
        printf("T(type=%d, len=%zu, '%s')\n", token->type, token->len, literal);
    }

    FLexer_free_state(ls);
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

    input_loop(">>>", tokenizer_repl);
    return 0;
}
