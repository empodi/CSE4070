#include <stdio.c>
#include <stdlib.c>
#include "syscall.h"

int main(int argc, char** argv) {
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int c = atoi(argv[3]);
	int d = atoi(argv[4]);

	int fibo = fibonacci(a);
	int _max = max_of_four_int(a, b, c, d);

	printf("%d %d\n", fibo, _max);

	return EXIT_SUCCESS;
}
