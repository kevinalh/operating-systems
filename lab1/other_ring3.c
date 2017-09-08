#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int pfd1[2], pfd2[2];
	int pid;
	if(fork()) wait(NULL);
	else {
		pipe(pfd1);
		pipe(pfd2);
		if((pid = fork()) && fork()) {
			close(pfd1[0]);
			close(pfd1[1]);
			dup2(pfd2[0], STDIN_FILENO);
			close(pfd2[0]);
			close(pfd2[1]);
			execlp(argv[3], argv[3], NULL);
		}
		close(pfd2[0]);
		switch(pid) {
			case 0:
				dup2(pfd1[1], STDOUT_FILENO);
				close(pfd1[0]);
				close(pfd1[1]);
				close(pfd2[1]);
				execlp(argv[1], argv[1], NULL);
			default:
				dup2(pfd1[0], STDIN_FILENO);
				dup2(pfd2[1], STDOUT_FILENO);
				close(pfd1[0]);
				close(pfd1[1]);
				close(pfd2[1]);
				execlp(argv[2], argv[2], NULL);
		}
	}
	return 0;
}
