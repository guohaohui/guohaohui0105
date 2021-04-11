#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "proto.h"

int main(int argc, char *argv[])
{
	int fd;
	struct sockaddr_in laddr;
	char buf[MSGMAX] = {};
	struct sockaddr_in raddr;
	socklen_t raddrlen;

	if(argc < 2)
		exit(0);

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(-1 == fd) {
		perror("socket()");
		exit(1);
	}
#if 0	
	//绑定地址
	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(RCVPORT);
	inet_aton(RCVIP, &laddr.sin_addr);
	if(bind(fd, (struct sockaddr *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	//对段地址长度必须初始化
	raddrlen = sizeof(struct sockaddr_in);

	while(1) {
		mesmet(buf, '\0', MSGMAX);		

		cnt = recvfrom(fd, buf, MSGMAX, 0, (struct sockaddr *)&raddr, &raddrlen);
		if(cnt == -1) {
			perror("recvform()");
			goto ERROR;
		}

		if(strcmp(buf, "exit") == 0)
			break;
		
		printf("remote addr:%s %d\n", inet_ntoa(raddr.sin_addr),\
				ntohs(raddr.sin_port));

		printf("data:%s\n", buf);
	
	}
#endif
	
	//发送
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(RCVPORT);
	inet_aton(RCVIP, &raddr.sin_addr);

	sendto(fd, argv[1], strlen(argv[1])+1, 0, \
			(struct sockaddr *)&raddr, sizeof(raddr));



	close(fd);
	exit(0);
ERROR:
	close(fd);
	exit(1);
}
