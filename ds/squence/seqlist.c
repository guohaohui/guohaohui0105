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
        if(cmp(s->arr + i * s->size, key) == 0)
        {
            return s->arr + i * s->size;
        }
    }
}