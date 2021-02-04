#include<stdio.h>

int main()
{
	int a = 10;
	int b = 5;
	int c;
	
	a++;
	printf("a = %d\n", a);
	a--;
	printf("a = %d\n", a);
	c = a+++b;
	printf("a = %d,b = %d,c = %d\n",a ,b ,c);
	c = a---b;
	printf("a = %d,b = %d,c = %d\n",a ,b ,c);
	c = --a + b;
	printf("a = %d,b = %d,c = %d\n",a ,b ,c);
	c = ++a + b;
	printf("a = %d,b = %d,c = %d\n",a ,b ,c);
	c = a++ + ++b;
	printf("a = %d,b = %d,c = %d\n",a ,b ,c);
	c = --a + ++b;
	printf("a = %d,b = %d,c = %d\n",a ,b ,c);
	printf("\n");
	c = a & b;
	printf("a = %d,b = %d,c = %d\n",a ,b ,c);
	c = a | b;
	printf("a = %d,b = %d,c = %d\n",a ,b ,c);
	c = ~a;
	printf("a = %d,b = %d,c = %d\n",a ,b ,c);
	c =~ b;
	printf("a = %d,b = %d,c = %d\n",a ,b ,c);

	char num1,num2,num3;
	num1 = 127;
	num2 = num1 >> 1;
	num3 = num1 << 1;
	printf("num2 = %d,num3 = %d\n",num2,num3);
	num1 = -15;
	num2 = num1 >> 1;
	num3 = num1 << 1;
	printf("num2 = %d,num3 = %d\n",num2,num3);

	num1 = -1;
	num2 = num1 >> 1;
	num3 = num1 << 1;
	printf("num2 = %d,num3 = %d\n",num2,num3);
	
	char n1 = 5 ,n2 = 6;
	printf("n1 = %d,n2 = %d\n",n1,n2);
	n1 = n1 ^ n2;
	n2 = n1 ^ n2;
	n1 = n1 ^ n2;
	
	printf("n1 = %d,n2 = %d\n",n1,n2);

	return 0;
}
