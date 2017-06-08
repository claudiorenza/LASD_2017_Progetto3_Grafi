#include "graph_list.h"

//Inizializzazione del Grafo, con elementi da riempire con vertici
GRAPHlist graph_list_init(int idx_max)   {
    GRAPHlist grafo_list = NULL;
    if((grafo_list = (struct GrafoLista *)malloc(sizeof(struct GrafoLista)))    //allocazione della struct per il grafo
    && (grafo_list->grafo_vrtx = (struct GrafoVertice **)calloc(MAX_graph, sizeof(struct GrafoVertice *))))  { //array dei puntatori ai vertici del Grafo (inizializzati a NULL)
        grafo_list->n_vrtx = 0;
        grafo_list->idx_max = idx_max;   //in questa posizione verrà registrato/aggiornato l'ultimo indice utilizzato dai vertici del grafo
    } else {
        printf("[MEM] ATTENZIONE: Problema di allocazione ");
        if(!grafo_list)
            printf("GRAPHlist ");
        else if(!(grafo_list->grafo_vrtx))
            printf("GRAPHvrtx * ");
        printf("- graph_list_init\n");
        exit(1);
    }
    return grafo_list;
}

//Inserimento/Allocazione di un nuovo vertice nel Grafo e nella Lista di Adiacenza
void graph_list_insVertex(GRAPHlist grafo_list, int idx) {
    if(idx == -1)    {   //se non è stato indicato manualmente l'indice del vertice
        while(!(grafo_list->grafo_vrtx[idx == random_num(0,255)]))  //cerco un vertice casuale disponibile
            ;  
    }
    printf("DEBUG insVertex: %d\n", idx);
    if(idx > grafo_list->idx_max)    
        grafo_list->idx_max = idx; //se ho superato il margine, aggiorno il contatore dell'ultimo indice
    if((grafo_list->grafo_vrtx[idx] = (struct GrafoVertice *)malloc(sizeof(struct GrafoVertice *))))  {  //assegno un puntatore della Lista di adiacenza, pronta ad aggiungere archi ai vertici adiacenti
        printf("Vertice %d correttamente inserito nel Grafo\n", idx);
        grafo_list->grafo_vrtx[idx]
        grafo_list->n_vertex += 1;
    } else  {
        printf("[MEM] ATTENZIONE: Problema di allocazione LIST - graph_list_insVertex\n");
        exit(1);
    }
}


