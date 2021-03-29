#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void handler1(int s)
{
	write(1, "!", 1);
}

static void handler2(int s)
{
	write(1, "#", 1);
}

int main(void)
{
	sigset_t set, oldset;
	
	signal(SIGINT, handler1);
	signal(SIGQUIT, handler2);
	
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);

	for(int i = 0; i < 10; i++) {
		//每一行执行期间不受SIGINT和SIGQUIT干扰
		sigprocmask(SIG_BLOCK, &set, &oldset);
		for(int j = 0; j < 5; j++) {
			write(1, "*", 1);
			sleep(1);
		}
		write(1, "\n", 1);
		sigprocmask(SIG_SETMASK, &oldset, NULL);
	}




	exit(0);
}
