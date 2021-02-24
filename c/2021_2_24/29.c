#include <stdio.h>

int do_dup(int a[], int N);
int main()
{
    int arr[6] = {4, 6, 9, 8, 6, 5};
    printf("%d\n",do_dup(arr,6));

    return 0;
}

int do_dup(int a[], int N)
{
    int i,j;
    for(i = 0;i < N;i++)
    {
        for(j = i+1;j < N; j++)
        {
            if(a[i] = a[j])
                return a[i];
        }
    }

}
