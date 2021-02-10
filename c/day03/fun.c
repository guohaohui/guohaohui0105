#include<stdio.h>

int perfect_number(int num);

int main()
{
	int res;
	for(int j = 1; j < 100; j++)
	{
		res = perfect_number(j);
		if(res)
			printf("%d是完数:\n", j);
	}
	return 0;
}

int perfect_number(int num)
{
	int s = 0;
	for(int i = 1; i < num; i++)
	{
		if(num % i == 0)
			s = s + i;
	}
	if(num == s)
		return 1;
	else
		return 0;
}
