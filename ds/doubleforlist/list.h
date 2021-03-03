#ifndef __LIST_H
#define __LIST_H    

enum {HEAD,TALT};
//数据结点
typedef struct node_st {
    void *data;
    struct node_st *prev;
    struct node_st *next;
}node_t;


//  头节点
typedef struct {
    node_t head;
    int size;
    int nmemb;
}listhead_t;

typedef int (*cmp_t)(const void *data, const void *key);
typedef void (*pri_t)(const void *data);

//  初始化
int listInit(int size, listhead_t **l);

//  增加
int listadd(listhead_t *l, const void *data, int key);

//  遍历
void listprintf(const listhead_t *l, pri_t pri);

//  删除
int listDelete(listhead_t *l, const void *key, cmp_t cmp);

/*查找*/
const void *listSearch(const listhead_t *l, const void *key, cmp_t cmp);

/*摘除:删掉指定结点的同时获得数据*/
void *listFetch(listhead_t *l, const void *key, cmp_t cmp);

/*是否为空*/
int listIsEmpty(const listhead_t *l);

/*销毁*/
void listDestroy(listhead_t *l);

#endif