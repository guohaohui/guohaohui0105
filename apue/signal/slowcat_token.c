#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

//令牌桶：速率	上限	令牌

#define BUFSIZE 10
#define CPS BUFSIZE
#define BURSET 100


static int token = 0;

static void alarm_handlef(int s)
{
	alarm(1);
	token += CPS;
	if(token >= BURSET)
		token = BURSET;
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
	do{
		fd = open(argv[1], O_RDONLY);
		if(-1 == fd)
		{
			//是否为假错
			if(errno == EINTR)
			{
				continue;
			}
			perror("open()");
			exit(1);
		}
		break;
	}while(1);

	while(1)
	{
		//alarm(1);
#if 1
		//流量控制
		while(token < CPS)
		{
			pause();//等待信号到来 
		}
#endif
		token -= CPS;
		memset(buf, '\0', BUFSIZE);
		cnt = read(fd, buf, BUFSIZE);
		while(1) {
			if(cnt == -1)
			{
				if(errno == EINTR)
					continue;
				perror("read()");
				exit(1);
			}
			break;
		}
		if(0 == cnt)
		{
			break;
		}
		write(1, buf, cnt);
	
	}

	close(fd);

}
