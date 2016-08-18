#include <stdio.h>
#include "heap.h"

int
test_case(int * array, size_t array_len) {
    size_t i;
    int ret;
    struct heap h;

    printf("--------test case-------\n");
    printf("array = ");
    for (i = 0 ; i < array_len ; i++) {
        printf("%u ", array[i]);
    }
    printf("\n");

    heap_init(&h, 100);

    printf("push...\n");
    for (i = 0 ; i < array_len ; i++) {
        if (heap_push(&h, array[i])) {
            printf("heap full\n");
            break;
        }
    }

    /* display_heap(&h); */
    printf("pop...\n");
    for (i = 0 ; i < array_len + 2 ; i++) {
        if(heap_pop(&h, &ret)) {
            printf("\nheap empty\n");
            break;
        }
        printf("%u ", ret);
    }
    printf("\n");

    heap_clean(&h);

    return 0;
}

int
main (int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    int array[] = { 0, 4, 72, 0, 4, 0, 4, 5, 6, 7, \
                    6, 45, 3, 6, 6, 5, 6, 0, 10, 100, \
                    6, 45, 3, 6, 8, 5, 6, 0, 10, 100, \
                    6, 45, 3, 8, 6, 5, 9, 0, 10, 100, \
                    6, 45, 3, 8, 8, 5, 6, 0, 10, 100, \
                    6, 45, 7, 8, 6, 5, 6, 0, 10, 100, \
                    6, 45, 3, 6, 6, 5, 9, 0, 10, 100, \
                    6, 45, 7, 6, 8, 9, 6, 0, 10, 100, \
                    6, 45, 3, 6, 6, 5, 6, 0, 10, 100, \
                    6, 45, 3, 6, 6, 5, 9, 0, 10, 100, \
                    6, 45, 7, 9, 8, 9, 6, 0, 10, 100, \
                    6, 45, 3, 6, 6, 5, 6, 0, 10, 100, \
                    6, 45, 3, 6, 6, 5, 9, 0, 10, 100, \
                    6, 45, 3, 6, 6, 5, 6, 0, 10, 100, \
                    1000000, 19, 15, 23, 543, 64, 646, 4, 5, 10 };
    test_case(array, 140);
    int array1[] = { 1, 0 };
    int array2[] = { 4, 5, 6, 7 };
    //int array3[] = { 4 }; /* does not work with push array  */
    int array4[] = { 5, 4, 4 };
    int array5[] = { 4, 4, 5 };
    //int array6[] = { }; /* does not work with push array */
    test_case(array, 21);
    test_case(array1, 2);
    test_case(array2, 4);
    //test_case(array3, 1); /* does not work with push array */
    test_case(array4, 3);
    test_case(array5, 3);
    //test_case(array6, 0); /* does not work with push array */
    //test_case(NULL, 0); /* does not work with push array */

    return 0;
}
