#include <stdio.h>
#include <string.h>

int main()
{
    char n = 1;
    char arr[20] = {};
    int i = 0;
    char c;
    while(1)//(c = getchar())&& c !='\n')
    {
        scanf("%c", &arr[i]);
        //arr[i]=c;
     //   if(arr[i] == '\n')
     //       break;
        printf("%c\n",arr[i]);
        if(arr[i] == '\n')
            break;
        i++;   //一定要在后面 不然判断会死循环
    }
    //gets(arr);
    printf("%s",arr);
    
    for(i = 0; i < strlen(arr); i++)
    {
        if(arr[i] == ' ')
        {
            n++;
        }
    }

    printf("一共%d个单词\n", n);

    return 0;
}