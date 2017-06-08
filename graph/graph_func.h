#ifndef GRAPH_FUNC_H_INCLUDED
#define GRAPH_FUNC_H_INCLUDED

#include "io.h"

void graph_func_generate(GRAPHlist grafo_list, int dup);

void graph_func_insertKey(GRAPHlist grafo_list, int dup);

void graph_func_insertEdge(GRAPHlist grafo_list);

void graph_func_BFS(GRAPHlist grafo_list);

void graph_func_DFS(GRAPHlist grafo_list);

void graph_func_delete(GRAPHlist grafo_list);

void graph_func_delVertex(GRAPHlist grafo_list);

void graph_func_delEdge(GRAPHlist grafo_list);

int graph_func_choiceVrtx(GRAPHlist grafo_list, char *str);

void graph_func_print(GRAPHlist grafo_list, int idx);


#endif // GRAPH_FUNC_H_INCLUDED
