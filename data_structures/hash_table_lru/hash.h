#ifndef HASH_H_
#define HASH_H_

#include <sys/queue.h>
#include <string.h>

#include "hash_elt.h"

/* Return codes */
enum {
    SUCCESS = 0,
    HT_ALREADY_ADDED,
    HT_MALLOC_ERROR,
    HT_ERROR,
};

/* Hastable */
struct ht {
    SLIST_HEAD(, ht_elt) *heads_elt;
    size_t size;

    ht_elt_t * lru;
    LIST_HEAD(, ht_elt) *lru_head;
    size_t lru_max;
    size_t lru_i;
};
typedef struct ht ht_t;

int ht_init(ht_t * h, size_t pow_size, size_t max_elt); /* size = 2^pow_size */
void ht_clean(ht_t * h);

/* look for a key, if not found, return least recent used */
ht_elt_t * ht_lookup(ht_t * h, const ht_key_t *key);

#endif /* HASH_H_ */
