#ifndef GRAPH_LIST_H_INCLUDED
#define GRAPH_LIST_H_INCLUDED

#define MAX_graph 256

#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "../io/io.h"
#include "../list/list.h"
#include "../prQueue/prQueue.h"


struct GrafoLista   {
    int n_vrtx;    //numero di nodi del grafo
    int idx_max;    //indice massimo raggiunto
    LIST *adj;   //array delle liste di adiacenza, sfruttando l'indice come identificativo del vertice del grafo
};
typedef struct GrafoLista * GRAPHlist;


GRAPHlist graph_list_init(int idx_max);

void graph_list_insVertex(GRAPHlist grafo_list, int idx, void key);

void graph_list_insArc(GRAPHlist grafo_list, int idx_src, int idx_dst, int weight, int n_vrtx);

GRAPHlist graph_list_deleteGRAPHlist(GRAPHlist grafo_list);

void graph_list_delVertex(GRAPHlist grafo_list, int idx_del, int n_vrtx);
GRAPHlist graph_list_nodeFree(GRAPHlist G_curr);

void graph_list_delKey(GRAPHlist grafo_list, int idx_src);

void graph_list_transpose(GRAPHlist grafo_list);

void graph_list_path(GRAPHlist grafo_list, int i_src, int j_dst);
int *graph_list_BFS(GRAPHlist *grafo_list, int i_src);
void graph_list_path_print(GRAPHlist *grafo_list, int i_src, int j, int *pred);

void graph_list_check_cycle(GRAPHlist grafo_list);
int graph_list_DFS(GRAPHlist *grafo_list, int i_src);
int graph_list_DFS_visit(GRAPHlist *grafo_list, int idx_curr, int *pred, char *color, int check_cycle);

void graph_list_adj_print(LIST *grafo_list_adj, int idx_max, int showlist);

LIST *graph_list_adj_mirror(GRAPHlist grafo_list);
void graph_list_adj_mirrorFree(LIST *adj_slave, int idx_max);


#endif // graph_LIST_H_INCLUDED

