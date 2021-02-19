#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **store(int *n);
void comparison(char **p, int n);

int main()
{
    char **tmp;

    int i = 0;
    int k = 0;
    tmp = calloc(1, sizeof(char *));
    
    tmp = store(&k);
    comparison(tmp, k);
    for (i = 0; i < k; i++)
        free(tmp[i]);
    free(tmp);
    return 0;
}

void comparison(char **p, int n)
{
    int i;
    int k = 0;

    for (i = 1; i < n; i++)
    {
        if (strlen(p[i - 1]) < strlen(p[i]))
        {
            k = i;
        }
    }
    printf("%s\n", p[k]);
}

char **store(int* n)
{
    char **arr;
    char *a;
    int k = 0;
    a = calloc(1,sizeof(char *));
    arr = calloc(1, sizeof(char *));
    while (scanf("%s", a) == 1)
    {
        if (*a == '0')
            break;
        arr = realloc(arr, (k + 1) * sizeof(char *));
        arr[k] = malloc(strlen(a) + 1);
        strcpy(arr[k], a);
        k++;
    }
    *n = k;
    free(a);
    a = NULL;
    return arr;
}