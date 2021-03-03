#include "list.h"
#include <stdlib.h>
#include <string.h>

int listheadInit(int size, listhead_t **l)
{
    listhead_t *h;

    h = malloc(sizeof(listhead_t));
    if(h == NULL)
        return -1;
    
    h->head.data = NULL;
    h->head.next = NULL;
    h->nmemb = 0;
    h->size = size;

    *l = h;

    return 0;
}

int listInsert(listhead_t *l, const void *data, int way)
{
    node_t *new;
    node_t *p;

    new = malloc(sizeof(node_t));
    if(new == NULL)
        return -1;
    new->data = malloc(l->size);
    if(NULL == new->data){
        free(new);
        return -1;
    }
    memcpy(new->data, data, l->size);
    if(way == HEADINSERT){
        new->next = l->head.next;
        l->head.next = new;
    }else if(way == TAILINSERT){
        for(p = l->head.next; p->next != NULL; p = p->next)
            ;
        p->next = new;
        new->next = NULL;
    }

    return 0;
}

// 返回待查找结点的前驱结点地址
static const node_t *findPrevNode(const listhead_t *l, const void *key, cmp_t cmp)
{
    const node_t *cur, *prev;

    for (prev = &l->head, cur = prev->next; cur != NULL; prev = cur, cur = cur->next){
        if(!(cmp(cur->data, key)))
            return prev;
    }

    return NULL;
}

int listDelete(listhead_t *l, const void *key, cmp_t cmp)
{
    node_t *cur;
    node_t *f = (node_t *)findPrevNode(l, key, cmp);
    if(f == NULL)
        return -1;
    cur = f->next;
    f->next = cur->next;
    cur->next = NULL;
    free(cur->data);
    free(cur);

    return 0;
}

void listTraval(const listhead_t *l, pri_t pri)
{
	node_t *p;

	for (p = l->head.next; p != NULL; p = p->next) {
		pri(p->data);
	}
}

/*
static void nodeDestroy(node_t **p)
{
	if ((*p)->next == NULL) {
		free(*p);
		*p = NULL;
	}

	nodeDestroy(&(*p)->next);
}

void listDestroy(listhead_t *l)
{
	nodeDestroy(&l->next);	
	free(l);
}
*/

void listDestroy(listhead_t *l)
{
	node_t *p, *n;

	for (p = l->head.next, n = p->next; ; n = n->next) {
		free(p);
		p = n;
		if (p == NULL)
			break;
	}

	free(l);
}

