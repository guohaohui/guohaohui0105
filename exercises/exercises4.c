#include <stdio.h>
//完全平方数
int main()
{
	int i, j;
	
	for(i = 10; i < 15; i++)
	{
		for(j = 100; j <=200; j++)
		{
			if(i * i == j)
			{
				printf("%d\n",j);
			}
		}
	}
}










