#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int x;
	printf("Please enter an integer: ");
	scanf("%d", &x);
	printf("The integer entered was %d\n", x);
	return EXIT_SUCCESS;
}
