#include <stdio.h>

int main()
{
	int i,j;
	int a, b;
	
	printf("请输入长和宽：");
	
	scanf("%d%d", &i, &j);
	
	for(a = 0; a < i ; a++)
	{
		for(b = 0; b < j; b++)
		{
			printf("#");
		}
		printf("\n");
	}
}




