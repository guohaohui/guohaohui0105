#ifndef __PROTO_H
#define __PROTO_H

#define PATHNAME "/etc/passwd"
#define PROJID 	 1

#define MSGSIZE 512

//数据格式
struct msgbuf {
	long mtype;
	char msg[MSGSIZE];
};

#endif
