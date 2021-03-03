#include <stdio.h>

#include "list.h"

static int intCmp(const void *data, const void *key)
{
    const int *d = data;
    const int *k = key;
    return *d - *k;
}

static void showInt(const void *data)
{
    const int *d = data;
    printf("%d ", *d);
}

int main(void)
{
    int arr[] = {3,1,6,7,8,9,4};
    listhead_t *head;

    listheadInit(sizeof(int), &head);
    for(int i = 0; i < sizeof(arr)/sizeof(*arr); i++)
    {
        listInsert(head,arr+i, HEADINSERT);//插入
    }

    listTraval(head, showInt);
    printf("\n");
    printf("Delete %d\n", *(arr+2));
    listDelete(head, arr+2, intCmp);//删除

    listTraval(head, showInt);//遍历
    printf("\n");

    int a = 20;
    printf("Change %d to %d\n",*(arr + 2), a);
    listUpdate(head, arr+2, intCmp, &a); //修改
    listTraval(head, showInt);//遍历
    printf("\n");

    listDestroy(head);//销毁
    return 0;
}