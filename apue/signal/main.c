#include "token_library.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
//令牌桶：速率	上限	令牌

#define BUFSIZE 10

int main(int argc, char *argv[])
{
	int fd;
	char buf[BUFSIZE] = {};
	int cnt;
	
	int fd1 = tokenInit(10, 100);
	
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
		tokenDele(fd1, BUFSIZE);

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
	tokenFree(fd1);
	close(fd);

}
