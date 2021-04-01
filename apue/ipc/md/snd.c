#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int msgid;
	key_t key;
	struct msgbuf buf;
	int created = 1;

	if(argc < 3)
		exit(1);

	key = ftok(PATHNAME, PROJID); //获取key值，没有血亲关系的两个进程通信key值要一样
	if(-1 == key) {
		perror("ftok()");
		exit(1);
	}
	
	msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0666);//创建消息队列
	if(-1 == msgid) {
		if(errno == EEXIST) {
			msgid = msgget(key, 0);//如果存在获取当前队列
			created = 0;
		} else {
			perror("msgget()");
			exit(1);
		}
	}
	
	buf.mtype = atoi(argv[1]);
	strncpy(buf.msg, argv[2], MSGSIZE);
	msgsnd(msgid, &buf, strlen(buf.msg)+1 ,0);//发送消息

	if(created) {
		msgctl(msgid, IPC_RMID, NULL);
	}

	exit(0);
}

