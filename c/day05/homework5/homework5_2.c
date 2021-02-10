/*从终端（键盘）将5个整数输入到数组a中，
  然后将a逆序复制到数组b中，并输出b中各元素的值。*/
#include<stdio.h>

#define N 5

int main()
{
	int arr[N] = {};
	int brr[N] = {};
	int j = 0;
	printf("请输入五个整形：\n");
		
	for(int i = 0; i < N; i++)
	{
		scanf("%d", arr+i); // &arr[i]
	}
	for(int i = N - 1; i >= 0; i--)
	{
		brr[i] = arr[j];
		j++;
	}
	for(j = 0; j < N; j++)
	{
		printf("%d ", brr[j]);
	}
	printf("\n");

	return 0;
}


