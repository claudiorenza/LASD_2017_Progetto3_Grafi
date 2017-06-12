#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct Lista    {
    int idx_vrtx_dst;
    int weight;
    struct Lista *next;
};
typedef struct Lista * LIST;    //elemento della lista

typedef struct GrafoVertice * GRAPHvrtx;

LIST list_newNode(int idx_vrtx_dst, int weight);

LIST list_insertHead(LIST lista, int idx_dst, int key);

LIST list_delete(LIST L_curr);

LIST list_delKey(LIST lista, int key);

int list_visit(LIST L_curr);

int list_visit_searchIdx(LIST L_curr, int idx);

#endif // LIST_H_INCLUDED
