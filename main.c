#include "include/internal/mem_debug.h"
#include "include/internal/debugcli.h"
#include "include/tokenizer.h"
#include "include/parser.h"

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
    printf("# of tokens: %zu, error: %s\n", ls->token_len, ls->error);
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
    FMem_set_allocator(default_allocator());
    test_region();

    input_loop(">>>", tokenizer_repl);
    return 0;
}
