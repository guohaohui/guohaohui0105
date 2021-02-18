#include <stdio.h>
/*
 指针的作用:
 1. 通过形参改变实参－－－》指针
 */

void swap2num(int *a, int *b);
int maxMinArr(int *arr, int n, int *min);
int main(void)
{
	int num1, num2;
	int arr[] = {3,2,7,6,8,9,4};
	int max, min;

	num1 = 100;
	num2 = 50;

	swap2num(&num1, &num2);

	printf("num1:%d, num2:%d\n", num1, num2);

	max = maxMinArr(arr, sizeof(arr) / sizeof(*arr), &min);
	printf("最大值:%d, 最小值:%d\n", max, min);

	return 0;
}

/*两个整型数的交换*/
void swap2num(int *a, int *b)
{
	int t;	
	
	t = *a; // t = num1
	*a = *b; // num1 = num2
	*b = t; // num2 = t
}

/*
 将给定的数组的最大最小值返回
 参数的回填
 */
int maxMinArr(int *arr, int n, int *min)
{
	int i;		
	int maxn, minn;

	maxn = minn = arr[0];
	for (i = 1; i < n; i++) {
		if (arr[i] > maxn) {
			maxn = arr[i];
		}
		if (arr[i] < minn)
			minn = arr[i];
	}
	
	*min = minn;

	return maxn;
}


