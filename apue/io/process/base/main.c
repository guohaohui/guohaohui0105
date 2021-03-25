#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void test(void)
{
	exit(0);
}

void guo1(void)
{
	printf("%s\n",__FUNCTION__);
}

void guo2(void)
{
	printf("%s\n",__FUNCTION__);
}

void guo3(void)
{
	printf("%s\n",__FUNCTION__);
}

int main()
{
	//test();
	printf("%ld", sizeof(guo1));
	
	atexit(guo1);
	atexit(guo2);
	atexit(guo3);

	//_Exit(EXIT_SUCCESS);
	//_exit(EXIT_SUCCESS);
	exit(EXIT_SUCCESS);
}
