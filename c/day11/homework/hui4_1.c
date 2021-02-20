/*
guo  hao hui
ch ' '
输出
guo
hao
hui
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **sep_str(const char *p, char ch);

int main(int argc, char *argv[])
{
    char **ret;
    if (argc < 3) //命令行参数必须大于3
        return 1;
    ret = sep_str(argv[1], *argv[2]);
    for (int i = 0; ret[i]; i++)
    {
        printf("%s\n",ret[i]);
    }

    return 0;
}

char **sep_str(const char *p, char ch)//把一行字符串中的字串保存到堆空间中
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
    strcpy(tmp, p);//把p的内容拷贝到tmp中

    p = tmp;

    while (*tmp)
    {
        if (*tmp != ch)//如果*tmp！=' ' 
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