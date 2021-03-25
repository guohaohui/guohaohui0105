#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
jmp_buf env;

static int shang(int a, int b)
{
	if(b == 0)
		//跳转到stejmp()
		longjmp(env, 1);
	return a / b;
}


int main()
{
	int a, b;
//	printf("%d %d\n",a ,b);
	if(setjmp(env) == 0) {
		printf("请输入两个整形数：");
	}else {
		printf("请重新输入：");
	}
	scanf("%d%d", &a, &b);
	
	printf("%d\n", shang(a, b));	

	exit(0);
}
