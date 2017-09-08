#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define BUFSIZE 64
#define WLOOP 5

int main(int narg, char* argv[]) {
	char buffer[BUFSIZE];
	char message[] = "Hello, what's up?\n";
	int ii, pipe_fd[2], fdaux[2], aux = 1;
	pipe(pipe_fd);
	pipe(fdaux);
	if(fork() == 0) {
		close(fdaux[1]);
		close(pipe_fd[0]);
		printf("I am PID[%d] (child).\n", (int) getpid());
		for(ii = 0; ii < WLOOP; ++ii) {
			write(pipe_fd[1], message, sizeof(message)-1);
			read(fdaux[0], &aux, sizeof(aux));
		}
		close(pipe_fd[1]);
		close(fdaux[0]);
	}
	else {
		close(fdaux[0]);
		close(pipe_fd[1]);
		printf("I am PID[%d] (parent).\n", (int) getpid());
		memset(buffer, 0, sizeof(buffer));
		/* The problem here will be that the scheduler might activate a clock
		 * interruption mid-writing, causing the parent to receive different
		 * amounts of data each time.
		 * Suggestions towards a solution:
		 * - Using sleep(0.1) after each write. This can still cause problems sometimes.
		 * - Using sizeof(message)-1 instead of BUFSIZE-1. But we won't necessarily know
		 * this size in practice! Also, the writing isn't atomic
		 * - Using alternative atomic functions so that the writing won't be interrupted
		 * - The solution of pipes used here is the best one, although a little
		 * convoluted for bigger and more complex scenarios. */
		while((ii=read(pipe_fd[0], buffer, BUFSIZE-1)) != 0) {
			printf("PARENT READ[%d]:\n%s\n", (int) ii, buffer);
			memset(buffer, 0, sizeof(buffer));
			write(fdaux[1], &aux, sizeof(aux));
		}
		close(pipe_fd[0]);
		close(fdaux[1]);
	}
	return 0;
}
