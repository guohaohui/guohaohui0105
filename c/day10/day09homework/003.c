#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add(int a, int b)
{
    return a+b;
}

int del(int a, int b)
{
    return a-b;
}

int mul(int a, int b)
{
    return a*b;
}

int divi(int a, int b)
{
    return a/b;
}

int op(int a, int b, int (*p)(int,int)) //指针函数
{
    return p(a,b);
}

int main(int argc , char **argv)
{
    int left ,right;

    if(argc < 4)
        return 1;
    left = atoi(argv[1]); //字符串转整形函数 atoi(3)
    right = atoi(argv[3]);

    if(!strcmp(argv[2],"+"))//判断命令行的输入
    {
        printf("%d+%d=%d\n", left, right,op(left, right, add));
    }
    else if(!strcmp(argv[2], "-"))
    {
        printf("%d+%d=%d\n", left, right,op(left, right, del));
    }
    else if(!strcmp(argv[2], "x"))
    {
        printf("%d+%d=%d\n", left, right,op(left, right, mul));
    }
    else if(!strcmp(argv[2], "/"))
    {
        printf("%d+%d=%d\n", left, right,op(left, right, divi));
    }

    return 0;

}