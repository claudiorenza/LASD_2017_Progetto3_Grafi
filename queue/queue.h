#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MAX_queue 256

typedef int * QUEUE;

QUEUE queue_init();

int queue_isEmpty(QUEUE);

int queue_isFull(QUEUE);

void queue_enqueue(QUEUE, int);

int queue_dequeue(QUEUE);

void queue_delete(QUEUE coda);

void queue_print(QUEUE);
void queue_print_recv(QUEUE coda);

void queue_reverse(QUEUE coda);

#endif
