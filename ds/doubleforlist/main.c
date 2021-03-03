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
    listInit(sizeof(int), &s);
    for(int i = 0; i < sizeof(arr)/sizeof(*arr); i++)
    {
        listadd(s,arr+i,cmpIint,TALT);
    }
	printf("\n");
    listprintf(s,pri);
}
