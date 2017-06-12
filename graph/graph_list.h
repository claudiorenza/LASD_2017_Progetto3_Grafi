#ifndef GRAPH_LIST_H_INCLUDED
#define GRAPH_LIST_H_INCLUDED

#define MAX_graph 256
#define MAX_weight 20

#include <stdlib.h>
#include <math.h>

//#include "graph_sp.h"
#include "../io/io.h"
#include "../list/list.h"
#include "../queue/queue.h"



struct GrafoVertice    {
    int height;         //altezza del vertice
    LIST adj;           //lista degli elementi adiacenti 
};
typedef struct GrafoVertice * GRAPHvrtx;


struct GrafoLista   {
    int n_vrtx;         //numero di nodi del grafo
    int idx_max;        //indice massimo raggiunto
    GRAPHvrtx *vrtx;    //array dei vertici del grafo    
    LIST *heights;      //array delle altezze disponibili
    int dup;            //flag per la possibilità di inserimento di duplicati
};
typedef struct GrafoLista * GRAPHlist;


GRAPHlist graph_list_init();
void graph_list_dupEnabler(GRAPHlist grafo_lista);

void graph_list_insVertex(GRAPHlist grafo_lista, int idx, int height, int weight);

void graph_list_insArc(GRAPHlist grafo_lista, int idx_src, int idx_dst, int weight);

void graph_list_deleteGraph(GRAPHlist grafo_lista);

void graph_list_delVertex(GRAPHlist grafo_lista, int idx_del);
LIST graph_list_delVertex_undirectedArcs(GRAPHlist grafo_lista, LIST L_curr, int idx_del);

void graph_list_delArc(GRAPHlist grafo_lista, int idx_src);


void graph_list_path(GRAPHlist grafo_lista, int idx_src, int idx_dst, int mode);
void graph_list_path_print(GRAPHlist grafo_lista, int idx_src, int idx_dst, int *pred);

int *graph_list_BFS(GRAPHlist grafo_lista, int idx_src);

int *graph_list_DFS(GRAPHlist grafo_lista, int idx_src);
void graph_list_DFS_visit(GRAPHvrtx *vrtx, int idx_curr, int *pred, char *color);


void graph_list_print(GRAPHlist grafo_lista);
int graph_list_adjVisit(LIST L_curr, GRAPHvrtx *vrtx, GRAPHvrtx *vrtx_slave);

GRAPHvrtx *graph_list_vrtx_mirror(GRAPHlist grafo_lista);
void graph_list_vrtx_mirrorPrint(GRAPHvrtx *vrtx_slave, int idx_max);
void graph_list_vrtx_mirrorFree(GRAPHvrtx *vrtx_slave, int idx_max);


#endif // GRAPH_LIST_H_INCLUDED

