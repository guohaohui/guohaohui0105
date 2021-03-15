#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd;
	char buf[100] = {};
	int cnt;
	int lse;
	if(argc < 2)
		return 1;

	fd = open(argv[1], O_RDWR/* | O_APPEND*/);
	if(fd == -1)
	{
		perror("open()");
		return 1;
	}
	printf("%ld\n", lseek(fd,0, SEEK_CUR));//偏移0
	read(fd, buf, 10);
	puts(buf);

	lse = lseek(fd, -40, SEEK_END);//从文件末尾偏移-40个字节
	printf("%d\n", lse);
	write(fd ,"guohaohui", 9);

	//空洞文件
	lseek(fd, 1024, SEEK_END);
	write(fd, "g" ,1);

	close(fd);

	return 0;
}
