#include <stdlib.h>

#include "stack.h"

int
stack_init(struct stack * st, unsigned int sz) {
    if (st == NULL) {
        return 1;
    }
    st->v = malloc(sizeof(*(st->v)) * sz);
    if (st->v == NULL) {
       return 1;
    }
    st->v_len = sz;
    st->last = 0;

    return 1;
}

void
stack_clean(struct stack * st) {
    if (st == NULL) {
        return;
    }
    free(st->v);
}
