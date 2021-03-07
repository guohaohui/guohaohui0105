#include <stdio.h>
#include "lstack1.h"


int main(void)
{
	lstack_t *me;

	int n;	

	lstackInit(sizeof(int), &me);
	
	for(int i = 1; i<10; i++)
	{
		lstackPush(me, &i);
	}
	while(lstackFull(me))
	{
		lstackPop(me, &n);
	printf("11111111111111111111\n");
		printf("%d\n",n);
	}

	lstackDestory(me);

}
