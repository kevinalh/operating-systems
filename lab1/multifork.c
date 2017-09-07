#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

#define DISPLAY1 "PID INDUK** ** pid (%5.5d) ** **********\n"
#define DISPLAY2 "val1(%5.5d) -- val2(%5.5d) - val3(%5.5d)\n"

int main() {
	pid_t val1, val2, val3;
	printf(DISPLAY1, (int) getpid());
	fflush(stdout);
	val1 = fork();
	wait(NULL);
	val2 = fork();
	wait(NULL);
	val3 = fork();
	wait(NULL);
	printf(DISPLAY2, (int) val1, (int) val2, (int) val3);
	return 0;
}
