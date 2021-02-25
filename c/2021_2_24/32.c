#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(char *s, char*t, int i);

int main()
{
    char arr[] = "guohaohui";
    char arr1[] = "hello";

    insert(arr,arr1,4);
    puts(arr);

    return 0;
}

void insert(char *s, char*t, int i)
{
    int len = strlen(s);
    int len1 = strlen(t);
    //char *p = (char *)calloc(len + len1 +1, sizeof(char));
    char *p = s; // p指向x;
    char *q = (char *)calloc(len - i + 1, sizeof(char));
    memcpy(q,s+i,len - i);
    memcpy(p,s,i);
    memcpy(p+i,t,len1);
    memcpy(p+i+len1,q,len - i);
    free(q);
   // memcpy(&s,&p,len+len1);

    
}
