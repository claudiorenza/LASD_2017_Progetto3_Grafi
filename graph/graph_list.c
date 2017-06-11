#include "graph_list.h"

//Inizializzazione del Grafo, con elementi da riempire con vertici
GRAPHlist graph_list_init()   {
    GRAPHlist grafo_lista = NULL;
    if((grafo_lista = (struct GrafoLista *)malloc(sizeof(struct GrafoLista)))    //allocazione della struct per il grafo
    && (grafo_lista->vrtx = (struct GrafoVertice **)calloc(MAX_graph, sizeof(struct GrafoVertice *)))    //array dei puntatori ai vertici del Grafo (inizializzati a NULL)
    && (grafo_lista->heights = (struct Lista **)calloc(MAX_graph, sizeof(struct Lista *))))  { //array delle altezze registrate (inizializzati a NULL)
        grafo_lista->n_vrtx = 0;
        grafo_lista->idx_max = 0;   //in questa posizione verrà registrato e aggiornato l'ultimo indice utilizzato dai vertici del grafo
    } else {
        printf("[MEM] ATTENZIONE: Problema di allocazione ");
        if(!grafo_lista)
            printf("GRAPHlist ");
        else if(!(grafo_lista->vrtx))
            printf("GRAPHvrtx * ");
        else if(!(grafo_lista->heights))
            printf("LIST * ");
        printf("- graph_list_init\n");
        exit(1);
    }
    return grafo_lista;
}

//Inserimento/Allocazione di un nuovo vertice nel Grafo e nella Lista di Adiacenza
void graph_list_insVertex(GRAPHlist grafo_lista, int idx, int height) {     //se il peso è = 0, trattasi di inserimento manuale e non generazione randomica
    if(idx == -1)    {   //se non è stato indicato manualmente l'indice del vertice
        do  {
            idx++;
        }while(!(grafo_lista->vrtx[idx]));  //cerco il primo vertice disponibile 
    }
    printf("DEBUG insVertex: %d\n", idx);
    if(idx > grafo_lista->idx_max)    //se ho superato il margine massimo, aggiorno il suo contatore
        grafo_lista->idx_max = idx; 
    if((grafo_lista->vrtx[idx] = (struct GrafoVertice *)malloc(sizeof(struct GrafoVertice))))  {  //assegno un puntatore della Lista di adiacenza, pronta ad aggiungere archi ai vertici adiacenti
        if(height == -1)  { //se non è stato indicato manualmente l'altezza
            if(!(grafo_lista->dup))    {   //se non è possibile inserire nodi nella stessa altezza
                while(!(grafo_lista->heights[height = random_num(0,255)]))  //cerco un'altezza casuale disponibile
                    ;
            } else  {//se posso inserire duplicati, va bene qualsiasi valore
                if(grafo_lista->heights[height = random_num(0,255)])  {   //verrà scelta un altezza randomicamente; se esiste già un nodo che ha la stessa altezza...
                    int weight;
                    graph_list_insArc(grafo_lista, idx, grafo_lista->heights[height]->idx_vrtx_dst, (weight = random_num(0,255)));   //...applico subito questo nuovo nodo all'adiacente del vertice posto alla stessa altezza
                        //IMPORTANTE: scegliere dalla lista delle altezze una delle sue destinazioni in maniera casuale e non al primo nodo presente in lista                    
                }
            }
        }  
        grafo_lista->vrtx[idx]->height = height;                 //assegno l'altezza al vertice creato
        grafo_lista->heights[height] = list_insertHead(grafo_lista->heights[height], idx, -1);  //inserisco un elemento nella lista delle altezze con l'identificativo del nodo associato     
        grafo_lista->n_vrtx += 1;                              //aggiorno la grandezza del grafo
        printf("Vertice %d correttamente inserito nel Grafo in altezza %d\n", idx, grafo_lista->vrtx[idx]->height);        
    } else  {
        printf("[MEM] ATTENZIONE: Problema di allocazione GRAPHvrtx - graph_list_insVertex\n");
        exit(1);
    }
}


