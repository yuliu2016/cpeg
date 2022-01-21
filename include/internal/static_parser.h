#ifndef CPEG_STATIC_PARSER_G
#define CPEG_STATIC_PARSER_G

#include "../peg.h"

static parser_t _static_parser;

static inline size_t _pos() {
    return _static_parser.pos;
}

static inline void *palloc(size_t size) {
    return mballoc(_static_parser.region, size);
}

static inline int _enter_frame(const frame_t *f) {
    #ifdef PARSER_DEBUG
        parser_enter_debug(&_static_parser, f);
    #endif
    return parser_advance_frame(&_static_parser);
}

static inline void *_exit_frame(const frame_t *f, void *result) {
    _static_parser.level--;
    if (!result) {
        _static_parser.pos = f->f_pos;
    }
    #ifdef PARSER_DEBUG
        parser_exit_debug(&_static_parser, result, f);
    #endif
    return result;
}


static inline void _insert_memo(const frame_t *f, void *node) {
    parser_memoize(&_static_parser, f->f_pos, f->f_type, node);
}

static inline int _is_memoized(const frame_t *f, void **resptr) {
   token_memo_t *memo = parser_get_memo(&_static_parser, f->f_type);
    #ifdef PARSER_DEBUG
        parser_memo_debug(&_static_parser, memo, f);
    #endif
    if (memo) {
        *resptr = memo->node;
        return 1;
    }
    return 0;
}

static inline int _test_and_reset(size_t f_pos, void *node) {
    return node && (_static_parser.pos = f_pos, 1);
}

static inline token_t *_consume(int tk_type, const char *literal) {
    #ifdef PARSER_DEBUG
        return parser_consume_debug(&_static_parser, tk_type, literal);
    #else
        return parser_consume_token(&_static_parser, tk_type);
    #endif
}

#endif //CPEG_STATIC_PARSER_G
