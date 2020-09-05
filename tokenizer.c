#include "include/peg.h"
#include "include/tokenmap.h"
#include "stdbool.h"

void lexer_add_line_index(FLexerState *ls, size_t i) {
    if (ls->lines_size >= ls->lines_capacity) {
        if (!ls->lines_capacity) {
            ls->lines_capacity = 1;
            ls->lines_size = 0;
            ls->line_to_index = FMem_malloc(sizeof(size_t));
        } else {
            ls->lines_capacity = ls->lines_capacity << 1u;
            ls->line_to_index = FMem_realloc(
                    ls->line_to_index, ls->lines_capacity * sizeof(size_t));
        }
    }
    ls->line_to_index[ls->lines_size] = i;
    ls->lines_size += 1;
}

FToken *create_token(FLexerState *ls,
                     unsigned int type, bool is_whitespace) {
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

    return token;
}


#define HAS_REMAINING(ls) ((ls)->curr_index < (ls)->src_len)
#define PEEK(ls) ls->src[(ls)->curr_index]
#define PEEK_NEXT(ls, n) ((ls)->curr_index < (ls)->src_len - (n) ? \
    (ls)->src[(ls)->curr_index + (n)] : 0)

#define ADVANCE(ls) ls->curr_index++;

void tokenizer_set_error(FLexerState *ls, char *msg, int offset) {
    ls->error = msg + offset;
}

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

#define T_INDENT 0
#define T_DEDENT 200

bool tokenize_newlines(FLexerState *ls, FToken **ptoken) {
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
            lexer_add_line_index(ls, ls->curr_index);
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
        *ptoken = create_token(ls, T_NEWLINE, 1);
    } else if (indent == (ls->indent + 4)) {
        *ptoken = create_token(ls, T_INDENT, 1);
    } else if (indent == (ls->indent - 4)) {
        *ptoken = create_token(ls, T_DEDENT, 1);
    } else {
        ls->error = "Incorrect indentation";
        return false;
    }

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
        ls->error = "Cannot parse name number after leading literal";
        return false;
    }

    if (ls->src[j - 1] == '_' || ls->src[ls->curr_index + 2] == '_') {
        ls->error = name;
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

bool tokenize_decimal(FLexerState *ls, FToken **ptoken) {
    return false;
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

int tokenize_symbol(FLexerState *ls, FToken **ptoken) {
    if (ls->error) {
        return 0;
    }

    return 1;
}


FToken *FTokenizer_get_next_token(FLexerState *ls) {
    FToken *token = NULL;

    skip_spaces(ls);

    ls->start_index = ls->curr_index;

    if (!HAS_REMAINING(ls)) {
        return create_token(ls, T_ENDMARKER, 0);
    }

    (tokenize_newlines(ls, &token)) ||
    (tokenize_number(ls, &token)) ||
    (tokenize_symbol(ls, &token));

    if (ls->error) {
        return NULL;
    }

    if (!token) {
        tokenizer_set_error(ls, "Unknown Syntax", 0);
        return NULL;
    }

    return token;
}