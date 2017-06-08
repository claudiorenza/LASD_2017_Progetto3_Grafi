#ifndef GRAPH_SP_H_INCLUDED
#define GRAPH_SP_H_INCLUDED

#include "graph_list.h"

struct Predecessore {
    int pred;     //indice del predecessore
    int dist;     //distanza calcolata dalla sorgente fino al nodo attuale
}
typedef struct Predecessore PRED;

int graph_sp_conditionAdj(int idx, int idx_src, int idx_dst, LIST adj_curr, PRED *path_pred)  {


#endif // GRAPH_LIST_H_INCLUDED
