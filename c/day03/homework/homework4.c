#include<stdio.h>

int feibo(int n);

int main()
{
	int n;

	printf("请输入第几项：");

	scanf("%d", &n);
	
	printf("第%d项为%d\n", n, feibo(n));

}

int feibo(int n)//非波
{
	int i = 1, j = 1;
	int num1 = 1;
	int num2 = 1;
	int num3 = 0;
	if(n == 1)
		return 1;
	else
	{
		for(n; n > 1; n--)
		{
			num3 = num1 + num2;
			num1 = num2;
			num2 = num3;	

		}
		return num3;
	}
}


