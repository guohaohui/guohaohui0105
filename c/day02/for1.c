#include<stdio.h>

int main()
{
	int n, num = 0;
	int a = 0;
	printf("请输入一个整形数：");

	scanf("%d", &n);

	for(n; n > 0; )
	{	
		a = n % 10;
		num = num * 10 +a;
		n = n / 10;
	}
	printf("%d\n", num);

	return 0;
}


