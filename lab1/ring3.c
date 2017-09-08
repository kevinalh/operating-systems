#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

#define BUFSIZE 20

void inv_str(char* cadena, int len) {
	int i;
	char ncadena[len+1];
	strcpy(ncadena, cadena);
	for(i = 0; i < len; ++i) {
		cadena[i] = ncadena[len-i-1];
	}
	return;
}

void up_str(char* cadena, int len) {
	int i;
	for(i = 0; i < len; ++i) {
		cadena[i] = toupper(cadena[i]);
	}
	return;
}

int main(int argc, char* argv[]) {
	char cadena[BUFSIZE+1];
	int fdr[2], fdu[2], fd2[2], len;
	pipe(fdr);
	pipe(fdu);
	if(fork()) {
		// Prompt/display
		close(fdr[0]);
		close(fdu[1]);
		fprintf(stdout, "Por favor ingrese una cadena: ");
		fgets(cadena, BUFSIZE, stdin);
		len = strlen(cadena);
		write(fdr[1], cadena, len);
		memset(cadena, 0, len);
		read(fdu[0], cadena, len);
		fprintf(stdout, "%s", cadena);
	}
	else {
		pipe(fd2);
		if(fork()) {
			// Reverse
			close(fdr[1]);
			close(fdu[0]);
			close(fdu[1]);
			close(fd2[0]);
			read(fdr[0], cadena, BUFSIZE);
			len = strlen(cadena);
			inv_str(cadena, len-1);
			write(fd2[1], cadena, len);
		}
		else {
			// Upper-case
			close(fdr[1]);
			close(fdr[0]);
			close(fdu[0]);
			close(fd2[1]);
			read(fd2[0], cadena, BUFSIZE);
			len = strlen(cadena);
			up_str(cadena, len-1);
			write(fdu[1], cadena, len);
		}
	}
	return 0;
}