//Inserimento di un nuovo arco con controllo dei vertici disponibili
void graph_list_insArc(GRAPHlist grafo_list, int idx_src, int idx_dst, int weight, int n_vrtx) {
    int n_edge;
    LIST *adj_slave = graph_list_adj_mirror(grafo_list);  //creo la Lista adj_slave in mirroring per indicare i vertici disponibili al collegamento
    adj_slave[idx_src] = NULL;    //rendo non disponibile il vertice di partenza

    printf("%d: ", idx_src);
    n_edge = list_visit((*(grafo_list->adj[idx_src]), adj_slave);    //stampo e conto i vertici adiacenti, controllando la disponibilità di vertici collegabili
    printf("\n\n");
    if(n_edge < grafo_list->n_vrtx)   {
        printf("Vertici disponibili per %d:\n", idx_src);

        graph_list_adj_print(adj_slave, grafo_list->n_vertex, 0); //mostro i restanti vertici disponibili; con '0' al secondo parametro ('int showlist') non mostro le Liste di Adiacenza di questi vertici
        do  {
            printf("A quale indice vuoi collegare il vertice %d? ", idx_src);    //DEBUG: controllo della coincidenza fra idx_src e idx del vertice
            idx_dst = io_getInteger();
            if(!grafo_list->adj[idx_dst])
                printf("ATTENZIONE: vertice scelto non presente nel Grafo\n\n");
            else if(!adj_slave[idx_dst])
                printf("ATTENZIONE: arco già presente per la destinazione scelta\n\n");
        }while(!grafo_list->adj[idx_dst] || !adj_slave[idx_dst]);
        do  {
            printf("Quale peso vuoi inserire all'arco? (Numero reale): ");
            weight ;
            if((weight = io_getInteger()) < 1)
                printf("ATTENZIONE: Valore non valido\n\n");
        }while(weight < 1);
        graph_list_adj_mirrorFree(adj_slave);   //non ho più bisogno del mirroring del grafo
        list_insertHead(grafo_list[idx_src]->adj, idx_dst, weight); //inserimento in testo nella Lista di Adiacenza di idx_src
        printf("Arco inserito in Lista fra i vertici %d -> %d di peso [%d]\n", idx_src, idx_dst, (*(grafo_list->adj[idx_src]))->weight);
    } else  
        printf("ATTENZIONE: tutti gli archi uscenti sono già collegati con tutti gli altri vertici\n\n");
}

//Eliminazione del Grafo con annesse Liste di Adiacenza
GRAPHlist graph_list_deleteGraph(GRAPHlist grafo_list) {
    int idx;
    for(idx=0;idx<grafo_list->idx_max;idx++){
        if(grafo_list->grafo_vrtx[idx]->adj)
            grafo_list->grafo_vrtx[idx]->adj = graph_list_nodeFree(grafo_list->grafo_vrtx[idx]->adj);
    }
    return NULL;
}


//Eliminazione del vertice con idx relativi archi entranti; ritorna il numero di vertici aggiornato
void graph_list_delVertex(GRAPHlist grafo_list, int idx_del, int n_vrtx)  {
    int idx;
    for(idx=0;idx<=grafo_list->idx_max;idx++) {
        if(grafo_list->grafo_vrtx[idx]->adj && idx!=idx_del)
            list_delKey(grafo_list->grafo_vrtx[idx]->adj, idx_del); //CHECK: passaggio del riferimento
        else if(idx==idx_del)    //elimino subito il vertice dell'indice scelto con la relativa lista
            grafo_list->grafo_vrtx[idx]->adj = graph_list_nodeFree(grafo_list->grafo_vrtx[idx]->adj);
    }
    if(idx_del == grafo_list->idx_max) {//se il vertice da eliminare è proprio l'ultimo, aggiorno anche il valore del margine massimo dell'array
        while(idx_del > 0 && !(grafo_list->grafo_vrtx[idx]->adj))    //cerco il minimo vertice disponibile
            idx_del--;   //decremento fin quando non trovo un vertice presente
        }
        grafo_list->idx_max = idx_del; //se ho superato il margine, aggiorno il contatore dell'ultimo indice
    }
    grafo_list->n_vertex -= 1;
}


//Liberazione della memoria allocata dinamicamente del vertice
LIST graph_list_nodeFree(LIST grafo_list_adj)	{
	*grafo_list_adj = list_delete(*grafo_list_adj); //elimino la Lista puntata
	free(grafo_list_adj);   //dealloco il puntatore alla Lista
	return NULL;
}


