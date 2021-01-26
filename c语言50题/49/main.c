#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

int main()
{
    int n, m = 0;

    int arr[10];
    int arr1[10];
    srand(getpid());

    for(int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 100;
        arr1[i] = rand() % 100;
    }

    for(int i = 0; i < 10; i++)
    {   
        printf("%d*%d =", arr[i], arr1[i]);
        scanf("%d", &n);
        if(arr[i] * arr1[i] == n)
        {
            printf("正确\n");
            m += 10;
        }
        else
        {
            printf("错误\n");
        }
    }
    printf("得分:%d\n", m);
    return 0;
}
