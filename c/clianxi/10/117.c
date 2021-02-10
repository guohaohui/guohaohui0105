/* 两数中的最大值*/
#include <stdio.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b)) //a>b返回a否则返回b

int main()
{
    printf("%d\n", MAX(10, 2));
}