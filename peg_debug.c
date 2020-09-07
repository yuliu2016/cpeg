#include "include/internal/peg_debug.h"
#include "stdio.h"

void print_indent_level(size_t s) {
    char *b = FMem_malloc(sizeof(char) * (s + 1));
    if (!b) {
        return;
    }
    for (size_t i = 0; i < s; ++i) {
        b[i] = ' ';
    }
    b[s] = '\0';
    printf("%s", b);
    FMem_free(b);
}

void enter_frame(size_t level, size_t pos, size_t rule_index, const char *rule_name) {
    print_indent_level(level);
    printf("Entering frame %zu:%s at pos %zu", rule_index, rule_name, pos);
}

void memo_hit(size_t level, size_t pos, size_t rule_index, const char *rule_name) {
    print_indent_level(level);
    printf("Memo found in frame %zu:%s at pos %zu", rule_index, rule_name, pos);
}

void exit_frame(FAstNode *res, size_t level, size_t pos, size_t rule_index, const char *rule_name) {
    print_indent_level(level);
    if (res) {
        printf("Success in frame %zu:%s at pos %zu", rule_index, rule_name, pos);
    } else {
        printf("Failure in frame %zu:%s at pos %zu", rule_index, rule_name, pos);
    }
}

FPegDebugHook FPeg_print_debug_hook() {
    return (FPegDebugHook) {enter_frame, memo_hit, exit_frame};
}