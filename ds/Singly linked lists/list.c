#include "list.h"
#include <stdlib.h>
#include <string.h>

/*初始化头节点*/
int listheadInit(int size, listhead_t **l)
{
    listhead_t *h;

    h = malloc(sizeof(listhead_t));
    if(h == NULL)
        return -1;
    h->next = NULL;
    h->nmemb = 0;
    h->size = size;

    *l = h;
    return 0;
}

/*
增
*/
int listInsert(listhead_t *l, const void *data, int way)
{
    node_t *new;
    node_t *p;

    new = malloc(sizeof(node_t));
    if(new == NULL)
        return -1;
    new->data = malloc(l->size);
    if(new->data == NULL)
    {
        free(new);
        return -1;
    }
    memcpy(new->data, data , l->size);
    if(way == HEADINSERT)
    {
        new->next = l->next;
        l->next = new;
    }
    else if(way == TAILINSERT)
    {
        for(p = l->next; p->next != NULL; p = p->next)
            ;
        p->next = new;
        new->next = NULL;
    }

    return 0;
}
/*
打印
*/
void listTraval(const listhead_t *l, pri_t pri)
{
    node_t *p;
    for(p = l->next; p != NULL; p = p->next)
        pri(p->data);
}

/*
删除
*/
int listDelete(listhead_t *l, const void *key, cmp_t cmp)
{
    node_t *p , *n;
    for(p = l->next; p != NULL; p = p->next)
    {
        if(cmp(p->data, key) == 0)//如果删除的是第一个元素
        {
            n = p;
            l->next = p->next;
            n->next = NULL;
            free(n->data);
            free(n);
            return 1;
        }
        else if(cmp(p->next->data, key) == 0)//遍历到要删除结点的前一个结点
        {
            n = p->next;
            p->next = n->next;
            n->next = NULL;
            free(n->data);
            free(n);
            return 1;
        }
    }
    return 0;
}

/*
修改
*/
int listUpdate(const listhead_t *l, const void *data, cmp_t cmp, const void *newdata)
{
    node_t *p;
    
    for(p = l->next; p != NULL; p = p->next)
    {
        if(cmp(p->data, data) == 0)
        {
            memcpy(p->data,(char *)newdata, l->size);
            return 1;
        }
    }
    return 0;
}



// 销毁
void listDestroy(listhead_t *l)
{
    node_t *p, *n;

    for(p = l->next, n = p->next; ; n = n->next)
    {
        free(p);
        p = n;
        if(p == NULL)
            break;
    }
    free(l);
}





