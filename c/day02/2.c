#include<stdio.h>
int main (void)
{
	int i, num;
	int cnt = 0;
	printf("在屏幕上输入一个四位数:");
	scanf("%d\n", &i);
	for(i = 1; i <= 9999; i = i * 10  ){
		if(num / i % 10 == num / 10 % 10)
			cnt++;
	
	}

		printf("%d的十位数出现了%d次\n", num , cnt);
	return 0;
}
