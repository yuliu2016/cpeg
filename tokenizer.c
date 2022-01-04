#include "include/peg.h"
#include "include/internal/tokenmap.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"


static inline int _has_remaining(lexer_t *ls) {
    return ls->curr_index < ls->src_len;
}

static inline char _peek(lexer_t *ls) {
    return ls->src[ls->curr_index];
}

static inline char _peek_safe(lexer_t *ls, size_t i) {
    if (i < ls->src_len) {
        return ls->src[i];
    } else {
        return 0;
    }
}

static inline char _peek_next(lexer_t *ls, size_t n) {
    return _peek_safe(ls, ls->curr_index + n);
}

static inline void _advance(lexer_t *ls) {
    ls->curr_index += 1;
}


// skip spaces and comments
static void skip_whitespace(lexer_t *ls) {
    if (ls->error) {
        return;
    }
    int in_comment = false;
    while (_has_remaining(ls)) {
        char ch = _peek(ls);
        if (ch == '#') {
            in_comment = true;
        } else if (ch == '\n' || ch == '\r') {
            in_comment = false;
        }
        if (!in_comment && !isblank(ch)) {
            return;
        }
        _advance(ls);
    }
}

#define T_INDENT 300
#define T_DEDENT 301

static bool tokenize_newline_or_indent(lexer_t *ls) {
    if (ls->error || ls->next_token) {
        return false;
    }

    if (!(_peek(ls) == '\n' || _peek(ls) == '\r')) {
        return false;
    }

    bool in_comment = false;
    size_t indent = 0;

    while (_has_remaining(ls)) {
        char ch = _peek(ls);
        bool newline = false;
        if (ch == '\r') {
            if (_peek_next(ls, 1) == '\n') {
                // cr-lf is treated as a single new line
                _advance(ls);
            }
            newline = true;
        } else if (ch == '\n') {
            newline = true;
        }

        if (newline) {
            indent = 0;
            lexer_add_line_index(ls, ls->curr_index);
            in_comment = false;
        } else {
            if (ch == '#') {
                in_comment = true;
            }
            if (!in_comment && ch == ' ') {
                ++indent;
            }
            if (!in_comment && !isblank(ch)) {
                break;
            }
        }

        _advance(ls);
    }

    if (indent == ls->indent) {
        ls->next_token = lexer_create_token(ls, T_NEWLINE);
    } else if (indent == (ls->indent + 4)) {
        ls->next_token = lexer_create_token(ls, T_INDENT);
    } else if (indent == (ls->indent - 4)) {
        ls->next_token = lexer_create_token(ls, T_DEDENT);
    } else {
        lexer_set_error(ls, "Incorrect indentation", 0);
        return false;
    }

    ls->indent = indent;

    return true;
}

static bool tokenize_non_decimal(lexer_t *ls, int (*test_char)(int), char *name) {
    size_t j = ls->curr_index + 2;

    while (j < ls->src_len) {
        char ch = ls->src[j];
        if (ch != '_' && !test_char(ch)) {
            break;
        }
        j++;
    }

    if (j == ls->curr_index + 2) {
        char buf[60];
        sprintf(buf, "Cannot parser %s number after leading literal", name);
        lexer_set_error(ls, buf, 0);
        return false;
    }

    // make sure the number literal doesn't end with '_'
    if (ls->src[j - 1] == '_') {
        char buf[30];
        sprintf(buf, "Invalid %s literal", name);
        lexer_set_error(ls, buf, 0);
        return false;
    }

    ls->curr_index = j;
    ls->next_token = lexer_create_token(ls, T_NUMBER);
    return true;
}


static int is_oct_digit(int ch) {
    return ch >= '0' && ch <= '7';
}

static int is_bin_digit(int ch) {
    return ch == '0' || ch == '1';
}


static size_t advance_decimal_sequence(lexer_t *ls, size_t i) {
    size_t j = i;
    while (j < ls->src_len) {
        char ch = ls->src[j];
        if (ch != '_' && !isdigit(ch)) {
            break;
        }
        j++;
    }

    // make sure the number literal doesn't start or end with '_'
    if (j == i || ls->src[j - 1] == '_' || ls->src[ls->curr_index + 2] == '_') {
        lexer_set_error(ls, "Invalid decimal literal", 0);
        return i;
    }

    return j;
}

static bool tokenize_decimal(lexer_t *ls) {

    size_t j = ls->curr_index;

    if (!isdigit(_peek(ls))) {
        return false;
    }

    j = advance_decimal_sequence(ls, j);
    if (ls->error) {
        return false;
    }

    // floating point
    bool is_floating_point = false;
    if (j < ls->src_len && ls->src[j] == '.') {
        is_floating_point = true;
        j++;
        j = advance_decimal_sequence(ls, j);
        if (ls->error) {
            return false;
        }
    }

    // exponent
    char ch = _peek_safe(ls, j);
    if (ch == 'e' || ch == 'E') {
        is_floating_point = true;
        j++;
        // exponent sign
        char ch2 = _peek_safe(ls, j);
        if (ch2 == '+' || ch2 == '-') {
            j++;
        }
        j = advance_decimal_sequence(ls, j);
        if (ls->error) {
            return false;
        }
    }

    // imaginary
    ch = _peek_safe(ls, j);
    if (ch == 'j' || ch == 'J') {
        is_floating_point = true;
        j++;
    }


    // 0-leading check
    if (!is_floating_point) {
        bool all_zero = true;

        for (size_t i = ls->curr_index; i < j; ++i) {
            if (ls->src[i] != '0') {
                all_zero = false;
                break;
            }
        }
        if (ls->src[ls->curr_index] == '0' && !all_zero) {
            lexer_set_error(ls, "Integer with leading zero; use 0o for octal numbers", 0);
            return false;
        }
    }

    ls->curr_index = j;
    ls->next_token = lexer_create_token(ls, T_NUMBER);

    return true;
}

