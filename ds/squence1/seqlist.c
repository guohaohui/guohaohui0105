#include <string.h>
#include <stdlib.h>
#include "seqlist.h"

seqlist_t *seqlistInit(int size)
{
    seqlist_t *s;
    s = malloc(sizeof(seqlist_t));
    if(s == NULL)
        return NULL;
    s->arr = NULL;
    s->nmemb = 0;
    s->size = size;
    return s;
}

int seqlistInsert(seqlist_t *s, const void *data)
{
    s->arr = realloc(s->arr, (s->nmemb +1)*s->size);
    if(s->arr == NULL)
        return -1;
    memcpy((char *)s->arr + s->nmemb * s->size, data, s->size);
    s->nmemb ++;
    return 0;
}

void seqlistTraval(const seqlist_t *s, void (*ptr)(const void *data))
{
    for(int i = 0; i < s->nmemb; i++)
    {
        ptr((char *)s->arr + i * s->size);
    }


}
// 查找
void *seqlistFind(const seqlist_t *s, const void *key, cmp_t cmp)
{
    for(int i = 0; i < s->nmemb; i++)
    {
        if(cmp((char *)s->arr + i * s->size, key) == 0)
        {
            return (char *)s->arr + i * s->size;
        }
    }

    return NULL;
}

//  删除

int seqlistDelete(seqlist_t *s, const void *key, cmp_t cmp)
{
    int i;
    for(i = 0; i < s->nmemb; i++)
    {
        if(cmp((char *)s->arr + i * s->size, key) == 0)
        {
            memcpy((char *)s->arr + i * s->size,(char *)s->arr + (i+1) * s->size,(s->nmemb - i) * s->size);
            break;
        }
    }
    if(i == s->nmemb)
        return -1;
    s->nmemb --;
    s->arr = realloc(s->arr, s->nmemb * s->size);

    return 0;
}

//  修改

int seqlistUpdate(const seqlist_t *s, const void *key, cmp_t cmp, const void *newdata)
{
    int i;
    for(i = 0; i < s->nmemb; i++)
    {
        if(cmp((char *)s->arr + i * s->size, key) == 0)
        {
            memcpy((char *)s->arr + i * s->size, (char *)newdata, s->size * sizeof(char));
            break;
        }
    }
    if(i == s->nmemb)
        return -1;
    return 0;
}

//  销毁
void seqlistDestroy(seqlist_t *s)
{
    free(s->arr);
    s->arr = NULL;
    free(s);
    s = NULL;
}
