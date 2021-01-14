#include<stdio.h>
//百钱买百鸡
int main()
{
	int a, b, c;
	int money = 100;
	for(a = 0; a < 100; a++)
	{
		for(b = 0; b < 100; b++)
		{
			for(c = 0; c < 301; c++)
			{
				if(a*3 + b*2 + c/3 == money && c%3 == 0 && a+b+c == money)
				{
					printf("🐓：%-5d母鸡：%-5d🐣：%-5d\n", a, b, c);
				}
			}
		}
	}
}



