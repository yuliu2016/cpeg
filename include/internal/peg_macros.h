
#ifndef CPEG_PEG_MACROS_H
#define CPEG_PEG_MACROS_H

#include "../peg.h"


#define PEG_DEBUG

#ifdef PEG_DEBUG
#define IF_DEBUG(s) s
#else
# define IF_DEBUG(s)
#endif

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-macro-parentheses"

#define DEBUG_EXTRAS pos, f_type, f_name

#define ENTER_FRAME(p, type, name) \
    const int f_type = type; \
    IF_DEBUG(const char* f_name = name;) \
    size_t pos = p->pos; \
    IF_DEBUG(p->debug_hook->enter_frame(++p->level, DEBUG_EXTRAS);) \
    if (pos > p->max_reached_pos) { p->max_reached_pos = pos; }     \
    FAstNode *res = ((void *) 0) \

#define EXIT_FRAME(p) \
    IF_DEBUG(p->debug_hook->exit_frame(res, --p->level, DEBUG_EXTRAS);) \
    if (!res) { p->pos = pos; } \
    return res

#define RETURN_IF_MEMOIZED(p) \
    FTokenMemo *memo = FPeg_get_memo(p, f_type); \
    if (memo) { IF_DEBUG(p->debug_hook->memo_hit(--p->level, DEBUG_EXTRAS);) \
    return memo->node; } \

#define ENTER_LEFT_RECURSION(p) \
    void * max = res; \
    size_t lastpos = pos; \
    left_rec_enter: \
    FPeg_put_memo(p, f_type, max, lastpos); \
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

#define OPTIONAL_TOKEN(p, type, value) OPTIONAL(AST_CONSUME(p, type, value))

#define TEST(p, node) (node || (p->pos = pos, 0))

#define RULE(name) FAstNode *name(FPegParser *p)

// FAstNode \*[a-z0-9_]+\(FPegParser \*p\)
// RULE($1)

#pragma clang diagnostic pop



#endif //CPEG_PEG_MACROS_H
