#ifndef HEAP_H_
#define HEAP_H_

/* The elements are of type int */
struct heap {
    int* val;
    size_t len;
    size_t last; /* index of last inserted value */
};

#define HEAP_MAX

int heap_init(struct heap* h, size_t max_len);
void heap_clean(struct heap* h);
void heap_display(struct heap * h);

int heap_push(struct heap* h, int elm);
int heap_push_array(struct heap* h, int* array, size_t array_len);
int heap_pop(struct heap* h, int *elm);

#endif /* HEAP_H_ */
