#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
int main()
{
	int num = 100;
	pid_t pid, ppid;
	
	pid = getpid();
	ppid = getppid();

	printf("pid = %d ppid = %d\n", pid, ppid);
	
	printf("!!!!!!!!!!!!!guohaohui!!!!!!!!!!!!");

	fflush(NULL);//刷新缓存区
	pid = fork();//创建子进程
	if(pid == -1) {
		perror("fork()");
		exit(1);
	}
	//两份代码在运行
	if(pid == 0)
	{
		printf("pid1: %d, ppid1: %d\n", getpid(), getppid());
		printf("num1 = %d\n", num);
		num = 200;
		printf("num2 = %d\n", num);

		exit(0);
	}

#if 0
	for(int i = 0; i < 3; i++)
	{
		write(1, "*", 1);
		sleep(1);
	}
#endif
	
	wait(NULL); //收尸
	printf("num = %d\n", num);


	exit(0);
}
