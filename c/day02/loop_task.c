/*
 1. 读入一个四则运算式，计算其结果
 例如:读入1+2
 输出 1+2=3
 例如:读入2*3
 输出 2*3=6
#include<stdio.h>
int main()
{
	int a, b, c;
	char d;
	printf("请输入：");
	
	scanf("%d%c%d", &a, &d, &c);
	b = d;
	if(b == 43)
		printf("%d+%d=%d\n", a, c,a+c);
	if(b == 42)
		printf("%d*%d=%d\n", a, c,a*c);
	if(b == 45)
		printf("%d-%d=%d\n", a, c,a-c);
	if(b == 47)
		printf("%d/%d=%d\n", a, c,a/c);
	return 0;

}
 2. 读入一个四位整型数，判断十位出现的次数

#include<stdio.h>
int main()
{
	int i =0;
	int num, num1;
	printf("请输入一个四位的整形数：");
	scanf("%d", &num);
	num1 = num /10 %10;
	while(num > 0)
	{
		if(num % 10 == num1)
			i++;
		num = num / 10;
	}
	printf("十位数是%d一共出现%d次\n",num1, i);
	return 0;
}


 3. 打印输出菱形,例如读入了4行，则输出一下图型
        *
	  * * *
	* * * * *
  * * * * * * *
    * * * * *
	  * * *
	    *
*//*
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int i, j, n, a;
	printf("请输入：");
	scanf("%d", &n);
	
	for(i = 0; i< n+n-1; i++)
	{
		if(i < n)
		{
			for(j = 1;j <abs(n-i); j++)
				printf(" ");
			for(j = 0;j <= i*2; j++)
				printf("*");
			printf("\n");
		}else
		{
			for(j = 0;j <=abs(n-i); j++)
				printf(" ");
			for(j = 2*j+1;j < n*2;j++ )	
				printf("*");	
			printf("\n");
		}
	}

	return 0;
}*/
#if 0
#include<stdio.h>

int main()
{
	int n;

	printf("请输入行数：");

	scanf("%d", &n);

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n-i- 1; j++)
			printf("  ");
		for(int j = 0; j < 2*i+1; j++)
			printf("* ");
		printf("\n");
	}

	for(int i = n - 2; i >= 0; i--)
	{
		for(int j = 0; j < n-i-1; j++)
			printf("  ");
		for(int j = 0; j < 2*i+1; j++)
			printf("* ");
		printf("\n");
	}

	return 0;
}

#endif


/*

 4. 一个2000以内的整型数，它+100后是一个完全平方数,再加上168
 又是一个完全平方数,请问该数为多少

 
#include<stdio.h>
#include<math.h>
 int main()
{
	double num, num1;

	for(int a = 0; a <= 2000; a++)
	{
		num = sqrt(a + 100);
		num1 = sqrt(a + 268);
		if(num == (int)num && num1 == (int)num1)
			printf("%d\n", a);
	}

	return 0;
}
*/
/*1. 从键盘输入年号和月号，求这一年的这一月共有多少天。
#include<stdio.h>

int main()
{
	int year, month , day;
	printf("请输入年月：");
	
	scanf("%d%d", &year, &month);

	if(month == 1 || month == 3 || month == 5 || month == 7 || \
	   month == 8 || month == 10 || month == 12)
		day = 31;
	else if(month == 4 || month == 6 || month == 9 || month ==11)
		day = 30;
	else
	{
		if(year % 4 == 0 && year % 100 != 0 || year % 400 ==0)
			day = 29;
		else
			day = 28;
	}
	printf("%d年的%d月有%d天\n", year, month, day);
	
	return 0;
}
*/
/*2. 求某一范围内完数的个数。如果一个数等于它的因子(因子就是所有可以整除这个数的数)之和
  ，则称该数为“完数”（或“完全数”)。例如，6的因子为1、2、3，而 6=1+2+3，因此6是“完数”。
范围由用户输入，例如输入100就是求100内由多少个完数
#include<stdio.h>

int main()
{
	int n;
	int num = 0;
	printf("请输入一个整形数：");

	scanf("%d", &n);
	
	for(int i = 1; i < n; i++)
	{
		num = 0;
		for(int j = 1; j < i; j++)
		{
			if(i % j == 0)
			{
				num = num + j;
			}
		}
		if(num == i)
			printf("%d\n", i);
	}
	

	return 0;
}

*/

/*99乘法表

#include <stdio.h>

int main()
{
     int i, j;
     int n;
     for(i = 1; i <= 9; i++)
     {
         for(n = 1; n < i; n++)
                printf("        ");
         for(j = i ; j <=9 ; j++)
         {
            
             printf("%d*%d=%2d  ",i,j,i*j);
         }
         printf("\n");
     }   
     return 0;
 }   
*/
/*输入年月日判断是这年的第几天*
#include<stdio.h>

int main()
{
	int year, month, day;
	int day1;
	int num = 0;
	printf("请输入年月日：");

	scanf("%d%d%d", &year, &month, &day);
	if(month >= 1 && month <= 12)
	{
		for(int i = 1; i < month; i++)
		{
			if(i == 1 || i == 3 || i == 5 || i == 7 || \
					i == 8 || i == 10 || i == 12)
				num += 31;
			else if(i == 4 || i == 6 || i == 9 || i ==11)
				num += 30;
			else
			{
				if(year % 4 == 0 && year % 100 != 0 || year % 400 ==0)
					num += 29;
				else
					num += 28;
			}
		}
		num += day;
		printf("%d年%d月%d日是%d年的第%d天\n", year, month, day, year, num);
	}
	else 
	{
		printf("错误\n");
	}
	return 0;
}


*/





















