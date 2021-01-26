/*5、数学中有个杨辉三角的概念，打印杨辉三角的前10行*/
#include <stdio.h>

#define N 10

int main()
{
    int i,j;
    int arr[N][N];

    for(i = 0; i < N; i++)
    {   
        for(j = N-1; j >= 0; j--)
        {
            arr[i][j] = 1;
        }
    }

    for(i = 2; i < N; i++)
    {
        for(j = 0; j < i-1; j++)
        {
            arr[i][j+1] = arr[i-1][j]+arr[i-1][j+1];
        }
    }
    
    for(i = 0; i < N; i++)
    {
        for(j = N-i; j > 0; j--)
        {
            printf("  ");
        }
        for(j = 0; j <= i; j++)
        {
            printf("%-4d", arr[i][j]);
        }
        printf("\n");

    }
	return 0;
}
