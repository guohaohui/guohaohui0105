#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	char *opts[] = {"ls", "-l", NULL};
	printf("%s start\n", __FUNCTION__);

	pid = fork();
	if(-1 == pid)
	{
		perror("fork()");
		exit(1);
	}

	if(0 == pid)
	{
		//execl("/bin/ls", "ls", "-l","-i","-h" ,"-a", NULL);//替换当前进程
		//execl("/home/xiaohao/guohaohui/guohaohui0105/apue/io/process/base/control/001","001", NULL);
		//execlp("ls", "ls", "-l","-i","-h" ,"-a", NULL);//execlp可以只传文件名，但是文件路径必须在extern char **environ;这个环境表里面有。
		//execv("/bin/ls", opts);// 把选项存到一个指针数组中，把这个数组的首地址传过去
		execvp("ls", opts);//和execlp差不多
		perror("exitl()");
		exit(1);
	}
	
	wait(NULL);
	printf("%s start\n", __FUNCTION__);
	exit(0);
}
