#include "lstack1.h"
#include <stdlib.h>
#include <string.h>

//	初始化栈
int lstackInit(int size, int capacity, lstack_t **ls)
{
	*ls = malloc(sizeof(lstack_t));
	if(*ls == NULL)
		return -1;
	(*ls)->bottom = (*ls)->top = calloc(capacity, size);
	if(((*ls)->bottom == NULL))
	{
		free(*ls);
		return -1;
	}
	(*ls)->size = size;
	(*ls)->capacity = capacity;

	return 0;
}

//	判断栈是否为空
int lstackEmpty(lstack_t *ls)
{
	return ls->top == ls->bottom;
}

//	判断栈是否为满
int lstackFull(lstack_t *ls)
{
	return ((char *)ls->top - (char *)ls->bottom) / ls->size == ls->capacity;
}
//	入栈
int lstackPush(lstack_t *ls, void *data)
{
	if(lstackFull(ls))
		return -1;
	memcpy(ls->top , data, ls->size);
	ls->top = (char *)ls->top + ls->size;

	return 0;
}



//	出栈
int lstackPop(lstack_t *ls, void *data)
{
	if(lstackEmpty(ls))
		return -1;
	ls->top = (char *)ls->top - ls->size;
	memcpy(data, ls->top, ls->size);
	return 0;
}


// 销毁
int lstackDestory(lstack_t *ls)
{
	free(ls->bottom);
	free(ls);
}












