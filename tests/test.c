#include <stdio.h>
#include "test.h"

int
test_init(struct test_suite * ts) {
    if (ts == NULL) {
        return 1;
    }
    ts->tests_count = 0;
    ts->tests_failed = 0;
    return 0;
}

int
_test_assert(struct test_suite * ts, const char *test, char result) {
    if (ts == NULL || test == NULL) {
        return 1;
    }
    (ts->tests_count)++;
    printf("\"%s\" : ", test);
    if (result) {
        printf("OK\n");
        return 0;
    }
    (ts->tests_failed)++;
    printf("FAILED\n");
    return 0;
}
int
test_display(const struct test_suite * ts) {
    if (ts == NULL) {
        return 1;
    }
    printf("=== results ===\ncount : %u\nfailed : %u\n", ts->tests_count, ts->tests_failed);
    return 0;
}
