#include<stdio.h>

int date (int y, int m);

int main()
{
	int a, b;
	int num;
	printf("请输入年月：");
	scanf("%d%d", &a, &b);

	num = date(a, b);

	printf("%d年的%d月有%d天\n", a, b, num);
	
	return 0;
}

int date(int y, int m)
{
	int day;

	if(m == 1 || m == 3 || m == 5 || m == 7 ||\
		   	m == 8 || m == 10 || m == 12)
		day = 31;
	else if(m == 4 || m == 6 || m == 9 || m == 11)
		day = 30;
	else 
	{
		if(y % 4 == 0 && y % 100 != 0 || y % 400 == 0)
			day = 29;
		else 
			day = 28;
	}
	return day;
}

