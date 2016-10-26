#ifndef HASH_ELT_H_
#define HASH_ELT_H_

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

struct ht_key {
     uint8_t * data;
     size_t data_len;
};
typedef struct ht_key ht_key_t;

#define ht_key_reset(k) do { \
    memset((k)->data, 0, (k)->data_len); \
    (k)->data_len = 0; \
}while(0)


static inline int 
ht_key_init(ht_key_t * k, uint8_t * data, size_t data_len) {
    assert(k != NULL);

    k->data = malloc(data_len);
    if (k->data == NULL) {
        return 1;
    }

    memcpy(k->data, data, data_len);
    k->data_len = data_len;

    return 0;
}

static inline void
ht_key_clean() {
    
}

static inline int
ht_key_cmp(const ht_key_t * k1, const ht_key_t * k2) {
    assert(k1 != NULL);
    assert(k2 != NULL);

    if (k1->data_len != k2->data_len) {
        return 1;
    }

    return memcmp(k1->data, k2->data, k1->data_len);
}

/* Jenkins one at a time hash algorithm */
static inline size_t
ht_hash(const ht_key_t * k) {
    size_t hash;
    size_t i;

    assert(k != NULL);

    hash = 0;
    for (i = 0; i < k->data_len; i++)
    {
        hash += (k->data)[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

/* Hastable entry */
struct ht_elt {
    LIST_ENTRY(ht_elt) next;
    TAILQ_ENTRY(ht_elt) next_lru;

    /* key */
    ht_key_t key;

    /* value */
    unsigned int count;
};
typedef struct ht_elt ht_elt_t;

static inline void 
ht_elt_reset(ht_elt_t * e) {
    LIST_NEXT(e, next) = NULL;
    TAILQ_NEXT(e, next_lru) = NULL;

    ht_key_reset(&(e->key));
    e->count = 0; /* TODO leave user manage this in his source file ? */
}

#endif /* HASH_ELT_H_ */
