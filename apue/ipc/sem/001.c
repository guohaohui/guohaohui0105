#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#define PATH_T "/tmp/out"

#define BUFSIZE 10
static int sempid;

static int P(void);
static int V(void);

int main() 
{
	char buf[BUFSIZE] = {};
	int cnt;
	int n;
	int ret;
	pid_t pid;

	int fd = open(PATH_T, O_RDWR | O_CREAT | O_TRUNC, 0666);

	write(fd, "0", 1);

	if(fd == -1) {
		perror("open()");
		exit(1);
	}
	//创建一个新的信号量集，集合中给一个元素
	sempid = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0600);
	if(sempid == -1) {
		perror("sempid()");
		close(fd);
		exit(1);
	}	

	semctl(sempid, 0, SETVAL, 1);//设置一个信号

	for(int i = 0; i < 20; i++)
	{
		pid = fork();
		if(pid == -1) {
			close(fd);
			perror("fork()");
			exit(1);
		}
		if(pid == 0) {
	
			ret = P();//取信号
			if(ret < 0) {
				fprintf(stderr, "P():%s", strerror(-ret));//向标准错误信号输出打印错误信息
				exit(1);
			}
			lseek(fd, 0, SEEK_SET);
			cnt = read(fd, buf, BUFSIZE);
			if(cnt == -1) {
				perror("read()");
				close(fd);
				exit(1);
			}	
			puts(buf);
			snprintf(buf, BUFSIZE, "%d", atoi(buf)+1);

			lseek(fd, 0, SEEK_SET);
			write(fd, buf, strlen(buf));
			ret = V();//还信号
			if(ret < 0) {
				fprintf(stderr, "P():%s", strerror(-ret));
				exit(1);
			}
			close(fd);
			exit(0);
		}
	}

	for(int i = 0; i < 20 ; i++) {
		wait(NULL);
	}
	close(fd);

	exit(0);
}

static int P(void)
{
	struct sembuf sops;
	
	sops.sem_num = 0;
	sops.sem_op = -1;
	sops.sem_flg = 0;
	
	if(semop(sempid, &sops, 1) == -1) {
		return -errno;
	}
	return 0;
}


static int V(void)
{
	struct sembuf sops;
	
	sops.sem_num = 0;
	sops.sem_op  = 1;
	sops.sem_flg = 0;
	
	if(semop(sempid, &sops, 1) == -1) {
		return -errno;
	}
	return 0;
}
