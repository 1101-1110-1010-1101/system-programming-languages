#include <stdio.h>
#include "is_prime.h"

int main(int argc, char** argv) {
	unsigned long d;
	int res;
	printf("%s\n", "Enter the number for primality test:");
	scanf("%lu", &d);
	res = is_prime(d);
	if (res == 1)
		printf("%ld is prime\n", d);
	else
		printf("%ld is not prime\n", d);
	return 0;
}