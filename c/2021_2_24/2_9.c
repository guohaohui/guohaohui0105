#include <stdio.h>

void func(char str[100])
{
	void *p;

	printf("sizeof(str) = %ld\n",sizeof(str));
	printf("sizeof(p) = %ld\n",sizeof(p));

}

int main()
{
	char str[100] = "hello yinchuan";
	char *p = str;
	char **pp = &p;
	printf("sizeof(str) = %ld\n",sizeof(str));
	printf("sizeof(p) = %ld\n",sizeof(p));
	printf("sizeof(pp) = %ld\n",sizeof(pp));
	func(str);

	return  0;
}
