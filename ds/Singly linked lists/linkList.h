#ifndef __LINKLIST_H
#define __LINKLIST_H

//  数据结点
typedef struct nose_st
{
    void *data; //  数据域首地址
    struct node_st *next;   //指向下一个数据结点的地址
}node_t;

//  头节点
typedef struct 
{
    struct node_st *next;   //指向下一个结点（下一个结点是struct node_st 类型的）
    int size;
    int nmemb;
}listhead_t;


#endif