#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static int mpyint(const void *a, const void *b);
static int mpychar(const void *a, const void *b);
static int mpystring(const void *a, const void *b);
void sortarr(void *arr, int number, int size, int (*cmp)(const void *a, const void *b));

int main()
{
    int arr[] = {3,8,9,1,5};
    char arr1[] = "guo hao hui";
    char *str[] = {"guo","hao","hui"};
    sortarr(arr, sizeof(arr)/sizeof(*arr), sizeof(int), mpyint);
    sortarr(arr1, strlen(arr1), sizeof(char), mpychar);
    sortarr(str,sizeof(str)/sizeof(*str),sizeof(char *),mpystring);
    for(int i = 0; i < sizeof(arr)/sizeof(*arr);i++)
        printf("%d ", arr[i]);
    printf("\n");
    puts(arr1);

    for(int i = 0; i < sizeof(str)/sizeof(*str);i++)
    {
        puts(str[i]);
    }

    return 0;
}

static int mpyint(const void *a, const void *b)
{
    const int *a1 = a;
    const int *a2 = b;

    return *a1 - *a2;
}

static int mpychar(const void *a, const void *b)
{
    const char *c1 = a;
    const char *c2 = b;
    
    return *c1 - *c2;
}

static int mpystring(const void *a, const void *b)
{
    char *const*s1 = a;
    char *const*s2 = b;

    return strcmp(*s1 , *s2);
}

void sortarr(void *arr, int number, int size, int (*cmp)(const void *a, const void *b))
{       
    char *temp = malloc(size);
    int i,j;
    for(i = 0; i < number; i++)
    {
        for(j = 0; j < number - i -1; j++ )
        {
            if(cmp((char*)arr + size*j, (char*)arr + size*(j+1)) < 0)
            {
                memcpy(temp,(char*)arr + size*j,size);
                memcpy((char*)arr + size*j,(char*)arr + size*(j+1),size);
                memcpy((char*)arr + size*(j+1),temp,size);
            }
        }
    }
    free(temp);
}










