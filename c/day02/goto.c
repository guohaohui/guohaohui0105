#include <stdio.h>

int main()
{
	int i = 0;
 	int n;
	do
	{
		printf("请输入一个数：");
		scanf("%d", &n);
	}while(n < 0 || n >100);


LOOP:
	if(i < 10)
	{
		printf("%d\n", i);
		i++;
		goto LOOP;
	}

	return 0;
}
