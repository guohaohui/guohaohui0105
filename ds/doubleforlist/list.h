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
int listadd(listhead_t *l, const void *data, cmp_t cmp, int key);

void listprintf(listhead_t *l, pri_t pri);

#endif