//编程求出所有的水仙花数(水仙花数只是自幂数的一种,严格来说3位数的3次幂数才称为水仙花数.)
#include <stdio.h>

int main()
{
    int i;
    int a,b,c;
    for(i = 100; i < 999; i++)
    {
        a = i/100;
        b = i/10 % 10;
        c = i % 10;
        if(i == (a*a*a) + (b*b*b) + (c*c*c))
            printf("%d\n",i);
    }

    return 0;
}

