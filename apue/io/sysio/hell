#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	if(argc < 2)
		return 1;
#if 0
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		printf("errno:%d\n", errno);
		perror("open()");
		return 1;
	}
	
	printf("%d\n", fd);
#endif
	// mode & ~umask  打开
	int fd = open(argv[1], O_RDWR | O_CREAT | OTRUNC, 0666);//O_TRUNC 清空
	
	if(fd == -1)
	{
		perror("open()");
		return 1;
	}
	
	//char buf[20] = {"\0"};
	//int len = read(fd, buf, 13);

	//printf("%s \n %d \n",buf, len);	
	

	close(fd);

	return 0;
}
