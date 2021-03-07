#include "lstack1.h"
#include <stdlib.h>
#include <string.h>


//	初始化栈
int lstackInit(int size, lstack_t **ls)
{
	lstack_t *me;
	me = malloc(sizeof(*me));
	if(me == NULL)
		return -1;
	me->top = me->bottom = me->bottom;
	me->size = size;
	me->nmemb = 0;
	*ls = me;
	return 0;
}

//	入栈
int lstackPush(lstack_t *ls, const void *data)
{
	ls->bottom = realloc(ls->bottom, (ls->nmemb + 1) * ls->size);
	if(ls == NULL)
		return -1;
	memcpy((char *)ls->bottom + ls->nmemb * ls->size, data, ls->size);
	ls->nmemb ++;
	ls->top += ls->size;
	return 0;
}


//	判断栈是否为满,或空
int lstackFull(lstack_t *ls)
{
	if((((char *)ls->top - (char *)ls->bottom)/ls->size) == 0)
		return 0;
	if((((char *)ls->top - (char *)ls->bottom)/ls->size) == ls->nmemb)
		return 1;

	return -1;
}

//	出栈
int lstackPop(lstack_t *ls, void *data)
{
	if(lstackFull(ls))
	{
		memcpy(data, ls->top - ls->size, ls->size);
		ls->top = ls->top - ls->size;
		return 1;
	}
	return 0;
}


// 销毁
int lstackDestory(lstack_t *ls)
{
	free(ls);
}












