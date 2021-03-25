#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <glob.h>
int parseString(char *s, glob_t *res)//分割字符串
{
	char *r;
	int i = 0;
	while(1) {
		r = strtok(s, " ");
		if(r == NULL)
			break;
		glob(r, GLOB_NOCHECK | GLOB_APPEND * i, NULL, res);
		i = 1;
		s = NULL;
	}
	return 0;
}
void mysystem(const char *s)// ---->system(const char *s)
{
	glob_t res;
	pid_t pid;
	char *arr = malloc(strlen(s)+1);
	strcpy(arr, s);
	parseString(arr, &res);
	
	pid = fork();
	if(-1 == pid) {
		perror("fork()");
		exit(1);
	}
	if(0 == pid) {
		execvp((res.gl_pathv)[0], res.gl_pathv);
		perror("execvp()");
		exit(1);
	}
	puts((res.gl_pathv)[0]);
	wait(NULL);
	free(arr);
	arr = NULL;
	globfree(&res);
}
int main(void)
{
	mysystem("clear");
	
	printf("1111111111\n");

	getchar();
	exit(0);
}
