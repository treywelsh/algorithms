#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stack.h>

#include "bst.h"

int
bst_init(struct bst* b, unsigned int max_len) {

    assert(b != NULL);
    assert(max_len >= 3);

    b->nodes = malloc(sizeof(*(b->nodes)) * (max_len + 1));
    if (b->nodes == NULL) {
        return 1;
    }
    b->nodes_len = max_len;
    b->node_last = BST_FIRST; /* Index 0 is the null node */
    memset(b->nodes, 0, sizeof(*(b->nodes)) * (max_len + 1));

    return 0;
}

void
bst_clean(struct bst* b) {
    assert(b != NULL);
    free(b->nodes);
}

static int
__bst_find(struct bst * b, int elm, unsigned int * index, unsigned int * parent_index) {
    unsigned int i, i_prev;

    assert(b != NULL);
    assert(b->nodes != NULL);
    assert(index != NULL);
    assert(parent_index != NULL);

    *index = BST_NULL;
    *parent_index = BST_NULL;

    /* if bst is empty */
    if (bst_is_empty(b)) {
        printf("empty, cannot find any node\n");
        return 1;
    }

    i_prev = BST_NULL;
    i = BST_FIRST;
    while ((b->nodes[i]).val != elm) {
        i_prev = i;
        if (elm > (b->nodes)[i].val && (b->nodes)[i].right != BST_NULL) {
            i = (b->nodes[i]).right;
        } else if (elm < (b->nodes[i]).val && (b->nodes)[i].left != BST_NULL) {
            i = (b->nodes[i]).left;
        } else {
            /* if there is neither left son nor right son
             * and current node does not contains the right value
             */
            return 0;
        }
    }

    *parent_index = i_prev;
    *index = i;
    return 1;
}

/*
   static int
   __bst_insert(unsigned int root_index, int elm) {
//unsigned int i, i_prev;
return 0;
}
*/

int
bst_insert(struct bst* b, int elm) {
    struct bst_node * bnode;
    unsigned int i;

    assert(b != NULL);
    assert(b->nodes != NULL);

    if (bst_is_full(b)) {
        printf("full, cannot insert\n");
        return 1;
    }


    /* Look for insertion point in tree */
    i = BST_FIRST;
    while(i <= b->node_last) {
        bnode = &(b->nodes)[i];

        if (elm > bnode->val && bnode->right != BST_NULL) {
            i = bnode->right;
            continue;
        } else if (elm <= bnode->val && bnode->left != BST_NULL) {
            i = bnode->left;
            continue;
        }

        /* link to parent node*/
        if (elm > bnode->val) {
            bnode->right = b->node_last;
        } else {
            bnode->left = b->node_last;
        }
        break;
    }

    /* Copy node at end of array */
    node_init(&((b->nodes)[b->node_last]), elm);
    (b->node_last)++;

    return 0;
}

int
bst_remove(struct bst* b, int elm) {
    unsigned int i, i_prev;

    assert(b != NULL);
    assert(b->nodes != NULL);

    if (bst_is_empty(b)) {
        printf("empty, cannot remove\n");
        return 1;
    }

    if (!__bst_find(b, elm, &i, &i_prev)) {
        return 1;
    }

    if (i == (b->nodes)[i_prev].left) {
        (b->nodes[i_prev]).left = BST_NULL;
    } else {
        (b->nodes[i_prev]).right = BST_NULL;
    }

    //http://www.algolist.net/Data_structures/Binary_search_tree/Removal

    /* TODO if node had childs, reconstruct subtree */
    /*
     * (b->nodes[i]).left = BST_NULL;
     * (b->nodes[i]).right = BST_NULL;
     *
     */

    return 0;
}

int
bst_find(struct bst* b, int elm, unsigned int *ret) {
    unsigned int i, i_prev;

    assert(b != NULL);
    assert(b->nodes != NULL);
    assert(ret != NULL);

    i = BST_NULL;
    i_prev = BST_NULL;
    *ret = BST_NULL;

    if (!__bst_find(b, elm, &i, &i_prev)) {
        return 0;
    }
    *ret = i;

    return 1;
}

#define STACK_SIZE 1024
/*
 * struct bst_inorder_iter {
 *  struct bst* b;
 *  struct stack stck;
 *  unsigned int node_i;
 * }
 *
 * int
 * bst_inorder_iter_init(struct bst* b, struct bst_inorder_iter * it) {
 *    if (bst_is_empty(b)) {
 *        return 1;
 *    }
 *
 *    stack_init(&stck, STACK_SIZE);
 *    node_i = BST_FIRST;
 *
 *  return 0;
 * }
 *
 *
 * int
 * bst_inorder_iter_next(struct bst_inorder_iter * it) {
 *
 *  return 0;
 * }
 *
 * int
 * bst_inorder_iter_clean(struct bst_inorder_iter * it) {
 *
 *      stack_clean(&it->stck);
 *      return 0;
 * }
 */
int bst_inorder(struct bst* b) {
    unsigned int node_i;
    struct stack stck;

    if (bst_is_empty(b)) {
        return 1;
    }

    stack_init(&stck, STACK_SIZE);

    //prev_node_i = BST_NULL;
    node_i = BST_FIRST;
    do {
        if (node_i != BST_NULL) {
            assert(!stack_is_full(&stck));
            stack_push(&stck, node_i);
            node_i = ((b->nodes)[node_i]).left;
            continue;
        }
        if (!stack_is_empty(&stck)) {
            node_i = stack_pop(&stck);
            //TODO return array or make an iterator ?
            printf("%d ", ((b->nodes)[node_i]).val);
            //prev_node_i = node;
        }
        node_i = ((b->nodes)[node_i]).right;
    } while (node_i != BST_NULL || !stack_is_empty(&stck));
    //TODO
    printf("\n");

    stack_clean(&stck);

    return 0;
}

