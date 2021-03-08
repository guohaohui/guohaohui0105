#include <stdlib.h>
#include <string.h>
#include "queue.h"

//初始化
int queueInit(int size, int capacity, queue_t **q)
{
	*q = malloc(sizeof(queue_t));
	if(*q == NULL)
		return -1;
	(*q)->base = calloc(capacity+1, size);
	if((*q)->base == NULL)
	{
		free(*q);
		return -1;
	}
	(*q)->front = (*q)->tail = 0;
	(*q)->size = size;
	(*q)->capacity = capacity;
	return 0;
}

//队空
int queueEmpty(const queue_t *q)
{
	return q->front == q->tail;
}

//队满
int queueFull(const queue_t *q)
{
	return q->front == ((q->tail + 1) % (q->capacity + 1));
}

//入队
int enq(queue_t *q, const void *data)
{
	if(queueFull(q))
		return -1;
	memcpy(q->base + q->tail*q->size, data,q->size);
	q->tail = (q->tail + 1) % (q->capacity + 1);
	return 0;
}

//出队
int deq(queue_t *q, void *data)
{
	if(queueEmpty(q))
		return -1;
	memcpy(data, q->base + q->front * q->size, q->size);
	q->front = (q->front + 1) % (q->capacity + 1);
	return 0;
}

//销毁
void queueDestroy(queue_t *q)
{
	free(q->base);
	free(q);
}

