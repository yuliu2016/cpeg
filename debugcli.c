#include "include/internal/debugcli.h"
#include "stdio.h"
#include "string.h"

void input_loop(char *prompt, char *(*func)(char *)) {
    print(prompt);
    char line[1024];
    for (;;) {
        fgets(line, 1024, stdin);
        if (strcmp(line, "exit\n") == 0) {
            break;
        }
        // remove the newline character at the end
        for (int i = 0; i < 1024; ++i) {
            if (i && !line[i]) {
                line[i - 1] = 0;
            }
        }
        print(func(line));
        print(prompt);
    }
}

void print(char *s) {
    printf("%s", s);
}

void println(char *s) {
    printf("%s\n", s);
}