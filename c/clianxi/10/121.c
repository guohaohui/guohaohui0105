/*小数分离*/
#include <stdio.h>
#include <math.h>

int main()
{
    float number;
    double f,i;
    printf("input the number:");
    scanf("%f", &number);
    f = modf(number,&i);
    printf("%f=%f+%f\n",number,i,f);
    return 0;
}