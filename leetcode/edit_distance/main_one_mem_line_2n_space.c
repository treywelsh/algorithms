#include <stdio.h>
#include <string.h>

/*
 * O(nm) in time
 * O(2*n) in space
 */

#define LEN_MAX 1000
int A[LEN_MAX];

int minDistance(const char* w1, const char* w2) {
    size_t i, j;
    size_t w1_len, w2_len, tmp_len;
    size_t min;
    size_t l_prev, l_curr, l2_off; /* each variable index a line of A */
    const char * tmp_w;

    w1_len = strlen(w1);
    w2_len = strlen(w2);

    if (w1_len == 0 || w2_len == 0) {
        return w1_len | w2_len;
    }

    /* The longer word define the A line size */
    if (w1_len > w2_len) {
        tmp_w = w1;
        w1 = w2;
        w2 = tmp_w;
        tmp_len = w2_len;
        w2_len = w1_len;
        w1_len = tmp_len;
    }

    l2_off = w2_len + 1;
    l_prev = 0;
    l_curr = l2_off;
    /* Init l_prev line */
    for (j = 0 ; j <= w2_len; j++) {
        A[j] = j;
    }
    for (i = 0 ; i < w1_len ; i++) {
        /* Init first column */
        A[l_curr] = i + 1;
        for (j = 0 ; j < w2_len ; j++) {
            min = A[l_prev + j] + (w1[i] != w2[j]);
            /* compare with left character */
            if (min > A[l_curr + j] + 1) {
                min = A[l_curr + j] + 1;
            }
            /* compare with left character */
            if (min > A[l_prev + j + 1] + 1) {
                min = A[l_prev + j + 1] + 1;
            }
            A[l_curr + j + 1] = min;
        }
        /* switch lines */
        l_curr = l_prev;
        l_prev ^= l2_off;
    }

    return A[l_prev + w2_len];
}

void
test_case(const char * w1, const char * w2) {
    printf("==============================\n");
    printf("w1=%s w2=%s edit_distance=%d\n", w1, w2, minDistance(w1, w2));
}


int
main(int argc, char ** argv)
{
    test_case("", "");
    test_case("a", "a");
    test_case("qwerty", "qwerty");
    test_case("a", "");
    test_case("a", "c");
    test_case("a", "ab");
    test_case("ab", "bc");
    test_case("adc", "abc");
    test_case("ade", "abc");
    test_case("a", "aaa");
    test_case("a", "abc");
    test_case("audi", "lada");
    test_case("aaaaaaaaaaaaaaaaaaaaudiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaladaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab");
    test_case("aaaaaaaaaaaaaaaaaaaladaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", "au");
    test_case("sea", "ate");
    return 0;
}
