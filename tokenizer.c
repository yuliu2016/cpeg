#include "include/tokenizer.h"
#include "include/tokenmap.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

FToken *create_token(FLexerState *ls, unsigned int type, bool is_whitespace) {
    FToken *token = FMem_malloc(sizeof(FToken));
    if (!token) {
        return NULL;
    }

    size_t line_start = ls->lines_size - 1;
    size_t col_start = ls->start_index - ls->line_to_index[line_start];

    token->lineno = line_start;
    token->column = col_start;
    token->len = ls->curr_index - ls->start_index;
    token->start = ls->src + ls->start_index;
    token->type = type;
    token->is_whitespace = (int) is_whitespace;
    token->memo = NULL;

    return token;
}


#define HAS_REMAINING(ls) ((ls)->curr_index < (ls)->src_len)
#define PEEK(ls) ls->src[(ls)->curr_index]
#define PEEK_SAFE(ls, i) ((i) < (ls)->src_len ? (ls)->src[i] : 0)
#define PEEK_NEXT(ls, n) PEEK_SAFE(ls, (ls)->curr_index + (n))

#define ADVANCE(ls) ++(ls)->curr_index;

// * returns the line end (exclusive) given line number
size_t get_line_end(FLexerState *ls, size_t lineno) {
    if (lineno < ls->lines_size - 1) {
        return ls->line_to_index[lineno + 1];
    } else if (lineno == ls->lines_size - 1) {
        size_t i = ls->line_to_index[lineno] + 1;
        while (i < ls->src_len)
        {
            char ch = ls->src[i];
            if (ch == '\r' || ch == '\n') {
                break;
            }
            i++;
        }
        return i;
    } else {
        return ls->src_len;
    }
}

void tokenizer_error(FLexerState *ls, char *msg, int char_offset) {
    size_t lineno = ls->lines_size - 1;
    size_t line_start = ls->line_to_index[lineno];
    size_t line_end = get_line_end(ls, lineno);
    if (char_offset < 0) {
        char_offset = 0;
    }
    size_t col = ls->curr_index - line_start + char_offset;

    // include an extra char for \0
    char *line_buf = FMem_calloc(line_end - line_start + 1, sizeof(char));
    int j = 0;
    for (size_t i = line_start; i < line_end; ++i) {
        line_buf[j] = ls->src[i];
        ++j;
    }

    char *caret_buf = FMem_calloc(col + 5, sizeof(char));
    for (size_t i = 0; i < col + 4; ++i) {
        caret_buf[i] = ' ';
    }
    
    size_t max_len = 45 + (line_end - line_start) + col + strlen(msg);
    char *err_buf = FMem_calloc(max_len, sizeof(char));
    
    sprintf(err_buf, "line %zu:\n    %s\n%s^\nError: %s", 
            lineno + 1, line_buf, caret_buf, msg);

    ls->error = err_buf;

    FMem_free(line_buf);
    FMem_free(caret_buf);
}

#define SET_ERROR(ls, msg, char_offset) tokenizer_error(ls, msg, char_offset)

int char_is_whitespace(char ch) {
    return ch == ' ' || ch == '\t';
}

// skip spaces and comments
void skip_spaces(FLexerState *ls) {
    if (ls->error) {
        return;
    }
    int in_comment = false;
    while (HAS_REMAINING(ls)) {
        in_comment = in_comment || PEEK(ls) == '#';
        if (!(in_comment || char_is_whitespace(PEEK(ls)))) {
            return;
        }
        ADVANCE(ls);
    }
}

#define T_INDENT 300
#define T_DEDENT 301

