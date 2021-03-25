#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>

#define LOCKFILE "/var/run/daemon.pid"

int mydaemon(void);
int run_already(void);
int main()
{
	time_t t;
	struct tm *res;
	char buf[512] = {};
	int fd1 = open("/tmp/ous", O_RDWR | O_CREAT | O_TRUNC, 0666);

	if(fd1 == -1)
	{
		perror("open");
		//syslog(LOG_ERR, "open1()%s", strerror(errno));
		exit(1);
	}
	if(-1 == mydaemon())
	{
		printf("错误\n");
		exit(1);
	}
	
	if(-1 == run_already())
	{
		syslog(LOG_ERR, "run_already():%s", strerror(errno));
		exit(1);
	}

	openlog(NULL, LOG_PID, LOG_DAEMON);
	

	while(1){
		time(&t);

		res = localtime(&t);
		if(res == NULL)
			exit(1);
		memset(buf, '\0', 512);
	//	strftime(buf, 512, "%Y-%m-%d %H:%M:%S",res);

		write(fd1, buf, strlen(buf));

		syslog(LOG_INFO, "%s", buf);

		write(fd1, "\n", 1);
		sleep(1);
		closelog();
	}
	exit(0);


}


int mydaemon(void)//创建守护进程
{
	pid_t pid;
	pid_t sid;
	int fd;
	pid = fork();
	if(-1 == pid)
	{
		perror("fork()");
		return -1;
	}

	if(pid > 0)
		exit(0);
	
	sid = setsid();
	if(sid == -1)
	{
		perror("setsid()");
		return -1;
	}
	
	umask(0);
	chdir("/");
	
	fd = open("/dev/null", O_RDWR);

	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if(fd > 2)
	{
		close(fd);
	}
	
	return 0;
}


int run_already(void)
{

	char buf[512] = {};

	int fd = open(LOCKFILE, O_WRONLY | O_CREAT, 0664);
	
	if(fd == -1)
	{
		syslog(LOG_ERR, "open():%s", strerror(errno));
		return -1;
	}
	
	if(lockf(fd, F_TLOCK, 0) == -1)
	{
		syslog(LOG_ERR, "lockf():%s", strerror(errno));
		close(fd);
		return -1;
	}
	
	ftruncate(fd, 0);//截断为零
	snprintf(buf, 512, "%d", getpid());
	write(fd, buf, strlen(buf));

	return 0;
}
	



