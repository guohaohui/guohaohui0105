#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "proto.h"

int main(void)
{
	struct sockaddr_in laddr;
	char buf[MSGMAX] = {};
	struct sockaddr_in raddr;
	socklen_t raddrlen;
	int cnt;

	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	// 绑定地址
	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(RCVPORT);
	inet_aton(RCVIP, &laddr.sin_addr); // 点分十进制地址转换为地址结构体
	if (bind(sd, (struct sockaddr *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	// 对端地址长度必须初始化
	raddrlen = sizeof(struct sockaddr_in);
	while (1) {
		memset(buf, '\0', MSGMAX);
		cnt = recvfrom(sd, buf, MSGMAX, 0, (struct sockaddr *)&raddr, &raddrlen);	
		if (cnt == -1) {
			perror("recvfrom()");
			goto ERROR;
		}

		if (strcmp(buf, "exit") == 0)
			break;

		printf("remote addr:%s %d\n", inet_ntoa(raddr.sin_addr),\
				ntohs(raddr.sin_port));
		printf("data:%s\n", buf);
	}

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}


