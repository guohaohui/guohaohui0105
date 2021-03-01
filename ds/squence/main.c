#include <stdio.h>
#include "seqlist.h"

static void showInt(const void *data)
{
    const int *d = data;
    printf("%d\n", *d);
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

    mylist = seqlistInit(sizeof(int));   //初始化
    for(int i = 1; i <= 20 ; i+=2) 
    {
        seqlistInsert(mylist, &i);  //插入
    }

    seqlistTraval(mylist,showInt);

    printf("\n");
    int t = 11;
    printf("%d\n", *(int *)(seqlistFind(mylist, &t, findInt)));

    return 0;
}