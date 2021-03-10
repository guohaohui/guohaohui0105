#ifndef __LSTACK1_H
#define __LSTACK1_H
//顺序表栈
typedef struct lstack_st
{
	void *bottom;
	void *top;
	int size;
	int capacity;
}lstack_t;

//	初始化栈
//用户指定字节大小和容量大小
int lstackInit(int size,int capacity, lstack_t **ls);

//	入栈
//传一个结构体类型的指针，和一个要入栈元素的地址
int lstackPush(lstack_t *ls, const void *data);

//	出栈
//传一个结构体类型的指针，把要出栈的元素回填到data里
int lstackPop(lstack_t *ls, void *data);

//	判断栈是否为空
int lstackEmpty(lstack_t *ls);
//	判断栈是否为满
int lstackFull(lstack_t *ls);


// 销毁
int lstackDestory(lstack_t *ls);



#endif
