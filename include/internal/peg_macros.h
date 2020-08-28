
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

#define DEBUG_EXTRAS f_type, f_name

#define ENTER_FRAME(p, type, name) \
    const int f_type = type; \
    IF_DEBUG(const char* f_name = name;) \
    size_t pos = p->pos; \
    IF_DEBUG(p->debug_hook->enter_frame(++p->level, pos, DEBUG_EXTRAS);) \
    if (pos > p->max_reached_pos) { p->max_reached_pos = pos; }     \
    FAstNode *r = 0, *a, *b, *c, *d \

#define EXIT_FRAME(p) \
    IF_DEBUG(p->debug_hook->exit_frame(r, --p->level, p->pos, DEBUG_EXTRAS);) \
    if (!r) { p->pos = pos; } \
    return r

#define RETURN_IF_MEMOIZED(p) \
    FTokenMemo *memo = FPeg_get_memo(p, f_type); \
    if (memo) { IF_DEBUG(p->debug_hook->memo_hit(--p->level, pos, DEBUG_EXTRAS);) \
    return memo->node; } \

#define ENTER_LEFT_RECURSION(p) \
    FAstNode *max = 0; \
    a = 0; \
    size_t lastpos = pos; \
    left_rec_enter: \
    FPeg_put_memo(p, f_type, max, lastpos); \
    p->pos = pos

#define EXIT_LEFT_RECURSION(p) \
    size_t end_pos = p->pos; \
    if (end_pos <= lastpos) { goto left_rec_exit; }\
    lastpos = end_pos; \
    max = a; \
    goto left_rec_enter; \
    left_rec_exit: \
    r = max ? AST_NEW_NODE(p, f_type, 1, max) : 0 \

#define OPTIONAL(node) node, 1

#define TEST(p, node) (node || (p->pos = pos, 0))

#define TOKEN(p, type, value) AST_CONSUME(p, type, value)

#define NODE_1(p, a) AST_NEW_NODE(p, f_type, 1, a)
#define NODE_2(p, a, b) AST_NEW_NODE(p, f_type, 2, a, b)
#define NODE_3(p, a, b, c) AST_NEW_NODE(p, f_type, 3, a, b, c)
#define NODE_4(p, a, b, c, d) AST_NEW_NODE(p, f_type, 4, a, b, c, d)

// FAstNode \*[a-z0-9_]+\(FPegParser \*p\)
// RULE($1)

#pragma clang diagnostic pop



#endif //CPEG_PEG_MACROS_H
