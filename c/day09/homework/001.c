#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *new_string(const char *p);

int main()
{
  char *ret = "ghaHuiH";
  char *new = NULL;
  new = new_string(ret);
  puts(new);
  free(new);
  new = NULL;
  return 0;
}
/*将字符串中的小写字符组成新的字符串返回*/
char *new_string(const char *p)
{
  char *ret = NULL;
  char *new = NULL;
  int i, j;
  size_t size;
  size = strlen(p) + 1;

  ret = malloc(size);//分配内存空间
  if (ret == NULL)
  {
    return -1;
  }
  memset(ret, '\0', size);//初始化内存空间

  for (i = 0, j = 0; p[i]; i++)
  {
    if (p[i] >= 'a' && p[i] <= 'z')
    {
      ret[j] = p[i];
      j++;
    }
  }

  if (j + 1 < size)
  {
    new = realloc(ret, j + 1); //重新分配空间大小(j+1)把旧空间的内容复制到新空间然后free旧空间
    if (new == NULL)
    {
      return -1;
    }
    ret = NULL;
    //free(ret);
  }
  return new;
}
