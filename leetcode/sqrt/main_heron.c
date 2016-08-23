#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double mySqrt(const int a) {
    double x = 2;
    double x2;
    double precision = 0.000001;
    size_t i;

    i = 0;
    x2 = a / x;
    do {
        //printf("x=%f x2=%f\n", x, x2);
        x = (x + x2) / 2;
        x2 = a / x;
        i++;
    } while (x - x2 > precision);
    printf("iter:%lu ", i);
    return x;	
}

int
main(int argc, char ** argv)
{
    printf("mySqrt=%f - sqrt=%f\n", mySqrt(2), sqrt(2));
    printf("mySqrt=%f - sqrt=%f\n", mySqrt(4), sqrt(4));
    printf("mySqrt=%f - sqrt=%f\n", mySqrt(5), sqrt(5));
    printf("mySqrt=%f - sqrt=%f\n", mySqrt(7), sqrt(7));
    printf("mySqrt=%f - sqrt=%f\n", mySqrt(16), sqrt(16));
    printf("mySqrt=%f - sqrt=%f\n", mySqrt(100), sqrt(100));
    printf("mySqrt=%f - sqrt=%f\n", mySqrt(1000), sqrt(1000));
    printf("mySqrt=%f - sqrt=%f\n", mySqrt(11111), sqrt(11111));
    printf("mySqrt=%f - sqrt=%f\n", mySqrt(111111), sqrt(111111));
    printf("mySqrt=%f - sqrt=%f\n", mySqrt(111112), sqrt(111112));
    return 0;
}
