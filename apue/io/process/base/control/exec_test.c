#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char *line = NULL;
	char *line1 = NULL;
	size_t len = 0;
	char ch = ' ';
	char *size;
	pid_t pid;
	glob_t res;
	int i ;
	while(1){
		i = 0;
		printf("[%s]$", getenv("PWD"));
		getline(&line, &len, stdin);//读一行
		if(strncmp(line, "exit\n", 4) == 0) {
			free(line);
			line = NULL;
			break;
		}
		line1 = line;
#if 1
		while(1){
			if(*(++line1) == '\n'){
				*line1-- = '\0';
				break;
			}
		}
#endif			
		while(1){
			size = strsep(&line, &ch);
			if(size == NULL)
				break;
			glob(size, GLOB_NOCHECK | GLOB_APPEND * i, NULL,&res);//把size存到res
			//printf("%s\n", size);
			i = 1;
			//line = NULL;
		}
		pid  = fork();
		if(-1 == pid)
		{
			perror("fork()");
			exit(1);
		}	
		if(0 == pid)
		{
			execvp((res.gl_pathv)[0], res.gl_pathv);//进程替换
			perror("execvp()");
			exit(1);		
		}
		wait(NULL);
		globfree(&res);
		free(line);
		line = NULL;
		len = 0;
	}

	exit(0);
}
