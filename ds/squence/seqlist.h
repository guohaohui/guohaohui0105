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

#define NEM 32
typedef struct 
{
    char name[NEM];
    int year;
    char phone[NEM];
    float a;
}student_t;

//比较函数，向函数内传待比较数的地址。
typedef int (*cmp_t)(const void *data, const void *key);
// 接口实现
/*
    初始化顺序表结构
*/
seqlist_t *seqlistInit(int size);//由用户来确定每个元素的字节个数

/*
增加新元素
*/
int seqlistInsert(seqlist_t *s, const void *data);//传一个结构体类型的指针，和一个任意类型数据的地址

// 遍历
//传一个结构体类型的指针，和一个打印函数
void seqlistTraval(const seqlist_t *s, void (*ptr)(const void *data));

//  查找
//传一个结构体类型的指针，一个要查找数据的地址，然后遍历顺序表让顺序表中的每个元素
//都和key放到比较函数中比较
void *seqlistFind(const seqlist_t *s, const void *key, cmp_t cmp);

//  删除
//和查找一样
int seqlistDelete(seqlist_t *s, const void *key, cmp_t cmp);

//  修改
//传一个结构体类型的指针，一个要修改元素的地址，比较函数和修改后数据的地址
int seqlistUpdate(const seqlist_t *s, const void *key, cmp_t cmp, const void *newdata);

//  销毁
void seqlistDestroy(seqlist_t *s);


#endif
