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

/* error case : 
 * test_case("b", "?*?");
 */
bool isMatch(const char* string, const char* pattern) {
    size_t i, j;
    size_t pattern_len, string_len;
    bool star_flag;

    star_flag = false;
    pattern_len = strlen(pattern);
    string_len = strlen(string);
    /* corner cases : empty string etc */
    if (pattern_len && pattern[0] == '*') {
        return true;
    }

    /* global case */
    i = 0;
    j = 0;
    while (i < string_len && j < pattern_len) {
        if (pattern[j] == string[i] || pattern[j] == '?') {
            /* next pattern char */
            j++;
            star_flag = false;
        } 
        if (pattern[j] == '*') {
            star_flag = true;
            j++;
        }
        i++;
    }
    //problem on one letter patterns
    //test_case("b", "?*?");
    //test_case("b", "*?*?");
    //test_case("b", "*?*b");
    //if (pattern[j] == '?' || !star_flag && (j < pattern_len || i < string_len)) {
    if (!star_flag && (j < pattern_len || i < string_len)) {
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
    test_case("b", "?*?");
    test_case("b", "?*?");
    return 0;
}
