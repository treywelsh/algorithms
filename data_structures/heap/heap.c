#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int
heap_init(struct heap* h, size_t max_len) {

    assert(h != NULL);
    assert(max_len >= 2);

    h->val = malloc(sizeof(*(h->val)) * (max_len + 1));
    if (h->val == NULL) {
        return 1;
    }
    h->val[0] = 0; /* index 0 is excluded. Correspond to empty heap. */
    h->len = max_len;
    h->last = 0;
    return 0;
}

void
heap_clean(struct heap* h) {
   free(h->val);
}

void
heap_display(struct heap * h) {
    size_t i;
    for (i = 1 ; i < h->last + 1 ; i++) {
        printf("%d ", h->val[i]);
    }
    printf("\n");
}

static inline void
heap_up(struct heap* h, size_t idx) {
    size_t i, parent;
    int node;

    assert(h != NULL);
    assert(h->val != NULL);
    assert(h->len > 2);
    assert(h->last <= h->len);
    assert(idx <= h->last);
    assert(idx > 0);

    i = idx;
    node = h->val[idx];
    for ( parent = i >> 1 ; parent >= 1 ; parent = i >> 1 ) {
#ifdef HEAP_MAX
        if (node > h->val[parent]) {
#else
        if (node < h->val[parent]) {
#endif
            /* insert node */
            break;
        }
        h->val[i] = h->val[parent];
        i = parent;
    }
    h->val[i] = node;
}

static inline void
heap_down(struct heap* h, size_t idx) {
    size_t i, left, right, max_son;
    int node;

    assert(h != NULL);
    assert(h->val != NULL);
    assert(h->len >= 2);
    assert(h->last <= h->len);
    assert(idx > 0);

    if (idx >= h->last) {
        return;
    }

    i = idx;
    node = h->val[idx];
    for ( left = i << 1 ; left <= h->last ; left = i << 1) {
        right = left + 1;
        max_son = left;
#ifdef HEAP_MAX
        if (right <= h->last && h->val[right] < h->val[left]) {
#else
        if (right <= h->last && h->val[right] > h->val[left]) {
#endif
           max_son = right;
        }
#ifdef HEAP_MAX
        if (node < h->val[max_son]) {
#else
        if (node > h->val[max_son]) {
#endif
            /* insert node */
            break;
        }
        /* value at i index go down */
        h->val[i] = h->val[max_son];
        i = max_son;
    }
    h->val[i] = node;
}

int
heap_push(struct heap* h, int elm) {

    assert(h != NULL);
    assert(h->val != NULL);
    assert(h->last <= h->len);

    /* heap full */
    if (h->last >= h->len) {
       return 1;
    }

    (h->last)++;
    h->val[h->last] = elm;
    heap_up(h, h->last);

    return 0;
}

int
heap_push_array(struct heap* h, int* array, size_t array_len) {
    size_t i, min_len;

    assert(h != NULL);
    assert(h->val != NULL);
    assert(h->last <= h->len);

    if (array == NULL || array_len < 2) {
       return 1;
    }

    min_len = array_len;
    if (array_len > h->len) {
        min_len = h->len;
    }
    min_len -= h->last;
    for (i = 0 ; i < min_len ; i++) {
        (h->last)++;
        h->val[h->last] = array[i];
        heap_up(h, h->last);
    }
    return 0;
}

int
heap_pop(struct heap* h, int *elm) {

    assert(h != NULL);
    assert(elm != NULL);
    assert(h->val != NULL);
    assert(h->last <= h->len);

    /* if heap is empty */
    if (h->last == 0) {
        *elm = h->val[0];
        return 1;
    }

    /* keep first value, swap it with last value, call down, and return it*/
    *elm = h->val[1];
    h->val[1] = h->val[h->last];
    (h->last)--;
    heap_down(h, 1);

    return 0;
}
