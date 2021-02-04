#include <stdio.h>

int main(void)
{
    char str[] = "guo hao hui";

    char *p = str;

    printf("%ld\n", sizeof(p));
    printf("%p\n", p);
    printf("%p\n", p+1);

    while(*p)
    {
        printf("%c", *p++);
    }
    printf("\n");
    return 0;
}