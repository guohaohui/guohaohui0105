#include<stdio.h>

int common_divisor(int a, int b);

int main()
{
	int num1, num2;

	printf("请输入两个整形数：");

	scanf("%d%d", &num1, &num2);
	
	printf("最大公约数为%d\n", common_divisor(num1, num2));
	
	return 0;
}

int common_divisor(int a, int b)
{

	int i;
	int t;
	if(a > b)
	{
		t = a;
		a = b;
		b = t;
	
	}
	for(i = a; i > 0; i--)
	{
		if(a % i == 0 && b % i == 0)
			return i;
			
	}

}
int commmon_dicisor(int a, int b)
{
	int t;
	if(a > b)
	{
		t = a;
		a = b;
		b = t;
	}
	while(1)
	{
		t = b % a;
		if(t == 0)
			return a;
		b = a;
		a = t;
	}









