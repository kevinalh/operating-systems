#define _POSIX_C_SOURCE  200809L
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int i, n, fd[2], actualstdout;
	if(argc < 2) {
		perror("Not enough arguments\n");
		return -1;
	}
	pipe(fd);
	actualstdout = fcntl(STDOUT_FILENO, F_DUPFD, 0);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	n = atoi(argv[1]);
	int j = 0;
	for(i = 1; i < n; ++i) {
		pipe(fd);
		if(fork()) {
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			++j;
			write(STDOUT_FILENO, &j, sizeof(int));
			break;
		}
		else {
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			read(STDIN_FILENO, &j, sizeof(int));
		}
	}
	dprintf(actualstdout, "Proceso %d con j = %d\n", i, j);
	wait(NULL);
	return 0;
}
