#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **sep_str(const char *p, char ch);

int main(int argc, char *argv[])
{
    char **ret;
    if (argc < 3)
        return 1;
    ret = sep_str(argv[1], *argv[2]);
    for (int i = 0; ret[i]; i++)
    {
        printf("%s\n",ret[i]);
    }

    return 0;
}

char **sep_str(const char *p, char ch)
{
    char *tmp;
    char **ret;
    int size = 1;
    ret = calloc(size, sizeof(char *));
    if (ret == NULL)
        return NULL;
    tmp = malloc(strlen(p) + 1);
    if (tmp == NULL)
        return NULL;
    strcpy(tmp, p);

    p = tmp;

    while (*tmp)
    {
        if (*tmp != ch)
        {
            tmp++;
        }
        else
        {
            *tmp = '\0';
            if (p == tmp)
            {
                p++;
                tmp++;
            }
            else
            {
                ret = realloc(ret, (size + 1) * sizeof(char *));
                ret[size - 1] = malloc(strlen(p));
                strcpy(ret[size - 1], p);
                size++;
                tmp++;
                p = tmp;
            }
        }
    }
    return ret;
}