//Inserimento di un nuovo arco per un grafo non orientato con controllo dei vertici disponibili
void graph_list_insArc(GRAPHlist grafo_lista, int idx_src, int idx_dst, int weight) {
    int n_edge;
    if(idx_dst == -1)    {   //se la destinazione è da specificare
        LIST *adj_slave = graph_list_adj_mirror(grafo_lista);  //creo la Lista adj_slave in mirroring per indicare i vertici disponibili al collegamento
        adj_slave[idx_src] = NULL;    //rendo non disponibile il vertice di partenza

        printf("%d: ", idx_src);
        n_edge = list_visit(grafo_lista->vrtx[idx_src]->adj, adj_slave);    //stampo e conto i vertici adiacenti, controllando la disponibilità di vertici collegabili
        printf("\n\n");
        if(n_edge < grafo_lista->n_vrtx)   {
            printf("Vertici disponibili per %d:\n", idx_src);
            graph_list_adj_mirrorPrint(adj_slave, grafo_lista->idx_max); //mostro i restanti vertici disponibili; con '0' al secondo parametro ('int showlist') non mostro le Liste di Adiacenza di questi vertici
            do  {
                printf("A quale indice vuoi collegare il vertice %d? ", idx_src);    //DEBUG: controllo della coincidenza fra idx_src e idx del vertice
                idx_dst = io_getInteger();
                if(!grafo_lista->vrtx[idx_dst]->adj)
                    printf("ATTENZIONE: vertice scelto non presente nel Grafo\n\n");
                else if(!adj_slave[idx_dst])
                    printf("ATTENZIONE: arco già presente per la destinazione scelta\n\n");
            }while(!grafo_lista->vrtx[idx_dst]->adj || !adj_slave[idx_dst]);
            graph_list_adj_mirrorFree(adj_slave, grafo_lista->idx_max);   //non ho più bisogno del mirroring del grafo
        } else  
            printf("ATTENZIONE: tutti gli archi uscenti sono già collegati con tutti gli altri vertici\n\n");   
    }
    if(!weight) {   //se il peso è da specificare (== 0)
        do  {
            printf("Quale peso vuoi inserire all'arco? (Numero reale): ");
            if((weight = io_getInteger()) < 1)
                printf("ATTENZIONE: Valore non valido\n\n");
        }while(weight < 1);
    }
    list_insertHead(grafo_lista->vrtx[idx_src]->adj, idx_dst, weight); //inserimento in testo nella Lista di Adiacenza di idx_src
    list_insertHead(grafo_lista->vrtx[idx_dst]->adj, idx_src, weight); //inserimento in testo nella Lista di Adiacenza di idx_dst (grafo non orientato)
    printf("Arco inserito in Lista fra i vertici %d <-> %d di peso [%d]\n", idx_src, idx_dst, grafo_lista->vrtx[idx_src]->adj->weight);
}

//Eliminazione del Grafo con annesse Liste di Adiacenza e con le Liste delle Altezze precedentemente registrate
void graph_list_deleteGraph(GRAPHlist grafo_lista) {
    int idx;
    for(idx=0;idx<grafo_lista->idx_max;idx++){
        if(grafo_lista->vrtx[idx] && grafo_lista->vrtx[idx]->adj)  {
            grafo_lista->vrtx[idx]->adj = list_delete(grafo_lista->vrtx[idx]->adj); //elimino tutta la Lista puntata ricorsivamente
            grafo_lista->heights[grafo_lista->vrtx[idx]->height] = list_delKey(grafo_lista->heights[grafo_lista->vrtx[idx]->height], idx); //elimino la corrispondente altezza nell'array delle altezze
	        free(grafo_lista->vrtx[idx]);   //dealloco il puntatore del vertice
        }
    }
	grafo_lista->n_vrtx = 0;
    grafo_lista->idx_max = 0;
}

//Eliminazione del vertice con idx relativi archi entranti e uscenti (grafo non orientato)
void graph_list_delVertex(GRAPHlist grafo_lista, int idx_del)  {
    grafo_lista->vrtx[idx_del]->adj = graph_list_delVertex_undirectedArcs(grafo_lista, grafo_lista->vrtx[idx_del]->adj, idx_del);  //eliminazione degli archi entranti al vertice e la sua Lista di Adiacenza
    grafo_lista->heights[grafo_lista->vrtx[idx_del]->height] = list_delKey(grafo_lista->heights[grafo_lista->vrtx[idx_del]->height], idx_del); //elimino la corrispondente altezza nell'array delle altezze
    free(grafo_lista->vrtx[idx_del]);    //dealloco il vertice
    grafo_lista->vrtx[idx_del] = NULL;   //rendo disponibile lo spazio nel caso di inserimento di un nuovo vertice

    if(idx_del == grafo_lista->idx_max) {//se il vertice da eliminare è proprio l'ultimo, aggiorno anche il valore del margine massimo dell'array
        do{ //cerco il minimo vertice disponibile
            grafo_lista->idx_max -= 1;   //decremento fin quando non trovo un vertice presente
        }while(grafo_lista->idx_max > 0 && !(grafo_lista->vrtx[grafo_lista->idx_max]));
    }
    grafo_lista->n_vrtx -= 1;  //IMPORTANTE: in caso di ultimo elemento eliminato, cancellare il grafo
}

