#include <stdio.h>
#include <string.h>

/*
 * O(nm) in time
 * O(2*n) in space
 */

#define LEN_MAX 1000
int A[2][LEN_MAX];

int minDistance(const char* w1, const char* w2) {
    size_t i, j;
    size_t w1_len, w2_len, tmp_len;
    size_t min;
    size_t line;
    const char * tmp;

    w1_len = strlen(w1);
    w2_len = strlen(w2);

    if (w1_len == 0 || w2_len == 0) {
        return w1_len | w2_len;
    }

    /* cache friendly if small word */
    if (w1_len > w2_len) {
        tmp = w1;
        w1 = w2;
        w2 = tmp;
        tmp_len = w2_len;
        w2_len = w1_len;
        w1_len = tmp_len;
    }

    line = 1;
    for (j = 0 ; j <= w2_len; j++) {
        A[0][j] = j;
    }
    for (i = 0 ; i < w1_len ; i++) {
        A[line][0] = i + 1;
        for (j = 0 ; j < w2_len ; j++) {
            min = A[line ^ 1][j] + (w1[i] != w2[j]);
            if (min > A[line][j] + 1) {
                min = A[line][j] + 1;
            }
            if (min > A[line ^ 1][j + 1] + 1) {
                min = A[line ^ 1][j + 1] + 1;
            }
            A[line][j + 1] = min;
        }
        line ^= 1;
    }

    return A[line ^ 1][w2_len];
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
    return 0;
}
