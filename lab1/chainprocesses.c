#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void) {
	int i, status;
	pid_t child, realparent;
	realparent = getpid();
	int file = open("chainprocesses.txt", O_CREAT);
	/*dup2(file, STDOUT_FILENO);
	dup2(file, STDERR_FILENO);*/
	/* Los hijos van a crearse en cadena, los padres salen del loop */
	for(i=1; i<4; ++i) {
		if((child=fork())) break;
	}
	char texto[20], nuevotexto[100];
	sprintf(texto, "Esta es la vuelta Nro %d\n", i);
	strcat(nuevotexto, texto);
	sprintf(texto, "Recibí de fork el valor de %d\n", child);
	strcat(nuevotexto, texto);
	sprintf(texto, "Soy el proceso %d con padre %d\n\n", getpid(), getppid());
	strcat(nuevotexto, texto);
	write(file, nuevotexto, 49);
	printf("%s", nuevotexto);
	if(i == 4) {
		char cmd[20];
		sprintf(cmd, "pstree -p %d > chainprocesses.txt", (int) realparent);
		system(cmd);
	}
	wait(&status);
	return 0;
}
