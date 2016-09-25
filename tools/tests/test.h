#ifndef TEST_C_
#define TEST_C_

struct test_suite {
    unsigned int tests_count;
    unsigned int tests_failed;
};

int test_init(struct test_suite * ts);
int _test_assert(struct test_suite * ts, const char *test, char result);

#define test_assert(ts, t) _test_assert((ts), #t, (t))

int test_display(const struct test_suite * ts);

#endif /* TEST_C_ */
