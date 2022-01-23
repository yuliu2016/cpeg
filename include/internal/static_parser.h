#ifndef CPEG_STATIC_PARSER_G
#define CPEG_STATIC_PARSER_G

#include "../peg.h"

static parser_t __p;

#define p (&__p)

static inline size_t pos() {
    return __p.pos;
}

static inline void restore(size_t pos) {
    __p.pos = pos;
}

static inline void *palloc(size_t size) {
    return mballoc(__p.region, size);
}

static inline int enter_frame(const char *f_rule) {
    #ifdef PARSER_DEBUG
        parser_enter_debug(p, f_rule);
    #endif
    return __p.errorcode == 0;
}

static inline void *exit_frame(size_t f_pos, void *result, const char *f_rule) {
    if (!result) {
        __p.pos = f_pos;
    }
    #ifdef PARSER_DEBUG
        parser_exit_debug(p, result, f_rule);
    #endif
    return result;
}


static inline void insert_memo(size_t f_pos, int f_type, void *node) {
    parser_memoize(p, f_pos, f_type, node);
}

static inline memo_t *fetch_memo(int f_type, const char *f_rule) {
    memo_t *memo = parser_get_memo(p, f_type);
    #ifdef PARSER_DEBUG
        parser_memo_debug(p, memo, f_rule);
    #endif
    return memo;
}

static inline int is_memoized(int f_type, void **resptr, const char *f_rule) {
   memo_t *memo = parser_get_memo(p, f_type);
    #ifdef PARSER_DEBUG
        parser_memo_debug(p, memo, f_rule);
    #endif
    if (memo) {
        *resptr = memo->node;
        return 1;
    }
    return 0;
}

static inline int test_and_reset(size_t f_pos, void *node) {
    return node && (__p.pos = f_pos, 1);
}


static inline token_t *consume(int tk_type, const char *literal) {
    size_t _pos = pos();
    if (__p.fast_match[_pos] == tk_type) {
        #ifdef PARSER_DEBUG
            parser_matched_debug(p, literal);
        #endif
        __p.pos += 1;
        return parser_fetch_token(p, _pos);
    } else {
        #ifdef PARSER_DEBUG
            parser_mismatch_debug(p, literal);
        #endif
        return 0;
    }
}

static inline ast_list_t *ast_list_new() {
    return mblist_new(__p.region, 0);
}

static inline ast_list_t *ast_list_of(void *first) {
    ast_list_t *seq = mblist_new(__p.region, 1);
    mblist_append(__p.region, seq, first);
    return seq;
}


static inline void ast_list_append(ast_list_t *seq, void *item) {
    mblist_append(__p.region, seq, item);
}

#undef p
#define __parser __p

#endif //CPEG_STATIC_PARSER_G
