#include <stdio.h>
#include <string.h>

/*
 * O(nm) in time
 * O(nm) in space
 */

#define LEN_MAX 1000
int A[LEN_MAX];

int minDistance(const char* w1, const char* w2) {
    size_t i, j;
    size_t w1_len, w2_len;
	size_t prev, min;

    w1_len = strlen(w1);
    w2_len = strlen(w2);

	if (w1_len == 0 || w2_len == 0) {
		return w1_len | w2_len;
	}

	for (j = 0 ; j <= w2_len; j++) {
		A[j] = j;
	}
    for (i = 0 ; i < w1_len ; i++) {
		A[0] = i;
		prev = i;
        for (j = 1 ; j <= w2_len ; j++) {
			min = A[j - 1] + (w1[i] != w2[j - 1]);
			if (min > prev + 1) {
				min = prev + 1;
			}
			if (min > A[j] + 1) {
				min = A[j] + 1;
			}
			A[j - 2] = prev;
			prev = min;
        }
    }

    return min;
}

void
test_case(const char * w1, const char * w2) {
    printf("==============================\n");
    printf("w1=%s w2=%s edit_distance=%d\n", w1, w2, minDistance(w1, w2));
}


    int
main(int argc, char ** argv)
{
    //test_case("", "");
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
