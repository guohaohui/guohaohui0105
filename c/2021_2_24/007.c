//1.	已知有声明void swap(int a,int b);现想要交换参数a b的值，请把知道的方法尽可能的写出
#include <stdio.h>

#define swap(a,b)\
a = a + b;\
b = a - b;\
a = a - b;

int main()
{
    int a = 5, b = 10;

    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("%d %d\n",a,b);
    swap(a,b)
    printf("%d %d\n",a,b);
    return 0;
}

