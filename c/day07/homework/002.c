/*
2、有一个字符串”1a2b3d4z”,；
要求写一个函数实现如下功能，
功能1：把偶数位字符挑选出来，组成一个字符串1。
功能2：把奇数位字符挑选出来，组成一个字符串2，
功能3：把字符串1和字符串2拼接组成一个新的字符串，返回。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *merge(char *arr, char *arr1, char *arr2);

int main()
{
    char arr[10] = "1a2b3d4z";
    char arr1[10] = {};
    char arr2[10] = {};   
    puts(merge(arr,arr1,arr2));
    return 0;
}
char *merge(char *arr, char *arr1, char *arr2)
{
    int i,j = 0;
    for(i = 0; arr[i]; i=i+2)
    {
        arr1[j] = arr[i];
        j++;
    }
    arr1[j] = '\0';
    j = 0;
    for(i = 1; arr[i]; i=i+2)
    {
        arr2[j] = arr[i];
        j++;
    }
    arr2[j] = '\0';  
    return strcat(arr1,arr2);
}

