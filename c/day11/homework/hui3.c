#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char **save_cmdline(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    char **tem;

    tem = save_cmdline(argc, argv);
    for(int i = 0; i < argc; i++)
    {
        puts(tem[i]);
        //printf("%s",tem[i]);
    }
    for(int i = 0; tem[i]; i++)
    {
        free(tem[i]);
    }
    free(tem);
    return 0;
}


char **save_cmdline(int argc, char *argv[])
{
    char **p;
    p = calloc(argc+1,sizeof(char *));
    if(p == NULL)
        return NULL;
    for(int i = 0; i < argc; i++)
    {
        p[i] = malloc(strlen(argv[i]+1));
        strcpy(p[i],argv[i]);
    }
    return p;
}