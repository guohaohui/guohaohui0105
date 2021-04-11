#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MIN 100
#define MAX 300

#define SIZE 201

static int shushu(int s)
{
	for(int i = 2; i < s; i++)
	{
		if(s % i == 0)
			return 0;
	}
	return s;
}
static void *ptr_job(void *s)
{
	int n = (int)s;
	if(shushu(n))
		fprintf(stdout , "%d\n", n);
	
	return (void *)0;
}




int main()
{
	pthread_t tid[SIZE] = {};
	int err;

	for(int i = MIN; i < MAX; i++)
	{
		err = pthread_create(tid + i - MIN, NULL, ptr_job, (void *)i);//创建线程
		if(err) {
			fprintf(stderr, "pthread_create():%s", strerror(err));
			exit(1);
		}
	}
	
	for(int i = MIN; i < MAX; i++)
		pthread_join( tid[i - MIN], NULL);

	pthread_exit((void *)0);
}
