#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*
 * O(n) time
 * O(n) space
 *
 */

/* Stack */
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

#define stack_size(s) \
    ((s)->last)

#define stack_get_last(s) \
    ((s)->val[(s)->last - 1])

/**
 *  Return an array of size *returnSize.
 *  Note: The returned array must be malloced, assume caller calls free().
 */
bool isValidBST(const struct TreeNode* root) {
    const struct TreeNode* node;
    struct stack stck;
    int prev, elt;
    bool first = true;

    if (root == NULL) {
        return true;
    }

    stack_init(&stck);

    node = root;
    do {
        if (node != NULL) {
            stack_push(&stck, node);
            node = node->left;
            continue;
        }
        if (!stack_is_empty(&stck)) {
            node = stack_pop(&stck);
            if (first == true) {
                prev = node->val;
                first = false;
            } else {
                elt = node->val;
                if (elt <= prev) {
                    return false;
                }
                prev = elt;
            }
        }
        //printf("right\n");
        node = node->right;
    } while (node != NULL || !stack_is_empty(&stck));

    return true;
}

int
main(void) {
    bool ret;
    struct TreeNode t1 = { .val = 1, .left = NULL, .right = NULL };
    struct TreeNode t2 = { .val = 2, .left = NULL, .right = NULL };
    struct TreeNode t3 = { .val = 3, .left = NULL, .right = NULL };
    struct TreeNode t4 = { .val = 4, .left = NULL, .right = NULL };
    struct TreeNode t5 = { .val = 5, .left = NULL, .right = NULL };
    struct TreeNode t6 = { .val = 6, .left = NULL, .right = NULL };
    /*
    t1.left = &t2 ; t1.right = &t3;
    t2.left = &t4 ; t2.right = &t5;
    t3.left = &t6 ;
    */
    //t1.left = &t2 ; t1.right = &t3;
    t2.left = &t1 ; t2.right = &t3;

    ret = isValidBST(&t2);
    if (ret == true) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    return 0;
}
