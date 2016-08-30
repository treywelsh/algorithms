#include <stdio.h>
#include "rbuff.h"

int test_case(void);

int
test_case(void) {
    rbuf_t b = {0};
    size_t i;
    int a[] = { 5, 6, 3, 4, 2, 6, 7};

    /* add integers to the ring buffer */
    rbuff_init(&b, 3);
    printf("size %u\n", b.bufmask + 1);
    for (i = 0 ; i < 30 ; i++) {
        if (!rbuff_is_full(&b)) {
            printf("%zu added\n", i);
            rbuff_add(&b, a[i]);
            continue;
        }
        printf("total : %zu elements added\n", i);
        break;
    }

    rbuff_clean(&b);

    return 0;
}

int
main (int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    test_case();

    return 0;
}
