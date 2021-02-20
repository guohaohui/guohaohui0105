#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char **getnString(int n);
int mygetline(char **ptr);
char *getLongString(int n, char **p);
int main()
{
    char **ret;
    int n;
    ret = getnString(5);
    for(n = 0; ret[n]; n++)
        ;
    printf("%s\n",getLongString(n,ret));

    for(int i = 0; i < n; i++)
        free(ret[n]);
    free(ret);
    return 0;
}

int mygetline(char **ptr)
{
    int ch;
    int size = 0;
    *ptr = NULL;
    while (1)
    {
        *ptr = realloc(*ptr, (size + 1) * sizeof(char));
        ch = getchar();
        if (ch == '\n')
        {
            //存'\0'
            (*ptr)[size] = '\0';
            break;
        }
        (*ptr)[size] = ch;
        size++;
    }
    return size;
}

//用户决定输入多少字节
char **getnString(int n)
{
    char **p;

    p = calloc(n + 1, sizeof(char *));
    if (p == NULL)
        return NULL;
    for (int i = 0; i < n; i++)
    {
        mygetline(p + i);
    }
    return p;
}

//最长

char *getLongString(int n, char **p)
{
    int len;
    int j = 0;

    len = strlen(p[0]);

    for (int i = 1; i < n; i++)
    {
        if (strlen(p[i]) > len)
        {
            len = strlen(p[i]);
            j = i;
        }
    }
    return p[j];
}