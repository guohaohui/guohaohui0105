//爬楼梯，他可以每次走1级、二级或者3级输入楼梯的级数求不同的走法数
#include <stdio.h>
int stairs(int n);
int main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n",stairs(n));
    return 0;
}

int stairs(int n)
{
    if(n == 1)
        return 1;
    if(n == 2)
        return 2;
    if(n == 3)
        return 4;
    if(n <= 0)
        return 0;
    return stairs(n-1) + stairs(n-2) + stairs(n-3);
    //if n = 5    |            |            |
             //4+2+1   +    4 + 0    +     2
}