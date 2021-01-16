/*
 数据类型
 */

#include <stdio.h>

int main(void)
{
	int num;

	num = 1;
	
	/*
     转义字符
	 \n
	 \b
  	 \r
	 \t
	*/

	printf("杨鹏辉真不\b好\t看\r郭浩辉\n");
	printf("num = %d", num);

	printf("%ld\n", sizeof(short));
	printf("%ld\n", sizeof(int));
	printf("%ld\n", sizeof(long));
	printf("%ld\n", sizeof(long long));
	printf("\n");
	printf("%ld\n", sizeof(char));
	printf("\n");
	printf("%ld\n", sizeof(float));
	printf("%ld\n", sizeof(double));
	printf("%ld\n", sizeof(long double));
	printf("%ld\n", sizeof(void));
	
	return 0;
}
