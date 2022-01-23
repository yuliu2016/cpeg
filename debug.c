#include "include/internal/mem_debug.h"
#include "include/internal/tokenmap.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "inttypes.h"
#include "include/peg.h"


void input_loop(char *prompt, char *(*func)(char *), int times) {
    printf("%s", prompt);
    char line[1024];
    while (times--) {
        fgets(line, 1024, stdin);
        if (strlen(line) == 0) {
            continue;
        }
        if (strcmp(line, "exit\n") == 0) {
            break;
        }
        // remove the newline character at the end
        line[strlen(line) - 1] = 0;
        char *s = func(line);
        if (!s) {
            break;
        }
        printf("%s", s);
        printf("%s", prompt);
    }
}


char *memregion_copy(mem_region_t *region) {
    size_t s = 0;
    mem_block_t *head = region->head_block;
    while (head) {
        s += head->block_size;
        head = head->next_block;
    }
    char *buf = malloc(s + 1);
    head = region->head_block;
    int i = 0;
    while (head) {
        char *acc = (char *) head->head_ptr;
        size_t bs = head->block_size;
        size_t offset = head->alloc_offset;
        int j = 0;
        for (; j < bs; ++j) {
            if (j < offset) {
                char ch = acc[j];
                if (ch) {
                    buf[i + j] = ch;
                } else {
                    buf[i + j] = '_';
                }
            } else {
                buf[i + j] = '#';
            }
        }
        i = j;
        head = head->next_block;
    }
    buf[i] = '\0';
    return buf;
}

void print_buf(void *head, int size) {
    char *buf = malloc(size + 1);
    char *acc = head;
    for (int i = 0; i < size; ++i) {
        char ch = acc[i];
        if (ch) {
            buf[i] = ch;
        } else {
            buf[i] = '^';
        }
    }
    buf[size] = '\0';
    printf("%s\n", buf);
    free(buf);
}


mem_block_t *mem_block_new(size_t size);

void test_block() {
    mem_block_t *block = mem_block_new(256);
    char *dest = block->head_ptr;
    block->alloc_offset += 11;
    strcpy(dest, "HelloWorld");
    dest = ((char *) block->head_ptr) + block->alloc_offset;
    block->alloc_offset += 3;
    strcpy(dest, "Ho");
    print_buf(block->head_ptr, 256);
    free(block);
}

void test_region() {
    mem_region_t *reg = mbregion(32, 0);
    PRINT_ADDR(reg);
    PRINT_ADDR(reg->cur_block);
    char *dst = mballoc(reg, 11);
    PRINT_ADDR(dst);
    strcpy(dst, "HelloWorld");
    dst = mballoc(reg, 3);
    PRINT_ADDR(dst);
    strcpy(dst, "Hi");
    dst = NULL;
    printf("%zu\n", sizeof(char *));
    char *x = memregion_copy(reg);
    printf("%s\n", x);
    mbpurge(reg);
    free(x);
}

void print_address(void *ptr, const char *name) {
    uintptr_t i = (uintptr_t) ptr;
    size_t s = sizeof(uintptr_t) / 4;
    if (s == 1) {
        printf("%-16s = %#08x\n", name, (unsigned int) i);
    } else {
        printf("%-16s = %#016llx\n", name, (unsigned long long) i);
    }
}


typedef struct token_kind {
    const char * name;
    const char * style;
    size_t min;
    size_t max;
} TokenKind;

static TokenKind token_kinds[] = {
    {"ENDMARKER", "\033[31m", 1, 2},
    {"NEWLINE", "", 2, 3},
    {"NAME", "\033[35m", 3, 4}, // magenta
    {"NUMBER", "\033[34m", 4, 5}, // blue
    {"STRING", "\033[32m", 5, 6}, // green
    {"OPERATOR", "\033[33m", 6, 54}, // yellow
    {"KEYWORD", "\033[34;1m", 55, 84}, // bright blue
};


void lexer_compute_next(lexer_t *ls);

static lexer_t *lexer_analyze_all(char *src) {
    lexer_t *ls = malloc(sizeof(lexer_t));

    // find length of string
    size_t len = strlen(src);

    lexer_init_state(ls, src, len);

    for (;;) {
        lexer_compute_next(ls);
        token_t *token = ls->next_token;
        if (!token) {
            break;
        }
        lexer_append_token(ls, token);
    }

    return ls;
}

char *tokenizer_repl(char *in) {
    lexer_t *ls = lexer_analyze_all(in);
    if (ls->error) {
        printf("\033[31mFile <lexertest>, %s\033[0m", ls->error);
        lexer_free_state(ls);
        return "\n";
    }

    if (ls->token_len == 0) {
        printf("[Empty Token List]\n");
        lexer_free_state(ls);
        return "";
    }

    size_t previous_line = -1;
    size_t literal_len = 100;
    char *literal = malloc(literal_len);

    for (int i = 0; i < ls->token_len; ++i) {
        token_t *token = ls->tokens[i];

        if (token->len > literal_len) {
            literal_len = token->len;
            literal = realloc(literal, literal_len);
        }

        for (int j = 0; j < literal_len; ++j) {
            literal[j] = 0;
        }
        for (size_t j = 0; j < token->len; ++j) {
            char ch = token->start[j];
            if (ch == '\n') {
                literal[j++] = '\\';
                literal[j] = 'n';
            } else {
                literal[j] = ch;
            }
        }

        int line = token->lineno;
        previous_line = line;

        int tk_type = token->tk_type;
        TokenKind kind;
        for (int i = 0; i < 7; ++i) {
            kind = token_kinds[i];
            if (tk_type >= kind.min && tk_type < kind.max) {
                break;
            }
        }

        printf("L%d:%-5d%-10s%s%s\033[0m\n", line + 1, token->column,
                kind.name, kind.style, literal);
    }

    free(literal);
    lexer_free_state(ls);
    return "";
}

