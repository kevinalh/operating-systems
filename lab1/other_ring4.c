#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int pf[2], i, n = argc-1;
	pid_t child;
	if(fork() != 0) {
		wait(NULL);
	}
	else {
		for(i = n; i > 1; --i) {
			pipe(pf);
			if((child = fork()) != 0) {
				// Padre
				dup2(pf[0], STDIN_FILENO);
				close(pf[0]);
				close(pf[1]);
				execlp(argv[i], argv[i], NULL);
				break;
			}
			else {
				// Hijo
				dup2(pf[1], STDOUT_FILENO);
				close(pf[0]);
				close(pf[1]);
			}
		}
	}
	if(i == 1) execlp(argv[1], argv[1], NULL);
	return 0;
}