bool tokenize_newline_or_indent(FLexerState *ls, FToken **ptoken) {
    if (ls->error) {
        return false;
    }

    if (!(PEEK(ls) == '\n' || PEEK(ls) == '\r')) {
        return false;
    }

    bool in_comment = false;
    size_t indent = 0;

    while (HAS_REMAINING(ls)) {
        char ch = PEEK(ls);
        bool newline = false;
        if (ch == '\r') {
            if (PEEK_NEXT(ls, 1) == '\n') {
                // cr-lf is treated as a single new line
                ADVANCE(ls);
            }
            newline = true;
        } else if (ch == '\n') {
            newline = true;
        }

        if (newline) {
            indent = 0;
            FLexer_add_index_for_line(ls, ls->curr_index);
            in_comment = false;
        } else {
            in_comment = in_comment || ch == '#';
            if (in_comment || char_is_whitespace(ch)) {
                if (ch == ' ') {
                    // indentation is only with spaces
                    indent += 1;
                }
            } else {
                break;
            }
        }

        ADVANCE(ls);
    }


    if (indent == ls->indent) {
        *ptoken = create_token(ls, T_NEWLINE, true);
    } else if (indent == (ls->indent + 4)) {
        *ptoken = create_token(ls, T_INDENT, true);
    } else if (indent == (ls->indent - 4)) {
        *ptoken = create_token(ls, T_DEDENT, true);
    } else {
        SET_ERROR(ls, "Incorrect indentation", 0);
        return false;
    }

    ls->indent = indent;

    return true;
}

bool tokenize_non_decimal(FLexerState *ls, bool (*test_char)(char), char *name, FToken **ptoken) {
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
        SET_ERROR(ls, buf, 0);
        return false;
    }

    // make sure the number literal doesn't end with '_'
    if (ls->src[j - 1] == '_') {
        char buf[30];
        sprintf(buf, "Invalid %s literal", name);
        SET_ERROR(ls, buf, 0);
        return false;
    }

    ls->curr_index = j;
    *ptoken = create_token(ls, T_NUMBER, false);
    return true;
}

bool test_hex(char ch) {
    return (ch >= 'A' && ch <= 'F') ||
            (ch >= 'a' && ch <= 'f') ||
            ch >= '0' && ch <= '9';
}

bool test_oct(char ch) {
    return ch >= '0' && ch <= '7';
}

bool test_bin(char ch) {
    return ch == '0' || ch == '1';
}

bool test_dec(char ch) {
    return ch >= '0' && ch <= '9';
}

size_t advance_decimal_sequence(FLexerState *ls, size_t i) {
    size_t j = i;
    while (j < ls->src_len) {
        char ch = ls->src[j];
        if (ch != '_' && !test_dec(ch)) {
            break;
        }
        j++;
    }

    // make sure the number literal doesn't start or end with '_'
    if (j == i || ls->src[j - 1] == '_' || ls->src[ls->curr_index + 2] == '_') {
        SET_ERROR(ls, "Invalid decimal literal", 0);
        return false;
    }

    return j;
}

bool tokenize_decimal(FLexerState *ls, FToken **ptoken) {

    size_t j = ls->curr_index;

    if (!test_dec(PEEK(ls))) {
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
    char ch = PEEK_SAFE(ls, j);
    if (ch == 'e' || ch == 'E') {
        is_floating_point = true;
        j++;
        // exponent sign
        char ch2 = PEEK_SAFE(ls, j);
        if (ch2 == '+' || ch2 == '-') {
            j++;
        }
        j = advance_decimal_sequence(ls, j);
        if (ls->error) {
            return false;
        }
    }

    // imaginary
    ch = PEEK_SAFE(ls, j);
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
            SET_ERROR(ls, "Integer with leading zero; use 0o for octal numbers", 0);
            return false;
        }
    }

    ls->curr_index = j;
    *ptoken = create_token(ls, T_NUMBER, false);

    return true;
}

