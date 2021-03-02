//按下列声明实现strncpy的函数功能
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *func(char *dest, const char *src, size_t n);
int main()
{
    char a[20];
    char arr[] = "guohaohui";
    func(a,arr,6);
    puts(a);

    return 0;
}

char *func(char *dest, const char *src, size_t n)
{
    if(dest != NULL && src != NULL)
    {
        char *res = dest;
        int len = 0;
        if(strlen(src) < n)
        {
            len = n - strlen(src);
            n = strlen(src);
        }
        while(n--)
        {
            *dest++ = *src++;
        }
        while(len--)
        {
            *dest++ = '\0';
        }
        return res;
    }
    else
    {
        return NULL;
    }

}



