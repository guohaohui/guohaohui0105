#include<stdio.h>

#define N 10

int main()
{
	int i,j;
	int n, n1;
	int arr[N];
	printf("请输入学生初始分数：");
	for(i = 0; i < N; i++)
	{
		 scanf("%d", &n);
		 arr[i] = n;
	}
	printf("\n");

	printf("请输入题数：");
	scanf("%d",&n);

	for(i = 0; i < n; i++)
	{

		for(j = 0; j < N; j++)
		{
			 printf("%d  ", arr[j]);
		}

		printf("题书：%d\n",n);

		for(j = 0; j < N; j++)
		{
			printf("%d\n", j);
		}
		printf("请输入得分同学：");
LOOP:
		scanf("%d", &n1);
		if(n1 < 0||n1 > 9)
		{
			printf("请重新输入编号：");
			goto LOOP;
		}
		arr[n1] += 10;
	}
	printf("\n");
	for(i = 0; i < N; i++)
	{
		printf("%d  ",arr[i]);
	}

	printf("\n");

	return 0;
}








