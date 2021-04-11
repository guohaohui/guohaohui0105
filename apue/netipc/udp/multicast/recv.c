#include <stdio.h>
#include <net/if.h>
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
	struct ip_mreqn mrq;

	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	// 绑定地址
	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(RCVPORT);
	// laddr.sin_addr = INADDR_ANY;
	inet_aton("0.0.0.0", &laddr.sin_addr); // 点分十进制地址转换为地址结构体
	if (bind(sd, (struct sockaddr *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	// 加入多播组
	inet_aton(GROUPIP, &mrq.imr_multiaddr);
	mrq.imr_address.s_addr = INADDR_ANY;
	mrq.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mrq, sizeof(mrq)) == -1) {
		perror("setsockopt()");
		goto ERROR;
	}

	// 对端地址长度必须初始化
	raddrlen = sizeof(struct sockaddr_in);
	memset(buf, '\0', MSGMAX);
	cnt = recvfrom(sd, buf, MSGMAX, 0, (struct sockaddr *)&raddr, &raddrlen);
	if (cnt == -1) {
		perror("recvfrom()");
		goto ERROR;
	}


	printf("remote addr:%s %d\n", inet_ntoa(raddr.sin_addr),\
			ntohs(raddr.sin_port));
	printf("data:%s\n", buf);

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

