#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;
	char ch;
	int cnt;
	int i = 0;
	fd = open(argv[1], O_RDWR);
	if(fd == -1)
	{
		perror("open()");
		return 1;
	}

	while(1)
	{
		cnt = read(fd, &ch, 1);
		if(cnt == -1)
		{
			perror("read()");
			close(fd);
			return 1;
		}
		if(cnt == 0)
			break;
		if(ch == ' ' || ch == '\n')
			i++;
	
	}

	printf("%d\n", i);
	return 0;
}
