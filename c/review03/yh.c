#include <stdio.h>
int triangle(int row, int col);
int main()
{
    int n;
    printf("请输入要打印多少行:");
    //scanf("%d", &n);
    for(int row = 0; row < 5; row++)
    {
        for(int col = 0; col <= row; col++)
        {
            printf("%d ",triangle(row,col));
        }
        printf("\n");
    }
}

int triangle(int row, int col)
{
    if(row < 2 || row == col || col == 0)
        return 1;
    else
    {
        return triangle(row-1,col-1) + triangle(row-1,col);
    }

}
