#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int** permute(int* nums, int numsSize, int* returnSize) {
    int i, j;
    int ** ret;
    int sz;
    int perm_cnt;
    int c[numsSize];
    int swap;

    for (sz = 1 , i = 1 ; i <= numsSize ; i++)
        sz *= i;
    *returnSize = sz;

    ret = malloc(sz * sizeof(int *));
    if (ret == NULL) {
        return NULL;
    }
    for (i = 0 ; i < sz ; i++) {
        ret[i] = malloc(numsSize * sizeof(int));
        if (ret[i] == NULL) {
            return NULL;
        }
    }

    perm_cnt = 0;
    memset(c, 0, numsSize * sizeof(int));
    //memcpy(ret[perm_cnt], nums, numsSize * sizeof(int));
    //perm_cnt++;

    for (i = 0 ; i < numsSize ; ) {
        memcpy(ret[perm_cnt], nums, numsSize * sizeof(int));
        if (c[i] < i) {
            if (i % 2 == 0) {
                //swap 0 and i elements
                swap = ret[perm_cnt][0];
                ret[perm_cnt][0] = ret[perm_cnt][i];
                ret[perm_cnt][i] = swap;
            } else {
                //swap i and c[i] elements
                swap = ret[perm_cnt][c[i]];
                ret[perm_cnt][c[i]] = ret[perm_cnt][i];
                ret[perm_cnt][i] = swap;
            }
            perm_cnt++;
            //printf("%d\n", perm_cnt);
            assert(perm_cnt < sz);
            c[i]++;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }
    return ret;
}


int
main(void) {
    int i, j;
    int array[] = {1, 2, 3};
    int sz;
    int ** ret;
    ret = permute(array, 3, &sz);
    for (i = 0 ; i < sz ; i++) {
        for (j = 0 ; j < 3 ; j++) {
            printf("%d ", ret[i][j]); 
        }
        printf("\n"); 
    }
}
