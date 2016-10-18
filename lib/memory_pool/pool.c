#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "errc.h"
#include "pool.h"

struct pool_free_elt {
    void * next;
};

/* NOTE: alignement is not checked
 * 
 */
int
pool_init(struct pool* p, uint32_t elt_count, uint32_t elt_size) {
    uint32_t area_len;
    uint32_t i;
    struct pool_free_elt * elt;

    assert(p != NULL);	
    assert(elt_count * elt_size > sizeof(struct pool_free_elt));

    area_len = elt_count * elt_size;

    p->area = malloc(area_len);
    if (p->area == NULL) {
        return POOL_MALLOC_ERROR;
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

    return SUCCESS;
}

void
pool_clean(struct pool* p) {
    assert(p != NULL);

    free(p->area);
}

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


int
pool_safe_memcpy(struct pool * p,
                void * dest,
                void * src,
                uint32_t src_len) {

    assert(p != NULL);
    assert(dest != NULL);
    assert(src != NULL);
    assert(src_len > 0);

    if (src_len > p->elt_size) {
        return ERROR;
    }

    memcpy(dest, src, p->elt_size);

    return SUCCESS;
}
