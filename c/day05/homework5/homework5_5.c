#include<stdio.h>

int main()
{
	int i, j;
	int n;
	int tem;
	int arr[9] = {1,4,80,23,47,76,14,52};
	
	for(i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	printf("\n");

	printf("请输入要插入的数:");

	scanf("%d", &n);
	
	for(i = 0; i < 8; i++)  //插入
	{
		if(n > arr[i])
		{
			tem = arr[i + 1];
			for(j = 9; j > i+1; j--)
			{
				arr[j] = arr[j - 1];
			}
			arr[i + 1] = n;
			break;
		}else
		{
			for(j = 9; j >= 1; j--)
				arr[j] = arr[j -1];
			arr[0] = n;
			break;
		}
	}
	for(i = 0; i < 9; i++)   // 打印
		printf("%d ", arr[i]);
	printf("\n");

	for(i = 0; i < 9; i++)//从大到小排序
	{
		for(j = i+1; j < 9; j++)
		{
			if(arr[j]>arr[i])
			{
				tem = arr[j];
				arr[j] = arr[i];
				arr[i] = tem;
			}
		}
	}
	for(i = 0; i < 9; i++)// 打印
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}




