#ifndef STACK_H_
#define STACK_H_

struct stack {
    unsigned int *v;
    unsigned v_len;
    unsigned last;
};

#define stack_is_empty(s) \
    ((s)->last == 0)

#define stack_is_full(s) \
    ((s)->last == (s)->v_len - 1)

#define stack_size(s) \
    ((s)->last)

#define stack_push(s, e) \
    (s)->v[((s)->last)++] = (e)

#define stack_pop(s) \
    ((s)->v[--((s)->last)])

#define stack_get_last(s) \
    ((s)->v[((s)->last) - 1])

int stack_init(struct stack * st, unsigned int sz);
void stack_clean(struct stack * st);

#endif /* STACK_H_ */
