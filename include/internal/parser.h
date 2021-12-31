
#ifndef CPEG_PARSER_H
#define CPEG_PARSER_H

#include "../ast.h"


#ifndef PEG_NODEBUG
// #define PEG_DEBUG
#endif

#ifdef PEG_DEBUG
#define IF_DEBUG(s) s
#else
# define IF_DEBUG(s)
#endif


#define FUNC __func__


static inline int enter_frame(parser_t *p, frame_t *f) {

    IF_DEBUG(parser_enter_debug(p, f);)

    if (parser_check_exit(p)) {
        return 0;
    }

    if (f->memoize) {
        token_memo_t *memo = parser_get_memo(p, f->f_type);
        IF_DEBUG(parser_memo_debug(p, memo, f);)
        if (memo) { 
            f->memo = memo->node;
            return 0;
        }
    }

    return 1;
}


static inline void *exit_frame(parser_t *p, frame_t *f, void *result) {

    IF_DEBUG(parser_exit_debug(p, result, f);)

    if (f->memo) {
        return f->memo;
    }

    if (f->memoize) {
        parser_memoize(p, f->f_pos, f->f_type, result, p->pos);
    }

    if (!result) { 
        p->pos = f->f_pos;
    }

    return result;
}

static inline void memoize(parser_t *p, frame_t *f, void *node, size_t endpos) {
    parser_memoize(p, f->f_pos, f->f_type, node, endpos);
}

static inline int test_and_reset(parser_t *p, frame_t *f, void *node) {
    return node && (p->pos = f->f_pos, 1);
}


static inline token_t *consume(parser_t *p, int tk_type, const char *literal) {

#ifdef PEG_DEBUG
    return parser_consume_debug(p, tk_type, literal);
#else
    return parser_consume_token(p, tk_type);
#endif

}

#endif //CPEG_PARSER_H
