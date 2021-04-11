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

int main(int argc, char *argv[])
{
	char buf[MSGMAX] = {};
	struct sockaddr_in raddr;
	struct ip_mreqn mrq;

	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	// 绑定地址 可省略

	// 设置为多播
	inet_aton(GROUPIP, &mrq.imr_multiaddr);
	mrq.imr_address.s_addr = INADDR_ANY;
	mrq.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &mrq, sizeof(mrq)) == -1) {
		perror("setsockopt()");
		goto ERROR;
	}

	// 发送
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(RCVPORT);
	inet_aton(GROUPIP, &raddr.sin_addr);
	while (1) {
		sendto(sd, "hello", 5, 0, \
				(struct sockaddr *)&raddr, sizeof(raddr));
		sleep(1);
	}
	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}


