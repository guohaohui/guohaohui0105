/*递归解决分鱼问题*/
#include <stdio.h>
int sub(int n);
int main()
{
    printf("%d\n",sub(5));

    return 0;
}
/*第一次每人分到的鱼的数量可用(x-1)/5表示，
余下的鱼数为4*(x-1)/5,将余下的数量重新赋值给x，
依然调用(x-1)/5,如果连续5次x-1后均能被5整除，
则说明最初的x值是本题目的解*/
int sub(int n)
{
    if (n == 1)
    {
        static int i = 0;
        do
        {
            i++;
        } while (i % 5 != 0);
        
        return (i + 1);
    }
    else
    {
        int t;
        do
        {
            t = sub(n - 1);
        } while (t % 4 != 0);
        printf("%d\n",t);
        return (t / 4 * 5 + 1);
    }
}