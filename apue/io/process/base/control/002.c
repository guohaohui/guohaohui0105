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

	for(i = 0; i < 3; i++)
	{
		pid = fork();
		if(-1 == pid)
		{
			perror("fork()");
			exit(1);
		}

		if(0 == pid)
		{
			for(int j = MIN +i; j < MAX; j+=3)
			{
				if(prime(j))
					printf("[%d] %d\n", getpid(), j);
			}
			exit(0);
		}
	}

	for(i = 0; i<3; i++)
		wait(NULL);


	exit(0);
}
