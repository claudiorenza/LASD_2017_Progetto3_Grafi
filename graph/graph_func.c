#include "graph_menu.h"

//interfaccia utente
int graph_func_menu(GRAPHroot grafo_root, int idx)	{
	int choiceMenu;
	printf("\t\t\tLibreria - Grafi - MEN\xEB PRINCIPALE\n");
    if(grafo_root->grafo)
        printf("\t\t\t\t\t\t\t\t\tStruttura del grafo: %s\n", graph_func_printTypeStruct(grafo_root->grafo_typeStructure);

	printf("1. Genera un Grafo\n");
	printf("2. Inserisci un nuovo vertice\n");
    if(grafo_root->grafo) {
        printf("3. Inserisci un nuovo arco\n"); //controllo archi disponibili (controllo vertici adiacenti)
        printf("4. Visualizza il grafo\n");
        printf("5. Visita il Grafo in BFS\n");
        printf("6. Visita il Grafo in DFS\n");
        printf("7. Cancella il grafo\n");
        printf("8. Cancella un vertice\n");
        printf("9. Cancella un arco\n");
        printf("10. Calcola un grafo trasposto\n");
    }
    printf("\n");
	printf("11. Esci\n");
	printf("\n\n");

	do {
		printf("SCELTA: ");
		if(((choiceMenu = io_getInteger()) < 1 || choiceMenu > 11) || (!grafo_root && (choiceMenu > 3 && choiceMenu < 11)))
			printf("ATTENZIONE: Valore non valido\n\n");
	}while((choiceMenu < 1 || choiceMenu > 11) || (!grafo_root && (choiceMenu > 3 && choiceMenu < 11)));
	system("cls");
	return choiceMenu;
}


//Inserimento di un nuovo vertice nel grafo (già esistente)
void graph_func_insertKey(GRAPHroot grafo_root)	{
    if(!grafo_root)    //nel caso di inserimento di un vertice in un grafo non presente
        grafo_root = graph_new();

    graph_func_print(grafo_root);	//stampa dei nodi e degli archi adiacenti per il tipo di struttura associata

	if(grafo_root->n_vertex < MAX_graph) { //controllo il numero di vertici per aggiungerne nuovi
        printf("DEBUG: n_vertex: %d - MAX_graph: %d\n", grafo_root->n_vertex, MAX_graph);
		int key;
        //
        //
        //(grafo_root->n_vertex)++;
        printf("\tGrafo aggiornato\n");
        graph_func_print(grafo_root);			//stampa dell'grafo aggiornato
	}
	else	//in caso di raggiungimento della capacità massima
		printf("ATTENZIONE: Capacità massima del grafo raggiunta\n");
}


//Inserimento di un nuovo arco
void graph_func_insertEdge(GRAPHroot grafo_root)	{
	graph_func_print(grafo_root);	//stampa dei nodi e degli archi adiacenti per il tipo di struttura associata
	if(grafo_root->n_vertex > 1) {
        graph_insArc(grafo_root->G, graph_func_choiceVrtx(grafo_root->G, "sorgente"), 0, 0, grafo_root->fnTypeData->Print, (grafo_root->n_vertex)-1);		//inserimento nella Grafo  all'interno della specifica struttura dati, con ritorno del nuovo n_vertex
    } else
        printf("ATTENZIONE: nel grafo scelto è presente un solo vertice\n");
}


//Visualizzazione percorso minimo fra due vertici dati in BFS
void graph_func_BFS(GRAPHroot grafo_root)   {
    graph_func_print(grafo_root);

    if(grafo_root->n_vertex > 1) {
        graph_path(grafo_root->G, graph_func_choiceVrtx(grafo_root->G, "sorgente"), graph_func_choiceVrtx(grafo_root->G, "di destinazione"), grafo_root->fnTypeData->Print);		//inserimento nella Grafo  all'interno della specifica struttura dati, con ritorno del nuovo n_vertex
    } else
        printf("ATTENZIONE: nel grafo scelto (�) presente un solo vertice\n");
}

//Visualizzazione del DFS
void graph_func_DFS(GRAPHroot grafo_root)   {
    graph_func_print(grafo_root);

    if(grafo_root->n_vertex > 1) {
        graph_path(grafo_root->G, graph_func_choiceVrtx(grafo_root->G, "sorgente"), graph_func_choiceVrtx(grafo_root->G, "di destinazione"), grafo_root->fnTypeData->Print);		//inserimento nella Grafo  all'interno della specifica struttura dati, con ritorno del nuovo n_vertex
    } else
        printf("ATTENZIONE: nel grafo scelto (�) presente un solo vertice\n");
}



//Cancellazione del grafo
void graph_func_delete(GRAPHroot grafo_root)	{
    char confirm;
    do	{
        printf("Sei sicuro di voler eliminare il grafo %d? (S/N): ", idx+1);
        confirm = io_getChar();
        if(confirm == 's' || confirm == 'S')	{
            if(!(grafo_root->G = graph_deleteGraph(grafo_root->G)))	{	//controllo ed eliminazione dell'grafo in caso di conferma
                grafo_root = graph_free(grafo_root);    //rimetto a disposizione l'elemento della grafo_roota/array per la creazione della nuova Grafo
                printf("Il grafo %d \x8A stato eliminato\n\n", idx+1);
            } else
                printf("ATTENZIONE: Errore durante l'eliminazione del grafo %d\n\n", idx+1);
        } else if(confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N')
            printf("ATTENZIONE: Comando non valido\n\n");
    }while(confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N');
}


//Cancellazione di un vertice
void graph_func_delVertex(GRAPHroot grafo_root)	{
    graph_func_print(grafo_root);		//stampa dell'grafo per una consultazione del vertice da eliminare

    if(!(grafo_root->n_vertex = graph_delVertex(grafo_root->G, graph_func_choiceVrtx(grafo_root->G, "da eliminare"), grafo_root->n_vertex)))	{	//eliminazione del vertice o eliminazione del Grafo in caso di nodi cancellati
            grafo_root = graph_free(grafo_root);     //rimetto a disposizione l'elemento della q_foresta/array per la creazione della nuova Grafo
            printf("La Grafo %d \x8A stato eliminato\n\n", idx+1);
    } else {
        printf("\tGrafo %d di %s Aggiornato\n", idx+1, grafo_root->fnTypeData->type_name);
        graph_func_print(grafo_root);
    }
}


//Cancellazione di un arco
void graph_func_delEdge(GRAPHroot grafo_root)	{
    graph_func_print(grafo_root);		//stampa dell'grafo per una consultazione del vertice da eliminare
    graph_delArc(grafo_root->G, graph_func_choiceVrtx(grafo_root->G, "sorgente"), grafo_root->fnTypeData->Print);
    printf("\tGrafo %d di %s Aggiornato\n", idx+1, grafo_root->fnTypeData->type_name);
    graph_func_print(grafo_root);
}



//Calcolo del Grafo trasposto
void graph_func_transpose(GRAPHroot grafo_root)	{
    printf("\tGrafo %d di %s Attuale\n", idx+1, grafo_root->fnTypeData->type_name);
    graph_func_print(grafo_root);
    graph_transpose(grafo_root->G);
    printf("\tGrafo %d di %s Trasposto\n", idx+1, grafo_root->fnTypeData->type_name);
    graph_func_print(grafo_root);
}



//FUNZIONE AUSILIARIA: Scelta del vertice disponibile del Grafo
int graph_func_choiceVrtx(GRAPH G, char *str)  {
    int idx_src;
    do  {
        printf("Scegli il vertice %s: ", str);
        idx_src = io_getInteger();
        if(!G[idx_src])
            printf("ATTENZIONE: vertice all'indice %d non presente\n\n", idx_src);
    }while(!G[idx_src]);
    return idx_src;
}

//Stampa del grafo
void graph_func_print(GRAPHroot grafo_root)	{
    graph_print(grafo_root->G, grafo_root->fnTypeData->Print, grafo_root->n_vertex);
    printf("\t\tNumero di vertici: %d\n\n", grafo_root->n_vertex);   //e contemporaneamente visualizza il contatore del numero dei vertici per la visualizzazione in output
}

//FUNZIONE AUSILIARIA: Stampa in std::out del tipo di lista
char * graph_func_printTypeStruct(int typeStrucutre)  {
    if(typeStructure == 1)
        return "Matrice di Adiacenza";
    return "Lista di Adiacenza";
}


