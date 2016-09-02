#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNTERS_SIZE 3 
int counters[COUNTERS_SIZE];

int
main(void) {
    int i, j, k;

    memset(counters, 0, COUNTERS_SIZE * sizeof(int));
    
    for (j = 0 ; j < COUNTERS_SIZE ; j++) {
        counters[j] = j;
    }
    
    for (i = 0 ; i < 25 ; i++) {

        for (j = 0 ; j < COUNTERS_SIZE ; j++) {
            printf("%d ", counters[j] + 1);
        }
        printf("\n");

        for (k = 0 ; k < COUNTERS_SIZE; k++) {
            counters[k] = (counters[k] + 1) % COUNTERS_SIZE;
            if (counters[k] != 0) {
                break;
            }
        }

    }
}
