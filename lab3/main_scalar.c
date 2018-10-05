#include <stdio.h>
#include "scalar.h" 

const int a[] = {1, 2, 3, 4, 5};
const int b[] = {1, 2, 3, 4, 5};
const int c = 5;

int main(int argc, char** argv) {
	int size = sizeof(a) / sizeof(a[0]);
	unsigned int i;
	printf("%s ", "First array is:");
	for (i = 0; i < size; i++){
		printf("%d ", a[i]);
	}
	printf("\n%s ", "Second array is:");
	for (i = 0; i < size; i++){
		printf("%d ", b[i]);
	}
	printf("\nAnswer is: %d\n", scalar(a, b, size));
	return 0;
}