
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

#define PEG_DEBUG

#ifdef PEG_DEBUG
#define IF_DEBUG(s) s
#else
# define IF_DEBUG(s)
#endif

#define ENTER_FRAME_D(p) \
    p->level++; \
    p->debug_hook->enter_frame(p->level, p->pos, f_type, f_name) \

#define ENTER_FRAME_X(p, type, name) \
    const int f_type = type; \
    const char* f_name = name; \
    IF_DEBUG(ENTER_FRAME_D(p)); \
    if (p->pos > p->max_reached_pos) { \
    p->max_reached_pos = p->pos; \
    }\
    size_t pos = p->pos \

#define EXIT_FRAME_D(p) \
    p->level--; \
    p->debug_hook->exit_frame(res, p->level, p->pos, f_type, f_name); \

#define EXIT_FRAME_X(p) \
    IF_DEBUG(EXIT_FRAME_D(p)) \
    if (!res) \
        p->pos = pos

#define RETURN_IF_MEMOIZED(p) \
    FTokenMemo *memo = FPeg_get_memo(p, f_type); \
    if (memo) { \
    IF_DEBUG(p->level--;) \
    IF_DEBUG(p->debug_hook->memo_hit(p->level, pos, f_type, f_name);) \
    void *node = memo->node; \
    if (node) { \
        p->pos = memo->end_pos;\
    }\
    return node; \
    } else goto no_memo; \
    no_memo: \

#define PUT_MEMO(p, type, node, end) FPeg_put_memo(p, type, node, end)

#define ENTER_LEFT_RECURSION(p) \
    void * max = res; \
    size_t lastpos = pos; \
    left_rec_enter: \
    PUT_MEMO(p, f_type, max, lastpos); \
    p->pos = pos

#define EXIT_LEFT_RECURSION(p) \
    size_t end_pos = p->pos; \
    if (end_pos <= lastpos) { goto left_rec_exit; }\
    lastpos = end_pos; \
    max = res; \
    goto left_rec_enter; \
    left_rec_exit: \
    res = max \

#define OPTIONAL(node) node, 1

#define TEST_MATCH(p, node) node || (p->pos = pos, 0)

#define TEST_NO_MATCH(p, node) !(node || (p->pos = pos, 0))

#define GET_CURR_TOKEN(p) p->tokens[p->pos]

#define PARSER_ALLOC(p, size) FMemRegion_malloc(p->region, size)

#ifdef PEG_DEBUG
#define CONSUME_TOKEN(p, type, value) FPeg_consume_token_debug(p, type, value)
#else
#define CONSUME_TOKEN(p, type, value) FPeg_consume_token(p, type)
#endif

#define LIST_NEW() FPeg_new_list()

#define LIST_APPEND(list, item) FPeg_list_append(list, item)

#define LIST_GET(list, index) list->items[index]

#define LIST_LENGTH(list) list->len

FPegParser *FPeg_new_parser(FMemRegion *region, FTokenArray *a, FPegDebugHook *dh);

FToken *FPeg_consume_token(FPegParser *p, int type);

FToken *FPeg_consume_token_debug(FPegParser *p, int type, char *literal);

FTokenMemo *FPeg_new_memo(FPegParser *p, int type, void *node, int end);

void FPeg_put_memo(FPegParser *p, int type, void *node, int end);

FTokenMemo *FPeg_get_memo(FPegParser *p, int type);

FPegList *FPeg_new_list();

void FPeg_list_append(FPegList *list, void *item);


#endif //CPEG_PEG_H
