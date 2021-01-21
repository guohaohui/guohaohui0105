/*输入10个数，分别统计其中正数、负数、零的个数。*/
#include <stdio.h>

#define N 10

int main()
{
	int i, a , b, n;
	a = b = n = 0;
	int arr[N];
	
	printf("请输入10个整数：\n");

	for(i = 0; i < N; i++)
	{
		scanf("%d", arr+i); // &arr[i]
	}
	for(i = 0; i < N; i++)
	{
		if(arr[i] == 0)
			n++;
		if(arr[i] > 0)
			a++;
		if(arr[i] < 0)
			b++;
	}
	printf("正数%d个 负数%d个 零%d个\n", a, b, n);
	
	return 0;
}

