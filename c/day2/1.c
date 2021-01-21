#include<stdio.h>
int main(void)
{
	int i,j;
	char f;

	printf("输入四则运算式:");

	scanf("%d%c%d", &i, &f, &j);

	switch(f){
		case '+':
			printf("%d + %d = %d\n", i , j ,i + j);
			break;
		case '-':
			printf("%d - %d = %d\n", i , j ,i - j);
			break;
		case '*':
			printf("%d * %d = %d\n", i , j ,i * j);
			break;
		case '/':
			printf("%d / %d = %d\n", i , j ,i / j);
			break;
	
	}

	return 0;


}
