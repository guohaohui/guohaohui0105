#include <stdio.h>
#include <lstack1.h>
#include <queue.h>

void outStack(queue_t *q, lstack_t *s, int  *pop)
{
	while(!lstackEmpty(s)) {
		lstackPop(s, pop);
		enq(q,pop);
	}

}

static int ballSeq(queue_t *ball)
{
	queue_t *tmp;
	int cur, next;
	int ret = 1;

	queueInit(sizeof(int), 27, &tmp);

	deq(ball, &cur);
	while(!queueEmpty(ball)) {
		enq(tmp, &cur);
		deq(ball, &next);
		if(next < cur)
			ret = 0;
		cur = next;
	}
	enq(tmp, &cur);
	
	while(!queueEmpty(tmp)) {
		deq(tmp, &cur);
		enq(ball, &cur);
	}

	queueDestroy(tmp);

	return ret;
}

int main(void)
{
	queue_t *ball;
	lstack_t *oneMin;
	lstack_t *fiveMin;
	lstack_t *oneHour;

	int out, pop;
	int days = 0;

	queueInit(sizeof(int), 27, &ball);
	lstackInit(sizeof(int), 4, &oneMin);
	lstackInit(sizeof(int), 11, &fiveMin);
	lstackInit(sizeof(int), 11, &oneHour);

	for(int i = 1; i <= 27; i++) {
		enq(ball, &i);
	}


	while(1) {
		deq(ball, &out);
		if(!lstackFull(oneMin)) {
			lstackPush(oneMin, &out);
		} else {
			outStack(ball, oneMin, &pop);
			if(!lstackFull(fiveMin)) {
				lstackPush(fiveMin, &out);
			} else {
				outStack(ball, fiveMin, &pop);
				if(!lstackFull(oneHour)) {
					lstackPush(oneHour, &out);
				} else {
					outStack(ball, oneHour, &pop);
					enq(ball, &out);
					//12小时一天
					days++;
					if(ballSeq(ball))
						break;
				}
			}
		}
		
	}

	printf("经过%d天球的次序有序了\n", days);
	return 0;
}
