#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(int **p,int *n,int number);
int find(int *p, int n, int number);
int dell(int **p,int *n, int number);
void show(int *a,int n);

int main()
{
    int *arr = NULL;
    int n = 0;
    int ret;

    for(int i = 1; i < 10; i++)
    {
        add(&arr,&n,i);
    }
    show(arr,n);
    ret = find(arr,n,5);
    if(ret == -1)
        printf("没找到\n");
    else
        printf("找到了:%d\n",ret);
    
    dell(&arr,&n,8);
    show(arr,n);
    return 0;
}

void add(int **p,int *n,int number) // 添加 *n 成员个数
{
    *p = realloc(*p, (*n + 1)*sizeof(int));
    if(*p == NULL)
        return;
    (*p)[*n] = number;
    (*n)++;//添加一次自增一次
}

int dell(int **p,int *n, int number)//删除指定元素
{
    int i;
    for(i = 0; i < *n; i++)
    {
        if((*p)[i] == number)
        {
            memcpy(*p + i,*p + i +1,sizeof(int));
            break;
        }
    }
    if(*n == i)
        return -1;
    (*n)--;
    *p = realloc(*p,*n * sizeof(int));
    return 0;
}

int find(int *p, int n, int number)//查找
{
    int i;
    for(i = 0; i < n; i++)
    {
        if(p[i] == number)
        {
            break;
        }
    }
    if(n == i)
    {
        return -1;
    }
    return p[i];
}

void show(int *a,int n)//遍历数组
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}


