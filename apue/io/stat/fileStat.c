#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

static char fileType(const struct stat res);
static char *fileMode(const struct stat res);
static long fileNlink(const struct stat res);
static char *fileUidName(const struct stat res);
static char *fileGidName(const struct stat res);
static long fileSize(const struct stat res);
static char *fileTime(const struct stat res);
int main(int argc, char *argv[])
{
	struct stat res;

	if(argc < 2)
		return 1;

	if(stat(argv[1], &res) == -1)
	{
		perror("stat()");
		return 1;
	}

	printf("%c",fileType(res));
	printf("%s",fileMode(res));
	printf(" %ld",fileNlink(res));
	printf(" %s",fileUidName(res));
	printf(" %s",fileGidName(res));
	printf(" %ld",fileSize(res));
	printf(" %s",fileTime(res));
	printf(" %s\n",argv[1]);
	return 0;
}

//类型
static char fileType(const struct stat res)
{
	
	switch (res.st_mode & S_IFMT) {
		case S_IFBLK:  return 'b';            break;
		case S_IFCHR:  return 'c';            break;
		case S_IFDIR:  return 'd';            break;
		case S_IFIFO:  return 'p';            break;
		case S_IFLNK:  return 'l';            break;
		case S_IFREG:  return '-';            break;
		case S_IFSOCK: return 's';            break;
		default:       return  -1;            break;
	}
}

static char *fileMode(const struct stat res)
{
	static char arr[10]= {'\0'};
//主权限
	switch(res.st_mode & S_IRUSR){
		case S_IRUSR: arr[0] = 'r'; break;
		default:      arr[0] = '-'; break;
	}

	switch(res.st_mode & S_IWUSR){
		case S_IWUSR: arr[1] = 'w'; break;
		default:      arr[1] = '-'; break;
	}

	switch(res.st_mode & S_IXUSR){
		case S_IXUSR: 
			switch(res.st_mode & S_ISUID){
				case S_ISUID: arr[2] = 's'; break;
				default:	  arr[2] = 'x'; break;
			}
		default:      arr[2] = '-'; break;
	}
//组权限
	switch(res.st_mode & S_IRGRP){
		case S_IRGRP: arr[3] = 'r'; break;
		default:      arr[3] = '-'; break;
	}

	switch(res.st_mode & S_IWGRP){
		case S_IWGRP: arr[4] = 'w'; break;
		default:      arr[4] = '-'; break;
	}

	switch(res.st_mode & S_IXGRP){
		case S_IXGRP:
			switch(res.st_mode & S_ISGID){
				case S_ISGID: arr[5] = 's'; break;
				default:	  arr[5] = 'x'; break;
			}
		default:      arr[5] = '-'; break;
	}
//其它权限
	switch(res.st_mode & S_IROTH){
		case S_IROTH: arr[6] = 'r'; break;
		default:      arr[6] = '-'; break;
	}

	switch(res.st_mode & S_IWOTH){
		case S_IWOTH: arr[7] = 'w'; break;
		default:      arr[7] = '-'; break;
	}

	switch(res.st_mode & S_IXOTH){
		case S_IXOTH:
			switch(res.st_mode & S_ISVTX){
				case S_ISVTX: arr[8] = 's'; break;
				default:	  arr[8] = 'x'; break;
			}
		default:      arr[8] = '-'; break;
	}

	return arr;
}
//硬链接数
static long fileNlink(const struct stat res)
{
	return res.st_nlink;
}
//用户名
static char *fileUidName(const struct stat res)
{
	struct passwd *p;
	p = getpwuid(res.st_uid);
	return p->pw_name;
}
//组名
static char *fileGidName(const struct stat res)
{
	struct group *g;
	g = getgrgid(res.st_gid);
	return g->gr_name;
}

//字节大小
static long fileSize(const struct stat res)
{
	return res.st_size;
}
//时间

static char *fileTime(const struct stat res)
{
	struct tm *t;
	static char buf[100] = {};
	t = localtime(&res.st_mtime/*time_t*/);
	if(t == NULL)
		return NULL;
	strftime(buf, 100, "%m月 %d %H:%M", t);

	return buf;
}




