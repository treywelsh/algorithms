#include <stdio.h>
#include "bst.h"

int
main (int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    struct bst b;
    int i, idx, ret, a;

    bst_init(&b, 1000);

    for (i = 9 ; i < 15 ; i++) {
        bst_insert(&b, i);
    }
    for (i = 8 ; i > 0 ; i--) {
        bst_insert(&b, i);
    }
    for (i = 7 ; i < 13 ; i++) {
        bst_insert(&b, i);
    }

    a = 12;
    ret = bst_find(&b, a, &idx);
    if (ret) {
        printf("%d found at %d\n", a, idx);
    }

    printf("inorder traversal : \n");
    bst_inorder(&b);

    bst_clean(&b);
    return 0;
}
