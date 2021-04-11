#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/epoll.h>

#define BUFSIZE	64
#define TTY1	"/dev/tty8"
#define TTY2	"/dev/tty9"

enum {
	STATE_R,
	STATE_W,
	STATE_EX,
	STATE_T
};
// 抽象状态机类型
struct relay_st {
	int rfd;
	int wfd;
	int state;
	char buf[BUFSIZE];
	int readcnt;
	char *errmsg;
	int pos;
};

// 状态机推动
int relay_drive(struct relay_st *r)
{
	int n;

	switch(r->state) {
		case STATE_R:
			r->readcnt = read(r->rfd, r->buf, BUFSIZE);
			if (r->readcnt == -1) {
				if (errno != EAGAIN) {
					// 文件为空--》假错
					r->errmsg = "read()";
					r->state = STATE_EX;	
				}
			} else if (r->readcnt == 0) {
				r->state = STATE_T;
			} else {
				r->pos = 0;
				r->state = STATE_W;	
			}
			break;
		case STATE_W:
			n = write(r->wfd, r->buf+r->pos, r->readcnt);
			if (n == -1) {
				if (errno != EAGAIN) {
					r->state = STATE_EX;
					r->errmsg = "write()";
				}
			} else if (n < r->readcnt) {
				r->pos += n;	
				r->readcnt -= n;
			} else {
				r->state = STATE_R;
			}
			break;
		case STATE_EX:
			fprintf(stderr, "%s:%s\n", r->errmsg, strerror(errno));
			r->state = STATE_T;
			break;
		case STATE_T:
			break;
	}

	return 0;
}

struct relay_st *relay_create(int rfd, int wfd)
{
	struct relay_st *me;
	int rfd_save, wfd_save;

	me = malloc(sizeof(*me));
	if (NULL == me)
		return NULL;

	// 确保rfd, wfd都是非阻塞io
	rfd_save = fcntl(rfd, F_GETFL);
	fcntl(rfd, F_SETFL, rfd_save | O_NONBLOCK);
	wfd_save = fcntl(wfd, F_GETFL);
	fcntl(wfd, F_SETFL, wfd_save | O_NONBLOCK);

	me->rfd = rfd;
	me->wfd = wfd;
	me->state = STATE_R;
	memset(me->buf, '\0', BUFSIZE);
	me->pos = 0;
	me->errmsg = NULL;
	me->readcnt = 0;

	return me;
}


int main(void)
{
	int fd1, fd2;
	struct relay_st *fd12, *fd21;
	
	int epfd;
	struct epoll_event evt, revt;

	fd1 = open(TTY1, O_RDWR);
	if (-1 == fd1) {
		perror("open()");
		exit(1);
	}

	fd2 = open(TTY2, O_RDWR | O_NONBLOCK);
	// if error

	fd12 = relay_create(fd1, fd2);
	fd21 = relay_create(fd2, fd1);

	//	创建epoll实例
	epfd = epoll_create(1);
	if(epfd == -1)
		goto ERROR;
	
	evt.events = 0;
	evt.data.fd = fd1;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd1, &evt);
	evt.events = 0;
	evt.data.fd = fd2;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd2, &evt);


	while (1) {
		if (fd12->state == STATE_T && fd21->state == STATE_T)
			break;
		if (fd12->state == STATE_EX) {
			relay_drive(fd12);
			continue;
		}

		if (fd21->state == STATE_EX) {
			relay_drive(fd21);
			continue;
		}

		evt.events = 0;
		evt.data.fd = fd1;

		if (fd12->state == STATE_R) {
			evt.events |= EPOLLIN;
		}
		if (fd21->state == STATE_W)
			evt.events |= EPOLLOUT;
		epoll_ctl(epfd, EPOLL_CTL_MOD, fd1, &evt);

		evt.events = 0;
		evt.data.fd = fd2;

		if (fd12->state == STATE_W)
			evt.events |= EPOLLOUT;
		if (fd21->state == STATE_R)
			evt.events |= EPOLLIN;

		epoll_ctl(epfd, EPOLL_CTL_MOD, fd2, &evt);

		while(epoll_wait(epfd, &revt, 1, -1) < 0) {
			if (errno == EINTR)
				continue;
			perror("select()");
			goto ERROR;
		}

		if (revt.events & EPOLLIN && revt.data.fd == fd1 || \
				revt.events & EPOLLOUT && revt.data.fd == fd2)
			relay_drive(fd12);
		if (revt.events & EPOLLIN && revt.data.fd == fd2 || \
				revt.events & EPOLLOUT && revt.data.fd == fd1)
			relay_drive(fd21);
	}

	free(fd12);
	free(fd21);

	close(fd1);
	close(fd2);
	close(epfd);
	exit(0);
ERROR:
	free(fd12);
	free(fd21);

	close(fd1);
	close(fd2);
	close(epfd);
	exit(1);
}






