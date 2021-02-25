#include <stdio.h>

typedef struct{
    char var1;
    int var2;
    long long var3;
    char var4;
}test2_t;

int func(int x)
{
	int countx = 0; 
	while(x) 
	{
		countx++;
		x = x &(x - 1);
    }
	return countx;
}

int main(void)
{
    test2_t t;
    printf("%ld\n",sizeof(long));
    printf("%ld\n",sizeof(long long));
    printf("%ld\n",sizeof(t));
    printf("%d\n",func(9999));
    return 0;
}
