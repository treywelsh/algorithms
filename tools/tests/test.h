#ifndef TEST_C_
#define TEST_C_

struct test_suite {
    unsigned int tests_count;
    unsigned int tests_failed;
};

int _test_ok(struct test_suite * ts, const char *test, char result, FILE * s, char * msg);

int test_init(struct test_suite * ts);
int test_display(const struct test_suite * ts);

#define test_ok(ts, t) _test_ok((ts), #t, (t), NULL, NULL)
#define test_ok_verbose(ts, msg, t) _test_ok((ts), #t, (t), stdout, msg)


#endif /* TEST_C_ */
