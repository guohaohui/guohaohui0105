#include <stdio.h>
void func(int n, char str[][4])
{
    int i;
    for (i = 0; i < n; i++)
        printf("/nstr[%d] = %s\n", i, str[i]);
}

void main()
{
    char *p[3];  //*(*(p+3))
    char str[][4] = {"abc", "def", "ghi"};
    func(3, str);
}
  //   str[1][2] == *(*(str+1)+2)c