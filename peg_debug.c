#include "peg_debug.h"
#include "stdio.h"

void print_indent_level(size_t s) {
    char *b = FMem_malloc(sizeof(char) * (s + 1));
    if (!b) {
        return;
    }
    for (int i = 0; i < s; ++i) {
        b[i] = ' ';
    }
    b[s] = '\0';
    printf("%s", b);
    FMem_free(b);
}

void enter_frame(int level, int pos, int rule_index, const char *rule_name) {
    print_indent_level(level);
    printf("Entering frame %d:%s at pos %d", rule_index, rule_name, pos);
}

void memo_hit(int level, int pos, int rule_index, const char *rule_name) {
    print_indent_level(level);
    printf("Memo found in frame %d:%s at pos %d", rule_index, rule_name, pos);
}

void exit_frame(void *res, int level, int pos, int rule_index, const char *rule_name) {
    print_indent_level(level);
    if (res) {
        printf("Success in frame %d:%s at pos %d", rule_index, rule_name, pos);
    } else {
        printf("Failure in frame %d:%s at pos %d", rule_index, rule_name, pos);
    }
}

void mark_token(void *res, int level, int expected, int actual) {
    print_indent_level(level);
    if (res) {
        printf("Success in token %d", actual);
    } else {
        printf("Failure in token %d, expecting %d", actual, expected);
    }
}

FPegDebugHook FPeg_print_debug_hook = {enter_frame, memo_hit, exit_frame, mark_token};