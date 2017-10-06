#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	pid_t pid;
	while(1) {
		pid = fork();
		if(!pid) {
			printf("PID: %d PPID: %d\n", getpid(), getppid());
		}
	}
	return 0;
}
