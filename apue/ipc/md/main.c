#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define BUFSIZE 512

struct msgbuf {
	long mtype;
	char msg[BUFSIZE];
};


int main()
{
	int msgpid;
	struct msgbuf buf;
	int created = 1;
	pid_t pid;
	msgpid = msgget(IPC_PRIVATE,IPC_CREAT | IPC_EXCL | 0600);//用于创建一个新的或打开一个已经存在的消息队列
	if(msgpid == -1)
	{
		if(errno == EEXIST) {
			msgpid = msgget(IPC_PRIVATE, 0);
			created = 0;
		} else {
			perror("msgget()");
			exit(1);
		}
	}
	
	pid = fork();//创建子进程
	if(pid == -1) {
		perror("fork()");
		msgctl(msgpid, IPC_RMID, NULL);
		exit(1);
	}

	if(0 == pid) {
		buf.mtype = 1;
		strcpy(buf.msg, "guo hao hui");
		msgsnd(msgpid, &buf, strlen(buf.msg) + 1, 0);//将一个新的消息写入队列
		if(created)
			msgctl(msgpid, IPC_RMID, NULL);// IPC_RMID销毁队列
		exit(0);
	}

	msgrcv(msgpid, &buf, BUFSIZE, 1, 0);//从消息队列中读取消息
	puts(buf.msg);

	if(created)
		msgctl(msgpid, IPC_RMID, NULL);
	exit(0);

}
