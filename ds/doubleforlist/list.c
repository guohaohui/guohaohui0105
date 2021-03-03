#include <stdlib.h>
#include <string.h>
#include "list.h"

//  初始化头节点
int listInit(int size, listhead_t **l)
{
    listhead_t *p;
    p = malloc(sizeof(listhead_t));
    if(p == NULL)
        return -1;
    p->head.data = NULL;
    p->head.prev = &p->head;
    p->head.next = &p->head;
    p->nmemb = 0;
    p->size = size;

    *l = p;
    return 0;
}
// 插入
int listadd(listhead_t *l, const void *data, int key)
{
    node_t *p;
    node_t *n;

    p = malloc(sizeof(node_t));
    if(p == NULL)
        return -1;
    p->data = malloc(l->size);
    if(p->data == NULL){
        free(p);
        return -1;
    }
    memcpy(p->data, data, l->size);
    if(key == HEAD){
        p->prev = &l->head;
        p->next = l->head.next;
       // l->head.next = p;
    }else if(key == TALT) {
		//for(n = l->head.next; n->next != &l->head; n = n->next)
		//	;
		//n->next = p;
		//p->prev = n;
		p->prev = l->head.prev;
		p->next = &l->head;
		//l->head.prev = p;

	}
	p->prev->next = p;
	p->next->prev = p;
    l->nmemb ++;
    return 0;
}
// 遍历
void listprintf(const listhead_t *l, pri_t pri)
{
    node_t *p;
    for(p = l->head.next; p != &l->head; p = p->next)
    {
        pri(p->data);
    }
}

/*查找*/
const void *listSearch(const listhead_t *l, const void *key, cmp_t cmp)
{
    const node_t *cur;
    for(cur = l->head.next; cur != &l->head; cur = cur->next)
    {
        if(cmp(cur->data, key) == 0)
        {
            return cur;
        }
    }
    return NULL;
}

//  删除
int listDelete(listhead_t *l, const void *key, cmp_t cmp)
{
    node_t *cur = (node_t *)listSearch(l, key, cmp);
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    free(cur->data);
    free(cur);
}

/*摘除:删掉指定结点的同事获得数据*/
void *listFetch(listhead_t *l, const void *key, cmp_t cmp)
{
    node_t *cur = (node_t *)listSearch(l, key, cmp);
    void *p;
    p = malloc(l->size);
    if(p == NULL)
        return NULL;
    memcpy(p, cur->data, l->size);    
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    free(cur->data);
    free(cur);
    return p;
}

/*判断是否为空表*/
int listIsEmpty(const listhead_t *l) 
{
    node_t *p;
    int i = 0;
    for(p = l->head.next; p != &l->head ; p = p->next)
        i++;
    if(i == 0)
        return 0;
    return 1;
}

/*销毁*/
void listDestroy(listhead_t *l)
{
    node_t *p;
    for(p = l->head.next; ; p = p->next)
    {
        if(p == &l->head)
            break;
        free(p->data);
        free(p);
    }
    free(l);
}





