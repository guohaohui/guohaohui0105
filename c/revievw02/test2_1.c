#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **gernString(int n);
char *getLongString(char **p, int n);
int main()
{
    char **ret;
    int n ;
    ret = gernString(5);
    for(n = 0; ret[n]; n++)
        ;
    printf("最长的:%s",getLongString(ret,n));
    return 0;
}

//存入一个字符串

int mygerline(char **p)
{
    int ch;
    int size = 0;
    *p = NULL;

    while(1)
    {
        *p = realloc(*p,(size+1)*sizeof(char));//开辟内存空间
        ch = getchar();//把终端输入的字符赋给ch
        if(ch == '\n') // 如果ch='\n'跳出循环，
        {
            (*p)[size]= '\0';//把'\0'赋值给(*p)[size] ==> (*p + size)
            break;
        }
        (*p)[size] = ch; //把读入的字符赋值给(*p)[size]
        size++;
    }
    return size;
}
//用户确定要输入多少给字符串
char **gernString(int n)
{
    char **p;
    p = calloc(n+1,sizeof(char *));//开辟n+1个成员的内存空间，每个成员占char*个字节用来存储每个成员的首地址。
    if(p == NULL)
        return NULL;
    
    for(int i = 0; i < n; i++)
    {
        mygerline(p+i);
    }
    return p;
}

//最长的那个字符串
char *getLongString(char **p, int n)
{
    int j = 0;
    int len;
    len = strlen(p[0]);
    for(int i = 1; i < n; i++)
    {
        if(len < strlen(p[i]))
        {
            j = i;
            len = strlen(p[i]);
        }
    }
    return p[j];
}

