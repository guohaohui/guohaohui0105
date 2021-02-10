#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
/*先随机产生N个三位自然数输出
  ，然后再输出其中同时是3、5、7倍数的数。（设N为100）*/

#define  N 100

int main()
{
	int arr[N];
	int i;

	srand(getpid());

	for(i = 0; i < N; i++)
	{
		arr[i] = rand() % (999 - 100) + 100;//产生100～999的随机数

		if(arr[i] % 3 == 0 && arr[i] % 5 == 0 && arr[i] % 7 == 0)
			printf("%d \n", arr[i]);
	}

	return 0;

}


