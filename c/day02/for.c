#include <stdio.h>

int main()
{
	/*
	int i;

	for(i = 0; i < 10; i++)
	{
		printf("第%d次运球\n",i+1);
		if(i == 3)
		{
			printf("小名肚子疼，停止训练\n");
			break;
		}
	}
*/

	int n, num = 0;

	printf("请输入一个整数:\n");

	scanf("%d", &n);
	
	for(int i = 1; i <= n; i++)
	{
		if(i % 2 == 1)
			num += i;
	}

	printf("前%d项合为%d\n", n, num);
	return 0;
}


