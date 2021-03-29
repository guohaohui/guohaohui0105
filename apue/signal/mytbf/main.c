#include "tbf.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
//令牌桶：速率	上限	令牌

#define CPS 10
#define BURST 100
int main(int argc, char *argv[])
{
	int fd;
	char buf[CPS] = {};
	int cnt;
	int n;
	int fd1 = tbf_init(CPS, BURST);
	
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
		n = tbf_fetchtoken(fd1, CPS);

		memset(buf, '\0', n);
		cnt = read(fd, buf, n);
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
		if(n > cnt)
			tbf_returntoken(fd1, n-cnt);
		if(0 == cnt)
		{
			break;
		}
		write(1, buf, cnt);
	
	}
	tbf_destroy(fd1);
	close(fd);
	exit(0);
}
