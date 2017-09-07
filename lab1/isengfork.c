#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

int main() {
	int ii = 0;
	if(fork() == 0) ii++;
	waitpid(-1, NULL, 0);
	if(fork() == 0) ii++;
	waitpid(-1, NULL, 0);
	if(fork() == 0) ii++;
	waitpid(-1, NULL, 0);
	printf("Result = %3.3d \n", ii);
	return 0;
}
