#include <stdlib.h>
#include <string.h>
#include "list.h"

//头结点初始化
int llisthead_init(int size, llisthead_t **list)
{
	llisthead_t *l;
	l = malloc(sizeof(llisthead_t));
	if(l == NULL)
		return -1;
	l->node.data = NULL;
	l->node.prev = &l->node;
	l->node.next = &l->node;
	l->nmemb = 0;
	l->size = size;
	
	*list = l;	
	return 0;
}
/*
将新的结点插入到两个结点之间
 */
static void nodeInsert(node_t *new, node_t *pv, node_t *nt)
{
	new->next = nt;
	new->prev = pv;
	pv->next = new;
	nt->prev = new;
}

/*插入*/
int llistInsert(llisthead_t *list, const void *data, int way)
{
	node_t *cur;
	cur = malloc(sizeof(node_t));
	if(cur == NULL)
		return -1;
	cur->data = malloc(list->size);
	if(cur->data == NULL) {
		free(cur);
		return -1;
	}
	memcpy(cur->data, data, list->size);
	if(way == INSERTHEAD) {
		nodeInsert(cur, &list->node, list->node.next);
	} else if (way == INSERTTAIL) {
		nodeInsert(cur, list->node.prev, &list->node);
	} else {
		free(cur->data);
		free(cur);
		return -1;
	}
	return 0;
}

/*遍历*/
void llistTraval(const llisthead_t *list, pri_t pri)
{
	node_t *cur;
	for(cur = list->node.next; cur != &list->node; cur = cur->next)
			pri(cur->data);
}

static void nodeDelete(node_t *del)
{
	del->prev->next = del->next;
	del->next->prev = del->prev;
	free(del->data);
	free(del);
}

static node_t *nodeFind(const llisthead_t *list, const void *key, cmp_t cmp)
{
	node_t *cur;
	for(cur = list->node.next; cur != &list->node; cur = cur->next) {
		if(!cmp(cur->data, key)) {
			return cur;
		}
	}
	return NULL;
}

/*删除*/
int llistDelete(llisthead_t *list, const void *key, cmp_t cmp)
{
	node_t *cur = nodeFind(list, key, cmp);
	if(cur == NULL)
		return -1;
	nodeDelete(cur);
	return 0;
}

/*查找*/
void  *llistSearch(const llisthead_t *list, const void *key, cmp_t cmp)
{
	node_t *cur = nodeFind(list, key, cmp);
	if(cur == NULL)
		return NULL;
	return cur->data;
}

/*摘除：删掉指定结点的同时获得数据*/
int llistFetch(llisthead_t *list, const void *key, cmp_t cmp, void *data)
{
	node_t *cur = nodeFind(list , key, cmp);
	if(cur == NULL)
		return -1;
	memcpy(data, cur->data, list->size);
	nodeDelete(cur);
	return 0;
}

/*是否为空*/
int llistIsEmpty(const llisthead_t *list)
{
	return list->node.next == &list->node && list->node.prev == &list->node;
}

/*销毁*/
void listDestroy(llisthead_t *list)
{
	node_t *cur;
	if(!llistIsEmpty(list)) {
		for(cur = (list->node.next)->next; ;cur = cur->next) {
			free(cur->prev);
			if(cur == &list->node)
				break;
		}
	}
	free(list);
}









