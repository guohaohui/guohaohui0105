/*1.组合数的和
 给定 N 个非 0 的个位数字，用其中任意 2 个数字都可以组合成 1 个 2 位的数字。
 要求所有可能组合出来的 2 位数字的和。例如给定 2、5、8，则可以组合出：25、28、52、58、82、85，它们的和>    为330。
 输入格式：
 输入在一行中先给出 N（1 < N < 10），随后给出 N 个不同的非 0 个位数字。数字间以空格分隔。*/

#include<stdio.h>

#define N 9

int main()
{
	int n;
	int arr[N] = {};
	int i, j;
	int sum = 0;

	do{
		printf("产生多少个10以内的整形数：");
		scanf("%d", &n);
	
	}while(N < 1 || N > 9);
	
	for(i = 0; i < n; i++)
	{
		scanf("%d", arr+i); //等价&arr[i]
		if(arr[i] < 1 || arr[i] > 9)
		{
			printf("请重新输入：");
			i--;
			continue;
		}
		
		for(j = i-1; j >= 0; j--)
		{
			if(arr[i] == arr[j])
			{
				break;
			}
		}
		if(j>=0)
		{
			printf("输入有重复请重新输入：");
			i--;
			continue;
		}

	}
	
	for(i = 0; i < n; i++)// 组合
	{
		for(j = 0; j < n; j++)
		{
			if(i != j)
			{
				printf("%d ",arr[i]*10 + arr[j]);
				sum += arr[i]*10 + arr[j];
			}
			
		}
	}
	
	printf("\n");
	printf("sum = %d\n", sum);

	return 0;
}





