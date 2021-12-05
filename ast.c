#include "include/tokenmap.h"
#include "include/ast.h"
#include <stdarg.h>
#include <stdio.h>

FToken *FPeg_consume_token(FParser *p, size_t type) {
    size_t pos = p->pos;

    FToken *curr_token = get_next_token_to_consume(p, &pos);
    if (!curr_token) {
        return NULL;
    }

    // now check for correct type
    if (curr_token->type == type) {
        p->pos = pos + 1;
        return curr_token;
    } else {
        return NULL;
    }
}

FToken *FPeg_consume_token_and_debug(FParser *p, size_t type, const char *literal) {
    size_t pos = p->pos;

    print_indent_level(p->level);
    FToken *curr_token = get_next_token_to_consume(p, &pos);
    if (!curr_token) {
        printf("Mismatch   \033[31;1m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu, \033[31mno more tokens\033[0m)\n",
                literal, p->level, p->pos);
        return NULL;
    }

    // now check for correct type
    if (curr_token->type == type) {
        p->pos = pos + 1;
        printf("Matched    \033[32;1m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu\033[0m)\n",
                literal, p->level, p->pos);
        return curr_token;
    } else {
        char *token_buf;

        token_buf = FMem_calloc(curr_token->len + 1, sizeof(char));
        for (size_t i = 0; i < curr_token->len; ++i) {
            token_buf[i] = curr_token->start[i];
        }

        printf("Mismatch   \033[31;1m%-15s\033[0m (\033[33mlv=%zu \033[34mi=%zu, \033[31mt='%s'\033[0m)\n",
                literal, p->level, p->pos, token_buf);
        FMem_free(token_buf);
        return NULL;
    }
}



ast_list_t *ast_list_new(FParser *p) {
    ast_list_t *seq = PARSER_ALLOC(p, sizeof(ast_list_t));
    if (!seq) {
        return NULL;
    }
    seq->capacity = 0;
    seq->len = 0;
    seq->items = NULL;
    return seq;
}


void ast_list_append(FParser *p, ast_list_t *seq, void *item) {
    if (seq->len >= seq->capacity) {
        if (!seq->capacity) {
            seq->capacity = 1;
            seq->len = 0;
            seq->items = PARSER_ALLOC(p, sizeof(void *));
        } else {
            seq->capacity = seq->capacity << 1u;
            // Since realloc isn't available with memory regions,
            // the nodes needs to be copied in a loop
            void **old_items = seq->items;
            seq->items = PARSER_ALLOC(p, seq->capacity * sizeof(void *));
            for (int i = 0; i < seq->len; ++i) {
                seq->items[i] = old_items[i];
            }
        }
    }
    seq->items[seq->len++] = item;
}

void *FAst_new_node(FParser *p, size_t t, int nargs, ...) {
    va_list valist;
    if (nargs > AST_NODE_MAX_FIELD) {
        return NULL;
    }
    va_start(valist, nargs);

    FAstNode *res = PARSER_ALLOC(p, sizeof(FAstNode));
    // a field-node, shift by 2 and mark as non-sequence
    res->ast_t = t << 2u | 1u;
    for (int i = 0; i < nargs; ++i) {
        res->ast_v.fields[i] = va_arg(valist, FAstNode *);
    }
    
    va_end(valist);
    return res;
}


/*
csum[double] (left_recursive):
    | csum '+' cterm { "binop_add(p, %a, %b)" }
    | csum '-' cterm { "binop_sub(p, %a, %b)" }
    | cterm { a }
cterm[double] (left_recursive):
    | cterm '*' cfactor { "binop_mul(p, %a, %b)" }
    | cterm '/' cfactor { "binop_div(p, %a, %b)" }
    | cterm '%' cfactor { "binop_mod(p, %a, %b)" }
    | cfactor { a }
cfactor[double]:
    | '+' cfactor { "unary_plus(p, %a)" }
    | '-' cfactor { "unary_minus(p, %a)" }
    | '~' cfactor { "unary_not(p, %a)" }
    | cpower { a }
cpower[double]:
    | catom '**' cfactor { "binop_pow(p, %a, %b)" }
    | catom { a }
catom[double]:
    | '(' csum ')' { a }
    | NAME '(' [cparameters] ')' { "call_func(p, %a)" }
    | NAME { "load_const(p, %a)" }
    | NUMBER { "to_double(p, %a)" }
cparameters[ast_list_t]:
    | ','.csum+ [','] { a }
    */

double *binop_add(FParser *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a + *b;
    return r;
}