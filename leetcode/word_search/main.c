#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
 * O() in time
 * O() in size
 *
 *
 */

#define STACK_LEN 100
struct stack {
    const struct TreeNode* val[STACK_LEN];
    size_t last;
};

#define stack_init(s) \
    (s)->last = 0; \

#define stack_is_empty(s) \
    ((s)->last == 0)

#define stack_size(s) \
    ((s)->last)

#define stack_push(s, e) \
    (s)->val[((s)->last)++] = (e)

#define stack_pop(s) \
    ((s)->val[--((s)->last)])

bool dfs(char** board, int boardRowSize, int boardColSize, char* word, int i, int j) {
    struct stack backtrack;
    
}

bool exist(char** board, int boardRowSize, int boardColSize, char* word) {
    int i, j;
    for (i = 0 ; i < boardRowSize ; i++) {
        for (j = 0 ; j < boardRowSize ; j++) {

        }
    }
}

void
test_case(const char * string, const char * pattern) {
    printf("==============================\n");
    //printf("str=%s pat=%s match=%d\n", string, pattern, isMatch(string, pattern));
}

int
main(int argc, char ** argv)
{
    //test_case("", "");
    return 0;
}
