#include "include/internal/mem_debug.h"
#include "include/internal/debugcli.h"
#include "include/tokenizer.h"
#include "include/parser.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
char *idchptr(char *in) {
    return in;
}

void *parse() {
    FParser *p = FPeg_init_new_parser(0, 0, FLexer_get_next_token, 0);
    return single_input(p);
}

char *tokenizer_repl(char *in) {
    FLexerState *ls = FLexer_analyze_all(in);
    return "\n";
}

#pragma clang diagnostic pop

int main() {
    FMem_set_allocator(default_allocator());
    test_region();

    input_loop(">>>", tokenizer_repl);
    return 0;
}
