#ifndef GRAPH_SP_H_INCLUDED
#define GRAPH_SP_H_INCLUDED

#include "graph_list.h"

struct Successore {
    int succ;     //indice del successore
    int dist;     //distanza calcolata dalla sorgente fino al nodo attuale
}
typedef struct Successore * SUCC;

int graph_sp_conditionElev(int idx, int idx_src, int idx_dst, LIST adj_curr, SUCC *path_SUCC)  {


#endif // GRAPH_LIST_H_INCLUDED
