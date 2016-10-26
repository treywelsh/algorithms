#ifndef HASH_ELT_H_
#define HASH_ELT_H_

#include <assert.h>
#include <sys/queue.h>
#include <string.h>

/* For each new usage of this implementation of hash table,
 * this header has to be redefined.
 */

struct ht_key {
    char * word;
    size_t len;
};
typedef struct ht_key ht_key_t;

/* Hastable entry */
struct ht_elt {
    SLIST_ENTRY(ht_elt) next;
    LIST_ENTRY(ht_elt) next_lru;

    /* key */
    ht_key_t key;

    /* value */
    unsigned int count;

    /* remove padding warning */
    unsigned int padding;
};
typedef struct ht_elt ht_elt_t;


static inline void 
ht_elt_reset(ht_elt_t * e) {
    const ht_key_t null = { .word = NULL, .len = 0};
    e->key = null;
    e->count = 0;
}

static inline void
ht_key_print(const ht_key_t * k) {
    if (k->word != NULL) {
        printf("%*s\n", k->len, k->word);
    }
}

static inline int
ht_elt_cmp(const ht_key_t * e1, const ht_key_t * e2) {
    assert(e1 != NULL);
    assert(e1->word != NULL);
    assert(e1->len > 0);

    assert(e2 != NULL);
    assert(e2->word != NULL);
    assert(e2->len > 0);

    if (e1->len != e2->len) {
        return 1;
    }
    return strncmp(e1->word, e2->word, e1->len);
}

/* Jenkins one at a time hash algorithm */
static inline size_t
ht_hash(const ht_key_t * k) {
    size_t hash;
    size_t i;

    assert(k != NULL);
    assert(k->word != NULL);

    hash = 0;
    for (i = 0; i < k->len; i++)
    {
        hash += (k->word)[i]; /* differ signedness*/
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

#endif /* HASH_ELT_H_ */
