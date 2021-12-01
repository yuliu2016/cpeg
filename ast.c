#include "include/tokenmap.h"
#include "include/ast.h"
#include <stdarg.h>
#include <stdio.h>


FAstNode *ast_node_from_token(FParser *p, size_t type, FToken *curr_token) {
    FAstNode *node = PARSER_ALLOC(p, sizeof(FAstNode));
    if (!node) {
        return NULL;
    }

    // not sequence -> | 1u
    // is token -> | 2u
    node->ast_t = type << 2u | 1u | 2u;
    node->ast_v.token = curr_token;
    return node;
}


FAstNode *FPeg_consume_token(FParser *p, size_t type) {
    size_t pos = p->pos;

    FToken *curr_token = get_next_token_to_consume(p, &pos);
    if (!curr_token) {
        return NULL;
    }

    // now check for correct type
    if (curr_token->type == type) {
        p->pos = pos + 1;
        return ast_node_from_token(p, type, curr_token);
    } else {
        return NULL;
    }
}

FAstNode *FPeg_consume_token_and_debug(FParser *p, size_t type, const char *literal) {
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
        return ast_node_from_token(p, type, curr_token);
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

FAstNode *seq_new(FParser *p) {
    FAstNode *node = PARSER_ALLOC(p, sizeof(FAstNode));
    if (!node) {
        return NULL;
    }
    // sequence type has a t of 0
    node->ast_t = 0;
    FAstSequence *seq = &node->ast_v.sequence;
    seq->capacity = 0;
    seq->len = 0;
    seq->items = NULL;
    return node;
}

ast_list *ast_list_new(FParser *p) {
    ast_list *seq = PARSER_ALLOC(p, sizeof(ast_list));
    if (!seq) {
        return NULL;
    }
    seq->capacity = 0;
    seq->len = 0;
    seq->items = NULL;
}

void seq_append(FParser *p, FAstNode *node, void *item) {
    FAstSequence *seq = &node->ast_v.sequence;
    if (seq->len >= seq->capacity) {
        if (!seq->capacity) {
            seq->capacity = 1;
            seq->len = 0;
            seq->items = PARSER_ALLOC(p, sizeof(FAstNode *));
        } else {
            seq->capacity = seq->capacity << 1u;
            // Since realloc isn't available with memory regions,
            // the nodes needs to be copied in a loop
            FAstNode **old_items = seq->items;
            seq->items = PARSER_ALLOC(p, seq->capacity * sizeof(FAstNode *));
            for (int i = 0; i < seq->len; ++i) {
                seq->items[i] = old_items[i];
            }
        }
    }
    seq->items[seq->len] = item;
    seq->len += 1;
}

ast_list *ast_list_append(FParser *p, ast_list *seq, void *item) {
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

FAstNode *FAst_new_node(FParser *p, size_t t, int nargs, ...) {
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

FAstNode *FPeg_parse_sequece_or_none(FParser *p, FRuleFunc rule) {
    FAstNode *node, *seq = seq_new(p);
    while ((node = rule(p))) {
        seq_append(p, seq, node);
    }
    return seq;
}

FAstNode *FPeg_parse_sequence(FParser *p, FRuleFunc rule) {
    FAstNode *node, *seq;
    if (!(node = rule(p))) return 0;
    seq = seq_new(p);

    do {
        seq_append(p, seq, node);
    } while ((node = rule(p)));

    return seq;
}

FAstNode *FPeg_parse_delimited(FParser *p, size_t delimiter, FRuleFunc rule) {
    FAstNode *node, *seq;
    if (!(node = rule(p))) return 0;
    seq = seq_new(p);
    size_t pos;

    do {
        seq_append(p, seq, node);
        pos = p->pos;
    } while (FPeg_consume_token(p, delimiter) && rule(p));

    p->pos = pos;
    return seq;
}

FAstNode *FPeg_parse_token_sequence(FParser *p, size_t token) {
    FAstNode *node, *seq;
    if (!(node = FPeg_consume_token(p, token))) return 0;
    seq = seq_new(p);

    do {
        seq_append(p, seq, node);
    } while ((node = FPeg_consume_token(p, token)));

    return seq;
}

FAstNode *FPeg_parse_token_sequence_or_none(FParser *p, size_t token) {
    FAstNode *node, *seq = seq_new(p);
    while ((node = FPeg_consume_token(p, token))) {
        seq_append(p, seq, node);
    }
    return seq;
}

FAstNode *FPeg_parse_token_delimited(FParser *p, size_t delimiter, size_t token) {
    FAstNode *node, *seq;
    if (!(node = FPeg_consume_token(p, token))) return 0;
    seq = seq_new(p);
    size_t pos;

    do {
        seq_append(p, seq, node);
        pos = p->pos;
    } while (FPeg_consume_token(p, delimiter) && FPeg_consume_token(p, token));

    p->pos = pos;
    return seq;
}