//Eliminazione dell'arco con controllo dei vertici adiacenti
void graph_list_delKey(GRAPHlist grafo_list, int idx_src) {
    if(grafo_list->adj[idx_src])    {
        int idx_del;
        LIST *adj_slave = graph_list_adj_mirror(grafo_list);

        printf("%d: ", idx_src);
        list_visit((*(grafo_list->adj[idx_src]), adj_slave);    //stampo e conto i vertici adiacenti, controllando la disponibilità di vertici collegabili
        printf("\n\n");
        do  {
            printf("Quale indice dell'arco uscente vuoi eliminare dal vertice %d? ", idx_src);    //attualmente in uso come DEBUG per controllare se l'indice del vettore coincide con l'indice del dato interno
            if(adj_slave[(idx_del = io_getInteger())])    //in tal caso adj_slave ha tutti gli archi uscenti mancanti
                printf("ATTENZIONE: arco NON presente per la destinazione scelta\n\n");
        }while(adj_slave[idx_del]);
        list_delKey((grafo_list->adj[idx_src], idx_del);    //eliminazione dell'arco
        graph_list_adj_mirrorFree(adj_slave);
    } else
        printf("ATTENZIONE: il vertice scelto non ha archi uscenti\n\n");
}


/*Trasposizione del Grafo in maniera efficiente T(n) = |V| + |E| e senza allocazione di nuova memoria, e con cambio dei riferimenti dei vertici
void graph_list_transpose(GRAPHlist grafo_list)    {
    int idx, idx_max = grafo_list->idx_max;
    LISTadj *L_arr_adj = NULL;    //creo un array con idx riferimenti alle Liste di Adiacenza di ogni vertice
    L_arr_adj = (struct ListaAdj **)malloc(sizeof(struct ListaAdj *) * idx_max);

    for(idx=0;idx<=idx_max;idx++) {  //Inizializzazione con copia dei riferimenti alle Liste
        if(grafo_list->grafo_vrtx[idx]->adj)   {
            L_arr_grafo_vrtx[idx]->adj = ((GRAPHlist)grafo_list->grafo_vrtx[idx]->adj)->adj;     //memorizzo idx riferimenti nell'array delle Liste
            ((GRAPHlist)grafo_list->grafo_vrtx[idx]->adj)->adj = NULL;             //tolgo idx riferimenti nel grafo per gli inserimenti di 'list_trasp_recv'
        }
    }
    for(idx=0;idx<=idx_max;idx++) {  //Visita delle Liste e inserimento dei vertici nel grafo trasposto
        if(grafo_list->grafo_vrtx[idx]->adj)
            L_arr_grafo_vrtx[idx]->adj = list_trasp_recv(L_arr_grafo_vrtx[idx]->adj, (grafo_list), idx);    //N.B.: L_arr_grafo_vrtx[idx]->adj diventa NULL, quindi nessuna perdita di dati in deallocazione
    }
    free(L_arr_adj);
}
*/

//Visualizzazione del percorso minimo fra due vertici (BFS)
void graph_list_path(GRAPHlist grafo_list, int idx_src, int idx_dst)  {
    if(idx_src != idx_dst)  {
        int *pred = graph_list_BFS(grafo_list, idx_src);
        graph_list_path_print(grafo_list, idx_src, idx_dst, pred);
    } else
        printf("ATTENZIONE: Sorgente e destinazione coincidono\n\n");
}

//Visita in ampiezza con creazione e ritorno dell'array degli indici dei predecessori
int *graph_list_BFS(GRAPHlist grafo_list, int idx_src)  {
    int idx, idx_max = grafo_list->idx_max;
    int *pred = (int *)calloc(idx_max, sizeof(int));    //creo l'array degli indici dei predecessori

    char *color = (char *)malloc(sizeof(char) * idx_max);   //creo l'array dei colori associati ai vertici, quantificati in grafo_list[0]

    QUEUE coda = queue_init(idx_max);  //creo una coda che ha una grandezza massima del numero dei vertici del Grafo
    LISTel adj_curr = NULL; //prendo gli elementi della lista di adiacenza del vertice estratto dalla coda

    for(idx=0;idx<idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_list->grafo_vrtx[idx]->adj && idx != idx_src) {
            color[idx] = 'w';
            pred[idx] = -1;
        }
    }

    color[idx_src] = 'g'; //GRIGIO sul vertice sorgente
    bfs_pred[idx_src]->pred= -1;  //che non ha predecessori
    queue_enqueue(coda, idx_src);   //inserisco in coda la sorgente
    while(!queue_check_empty(coda))    {    //ciclo fin quando non svuoto la coda
        idx = queue_dequeue(coda);    //estraggo la testa della Coda
        adj_curr = *(grafo_list->grafo_vrtx[idx]->adj);  //prendo la Lista di Adiacenza dell'elemento appena estratto
        while(adj_curr) {
            if(color[adj_curr->vrtx_dst] == 'w')  { //se BIANCO (white)
                color[adj_curr->vrtx_dst] = 'g';   //coloro di GRIGIO (grey)
                pred[adj_curr->vrtx_dst] = idx;      //assegno il suo predecessore
                queue_enqueue(coda, adj_curr->vrtx_dst);   //inserisco l'indice nella coda per le future iterazioni
            }
            adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
        }
        color[idx] = 'b';  //completo la visita del nodo in NERO (black)
    }
    free(color);
    free(coda);
    return pred;
}

//Semplificazione delle condizioni per l'inserimento in coda di elementi adiacenti
//N.B.: per una migliore comprensione, invece di inserire tutte le condizioni in un unico 'if', possiamo analizzare separatamente i casi validi per l'inserimento in coda
int graph_list_conditionAdj(int idx, int idx_src, int idx_dst, LISTel adj_curr, PRED *bfs_pred)  {
    int ret = 0;    //inizializzazione a 0 (nel caso nessuna condizione sia verificata, la funzione ritornerà 0)
    if(idx == idx_src || idx < idx_dst) {   //Se parto dalla sorgente, oppure la destinazione è situata più in alto e sei appena salito,
        if(idx < adj_curr->vrtx_dst)   {        //devo necessariamente salire, selezionando solo i nodi adiacenti in salita.
            if(adj_curr->vrtx_dst != idx_dst)       //Se salendo non trovo già la destinazione,
                ret = 1;                            //inserisco il nodo adiacente in coda.
        }
    } else if(idx > idx_dst)    {           //Se, invece, mi trovo più in alto rispetto alla destinazione,
        if(bfs_pred[idx]->pred < idx)    {      //se il predecessore è più in basso rispetto alla posizione attuale (ho appena effettuato una salita)
            if(idx < adj_curr->vrtx_dst && adj_curr->vrtx_dst != idx_dst) //e salendo non trovo già la destinazione,
                ret = 1;                            //inserisco il nodo adiacente in coda.
            else if(idx > adj_curr->vrtx_dst)       //In caso di discesa,
                ret = 1;                            //non esiste discriminante per l'inserimento.
        } else {                                //Se il predecessore è più in alto rispetto alla posizione attuale (ho appena effettuato una discesa),
            if(idx > adj_curr->vrtx_dst && idx > idx_dst) //devo necessariamente scendere, non andando oltre al di sotto del nodo di destinazione
                ret = 1;                            //inserendo solo i nodi adiacenti in discesa.
        }                    
    }
    //N.B.: se "idx" è attualmente il nodo di destinazione "idx_dst", non visito i suoi nodi adiacenti (non entrerò in alcuna 'if' e ritornerò 0),
    //siccome dovrò eventualmente confrontare gli altri percorsi provenienti dai suoi adiacenti, come archi entranti 
    return ret;
}



//Stampa del percorso minimo fra due vertici definito dall'array dei predecessori
void graph_list_path_print(GRAPHlist grafo_list, int idx_src, int idx_dst, int *pred)  {
    if(idx_src == idx_dst)
        printf("%d ", idx_src)
    else if(pred[idx_dst] == -1)
        printf("ATTENZIONE: non esiste alcun cammino tra la sorgente e la destinazione scelta\n\n");
    else    {
        graph_list_path_print(grafo_list, idx_src, pred[idx_dst], pred);
        printf("-> %d ", idx_dst);
    }
}

//Ricerca nel grafo di un arco di ritorno, ovvero di un ciclo
void graph_list_check_cycle(GRAPHlist grafo_list)  {
    int idx=0;
    while(!grafo_list->grafo_vrtx[idx]->adj)   //vedo l'indice minimo del primo elemento presente attualmente nel grafo
        idx++;
    if(graph_list_DFS(grafo_list, idx))  //se c'� un ciclo, lo notifico
        printf("Il grafo contiene un ciclo\n\n");
    else
        printf("Il grafo NON contiene un ciclo\n\n");
}


//Visita in profondità con verifica di ciclicità
int graph_list_DFS(GRAPHlist grafo_list, int idx_src)  {
    int idx, idx_max = grafo_list->idx_max, check_cycle = 0; //intero che controlla l'effettiva presenza di un ciclo
    int *pred = (int *)malloc(sizeof(int) * idx_max);    //per futura utitlit�, dispongo anche l'array degli indici dei predecessori

    char *color = (char *)malloc(sizeof(char) * idx_max);   //creo l'array dei colori associati ai vertici, quantificati in grafo_list[0]

    LISTadj adj_curr = NULL; //prendo gli elementi della lista di adiacenza del vertice estratto dalla coda

    for(idx=idx_src;idx<=idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_list->grafo_vrtx[idx]->adj)
            color[idx] = 'w';
            pred[idx] = -1;
    }

    adj_curr = grafo_list[idx_src]->adj;   //prendo la Lista di Adiacenza del primo elemento
    while(adj_curr) {
        if(color[adj_curr->vrtx_dst] == 'w')   //se BIANCO
            check_cycle = graph_list_DFS_visit(grafo_list, adj_curr->vrtx_dst, pred, color, check_cycle); //visito l'elemento della lista di adiacenza
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
    }
    free(color);
    return check_cycle;
}

