#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
	printf("%ld", sysconf(_SC_PAGESIZE));
	return 0;
}