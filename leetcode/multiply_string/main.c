#include <stdio.h>
#include <string.h>

/*
 * O(nm) in time
 * O(1) in space
 *
 * Trachtenberg multiplication
 */

char res[256];

char * multiply(char* n1, char* n2) {
    int i, j, max_len, min_len, swap_len;
    int p, sum, remainder, prev_remainder;
    char * max_n, *min_n;

    if (!strcmp(n1, "0") || !strcmp(n2, "0")) {
        return "0";
    }

    memset(res, '\0', 256);

    max_len = strlen(n1);
    min_len = strlen(n2);
    max_n = n1;
    min_n = n2;
    if (min_len > max_len) {
        swap_len = max_len;
        max_len = min_len;
        min_len = swap_len;
        max_n = n2;
        min_n = n1;
    }

    prev_remainder = 0;
    /* i is the index of the digit being computed */
    for (i = max_len - 1 ; i >= - min_len + 1 ; i--) {
        remainder = 0;
        sum = 0;
        for (j = min_len - 1 ; j >= 0 ; j--) {
            /* Avoid bad indexes */
            if (i + min_len - 1 - j > max_len - 1 || i + min_len - 1 - j < 0) {
                continue;
            }
            p = (max_n[i + min_len - 1 - j] - '0') * (min_n[j] - '0');
            remainder += p / 10;
            sum += p % 10;
        }
        sum += prev_remainder;
        remainder += sum / 10;
        prev_remainder = remainder;
        res[min_len + i] = sum % 10 + '0';
    }

    /* last remainder digit */
    if (remainder > 0) {
        res[0] = remainder + '0';
    } else {
        return res + 1;
    }

    return res;
}

void
test_case(char * n1, char * n2) {
    printf("==============================\n");
    printf("%s * %s = %s\n", n1, n2, multiply(n1, n2));
}


    int
main(int argc, char ** argv)
{
    test_case("123456", "0");
    test_case("123456", "789");
    test_case("11", "11");
    test_case("4", "4");
    test_case("10", "4");
    test_case("4", "10");
    test_case("15", "4");
    test_case("4", "15");
    test_case("99", "10");
    test_case("123", "456");
    return 0;
}
