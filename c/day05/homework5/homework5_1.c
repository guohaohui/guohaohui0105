/*从终端（键盘）读入20个数据到数组中
  ，统计其中正数的个数，并计算这些正数之和。*/
#include<stdio.h>

#define N 20

int main()
{
	int i;
	int n = 0, sum = 0;
	int arr[N] = {};
	printf("请输入20个整形数：\n");
	for(i = 0; i < N; i++)
	{
		scanf("%d", &arr[i]);
		if(arr[i] > 0)
		{
			n++;
			sum += arr[i];
		}
	}
	printf("\n");
	
	printf("一共%d个正数合是%d\n",n ,sum);
	
	return 0;
}




