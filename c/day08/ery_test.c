#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverseString(const char *p);

int main()
{
    char *guo = "guo HAO hui";

    char *ret1 = reverseString(guo);

    puts(ret1);

    free(ret1);
    ret1 = NULL;

    return 0;
}

char *reverseString(const char *p)
{
    char *ret = NULL;
    int i;
    size_t size;
    size = strlen(p)+1;

    ret = calloc(size, sizeof(char));
    if(ret == NULL)
    {
        exit(1);
    }

    for(i = 0; i < size; i++)
    {
        if(p[i] >= 'a' && p[i] <= 'z')
        {
            ret[i] = p[i] - 32;
        }
        else if(p[i] >= 'A' && p[i] <= 'Z')
        {
            ret[i] = p[i] + 32;
        }
        else
        {
            ret[i] = p[i];
        }
    }

    return ret;

}