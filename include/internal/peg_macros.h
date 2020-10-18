
#ifndef CPEG_PEG_MACROS_H
#define CPEG_PEG_MACROS_H

#include "../peg.h"


#define PEG_DEBUG

#ifdef PEG_DEBUG
#define IF_DEBUG(s) s
#else
# define IF_DEBUG(s)
#endif


#define DEBUG_EXTRAS f_type, __func__

#define ENTER(type) \
    if (p->error) { return 0; } \
    const size_t f_type = type; \
    size_t pos = p->pos; \
    IF_DEBUG(FPeg_debug_enter(p, DEBUG_EXTRAS);) \
    if (pos > p->max_reached_pos) { p->max_reached_pos = pos; }     \
    FAstNode *r = 0, *a = 0, *b = 0, *c = 0, *d = 0

#define EXIT() \
    IF_DEBUG(FPeg_debug_exit(p, r, DEBUG_EXTRAS);) \
    if (!r) { p->pos = pos; } \
    return r

#define RETURN_IF_MEMOIZED() \
    FTokenMemo *memo = FPeg_get_memo(p, f_type); \
    IF_DEBUG(FPeg_debug_memo(p, memo, DEBUG_EXTRAS);) \
    if (memo) { return memo->node; }

#define MEMOIZE() \
    FPeg_put_memo(p, pos, f_type, r, p->pos)

#define ENTER_LEFT_RECURSION() \
    FAstNode *max = 0; \
    a = 0; \
    size_t lastpos = pos; \
    left_rec_enter: \
    FPeg_put_memo(p, pos, f_type, max, lastpos); \
    p->pos = pos

#define EXIT_LEFT_RECURSION() \
    size_t end_pos = p->pos; \
    if (end_pos <= lastpos) { goto left_rec_exit; }\
    lastpos = end_pos; \
    max = a; \
    goto left_rec_enter; \
    left_rec_exit: \
    p->pos = lastpos; \
    r = max ? AST_NEW_NODE(p, f_type, 1, max) : 0

#define WS_PUSH_1() \
    int old_ws = p->ignore_whitespace; \
    p->ignore_whitespace = 1;

#define WS_PUSH_0() \
    int old_ws = p->ignore_whitespace; \
    p->ignore_whitespace = 0;

#define WS_POP() \
    p->ignore_whitespace = old_ws;

#define OPT(node) node, 1

#define TEST(node) (node || (p->pos = pos, 0))

#ifdef PEG_DEBUG
#define TOKEN(type, value) FPeg_consume_token_and_debug(p, type, value)
#else
#define TOKEN(type, value) FPeg_consume_token(p, type)
#endif

#define SEQ_OR_NONE(p, rule) \
    FPeg_parse_sequece_or_none(p, rule)

#define SEQUENCE(p, rule) \
    FPeg_parse_sequence(p, rule)

#define DELIMITED(p, delimiter, literal, rule) \
    FPeg_parse_delimited(p, delimiter, rule)

#define TOKEN_SEQ_OR_NONE(p, t, v) \
    FPeg_parse_token_sequence_or_none(p, t)

#define TOKEN_SEQUENCE(p, t, v) \
    FPeg_parse_token_sequence(p, t)

#define TOKEN_DELIMITED(p, delimiter, literal, t, v) \
    FPeg_parse_token_delimited(p, delimiter, t)


#define AST_NEW_NODE(p, t, nargs, ...) FAst_new_node(p, t, nargs, __VA_ARGS__)
#define NODE_1() AST_NEW_NODE(p, f_type, 1, a)
#define NODE_2() AST_NEW_NODE(p, f_type, 2, a, b)
#define NODE_3() AST_NEW_NODE(p, f_type, 3, a, b, c)
#define NODE_4() AST_NEW_NODE(p, f_type, 4, a, b, c, d)

// FAstNode \*[a-z0-9_]+\(FParser \*p\)
// RULE($1)


#endif //CPEG_PEG_MACROS_H
