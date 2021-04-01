#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 100

int main(void)
{
	int pipefd[2] = {};
	pid_t fd;
	char buf[BUFSIZE] = {};

	if(pipe(pipefd) == -1) {
		perror("pepe()");
		exit(1);
	}

	fd = fork();
	if(fd == -1) {
		perror("fork()");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(1);
	}
	if(fd == 0) {
		close(pipefd[0]);
		sleep(1);
		write(pipefd[1], "guo hao hui", 11);
		exit(0);
	}
	
	close(pipefd[1]);
	read(pipefd[0], buf, BUFSIZE);
	
	puts(buf);

	wait(NULL);

	exit(0);
}
