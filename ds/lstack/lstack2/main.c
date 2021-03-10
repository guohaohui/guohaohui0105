#include <stdio.h>
#include "lstack1.h"
#include <stdlib.h>
void transfer(lstack_t *ls, int x, int y)
{
	int a;
	while(x != 0)
	{
		a = x % y;
		lstackPush(ls,&a);
		x = x/y;
	}	
}

int main(int argc, char *argv[])
{

	lstack_t *me;
	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	int n;	
	lstackInit(sizeof(int),100, &me);
	
	transfer(me,x,y);
	while(!lstackEmpty(me))
	{
		lstackPop(me, &n);
		if(n > 9)
			printf("%c\n", n+87);
		else
			printf("%d\n",n);
	}

	lstackDestory(me);

	return 0;

}
