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
_test_ok(struct test_suite * ts, const char *test, char result, FILE * s, char * msg) {
    const char * str;
    if (ts == NULL || test == NULL) {
        return 1;
    }

    (ts->tests_count)++;

    if (!result) {
        (ts->tests_failed)++;
        str = "FAILED";
    } else {
        str = "OK";
    }
    if (s != NULL) {
        fprintf(s, "%-40s %-40s %s\n", msg, test, str);
    }
    return 0;
}

int
test_display(const struct test_suite * ts) {
    if (ts == NULL) {
        return 1;
    }
    printf("=== Test suite ===\nfailed : %u\ntotal : %u\n",
            ts->tests_failed, ts->tests_count);
    return 0;
}
