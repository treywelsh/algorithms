#ifndef BLOOM_FILTER_
#define BLOOM_FILTER_

typedef unsigned int (*bf_hashfunc_t)(data);


struct bloom_filter {
     bf_hashfunc_t hash;
     unsigned int *bit_vect;
     unsigned int bit_vect_size;
};

struct bloom_filters {
    struct bloom_filter *bf;
    unsigned int bf_count;
};

#define BF_BIT_VECT_TYPE_SIZE sizeof(unsigned int)
#define BF_BIT_SET(BIT_VECT, N) ((BIT_VECT)[(N) / BIT_VECT_TYPE_SIZE] |= (1 << ((N) % BIT_VECT_TYPE_SIZE)))
#define BF_BIT_GET(BIT_VECT, N) ((BIT_VECT)[(N) / BIT_VECT_TYPE_SIZE] &  (1 << ((N) % BIT_VECT_TYPE_SIZE)))

bloom_filter_create(struct bloom_filter * bf, unsigned int size, bf_hashfunc_t hash)
bloom_filter_destroy(struct bloom_filter * bf, )
bloom_filter_insert(struct bloom_filter * bf, )
bloom_filter_contains(struct bloom_filter * bf, )

bloom_filters_add() {}
bloom_filters_destroy() {}


#endif /* BLOOM_FILTER_ */
