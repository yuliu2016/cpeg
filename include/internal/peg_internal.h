#ifndef CPEG_PEG_INTERNAL_H
#define CPEG_PEG_INTERNAL_H

#include "../peg.h"


#define PEG_DEBUG

#ifdef PEG_DEBUG
#define IF_DEBUG(s) s
#else
# define IF_DEBUG(s)
#endif

#define DEBUG_EXTRAS pos, f_type, f_name

#define ENTER_FRAME_X(p, type, name) \
    const int f_type = type; \
    const char* f_name = name; \
    size_t pos = p->pos; \
    IF_DEBUG(p->debug_hook->enter_frame(++p->level, DEBUG_EXTRAS);) \
    if (pos > p->max_reached_pos) { p->max_reached_pos = pos; } \

#define EXIT_FRAME_X(p) \
    IF_DEBUG(p->debug_hook->exit_frame(res, --p->level, DEBUG_EXTRAS);) \
    if (!res) { p->pos = pos; }

#define GET_MEMO(p, type) FPeg_get_memo(p, f_type)

#define RETURN_IF_MEMOIZED(p) \
    FTokenMemo *memo = GET_MEMO(p, f_type); \
    if (memo) { IF_DEBUG(p->debug_hook->memo_hit(--p->level, DEBUG_EXTRAS);) \
    return memo->node; } \

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

#ifdef PEG_DEBUG
#define CONSUME_TOKEN_X(p, type, value) FPeg_consume_token_debug(p, type, value)
#else
#define CONSUME_TOKEN_X(p, type, value) FPeg_consume_token(p, type)
#endif

#define LIST_NEW() FPeg_new_list()

#define LIST_APPEND(list, item) FPeg_list_append(list, item)

#define LIST_GET(list, index) list->items[index]

#define LIST_LENGTH(list) list->len


#endif //CPEG_PEG_INTERNAL_H
