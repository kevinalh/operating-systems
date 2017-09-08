#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

double final;
void crea_arbol(int);

int n;
pid_t parent_pid;
int fd[2];
int fdc[2];
int children;

int main(int narg, char* argv[]) {
	parent_pid = getpid();
	n = atoi(argv[1]);
	final = pow(2, (n-1));
	pipe(fd);
	pipe(fdc);
	children = (int) pow(2, n)-1;
	crea_arbol(1);
	return 0;
}

void crea_arbol(int x) {
	char cadena[60];
	int esc, lec, i;
	int br;
	/*
	if((int) pow(2, n) == x + 1) {
		sprintf(cadena, "pstree -p %d > binarytree.txt", parent_pid);
		system(cadena);
	}
	*/
	sprintf(cadena, "Soy el proceso %d con pid %d y ppid %d\n", x, getpid(), getppid());
	write(STDOUT_FILENO, cadena, strlen(cadena));
	if(x < final) {
		if(!fork()) {
			crea_arbol(2*x);
			return;
		}
		if(!fork()) {
			crea_arbol(2*x+1);
			return;
		}
	}
	if((int) getpid() == parent_pid) {
		close(fdc[1]);
		close(fd[0]);
		esc = parent_pid;
		for(i = 0; i < children-1; ++i) {
			br = read(fdc[0], &lec, sizeof(lec));
			printf("PADRE: Read br: %d, lec: %d\n", br, lec);
		}
		for(i = 0; i < children-1; ++i) {
			br = write(fd[1], &esc, sizeof(esc));
			printf("PADRE: Written %d\n", br);
			wait(NULL);
		}
	} else {
		close(fdc[0]);
		close(fd[1]);
		esc = x;
		br = write(fdc[1], &esc, sizeof(esc));
		printf("HIJO: Written %d, x: %d, pid: %d\n", br, x, getpid());
		br = read(fd[0], &lec, sizeof(lec));
		printf("HIJO: Read br: %d, lec: %d, pid: %d, x: %d\n", br, lec, getpid(), x);
	}
	wait(NULL);
	wait(NULL);
	return;
}
