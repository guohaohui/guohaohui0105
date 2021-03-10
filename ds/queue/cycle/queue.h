#ifndef __QUEUE_H
#define __QUEUE_H
//顺序表队列
typedef struct {
	void *base;//首地址
	int front;//队头元素的下标
	int tail;//队尾元素的下标
	int size;
	int capacity;//容量
}queue_t;

//初始化
//用户指定字节大小和容量大小
int queueInit(int size, int capacity, queue_t **q);

//队空
int queueEmpty(const queue_t *q);

//队满
int queueFull(const queue_t *q);

//入队
//传一个结构体类型的指针，和要入队元素的地址
int enq(queue_t *q, const void *data);

//出队
//传一个结构体类型的指针把出队的元素回填到data中
int deq(queue_t *q, void *data);

//销毁
void queueDestroy(queue_t *q);

#endif
