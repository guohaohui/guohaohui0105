#include <stdio.h>

int main()
{
    int arr[2][3] = {{1,2,3},{4,5,6}};
    int arr1[2] = {1,2};
    printf("%p\n", *arr + 4);//第五个元素的地址
    //printf("%ls\n", *arr + 4);
    printf("%d\n", *(*arr + 4));//第五个元素的值
    printf("%p\n", arr[1] + 1); //第五个元素的地址
    printf("%d\n", arr[1][1]);//第五个元素的值
    printf("%p\n", &arr1[0]);//arr1[0]的地址
    printf("%p\n", *arr+1);//第2个元素的地址
    printf("%p\n", arr1);//arr1的地址
    printf("%d\n", *arr1);//arr1的首地址
    return 0;
}
