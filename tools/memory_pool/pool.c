#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "pool.h"

struct pool_free_elt {
    void * next;
};

int
pool_init(struct pool* p, unsigned int elt_count, unsigned int elt_size) {
    unsigned int area_len;
    unsigned int i;
    struct pool_free_elt * elt;

    assert(p != NULL);	
    assert(elt_count * elt_size > sizeof(struct pool_free_elt));
    //Suppose elt_size will align each element

    area_len = elt_count * elt_size; /* each element has to be aligned ... */

    p->area = malloc(area_len);
    if (p->area == NULL) {
        return 1;
    }
    p->area_len = area_len;

    elt = p->area;
    for (i = 0; i < elt_count - 1; i++) {
        elt->next = (void *)((size_t)elt + elt_size);
        elt = elt->next;
    }

    p->elt_count = elt_count;
    p->elt_size = elt_size;

    p->free = p->area;
    p->free_count = elt_count;

    return 0;
}

void
pool_clean(struct pool* p) {
    assert(p != NULL);

    free(p->area);
}

//TODO alignment ?
/*
static inline void *
pool_next_addr(const struct pool * p) {
    return (void *)((size_t)(p->area) + p->elt_size);
}
*/

void *
pool_alloc(struct pool * p) {
    void * elt;

    if (pool_is_empty(p)) {
        return NULL;
    }

    elt = p->free;
    p->free = ((struct pool_free_elt *)(p->free))->next;
    (p->free_count)--;

    return elt;
}

void
pool_free(struct pool * p, void * elt) {
    struct pool_free_elt * free_elt;

    if (pool_is_full(p)) {
        return;
    }

    free_elt = (struct pool_free_elt *)elt;

    free_elt->next = p->free;
    p->free = free_elt;
    (p->free_count)++;
}

/*
int
pool_safe_write(struct pool * p, void * pool_chunk, void * data, size_t data_len) {
     * if (data_len > p->elt_size) {
     *  return 1;
     * }
     * memcpy(pool_chunk, data, p->elt_size);
     * return 0;
}
*/
