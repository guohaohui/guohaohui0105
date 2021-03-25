#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[])
{
	char buf[100] = {};
	time_t t;
	time(&t);
	//printf("%ld\n", t);		
	struct tm *time;

	time = localtime(&t);
	
	time->tm_mday += atoi(argv[1]);

	t = mktime(time);
	
	time = localtime(&t);
//	time->tm_year += 1900;
	strftime(buf, 100, "%Y年 %m月 %d %H:%M", time);

	puts(buf);

	//printf("%ld\n", t);		

	return 0;
}
