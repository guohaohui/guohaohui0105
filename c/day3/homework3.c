#if 0
#include<stdio.h>

int num = 0;
int num1 = 0;
int num2 = 0;
int palindrome(int k);
int palindrome1(int k);
int main()
{
    int n;
	printf("请输入一个整形数：");
    scanf("%d", &n);
    num2 = n;
    for(int i = 0; i <= 7; i++)
    {
        if(palindrome1(num2))
        {
            printf("循环了%d次得到回数%d\n", i, num2);
            break;
        }
        if(i == 7)
        {
            printf("循环了%d次没有得到回数\n", i);
            break;
        }
        printf("%d+%d=%d\n",num2,num1,num2+num1);
        num2 += palindrome(num2);
    }
    return 0;
}

int palindrome(int k) //求倒数
{
    num = 0;
  while(k > 0)
  {
      num = num*10 + k % 10;
      k = k / 10;
  }
    return num;
}
int palindrome1(int k) //判断是否是回数
{
    num1 = 0;
  while(k > 0)
  {
      num1 = num1*10+ k % 10;
      k = k / 10;
  }
    if(num1 == num2)
        return 1;
    else
        return 0;
}
#endif

#include<stdio.h>

int main()
{


	return 0;
}














