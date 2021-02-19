
//错误程序！！！！！！！！！！！！！！！！！！！！！！！

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char **sep_str(const char *p, char ch);
int main()
{
    char *p = "hello  world after  noon ";
    char **tmp = sep_str(p,' ');
    for(int i = 0; i < strlen(*tmp); i++)
        puts(tmp[i]);
    return 0;
}

char **sep_str(const char *p, char ch)
{
    char **tmp;
    int i = strlen(p);
    int j, k, m = 0,n=0,d = 0;;
    for (j = 0; j < i; j++)
    {
        if (p[j] == ch)
        {
            k = j;
            m++;
            for (k; k < i; k++)
            {
                if (p[k] != ch)
                {
                    j = k;
                    break;
                }
            }
        }
    }
    tmp = calloc(m + 1, sizeof(char *));
    for (j = 0; j < i; j++)
    {
        m = 0;
        while (p[j] != ch)
        {
            m++;
            j++;
            k = j;
        }
        for (k; k < i; k++)
        {
            if (p[k] != ch)
            {
                j = k;
                break;
            }
        }
        tmp[n] = malloc((m+1)*sizeof(char));
        strcpy(tmp[n],&p[d]);
        d= j;
        n++;
    }

    return tmp;
}