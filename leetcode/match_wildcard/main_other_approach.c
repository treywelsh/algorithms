#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
 * O() in time
 * O() in size
 *
 *
 */
#define LEN_MAX 4000
bool dyn[LEN_MAX][LEN_MAX];

bool isMatch(const char* string, const char* pattern) {
    size_t i, j, pi, pj;
    size_t pattern_len, string_len;
    bool star;

    pattern_len = strlen(pattern);
    string_len = strlen(string);

    /* empty strings */
    if (pattern_len + string_len == 0) {
        return true;
    }

    /* global case */
    i = 0;
    j = 0;
    pi = 0;
    pj = 0;
    star = false;
    while (i < string_len && j < pattern_len) {
        if (pattern[j] == string[i] || pattern[j] == '?') {
            j++;
            i++;
            star = false;
            continue;
        } else if (j < pattern_len && pattern[j] == '*') {
            j++;
            pi = i;
            pj = j;
            star = true;
            continue;
        }
        if (star) {
            i++;
            continue;
        }
        printf("pat %c\n", pattern[j]);
        printf("str %c\n", string[i]);
        /* Neither star, nor match */
        i = pi++; 
        j = pj; 
    }
    if (j == pattern_len - 1 && pattern[pattern_len - 1] != '*') {
        return false;
    } else if (j < pattern_len - 1) {
        return false;
    } else if (!star && j == pattern_len && i < string_len) {
       return false; 
    }
    return true;
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
    test_case("hi", "*?");
    test_case("", "*");
    test_case("a", "*");
    test_case("t", "*t");
    test_case("t", "t*");
    test_case("abc", "*");
    test_case("a", "?");
    test_case("aa", "a");
    test_case("a", "aa");
    test_case("atubic", "a*b?c");
    test_case("atubic", "*");
    test_case("atubic", "a*?c");
    test_case("atubicdkdal", "a*bkjfalsdkf?casdlfja");
    test_case("ho", "**ho");
    test_case("ho", "t**ho");
    test_case("b", "?*?");
    test_case("b", "*?*?");
    return 0;
}
