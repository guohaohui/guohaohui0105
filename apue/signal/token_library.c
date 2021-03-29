#include "token_library.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define PAILSIZE 1024

int flage = 0;

token_st *token[PAILSIZE] = {};

static void alrm_handler(int s)
{
	alarm(1);
	for (int i = 0; i < PAILSIZE; i++)
	{
		if(token[i] != NULL)
		{
			token[i]->token += token[i]->cps;
			if(token[i]->token >= token[i]->burst)
			{
				token[i]->token = token[i]->burst;
			}
		}
	}
}

int tokenInit(int cps, int burst)//速率，上限
{
	int fd;
	for(fd = 0; fd < PAILSIZE; fd++)
	{
		if(token[fd]  == NULL)
		{
			token[fd] = malloc(sizeof(token_st));	
			if(token[fd] == NULL)
				return -1;
			token[fd]->cps = cps;
			token[fd]->burst = burst;
			token[fd]->token = 0;
			if(flage == 0)
			{
				flage = 1;
				signal(SIGALRM, alrm_handler);
				alarm(1);
			}
			break;
		}
	}
	return fd;
}


int tokenDele(int fd, int tokens)//桶描述符，令牌桶个数
{
	int res;
	while(token[fd]->token < token[fd]->cps)//限流
		pause();
	if(tokens > token[fd]->token)
	{
		res = token[fd]->token;
		token[fd]->token = 0;
		return res;
	}
	token[fd]->token -= tokens;
	return tokens;
}

void tokenFree(int fd)//桶描述符
{
	free(token[fd]);
	token[fd] = NULL;
}
