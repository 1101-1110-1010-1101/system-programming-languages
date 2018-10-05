#include <stdio.h>
#include <stdlib.h>

int is_prime(unsigned long num) {
	int k;
	if (num == 1) {
		return 0;
	}
	for(k = 2; k*k <= num; k++) {
		if (num % k == 0) {
			return 0;
		}
	}
	return 1;
}