#include <stdio.h>
#include "seqlist.h"

void showInt(const void *data)
{
    const int *d = data;
    printf("%d\n", *d);
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


    return 0;
}