//3.现有一数组存储着杂乱无序的数据，要求按照从大到小的顺序排序，要求用给出的函数声明实现
#include <stdio.h>

void Arr_Sort(int Arrav_Val[], int Array_Size)
{
    int t,j,i;
    for(i = 1; i < Array_Size; i++)
    {
        t = Arrav_Val[i];
        for(j = i-1; j >= 0; j--)
        {
            if(t > Arrav_Val[j])
            {
                Arrav_Val[j+1] = Arrav_Val[j];
            }
            else
                break;
        }
        Arrav_Val[j+1] = t;
    }
}

int main()
{
    int arr[5] = {1,3,5,2,9};
    Arr_Sort(arr,sizeof(arr)/sizeof(*arr));
    for(int i = 0; i < sizeof(arr)/sizeof(*arr); i++)
    {
        printf("%d",arr[i]);
    }
    return 0;
}

