#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void myqsort(int *arr,int low,int high);
void show(int *arr, int);
int main(int argc, char *argv[])
{
    int len;
    int *a;
    int i;
    if(argc < 2)
    {
        return 0;
    }
    len = strlen(argv[1]);

    a = calloc(len, sizeof(int));

    for(i = 0; argv[1][i];i++)
    {
        a[i] = argv[1][i] - '0';
    }

    int low = 0, high = len-1;
    myqsort(a,low,high);
    show(a, len);
    free(a);
    return 0;
}

void jiaoHuan(int *arr, int low, int high)
{
    int t;
    t = arr[low];
    arr[low] = arr[high];
    arr[high] = t;
}

int kuaiPai(int *arr, int low, int high)
{
    int k = arr[low];
    while(low < high)
    {
        while(arr[high] >= k && low < high)
        {
            high--;
        }
        if(low < high)
        {
            jiaoHuan(arr,low,high);
        }
        while(arr[low] <= k && low < high)
        {
            low++;
        }
        if(low >= high)
        {
            break;
        }
        jiaoHuan(arr,low,high);
    }
    arr[low] = k;
    return low;
}

void myqsort(int *arr,int low,int high)
{
    int sort;
    if(low >= high)
        return ;

    sort = kuaiPai(arr,low,high);

    myqsort(arr,low,sort-1);
    myqsort(arr,sort+1,high);

}

void show(int *arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("%d ",arr[i]);
    }
}