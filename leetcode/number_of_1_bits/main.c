#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
 * O(n) in time
 * O(1) in space
 * better implementations proposed here :
 * https://en.wikipedia.org/wiki/Hamming_weight
 */


/* 8 bits implem */
int bit_count_8bits[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8 }; 
int hammingWeight_8(uint32_t n) {
    uint32_t i;
    int dist;
    union { uint32_t * i; uint8_t * c; } u;

    u.i = &n;
    dist = 0;
    for (i = 0 ; i < 4 ; i++) {
        dist += bit_count_8bits[u.c[i]];
    }
    return dist;
}


/* 4 bits implem */
int bit_count_4bits[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
#define MASK_4 ((1 << 4) - 1)
int hammingWeight_4(uint32_t n) {
    uint32_t i;
    int dist;
    union { uint32_t * i; uint8_t * c; } u;

    u.i = &n;
    dist = 0;
    for (i = 0 ; i < 4 ; i++) {
        dist += bit_count_4bits[u.c[i] & MASK_4] + \
                bit_count_4bits[(u.c[i] >> 4) & MASK_4];
    }
    return dist;
}

/* 1 bits implem */
int hammingWeight_naive(uint32_t n) {
    uint32_t i;
    int dist;

    dist = 0;
    i = n;
    while (i > 0) {
        if (i & 1) {
            dist++;
        }
        i >>= 1;
    }
    return dist;
}

void
test_case(uint32_t n) {
    printf("==============================\n");
    if (hammingWeight_4(n) != hammingWeight_naive(n) || hammingWeight_8(n) != hammingWeight_naive(n)) {
        printf("error\n");
        exit(1);
    }
    printf("n=%d weight_8=%d weight_4=%d weight naive=%d\n", n, \
            hammingWeight_8(n), \
            hammingWeight_4(n), \
            hammingWeight_naive(n));
    /* printf("%d, ", hammingWeight_naive(n)); */
}

    int
main(int argc, char ** argv)
{
    int i;
    for (i = 0 ; i < 20 ; i++) {
        test_case(i);
    }
    return 0;
}
