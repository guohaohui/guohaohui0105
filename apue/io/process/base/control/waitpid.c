#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid, wait_pid;

	pid = fork();
	if(-1 == pid)
	{
		perror("fork()");
		exit(1);
	}
	if(0 == pid)
	{
		setpgid(getpid, getpid());
		printf("pid:%d gid:%d\n", getpid(), getpgid(getpid()));
		exit(0);
	}

	printf("parent pid:%d gid:%d\n", getpid(), getpgid(getpid()));

	//wait_pid = waitpid(-1, NULL, 0);
	//wait_pid = waitpid(0, NULL, 0);
	//wait_pid = waitpid(pid, NULL, 0);
	wait_pid = waitpid(-pid, NULL, 0);
	printf("pid:%d wait_pid:%d\n", pid, wait_pid);

	exit(0);
}
