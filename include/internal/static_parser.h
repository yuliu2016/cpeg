#ifndef CPEG_STATIC_PARSER_G
#define CPEG_STATIC_PARSER_G

#include "../peg.h"

static parser_t __parser;

static inline size_t pos() {
    return __parser.pos;
}

static inline void setpos(size_t pos) {
    __parser.pos = pos;
}

static inline void *palloc(size_t size) {
    return mballoc(__parser.region, size);
}

static inline int enter_frame(const frame_t *f) {
    #ifdef PARSER_DEBUG
        parser_enter_debug(&__parser, f);
    #endif
    return parser_advance_frame(&__parser);
}

static inline void *exit_frame(const frame_t *f, void *result) {
    __parser.level--;
    if (!result) {
        __parser.pos = f->f_pos;
    }
    #ifdef PARSER_DEBUG
        parser_exit_debug(&__parser, result, f);
    #endif
    return result;
}


static inline void insert_memo(const frame_t *f, void *node) {
    parser_memoize(&__parser, f->f_pos, f->f_type, node);
}

static inline int is_memoized(const frame_t *f, void **resptr) {
   token_memo_t *memo = parser_get_memo(&__parser, f->f_type);
    #ifdef PARSER_DEBUG
        parser_memo_debug(&__parser, memo, f);
    #endif
    if (memo) {
        *resptr = memo->node;
        return 1;
    }
    return 0;
}

static inline int test_and_reset(size_t f_pos, void *node) {
    return node && (__parser.pos = f_pos, 1);
}

static inline token_t *consume(int tk_type, const char *literal) {
    #ifdef PARSER_DEBUG
        return parser_consume_debug(&__parser, tk_type, literal);
    #else
        return parser_consume_token(&__parser, tk_type);
    #endif
}

static inline ast_list_t *ast_list_new() {
    return mblist_new(__parser.region, 0);
}

static inline ast_list_t *ast_list_of(void *first) {
    ast_list_t *seq = mblist_new(__parser.region, 1);
    mblist_append(__parser.region, seq, first);
    return seq;
}


static inline void ast_list_append(ast_list_t *seq, void *item) {
    mblist_append(__parser.region, seq, item);
}

#endif //CPEG_STATIC_PARSER_G
