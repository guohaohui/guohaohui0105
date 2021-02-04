#include<stdio.h>
int year(int y);
int month(int y, int m);
int main()
{
	int year1, month1 ,day1;
	int num = 0;

	printf("请输入年月日:");

	scanf("%d%d%d", &year1, &month1,  &day1);
	
	if(month(year1, month1))
	{
		num = month(year1, month1) + day1;
		printf("%d年%d月%d日是%d年的%d天\n", year1, month1, day1, year1, num);
	}
	else
	{
		printf("没有这个月份\n");
	}
	return 0;
}
int year(int y)
{
	if(y % 4 == 0 && y % 100 != 0 || y % 400 == 0)
		return 1;
	else
		return 0;
}
int month(int y, int m)
{
	int num = 0;
	if(m > 0 && m < 12)
	{
		for(m=m-1; m > 0; m--)
		{
			if(m == 1 || m == 3|| m == 5 || m == 7 || m == 8 ||\
					m == 10 || m == 12)
				num += 31;
			else if(m == 4 || m == 6 || m == 9 || m == 11)
				num += 30;
			else
				num += 28 + year(y);
		}
		return num;
	}
	else
	{
		return 0;
	}
}




