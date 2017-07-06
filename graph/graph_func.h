#ifndef GRAPH_FUNC_H_INCLUDED
#define GRAPH_FUNC_H_INCLUDED

#include "../io/io.h"
#include "graph_list.h"
#include "graph_sp.h"


void graph_func_load(GRAPHlist grafo_lista);

void graph_func_generate(GRAPHlist grafo_lista);

void graph_func_insertKey(GRAPHlist grafo_lista);

void graph_func_insertArc(GRAPHlist grafo_lista);

void graph_func_BFS(GRAPHlist grafo_lista);

void graph_func_DFS(GRAPHlist grafo_lista);

void graph_func_delete(GRAPHlist grafo_lista);

void graph_func_delVertex(GRAPHlist grafo_lista);

void graph_func_delEdge(GRAPHlist grafo_lista);

int graph_func_choiceVrtx(GRAPHlist grafo_lista, char *str);

void graph_func_print(GRAPHlist grafo_lista);

void graph_func_sp(GRAPHlist grafo_lista);


#endif // GRAPH_FUNC_H_INCLUDED
