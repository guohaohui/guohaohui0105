#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THRNR	4
#define START	100
#define END		300

/*
 job > 0所发放的任务
 job == 0 任务已经被取走
 job == -1 所有任务发放完成
 */
static int job = 0; // 临界区
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;//初始化互斥量
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


static int is_primer(int n)
{
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return 0;
	return 1;
}

static void *thr_job(void *s)
{
	int gent;
	while(1) {
		pthread_mutex_lock(&mut);
		while(job == 0) {
			/*
			pthread_mutex_unlock(&mut);
			sched_yield();
			continue;
			*/
			pthread_cond_wait(&cond, &mut);
			if (job == -1) {
				/*
				   pthread_mutex_unlock(&mut);
				   pthread_exit((void *)0);
				 */
				pthread_mutex_unlock(&mut);
	//			printf("1111111111111\n");
				pthread_exit((void *)0);
			}
		}
		gent = job;
		pthread_cond_broadcast(&cond);
		job = 0;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mut);
		if(is_primer(gent)) {
			printf("%d is primer\n", gent);
		}
			
	}
	pthread_exit((void *)0);
}

int main(void)
{
	pthread_t tids[THRNR] = {};
	int i;

	for (i = 0; i < THRNR; i++)	{
		pthread_create(tids+i, NULL, thr_job, NULL);
		// if error
	}

	// 发放任务
	for (i = START; i <= END; i++) {
		pthread_mutex_lock(&mut);

		if (job != 0) {
			/*
			// 上次任务还未被取走
			pthread_mutex_unlock(&mut);
			sched_yield();//出让调度，让内核先执行其它线程
			pthread_mutex_lock(&mut);
			*/
			pthread_cond_wait(&cond, &mut);
		}
		job = i;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mut);
	}

	// 任务发放完成
	pthread_mutex_lock(&mut);
	if (job > 0) {
		/*
		// 最后一个任务还未取走
		pthread_mutex_unlock(&mut);
		sched_yield();
		pthread_mutex_lock(&mut);
		*/
		pthread_cond_wait(&cond, &mut);
	}
	job = -1;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mut);

	for (i = 0; i < THRNR; i++)
		pthread_join(tids[i], NULL);

	pthread_mutex_destroy(&mut);
	pthread_cond_destroy(&cond);

	exit(0);
}
