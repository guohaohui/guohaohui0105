#include <stdio.h>
#include "lstack1.h"


int main(void)
{
	lstack_t *me;

	int n;	
	lstackInit(sizeof(int),10, &me);
	
	for(int i = 1; i<100; i++)
	{
		if(lstackPush(me, &i)!= 0)
		{
			break;
		}
	}
	while(!lstackEmpty(me))
	{
		lstackPop(me, &n);
		printf("%d\n",n);
	}

	lstackDestory(me);

	return 0;

}
