#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define NAMESIZE 10

int main(int argc, char *argv[])
{
	int rfd, wfd;
	char add[NAMESIZE]={};

	if(argc < 3)
		return 1;

	rfd = open(argv[1], O_RDONLY);
	if(rfd == -1)
	{
		perror("open()");
		goto ERROR1;
	}
	wfd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if(wfd == -1)
	{
		perror("open()");
		goto ERROR2;
	}

	int i = 0;
	int lse;
	int len;
	while(1)
	{
		lse = lseek(rfd, i-- , SEEK_END);
		if(lse == -1)
			break;
		
		len = read(rfd, add, 1);
		if(len == -1)
		{
			perror("read()");
			goto ERROR;
		}
		write(wfd, add, 1);
		//i--;
	
	}

	close(rfd);
	close(wfd);

	return 0;
ERROR:
	close(wfd);
ERROR2:
	close(rfd);
ERROR1:
	return 1;
}



