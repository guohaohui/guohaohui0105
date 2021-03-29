#include "tbf.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

typedef struct {
	int cps;
	int token;
	int burst;
}tbf_t;

#define MAXTBFS 1024

tbf_t *jobs[MAXTBFS] = {};

static int falg = 0;

static void alrm_handler(int s)
{
	int i;
	alarm(1);
	for(i = 0; i < MAXTBFS; i++) {
		if(jobs[i]) {
			jobs[i]->token += jobs[i]->cps;
			if(jobs[i]->token > jobs[i]->burst)
				jobs[i]->token = jobs[i]->burst;
		}
	}
	
}

static void moduler_load(void)
{
	signal(SIGALRM, alrm_handler);
	alarm(1);
}

static int get_free_pos(void)
{
	for(int i = 0; i < MAXTBFS; i++) {
		if(jobs[i] == NULL)
			return i;
	}
	return -1;
}
//初始化令牌桶
int tbf_init(int cps, int burst)
{
	tbf_t *t;
	int pos;
	
	if(falg == 0) {
		moduler_load();
		falg = 1;
	}

	t = malloc(sizeof(tbf_t));
	if(t == NULL)
		return -1;
	t->cps = cps;
	t->burst = burst;
	t->token = 0;
	
	pos = get_free_pos();
	if(pos < 0) {
		free(t);
		return -1;
	}
	jobs[pos] = t;

	return 0;
}

//取令牌桶
int tbf_fetchtoken(int tbf_id, int ntokens)
{
	int n;
	if(tbf_id >= MAXTBFS || tbf_id < 0)
		return -1;
	
	while(jobs[tbf_id]->token <= 0)
		pause();
	if(jobs[tbf_id]->token > ntokens)
		n = ntokens;
	else
		n = jobs[tbf_id]->token;
	
	jobs[tbf_id]->token -= n;
	
	return n;
}


//销毁指定令牌
void tbf_destroy(int tbf_id)
{
	free(jobs[tbf_id]);
	jobs[tbf_id] = NULL;
}

//销毁所有令牌
void tbf_destroy_all(void)
{
	int i;
	for(i = 0; i < MAXTBFS; i++)
		tbf_destroy(i);
}


//还令牌
int tbf_returntoken(int tbf_id, int ntokens)
{
	
	if(tbf_id >= MAXTBFS || tbf_id < 0)
		return -1;
	jobs[tbf_id]->token += ntokens;
	if(jobs[tbf_id]->token > jobs[tbf_id]->burst)
		jobs[tbf_id]->token = jobs[tbf_id]->burst;
	
	return 0;
}





