#ifndef __LIST_H
#define __LIST_H

enum {HEADINSERT, TAILINSERT};

//数据结点
typedef struct node_st{
    void *data; //   数据域首地址
    struct node_st *next;//指针域
}node_t;

// 头节点
typedef struct {
    //  struct node_st *next;
    node_t head;
    int size;
    int nmemb;
}listhead_t;

//比较函数
typedef int (*cmp_t)(const void *data, const void *key);
//打印函数
typedef void (*pri_t)(const void *data);

// 接口
/*
 初始化头结点
 */
// 传一个由用户决定的每个元素字节大小size,和一个结构体类型的指针的地址
int listheadInit(int size, listhead_t **l);

int daoxu(listhead_t *head);
/*
 增
 */
// 传一个结构体类型的指针，和待插入元素的地址，和插入模式(头插还是尾插)
int listInsert(listhead_t *l, const void *data, int way);

/*
 删除
 */
//
// 传一个结构体类型的指针，和待删除元素的地址，和比较函数
int listDelete(listhead_t *l, const void *key, cmp_t cmp);

/*
 遍历
 */

// 传一个结构体类型的指针和打印函数
void listTraval(const listhead_t *l, pri_t pri);

void listDestroy(listhead_t *l);


#endif
