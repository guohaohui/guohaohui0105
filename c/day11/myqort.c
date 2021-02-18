#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*cmp_t)(const void *daty1, const void *daty2);

void myqsort(void *arr,int low,int high, int size,cmp_t p);
void show(void *arr, int len, int size);



static int intcmp(const void *data1, const void *data2)
{
    const int *d1 = data1;
    const int *d2 = data2;

    return *d2 - *d1;
}

static int floatcmp(const void *data1, const void *data2)
{
    const float *d1 = data1;
    const float *d2 = data2;

    return *d1 - *d2;
}

static int charcmp(const void *data1, const void *data2)
{
    const char *d1 = data1;
    const char *d2 = data2;

    return *d2 - *d1;
}

static int str_cmp(const void *data1, const void *data2)
{
    char *const*d1 = data1;
    char *const*d2 = data2;

    return strcmp(*d1,*d2);
}

int main(int argc, char *argv[])
{
    int len = 9;
    int i;

    int arr[9] = {5,1,8,7,3,9,4,2,6};
    float arr1[9] = {2.0,2.5,4.3,9.2,8.1,9.9,1.2,3.0,6.6};
    char arr2[9] = "guohaohui";
    char *arr3[3] = {"guo","aao","hui"};
    int low = 0, high = len-1;
    myqsort(arr,low,high,sizeof(int),intcmp);
    show(arr, len, sizeof(int));
    printf("\n");
    myqsort(arr1,low,high,sizeof(float),intcmp);
    for(i = 0; i < len; i++)
    {
        printf("%f ",arr1[i]);
    }
    printf("\n");
    myqsort(arr2,low,high,sizeof(char),charcmp);
    puts(arr2);
    myqsort(arr3,low,2,sizeof(char *),str_cmp);
    for(i = 0; i<3; i++)
        puts(arr3[i]);
    return 0;
}
void show(void *arr, int len, int size)
{

    for(int i = 0; i < len; i++)
    {
        printf("%d ",*((char*)arr + i*size));
    }
}

void jiaoHuan(char *arr, int low, int high, int size)
{
    char *tmp;
    tmp = malloc(size);
    if(tmp == NULL)
    {
        return ;
    }
    // *temp= *(arr + low * size);
    // *(arr + low * size) = *(arr + high * size);
    // *(arr + high * size) = *temp;
    memcpy(tmp, (char *)arr + low * size, size);
    memcpy((char *)arr + low * size, (char *)arr + high * size, size);
    memcpy((char *)arr + high * size, tmp, size);
    free(tmp);
    
}

int kuaiPai(void *arr, int low, int high, int size, cmp_t p)
{   
    char *arr1 = arr;
    char *tmp = malloc(size);
    // if (tmp == NULL)
    //     return 0;
    memcpy(tmp, (char *)arr + low * size, size);
    //int k = *(arr1 + low * size);
    while(low < high)
    {
        while(p(arr1 + high*size,tmp) >= 0 && low < high)
        {
            high--;
        }
        if(low < high)
        {
            jiaoHuan(arr1,low,high,size);
        }
        while(p(arr1 + low*size,tmp) <=0 && low < high)
        {
            low++;
        }
        if(low >= high)
        {
            break;
        }
        jiaoHuan(arr1,low,high,size);
    }
    //*(arr1 + low * size) = k;
    free(tmp);
    return low;
}

void myqsort(void *arr,int low,int high, int size, cmp_t p)
{
    int sort;
    if(low >= high)
        return ;

    sort = kuaiPai(arr,low,high,size,p);

    myqsort(arr,low,sort-1,size, p);
    myqsort(arr,sort+1,high,size, p);

}

