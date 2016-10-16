#include <stdio.h>

#include <err.h>
#include <stack.h>


int test_case(void);

int
test_case(void) {
    unsigned int i;
    unsigned int ret;
    stack_t s;

    stack_init(&s, 5);

    for (i = 0 ; i < 10 ; i++) {
        stack_safe_push(&s, i); /* No error will occur
                                 * even if the stack is full */
    }

    ret = 0;
    for (i = 0 ; i < 10 ; i++) {
        if (stack_is_empty(&s)) {
            printf("stack is empty\n");
        } else {
            ret = stack_pop(&s); /* not safe but the stack
                                  * has been previoulsy checked */
            printf("%u\n", ret);
        }
    }

    stack_clean(&s);

    return 0;
}


INIT_ERR();

int
main (int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    SET_ERR(stdout);

    test_case();

    return 0;
}
