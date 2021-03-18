#include <stdio.h>

#define FILENAME "./mycat.c"

#define BUFSIZE 100


int main()
{
	FILE *fd;
	char buf[BUFSIZE] = {};
	int cnt;

	fd = fopen(FILENAME, "r");
	if(fd == NULL)
	{
		perror("fopen()");
		return 1;
	}

	fseek(fd, 10, SEEK_CUR);//设置偏移量

	printf("%ld\n", ftell(fd));//打印偏移了多少字节
	rewind(fd);//把偏移量设置到开头

	cnt = fread(buf, 1, BUFSIZE, fd);

	fwrite(buf, 1, cnt, stdout);
	
	fclose(fd);

	return 0;
}
