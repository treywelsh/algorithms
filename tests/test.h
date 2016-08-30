#ifndef TEST_C_
#define TEST_C_

#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

uint32_t tests_count = 0; 
static uint32_t tests_passed = 0; 

static inline void _assert(char *test, char result) {
    tests_count++;
    printf("\"%s\" : ", test);
    if (result) {
        tests_passed++;
        printf("OK\n");
        return;
    }
    printf("FAILED\n");
}

#define test_assert(t) _assert(#t, (t))




#endif /* TEST_C_ */
