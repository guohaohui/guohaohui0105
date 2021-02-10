#include<stdio.h>

int main()
{
	int num = 0;
	int b,c;
	for(int i = 100; i < 1000; i++)
	{
		num = 0;
		b = i;
		for(b; b > 0;)
		{
			c = b % 10;
			num = c*c*c + num;
			b = b / 10;
			
		}
		if(i == num )
			printf("%d\n",i);
	
	}
	
	return 0;
}



