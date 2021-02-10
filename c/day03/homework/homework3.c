#include<stdio.h>

int prime(int d);
int main()
{
	int n;

	printf("请输入一个整形数：");

	scanf("%d", &n);
	
	if(prime(n))
	{
		printf("%d是素数\n", n);
	}
	else
	{
		printf("%d不是素数\n",n);
	}
	return 0;
}

int prime(int d)
{
	int i;
	for(i = 2; i < d; i++)
	{
		if(d % i == 0)
			break;
	}
	if(i == d)
		return 1;
	else
		return 0;
}


