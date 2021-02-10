/*递归解决年龄问题*/
#include <stdio.h>

int age(int);

int main()
{
    int n;
    scanf("%d", &n);

    printf("%d\n", age(n));

    return 0;
}

int age(int n)
{
    if (n == 1)
        return 10;
    else
        return age(n - 1) + 2;//递归
}