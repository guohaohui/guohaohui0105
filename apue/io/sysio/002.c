#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define NAMESIZE 1024

int main(int argc, char *argv[])
{
	int i = 0;
	int rfd, wfd;
	char buf[NAMESIZE] = {};
	int cnt, len;
	char ch;	
	if(argc < 4)
		return 1;
	rfd = open(argv[1], O_RDONLY);
	if(rfd == -1)
	{
		perror("open()");
		goto ERROR1;
	}
	wfd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if(wfd == -1)
	{
		perror("open()");
		goto ERROR2;
	}
	
	while(1)
	{
		cnt = read(rfd, buf, 1);
		if(cnt == -1)
		{
			perror("read()");
			goto ERROR;
		}
		if(cnt == 0)
			break;
		if(i == 3)
		{
			len = strlen(argv[2]);
			lseek(wfd, -1, SEEK_CUR);
			write(wfd, argv[2], len+1);
			write(wfd, "\n", 1);
			i++;
		}
		if(buf[0] == '\n')
		{
			i++;
		}


		write(wfd, buf, cnt);
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
