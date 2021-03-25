#include <stdio.h>
#include <glob.h>

int main(int argc, char *argv[])
{
	glob_t res;

	glob("/etc/*", 0, NULL, &res);
	glob("/etc/.*", GLOB_APPEND, NULL, &res);

	for(int i = 0; i < res.gl_pathc; i++)
	{
		puts((res.gl_pathv)[i]);
	}

	globfree(&res);
	return 0;
}
