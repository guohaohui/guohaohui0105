#include<stdio.h>

#define NUM 10

#define SQUARE(x) (x)*(x)

#define SWAP(x, y) \
	do {\
		typeof(x) t; t = x; x = y; y = t;\     //typeof(x) 获取变量的类型值
	}while(0)



int main()
{
	int i;
	int score;
	int x = 5, y = 10;

	SWAP(x, y);

	printf("x = %d y = %d\n",x ,y);

	i = 5;

	printf("%d\n",SQUARE(i+2));
#if 0
	for(i = 0; i < NUM; i++)
	{
		scanf("%d", &score);
	}
#endif
	return 0;
}



