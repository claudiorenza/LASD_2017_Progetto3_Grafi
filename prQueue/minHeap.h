#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

typedef int ** PRQUEUE;
typedef int * PRQUEUEel;

void minHeap_heapify(PRQUEUE coda, int idx);

int minHeap_sinistro(int idx);

int minHeap_destro(int idx);

int minHeap_padre(int idx);

void minHeap_buildHeap(PRQUEUE coda);

void minHeap_swap(PRQUEUE coda, int idx_1, int idx_2);


#endif