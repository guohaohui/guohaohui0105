#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*cmp_t)(const void *data1, const void *data2);

void myqsort(void *arr, int low, int high, int size, cmp_t cmp);

int char_cmp(const void *data1, const void *data2)
{
    const char *d1 = data1;
    const char *d2 = data2;
    return *d1 - *d2;
}

int str_cmp(const void *data1, const void *data2)
{
    char *const*d1 = data1;
    char *const*d2 = data2;
    return strcmp(*d1,*d2);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;
    myqsort(argv[1], 0, strlen(argv[1])-1, sizeof(char), char_cmp);
    puts(argv[1]);

    myqsort(argv,0,argc-1,sizeof(char *),str_cmp);
    for(int i = 0; i<argc;i++)
    {
        puts(argv[i]);
    }

    return 0;
}

static void swap(void *arr, int low, int high, int size)
{
    char *tmp = malloc(size);
    // if (tmp == NULL)
    //     return;
    memcpy(tmp, (char *)arr + low * size, size);
    memcpy((char *)arr + low * size, (char *)arr + high * size, size);
    memcpy((char *)arr + high * size, tmp, size);
    free(tmp);
}

int partition(void *arr, int low, int high, int size, cmp_t cmp)
{
    char *tmp = malloc(size);
    // if (tmp == NULL)
    //     return 0;
    memcpy(tmp, (char *)arr + low * size, size);

    while (low < high)
    {
        while (cmp((char *)arr + high * size, tmp) >= 0 && low < high)
        {
            high--;
        }
        if (low < high)
        {
            swap(arr, low, high, size);
        }
        while (cmp((char *)arr + low * size, tmp) <= 0 && low < high)
        {
            low++;
        }
        if (low >= high)
        {
            break;
        }
        swap(arr, low, high, size);
    }
    free(tmp);
    return low;
}

void myqsort(void *arr, int low, int high, int size, cmp_t cmp)
{
    int base;
    if (low >= high)
        return;
    base = partition(arr, low, high, size, cmp);
    myqsort(arr, low, base - 1, size, cmp);
    myqsort(arr, base + 1, high, size, cmp);
}