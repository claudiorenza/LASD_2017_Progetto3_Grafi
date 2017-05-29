#ifndef GRAPH_LIST_H_INCLUDED
#define GRAPH_LIST_H_INCLUDED

#define MAX_GRAPH 256

#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "../io/io.h"
#include "../list/list.h"
#include "../prQueue/prQueue.h"


struct GrafoLista   {
    int n_vrtx;    //numero di nodi del grafo
    struct  *adj;   //array delle liste di adiacenza, sfruttando l'indice come identificativo del vertice del grafo
};
typedef struct GrafoLista * GRAPHlistlist;


GRAPHlist graph_list_init(int idx_max);

void graph_list_insVertex(GRAPHlist grafo_list, int idx, void key);
GRAPHlistlist graph_list_newNode(void key, int idx);

void graph_list_insArc(GRAPHlist grafo_list, int idx_src, int idx_dst, int weight, int n_vrtx);

void graph_list_path(GRAPHlist grafo_list, int i_src, int j_dst);
int *graph_list_BFS(GRAPHlistlist *grafo_list, int i_src);
void graph_list_path_print(GRAPHlistlist *grafo_list, int i_src, int j, int *pred);

GRAPHlist graph_list_deleteGRAPHlist(GRAPHlist grafo_list);

int graph_list_delVertex(GRAPHlist grafo_list, int idx_del, int n_vrtx);
GRAPHlistlist graph_list_nodeFree(GRAPHlistlist G_curr);

void graph_list_delArc(GRAPHlist grafo_list, int idx_src);

GRAPHlist graph_list_convert(GRAPHlist grafo_list);

void graph_list_transpose(GRAPHlist grafo_list);

void graph_list_check_cycle(GRAPHlist grafo_list);
int graph_list_DFS(GRAPHlistlist *grafo_list, int i_src);
int graph_list_DFS_visit(GRAPHlistlist *grafo_list, int idx_curr, int *pred, char *color, int check_cycle);

void graph_list_print(GRAPHlist grafo_list, int showlist);

GRAPHlist graph_list_mirror(GRAPHlist grafo_list);
void graph_list_mirrorFree(GRAPHlist G_slave);


#endif // graph_LIST_H_INCLUDED

