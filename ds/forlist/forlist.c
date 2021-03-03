#include "forlist.h"
#include <stdlib.h>
#include <string.h>

//  初始化头节点
int listInit(int size, listhead_t **l)
{
    listhead_t *p;
    p = malloc(sizeof(listhead_t));
    if(p == NULL)
        return -1;
    p->head.data = NULL;
    p->head.next = &p->head;
    p->nmemb = 0;
    p->size = size;

    *l = p;
    return 0;
}

//  增加
int listadd(listhead_t *l, const void *data, cmp_t cmp, int key)
{
    node_t *p;
    node_t *n;
    p = malloc(sizeof(node_t));
    if(p == NULL)
        return -1;
    p->data = malloc(l->size);
    if (p->data == NULL){
        free(p);
        return -1;
    }
    memcpy(p->data, data, l->size);
    if(key == HEAD){
        p->next = l->head.next;
        l->head.next = p;
    }else if (key == TAIL) {
        for(n = l->head.next; n != &l->head; n = n->next)
            ;
        n->next = p;
        p->next = &l->head;
    }
    l->nmemb ++;
    return 0;
}

//  遍历
void listprintf(listhead_t *l, pri_t pri)
{
    node_t *p;
    for(p = l->head.next; p != &l->head; p = p->next) {
        pri(p->data);
    }
}
