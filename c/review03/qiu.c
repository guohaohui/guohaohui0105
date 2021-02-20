//在n个球中，任意取出m个（不放回），求共有多少种取法
#include <stdio.h>
int theBall(int n, int m);
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    printf("%d\n",theBall(n,m));
    return 0;
}

int theBall(int n, int m)
{
    if(n < m)
        return 0;
    if(n == m)
        return 1;
    if(m == 0)
        return 1;
    return theBall(n-1,m-1) + theBall(n-1,m);
}