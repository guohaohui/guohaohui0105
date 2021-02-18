#include <stdio.h>
char *mystrcpy(char *dest, char *src);
char *mystrcat(char *dest, char *src);
int main()
{
	int i;
	char guo[50] = "guohaohui"; //
	char hui[50] = "";
	char *p; //*p 相当于一个数组p[]的首地址
	p = mystrcpy(hui, guo);
	for (int i = 0; i < 10; i++)
	{
		printf("%c", *p++);
	}
	printf("\n");
	for (i = 0; hui[i] != '\0'; i++)
	{
		putchar(hui[i]);
	}

	printf("\n");
	mystrcat(guo, "zhenshuai");
	puts(guo);

	return 0;
}

/*
dest 目的位置的首地址
src  要复制的原字符串的首地址
return 目的位置首地址
 */
/*strcpy(3)*/
char *mystrcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)// 遇到'\0'结束循环
	{
		dest[i] = src[i];//把src[]里的内容复制到dest[]
	}

	dest[i] = '\0';
	return dest;
}

/*strcat(3)  字符串拼接*/

char *mystrcat(char *dest, char *src)
{
	int i;
	for(i = 0; dest[i]; i++)
		;
	mystrcpy(dest+i,src);//把src的内容拷贝到dest(从dest+i处拷贝）

	return dest;
}


