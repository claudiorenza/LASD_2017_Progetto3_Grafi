#ifndef GRAPH_LIST_H_INCLUDED
#define GRAPH_LIST_H_INCLUDED

#define MAX_graph 256

#include <stdlib.h>
#include <math.h>

#include "graph_sp.h"
#include "../io/io.h"
#include "../list/list.h"
#include "../queue/queue.h"


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


GRAPHlist graph_list_init();

void graph_list_insVertex(GRAPHlist grafo_list, int idx, int height, int dup);

void graph_list_insArc(GRAPHlist grafo_list, int idx_src, int idx_dst, int weight);

void graph_list_deleteGraph(GRAPHlist grafo_list);

void graph_list_delVertex(GRAPHlist grafo_list, int idx_del);
LIST graph_list_delVertex_undirectedArcs(GRAPHlist grafo_list, LIST L_curr, int idx_del);

void graph_list_delArc(GRAPHlist grafo_list, int idx_src);


void graph_list_path(GRAPHlist grafo_list, int idx_src, int idx_dst);
void graph_list_path_print(GRAPHlist grafo_list, int idx_src, int idx_dst, int *pred);

int *graph_list_BFS(GRAPHlist grafo_list, int idx_src);

int *graph_list_DFS(GRAPHlist grafo_list, int idx_src);
void graph_list_DFS_visit(GRAPHlist grafo_list, int idx_curr, int *pred, char *color);


void grafo_list_print(GRAPHlist grafo_list, int showlist);

LIST *graph_list_adj_mirror(GRAPHlist grafo_list);
void graph_list_adj_mirrorFree(LIST *adj_slave, int idx_max);


#endif // GRAPH_LIST_H_INCLUDED