bool tokenize_number(FLexerState *ls, FToken **ptoken) {
    if (ls->error) {
        return false;
    }

    char ch1 = PEEK(ls);
    if (ch1 == '0') {
        char ch2 = PEEK_NEXT(ls, 1);
        switch (ch2) {
            case 'x':
            case 'X':
                return tokenize_non_decimal(ls, test_hex, "hexadecimal", ptoken);
            case 'b':
            case 'B':
                return tokenize_non_decimal(ls, test_bin, "binary", ptoken);
            case 'o':
            case 'O':
                return tokenize_non_decimal(ls, test_oct, "octal", ptoken);
            default:;
        }
    }

    return tokenize_decimal(ls, ptoken);
}

bool tokenize_string(FLexerState *ls, FToken **ptoken) {
    if (ls->error) {
        return false;
    }

    bool multi_line = false;

    size_t i = ls->curr_index;

    if (PEEK_SAFE(ls, i) == 'r') {
        i++;
    }
    if (PEEK_SAFE(ls, i) == 'f') {
        i++;
    }

    char open_char = PEEK_SAFE(ls, i);
    if (!(open_char == '\'' || open_char == '\"')) {
        return false;
    }
    i += 1;

    if (PEEK_SAFE(ls, i + 1) == open_char && PEEK_SAFE(ls, i + 2) == open_char) {
        multi_line = true;
        i += 2;
    }

    bool closed = false;

    if (multi_line) {
        int close_counter = 0;
        while (i < ls->src_len) {
            char ch = PEEK_SAFE(ls, i);
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
                FLexer_add_index_for_line(ls, i);
            } else if (ch == '\r') {
                if (PEEK_SAFE(ls, i + 1) == '\n') {
                    i++;
                }
                FLexer_add_index_for_line(ls, i);
            }
            i++;
        }
    } else {
        while (i < ls->src_len) {
            char ch = PEEK_SAFE(ls, i);
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
        SET_ERROR(ls, "String not closed, unexpected EOL", 0);
        return false;
    }

    ++ls->curr_index;
    *ptoken = create_token(ls, T_STRING, false);

    return true;
}

bool test_name(char ch) {
    return (ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9') ||
            (ch == '_');
}

struct token_literal {
    const char *literal;
    size_t type;
};

static struct token_literal keywords[] = {
        {"return",   T_RETURN},
        {"nonlocal", T_NONLOCAL},
        {"if",       T_IF},
        {"elif",     T_ELIF},
        {"else",     T_ELSE},
        {"and",      T_AND},
        {"or",       T_OR},
        {"not",      T_NOT},
        {"is",       T_IS},
        {"in",       T_IN},
        {"pass",     T_PASS},
        {"as",       T_AS},
        {"from",     T_FROM},
        {"import",   T_IMPORT},
        {"with",     T_WITH},
        {"async",    T_ASYNC},
        {"await",    T_AWAIT},
        {"while",    T_WHILE},
        {"for",      T_FOR},
        {"continue", T_CONTINUE},
        {"break",    T_BREAK},
        {"try",      T_TRY},
        {"except",   T_EXCEPT},
        {"finally",  T_FINALLY},
        {"raise",    T_RAISE},
        {"del",      T_DEL},
        {"assert",   T_ASSERT},
        {"None",     T_NONE},
        {"True",     T_TRUE},
        {"False",    T_FALSE}
};

bool tokenize_name_or_keyword(FLexerState *ls, FToken **ptoken) {
    if (ls->error) {
        return false;
    }

    // numbers have already been tokenized,
    // so this doesn't test if the first char is a number

    if (!test_name(PEEK(ls))) {
        return false;
    }

    while (HAS_REMAINING(ls) && test_name(PEEK(ls))) {
        ADVANCE(ls);
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
            *ptoken = create_token(ls, pair.type, false);
            return true;
        }
    }

    // not any of the keywords
    *ptoken = create_token(ls, T_NAME, false);
    return true;
}

