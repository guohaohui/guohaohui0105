#include <stdio.h>
#include <queue.h>
#include <lstack1.h>
#include <string.h>
#include <stdlib.h>

static int isDigital(char ch)
{
	return ch >= '0' && ch <= '9';
}

static int isOperator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

static int charactorToInt(char ch)
{
	return ch - '0';
}

static int operatorLevel(char ch)
{
	int level = 0;
	
	if(ch == '+' || ch == '-')
		level = 1;
	else if (ch == '*' || ch == '/')
		level = 2;

	return level;
}

char *midToLast(const char *p)
{
	int i;
	int len;
	char top;
	char *res = NULL;
	
	len = strlen(p);

	queue_t *q;//队
	queueInit(sizeof(char), len,&q);//初始化队列
	lstack_t *s;//栈
	lstackInit(sizeof(char), len, &s);//初始化栈

	while(*p) {
		if (isDigital(*p)) {
			enq(q,p);
		} else if (isOperator(*p)) {
			while(!lstackEmpty(s)) {
				lstackPop(s, &top);
				if(operatorLevel(*p) > operatorLevel(top)) {
					lstackPush(s, &top);
					break;
				}
				enq(q, &top);
			}
			lstackPush(s,p);
		} else if(*p == '(') {
			lstackPush(s,p);
		} else if(*p == ')') {
			while(!lstackEmpty(s)) {
				lstackPop(s, &top);
				if(top == '(')
					break;
				enq(q, &top);
			}
		} else
			break;
	
		p++;
	}
	if(*p != '\0') {
		lstackDestory(s);
		queueDestroy(q);
		return NULL;
	}
	while(!lstackEmpty(s)) {
		lstackPop(s, &top);
		enq(q, &top);
	}
	i = 0;
	while(!queueEmpty(q)) {
		res = realloc(res, i + 1);
		deq(q, res + i);
		i++;
	}	
	res = realloc(res, i + 1);
	res[i] = '\0';

	lstackDestory(s);
	queueDestroy(q);

	return res;
}


int main(int argc, char **argv)
{
	if(argc < 2)
		return 1;

	char *r = midToLast(argv[1]);
	puts(r);

	free(r);

	return 0;
}

