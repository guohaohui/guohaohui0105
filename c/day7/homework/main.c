/*
1、有一个字符串开头或结尾含有n个空格
（”   abcdefgdddd    ”），欲去掉前后
空格，返回一个新字符串。
要求：请自己定义一个接口（函数），并实现功能
*/
#include <stdio.h>
char *new_string(char *arr);

int main()
{
    char arr[30] = "   abcdefgdddd    ";
    
    new_string(arr);
    puts(arr);

    return 0;
}

char *new_string(char *arr)
{
    int i = 0;
    int j = 0;
    for (i = 0; arr[i]; i++)
    {
        if (arr[i] != ' ')
        {
            arr[j] = arr[i];
            j++;
        }
    }
    arr[j] = '\0';

    return arr;
}
