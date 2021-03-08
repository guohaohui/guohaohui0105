#include <stdio.h>
#include "queue.h"

int main(void)
{	
	queue_t *me;
	int n;
	queueInit(sizeof(int), 10, &me);//初始化

	for(int i = 1; i < 100; i++)
	{
		if(enq(me, &i)!= 0)//入队
		{
			break;
		}
	}
	
	while(!queueEmpty(me))
	{
		deq(me, &n);//出队
		printf("%-4d ", n);
	}
	printf("\n");
	for(int i = 21; i < 100; i++)
	{
		if(enq(me, &i)!= 0)//入队
		{
			break;
		}
	}
	
	while(!queueEmpty(me))
	{
		deq(me, &n);//出队
		printf("%-4d ", n);
	}
	printf("\n");
	queueDestroy(me);//销毁
	return 0;
}
