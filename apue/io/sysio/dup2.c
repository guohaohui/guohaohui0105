#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int rfd, wfd;



	if(argc > 1 && strcmp(argv[1], ">>>>")==0)
	{
		wfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if(wfd == -1)
		{
			perror("open()");
			return 1;
		}
		dup2(wfd, 1);
	}

	for(int i = 0; i < 10; i++)
	{
		for(int j = 1; j <= i; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	
	close(wfd);

	return 0;
}

