#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 10

int main(int argc, char *argv[])
{
	int fd, wfd;
	int cnt;
	char buf[BUFSIZE] = {};

	if(argc < 3)
		return 1;
	//打开文件
	fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		perror("open()");
		goto ERROR1;
	}
	wfd = open(argv[2], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if(wfd == -1)
	{
		perror("open()");
		goto ERROR2;
	}

	while(1)
	{
		//memset(buf,'\0', BUFSIZE);
		cnt = read(fd, buf, BUFSIZE);
		if(cnt == -1)
		{
			perror("read()");
			goto ERROR;
		}
		if(cnt == 0)
		{
			break;
		}
		//写入
		write(wfd, buf, cnt);
	}
	
	close(fd);
	close(wfd);

	return 0;
ERROR:
	close(wfd);
ERROR2:
	close(fd);
ERROR1:
	return 1;
}
