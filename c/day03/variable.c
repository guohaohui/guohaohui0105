#include<stdio.h>

int glob;
int glob2 = 2;
static void test(void);
int main(void)
{
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
	for(int i = 0; i < glob2; i++)
		printf("i = %d\n", i);// 块变量，存储在栈中的
	printf("glob = %d\nglob2 = %d\na = %d\nb = %d\n", glob, glob2, a, b);
	printf("c = %d\nd = %d\ne = %d\nf = %d \n", c, d, e, f);

	test();
	test();
	test();
//	printf("%d",n);
	return 0;
}

static void test(void) //限制作用域在文本
{
   static int n;

	printf("n = %d\n", n);

	n++;

}
