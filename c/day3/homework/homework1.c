#if 1
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
	/*  for(int i = 0; i <= 7; i++)
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
		}*/
	int i = 0;
	int ver , m;
	while(i < 7)
	{
		if(palindrome1(n))
		{
			printf("循环了%d次得到回数%d\n", i, n);
			break;
		}
		ver = palindrome(n);
		m = n + ver;
		printf("%d+%d=%d\n", n, ver, m);
		n = m;
		i ++;
	}
	if(i == 7)
	{
		printf("循环了%d次没得到回数\n", i);
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

int palindrome1(int k) //判断回文数
{
	return k == palindrome(k);
}


/*
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
   }*/

#endif













