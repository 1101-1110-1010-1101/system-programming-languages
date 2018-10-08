#include <stdio.h>
#include "is_prime.h"

int main(int argc, char** argv) {
	unsigned long d = 0;
	int res;
	printf("%s\n", "Enter the number for primality test:");
	if (scanf("%lu", &d)){
		res = is_prime(d);
		if (res == 1)
			printf("%lu is prime\n", d);
		else
			printf("%lu is not prime\n", d);
	}
	else
		printf("%s\n", "Value should be a number");
	return 0;
}