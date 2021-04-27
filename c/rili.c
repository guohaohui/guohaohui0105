#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int year(int a)
{
	if(a % 4 == 0 && a % 100 != 0 || a % 400 == 0)
	{
		return 1;
	}
	
	return 0;
}

int math(int a, int b)
{
	if(a == 1 || a == 3 || a == 5 || a == 7 || a == 8 || a == 10 || a == 12)
		return 31;
	if(a == 4 || a == 6 || a == 9 || a == 11)
		return 30;
	if(a == 2)
		return 28 + year(b);
}

int day(int y, int m)
{
	int num = 0;
	for(int i = 1900 ; i < y; i++)
	{
		num += 365 + year(i);
	}

	for(int i = 1; i < m; i++)
	{
		num += math(m, y);
	}

	return num;
}

int main(int argc, char *argv[])
{
	if(argc < 3)
		return -1;
	int y = atoi(argv[1]);
	int m = atoi(argv[2]);

	int daye = day(y, m);

	int xingqi = daye % 7;
	printf("日 一 二 三 四 五 六\n");
	for(int i = 0; i <= xingqi; i++)
		printf("   ");
	for(int i = 1; i <= math(m,y); i++)
	{
		printf("%2d ", i);
		if((i + xingqi + 1) % 7 == 0)
			printf("\n");
	}
	printf("\n");
	return 0;
}


