#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE 10

int main(int argc, char *argv[])
{
	int fd;
	int cnt;
	char buf[BUFSIZE] = {};

	if(argc < 2)
		return 1;
	fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		perror("open()");
		return 1;
	}

	while(1)
	{
		memset(buf, '\0', BUFSIZE);
		cnt = read(fd, buf, BUFSIZE);
		if(cnt == -1)
		{
			perror("read()");
			goto ERROR;
		}
		if(cnt == 0)
		{
			// EOF
			break;
		}
		write(1, buf, cnt);
	}

	close(fd);
	return 0;
ERROR:
	close(fd);
	return 1;
}
