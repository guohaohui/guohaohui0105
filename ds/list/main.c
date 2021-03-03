#include <stdio.h>

#include "list.h"

static void showInt(const void *data)
{
	const int *d = data;

	printf("%d\n", *d);
}

static int cmpInt(const void *data, const void *key)
{
	const int *d = data;
	const int *k = key;

	return *d - *k;
}

int main(void)
{
	int arr[] = {3,1,6,7,8,9,4};
	listhead_t *head;
	int del;

	listheadInit(sizeof(int), &head);

	for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		listInsert(head, arr+i, HEADINSERT);
	}

	listTraval(head, showInt);

	printf("*****************delete******************\n");
	del = 3;
	listDelete(head, &del, cmpInt);
	listTraval(head, showInt);

	listDestroy(head);

	return 0;
}

