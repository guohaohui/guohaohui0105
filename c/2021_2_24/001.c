//1.有一组杂乱无章的数据存放在数组中,现在想要使数组中的数据降序排列,请完成功能
#include <stdio.h>
void sort(int *data_arr, int size);
int main()
{
    int arr[] = {1,6,9,4,8,3};
    sort(arr,sizeof(arr)/sizeof(*arr));
    for(int i = 0; i <sizeof(arr)/sizeof(*arr);i++)
        printf("%d",arr[i]);
    return 0;
}

void sort(int *data_arr, int size)
{
    int tmp;
    int i,j;
    for(i = 0; i < size-1; i++)
    {
        for(j = 0; j < size - i -1; j++)
        {
            if(data_arr[j] < data_arr[j + 1])
            {
                tmp = data_arr[j];
                data_arr[j] = data_arr[j+1];
                data_arr[j+1] = tmp;
            }
        }
    }
}



