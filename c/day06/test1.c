``#include<stdio.h>

int MaxAddr(int *p, int n);

int main()
{
	int arr[] = {1,2,3,4,8,9,6,3,5};

	printf("%d\n",MaxAddr(arr, sizeof(arr) / sizeof(arr[0])));

	return 0;
}
// 返回给定的整型数组中所有元素的最大值

int MaxAddr(int *p, int n)   // 数组的首地址是 int* 类型的 定义一个int* 的变量来接受它
{							// int n 数组成员个数
	int i;
	int max;
	max = p[0];           // [] 是个运算符

	for(i = 1; i < n; i++)
	{
		if(max < *(p+i))  //  *(p+i) == p[i]
			max = p[i];
	}

	return max;
}
