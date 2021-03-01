#ifndef __SEQLIST_H
#define __SEQLIST_H

//抽象数据类型
// 顺序表
typedef struct 
{
    void *arr; // 存储数据的首地址
    int size; //每一个元素所占字节个数
    int nmemb; // 结构中拥有的成员个数
}seqlist_t;

// 接口实现
/*
    初始化顺序表结构
*/
seqlist_t *seqlistInit(int size);

/*
增加新元素
*/
int seqlistInsert(seqlist_t *s, const void *data);

// 遍历

void seqlistTraval(const seqlist_t *s, void (*ptr)(const void *data));

#endif