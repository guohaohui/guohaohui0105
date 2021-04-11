#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	char *ptr = NULL;
	int fd;
	struct stat res;
	
	if(argc < 2)
		exit(0);
	
	fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		perror("open()");
		exit(1);
	}

	if(fstat(fd, &res) == -1)
	{
		perror("fstat()");
		close(fd);
		exit(1);
	}

	ptr = mmap(NULL, res.st_size, PROT_READ,  MAP_PRIVATE, fd, 0);//映射
	
	puts(ptr);

	munmap(ptr, res.st_size);

	close(fd);

	exit(0);
}
