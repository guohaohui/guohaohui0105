#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int len;

int getLength(int *p);
int *delete(int *p, int n);
int *addArr(int *p, int arr[], int n);
int main()
{

  int i = 0;
  int *arr = NULL;
  int *new;
  int arr1[] = {90, 80, 2, 4};
  printf("请确定数组长度:");

  if (scanf("%d", &len) != 1)
  {
    printf("没有输入任何数!\n");
    exit(0);
  }

  arr = (int *)malloc(sizeof(int) * len);

  if (arr == NULL)
  {
    printf("内存申请失败!!!\n");
    exit(0);
  }
  printf("请给动态数组写入值\n");

  while (i < len && scanf("%d", &arr[i]) == 1)
  {
    ++i;
  }

  arr = addArr(arr, arr1, 4);
  for (i = 0; arr[i]; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  arr = delete(arr, 4);
  for (i = 0; arr[i]; i++)
  {
    printf("%d ", arr[i]);
  }
  free(arr);
  return 0;
}
/*向数组里添加值*/
int *addArr(int *p, int *arr, int n)
{
  int len1 = getLength(arr);

  if (n < len)
  {
    p = (int *)realloc(p, len * sizeof(int)  +  len1 * sizeof(int));

    if (p == NULL)
    {
      exit(0);
    }
    for (int i = (len + len1 - 1), j = len - 1; j >= n - 1; i--, j--)
    {
      p[i] = p[j];
    }
    for (int i = n - 1, j = 0; j < len1; i++, j++)
    {
      p[i] = arr[j];
    }
  }
  else if (n > len)
  {
    p = realloc(p, sizeof(int) * len + sizeof(int) * (len1));
    if (p == NULL)
    {
      exit(0);
    }

    for (int i = len , j = 0; j < len1; i++, j++)
    {
      p[i] = arr[j];
    }
  }
  return p;
}

int getLength(int *p)
{
  for (int i = 0;; i++)
  {
    if (!p[i])
    {
      return i - 1;
    }
  }
}

int *delete(int *p, int n)
{
  int q ;
  int len2 = getLength(p);
  int i,j;
  for(i = 0; i < len2; i++)
  {
    if(p[i] == n)
    {
      j = i;
      break;
    }
  }
  q = p[len2 - 3];
  p = realloc(p, sizeof(int) * (len2 -1));

  for(i = j; i < len2 -3; i++)
  {
     p[i] = p[i+1]; 
  }
  p[i] = q;
  return p;
}


