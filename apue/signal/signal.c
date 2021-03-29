#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
typedef void (*sighandler_t)(int);

static void handler(int s)// s 响应此信号处理函数的值
{
	printf("arg s:%d\n", s);
	for(int i = 0; i < 3; i++) {
		write(1, "!", 1);
		//kill(getpid(), SIGSTOP);
		sleep(1);
	}
}


int main()
{
	int i = 0;
	//sighandler_t sig = signal(SIGINT, handler);

	//sighandler_t sig1 = signal(SIGQUIT, handler);

	struct sigaction act, oldact;

	act.sa_handler = handler;
	act.sa_flags = 0;

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaction(SIGQUIT, &act, &oldact);


	while(1) {
		
		if(i > 10)
		{
			//signal(SIGINT,sig);
			sigaction(SIGQUIT, &oldact, NULL);
			//signal(SIGQUIT,sig1);
		}
		printf("*");
		fflush(NULL);
		sleep(1);
		i++;
	}

	exit(0);
}
