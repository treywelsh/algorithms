#ifndef HASH_ELT_H_
#define HASH_ELT_H_

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "err.h"

#define MAC_LEN 6

struct ht_key {
     uint8_t mac[MAC_LEN];
     uint16_t padding; /* Unused, remove warnings */
};
typedef struct ht_key ht_key_t;

#define ht_key_reset(k) \
    memset((k)->mac, 0, MAC_LEN)

#define ht_key_cpy(d, s) \
    memcpy((d)->mac, (s)->mac, MAC_LEN);

static inline int
ht_key_init(ht_key_t * k, uint8_t * mac, size_t mac_len) {
    if (mac_len != MAC_LEN) {
        fprintf(stderr, "Bad mac adress size\n");
        return ERROR;
    }
    memcpy(k->mac, mac, MAC_LEN);
    return SUCCESS;
}

static inline int
ht_key_cmp(const ht_key_t * k1, const ht_key_t * k2) {
    assert(k1 != NULL);
    assert(k2 != NULL);

    return memcmp(k1->mac, k2->mac, MAC_LEN);
}

/* Jenkins one at a time hash */
static inline size_t
ht_hash(const ht_key_t * k) {
    size_t hash;
    size_t i;

    assert(k != NULL);

    hash = 0;
    for (i = 0; i < MAC_LEN ; i++)
    {
        hash += (k->mac)[i];
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
    uint64_t count;
};
typedef struct ht_elt ht_elt_t;

static inline void 
ht_elt_reset(ht_elt_t * e) {
    ht_key_reset(&(e->key));

    /* reset value */
    e->count = 0;
}

#endif /* HASH_ELT_H_ */
