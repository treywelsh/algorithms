#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <float.h>

/* Compute a^b
 * Complexity O(log b) 
 * Limitation on "unsigned long long" max type value.
 */

double 
fast_exp(double a, int b) {
    char b_sign;
    double result;
    double ap2;
    unsigned long long p2;
    unsigned long long rest;

    /* variable 'a' has to be different from 0 in order to check
     * overflow.
     */
    if (a == 0) {
        if (b == 0) {
            return 1;
        }
        return 0;
    }
    result = 1;
    p2 = 1;
    ap2 = a;
    b_sign >>= sizeof(int) * 8 - 1;
    rest = b_sign * b;

    while (rest > 0) {
        if (p2 & rest) {
            result *= ap2;
            //need to test result against DBL_MAX ?
            rest ^= p2;
        }
        p2 = p2 << 1;
        if (ap2 > (DBL_MAX / ap2)) {
            return 0;
        }
        ap2 *= ap2;
    }
    if (b_sign < 0)
        return 1/result;
    return result;
}

/* TODO update for double values */
static inline int 
convert_number(const char * str,
               unsigned long long * number) {
    char *end;

    if (str[0] == '-') {
        fprintf(stderr, "error : you have to give a positive number\n");
        return 1; 
    }
    //double strtod(const char *nptr, char **endptr);
    *number = strtoull(str, &end, 10);
    if (*number == ULLONG_MAX 
        && errno == ERANGE) {
        fprintf(stderr, "error : first number exceed variable limit\n");
        return 1;
    } 
    if (end == str) {
        fprintf(stderr, "No digits were found\n");
    }
    return 0;
}

int
main (int argc, char *argv[]) {
    unsigned long long a;
    unsigned long long b;
    unsigned long long res;
    int ret;

    if (argc != 3) {
        printf("USAGE: %s <a> <b>\na and b has to be unsigned integers.\n", argv[0]);
        return 1;
    }
    errno = 0;

    ret = convert_number(argv[1], &a);
    if (ret != 0) {
        fprintf(stderr, "error : can't convert number %s\n", argv[1]);
        return ret;
    }

    ret = convert_number(argv[2], &b);
    if (ret != 0) {
        fprintf(stderr, "error : can't convert number %s\n", argv[2]);
        return ret;
    }

    printf("%llu^%lld = %f\n", a, b, fast_exp(a, b));

    return 0;
}
