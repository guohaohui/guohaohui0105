#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd;

	fd = open("guo1", O_WRONLY | O_CREAT | O_TRUNC, 0666);
#if 0
	close(1);
	dup(fd);
#endif
	
	dup2(fd, 1);

	printf("guohaomeng\n");
	close(fd);

	return 0;
}


