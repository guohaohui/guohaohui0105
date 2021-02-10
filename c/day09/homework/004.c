#include<stdio.h>
#include<string.h>
int tran(char *p);
int main(int reav, char **reag)
{
    if(strcmp(reag[2], "+") == 0)
        printf("%s%s%s=%d\n",reag[1],reag[2],reag[3],tran(reag[1])+tran(reag[3]));
    if(strcmp(reag[2], "-") == 0)
        printf("%s%s%s=%d\n",reag[1],reag[2],reag[3],tran(reag[1])-tran(reag[3]));
    if(strcmp(reag[2], "x") == 0)
        printf("%s%s%s=%d\n",reag[1],reag[2],reag[3],tran(reag[1])*tran(reag[3]));
    if(strcmp(reag[2], "/") == 0)
        printf("%s%s%s=%d\n",reag[1],reag[2],reag[3],tran(reag[1])/tran(reag[3]));
    return 0;
}

int tran(char *p)
{
    int len = strlen(p);
    int sum=0;
    for (int i = 0; i < len; i++)
    {
        sum = sum * 10 + (p[i]-48);
     }

    return sum;
}