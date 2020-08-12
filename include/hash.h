#ifndef CPEG_HASH_H
#define CPEG_HASH_H

#include "mem.h"

typedef unsigned int ht_hash_t;

typedef struct {
    char *start;
    size_t len;
    ht_hash_t computed_hash;
} ht_str;

ht_str *ht_str_new(char *str);

typedef struct ht_node ht_node;

struct ht_node {
    ht_hash_t hash;
    ht_str *key;
    char *value;
    ht_node *next;
    ht_node *before;
    ht_node *after;
};

typedef struct {
    size_t size;
    size_t tsize;
    ht_node **table;
    ht_node *head;
    ht_node *tail;
    ht_node *iter;
} ht_hashtable;

char *ht_put(ht_hashtable *ht, ht_str *key, char *value);

void ht_put_free(ht_hashtable *ht, ht_str *key, char *value);

char *ht_get(ht_hashtable *ht, ht_str *key);

ht_hashtable *ht_new();

void ht_free(ht_hashtable *ht);

int ht_iter_head(ht_hashtable *ht);

int ht_iter_tail(ht_hashtable *ht);

ht_node *ht_next(ht_hashtable *ht);

ht_node *ht_prev(ht_hashtable *ht);

void ht_iterate(ht_hashtable *ht, void (*iterator)(ht_node*));

void ht_reversed(ht_hashtable *ht, void (*iterator)(ht_node*));

#endif //CPEG_HASH_H