static struct token_literal operators[] = {

// ====== Single-char operators ======
        {".",   T_OP_DOT},
        {",",   T_OP_COMMA},
        {"=",   T_OP_ASSIGN},
        {":",   T_OP_COLON},
        {"?",   T_OP_TERNERY},
        {"!",   T_OP_NOT},
        {";",   T_OP_SEMICOLON},

// second most common - brackets
        {"(",   T_OP_LPAR},
        {")",   T_OP_RPAR},
        {"{",   T_OP_LBRACE},
        {"}",   T_OP_RBRACE},
        {"[",   T_OP_LSQB},
        {"]",   T_OP_RSQB},
        {"<",   T_OP_LESS},
        {">",   T_OP_GREATER},

// arithmetic
        {"+",   T_OP_PLUS},
        {"-",   T_OP_MINUS},
        {"*",   T_OP_TIMES},
        {"/",   T_OP_DIV},
        {"%",   T_OP_MODULUS},
        {"@",   T_OP_MATRIX_TIMES},

// bitwise operators
        {"|",   T_OP_BIT_OR},
        {"&",   T_OP_BIT_AND},
        {"~",   T_OP_BIT_NOT},
        {"^",   T_OP_BIT_XOR},

// ====== Double-Char Operators ======
        {"==",  T_OP_EQUAL},
        {"!=",  T_OP_NEQUAL},
        {"<=",  T_OP_LESS_EQUAL},
        {">=",  T_OP_MORE_EQUAL},
        {"->",  T_OP_PIPE},
        {":=",  T_OP_ASGN_EXPR},
        {"//",  T_OP_FLOOR_DIV},
        {"**",  T_OP_POWER},
        {"+=",  T_OP_PLUS_ASSIGN},
        {"-=",  T_OP_MINUS_ASSIGN},
        {"*=",  T_OP_TIMES_ASSIGN},
        {"/=",  T_OP_DIV_ASSIGN},
        {"%=",  T_OP_MODULUS_ASSIGN},
        {"@=",  T_OP_MATRIX_TIMES_ASSIGN},
        {"|=",  T_OP_BIT_OR_ASSIGN},
        {"&=",  T_OP_BIT_AND_ASSIGN},
        {"^=",  T_OP_BIT_XOR_ASSIGN},
        {"<<",  T_OP_LSHIFT},
        {">>",  T_OP_RSHIFT},

// ====== Triple-char operators ======
        {"//=", T_OP_FLOOR_DIV_ASSIGN},
        {"**=", T_OP_POWER_ASSIGN},
        {"<<=", T_OP_LSHIFT_ASSIGN},
        {">>=", T_OP_RSHIFT_ASSIGN}
};

bool tokenize_operator_or_symbol(FLexerState *ls, FToken **ptoken) {
    if (ls->error) {
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
            *ptoken = create_token(ls, pair.type, false);
            return true;
        }
    }
    return false;
}

FToken *FLexer_get_next_token(FLexerState *ls) {
    ls->start_index = ls->curr_index;

    // lexer still needs an ending token
    if (!HAS_REMAINING(ls)) {
        if (ls->endmarker) {
            ls->endmarker = 0;
            return create_token(ls, T_ENDMARKER, 0);
        }
        return NULL;
    }

    skip_spaces(ls);

    FToken *token = NULL;
    (tokenize_newline_or_indent(ls, &token)) ||
    (tokenize_number(ls, &token)) ||
    (tokenize_string(ls, &token)) ||
    (tokenize_name_or_keyword(ls, &token)) ||
    (tokenize_operator_or_symbol(ls, &token));

    if (ls->error) {
        return NULL;
    }

    if (!token) {
        tokenizer_error(ls, "Unknown Syntax", 0);
        return NULL;
    }

    return token;
}

FLexerState *FLexer_analyze_all(char *src) {
    FLexerState *ls = FMem_malloc(sizeof(FLexerState));

    // find length of string
    size_t len = strlen(src);

    FLexer_init_state(ls, src, len, false);

    for (;;) {
        FToken *token = FLexer_get_next_token(ls);
        if (!token) {
            break;
        }
        FLexer_add_token(ls, token);
    }

    return ls;
}