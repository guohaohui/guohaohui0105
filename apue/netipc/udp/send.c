#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	char buf[MSGMAX] = {};
	struct sockaddr_in raddr;

	if (argc < 2)
		exit(1);

	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	// 绑定地址 可省略

	// 发送
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(RCVPORT);
	inet_aton(RCVIP, &raddr.sin_addr);
	sendto(sd, argv[1], strlen(argv[1])+1, 0, \
			(struct sockaddr *)&raddr, sizeof(raddr));

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}