//Durante la visita in profondità, posso notificare la presenza di un ciclo all'interno del grafo
int graph_list_DFS_visit(GRAPHlist grafo_list, int idx_curr, int *pred, char *color, int check_cycle)    {
    LISTadj adj_curr = grafo_list[idx_curr]->adj; //prendo gli elementi della lista di adiacenza del vertice attuale
    color[idx_curr] = 'g'; //GRIGIO sul vertice attuale

    while(adj_curr)    {    //ciclo fin quando non svuoto la coda
        if(color[adj_curr->vrtx_dst] == 'w')  { //se BIANCO
            pred[adj_curr->vrtx_dst] = idx_curr;       //applico l'attuale vertice come predecessore di questo nodo adiacente
            check_cycle = graph_list_DFS_visit(grafo_list, adj_curr->vrtx_dst, pred, color, check_cycle);    //visito il nodo appena incontrato
        } else if(!check_cycle && color[adj_curr->vrtx_dst] == 'g')       //se mi ritrovo un GRIGIO, � un arco di ritorno (ciclo)
            check_cycle = 1;    //N.B.: è consono continuare l'algoritmo, invece di ritornare subito la notifica
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
    }
    color[idx_curr] = 'b';  //completo la visita del nodo in NERO
    return check_cycle;
}


