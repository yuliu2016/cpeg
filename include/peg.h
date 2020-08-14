
#ifndef CPEG_PEG_H
#define CPEG_PEG_H

#include "mem.h"
#include "token.h"

/**
 * PEG parse tree implementation
 * Source of implementation algorithms:
 * https://github.com/python/cpython/blob/master/Grammar/python.gram
 * https://medium.com/@gvanrossum_83706/left-recursive-peg-grammars-65dab3c580e1
 * https://www.python.org/dev/peps/pep-0617/
 * https://github.com/PhilippeSigaud/Pegged/wiki/Left-Recursion
 */

typedef struct peg_debug_hook_t {
    void (*enter_frame)(int level, int pos, int rule_index, const char *rule_name);

    void (*memo_hit)(int level, int pos, int rule_index, const char *rule_name);

    void (*exit_frame)(void *res, int level, int pos, int rule_index, const char *rule_name);

    void (*mark_token)(void *res, int level, int expected, int actual, const char *literal);
} FPegDebugHook;

typedef struct peg_list_t {
    size_t len;
    size_t capacity;
    void **items;
} FPegList;

typedef struct peg_parser_t {
    size_t pos;
    size_t max_reached_pos;
    size_t level;
    FToken **tokens;
    size_t token_len;
    FPegDebugHook *debug_hook;
    FMemRegion *region;
} FPegParser;

#define GET_CURR_TOKEN(p) p->tokens[p->pos]

#define PARSER_ALLOC(p, size) FMemRegion_malloc(p->region, size)

FPegParser *FPeg_new_parser(FMemRegion *region, FTokenArray *a, FPegDebugHook *dh);

FToken *FPeg_consume_token(FPegParser *p, int type);

FToken *FPeg_consume_token_debug(FPegParser *p, int type, char *literal);

FTokenMemo *FPeg_new_memo(FPegParser *p, int type, void *node, int end);

void FPeg_put_memo(FPegParser *p, int type, void *node, int end);

FTokenMemo *FPeg_get_memo(FPegParser *p, int type);

FPegList *FPeg_new_list();

void FPeg_list_append(FPegList *list, void *item);


#endif //CPEG_PEG_H
