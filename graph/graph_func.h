#ifndef GRAPH_FUNC_H_INCLUDED
#define GRAPH_FUNC_H_INCLUDED

#include "graph.h"
#include "io.h"

typedef void (*FN_GRAPH_MENU) (GRAPHroot *, int, FTstructure *, FTdata *);

FN_GRAPH_MENU * init_fnType_menu_graph();

int graph_func_menu(GRAPHroot grafo_root, int idx);


void graph_func_insertKey(GRAPHroot grafo_root);

void graph_func_insertEdge(GRAPHroot grafo_root);

void graph_func_BFS(GRAPHroot grafo_root);

void graph_func_BFS(GRAPHroot grafo_root);

void graph_func_delete(GRAPHroot grafo_root);

void graph_func_delVertex(GRAPHroot grafo_root);

void graph_func_delEdge(GRAPHroot grafo_root);

void graph_func_transpose(GRAPHroot grafo_root);


int graph_func_choiceVrtx(GRAPH G, char *str);


void graph_func_print(GRAPHroot grafo_root, int idx);

char * graph_func_printTypeStruct(int typeStructure);

#endif // GRAPH_FUNC_H_INCLUDED
