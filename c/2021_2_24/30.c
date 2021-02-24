#include <stdio.h>
#include <string.h>
char * str_cpy(char * strDest,const char * strSrc);
int main()
{
    char arr[] = "guohaohui";
    char d[] = "";
    str_cpy(d,arr);
    puts(d);

    return 0;
}

char * str_cpy(char * strDest,const char * strSrc)
{
    int len = strlen(strSrc);
    for(int i = 0; i < len; i++)
        strDest[i] = strSrc[i];
    strDest[len] = '\0';
    return strDest;
}
