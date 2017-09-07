#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

int main() {
	int i;
	pid_t child, pid_padre;
	pid_padre = getpid();
	int fd[2], fdc[2];
	int br, bw;
	pipe(fdc);
	pipe(fd);
	for(i=1; i<4; ++i) {
		if((child = fork()) <= 0) break;
		else {
			fprintf(stderr, "Este es el ciclo Nro %d y se esta creando el proceso %d\n", i, child);
		}
	}
	if(pid_padre == getpid()) {
		int lec, esc[4] = {1, 2, 3, 4};
		close(fd[0]);
		close(fdc[1]);
		for(i=1; i<4; ++i) {
			br = read(fdc[0], &lec, sizeof(lec));
			fprintf(stderr, "Padre: br: %d, lec: %d\n", br, lec);
		}
		char cmd[20];
		sprintf(cmd, "pstree -p %d > fanprocesses.txt", pid_padre);
		system(cmd);
		bw = write(fd[1], esc, 3*sizeof(int));
		fprintf(stderr, "Padre: bw: %d\n", bw);
		for(i=1; i<4; ++i) wait(NULL);
	}
	else {
		int lec, esc = getpid();
		close(fd[1]);
		close(fdc[0]);
		bw = write(fdc[1], &esc, sizeof(esc));
		br = read(fd[0], &lec, sizeof(lec));
		fprintf(stderr, "Hijo: br2: %d, bw2 = %d, lec = %d\n", br, bw, lec);
	}
	fprintf(stderr, "Este es el proceso %d con padre %d\n", getpid(), getppid());
	return 0;
}
