#ifndef GRAPH_LIST_H_INCLUDED
#define GRAPH_LIST_H_INCLUDED

#define MAX_graph 256

#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "../io/io.h"
#include "../list/list.h"
#include "../prQueue/prQueue.h"


struct GrafoVertice    {
    int height; //altezza del vertice
    LIST adj;   //lista degli elementi adiacenti 
}
typedef struct GrafoVertice * GRAPHvrtx


struct GrafoLista   {
    int n_vrtx;    //numero di nodi del grafo
    int idx_max;    //indice massimo raggiunto
    LIST *heights; //array delle altezze disponibili
    struct GRAPHvrtx *vrtx;   //array dei vertici del grafo
};
typedef struct GrafoLista * GRAPHlist;


struct Predecessore {
    int pred;     //indice del predecessore
    int dist;     //distanza calcolata dalla sorgente fino al nodo attuale
}
typedef struct Predecessore * PRED;

GRAPHlist graph_list_init(int idx_max);

void graph_list_insVertex(GRAPHlist grafo_list, int idx, void key);

void graph_list_insArc(GRAPHlist grafo_list, int idx_src, int idx_dst);

GRAPHlist graph_list_deleteGRAPHlist(GRAPHlist grafo_list);

void graph_list_delVertex(GRAPHlist grafo_list, int idx_del, int n_vrtx);
GRAPHlist graph_list_nodeFree(GRAPHlist G_curr);

void graph_list_delKey(GRAPHlist grafo_list, int idx_src);

void graph_list_transpose(GRAPHlist grafo_list);

void graph_list_path(GRAPHlist grafo_list, int idx_src, int idx_dst);
int *graph_list_BFS(GRAPHlist grafo_list, int idx_src);

int graph_list_conditionAdj(int idx, int idx_src, int idx_dst, LIST adj_curr, PRED *bfs_pred);

void graph_list_path_print(GRAPHlist grafo_list, int idx_src, int idx_dst, int *pred);

/*
void graph_list_check_cycle(GRAPHlist grafo_list);
int graph_list_DFS(GRAPHlist grafo_list, int idx_src);
int graph_list_DFS_visit(GRAPHlist grafo_list, int idx_curr, int *pred, char *color, int check_cycle);
*/

void graph_list_adj_print(LIST *grafo_list_adj, int idx_max, int showlist);

LIST *graph_list_adj_mirror(GRAPHlist grafo_list);
void graph_list_adj_mirrorFree(LIST *adj_slave, int idx_max);


#endif // graph_LIST_H_INCLUDED

