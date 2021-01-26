#include <stdio.h>

#define N 10

int main()
{
    int arr[N] = {0,1,2,3,4,5,6,7,8,9};
    int arr1[N] = {0,1,2,3,4,5,6,7,8,9};
    int i,n;
    int num = 0;

    printf("请输入一个0~9之间的数：");

    // LOOP:
    //     scanf("%d", &n);
    //     if(n < 0 || n > 9)
    //     {
    //         printf("必须是0~9的数！！\n");
    //         printf("请重新输入：");
    //         goto LOOP;
    //     }
    // do
    // {
    //     scanf("%d", &n);

    // } while (n < 0 || n > 9);
    
    while(1)
    {
        scanf("%d", &n);
        if(n < 0 || n > 9)
        {
          printf("必须是0~9的数！！\n");
          printf("请重新输入："); 
          continue; 
        }
        break;
    }




    for(i = 1; i <= n; i++)
    {
        num += arr[i];
        arr[i+1] = arr[i]*10+arr[i+1];
    }

    printf("%d\n", num);
    return 0;
}