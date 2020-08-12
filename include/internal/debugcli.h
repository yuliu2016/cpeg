#ifndef CPEG_DEBUGCLI_H
#define CPEG_DEBUGCLI_H

void input_loop(char *prompt, char *(*func)(char *));

void print(char *s);

void println(char *s);

#endif //CPEG_DEBUGCLI_H
