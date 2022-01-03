#include "include/hash.h"
#include "stdlib.h"

ht_str *ht_str_new(char *str) {
    ht_str *cs = malloc(sizeof(ht_str));
    if (!cs) {
        return NULL;
    }
    size_t len = 0;
    ht_hash_t hash = 0;
    while (1) {
        char ch = str[len];
        if (ch == '\0') {
            break;
        }
        ++len;
        hash = hash * 31 + ((unsigned char) ch & 0xffu);
    }
    cs->start = str;
    cs->len = len;
    cs->computed_hash = hash;
    return cs;
}

int ht_check_equal_key(ht_str *k1, ht_str *k2) {
    if (k1 == k2) {
        return 1;
    }
    if (k1->len != k2->len) {
        return 0;
    }
    if (k1->computed_hash != k2->computed_hash) {
        return 0;
    }
    for (int i = 0; i < k1->len; ++i) {
        if (k1->start[i] != k2->start[i]) {
            return 0;
        }
    }
    return 1;
}

int ht_resize(ht_hashtable *ht) {
    return ht->tsize;
}

ht_node *ht_node_new(ht_str *key, char *value) {
    ht_node *node = malloc(sizeof(ht_node));
    node->hash = key->computed_hash;
    node->key = key;
    node->value = value;
    node->next = NULL;
    node->before = NULL;
    node->after = NULL;
    return node;
}

ht_node *ht_node_add_linked(ht_hashtable *ht, ht_str *key, char *value) {
    ht_node *new_node = ht_node_new(key, value);
    ht_node *before = ht->tail;
    ht->tail = new_node;
    if (before) {
        before->after = new_node;
        new_node->before = before;
    }
    if (!ht->head) {
        ht->head = new_node;
    }
    return new_node;
}

char *ht_put(ht_hashtable *ht, ht_str *key, char *value) {
    if (ht->iter) {
        return NULL;
    }
    size_t n;
    if (ht->tsize == 0) {
        n = ht_resize(ht);
    } else {
        n = ht->tsize;
    }
    ht_hash_t hash = key->computed_hash;
    size_t i = hash % n;
    ht_node *prev = ht->table[i];
    if (!prev) {
        // no match in table - add table entry
        ht->table[i] = ht_node_add_linked(ht, key, value);
    } else {
        ht_node *next = NULL;
        while (1) {
            next = prev->next;
            if (!next) {
                // no match in linked-list - add to the end
                prev->next = ht_node_add_linked(ht, key, value);
                break;
            }
            if (next->hash == hash && ht_check_equal_key(key, next->key)) {
                // matched key - updating existing value
                char *old_val = next->value;
                next->value = value;
                return old_val;
            }
            prev = next;
        }
    }
    ++ht->size;
    return NULL;
}

void ht_put_free(ht_hashtable *ht, ht_str *key, char *value) {
    char * old_val = ht_put(ht, key, value);
    if (old_val) {
        free(old_val);
    }
}

char *ht_get(ht_hashtable *ht, ht_str *key) {
    if (key && ht && ht->tsize != 0) {
        ht_hash_t hash = key->computed_hash;
        ht_node *node = ht->table[hash % ht->tsize];
        while (node) {
            if (node->hash == hash && ht_check_equal_key(key, node->key)) {
                return node->value;
            }
            node = node->next;
        }
    }
    return NULL;
}

ht_hashtable *ht_new() {
    ht_hashtable *ht = malloc(sizeof(ht_hashtable));
    if (!ht) {
        return NULL;
    }
    ht->size = 0;
    ht->tsize = 0;
    ht->table = NULL;
    ht->head = NULL;
    ht->tail = NULL;
    ht->iter = NULL;
    return ht;
}

void ht_free(ht_hashtable *ht) {
    free(ht);
}

int ht_iter_head(ht_hashtable *ht) {
    if (ht->iter == NULL) {
        ht->iter = ht->head;
        return 1;
    }
    return 0;
}

int ht_iter_tail(ht_hashtable *ht) {
    if (ht->iter == NULL) {
        ht->iter = ht->tail;
        return 1;
    }
    return 0;
}

ht_node *ht_next(ht_hashtable *ht) {
    if (!ht->iter) {
        return NULL;
    }
    ht_node *after = ht->iter->after;
    ht->iter = after;
    return after;
}

ht_node *ht_prev(ht_hashtable *ht) {
    if (!ht->iter) {
        return NULL;
    }
    ht_node *before = ht->iter->before;
    ht->iter = before;
    return before;
}


void ht_iterate(ht_hashtable *ht, void (*iterator)(ht_node *)) {
    if (!ht_iter_head(ht)) {
        return;
    }
    ht_node *node;
    while ((node = ht_next(ht))) {
        iterator(node);
    }
}

void ht_reversed(ht_hashtable *ht, void (*iterator)(ht_node *)) {
    if (!ht_iter_tail(ht)) {
        return;
    }
    ht_node *node;
    while ((node = ht_prev(ht))) {
        iterator(node);
    }
}
