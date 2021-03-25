#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


#define BUFSIZE 512
int directory(char *buf)
{
	struct stat res;

	if(stat(buf, &res) == -1)
	{
		perror("stat()");
		return -1;
	}
	if(res.st_mode & S_IFMT == S_IFDIR)
	{
		return 1;
	}   
	return 0;
}
int data(char *buf)
{

	struct stat res;

	if(stat(buf, &res) == -1)
	{
		perror("stat()");
		return -1;
	}
	return res.st_blocks;
}

char *charCat(struct dirent *entry, char *buf)
{		

	strcat(buf, "/");
	strncat(buf, entry->d_name, BUFSIZE);
	puts(buf);
	return buf;
}           

static long long blocks(DIR *fd, char *buf)
{
	char *arr[BUFSIZE];
	struct dirent *entry;
	struct stat res;
	long long sum;
	entry = readdir(fd);
	if(entry == NULL)
	{   
		if(!errno) 
			return 0;
		closedir(fd);
		return -1;
	}
	arr = charCat(entry, buf);

	if(stat(arr, &res) == -1)
	{
		perror("stat()");
		return -1;
	}
	if(!(res.st_mode & S_IFMT == S_IFDIR))
	{
		return res.st_blocks;
	}

	sum = 0;
	if(directory(arr)==-1)
		return 0;
	if(directory(arr))
	{
		fd = opendir(arr);
		sum +=blocks(fd, arr);
	}
	sum += res.st_blocks;
	return sum;
}

int main(int argc, char *argv[])
{
	DIR *fd;
	struct dirent *entry;
	char buf[BUFSIZE] = {};
	char buf1[BUFSIZE] = {};
	if(argc < 2)
		return 1;
	fd = opendir(argv[1]);
	if(fd == NULL)
	{
		perror("opendir()");
		return 1;
	}
	strcpy(buf, argv[1]);
	puts(buf);
	blocks(fd, buf);

	return 0;
}