//Stampa del Grafo con la Lista di Adiacenza dei rispettivi vertici
void graph_list_adj_print(LIST *grafo_list_adj, int idx_max, int showlist)   {
    int idx;
    for(idx=0;idx<=idx_max;idx++) {
        if(grafo_list_grafo_vrtx[idx]->adj)   { //se esiste il vertice nell'array delle liste
            printf("%d", idx);
            if(showlist)    //si può richiedere dal parametro 'showlist' passando '1' per mostrare la Lista di Adiacenza del vertice attuale
                printf(":");
                list_visit(*grafo_list_grafo_vrtx[idx]->adj, NULL); //passo la lista di adiacenza del vertice attuale
            printf("\n");
        }
    }
}

//Copia idx riferimenti dei nodi del Grafo, utile per reperire la disponibilit� e idx dati dei nuovi vertici adiacenti a tempo costante
LIST *graph_list_adj_mirror(GRAPHlist grafo_list)    {
    int idx;
    LIST *adj_slave = NULL;
    if(adj_slave = (LIST *)calloc(grafo_list->idx_max, sizeof(LIST))) {
        for(idx=0;idx<=grafo_list->idx_max;idx++)
            adj_slave[idx] = grafo_list->grafo_vrtx[idx]->adj;    //copio i riferimenti di tutti i nodi (disponibili e non);
    }

    return adj_slave;
}

//Liberazione dell'array dei riferimenti
void graph_list_adj_mirrorFree(LIST *adj_slave, int idx_max)    {
    int idx;
    for(idx=0;idx<idx_max;idx++)    {   //assicuro che non ho i riferimenti ai nodi del vertice, evitando di liberare la loro memoria quando eseguo 'free'
        adj_slave[idx] = NULL;
    }
    free(adj_slave);
}
