#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*cmp_t)(const void *data1, const void *data2);
void toCompare(void *arr, int number, int size, cmp_t cmp, void *);
static int int_cmp(const void *data1, const void *data2)
{
    const int *d1 = data1;
    const int *d2 = data2;

    return *d1 - *d2;
}

static int double_cmp(const void *data1, const void *data2)
{
    const double *d1 = data1;
    const double *d2 = data2;

    return *d1 - *d2;
}

static int char_cmp(const void *data1, const void *data2)
{
    const char *d1 = data1;
    const char *d2 = data2;

    return *d1 - *d2;
}

static int str_cmp(const void *data1, const void *data2)
{
    char *const*d1 = data1;
    char *const*d2 = data2;

    return strcmp(*d1,*d2);
}


int main()
{
    int arr[9] = {5, 1, 8, 7, 3, 9, 4, 2, 6};
    float arr1[9] = {2.0,2.5,4.3,9.2,8.1,9.9,1.2,3.0,6.6};
    char arr2[9] = "325415668";
    char *arr3[3] = {"guo","aao","hui"};
    char max, min;
    float max1;
    char *max2;
    toCompare(arr, 9, sizeof(int), int_cmp, &max);
    printf("max = %d \n", max);
    toCompare(arr2, 9, sizeof(char), char_cmp, &max);
    printf("max = %c \n", max);
    toCompare(arr1, 9, sizeof(double), double_cmp, &max1);
    printf("max = %f \n", max1);
    toCompare(arr, 3, sizeof(char *), str_cmp, &max);
    printf("max = %s \n", arr3[max]);
    return 0;
}

void swap(void *arr, int number, int size)
{
    char *tmp = malloc(size);
    if (tmp == NULL)
        return;
    memcpy(tmp, (char *)arr + (number - 1) * size, size);
    memcpy((char *)arr + (number - 1) * size, (char *)arr + number * size, size);
    memcpy((char *)arr + number * size, tmp, size);
    free(tmp);
}

void toCompare(void *arr, int number, int size, cmp_t cmp, void *max)
{
    char *max2 ;
    //char *min2 = malloc(size);
    max2 = max;
    //min2 = min;
    char *max1 ;
    if (max1 == NULL)
        return;
    // char *min1 = malloc(size);
    // if (min1 == NULL)
    //     return;
    //*max1 = *min1 = *(char *)arr ;
    char *tmp = malloc(size);
            if (tmp == NULL)
                return;
    for (int i = 0; i < number; i++)
    {
        if (cmp((char *)arr, (char *)arr + i * size) <= 0)
        {  
             memcpy((char*)arr, (char *)arr + (i) * size, size);
            // memcpy((char *)arr + (i) * size, (char *)arr + (i + 1) * size, size);
            // memcpy((char *)arr + (i + 1) * size, tmp, size);
            
        }
    }
    max1 = (char *)arr  ;
    free(tmp);
    // for (int i = number-1; i > 0; i--)
    // {
    //     if (cmp((char *)arr, (char *)arr + i * size) > 0)
    //     {
    //         char *tmp1 = malloc(size);
    //         if (tmp1 == NULL)
    //             return;
    //         memcpy(tmp1, (char *)arr + (number - 1) * size, size);
    //         memcpy((char *)arr + (number - 1) * size, (char *)arr + number * size, size);
    //         memcpy((char *)arr + number * size, tmp1, size);
    //         min1 = (char *)arr + i * size;
            
    //         free(tmp1);
    //     }
    // }
    
    *max2 = *max1;
    //*min2 = *min1;
    
}
