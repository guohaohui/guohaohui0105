#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MIN 100
#define MAX 301

static int prime(int i)
{
	for(int j = 2; j < i; j++)
	{
		if(i % j == 0)
			return 0;
	}
	return 1;
}


int main()
{
	pid_t pid;
	int i;
	
	for(i = MIN; i < MAX; i++)
	{
		pid = fork();//创建子进程
		if(-1 == pid)
		{
			perror("fork()");
			exit(1);
		}
		if(0 == pid)
		{
			if(prime(i))
				printf("[%d] %d\n", getpid(), i);
			exit(0);
		}
	}

	for(i = MIN; i<MAX; i++)
	{
		wait(NULL);
	}
	

	exit(0);	
}
