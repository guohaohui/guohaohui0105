#include <stdio.h>
#include <queue.h>
#include <lstack1.h>
#include <string.h>
#include <stdlib.h>

int lastRes(const char *p);
char *midToLast(const char *p);
int main(int argc, char **argv)
{
	if(argc < 2)
		return 1;

	char *r = midToLast(argv[1]);
	puts(r);
	printf("%d\n", lastRes(r));
	free(r);

	return 0;
}


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
		if (isDigital(*p)) { //如果是数字
			enq(q,p);			//入队
		} else if (isOperator(*p)) { //如果是运算符
			while(!lstackEmpty(s)) { //栈不为空
				lstackPop(s, &top);	//出栈
				if(operatorLevel(*p) > operatorLevel(top)) {//判断优先级
					lstackPush(s, &top); //入栈
					break;
				}
				enq(q, &top);//入队
			}
			lstackPush(s,p);//入栈
		} else if(*p == '(') {
			lstackPush(s,p);
		} else if(*p == ')') {
			while(!lstackEmpty(s)) {//栈不为空
				lstackPop(s, &top);	//出栈
				if(top == '(')
					break;
				enq(q, &top);//入队
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
	while(!lstackEmpty(s)) {//栈不为空
		lstackPop(s, &top);
		enq(q, &top);
	}
	i = 0;
	while(!queueEmpty(q)) {//队列不为空
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

static int op2num(int left, int right, char op)
{
	int res;

	switch(op) {
		case '+':
			res = left + right;
			break;
		case '-':
			res = left - right;
			break;
		case '*':
			res = left * right;
			break;
		case '/':
			res = left / right;
			break;
		default:
			//异常
			break;
	}
	return res;
}

int lastRes(const char *p)
{
	lstack_t *s;
	int left ,right;
	int res;
	int push;

	lstackInit(sizeof(int), strlen(p), &s);
	
	while(*p) {
		if(isDigital(*p)) {
			push = charactorToInt(*p);
			lstackPush(s, &push);
		} else {
			lstackPop(s, &right);
			lstackPop(s, &left);
			// if error

			res = op2num(left, right, *p);

			lstackPush(s, &res);
		}
		p++;
	}
	lstackPop(s, &res);
	if(!lstackEmpty(s)) {
		exit(1);
	}

	lstackDestory(s);

	return res;
}