//Eliminazione diretta di tutta la Lista di Adiacenza con gli archi entranti associati
LIST graph_list_delVertex_undirectedArcs(GRAPHlist grafo_lista, LIST L_curr, int idx_del) {
    if(L_curr)  {
        L_curr->next = graph_list_delVertex_undirectedArcs(grafo_lista, L_curr->next, idx_del);
        grafo_lista->vrtx[L_curr->idx_vrtx_dst]->adj = list_delKey(grafo_lista->vrtx[L_curr->idx_vrtx_dst]->adj, idx_del);    //eliminazione dell'arco entrante
        free(L_curr);   //deallocazione dell'arco uscente
    }
    return NULL;
}

//Eliminazione manuale dell'arco con controllo dei vertici adiacenti
void graph_list_delArc(GRAPHlist grafo_lista, int idx_src) {
    if(grafo_lista->vrtx[idx_src]->adj)    {
        int idx_del;
        LIST *adj_slave = graph_list_adj_mirror(grafo_lista);

        printf("%d: ", idx_src);
        list_visit((grafo_lista->vrtx[idx_src]->adj), adj_slave);    //stampo e conto i vertici adiacenti, controllando la disponibilità di vertici collegabili
        printf("\n\n");
        do  {
            printf("Quale indice dell'arco uscente vuoi eliminare dal vertice %d? ", idx_src);    //attualmente in uso come DEBUG per controllare se l'indice del vettore coincide con l'indice del dato interno
            if(adj_slave[(idx_del = io_getInteger())])    //in tal caso adj_slave ha tutti gli archi uscenti mancanti
                printf("ATTENZIONE: arco NON presente per la destinazione scelta\n\n");
        }while(adj_slave[idx_del]);
        graph_list_adj_mirrorFree(adj_slave, grafo_lista->idx_max);        
        grafo_lista->vrtx[idx_src]->adj = list_delKey(grafo_lista->vrtx[idx_src]->adj, idx_del);    //eliminazione dell'arco uscente
        grafo_lista->vrtx[idx_del]->adj = list_delKey(grafo_lista->vrtx[idx_del]->adj, idx_src);    //eliminazione dell'arco entrante
    } else
        printf("ATTENZIONE: il vertice scelto non ha archi uscenti\n\n");
}

//Visualizzazione del percorso fra due vertici in BFS o DFS
void graph_list_path(GRAPHlist grafo_lista, int idx_src, int idx_dst, int mode)  {   //mode == 0 -> BFS; mode == 1 -> DFS
    if(idx_src != idx_dst)  {
        int *pred = NULL;
        if(!mode)   //BFS
            pred = graph_list_BFS(grafo_lista, idx_src);
        else        //DFS
            pred = graph_list_DFS(grafo_lista, idx_src);
        graph_list_path_print(grafo_lista, idx_src, idx_dst, pred);
    } else
        printf("ATTENZIONE: Sorgente e destinazione coincidono\n\n");
}

//Stampa del percorso minimo fra due vertici definito dall'array dei predecessori
void graph_list_path_print(GRAPHlist grafo_lista, int idx_src, int idx_dst, int *pred)  {
    if(idx_src == idx_dst)
        printf("%d ", idx_src);
    else if(pred[idx_dst] == -1)
        printf("ATTENZIONE: non esiste alcun cammino tra la sorgente e la destinazione scelta\n\n");
    else    {
        graph_list_path_print(grafo_lista, idx_src, pred[idx_dst], pred);
        printf("-> %d ", idx_dst);
    }
}


//Visita in ampiezza con creazione e ritorno dell'array degli indici dei predecessori
int *graph_list_BFS(GRAPHlist grafo_lista, int idx_src)  {
    int idx;
    int *pred = (int *)calloc(grafo_lista->idx_max, sizeof(int));    //creo l'array degli indici dei predecessori

    char *color = (char *)malloc(sizeof(char) * grafo_lista->idx_max);   //creo l'array dei colori associati ai vertici, quantificati in grafo_lista[0]

    QUEUE coda = queue_init(grafo_lista->idx_max);  //creo una coda che ha una grandezza massima del numero dei vertici del Grafo
    LIST adj_curr = NULL; //prendo gli elementi della lista di adiacenza del vertice estratto dalla coda

    for(idx=0;idx<grafo_lista->idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_lista->vrtx[idx] && idx != idx_src) {
            color[idx] = 'w';
            pred[idx] = -1;
        }
    }

    color[idx_src] = 'g'; //GRIGIO sul vertice sorgente
    pred[idx_src] = -1;  //che non ha predecessori

    queue_enqueue(coda, idx_src);   //inserisco in coda la sorgente
    while(!queue_isEmpty(coda))    {    //ciclo fin quando non svuoto la coda
        idx = queue_dequeue(coda);    //estraggo la testa della Coda
        adj_curr = grafo_lista->vrtx[idx]->adj;  //prendo la Lista di Adiacenza dell'elemento appena estratto
        while(adj_curr) {
            if(color[adj_curr->idx_vrtx_dst] == 'w')  { //se BIANCO (white)
                color[adj_curr->idx_vrtx_dst] = 'g';   //coloro di GRIGIO (grey)
                pred[adj_curr->idx_vrtx_dst] = idx;      //assegno il suo predecessore
                queue_enqueue(coda, adj_curr->idx_vrtx_dst);   //inserisco l'indice nella coda per le future iterazioni
            }
            adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
        }
        color[idx] = 'b';  //completo la visita del nodo in NERO (black)
    }
    free(color);
    free(coda);
    return pred;
}


