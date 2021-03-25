#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 128

static long data(DIR *fd,struct dirent *entry,struct stat res, char *buf, char *a);
int main(int argc, char *argv[])
{

	DIR *fd;
	struct dirent *entry;
	long size = 0;
	struct stat s;
	char buf[BUFSIZE] = {};
	if(argc < 2)
		return 1;

	stat(buf , &s);
	fd = opendir(argv[1]);
	if(fd == NULL)
	{
		perror("opendir()");
		return 1;
	}
	
	strncpy(buf, argv[1], BUFSIZE);
	size = data(fd, entry, s, buf, argv[1]);
#if 0
	while(1)
	{
		entry = readdir(fd);
		if(entry == NULL)
		{
			if(!errno)
				break;
			goto READERROR;
		}
		memset(buf ,'\0', BUFSIZE);
		strncpy(buf, argv[1], BUFSIZE);
		strcat(buf, "/");
		strncat(buf, entry->d_name, BUFSIZE);
		if(stat(buf , &s) == -1)
		{
			perror("stat()");
			goto READERROR;
		}
		size += s.st_size;
		//printf("%s\n", entry->d_name);
	}
#endif
	printf("%ld\n", size);
	closedir(fd);
	return 0;
READERROR:
	closedir(fd);
	return 1;
}
static void cat(char *buf, char *a, struct dirent *entry)
{
	strcat(buf, "/");
	strncat(buf, entry->d_name, BUFSIZE);
}


static long data(DIR *fd,struct dirent *entry,struct stat res, char *buf, char *a)
{
	entry = readdir(fd);
	if(entry == NULL)
	{
		if(!errno)
			return 0;
		return -1;
	}
	memset(buf ,'\0', BUFSIZE);
	cat(buf, a, entry);
	puts(buf);
	if(res.st_mode & S_IFMT == S_IFDIR)
	{
		fd = opendir(buf);
		return data(fd,entry,res, buf,a) + res.st_blocks;
	}
	else
	{
		return data(fd,entry,res,buf,a);
	}
}

