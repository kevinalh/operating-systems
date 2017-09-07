#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>

int main(void) {
	pid_t child;
	if((child = fork())) {
		/* Padre */
		fprintf(stderr, "\nFork() devolvió %d por tanto soy el padre con ID = %d", child, getpid());
		waitpid(child, NULL, 0);
	}
	else {
		/* Hijo */
		char cmd[50];
		fprintf(stderr, "\nFork() devolvió %d por tanto soy el hijo con ID = %d\n", child, getpid());
		chdir("./tests");
		sprintf(cmd, "pstree -p %d > aprocesos.txt", getppid());
		system(cmd);
	}
	return 0;
}
