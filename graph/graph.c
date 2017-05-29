#include "graph.h"

//Inizializzazione struttura array generica
GRAPHroot graph_init()	{
	GRAPHroot grafo_root = NULL;
	if(!(grafo_root = (struct RootGrafo *)malloc(MAX_grafo_root*sizeof(struct RootGrafo)))) //ogni elemento dell'array punter� ad un grafo
        printf("[MEM] ATTENZIONE: Problema di allocazione GRAPHroot * - graph_init\n");
	int idx;
	
	return grafo_root;
}

//Creo il nuovo Grafo stabilendo la struttura dati e il tipo di dato
void graph_new(GRAPHroot grafo_root)  {
    do {
        printf("Scegli la struttura dati del Grafo\n1. Matrice di Adiacenza\t\t2. Lista di Adiacenza: ");
        ;
        if((grafo_root->grafo_typeStructure = io_getInteger()) < 1 || grafo_root->grafo_typeStructure > 2)
            printf("ATTENZIONE: Valore non valido\n\n");
    }while(grafo_root->grafo_typeStructure < 1 || grafo_root->grafo_typeStructure > 2);
    grafo_root->n_vertex = 0;
    
    if(grafo_root->grafo_typeStructure == 1)    {
        grafo_root->grafo = graph_mtrx_init(0);
    } else if(grafo_root->grafo_typeStructure == 2) {
        grafo_root->grafo = graph_list_init(0);
    }
}


//Liberazione della memoria allocata dinamicamente del nodo
GRAPHroot graph_free(GRAPHroot grafo_root)	{
	free(grafo_root->G);
	free(grafo_root);
	return NULL;
}