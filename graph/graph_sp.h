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

void graph_sp_DFS_visit(GRAPHvrtx *vrtx, int idx_curr, int idx_src, int idx_dst, int *pred, char *color, int isAscent);

int graph_sp_conditionElev(int height_curr, int height_adj, int isAscent, int height_src, int height_dst);

void graph_sp_calculate(GRAPHlist grafo_lista, int *pred, int idx_src, int idx_dst);

void graph_sp_calculate_visit(GRAPHvrtx *vrtx, int *pred, int idx_curr, SUCC *sp_succ_up, SUCC *sp_succ_down, int idx_src, int idx_dst, int isAscent, int *vrtx_visited);

void graph_sp_calculate_DFS_visit(GRAPHvrtx *vrtx, int *pred, int idx_curr, SUCC *sp_succ_up, SUCC *sp_succ_down, int idx_src, int idx_dst, int isAscent, int *vrtx_visited);

int graph_sp_conditionSucc_high(int heigth_curr, int heigth_adj, int isAscent);

int graph_sp_conditionSucc_low(int heigth_curr, int heigth_adj, int isAscent);

void graph_sp_printPath(GRAPHvrtx *vrtx, SUCC *sp_succ_up, SUCC *sp_succ_down, int idx_src, int idx_dst, int isAscent);



#endif // GRAPH_LIST_H_INCLUDED
