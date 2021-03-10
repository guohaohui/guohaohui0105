#include <stdio.h>
#include <stdlib.h>

#include <lstack1.h>

char *change(int num, int n)
{
	lstack_t *s;
	int r;
	char ch;
	char *res = NULL;
	lstackInit(sizeof(char), 32, &s);

	while(num){
		r = num % n;
		if(r < 10){
			ch = r + '0';
		}else {
			ch = r - 10 + 'a';
		}
		lstackPush(s, &ch);
		num /= n;
	}
	int i = 0;
	while(!lstackEmpty(s)) {
		res =realloc(res, i+1);
		lstackPop(s,res + i);
		i++;
	}
	res = realloc(res , i+1);
	res[i] = '\0';
	
	lstackDestory(s);
	return res;
}


int main(int argc, char **argv)
{
	if(argc < 3)
		return 1;
	char *p = change(atoi(argv[1]),atoi(argv[2]));
	puts(p);

	free(p);
	return 0;
}


