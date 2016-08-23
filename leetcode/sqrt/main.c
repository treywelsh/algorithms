#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//http://www.geeksforgeeks.org/square-root-of-a-perfect-square/

double mySqrt(const int a, const size_t iter_count) {
	double x = 2;
	double x2;
	double precision = 0.00002;
	size_t i;

	i = 0;
	while(i < iter_count) {
		printf("x=%f\n", x);
		x = (x + a / x) / 2;
		i++;
	}
	printf("iter:%lu ", i);
	return x;	
}


int
main(int argc, char ** argv)
{
	printf("mySqrt=%f - sqrt=%f\n", mySqrt(2, 10), sqrt(2));
	printf("mySqrt=%f - sqrt=%f\n", mySqrt(4, 10), sqrt(4));
	printf("mySqrt=%f - sqrt=%f\n", mySqrt(5, 10), sqrt(5));
	printf("mySqrt=%f - sqrt=%f\n", mySqrt(7, 10), sqrt(7));
	printf("mySqrt=%f - sqrt=%f\n", mySqrt(16, 10), sqrt(16));
	printf("mySqrt=%f - sqrt=%f\n", mySqrt(100, 10), sqrt(100));
	printf("mySqrt=%f - sqrt=%f\n", mySqrt(1000, 10), sqrt(1000));
	printf("mySqrt=%f - sqrt=%f\n", mySqrt(11111, 10), sqrt(11111));
    return 0;
}
