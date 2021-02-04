/*4、c语言中有一个函数strstr(3)的功能是在字符串中找子串
，尝试自己定义一个函数实现其功能*/
#include <stdio.h>
#include <string.h>
int findStr1(char *s,char *l);
int main()
{
    char s[100] = "";
    char l[10]="";
    char *p;
    printf("请输入源字符串：");
    gets(s);
    //scanf("%s",s);
    printf("请输入要查找的字符串：");
    gets(l);
    //scanf("%s",l);
    findStr1(s,l);
    return 0;
}
int findStr1(char *s,char *l)
{ 
    int j, m=1;
    for ( j = 0; j < strlen(s); j++)
    {
        if (s[j] == l[0])
        {
            for (int i = 1; i < strlen(l);i++)
            {
                if (s[j+i] == l[i])
                {
                    m++;
                }               
            }
            if (m==strlen(l))
            {
                char *p1 = &s[j];
                puts(p1);
                printf("首次出现位置：%d\n",++j);
                j=0;
                break;
            }  
        }  
    }
    if(j==strlen(s)){
        printf("not found\n");
    }

    return 0;
}