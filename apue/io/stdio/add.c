#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int add(FILE *rfd, FILE *tmp, char *a, char *b);
int main(int argc, char *argv[])
{
	FILE *rfd, *tmp;
	int cnt, i = 0;
	char ch;

	if(argc < 3)
		return 1;

	tmp = tmpfile();

	rfd = fopen(argv[1], "r+");
	if(rfd == NULL)
	{
		perror("fopen()");
		return 1;
	}
	
	printf("%d\n",add(rfd,tmp, argv[2], argv[3]));

	fclose(rfd);
	fclose(tmp);


	return 0;
}

int add(FILE *rfd, FILE *tmp, char *a, char *b)
{
	int i = 0;
	int cnt;
	char ch;
	while(1)
	{
		cnt = fread(&ch, 1, 1, rfd);
		if(cnt == 0)
		{
			if(feof(rfd))
				break;
			goto ERROR;
		}
		if(i == atoi(a)-1)
		{
			fwrite(b, 1, strlen(b), tmp);
			i++;
		}
		if(ch == '\n')
		{
			i++;
		}
		
		fwrite(&ch, 1, 1, tmp);
	}

	rewind(rfd);
	rewind(tmp);
	
	while(1)
	{
		cnt = fread(&ch, 1, 1 ,tmp);
		if(cnt == 0)
		{
			if(feof(tmp))
				break;
			goto ERROR1;
		}
	
		fwrite(&ch, 1, 1, rfd);
	}


	return 0;
ERROR1:
	fclose(tmp);
ERROR:
	fclose(rfd);
	return 1;
}


