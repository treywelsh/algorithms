#ifndef HASH_H_
#define HASH_H_

#include <stdint.h>
#include <sys/queue.h>

#include "hash_elt.h"

/* Hastable */
struct ht {
    ht_elt_t * pool;

    /* Hash */
    LIST_HEAD(, ht_elt) *elt_heads;
    size_t size;

    /* LRU */
    TAILQ_HEAD(, ht_elt) *lru_head;
    size_t lru_max;
};
typedef struct ht ht_t;

/* hash table size : size = 2^pow_size
 * max_elt : pool size */
int ht_init(ht_t * h, size_t pow_size, size_t max_elt);
void ht_clean(ht_t * h);

/* look for a key, if not found, return least recent used */
ht_elt_t * ht_lookup(ht_t * h, const ht_key_t * key);

/* print LRU in order to debug it */
void ht_print_lru_content(const ht_t * ht);

#endif /* HASH_H_ */
