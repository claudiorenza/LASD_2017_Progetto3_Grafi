#include "graph_func.h"

void graph_func_load(GRAPHlist grafo_lista) {
    char file_nome[255] = "graph1.txt";
    FILE *file;
    if(grafo_lista->n_vrtx != 0)	{	//se è già presente, chiedo al'utente quale operazione effettuare sul grafo
        printf("ATTENZIONE: Grafo già presente. È necessaria la cancellazione\n\n");
        graph_func_delete(grafo_lista);
        printf("\n");
    }    
    if(!(grafo_lista->n_vrtx))  { //se il Grafo è stato cancellato o se già era vuoto
        printf("Inserisci il nome del file: ");
        io_getString(file_nome, 255);
        if((file = fopen(file_nome,"r")))   {   //Apertura e controllo del file in sola lettura
            graph_list_parse(grafo_lista, file);  //Lettura dei valori presenti nel file
            fclose(file);
            printf("\n");
            if(grafo_lista->vrtx)    {  //Stampa del grafo
                printf("Lettura file completata\n\n");
                printf("\n\n");
                printf("\tGrafo [<indice>]<altezza> (<peso>)\n");
                graph_func_print(grafo_lista);
            } else
                printf("ATTENZIONE: Grafo vuoto\n");
        } else
            printf("ATTENZIONE: Errore nell'apertura del file\n");
    }
}



void graph_func_generate(GRAPHlist grafo_lista) {
    int idx, n_elem, n_arcs, idx_arc, idx_dst;
    if(grafo_lista->n_vrtx != 0)	{	//se è già presente, chiedo al'utente quale operazione effettuare sul grafo
        int choice;
        printf("ATTENZIONE: Grafo già presente. Cosa preferisci fare?\n\t1. Generazione nuovo Grafo\t2. Inserimento nuovi vertici\n\n");
        do  {
            printf("SCELTA: ");
            if((choice = io_getInteger()) < 1 || choice > 2)
                printf("ATTENZIONE: valore non valido\n\n");
        }while(choice < 1 || choice > 2);
        if(choice == 1) {
            graph_list_deleteGraph(grafo_lista);   //eliminazione completa del Grafo
            printf("\n");
            if(!(grafo_lista->n_vrtx))  {
                printf("Grafo eliminato\n\n");
                graph_list_dupEnabler(grafo_lista);
            }
        }
    }
    
    do  {
        printf("Quanti elementi vuoi inserire nel Grafo? (1-%d): ", MAX_graph - grafo_lista->n_vrtx);
        if((n_elem = io_getInteger()) < 1 || n_elem > MAX_graph - grafo_lista->n_vrtx)
			printf("ATTENZIONE: valore non valido\n\n");
	}while(n_elem < 1 || n_elem > MAX_graph - grafo_lista->n_vrtx);

    for(idx=0;idx<n_elem;idx++)
        graph_list_insVertex(grafo_lista, -1, -1, 0);	//inserisce un vertice assegnando un altezza casuale, l'indice del vertice è assegnato automaticamente
    
    GRAPHvrtx *vrtx_slave = NULL;

    for(idx=0;idx<=grafo_lista->idx_max;idx++) {    //inserisco gli archi in maniera casuale
        if(grafo_lista->vrtx[idx])  {
            vrtx_slave = graph_list_vrtx_mirror(grafo_lista);  //creo la Lista vrtx_slave in mirroring per indicare i vertici disponibili al collegamento
            vrtx_slave[idx] = NULL;    //rendo non disponibile il vertice di partenza come arco da collegare
            n_arcs = graph_list_adjVisit(grafo_lista->vrtx[idx]->adj, NULL, vrtx_slave);    //stampo e conto i vertici adiacenti, controllando la disponibilità di vertici collegabili
            if(n_arcs < (grafo_lista->n_vrtx) - 1)  {   //se gli archi non sono collegati a tutti i nodi
                for(idx_arc=0;idx_arc<random_num(0,2);idx_arc++)  {   //per ogni vertice posso inserire un massimo di 2 archi
                    while(!(grafo_lista->vrtx[(idx_dst = random_num(0,grafo_lista->idx_max))]) || !vrtx_slave[idx_dst]) //cerco un vertice disponibile
                        ;
                    graph_list_insArc(grafo_lista, idx, idx_dst, random_num(1, MAX_weight)); //inserisco l'arco con un peso random
                    vrtx_slave[idx_dst] = NULL;
                }    
            }
            graph_list_vrtx_mirrorFree(vrtx_slave, grafo_lista->idx_max);   //non ho più bisogno del mirroring del grafo
            vrtx_slave = NULL;
        }
    }

    
    printf("\n\n");
    printf("\tGrafo [<indice>]<altezza> (<peso>)\n");
    graph_func_print(grafo_lista);
}

