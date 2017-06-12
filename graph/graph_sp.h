#ifndef GRAPH_SP_H_INCLUDED
#define GRAPH_SP_H_INCLUDED

#include <limits.h>

#include "graph_list.h"

struct Successore {
    int succ;     //indice del successore
    int dist;     //distanza calcolata dalla sorgente fino al nodo attuale
};
typedef struct Successore * SUCC;

int *graph_sp_DFS(GRAPHlist grafo_lista, int idx_src, int idx_dst);

void graph_sp_DFS_visit(GRAPHvrtx *vrtx, int idx_curr, int idx_src, int idx_dst, int *pred, int *dist, char *color, int isAscent);

int graph_sp_conditionElev(int height_curr, int height_adj, int isAscent, int height_src, int height_dst);

int graph_sp_path_print(GRAPHvrtx *vrtx, int idx_src, int idx_dst, int *pred);




#endif // GRAPH_LIST_H_INCLUDED
