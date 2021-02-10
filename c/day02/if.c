#include <stdio.h>

int main()
{
	int a, b, c;
	int tem;
	printf("请输入3个整形数：");

	scanf("%d%d%d", &a, &b, &c);

	if(a < b)
	{
		tem = a;
		a = b;
		b = tem;
		
	}
	if(a < c)
	{
		tem = a;
		a = c;
		c = tem;
		
	}
	if(b < c)
	{
		tem = c;
		c = b;
		b = tem;
		
	}
	
	printf("%d,%d,%d\n",a,b,c);



	


}


