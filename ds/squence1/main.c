#include <stdio.h>
#include "seqlist.h"

static void showInt(const void *data)
{
    const int *d = data;
    printf("%d ", *d);
}

static int findInt(const void *data, const void *key)
{
    const int *d1 = data;
    const int *d2 = key;

    return *d1 - *d2;
}


int main()
{
    
    seqlist_t *mylist;
    void *p;
    int n;
    mylist = seqlistInit(sizeof(int));   //初始化
    for(int i = 1; i <= 20 ; i+=2) 
    {
        seqlistInsert(mylist, &i);  //插入
    }

    seqlistTraval(mylist,showInt);//遍历

    printf("\n");
    int t = 11;
    p = seqlistFind(mylist, &t, findInt);//查找
    if(p == NULL)
        printf("There is no %d element.\n", t);
    else
        printf("%d\n", *(int *)p);

    n = seqlistDelete(mylist, &t, findInt);//删除
    if(n == 0)
        printf("Delete the success.\n");
    else
        printf("Delete failed. There is no %d element.\n",t);
    seqlistTraval(mylist,showInt);//遍历
    printf("\n");
    int b = 15;
    int c = 99;
    n = seqlistUpdate(mylist, &b, findInt, &c); //替换
    if(n == 0)
        printf("Modify the success\n");
    else
        printf("Modification failed. There is no %d element in array\n", b);
    seqlistTraval(mylist,showInt); //遍历
    printf("\n");
    seqlistDestroy(mylist); // 销毁
    return 0;
}