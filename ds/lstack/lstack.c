#include <stdio.h>
#include "lstack.h"


//	初始化

int lstackInit(int size, lstack_t **ls)
{
	return llisthead_init(size, ls);
}

//	入栈
int lstackPush(lstack_t *ls, const void *data)
{
	return llistInsert(ls, data, INSERTHEAD);
}
static int alwaysCmp(const void *data, const void *key)
{
	return 0;
}
//	出栈
int lstackChu(lstack_t *ls, void *data)
{
	return llistFetch(ls, NULL, alwaysCmp, data);
}

//	是否为空
int lstackIsEmpty(lstack_t *ls)
{
	return llistIsEmpty(ls);
}

//	销毁
void lstackDestroy(lstack_t *ls)
{
	listDestroy(ls);
}



