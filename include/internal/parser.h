
#ifndef CPEG_PARSER_H
#define CPEG_PARSER_H

#include "../ast.h"


#define PEG_DEBUG

#ifdef PEG_DEBUG
#define IF_DEBUG(s) s
#else
# define IF_DEBUG(s)
#endif


#define DEBUG_EXTRAS f_type, __func__

#define F_MEMO (1 << 16u)
#define F_LR (1 << 20u)
#define F_ALLOW_SPACES (11 << 17u)
#define F_DISALLOW_SPACES (10 << 17u)
#define FUNC __func__

#define CURRENT_SPACE (1 << 19u)

typedef struct frame {
    size_t f_type;
    size_t f_pos;
    const char *f_rule;
    void *memo;
    size_t flags;
} frame_t;

static inline int enter(FParser *p, frame_t *f, int memoize) {
    if (FPeg_is_done(p)) {
        return 0;
    }

    IF_DEBUG(FPeg_debug_enter(p, f->f_type, f->f_rule);)

    if (f->flags & F_MEMO || f->flags & F_LR) {
        FTokenMemo *memo = FPeg_get_memo(p, f->f_type);
        IF_DEBUG(FPeg_debug_memo(p, memo, f->f_type, f->f_rule);)
        if (memo) { 
            f->memo = memo->node;
            return 0;
        }
    }


    if (f->flags & F_ALLOW_SPACES) {
        f->flags |= p->ignore_whitespace & F_ALLOW_SPACES;
        p->ignore_whitespace = 1;
    }

    if (f->flags & F_ALLOW_SPACES) {
        f->flags |= p->ignore_whitespace & F_ALLOW_SPACES;
        p->ignore_whitespace = 0;
    }

    return 1;
}


static inline void *exit(FParser *p, frame_t *f, FAstNode *result) {

    IF_DEBUG(FPeg_debug_exit(p, result, f->f_type, f->f_rule);)

    if (f->memo) {
        return f->memo;
    }

    if (f->flags & F_ALLOW_SPACES | f->flags & F_DISALLOW_SPACES) {
        p->ignore_whitespace = !!(f->flags & F_ALLOW_SPACES);
    }

    if (f->flags & F_MEMO || f->flags & F_LR) {
        FPeg_put_memo(p, f->f_pos, f->f_type, result, p->pos);
    }

    if (!result) { 
        p->pos = f->f_pos;
    }

    return result;
}

static inline void memoize(FParser *p, frame_t *f, void *node, size_t endpos) {
    FPeg_put_memo(p, f->f_pos, f->f_type, node, endpos);
}

static inline int test_and_reset(FParser *p, frame_t *f, void *node) {
    return node && (p->pos = f->f_pos, 1);
}


static inline FAstNode *consume(FParser *p, size_t type, const char *literal) {
    return FPeg_consume_token_and_debug(p, type, literal);
}


static inline FAstNode *node_0(FParser *p, frame_t *f) {
    return FAst_new_node(p, f->f_type, 0);
}

static inline FAstNode *node_1(FParser *p, frame_t *f, FAstNode *a) {
    return FAst_new_node(p, f->f_type, 1, a);
}

static inline FAstNode *node_2(FParser *p, frame_t *f, FAstNode *a , FAstNode *b) {
    return FAst_new_node(p, f->f_type, 2, a, b);
}

static inline FAstNode *node_3(FParser *p, frame_t *f, FAstNode *a, FAstNode *b, FAstNode *c) {
    return FAst_new_node(p, f->f_type, 3, a, b, c);
}

static inline FAstNode *node_4(FParser *p, frame_t *f, FAstNode *a, FAstNode *b, FAstNode *c, FAstNode *d) {
    return FAst_new_node(p, f->f_type, 4, a, b, c, d);
}


#endif //CPEG_PARSER_H
