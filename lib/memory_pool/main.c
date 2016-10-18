#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "pool.h"

int test_case(void);

#define POOL_TEST_SZ 100

int
test_case(void) {
     struct pool p;
     void * ret[POOL_TEST_SZ];
     unsigned int indexes[] = {10, 0, 50, 6, 90};
     unsigned int indexes_len = 5;
     unsigned int i;

     pool_init(&p, POOL_TEST_SZ, 64);

     assert(pool_is_full(&p));

     for (i = 0; i < POOL_TEST_SZ; i++) {
         ret[i] = pool_alloc(&p);
         assert(ret[i] != NULL);
         memset(ret[i], 0, 64); /* don't write more than element size bytes
                                 * or memory errors will occur
                                 */
     }

     assert(pool_is_empty(&p));
     assert(pool_alloc(&p) == NULL);

     for (i = 0; i < indexes_len; i++) {
        pool_free(&p, ret[indexes[i]]);
     }
     assert(!pool_is_empty(&p));

     for (i = 0; i < indexes_len; i++) {
        ret[indexes[i]] = pool_alloc(&p);
        assert(ret[indexes[i]] != NULL);
        memset(ret[indexes[i]], 0, 64);
     }

     for (i = 0; i < POOL_TEST_SZ; i++) {
         pool_free(&p, ret[i]);
     }

     pool_free(&p, ret[0]);

     ret[1] = pool_alloc(&p);
     assert(ret[1] != NULL);
     memset(ret[1], 0, 64);

     pool_free(&p, ret[1]);

     pool_clean(&p);

    return 0;
}

int
main (int argc, char *argv[]) {
    (void)argc;
    (void)argv;


    test_case();


    return 0;
}