//Visita in profondità con verifica di ciclicità
int *graph_list_DFS(GRAPHlist grafo_lista, int idx_src)  {
    int idx; //intero che controlla l'effettiva presenza di un ciclo
    int *pred = (int *)malloc(sizeof(int) * grafo_lista->idx_max);    //per futura utitlità, dispongo anche l'array degli indici dei predecessori

    char *color = (char *)malloc(sizeof(char) * grafo_lista->idx_max);   //creo l'array dei colori associati ai vertici, quantificati in grafo_lista[0]

    for(idx=0;idx<grafo_lista->idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_lista->vrtx[idx]->adj)
            color[idx] = 'w';
            pred[idx] = -1;
    }

    for(idx=0;idx<grafo_lista->idx_max;idx++) {
        if(grafo_lista->vrtx[idx] && color[idx] == 'w')   //se esiste il vertice ed è BIANCO
            graph_list_DFS_visit(grafo_lista, idx, pred, color); //visito l'elemento della lista di adiacenza
    }
    free(color);
    return pred;
}

//Durante la visita in profondità, posso notificare la presenza di un ciclo all'interno del grafo
void graph_list_DFS_visit(GRAPHlist grafo_lista, int idx_curr, int *pred, char *color)    {
    LIST adj_curr = grafo_lista->vrtx[idx_curr]->adj; //prendo gli elementi della lista di adiacenza del vertice attuale
    color[idx_curr] = 'g'; //GRIGIO sul vertice attuale

    while(adj_curr)    {    //ciclo fin quando non svuoto la coda
        if(color[adj_curr->idx_vrtx_dst] == 'w')  { //se BIANCO
            pred[adj_curr->idx_vrtx_dst] = idx_curr;       //applico l'attuale vertice come predecessore di questo nodo adiacente
            graph_list_DFS_visit(grafo_lista, adj_curr->idx_vrtx_dst, pred, color);    //visito il nodo appena incontrato
        }
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
    }
    color[idx_curr] = 'b';  //completo la visita del nodo in NERO
}

//Stampa del Grafo con la Lista di Adiacenza dei rispettivi vertici
void graph_list_print(GRAPHlist grafo_lista)   {
    int idx;
    for(idx=0;idx<grafo_lista->idx_max;idx++) {
        if(grafo_lista->vrtx[idx])   { //se esiste il vertice nell'array
            printf("%d: ", idx);
            list_visit(grafo_lista->vrtx[idx]->adj, NULL); //passo la lista di adiacenza del vertice attuale
            printf("\n");
        }
    }
}

//Copia i riferimenti dei nodi del Grafo, utile per reperire la disponibilità e i dati dei nuovi vertici adiacenti a tempo costante
LIST *graph_list_adj_mirror(GRAPHlist grafo_lista)    {
    int idx;
    LIST *adj_slave = NULL;
    if((adj_slave = (LIST *)calloc(grafo_lista->idx_max, sizeof(LIST)))) {     //array slave delle Liste di Adiacenza da riferire
        for(idx=0;idx<grafo_lista->idx_max;idx++)
            adj_slave[idx] = grafo_lista->vrtx[idx]->adj;    //copio i riferimenti delle Liste di Adiacenza di tutti i nodi (disponibili e non);
    }

    return adj_slave;
}

//Stampa del Grafo con la Lista di Adiacenza dei rispettivi vertici
void graph_list_adj_mirrorPrint(LIST *adj_slave, int idx_max)   {
    int idx;
    for(idx=0;idx<idx_max;idx++) {
        if(adj_slave[idx])    //se esiste il vertice nell'array dei vertici disponibili
            printf("%d\n", idx);
    }
}

//Liberazione dell'array dei riferimenti
void graph_list_adj_mirrorFree(LIST *adj_slave, int idx_max)    {
    int idx;
    for(idx=0;idx<idx_max;idx++)    {   //assicuro che non ho i riferimenti ai nodi del vertice, evitando di liberare la loro memoria quando eseguo 'free'
        adj_slave[idx] = NULL;
    }
    free(adj_slave);
}
