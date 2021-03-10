#include <stdio.h>
#include <string.h>

char *deleChar(char *arr,char *p)
{
    int i=0,j=0;
    while(*(p+i) != '\0')
    {
        if(p[i] == ' ')
        {
            i++;
            continue;
        }
        strcpy(arr+j, p+i);
        //*(p+j) = *(p+i);
        i++;
        j++;
    }
    arr[j] = '\0';
    
}

int main()
{
    char *a = "ab   cc\t  dd";
    char arr[10];
    deleChar(arr,a);
    puts(arr);
    return 0;
}