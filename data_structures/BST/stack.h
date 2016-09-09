#ifndef STACK_H_
#define STACK_H_

#define STACK_LEN 100
struct stack {
    //unsigned int *v;
    //unsigned v_len;
    unsigned int v[STACK_LEN];
    unsigned last;
};

#define stack_init(s) \
    (s)->last = 0
    //(s)->v_len = len

#define stack_is_empty(s) \
    ((s)->last == 0)

#define stack_is_full(s) \
    ((s)->last == STACK_LEN - 1)
    //((s)->last == (s)->v_len)

#define stack_size(s) \
    ((s)->last)

#define stack_push(s, e) \
    (s)->v[((s)->last)++] = (e)

#define stack_pop(s) \
    ((s)->v[--((s)->last)])

#endif /* STACK_H_ */
