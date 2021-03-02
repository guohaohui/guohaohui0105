#include <stdio.h>
#include "seqlist.h"

#define N 3


static void showInt(const void *data)
{
    const int *d = data;
    printf("%d ", *d);
}

static void showInt1(const void *data)
{
    const student_t *d = data;
    printf("%-10s  %-5d  %-15s %-6f\n", d->name, d->year, d->phone, d->a);
}


static int findInt1(const void *data, const void *key)
{
    const student_t *d1 = data;
    const int *d2 = key;

    return d1->year - *d2;
}
static int nameCmp(const void *data, const void *key)
{
    const student_t *d1 = data;
    const int *d2 = key;

    return d1->year - *d2;
}

static int findInt(const void *data, const void *key)
{
    const int *d1 = data;
    const int *d2 = key;

    return *d1 - *d2;
}




int main()
{
    student_t s;
    student_t *q;
    seqlist_t *mylist;
    void *p;
    int n;
    mylist = seqlistInit(sizeof(student_t));   //初始化
    for(int i = 1; i <= 20 ; i+=2) 
    {
        snprintf(s.name, NEM, "stu%d", i);
        snprintf(s.phone, NEM, "1234%d67%d90%d", i%10,i%5,i%6);
        s.year = 20+i;
        s.a = 1.33+i;
        seqlistInsert(mylist, &s);  //插入
    }

    seqlistTraval(mylist,showInt1);//遍历

    printf("\n");
    int t = 25;
    q = seqlistFind(mylist, &t, findInt1);//查找
    if(q == NULL)
        printf("There is no %d element.\n", t);
    else
        printf("%s\n", q->name);

    n = seqlistDelete(mylist, &t, findInt1);//删除
    if(n == 0)
    {
        printf("Delete the success.\n");
        seqlistTraval(mylist,showInt1);//遍历
    }
    else
        printf("Delete failed. There is no %d element.\n",t);
    
    printf("\n");
    /*
    int b = 21;
    int c = 99;
    n = seqlistUpdate(mylist, &b, findInt, &c); //替换
    if(n == 0)
    {
        printf("Modify the success\n");
        seqlistTraval(mylist,showInt); //遍历
    }
    else
        printf("Modification failed. There is no %d element in array\n", b);
    
    printf("\n");
    */
    seqlistDestroy(mylist); // 销毁
    return 0;
}

