#ifndef POOL_H_
#define POOL_H_

struct pool {
    void * area;
    unsigned int area_len;

    unsigned int elt_count;
    unsigned int elt_size;

    unsigned int free_count;
    void * free; /* Free list head */
};

int pool_init(struct pool * p,
	          unsigned int elt_count,
	          unsigned int elt_size);
void pool_clean(struct pool * p);

void * pool_alloc(struct pool * p);
void pool_free(struct pool * p,
	           void * elt);

/* If data size is larger than elt_size,
 * next chunk will be corrupted
 * This function avoid this problem
int pool_safe_write(struct pool * p, void * pool_chunk, void * data);
 */

#define pool_is_empty(p) ((p)->free_count == 0)
#define pool_is_full(p) ((p)->free_count == (p)->elt_count)

#endif /* POOL_H_ */
