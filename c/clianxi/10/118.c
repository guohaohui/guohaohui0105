/*判断素数*/
#include <stdio.h>

int isprime(int);

int main()
{
    int n;
    printf("input an integer\n");
    scanf("%d", &n);
    if (isprime(n)) //判断函数返回值真假
        printf("%d is a primc", n);
    else
        printf("%d is not a primc", n);
    printf("\n");
    return 0;
}

int isprime(int n)
{
    int flag = 1, i;
    for (i = 2; i < n; i++)
        if (n % i == 0) //能被整除就不是素数
            flag = 0;
    return flag;
}