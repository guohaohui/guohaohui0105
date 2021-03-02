//键盘输入长方体的长宽高L\W\H，求其体积及表面积。
#include <stdio.h>

int funca(int L, int W, int H)
{
    return L * W * H;
}
int funcb(int L, int W, int H)
{
    return (L * W + L * H + W * H) * 2;
}


int main()
{
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    printf("%d\n",funca(a,b,c));
    printf("%d\n",funcb(a,b,c));

    return 0;
}


