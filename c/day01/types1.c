#include <stdio.h>

int main(void)
{
	char ch1 = 'b';
	int num,num1;
	float f,g;
	//隐式转换
	//显式转换	
	g = 2.9;
	num = ch1;
	f = ch1;
	num1 = (int)g;
	
	
	printf("num = %d\n", num);
	printf(" %d\n", num + ch1);
	
	printf("f = %f\n", f);
	
	printf("num1 = %d\n", num1);

	printf("g = %f\n", g+ch1);

	printf("%d\n", (int)g);	



	return 0;
}
