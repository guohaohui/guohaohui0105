#include <stdio.h>

int find(char *arr);

int main()
{
    char arr[100] = "guo hao hui";
    int n;
    find(arr);     
    return 0;
}

int find(char *arr)
{
    int i;
    char n[1] = {};
    printf("请输入一个字符:");
    scanf("%c", &n[0]);
    for(i = 0; arr[i]; i++)
    {
        if(n[0] == arr[i])
        {
            printf("和第%d个元素%c相等\n",i,arr[i]);
        }
    }
    if(arr[i] == '\0')
        printf("没有相等的\n");
    return 0;

}
