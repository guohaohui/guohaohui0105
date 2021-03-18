#include <stdio.h>
#include <unistd.h>


int main(void)
{
	//标准I/O有缓存区
	printf("hello");
	fflush(NULL);//强制刷新缓存区
	printf("world");

	//文件I/O没有缓存区
	write(1, "good", 4);
	write(1, "morning", 7);


	return 0;//进程表结束刷新缓存区
}
