#include <stdio.h>
#include <string.h>

int str_cmp(const char *src, const char *dst);

int main()
{
    char arr[] = "gbohaohui";
    char arr1[] = "gahaohui";
    printf("%d\n",str_cmp(arr,arr1));
    
    return 0;
}

int str_cmp(const char *src, const char *dst)
{
    int i,j;
    for(i = 0; src[i]!= '\0' || dst[i] != '\0';i++)
    {
        if(src[i] != dst[i])
            return src[i] - dst[i];
    }
    return 0;
}
