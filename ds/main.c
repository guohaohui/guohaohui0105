#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void init_t(char **);
int main()
{
	char *q;

	init_t(&q);

	printf("%s\n",q);
	return 0;
}

void init_t(char **q)
{
	char *p = calloc(10, sizeof(char));

	strcpy(p,"hello");
	
	*q = p;

}


