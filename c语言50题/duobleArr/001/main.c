#include <stdio.h>
#include <stdlib.h>
/*行列互换
1 2 3
4 5 6

1 4
2 5
3 6
*/
#define N 3
#define M 2
int main()
{
    int arr[M][N] = {{1, 2, 3}, {4, 5, 6}};
    int arr1[N][M];

    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            arr1[j][i] = arr[i][j];
        }
    }
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d \n",arr1[i][j]);
        }
    }

    exit(0);
}