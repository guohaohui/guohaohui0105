#include<stdio.h>
int main(void)
{
	int a , b, c = 0;
	printf("请输入范围;");
	scanf("%d", &a);

	for(int i = 1;i < a ;i++){
		b = 0;
		for(int j = 1; j < i; j++){
			if(i % j == 0){
			b += j ;
		
			}		
		
		}
		if(b == i){
			printf("%d\n", i);
			c++;
		
		}
	
	}
	printf("共%d个", c);
	return 0;
}
