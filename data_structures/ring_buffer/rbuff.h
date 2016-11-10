#ifndef RBUFF_H_
#define RBUFF_H_

#include <assert.h>
#include <stdlib.h>

/* NOTE: redefine type of "buf" field in order to adapt
 * this implementation to your needs.
 */

struct rbuf {
    int * buf;
    unsigned int bufmask;
    unsigned int w_i;
    unsigned int r_i;
};
typedef struct rbuf rbuf_t;

static inline int
rbuff_init(rbuf_t * b, size_t b_two_pow_sz) {
    size_t size;

    assert(b != NULL);

    size = 1 << b_two_pow_sz;

    b->buf = malloc(size * sizeof(*(b->buf)));
    if (b->buf == NULL) {
        return 1;
    }
    b->w_i = 0;
    b->r_i = 0;
    b->bufmask = size - 1;

    return 0;
}

static inline void
rbuff_clean(rbuf_t * b) {
    assert(b != NULL);

    free(b->buf);
}

#define rbuff_is_full(rbf) ((rbf)->r_i == (((rbf)->w_i + 1) & (rbf)->bufmask))
#define rbuff_is_empty(rbf) ((rbf)->w_i == (rbf)->r_i)

/* add an element */
#define rbuff_add(rbf, elt) do{ \
    if (rbuff_is_full((rbf))) { \
        (rbf)->r_i = ((rbf)->r_i + 1) & (rbf)->bufmask; \
    } \
    (rbf)->buf[(rbf)->w_i] = (elt); \
    (rbf)->w_i = ((rbf)->w_i + 1) & (rbf)->bufmask; \
}while(0)

/* access oldest element */
#define rbuff_get_last(rbf, elt) do{ \
    if(rbuff_is_empty((rbf))) { \
        (elt) = NULL; \
    } else { \
        (elt) = ((rbf)->buf)[(rbf)->r_i]; \
    } \
}while(0)

/* drop oldest element */
#define rbuff_drop(rbf) ((rbf)->r_i = ((rbf)->r_i + 1) & (rbf)->bufmask)

/* retrieve an element */
#define rbuff_get(rbf, elt) do{ \
    rbuff_get_last((rbf), (elt)); \
    rbuff_drop((rbf)); \
}while(0)

#endif /* RBUFF_H_ */
