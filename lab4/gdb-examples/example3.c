#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int main(int argc, char* argv[]) {
	srand(time(NULL));
	printf("%ld \n", INT_MAX);
	int n = INT_MAX;
	int A[n];
	int i = 0;
	while (i < n) {
		A[i] = rand()%10;
		i++;
	}
	return EXIT_SUCCESS;
}
