#include "minHeap.h"

//Heapify
void minHeap_heapify(PRQUEUE coda, int idx)	{
	int idx_l, idx_r, idx_min;
	idx_l = minHeap_sinistro(idx);
	idx_r = minHeap_destro(idx);

	if (idx_l <= *(coda[0]) && *(coda[idx_l]) < *(coda[idx]))
		idx_min = idx_l;
	else
		idx_min = idx;

	if(idx_r <= *(coda[0]) && *(coda[idx_r]) < *(coda[idx_min]))
		idx_min = idx_r;

	if(idx_min != idx)	{
		minHeap_swap(coda, idx, idx_min);
		minHeap_heapify(coda, idx_min);
	}
}


//Ricavo l'indice del figlio sinistro
int minHeap_sinistro(int idx)	{
	return 2*idx;
}


//Ricavo l'indice del il figlio destro
int minHeap_destro(int idx)	{
	return 2*idx+1;
}


//Ricavo l'indice del padre
int minHeap_padre(int idx)	{
	return idx/2;
}


//Creazione dello Heap
void minHeap_buildHeap(PRQUEUE coda)	{
	int idx;
	for(idx=*(coda[0])/2; idx>0; idx--)
		minHeap_heapify(coda, idx);
}


//Swap dei riferimenti
void minHeap_swap(PRQUEUE coda, int idx_1, int idx_2) {
    int *tmp = coda[idx_2];
    coda[idx_2] = coda[idx_1];
    coda[idx_1] = tmp;
}
