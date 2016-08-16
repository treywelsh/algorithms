#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
 * O(nm) in time
 * O(nm) in size
 *
 * Not optimal
 */
#define LEN_MAX 4000
bool dyn[LEN_MAX][LEN_MAX];

bool isMatch(const char* string, const char* pattern) {
    size_t i, j;
    size_t pattern_len, string_len;

    pattern_len = strlen(pattern);
    string_len = strlen(string);

    /* Initialize */
    dyn[0][0] = true;
    for (i = 1 ; i <= string_len ; i++) {
        dyn[i][0]   = false;
    }
    for (i = 1 ; i <= pattern_len ; i++) {
        if (pattern[i - 1] == '*' && dyn[0][i - 1] == true) {
            dyn[0][i]   = true;
            continue;
        }
        dyn[0][i]   = false;
    }

    /* Fill the array */
    for (i = 1 ; i <= string_len; i++) {
        for (j = 1 ; j <= pattern_len; j++) {
            if (pattern[j - 1] == string[i - 1]
                    || pattern[j - 1] == '?') {
                dyn[i][j] = dyn[i - 1][j - 1];
            }
            else if (pattern[j - 1] == '*' && (dyn[i][j - 1] || dyn[i - 1][j])) {
                dyn[i][j] = true;
            } else {
                dyn[i][j] = false;
            }
            printf("%d ", dyn[i][j]);
        }
        printf("\n");
    }

    return dyn[string_len][pattern_len];

}

void
test_case(const char * string, const char * pattern) {
    printf("==============================\n");
    printf("str=%s pat=%s match=%d\n", string, pattern, isMatch(string, pattern));
}


    int
main(int argc, char ** argv)
{
    test_case("", "");
    test_case("", "*");
    test_case("a", "*");
    test_case("t", "*t");
    test_case("t", "t*");
    test_case("abc", "*");
    test_case("a", "?");
    test_case("aa", "a");
    test_case("atubic", "a*b?c");
    test_case("atubic", "*");
    test_case("atubic", "a*?c");
    test_case("atubicdkdal", "a*bkjfalsdkf?casdlfja");
    test_case("ho", "**ho");
    test_case("ho", "t**ho");
    return 0;
}
