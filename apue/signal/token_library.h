#ifndef _TOKEN_H
#define _TOKEN_H


typedef struct {
	int token;//令牌
	int cps;//速率
	int burst;//上限
}token_st;

int tokenInit(int cps, int burst);//速率，上限

int tokenDele(int fd, int tokens);//桶描述符，令牌桶个数

void tokenFree(int fd);//桶描述符



#endif

