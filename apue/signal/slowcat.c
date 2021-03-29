#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE 10



static int token = 0;

static void alarm_handlef(int s)
{
	alarm(1);
	token = 1;
}

int main(int argc, char *argv[])
{
	int fd;
	char buf[BUFSIZE] = {};
	int cnt;

	signal(SIGALRM, alarm_handlef);
	alarm(1);//以秒为单位安排一个SIGALRM信号发送给调用系统

	if(argc < 2)
		exit(0);
	
	fd = open(argv[1], O_RDONLY);
	if(-1 == fd)
	{
		perror("open()");
		exit(1);
	}
	

	while(1)
	{
		//alarm(1);
#if 1
		//流量控制
		while(token == 0)
		{
			pause();//等待信号到来 
		}
#endif
		token = 0;
		memset(buf, '\0', BUFSIZE);
		cnt = read(fd, buf, BUFSIZE);
		if(cnt == -1)
		{
			perror("read()");
			exit(1);
		}
		if(0 == cnt)
		{
			break;
		}
		write(1, buf, cnt);
	
	}

	close(fd);

}