//Inserimento di un nuovo vertice nel grafo (già esistente)
void graph_func_insertKey(GRAPHlist grafo_lista)	{
    printf("\tGrafo [<indice>]<altezza> (<peso>)\n");    
    graph_func_print(grafo_lista);	//stampa dei nodi e degli archi adiacenti per il tipo di struttura associata

	if(grafo_lista->n_vrtx <= MAX_graph) { //controllo il numero di vertici per aggiungerne nuovi
        int height, idx_new = -1, weight = 0;
        char confirm;
        do	{
            printf("Vuoi inserire manualmente l'indice al vertice da inserire? (S/N): ");
            confirm = io_getChar();
            if(confirm == 's' || confirm == 'S')	{
                do  {
                    printf("In quale indice vuoi applicare il nuovo vertice? (0-%d): ", MAX_graph-1);
                    if((idx_new = io_getInteger()) < 0 || idx_new > MAX_graph-1)
                        printf("ATTENZIONE: valore non valido\n\n");
                    else if((grafo_lista->vrtx[idx_new]))    //se l'indice nel Grafo è già occupato
                        printf("ATTENZIONE: indice già occupato nel Grafo\n\n");
                }while((idx_new < 0 || idx_new > MAX_graph-1) || ((grafo_lista->vrtx[idx_new])));
            } else if(confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N')
                printf("ATTENZIONE: Comando non valido\n\n");
        }while(confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N');
    
        do  {
            printf("Quale altezza vuoi applicare al nuovo vertice? (0-%d): ", MAX_graph-1);
            if((height = io_getInteger()) < 0 || height > MAX_graph-1)
                printf("ATTENZIONE: valore non valido\n\n");
            else if(!(grafo_lista->dup) && grafo_lista->heights[height])    //se il Grafo non può avere due incroci posti alla stessa altezza
                printf("ATTENZIONE: altezza già presente nel Grafo\n\n");
        }while((height < 0 || height > MAX_graph-1) || (!(grafo_lista->dup) && grafo_lista->heights[height]));

        if(grafo_lista->dup && grafo_lista->heights[height])    {   //se posso inserire duplicati ed esiste un nodo che ha la stessa altezza
            printf("\n");
            printf("Altezza %d già presente in indice [%d]\n\n", height, grafo_lista->heights[height]->idx_vrtx_dst);
            do  {
                printf("Quale peso vuoi inserire nell'arco che parte da [%d]? (1-%d): ", grafo_lista->heights[height]->idx_vrtx_dst, MAX_weight);
                if((weight = io_getInteger()) < 1 || weight > MAX_weight)   //inserisco il peso dell'arco per l'adiacente al nodo posto alla stessa altezza
                    printf("ATTENZIONE: valore non valido\n\n");
            }while(weight < 1 || weight > MAX_weight);
        }

        graph_list_insVertex(grafo_lista, idx_new, height, weight);      //se il peso è = 0, trattasi di inserimento manuale, quindi in caso di generazione verrà assegnato un peso casuale

        printf("\tGrafo Aggiornato [<indice>]<altezza> (<peso>)\n");
        graph_func_print(grafo_lista);			//stampa dell'grafo aggiornato
	} else	//in caso di raggiungimento della capacità massima
		printf("ATTENZIONE: Capacità massima del Grafo raggiunta\n");
}


//Inserimento di un nuovo arco
void graph_func_insertArc(GRAPHlist grafo_lista)	{
    printf("\tGrafo [<indice>]<altezza> (<peso>)\n");	
    graph_func_print(grafo_lista);	//stampa dei nodi e degli archi adiacenti per il tipo di struttura associata
	if(grafo_lista->n_vrtx > 1) {
        int idx_src;
        int n_arcs;
        GRAPHvrtx *vrtx_slave = graph_list_vrtx_mirror(grafo_lista);  //creo la Lista vrtx_slave in mirroring per indicare i vertici disponibili al collegamento
        vrtx_slave[(idx_src = graph_func_choiceVrtx(grafo_lista, "sorgente"))] = NULL;    //scelgo e rendo non disponibile il vertice di partenza come arco da collegare
        printf("[%d]%d: ", idx_src, grafo_lista->vrtx[idx_src]->height);
        n_arcs = graph_list_adjVisit(grafo_lista->vrtx[idx_src]->adj, grafo_lista->vrtx, vrtx_slave);    //stampo e conto i vertici adiacenti, controllando la disponibilità di vertici collegabili
        printf("\n\n");
        if(n_arcs < (grafo_lista->n_vrtx) - 1)  {   //se gli archi sono collegati a tutti i nodi
            int idx_dst, weight;
            printf("Vertici disponibili per %d:\n", idx_src);
            graph_list_vrtx_mirrorPrint(vrtx_slave, grafo_lista->idx_max); //mostro i restanti vertici disponibili; con '0' al secondo parametro ('int showlist') non mostro le Liste di Adiacenza di questi vertici
            do  {
                if(!vrtx_slave[(idx_dst = graph_func_choiceVrtx(grafo_lista, "destinazione"))])
                    printf("ATTENZIONE: arco già presente per la destinazione scelta\n\n");
            }while(!(grafo_lista->vrtx[idx_dst]) || !vrtx_slave[idx_dst]);
            graph_list_vrtx_mirrorFree(vrtx_slave, grafo_lista->idx_max);   //non ho più bisogno del mirroring del grafo
            do  {
                printf("Quale peso vuoi inserire nell'arco? (1-%d): ", MAX_weight);
                if((weight = io_getInteger()) < 1 || weight > MAX_weight)
                    printf("ATTENZIONE: valore non valido\n\n");
            }while(weight < 1 || weight > MAX_weight);
            graph_list_insArc(grafo_lista, idx_src, idx_dst, weight);     //3° param = -1: destinazione da scegliere; 4° param = 0: peso da scegliere
            io_clearScreen();
            printf("Arco inserito in Lista fra i vertici %d <-> %d di peso [%d]\n", idx_src, idx_dst, grafo_lista->vrtx[idx_src]->adj->weight); //accedo direttamente al peso dell'elemento in testa appena inserito
            printf("\tGrafo Aggiornato [<indice>]<altezza> (<peso>)\n");
            graph_func_print(grafo_lista);			//stampa dell'grafo aggiornato        
        } else  
            printf("ATTENZIONE: tutti gli archi uscenti sono già collegati con tutti gli altri vertici\n\n");   
    } else
        printf("ATTENZIONE: nel grafo scelto è presente un solo vertice\n");
}


//Visualizzazione percorso minimo fra due vertici dati in BFS
void graph_func_BFS(GRAPHlist grafo_lista)   {
    printf("\tGrafo [<indice>]<altezza> (<peso>)\n");    
    graph_func_print(grafo_lista);

    int idx_src = graph_func_choiceVrtx(grafo_lista, "sorgente"), idx_dst = graph_func_choiceVrtx(grafo_lista, "di destinazione");
    
    if(grafo_lista->n_vrtx > 1) {
        graph_list_path(grafo_lista, idx_src, idx_dst, 0);  //4° param = 0: BFS
    } else
        printf("ATTENZIONE: nel grafo scelto è presente un solo vertice\n");
}

//Visualizzazione del DFS
void graph_func_DFS(GRAPHlist grafo_lista)   {
    printf("\tGrafo [<indice>]<altezza> (<peso>)\n");        
    graph_func_print(grafo_lista);

    int idx_src = graph_func_choiceVrtx(grafo_lista, "sorgente"), idx_dst = graph_func_choiceVrtx(grafo_lista, "di destinazione");
    
    if(grafo_lista->n_vrtx > 1) {
        graph_list_path(grafo_lista, idx_src, idx_dst, 1);   //4° param = 1: DFS
    } else
        printf("ATTENZIONE: nel grafo scelto è presente un solo vertice\n");
}


//Cancellazione del grafo
void graph_func_delete(GRAPHlist grafo_lista)	{
    char confirm;
    do	{
        printf("Sei sicuro di voler eliminare il Grafo? (S/N): ");
        confirm = io_getChar();
        if(confirm == 's' || confirm == 'S')	{
            graph_list_deleteGraph(grafo_lista);		//controllo ed eliminazione dell'grafo in caso di conferma
            if(!(grafo_lista->n_vrtx))
                printf("Il Grafo è stato eliminato\n\n");
        } else if(confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N')
            printf("ATTENZIONE: Comando non valido\n\n");
    }while(confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N');
}


//Cancellazione di un vertice
void graph_func_delVertex(GRAPHlist grafo_lista)	{
    printf("\tGrafo [<indice>]<altezza> (<peso>)\n");        
    graph_func_print(grafo_lista);		//stampa dell'grafo per una consultazione del vertice da eliminare

    graph_list_delVertex(grafo_lista, graph_func_choiceVrtx(grafo_lista, "da eliminare")); 	//eliminazione del vertice o eliminazione del Grafo in caso di nodi cancellati
    if(!(grafo_lista->n_vrtx))
        printf("Il Grafo è stato eliminato\n\n");
    else {
        printf("\n\n");
        printf("\tGrafo Aggiornato [<indice>]<altezza> (<peso>)\n");
        graph_func_print(grafo_lista);
    }
}


//Cancellazione di un arco
void graph_func_delEdge(GRAPHlist grafo_lista)	{
    printf("\tGrafo [<indice>]<altezza> (<peso>)\n");        
    graph_func_print(grafo_lista);		//stampa dell'grafo per una consultazione del vertice da eliminare
    
    graph_list_delArc(grafo_lista, graph_func_choiceVrtx(grafo_lista, "sorgente"));
    printf("\n\n");
    printf("\tGrafo Aggiornato [<indice>]<altezza> (<peso>)\n");
    graph_func_print(grafo_lista);
}


//FUNZIONE AUSILIARIA: Scelta del vertice disponibile del Grafo
int graph_func_choiceVrtx(GRAPHlist grafo_lista, char *str)  {
    int idx_src;
    do  {
        printf("Scegli il vertice %s: ", str);
        if((idx_src = io_getInteger()) < 0 || idx_src > MAX_graph-1)
            printf("ATTENZIONE: valore non valido\n\n");
        else if(!(grafo_lista->vrtx[idx_src]))
            printf("ATTENZIONE: vertice all'indice %d non presente\n\n", idx_src);
    }while((idx_src < 0 || idx_src > MAX_graph-1) || !(grafo_lista->vrtx[idx_src]));

    return idx_src;
}

//Stampa del grafo
void graph_func_print(GRAPHlist grafo_lista)	{
    graph_list_print(grafo_lista);    
    printf("\t\tNumero di vertici: %d\n\n", grafo_lista->n_vrtx);   //e contemporaneamente visualizza il contatore del numero dei vertici per la visualizzazione in output
}

//Visita in DFS con applicazione dei vincoli
void graph_func_sp(GRAPHlist grafo_lista)    {
    printf("\tGrafo [<indice>]<altezza> (<peso>)\n");        
    graph_func_print(grafo_lista);		//stampa dell'grafo per una consultazione dei vertici da definire come sorgente e destinazione
    
    printf("\t[DEBUG DFS] INIZIO algoritmo\n");    
    int idx_src = graph_func_choiceVrtx(grafo_lista, "sorgente"), idx_dst = graph_func_choiceVrtx(grafo_lista, "destinazione");
    int *pred = graph_sp_DFS(grafo_lista, idx_src, idx_dst);
    printf("\t[DEBUG DFS] FINE algoritmo\n");
    if(pred[idx_dst] != -1)   {   //se è stato visitato il nodo di destinazione partendo dalla sorgente, allora esiste un percorso applicato ai vincoli
        graph_sp_path_print(grafo_lista->vrtx, idx_src, idx_dst, pred); //stampa del percorso
    }
}
