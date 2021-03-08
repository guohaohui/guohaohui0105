#ifndef __QUEUE_H
#define __QUEUE_H

typedef struct {
	void *base;
	int front;//队头元素的下标
	int tail;//队尾元素的下标
	int size;
	int capacity;
}queue_t;

//初始化
int queueInit(int size, int capacity, queue_t **q);

//队空
int queueEmpty(const queue_t *q);

//队满
int queueFull(const queue_t *q);

//入队
int enq(queue_t *q, const void *data);

//出队
int deq(queue_t *q, void *data);

//销毁
void queueDestroy(queue_t *q);

#endif
