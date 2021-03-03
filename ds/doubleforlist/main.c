#include <stdio.h>
#include "list.h"
static int cmpIint(const void *data, const void *key)
{
    const int *d = data;
    const int *k = key;
    return *d - *k;
}
static void pri(const void *data)
{
    const int *d = data;
    printf("%d ", *d);
}
int main()
{
    int arr[] = {3,6,1,2,9,7};

    listhead_t *s;
    
    listInit(sizeof(int), &s); //   初始化
    
    for(int i = 0; i < sizeof(arr)/sizeof(*arr); i++)
    {
        listadd(s,arr+i,TALT); //   添加
    }
    listprintf(s,pri); //   遍历
    printf("\n");
    printf("Delete %d\n",*(arr+1));
    listDelete(s,arr+1,cmpIint);//  删除
    listprintf(s,pri); //   遍历
    printf("\n");

    printf("Delete the %d\n",*(int *)listFetch(s,arr+3,cmpIint)); //把删除后的书打印出来
    listprintf(s,pri); //   遍历
    printf("\n");
    if(listIsEmpty(s) == 0) //判断是否为空链表
        printf("It's an empty linked list !\n");
    else
        printf("It's not an empty linked list !\n");
    listDestroy(s);// 销毁
    return 0;
}
