#include <stdio.h>

#include "lstack.h"

int main(void)
{
	lstack_t *me;
	int n;

	lstackInit(sizeof(int), &me);

	for (int i = 1; i < 10; i++) {
		lstackPush(me, &i);
	}

	while (!lstackIsEmpty(me)) {
		lstackChu(me, &n);
		printf("%d\n", n);
	}

	lstackDestroy(me);

	return 0;
}

