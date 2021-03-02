#ifndef __LINKLIST_H
#define __LINKLIST_H


typedef struct data
{
    void *data;
    struct data *next;
};

typedef struct head
{
    struct data *head;
    int size;
    int nmemb;
};


#endif