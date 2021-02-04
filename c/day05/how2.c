#include<stdio.h>

#define N 4
int main()
{
	int n;
	int num, num1;
	int arr[4]={};
	printf("请输入一个四位数：");

	scanf("%d", &n);

	for(int i = N-1; i >= 0; i--)
	{
		arr[i] = n % 10;
		n = n / 10;
	}
	
	for(int i = 0; i < N; i++)
	{
		printf("%d", arr[i]);
	}
	printf("\n");
	
	for(int i = 0; i < N; i++)
	{
		arr[i] = (arr[i] + 9) % 10;
	}
	
	for(int i = 0; i < N; i++)
	{
		printf("%d", arr[i]);
	}
	printf("\n");
	num = arr[0];
	arr[0] = arr[2];
	arr[2] = num;

	num1 = arr[1];
	arr[1] = arr[3];
	arr[3] = num1;
	
	for(int i = 0; i < N; i++)
	{
		printf("%d", arr[i]);
	}
	printf("\n");

}	









