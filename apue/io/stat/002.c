#include "001.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <glob.h> 
int fileStat_l(void) 
{ 
	glob_t res; 
	glob("*", 0, NULL, &res); 
	for(int i = 0; i < res.gl_pathc; i++) 
	{ 
		stat_l((res.gl_pathv)[i]);
		//puts((res.gl_pathv)[i]); 
	} 
	globfree(&res); 
	return 0; 
}
int fileStat_la(void) 
{ 
	fileStat_l();
	glob_t res; 
	glob(".*", 0, NULL, &res); 
	for(int i = 0; i < res.gl_pathc; i++) 
	{ 
		stat_l((res.gl_pathv)[i]);
		//puts((res.gl_pathv)[i]); 
	} 
	globfree(&res); 
}
int fileStat_li(void) 
{ 
	glob_t res; 
	glob("*", 0, NULL, &res); 
	for(int i = 0; i < res.gl_pathc; i++) 
	{ 
		stat_i((res.gl_pathv)[i]);
		stat_l((res.gl_pathv)[i]);
		//puts((res.gl_pathv)[i]); 
	} 
	globfree(&res); 
	return 0; 
}
int fileStat_lai(void) 
{ 
	glob_t res; 
	glob("*", 0, NULL, &res); 
   	glob(".*", GLOB_APPEND, NULL, &res);	
	for(int i = 0; i < res.gl_pathc; i++) 
	{ 
		stat_i((res.gl_pathv)[i]);
		stat_l((res.gl_pathv)[i]);
		//puts((res.gl_pathv)[i]); 
	} 
	globfree(&res); 
	return 0; 
}
int fileStat_ai(void) 
{ 
	glob_t res; 
	glob("*", 0, NULL, &res);
   	glob(".*", GLOB_APPEND, NULL, &res);	
	for(int i = 0; i < res.gl_pathc; i++) 
	{ 
		stat_i((res.gl_pathv)[i]);
		puts((res.gl_pathv)[i]); 
	} 
	globfree(&res); 
	return 0; 
}
int fileStat_i(void) 
{ 
	glob_t res; 
	glob("*", 0, NULL, &res); 
	for(int i = 0; i < res.gl_pathc; i++) 
	{ 
		stat_i((res.gl_pathv)[i]);
		printf(" %s\n", ((res.gl_pathv)[i])); 
	} 
	globfree(&res); 
	return 0; 
}

int fileStat_a(void) 
{ 
	glob_t res; 
	glob("*", 0, NULL, &res);
   	glob(".*", GLOB_APPEND, NULL, &res);	
	for(int i = 0; i < res.gl_pathc; i++) 
	{ 
		puts((res.gl_pathv)[i]); 
	} 
	globfree(&res); 
	return 0; 
}

int fileStat_Path(char *arr) 
{ 
	glob_t res;
	strcat(arr, "*");
	glob(arr, 0, NULL, &res); 
	for(int i = 0; i < res.gl_pathc; i++) 
	{ 
		//stat_i((res.gl_pathv)[i]);
		puts((res.gl_pathv)[i]+strlen(arr)-1); 
	} 
	globfree(&res); 
	return 0; 
}
int main(int argc, char *argv[])
{
	int ch;
	char *arr;
	int judge = 0x0F;
	int a,b,c,d;
	a = b = c = d = 0x00;
	while (1) {
		ch = getopt(argc, argv, "-lai");
		if (-1 == ch)
			break;
		switch (ch) {
			case 'l':
				a = 0x01;
				//fileStat_l();		
				break;
			case 'a':
				b = 0x02;
				break;
			case 'i':
				c = 0x04;
				break;
			case 1:
				d = 0x08;
				if (optarg != NULL)
					//printf("arg:%s\n", optarg);
				arr = optarg;
				break;
			case '?':
				printf("i don't know\n");
				break;
			default:
				break;
		}
	}

	if(judge & (a | b | c) == 0x03){
		fileStat_la();
		return 0;
	}
	if(judge & (a | b | c) == 0x05){
		fileStat_li();
		return 0;
	}
	if(judge & (a | b| c) == 0x06){
		fileStat_ai();
		return 0;
	}
	if(judge & (a | b | c) == 0x07){
		fileStat_lai();
		return 0;
	}
	if(judge & a == 0x01){
		fileStat_l();
		return 0;
	}
	if(judge & b == 0x02){
		fileStat_a();
		return 0;
	}
	if(judge & c == 0x04){
		fileStat_i();
		return 0;
	}
	if(judge & d == 0x08){
		fileStat_Path(arr);
		return 0;
	}
	return 0;
}




