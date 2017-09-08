#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	pid_t childpid;
	int error; // return value of dup2 call
	int fd[2];
	int i; // number of this process (starting at 1)
	int nprocs; // total number of processes in ring
	if((argc != 2) || ((nprocs = atoi(argv[1]))) <= 0) {
		fprintf(stderr, "Usage: %s nprocs\n", argv[0]);
		return 1;
	}
	// Create pipe
	if(pipe(fd) == -1) {
		perror("Failed to create starting pipe");
		return 1;
	}
	// Connect pipe to stdin and stdout
	if((dup2(fd[0], STDIN_FILENO) == -1) || (dup2(fd[1], STDOUT_FILENO)) == -1) {
		perror("Failed to connect pipe");
		return 1;
	}
	// Close unneeded descriptors
	if((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
		perror("Failed to close extra descriptors");
		return 1;
	}
	// For each process in the ring
	for(i = 1; i < nprocs; ++i) {
		// Create pipe on fd
		if(pipe(fd) == -1) {
			fprintf(stderr, "[%d]: failed to create pipe %d: %s\n", getpid(), i, strerror(errno));
			return 1;
		}
		// Fork
		if((childpid = fork()) == -1) {
			fprintf(stderr, "[%d]:failed to create child %d: %s\n", getpid(), i, strerror(errno));
			return 1;
		}
		if(childpid > 0) { // For parent, on success
			error = dup2(fd[1], STDOUT_FILENO);
		}
		else { // For child
			error = dup2(fd[0], STDIN_FILENO);
		}
		if(error == -1) { // Error on dup2
			fprintf(stderr, "[%d]:failed to dup pipes for iteration %d: %s\n", getpid(), i, strerror(errno));
			return 1;
		}
		if((close(fd[0]) == -1) || (close(fd[1]) == -1)) { // Closing extra descriptors
			fprintf(stderr, "[%d]:failed to close extra descriptors %d: %s\n", getpid(), i, strerror(errno));
			return 1;
		}
		if (childpid) { // Don't let a parent have another child
			break;
		}
	}
	fprintf(stderr, "This is process %d with ID %d and parent id %d\n", i, getpid(), getppid());
	wait(NULL);
	return 0;
}
