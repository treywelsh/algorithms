#ifndef HASH_ELT_H_
#define HASH_ELT_H_

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/queue.h>

#define MAC_LEN 6

/* TODO only this header is user redefined ?? useless, merge headers ? 
 * struct ht_elt_key {
 *      uint8_t mac[MAC_LEN];
 * };
 * typedef struct ht_elt_key ht_elt_key_t;
 * */

/* Hastable entry */
struct ht_elt {
    LIST_ENTRY(ht_elt) next;

    TAILQ_ENTRY(ht_elt) next_lru;

    /* key */
    /* ht_elt_key_t key*/
    uint8_t mac[MAC_LEN];

    /* value */
    unsigned int count;
};
typedef struct ht_elt ht_elt_t;


static inline void 
ht_elt_reset(ht_elt_t * e, const uint8_t * mac) {
//ht_elt_reset(ht_elt_t * e, ht_elt_key_t * key) {

    //assert(strlen((char *)(key->mac)) == MAC_LEN);
    assert(strlen((char *)mac) == MAC_LEN);

    memcpy((char *)(e->mac), (char *)mac, MAC_LEN);
    e->count = 0;

    LIST_NEXT(e, next) = NULL;
}

static inline int
ht_elt_cmp(const uint8_t * e1, const uint8_t * e2) {
    assert(e1 != NULL);
    assert(e2 != NULL);

    return strncmp((char *)e1, (char *)e2, MAC_LEN);
}

/* Jenkins one at a time hash algorithm */
static inline size_t
ht_hash(const uint8_t * k) {
    size_t hash;
    size_t i;

    assert(k != NULL);

    hash = 0;
    for (i = 0; i < MAC_LEN; i++)
    {
        hash += k[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

#endif /* HASH_ELT_H_ */
