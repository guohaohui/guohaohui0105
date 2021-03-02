//2.现要完成功能,返回指定出现c的位置的指针，返回的地址是
//被查找字符串指针开始的第一个与c相同字符的指针，如果s中不存在c则返回NULL。
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *str_func(const char *s, int c);

int main()
{
    char p[] = "guohaohui";
    char *q = str_func(p,'a');
    puts(q);
    free(q);
    return 0;
}

char *str_func(const char *s, int c)
{
    char *p = NULL;
    int len;
    int i;
    for(i = 0; i < strlen(s); i++)
    {
        if(c == s[i])
        {
            len = i;
            break;
        }
    }
    if(i == strlen(s))
        return NULL;
    p = (char *)calloc(strlen(s)-len+1,sizeof(char));
    memcpy(p,s+len,strlen(s)-len+1);
    return p;
}
