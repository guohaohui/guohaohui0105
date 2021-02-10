#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define N 128

int main()
{
	int n, n1;
	int i, j, k=0;
	int num;
	int num1 = 0;
	scanf("%d", &n);

	int arr[n];
	n1 = n*n;
	int arr1[N]={};
	srand(getpid());
	for(i = 0; i < n; i++)
	{
		arr[i] = rand() % (9 - 1) + 1;
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n ; j++)
		{
			if(i == n-1 && j == n-1)
				break;
			if(j == i)
				j++;		
			num =  arr[i] * 10 + arr[j];
			arr1[k] = num;
			k++;
			printf("%d ", num);
		}
	}
	printf("\n");
	for(i = 0; i < N; i++)
	{
		for(j = i+1; j < N; j++)
		{
			if(arr1[i]==arr1[j])
				arr1[j] = 0;
		}
	}
	for(i = 0; i < N; i++)
	{
		if(arr1[i] != 0)
		{
			printf("%d ", arr1[i]);
			num1 += arr1[i];

		}
	}
	printf("\n");
	printf("%d\n", num1);
}













