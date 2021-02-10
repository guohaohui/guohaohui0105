#include <stdio.h>

int main()
{
    int arr[2][3] = {{1,2,3},{4,5,6}};
    int arr1[2] = {1,2};
    printf("%p\n", *arr + 4);
    //printf("%ls\n", *arr + 4);
    printf("%d\n", *(*arr + 4));
    printf("%p\n", arr[1] + 1);
    printf("%d\n", arr[1][1]);
    printf("%p\n", &arr1[0]);
    printf("%p\n", *arr+1);
    printf("%p\n", arr1);
    printf("%d\n", *arr1);
    return 0;
}