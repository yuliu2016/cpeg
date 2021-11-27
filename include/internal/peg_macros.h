
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
    if (FPeg_is_done(p)) { return 0; } \
    const size_t f_type = type; \
    size_t pos = p->pos; \
    IF_DEBUG(FPeg_debug_enter(p, DEBUG_EXTRAS);) \
    FAstNode *r = 0, *a = 0, *b = 0, *c = 0, *d = 0

typedef struct frame {
    size_t f_type;
    size_t f_initial_pos;
    IF_DEBUG(char *f_rule_name;)
    void *memo;
} frame_t;

static inline frame_t enter(FParser *p, size_t f_type, char *rule_name) {
    frame_t f;
    f.f_type = f_type;
    IF_DEBUG(f.f_rule_name = rule_name;)
    f.f_initial_pos = p->pos;
    if (FPeg_is_done(p)) {
        f.memo = 1;
    } else {
        f.memo = 0;
    }
    return f;
}

#define FUNC __func__

#define EXIT() \
    IF_DEBUG(FPeg_debug_exit(p, r, DEBUG_EXTRAS);) \
    if (!r) { p->pos = pos; } \
    return r

static inline void exit(FParser *p, frame_t *f, FAstNode *r) {
    //  IF_DEBUG(FPeg_debug_exit(p, r, DEBUG_EXTRAS);)
    IF_DEBUG(FPeg_debug_exit(p, r, 0, 0);)
    if (!r) { p->pos = f->f_initial_pos; } 
}

#define RETURN_IF_MEMOIZED() \
    FTokenMemo *memo = FPeg_get_memo(p, f_type); \
    IF_DEBUG(FPeg_debug_memo(p, memo, DEBUG_EXTRAS);) \
    if (memo) { return memo->node; }

#define MEMOIZE() \
    FPeg_put_memo(p, pos, f_type, r, p->pos)

#define ENTER_LEFT_RECURSION() \
    FAstNode *max_node = 0; \
    a = 0; \
    size_t max_end_pos = pos; \
    \
    parse_with_memo: \
    FPeg_put_memo(p, pos, f_type, max_node, max_end_pos); \
    p->pos = pos

#define EXIT_LEFT_RECURSION() \
    size_t end_pos = p->pos; \
    if (end_pos <= max_end_pos) { goto max_reached; }\
    max_end_pos = end_pos; \
    max_node = a; \
    goto parse_with_memo; \
    \
    max_reached: \
    p->pos = max_end_pos; \
    r = max_node ? AST_NEW_NODE(p, f_type, 1, max_node) : 0

#define WS_PUSH_1() \
    int old_ws = p->ignore_whitespace; \
    p->ignore_whitespace = 1;

#define WS_PUSH_0() \
    int old_ws = p->ignore_whitespace; \
    p->ignore_whitespace = 0;

#define WS_POP() \
    p->ignore_whitespace = old_ws;


#define TEST(node) (node || (p->pos = pos, 0))


static inline FAstNode *consume(FParser *p, size_t type, const char *literal) {
    return FPeg_consume_token_and_debug(p, type, literal);
}

static inline FAstNode *sequence(FParser *p, size_t type, int allow_empty) {
    if (allow_empty) {
        return FPeg_parse_sequece_or_none(p, type);
    } else {
        return FPeg_parse_sequence(p, type);
    }
}

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
