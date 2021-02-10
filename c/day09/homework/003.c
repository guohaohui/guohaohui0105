#include<stdio.h>
#include<stdlib.h>

int main()
{
  int len;
  int i = 0;
  int *arr;
  int *new;
  int arr1[] = {90,80,2,4};
  printf("请确定数组长度:");

  if(scanf("%d", &len) != 1)
  {
    printf("没有输入任何数!\n");
    return 0;
  }
  
  //arr = (int *)malloc(sizeof(int)*len);
  if ((arr = (int *)malloc(len * sizeof(int))) == NULL)//if(arr = NULL)
  {
    printf("内存申请失败!!!\n");
    return 0;
  }
  printf("请给动态数组写入值\n");
  
     //arr[0] = 1;
    
 /*
  while(i < len && scanf("%d", &arr[i]) == 1)
  {
    ++i;
  }
  */
   for (i = 0; i < len; i++) /*向申请成功的数组中赋值*/
  {
    arr[i] = i + 1;
    printf("%d\t", arr[i]);
    if (0 == (i + 1) % 10)
      printf("\n"); /*一行打印四个元素*/
  }
  for(i = 0; i < sizeof(arr)/sizeof(*arr);i++)
  {
    printf("%d",arr[i]);
  }
  return 0;
}