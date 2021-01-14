#include<stdio.h>

// 求100 到 999 内的素数
int N = 0;

int prime();

int main()
{
	int ch;
	for(ch = 100; ch < 1000; ch++)
	{
		while(prime(ch))
		{
			printf("%d\n ",ch);
			break;
		}
	}
	printf("一共%d个素数\n",N);
	return 0;
}


int prime(int a)
{
	int j;
		for(j = 2; j < a; j++)
		{
			if(a % j == 0)
			{
				return 0;
			}
		}
		if(a == j)
		{
			N++;
			return 1;
		}
}




