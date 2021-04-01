#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;

	char *ptr;

	ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1 , 0);
	if(MAP_FAILED == ptr) {
		perror("mmap()");
		exit(1);
	}

	pid = fork();
	if(-1 == pid) {
		perror("fork()");
		exit(1);
	}

	if(pid == 0) {
		memcpy(ptr, "guo hao hui", 11);
		munmap(ptr, 1024);
		exit(0);
	}

	wait(NULL);

	puts(ptr);

	munmap(ptr, 1024);


	exit(0);
}