static bool tokenize_number(lexer_t *ls) {
    if (ls->error || ls->next_token) {
        return false;
    }

    char ch1 = _peek(ls);
    if (ch1 == '0') {
        char ch2 = _peek_next(ls, 1);
        switch (ch2) {
            case 'x':
            case 'X':
                return tokenize_non_decimal(ls, isxdigit, "hexadecimal");
            case 'b':
            case 'B':
                return tokenize_non_decimal(ls, is_bin_digit, "binary");
            case 'o':
            case 'O':
                return tokenize_non_decimal(ls, is_oct_digit, "octal");
            default:;
        }
    }

    return tokenize_decimal(ls);
}

static bool tokenize_string(lexer_t *ls) {
    if (ls->error || ls->next_token) {
        return false;
    }

    bool multi_line = false;

    size_t i = ls->curr_index;

    if (_peek_safe(ls, i) == 'r') {
        i++;
    }
    if (_peek_safe(ls, i) == 'f') {
        i++;
    }

    char open_char = _peek_safe(ls, i);
    if (!(open_char == '\'' || open_char == '\"')) {
        return false;
    }
    i += 1;

    if (_peek_safe(ls, i + 1) == open_char && _peek_safe(ls, i + 2) == open_char) {
        multi_line = true;
        i += 2;
    }

    bool closed = false;

    if (multi_line) {
        int close_counter = 0;
        while (i < ls->src_len) {
            char ch = _peek_safe(ls, i);
            if (ch == open_char) {
                close_counter++;
            } else {
                close_counter = 0;
            }
            if (close_counter == 3) {
                closed = true;
                break;
            }
            if (ch == '\n') {
                lexer_add_line_index(ls, i);
            } else if (ch == '\r') {
                if (_peek_safe(ls, i + 1) == '\n') {
                    i++;
                }
                lexer_add_line_index(ls, i);
            }
            i++;
        }
    } else {
        while (i < ls->src_len) {
            char ch = _peek_safe(ls, i);
            if (ch == open_char) {
                closed = true;
                break;
            }
            if (ch == '\n' || ch == '\r') {
                break;
            }
            i++;
        }
    }

    ls->curr_index = i;

    if (!closed) {
        // todo add correct offsets for strings
        lexer_set_error(ls, "String not closed, unexpected EOL", 0);
        return false;
    }

    ++ls->curr_index;
    ls->next_token = lexer_create_token(ls, T_STRING);

    return true;
}

static bool test_name(int ch) {
    return isalnum(ch) || ch == '_';
}


static bool tokenize_name_or_keyword(lexer_t *ls) {
    if (ls->error || ls->next_token) {
        return false;
    }

    // numbers have already been tokenized,
    // so this doesn't test if the first char is a number

    if (!test_name(_peek(ls))) {
        return false;
    }

    while (_has_remaining(ls) && test_name(_peek(ls))) {
        _advance(ls);
    }

    // Since some literals and all keywords have the same rules as symbols
    // just add them here

    int n_keywords = sizeof(keywords) / sizeof(struct token_literal);

    for (int i = 0; i < n_keywords; ++i) {
        struct token_literal pair = keywords[i];

        const char *kw = pair.literal;
        size_t j = ls->start_index;

        bool matching = true;
        char ch;
        while ((ch = *kw)) {
            if (ch != ls->src[j]) {
                matching = false;
                break;
            }
            ++j;
            ++kw;
        }

        if (matching && j == ls->curr_index) {
            ls->next_token = lexer_create_token(ls, pair.tkl_type);
            return true;
        }
    }

    // not any of the keywords
    ls->next_token = lexer_create_token(ls, T_NAME);
    return true;
}


static bool tokenize_operator_or_symbol(lexer_t *ls) {
    if (ls->error || ls->next_token) {
        return false;
    }

    int n_operators = sizeof(operators) / sizeof(struct token_literal);

    // reversed because the longest operators has to be checked first
    for (int i = n_operators - 1; i >= 0; --i) {
        struct token_literal pair = operators[i];

        const char *op = pair.literal;
        size_t j = ls->start_index;

        bool matching = true;
        char ch;
        while ((ch = *op)) {
            if (ch != ls->src[j]) {
                matching = false;
                break;
            }
            ++j;
            ++op;
        }

        if (matching) {
            ls->curr_index = j;
            ls->next_token = lexer_create_token(ls, pair.tkl_type);
            return true;
        }
    }
    return false;
}

token_t *lexer_get_next_token(lexer_t *ls) {

    skip_whitespace(ls);

    // lexer still needs an ending token
    if (!_has_remaining(ls)) {
        if (ls->endmarker) {
            ls->endmarker = 0;
            return lexer_create_token(ls, T_ENDMARKER);
        }
        return NULL;
    }

    ls->start_index = ls->curr_index;
    ls->next_token = NULL;

    tokenize_newline_or_indent(ls);
    tokenize_number(ls);
    tokenize_string(ls);
    tokenize_name_or_keyword(ls);
    tokenize_operator_or_symbol(ls);

    if (ls->error) {
        return NULL;
    }

    if (!ls->next_token) {
        lexer_set_error(ls, "Unknown Syntax", 0);
        return NULL;
    }

    return ls->next_token;
}
