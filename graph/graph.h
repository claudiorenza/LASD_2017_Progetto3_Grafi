#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "graph_mtrx.h"
#include "graph_list.h"

#include <stdio.h>

#define MAX_grafo_root 12


typedef void ** GRAPH;    //definizione di tipo a puntatore su struttura generica
            
struct RootGrafo {
    GRAPH grafo;            //puntatore al primo elemento del Grafo per una struttura dati generica
	int n_vertex;
    int grafo_typeStructure;
};
typedef struct RootGrafo * GRAPHroot;


GRAPHroot graph_init();

GRAPHroot graph_new();

GRAPHroot graph_free(GRAPHroot grafo_root);

#endif // GRAPH_H_INCLUDED
