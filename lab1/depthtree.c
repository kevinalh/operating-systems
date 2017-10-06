#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <math.h>

int n;

void crea_arbol(int x);

int main() {
	n = 3;
	crea_arbol(1);
	return 0;
}

int crea_arbol(int x) {
	// x: profundidad a la que se encuentra actualmente
	printf("Soy el proceso %d con pid %d y ppid %d\n", x, getpid(), getppid());
	if(x == n) return;
	int y;
	if(!fork()) {
		// Primer hijo
		crea_arbol(x+1);
		exit(0);
	}
	wait(NULL);
	if(!fork()) {
		// Segundo hijo
		crea_arbol(x+1);
		exit(0);
	}
	wait(NULL);
	return y;
}
