#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	FILE *fp, *wfp;
	int ch, cnt;
	char buf[10] = {};
	if(argc < 2)
		return 1;
	
	fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		perror("fopen()");
		return 1;
	}
	wfp = fopen(argv[2], "w");
	if(wfp == NULL)
	{
		perror("fopen1()");
		fclose(fp);
		return 1;
	}

	while(1)
	{
#if 0
		ch = fgetc(fp);  //字符读写
		if(ch == EOF)
		{
			if(feof(fp))
				break;
			else
				goto ERROR;
		}
		
		fputc(ch, stdout);
#endif
#if 0
		memset(buf, '\0', 10);
		if(fgets(buf, 10 ,fp) == NULL)	//行读写
		{
			if(feof(fp))
				break;
			goto ERROR;
		}
		
		fputs(buf, stdout);
		
		sleep(1);
#endif
		cnt = fread(buf, 1, 10, fp); //二进制读写
		if(cnt == 0)
		{
			if(feof(fp))
				break;
			goto ERROR;
		}
		fwrite(buf, 1, cnt, wfp);
	}

	fclose(fp);
	fclose(wfp);
	return 0;
ERROR:
	fclose(fp);
	return 1;
}
