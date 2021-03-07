#ifndef __LSTACK_H
#define __LSTACK_H

#include <list.h>

typedef llisthead_t lstack_t;

//	初始化

int lstackInit(int size, lstack_t **ls);

//	入栈
int lstackPush(lstack_t *ls, const void *data);

//	出栈
int lstackChu(lstack_t *ls, void *data);

//	是否为空
int lstackIsEmpty(lstack_t *ls);

//	销毁
void lstackDestroy(lstack_t *ls);


#endif
