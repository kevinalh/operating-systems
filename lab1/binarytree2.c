#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	pid_t padre = getpid();
	if(argc != 2) {
		exit(0);
	}
	int n = atoi(argv[1]);
	int i = 1, j = 0;
	while(i < n && j < 2) {
		if(fork() == 0) {
			i++;
			j = 0;
		}
		else j++;
		wait(NULL);
	}
	fprintf(stderr, "Soy el proceso %d con pid %d y ppid %d\n", (int) getpid()-padre+1, getpid(), getppid());
	return 0;
}
