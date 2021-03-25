#include <stdio.h>
#include <stdlib.h>
extern char **environ;

int main(void)
{
#if 0
	for(int i = 0; environ[i]; i++)
		puts(environ[i]);
#endif
	char *p = getenv("C_INCLUDE_PATH");
	puts(p);
	//setenv("PATH", ".", 1);
	//p = getenv("PATH");
	puts(p);
	return 0;
}
