
#ifndef CPEG_PARSER_H
#define CPEG_PARSER_H

#include "../ast.h"


#ifndef PEG_NODEBUG
#define PEG_DEBUG
#endif

#ifdef PEG_DEBUG
#define IF_DEBUG(s) s
#else
# define IF_DEBUG(s)
#endif


#define FUNC __func__

typedef struct frame {
    size_t f_type;
    size_t f_pos;
    const char *f_rule;
    void *memo;
    int memoize;
} frame_t;

static inline int enter_frame(parser_t *p, frame_t *f) {

    IF_DEBUG(FPeg_debug_enter(p, f->f_type, f->f_rule);)

    if (FPeg_is_done(p)) {
        return 0;
    }

    if (f->memoize) {
        FTokenMemo *memo = FPeg_get_memo(p, f->f_type);
        IF_DEBUG(FPeg_debug_memo(p, memo, f->f_type, f->f_rule);)
        if (memo) { 
            f->memo = memo->node;
            return 0;
        }
    }

    return 1;
}


static inline void *exit_frame(parser_t *p, frame_t *f, void *result) {

    IF_DEBUG(FPeg_debug_exit(p, result, f->f_type, f->f_rule);)

    if (f->memo) {
        return f->memo;
    }

    if (f->memoize) {
        FPeg_put_memo(p, f->f_pos, f->f_type, result, p->pos);
    }

    if (!result) { 
        p->pos = f->f_pos;
    }

    return result;
}

static inline void memoize(parser_t *p, frame_t *f, void *node, size_t endpos) {
    FPeg_put_memo(p, f->f_pos, f->f_type, node, endpos);
}

static inline int test_and_reset(parser_t *p, frame_t *f, void *node) {
    return node && (p->pos = f->f_pos, 1);
}


static inline token_t *consume(parser_t *p, size_t type, const char *literal) {

#ifdef PEG_DEBUG
    return FPeg_consume_token_and_debug(p, type, literal);
#else
    return FPeg_consume_token(p, type);
#endif

}

#endif //CPEG_PARSER_H
