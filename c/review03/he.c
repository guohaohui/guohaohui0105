/*请输入整数n,求 1！+2！+3！+...+n!的和*/

#include <stdio.h>
int and(int n);
int main()
{
    int n;
    int ret=0;
    scanf("%d", &n);
    for(int i = n; i > 0; i--)
    {
        ret = ret + and(i);
    }
    printf("%d\n", ret);
}

int and(int n)
{
    if(n <= 0)
        return 0;
    if(n == 1)
        return 1;
    
    return n* and(n-1);
}