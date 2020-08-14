#include "include/internal/debugcli.h"
#include "stdio.h"
#include "string.h"

void input_loop(char *prompt, char *(*func)(char *)) {
    print(prompt);
    char line[1024];
    for (;;) {
        fgets(line, 1024, stdin);
        if (strcmp(line, "exit") == 0) {
            break;
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