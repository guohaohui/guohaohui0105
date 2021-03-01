#include <stdio.h>

union test_un
{
    int a;
    char b;
};


int main()
{
    union test_un t;
    //小端存储：低字节存低地址，高字节存高地址
    //大端存储：低字节存高地址，高字节存低地址
    t.a = 0x12345678;

    printf("%#x\n", t.b);

    int a = 0x12345678;
    char *p = (char *)&a;
    printf("%#x\n",*p);
    return 0;
}