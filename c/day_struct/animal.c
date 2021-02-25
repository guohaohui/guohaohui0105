/*
 定义一个动物结构体；
    颜色
    名字
    月龄

定义一个接口函数，求出整个结构中年龄最大的动物
 */
#include <stdio.h>

#define NAMESIZE 32

struct animal
{
    char color[NAMESIZE];
    char name[NAMESIZE];
    int year;
};

int MAX(struct animal *arr);
int main()
{
    struct animal arr[5];

    for(int i = 0; i < 5; i++)
    {
        scanf("%s%s%d", arr[i].color, arr[i].name, &arr[i].year);
    }

    MAX(arr);

    return 0;
}

int MAX(struct animal *arr)
{
    int i,j;
    int max = 0;
    for(i = 0; i < 5; i++)
    {
        max = (arr[max].year < arr[i].year) ? i : max; 
    }
    printf("%s %s %d\n",arr[max].color, arr[max].name, arr[max].year);
}