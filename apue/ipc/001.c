/*父进程将argv[1]文件陆续写入管道，子进程读管道数据并大小写转换写到终端*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE 10

int chargeStr(char *p);
static int mywrite(int wfd, int rfd, int flag)
{
	char buf[BUFSIZE] = {};
	int cnt;
	//while(1) {
		memset(buf, '\0', BUFSIZE);
		cnt = read(rfd, buf, BUFSIZE-1);
		if(cnt == -1)
		{
			close(rfd);
			exit(1);
		}
		if(cnt == 0)
			return 1;
			//break;
		if(flag)
			chargeStr(buf);
		write(wfd, buf, cnt);
	//}
	return 0;
}


int main(int argc, char *argv[])
{
	int pipefd[2] = {};
	pid_t st;
	char buf[BUFSIZE] = {};

	int fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		perror("open()");
		exit(1);
	}
	
	if(pipe(pipefd) == -1)//创建管道!!!!!!!!!
	{
		perror("pipe()");
		goto ERROR1;
	}

	st = fork();//创建子进程
	if(st == -1)
	{
		perror("fork()");
		goto ERROR2;
	}
	if(st == 0)
	{
		while(1) {//父子进程互不干扰
			close(pipefd[0]);//关闭读
			sleep(1);
			if(mywrite(pipefd[1], fd, 1))//写
				exit(0);
		}
	}

while(1) {
	close(pipefd[1]);
	if(mywrite(1,pipefd[0], 0))//读的时候要等带管道写完，如果管道没有写就会一直阻塞
		break;
}
	wait(NULL);

	exit(0);
ERROR2:
	close(pipefd[0]);
	close(pipefd[1]);
ERROR1:
	close(fd);
	exit(1);
}

int chargeStr(char *p)//大小写转换
{
	while(*p)
	{
		if(*p >= 'A' && *p <= 'Z')
		{
			*p = *p + ('a' - 'A');
		}
		else if(*p >= 'a' && *p <= 'z')
		{
			*p = *p - ('a' - 'A');
		}
		p++;
	}
	return 0;
}