char *idchptr(char *in) {
    return in;
}

static void print_indent_level(size_t s) {
    if (s > 40) {
        s = s % 40u;
    }
    char *b = malloc(sizeof(char) * (s * 2 + 1));
    if (!b) {
        return;
    }
    for (size_t i = 0; i < s; ++i) {
        if (i % 2 == 0) {
            b[i * 2] = '|';
        } else {
            b[i * 2] = ' ';
        }
        b[i * 2 + 1] = ' ';
    }
    b[s * 2] = '\0';
    printf("%s", b);
    free(b);
}

void parser_matched_debug(parser_t *p, const char *literal) {
    print_indent_level(p->level);
    token_t *curr_token = parser_fetch_token(p, p->pos);
    if (!curr_token) {
        printf("fatal: no curr_token when debugging matched");
        exit(1);
    }
    char *token_buf = token_heap_copy(curr_token);
    printf("Matched    \033[32;1m%-20s\033[0m (\033[33mlv=%zu \033[34mi=%zu \033[32mt='%s'\033[0m)\n",
            literal, p->level, p->pos, token_buf);
    free(token_buf);
}

void parser_mismatch_debug(parser_t *p, const char *literal) {
    print_indent_level(p->level);
    token_t *curr_token = parser_fetch_token(p, p->pos);
    if (!curr_token) {
        printf("Mismatch   \033[31;1m%-20s\033[0m (\033[33mlv=%zu \033[34mi=%zu, \033[31mno more tokens\033[0m)\n",
                literal, p->level, p->pos);
        return;
    }
    char *token_buf = token_heap_copy(curr_token);
    printf("Mismatch   \033[31;1m%-20s\033[0m (\033[33mlv=%zu \033[34mi=%zu \033[31mt='%s'\033[0m)\n",
            literal, p->level, p->pos, token_buf);
    free(token_buf);
}


void parser_enter_debug(parser_t *p, const char *f_rule) {
    print_indent_level(p->level);

    // fetch_token needed over direct access
    token_t *curr_token = parser_fetch_token(p, p->pos);

    char *token_buf = token_heap_copy(curr_token);

    printf("Checking   \033[36m%-20s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[36m t='%s'\033[0m)\n",
            f_rule, p->level, p->pos, token_buf);

    free(token_buf);
    p->level++;
}

void parser_exit_debug(parser_t *p, void *res, const char *f_rule) {
    print_indent_level(p->level);
    if (res) {
        printf("Success in \033[32m%-20s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[0m)\n", f_rule, p->level, p->pos);
    } else {
        printf("Failure in \033[31m%-20s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[0m)\n", f_rule, p->level, p->pos);
    }
}

void parser_memo_debug(parser_t *p, token_memo_t *memo, const char *f_rule) {
    p->level--;
    if (!memo) {
        return;
    };
    if (!memo->node) return;
    print_indent_level(p->level);
    char *succ;
    if (memo->node) {
        succ = "was a \033[32mSuccess\033[0m";
    } else {
        succ = "was a \033[31mFailure\033[0m";
    }
    printf("Memoized   \033[35m%-20s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[0m, %s)\n", 
            f_rule, p->level, p->pos, succ);
}


void *parse_grammar(int entry_point);
double *parse_calc();
parser_t *get_static_parser();
parser_t *get_calc_parser();


static int print_if_error(parser_t *p, void *result) {
    lexer_t *ls = &p->lexer_state;
    if (p->error) {
        printf("======================\n\033[31;1m");
        printf("parser error: %s\n\033[0m", p->error);
        printf("======================");
        return 1;
    } else if (ls->error) {
        printf("======================\n\033[31;1m");
        printf("lexer error: %s\n\033[0m", ls->error);
        printf("======================");
        return 1;
    } else if (!result) {
        printf("======================\n\033[31;1m");
        printf("Not a valid parse tree\n\033[0m");
        printf("======================");
        return 1;
    } 
    return 0;
}

char *calc_repl(char *in) {
    
    parser_t *p = get_calc_parser();
    parser_init_state(p, in, strlen(in), 
            lexer_compute_next, (char **) indices);
    
    double *n = parse_calc();
    lexer_t *ls = &p->lexer_state;
    parser_verify_eof(p);
    if (!print_if_error(p, n)) {
        printf("Result: %lf", *n);
    }
    parser_free_state(p);
    return "\n";
}

char *parser_repl(char *in) {
    parser_t *p = get_static_parser();
    parser_init_state(p, in, strlen(in), 
            lexer_compute_next, (char **) indices);
    void *n = parse_grammar(0);
    lexer_t *ls = &p->lexer_state;
    parser_verify_eof(p);
    if (!print_if_error(p, n)) {
        printf("Success!");
    }
    parser_free_state(p);
    return "\n";
}

typedef struct iotest {
    char *in;
    char *out;
} iotest_t;

typedef struct iostest_suite {
    int ntests;
    iotest_t *tests;
} iotest_suite_t;