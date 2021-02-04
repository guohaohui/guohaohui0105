#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4
int len = 0, len1 = 0;

int getLength(int *p);
void show(int *p);                     //遍历
void find(int *p, int n);              //查找第几个数的值
int *delete (int *p, int n);           //删除指定的数
int *addArr(int *p, int arr[], int n); //插入
int main()
{
  int i = 0, a;
  int *arr = NULL;
  int arr1[N] = {90, 80, 2, 4};
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

  while (1)
  {
    printf("1:插入\t2:删除\t3:查找\t4:退出\n");
    show(arr);
    printf("请输入要做什么功能:");
    scanf("%d", &a);
    switch (a)
    {
    case 1:
      printf("从那个位置开始插入:");
      scanf("%d", &i);
      arr = addArr(arr, arr1, i);
      show(arr);
      break;
    case 2:
      printf("请输入要删除的数:");
      scanf("%d", &i);
      arr = delete (arr, i);
      show(arr);
      break;
    case 3:
      printf("请输入待查找元素的位置:");
      scanf("%d", &i);
      find(arr, i);
      break;
    default:
      free(arr);
      arr = NULL;
      exit(0);
    }
  }

  free(arr);
  return 0;
}
/*向数组里添加值*/
int *addArr(int *p, int *arr1, int n)
{

  len1 = N;

  if (n <= len)
  {
    len += len1;
    p = (int *)realloc(p, (len1 + len) * sizeof(int));
    if (p == NULL)
    {
      exit(0);
    }
    for (int i = (len1 + len - 1), j = len - 1; j >= n - 1; i--, j--)
    {
      p[i] = p[j];
    }
    for (int i = n - 1, j = 0; j < N; i++, j++)
    {
      p[i] = arr1[j];
    }
  }
  else if (n >= len)
  {
    p = realloc(p, sizeof(int) * (len1 + len));
    if (p == NULL)
    {
      exit(0);
    }
    for (int i = len, j = 0; j < N; i++, j++)
    {
      p[i] = arr1[j];
    }
    len += len1;
  }

  return p;
}

int *delete (int *p, int n)
{
  int q;
  int i, j,k;
  for (i = 0; i < len; i++)
  {
    if (p[i] == n)
    {
      j = i;
      //break;
      if (j != i)
      {
        exit(0);
      }
      len = len - 1;
      // if (len == 0)
      // {
      //   p[0] = 0;
      //   p = NULL;
      //   return p;
      // }
      if(j == len)
      {
        p = realloc(p, sizeof(int) * (len));
        break;
      }
      q = p[len];
      
      p = realloc(p, sizeof(int) * (len));
      if (p == NULL)
      {
        exit(0);
      }
      for (k = j; k < len - 1; k++)
      {
        p[k] = p[k + 1];
      }
      p[k] = q;
      i = -1;
    }
    
  }

  return p;
}

void find(int *p, int n)
{
  if (n <= len)
  {
    printf("找到了是%d\n", p[n - 1]);
  }
  else
  {
    printf("没找到！！\n");
  }
}

void show(int *p)
{
  for (int i = 0; i < len; i++)
  {
    printf("%d ", p[i]);
  }
  printf("\n");
}
