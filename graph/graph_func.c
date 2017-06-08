#include "graph_func.h"


void graph_func_generate(GRAPHlist grafo_list, int dup) {
    int idx, n_elem;
    if(grafo_list->n_vrtx != 0)	{	//se è già presente, chiedo al'utente quale operazione effettuare sul grafo
        int choice;
        printf("ATTENZIONE: Grafo già presente. Cosa preferisci fare?\n\t1. Generazione nuovo Grafo\t2. Inserimento nuovi vertici\n\n");
        do  {
            printf("SCELTA: ");
            if((choice = io_getInteger()) < 1 || choice > 2)
                printf("ATTENZIONE: Valore non valido\n\n");
        }while(choice < 1 || choice > 2);
        if(choice == 1) {
            graph_list_deleteGraph(grafo_list);   //eliminazione completa del Grafo
            printf("\n");
            if(!(grafo_list->n_vrtx))
                printf("Grafo eliminato\n\n");
        }
    }
    
    do  {
        printf("Quanti elementi vuoi inserire nel Grafo? (1-%d): ", MAX_graph - grafo_list->n_vrtx);
        if((n_elem = io_getInteger()) < 1 || n_elem > MAX_graph - grafo_list->n_vrtx)
			printf("ATTENZIONE: Valore non valido\n\n");
	}while(n_elem < 1 || n_elem > MAX_graph - grafo_list->n_vrtx);

    for(idx=0;idx<n_elem;idx++)
        graph_list_insVertex(grafo_list, idx, -1, dup));	//inserisce un vertice assegnando un altezza casuale
    printf("\n");

    graph_func_print(grafo_list);
}

//Inserimento di un nuovo vertice nel grafo (già esistente)
void graph_func_insertKey(GRAPHlist grafo_list, int dup)	{
    graph_func_print(grafo_list);	//stampa dei nodi e degli archi adiacenti per il tipo di struttura associata

	if(grafo_list->n_vertex < MAX_graph) { //controllo il numero di vertici per aggiungerne nuovi
        printf("DEBUG: n_vertex: %d - MAX_graph: %d\n", grafo_list->n_vertex, MAX_graph);
		int height;
        
        do  {
            printf("Quale altezza vuoi applicare al vertice? (0-%d) ", MAX_graph-1);
            if((height = io_getInteger()) < 0 || height > MAX_graph-1)
                printf("ATTENZIONE: Valore non valido\n\n");
            else if(!dup && grafo_list->heights[height])    //se il Grafo non può avere due incroci posti alla stessa altezza
                printf("ATTENZIONE: altezza già presente nel grafo\n\n");
        }while((height < 0 || height > MAX_graph) || (!dup && grafo_list->heights[height]));

        graph_list_insVertex(grafo_list, -1, height, dup)      //se il peso è = 0, trattasi di inserimento manuale e non generazione randomica

        printf("\tGrafo aggiornato\n");
        graph_func_print(grafo_list);			//stampa dell'grafo aggiornato
	} else	//in caso di raggiungimento della capacità massima
		printf("ATTENZIONE: Capacità massima del Grafo raggiunta\n");
}


//Inserimento di un nuovo arco
void graph_func_insertEdge(GRAPHlist grafo_list)	{
	graph_func_print(grafo_list);	//stampa dei nodi e degli archi adiacenti per il tipo di struttura associata
	if(grafo_list->n_vertex > 1) {
        graph_list_insArc(grafo_list, graph_func_choiceVrtx(grafo_list, "sorgente"), -1, 0);     //3° param = -1: destinazione da scegliere; 4° param = 0: peso da scegliere
    } else
        printf("ATTENZIONE: nel grafo scelto è presente un solo vertice\n");
}


//Visualizzazione percorso minimo fra due vertici dati in BFS
void graph_func_BFS(GRAPHlist grafo_list)   {
    graph_func_print(grafo_list);

    if(grafo_list->n_vertex > 1) {
        graph_list_path(grafo_list, graph_func_choiceVrtx(grafo_list, "sorgente"), graph_func_choiceVrtx(grafo_list, "di destinazione"), 0);  //4° param = 0: BFS
    } else
        printf("ATTENZIONE: nel grafo scelto è presente un solo vertice\n");
}

//Visualizzazione del DFS
void graph_func_DFS(GRAPHlist grafo_list)   {
    graph_func_print(grafo_list);

    if(grafo_list->n_vertex > 1) {
        graph_list_path(grafo_list, graph_func_choiceVrtx(grafo_list, "sorgente"), graph_func_choiceVrtx(grafo_list, "di destinazione"), 1);   //4° param = 1: DFS
    } else
        printf("ATTENZIONE: nel grafo scelto è presente un solo vertice\n");
}


//Cancellazione del grafo
void graph_func_delete(GRAPHlist grafo_list)	{
    char confirm;
    do	{
        printf("Sei sicuro di voler eliminare il Grafo? (S/N): ");
        confirm = io_getChar();
        if(confirm == 's' || confirm == 'S')	{
            graph_list_deleteGraph(grafo_list);		//controllo ed eliminazione dell'grafo in caso di conferma
            if(!(grafo_list->n_vrtx))
                printf("Il Grafo è stato eliminato\n\n");
        } else if(confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N')
            printf("ATTENZIONE: Comando non valido\n\n");
    }while(confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N');
}


//Cancellazione di un vertice
void graph_func_delVertex(GRAPHlist grafo_list)	{
    graph_func_print(grafo_list);		//stampa dell'grafo per una consultazione del vertice da eliminare

    graph_list_delVertex(grafo_list, graph_func_choiceVrtx(grafo_list, "da eliminare")); 	//eliminazione del vertice o eliminazione del Grafo in caso di nodi cancellati
    if(!(grafo_list->n_vertex))
        printf("Il Grafo è stato eliminato\n\n");
    } else {
        printf("\tGrafo Aggiornato\n");
        graph_func_print(grafo_list);
    }
}


//Cancellazione di un arco
void graph_func_delEdge(GRAPHlist grafo_list)	{
    graph_func_print(grafo_list);		//stampa dell'grafo per una consultazione del vertice da eliminare
    
    graph_delArc(grafo_list, graph_func_choiceVrtx(grafo_list, "sorgente"));
    printf("\tGrafo %d di %s Aggiornato\n", idx+1);
    graph_func_print(grafo_list);
}


//FUNZIONE AUSILIARIA: Scelta del vertice disponibile del Grafo
int graph_func_choiceVrtx(GRAPHlist grafo_list, char *str)  {
    int idx_src;
    do  {
        printf("Scegli il vertice %s: ", str);
        if((idx_src = io_getInteger()) < 0 || idx_src > MAX_graph-1)
            printf("ATTENZIONE: valore non valido\n\n");
        else if(!(grafo_list->vrtx[idx_src]))
            printf("ATTENZIONE: vertice all'indice %d non presente\n\n", idx_src);
    }while((idx_src < 0 || idx_src > MAX_graph-1) || !(grafo_list->vrtx[idx_src]));

    return idx_src;
}

//Stampa del grafo
void graph_func_print(GRAPHlist grafo_list)	{
    graph_list_print(grafo_list, 1);    //2° param = 1: mostro la Lista di Adiacenza di ogni vertice presente
    printf("\t\tNumero di vertici: %d\n\n", grafo_list->n_vertex);   //e contemporaneamente visualizza il contatore del numero dei vertici per la visualizzazione in output
}


