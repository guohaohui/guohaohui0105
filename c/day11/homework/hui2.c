#include<stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    return 0;
}

int myatoi(const char *p)
{
    int ret = 1;
    int res = 0;

    if(p == NULL)
        return 0;
    if(*p == '-')
    {
        ret = -1;
        p++;
    }
    
}