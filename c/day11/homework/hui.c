#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*cmp_t)(const void *data1, const void *data2);
int guo(void *arr, int number, int size, cmp_t cmp);

static int int_cmp(const void *data1, const void *data2)
{
    const int *d1 = data1;
    const int *d2 = data2;

    return *d1 - *d2;
}

int main(void)
{
    int max, min;
    int arr[9] = {5, 1, 8, 7, 3, 9, 4, 2, 6};
    max = guo(arr, 9, sizeof(int), int_cmp);
    printf("max = %d\n", arr[max]);

    return 0;
}

int guo(void *arr, int number, int size, cmp_t cmp)
{
    char *tmp = malloc(size);
    int i, j = 0;
    memcpy(tmp, arr, size);
    for (i = 0; i < number; i++)
    {
        if (cmp(tmp, (char *)arr + i * size) < 0)
        {
            memcpy(tmp, (char *)arr + i * size, size);
            j = i;
        }
    }
    free(tmp);
    return j;
}