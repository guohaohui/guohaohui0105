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
	int cnt;

	key = ftok(PATHNAME, PROJID); //获取key值，没有血亲关系的两个进程通信key值要一样
	if(-1 == key) {
		perror("ftok()");
		exit(1);
	}
	
	msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0666);//用于创建一个新的或打开一个已经存在的消息队列
	if(-1 == msgid) {
		if(errno == EEXIST) {
			msgid = msgget(key, 0);
			created = 0;
		} else {
			perror("msgget()");
			exit(1);
		}
	}

	while(1) {
		cnt = msgrcv(msgid, &buf, MSGSIZE, -5, 0);//读消息
		if(-1 == cnt) {
			perror("msgrcv()");
			goto ERROR;
		}
		if(strcmp(buf.msg, "exit") == 0)
			break;
		puts(buf.msg);
	}

	if(created) {
		msgctl(msgid, IPC_RMID, NULL);
	}

	exit(0);
ERROR:
	if(created) {
		msgctl(msgid, IPC_RMID, NULL);
	}
	exit(1);
}

