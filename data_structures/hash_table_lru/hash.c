#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "hash_elt.h"
#include "hash.h"


int
ht_init(ht_t *ht, size_t pow_size, size_t elt_max) {
    size_t i;
    size_t size;

    assert(ht != NULL && pow_size > 0);

    /* hash table size */
    size = (1 << pow_size);

    ht->heads_elt = malloc((size) * sizeof(*ht->heads_elt));
    if (ht->heads_elt == NULL) {
        return HT_MALLOC_ERROR;
    }

    for (i = 0; i < size ; i++) {
        SLIST_INIT(&(ht->heads_elt)[i]);
    }

    ht->size = size;

    /* allocate elements */
    ht->lru = calloc(elt_max, sizeof(struct ht_elt));
    if (ht->lru == NULL) {
        return HT_MALLOC_ERROR;
    }
    ht->lru_i = 0;

    /* fill lru linked list*/
    for (i = 0 ; i < ht->lru_max ; i++) {
        LIST_INSERT_HEAD(ht->lru_head, &(ht->lru)[i], next_lru);
    }

    ht->lru_max = elt_max;

    return SUCCESS;
}

void
ht_clean(ht_t * ht) {
    size_t i;
    assert(ht != NULL);

    /* For each head of */
    for (i = 0 ; i < ht->size ; i++) {
        while(!SLIST_EMPTY(&(ht->heads_elt)[i])) {
            SLIST_REMOVE_HEAD(&(ht->heads_elt)[i], next);
        }
    }

    free(ht->heads_elt);
    free(ht->lru);
}

ht_elt_t *
ht_lookup(ht_t * ht, const ht_key_t * k) {
    size_t hash;
    ht_elt_t *p;
    ht_elt_t *elt;

    hash = ht_hash(k);
    SLIST_FOREACH(p, &(ht->heads_elt)[hash & (ht->size - 1)], next) {
        /* compare keys */
        if (!ht_elt_cmp(&p->key, k)) {
            /* already exist*/
            return p;
        }
    }
    /* "new" element or least recent */
    elt = &(ht->lru[ht->lru_i]);
    ht_elt_reset(elt);
    ht->lru_i = (ht->lru_i + 1) % ht->lru_max;

    return elt;
}

void
ht_print_lru_content(ht_t * ht) {
    size_t i;
    for (i = 0 ; i < ht->lru_max ; i++ ) {
        if (((ht->lru)[i]).key.word == NULL) {
           continue; 
        }
        ht_key_print(((ht->lru)[i]).key);
    }
}
