#include <stdio.h>

int main(void)
{
    char str[] = "guo hao hui";

    char *p = str;

    printf("%ld\n", sizeof(p));//查看指针p占字节大小
    printf("%p\n", p); //查看指针p的地址
    printf("%p\n", p+1);//查看指针p+1的地址

    while(*p)
    {
        printf("%c", *p++);
    }
    printf("\n");
    return 0;
}
