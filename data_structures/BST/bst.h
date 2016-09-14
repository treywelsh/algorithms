#ifndef BST_H_
#define BST_H_

//#include "stack.h"

/* Single node with int values */
struct bst_node {
    int val;
    unsigned int left;
    unsigned int right;
};
#define BST_NULL 0
#define BST_FIRST 1
#define bst_has_child(n) ((n)->left | (n)->right)

#define node_init(n, value) do{ \
    (n)->val = (value); \
    (n)->left = BST_NULL; \
    (n)->right = BST_NULL; \
}while(0)

/* BST */
/* TODO stack empty positions ?
 * avoid reinsert all subnodes
 */
struct bst {
    struct bst_node * nodes;
    unsigned int nodes_len;
    unsigned int node_last;
    //struct stack free; /* discard node_last */
    //All in this stack at init time, check stack size !!! 
};
#define bst_is_full(b) ((b)->node_last == (b)->nodes_len)
#define bst_is_empty(b) ((b)->node_last == BST_FIRST)
#define bst_node_count(b) ((b)->node_last - BST_FIRST)
//#define bst_get_node(b, i) ((b)->nodes[(i)])

int bst_init(struct bst* b, unsigned int max_len);
void bst_clean(struct bst* b);

int bst_insert(struct bst* b, int elm);
int bst_remove(struct bst* b, int elm);
int bst_find(struct bst* b, int elm, unsigned int *ret);
int bst_inorder(struct bst* b);

#endif /* BST_H_ */
