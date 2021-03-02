//200以内的素数
#include <stdio.h>

int main()
{
    int i,j;
    for(i = 0; i < 200; i++)
    {
        for(j = 2; j < i; j++)
        {
            if(i % j == 0)
                break;
        }
        if(i == j)
            printf("%d\n",i);
    }

    return 0;
}
