#include <stdio.h>
#include "forlist.h"

static int cmpInt(const void *data, const void *key)
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
    int arr[] = {3,6,4,1,9,8};

    listhead_t *l;

    listInit(sizeof(int), &l);

    for(int i = 0; i< sizeof(arr)/sizeof(*arr); i++)
    {
        listadd(l, arr+i, cmpInt, TAIL);
    }

    listprintf(l,pri);

    return 0;
}