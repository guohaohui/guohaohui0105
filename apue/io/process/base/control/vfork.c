#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	int num = 100;
	pid = vfork();
	if(-1 == pid)
	{
		perror("vfork()");
		exit(0);
	}

	if(0 == pid)
	{
		num++;
		printf("[%d], %d\n", getpid(), num);
		sleep(1);
		_exit(0);
	}
	
	printf("[%d], %d\n", getpid(), num);


	exit(0);
}
