#include <assert.h>
#include <stdint.h>
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

    /* Initialize hash table : array of linked lists */
    ht->elt_heads = malloc((size) * sizeof(*ht->elt_heads));
    if (ht->elt_heads == NULL) {
        return HT_MALLOC_ERROR;
    }
    for (i = 0; i < size ; i++) {
        LIST_INIT(&(ht->elt_heads)[i]);
    }
    ht->size = size;

    /* Allocate pool of elements */
    ht->pool = calloc(elt_max, sizeof(struct ht_elt));
    if (ht->pool == NULL) {
        return HT_MALLOC_ERROR;
    }

    /* Initialize LRU linked list */
    ht->lru_head = malloc(sizeof(*ht->lru_head));
    if (ht->lru_head == NULL) {
       return HT_MALLOC_ERROR;
    }
    TAILQ_INIT(ht->lru_head);

    /* Fill LRU with pool elements */
    for (i = 0 ; i < elt_max ; i++) {
        TAILQ_INSERT_HEAD(ht->lru_head, &(ht->pool)[i], next_lru);
        //TODO refactor : reset element ?
        memset(&(ht->pool)[i], '\0', 6);
    }

    ht->lru_max = elt_max;

    return SUCCESS;
}

void
ht_clean(ht_t * ht) {
    size_t i;
    assert(ht != NULL);

    /* Remove hash elements */
    for (i = 0 ; i < ht->size ; i++) {
        while(!LIST_EMPTY(&(ht->elt_heads)[i])) {
            LIST_REMOVE(LIST_FIRST(&(ht->elt_heads)[i]), next);
        }
    }

    free(ht->elt_heads);
    free(ht->lru_head);
    free(ht->pool);
}

static inline ht_elt_t *
_ht_hash_lookup(const ht_t * ht, const uint8_t * mac, size_t hash) {
    ht_elt_t *p;

    LIST_FOREACH(p, &(ht->elt_heads)[hash & (ht->size - 1)], next) {
        if (!ht_elt_cmp((const uint8_t *)&(p->mac), mac)) {
            return p;
        }
    }
    return NULL;
}

ht_elt_t *
ht_lookup(ht_t * ht, const uint8_t * mac) {
    size_t hash;
    size_t old_hash;
    ht_elt_t *ret;
    ht_elt_t *elt;

    hash = ht_hash(mac);
    ret = _ht_hash_lookup(ht, mac, hash);
    if (ret != NULL) {
        /* if already exist, lru update :
         * element is moved to the end
         */
        TAILQ_REMOVE(ht->lru_head, ret, next_lru);
        TAILQ_INSERT_TAIL(ht->lru_head, ret, next_lru);
        return ret;
    }

    /* If it's a new element, we take the least recent used element
     * in order to recycling it */
    elt = TAILQ_FIRST(ht->lru_head);

    /* move it at end of lru */
    TAILQ_REMOVE(ht->lru_head, elt, next_lru);
    TAILQ_INSERT_TAIL(ht->lru_head, elt, next_lru);

    /* Search the position of this (maybe) old hash element
     * in order to remove it */
    old_hash = ht_hash(elt->mac);
    ret = _ht_hash_lookup(ht, elt->mac, old_hash);
    if (ret != NULL) {
        assert(elt == ret);
        LIST_REMOVE(ret, next);
    }

    /* reset element with new mac address and then
     * insert it in hash */
    ht_elt_reset(elt, mac);
    LIST_INSERT_HEAD(&(ht->elt_heads)[hash & (ht->size - 1)], elt, next);

    return elt;
}

void
ht_print_lru_content(const ht_t * ht) {
    ht_elt_t *p;
    TAILQ_FOREACH(p, ht->lru_head, next_lru) {
        printf("%s\n", &(p->mac));
    }
}