#ifndef __LLIST_H
#define __LLIST_H

enum {INSERTHEAD, INSERTTAIL};

//数据结点
typedef struct node_st {
	void *data; //	数据域地址
	struct node_st *prev; //前驱
	struct node_st *next; //后继
}node_t;

//头结点
typedef struct {
	node_t node;
	int nmemb;
	int size;
}llisthead_t;

typedef void (*pri_t)(const void *);//打印函数
typedef int (*cmp_t)(const void *data, const void *key);//比较函数

//头结点初始化
// 传一个由用户决定的每个元素字节大小size,和一个结构体类型的指针的地址
int llisthead_init(int size, llisthead_t **list);

/*插入*/
// 传一个结构体类型的指针，和待插入元素的地址，和插入模式(头插还是尾插)
int llistInsert(llisthead_t *list, const void *data, int way);

/*遍历*/
// 传一个结构体类型的指针和打印函数
void llistTraval(const llisthead_t *list, pri_t pri);

/*删除*/
// 传一个结构体类型的指针，和待删除元素的地址，和比较函数
int llistDelete(llisthead_t *list, const void *key, cmp_t cmp);

/*查找*/
// 传一个结构体类型的指针，和要查找元素的地址，和比较函数
void *llistSearch(const llisthead_t *list, const void *key, cmp_t cmp);

/*摘除：删掉指定结点的同时获得数据*/
// 传一个结构体类型的指针，和要摘除元素的地址，和比较函数，和一个任意类型的变量的地址。
int llistFetch(llisthead_t *list, const void *key, cmp_t cmp, void *data);

/*是否为空*/
int llistIsEmpty(const llisthead_t *list);// 传一个结构体类型的指针

/*销毁*/
void listDestroy(llisthead_t *list);// 传一个结构体类型的指针



#endif
