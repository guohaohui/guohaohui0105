#ifndef __LIST_H
#define __LIST_H

enum {HEADINSERT, TAILINSERT};

//  数据结点
typedef struct node_st
{
    void *data; //  数据域首地址
    struct node_st *next;   //指向下一个结点的地址
}node_t;

//  头节点
typedef struct 
{
    struct node_st *next;   //指向下一个结点（下一个结点是struct node_st 类型的）
    int size;
    int nmemb;
}listhead_t;

typedef int (*cmp_t)(const void *data, const void *key);

typedef void (*pri_t)(const void *data);

//  接口
/*
    初始化头结点
*/
int listheadInit(int size, listhead_t **l);

/*
增
*/
int listInsert(listhead_t *l, const void *data, int way);

/*
删除
*/
int listDelete(listhead_t *l, const void *key, cmp_t cmp);

/*
修改
*/
int listUpdate(const listhead_t *l, const void *data, cmp_t cmp, const void *newdata);

/*
遍历
*/
void listTraval(const listhead_t *l, pri_t pri);

/*
销毁
*/
void listDestroy(listhead_t *l);

#endif