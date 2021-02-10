#include<stdio.h>

int main()
{
    char *arr[4] = {"guo", "hao", "hui", "guohaohui"};

    for(int i = 0; i < 4; i++)
    {
        printf("%s\n", arr[i]);
        printf("%p\n", arr[i]);
        puts(arr[i]);
    }

    return 0;
}