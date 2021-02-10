#include <stdio.h>

int chararry(char *p);

int main()
{
	char arr[20] = "guo hao hui";
	char cha1[] = {"guo hao hui"};
	char cha2[4] = {'g', 'u', 'o','\0'};
	char chr3[3] = {'g', 'u', 'o'}; // ???
	char chr4[4] = {'g', 'u', 'o'};
	
	int i;

	for(i = 0 ; arr[i] != '\0'; i++)
	{
		putchar(arr[i]); //printf("%c", arr[i])

	}
	printf("\n");
	
	printf("%d", chararry(cha1));
	printf("\n");

	
	
	return 0;
}

int chararry(char *p) //数组名是个指针常量
{
	int i;
	int n = 0;

	for(i = 0; p[i] != '\0'; i++)
		n++;
	return n;

}



