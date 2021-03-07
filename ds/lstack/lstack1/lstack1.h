#ifndef __LSTACK1_H
#define __LSTACK1_H

typedef struct lstack_st
{
	void *bottom;
	void *top;
	int size;
	int nmemb;
}lstack_t;

//	初始化栈
int lstackInit(int size, lstack_t **ls);

//	入栈
int lstackPush(lstack_t *ls, const void *data);

//	出栈
int lstackPop(lstack_t *ls, void *data);

//	判断栈是否为满,或空
int lstackFull(lstack_t *ls);

// 销毁
int lstackDestory(lstack_t *ls);



#endif
