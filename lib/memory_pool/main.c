#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "pool.h"

int test_case(void);

#define POOL_TEST_SZ 100
#define POOL_ELT_SZ 64

#define INIT_CHAR 'a'

int
test_case(void) {
     struct pool p;
     void * ret[POOL_TEST_SZ];
     unsigned int indexes[] = {10, 0, 50, 6, 90};
     unsigned int indexes_len = 5;
     unsigned int i;
     unsigned char test_data[POOL_ELT_SZ];

     memset(test_data, INIT_CHAR, POOL_ELT_SZ);

     printf("init pool...\n");
     pool_init(&p, POOL_TEST_SZ, POOL_ELT_SZ);

     assert(pool_is_full(&p));

     printf("alloc all elements and copy data...\n");
     for (i = 0; i < POOL_TEST_SZ; i++) {
         ret[i] = pool_alloc(&p);
         assert(ret[i] != NULL);
         pool_safe_memcpy(&p, ret[i], test_data, POOL_ELT_SZ);
     }

     assert(pool_is_empty(&p));
     assert(pool_alloc(&p) == NULL);

     printf("free some elements...\n");
     for (i = 0; i < indexes_len; i++) {
        pool_free(&p, ret[indexes[i]]);
     }
     assert(!pool_is_empty(&p));

     printf("alloc previous freed elements and write data...\n");
     for (i = 0; i < indexes_len; i++) {
        ret[indexes[i]] = pool_alloc(&p);
        assert(ret[indexes[i]] != NULL);
        assert(((char *)ret[indexes[i]])[POOL_ELT_SZ - 1] == INIT_CHAR); /* test a byte */
        memset(ret[indexes[i]], 0, POOL_ELT_SZ);
     }

     printf("free all elements...\n");
     for (i = 0; i < POOL_TEST_SZ; i++) {
         pool_free(&p, ret[i]);
     }

     printf("clean pool...\n");
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
