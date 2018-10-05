#include "scalar.h"
int scalar(const int a[], const int b[], unsigned int size) {
	unsigned int i;
	int ans = 0;
	for (i = 0; i < size; i++){
		ans += a[i] * b[i];
	}
	return ans;
}