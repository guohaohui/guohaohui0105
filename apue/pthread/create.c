#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

static void exit_handler1(void *s)
{
	printf("%s is called\n",__FUNCTION__);
}

static void exit_handler2(void *s)
{
	printf("%s is called\n",__FUNCTION__);
}

static void *ptr_job(void *s)
{
	pthread_cleanup_push(exit_handler1, NULL);
	pthread_cleanup_push(exit_handler2, NULL);

	for(int i = 0; i < 8; i++)
	{
		write(1, "*", 1);
		sleep(1);
	}

	//return (void *)0;
	pthread_exit(NULL);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
}

int main()
{
	pthread_t tid;
	int err;

	err = pthread_create(&tid, NULL, ptr_job, NULL);//创建线程
	if(err) {
		fprintf(stderr, "pthread_create():%s", strerror(err));
		exit(1);
	}

	for(int i = 0 ; i < 3; i++) {
		write(1, "!", 1);
		sleep(1);
	}


	pthread_join(tid, NULL);
	pthread_exit((void *)0);


	//ptr_job(NULL);

	return 0;
}
