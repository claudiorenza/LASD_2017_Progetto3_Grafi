#include "graph_list.h"

//Inizializzazione del Grafo, con elementi da riempire con vertici
GRAPHlist graph_list_init(int idx_max)   {
    void **grafo_list = NULL;
    if(grafo_list = calloc(MAX_GRAPHlist, sizeof(void *)) { //array dei puntatori ai vertici del Grafo
        int idx;
        for(idx=0; idx<MAX_GRAPHlist; idx++)     //CHECK: metto a disposizione dei puntatori per rendere disponibile l'aggiunta/l'allocazione di nuovi vertici
            grafo_list[idx] = NULL;
        if(idx_max >= 0)  {   //nel caso non debba fare una trasposizione, alloco il contatore
            grafo_list[0] = (int *)malloc(sizeof(int));
            *((int *)grafo_list[0]) = idx_max;   //in questa posizione verrà registrato/aggiornato l'ultimo indice utilizzato dai vertici del grafo
        }
    } else {
        printf("[MEM] ATTENZIONE: Problema di allocazione GRAPHlist - graph_list_init\n");
        exit(1);
    }
    return grafo_list;
}

//Inserimento/Allocazione di un nuovo vertice nel Grafo e nella Lista di Adiacenza
void graph_list_insVertex(GRAPHlist grafo_list, int key) {
    if(idx == 0)    {   //se non è stato indicato manualmente l'indice del vertice, cerco il primo libero
        idx++;
        while(idx <= *((int *)grafo_list[0]) && grafo_list[idx])    //controllo se sono disponibili indici di vertici eliminati in precedenza
            idx++;
        if(idx > *((int *)grafo_list[0]))    {
            *((int *)grafo_list[0]) += 1; //se ho raggiunto il margine (quindi tutti gli indici precedenti a 'idx' sono stati gi� riempiti), aumento il contatore dell'ultimo indice
/*DEBUG*/   if(*((int *)grafo_list[0]) != idx)
                printf("DEBUG: desincronizzazione dell'indice di margine\n\n"); //in tal caso, *((int *)grafo_list[0]) dovr� essere sempre uguale a 'idx'
        }
    }
    GRAPHlistlist G_elem = graph_list_newNode(elemento, idx);
    grafo_list[idx] = G_elem;
    if(grafo_list[idx]) {
        printf("Vertice ");
        graph_printNode(((GRAPHlistlist)grafo_list[idx])->elem, idx, Print);
        printf(" correttamente inserito nella Lista\n");
    }
}

//Allocazione di un nuovo nodo della Lista di Adiacenza
GRAPHlistlist graph_list_newNode(void key, int idx)    {
    GRAPHlistlist G_elem = (struct GrafoLista *)malloc(sizeof(struct GrafoLista));
    G_elem->idx = idx;
    G_elem->elem = elemento;
    G_elem->adj = NULL;
    return G_elem;
}


//Inserimento di un nuovo arco con controllo dei vertici disponibili
void graph_list_insArc(GRAPHlist grafo_list, int idx_src, int idx_dst, int weight, int n_vrtx) {
    if(Print)   {
        int n_edge;
        GRAPHlist G_slave = graph_list_mirror(grafo_list);  //creo la Lista mirror per indicare idx vertici disponibili
        G_slave[idx_src] = NULL;    //rendo non disponibile il vertice di partenza

        graph_printNode(((GRAPHlistlist)grafo_list[idx_src])->elem, idx_src, Print);
        printf(": ");
        n_edge = list_visit(((GRAPHlistlist)grafo_list[idx_src])->adj, Print, *G_slave);    //stampo e conto idx vertici adiacenti
        printf("\n\n");
        if(n_edge < n_vrtx)   {
            printf("Vertici disponibili per ");
            graph_printNode(((GRAPHlistlist)grafo_list[idx_src])->elem, idx_src, Print);
            printf(":\n");
            graph_list_print(G_slave, Print, 0); //mostro idx restanti vertici disponibili; con 0 all'ultimo parametro 'showlist' non mostro le Liste di Adiacenza di questi vertici
            do  {
                printf("A quale indice vuoi collegare il vertice %d? ", ((GRAPHlistlist)grafo_list[idx_src])->idx);    //DEBUG: controllo della coincidenza fra idx_src e idx del vertice
                idx_dst = io_getInteger();
                if(!grafo_list[idx_dst])
                    printf("ATTENZIONE: vertice scelto non presente nel Grafo\n\n");
                else if(!G_slave[idx_dst])
                    printf("ATTENZIONE: arco gi(�) presente per la destinazione scelta\n\n");
            }while(!grafo_list[idx_dst] || !G_slave[idx_dst]);
            do  {
                printf("Quale peso vuoi inserire all'arco? (Numero reale): ");
                weight = io_getInteger();
                if(!weight)
                    printf("ATTENZIONE: valore non valido\n\n");
            }while(!weight);
            graph_list_mirrorFree(G_slave);
        } else  {
            printf("ATTENZIONE: tutti gli archi uscenti sono gi� collegati con tutti gli altri vertici\n\n");
            return;
        }
    }
    if(grafo_list[idx_dst]) {
        ((GRAPHlistlist)grafo_list[idx_src])->adj = list_addHead(((GRAPHlistlist)grafo_list[idx_src])->adj, grafo_list[idx_dst], weight);
        printf("Arco inserito in Lista fra idx vertici %d -> %d di peso [%d]\n", idx_src, idx_dst, ((GRAPHlistlist)grafo_list[idx_src])->adj->peso);
    } else
        printf("ATTENZIONE [errore file]: arco uscente non valido per mancanza del vertice %d", idx_dst); //utile in caso di errori nei valori presenti nel file

}

//Visualizzazione del percorso minimo fra due vertici (BFS)
void graph_list_path(GRAPHlist grafo_list, int i_src, int j_dst)  {
    if(i_src != j_dst)  {
        int *pred = graph_list_BFS((GRAPHlistlist *)grafo_list, i_src);
        graph_list_path_print((GRAPHlistlist *)grafo_list, i_src, j_dst, pred, Print);
    } else
        printf("ATTENZIONE: Sorgente e destinazione coincidono\n\n");
}

//Visita in ampiezza con creazione e ritorno dell'array degli indici dei predecessori
int *graph_list_BFS(GRAPHlistlist *grafo_list, int i_src)  {
    int idx, i_max = *((int *)grafo_list[0]);
    int *pred = (int *)malloc(sizeof(int) * i_max);    //creo l'array degli indici dei predecessori

    char *color = (char *)malloc(sizeof(char) * i_max);   //creo l'array dei colori associati ai vertici, quantificati in grafo_list[0]

    QUEUE coda = queue_init(i_max);  //creo una coda che ha una grandezza massima del numero dei vertici del Grafo
    LISTadj adj_curr = NULL; //prendo gli elementi della lista di adiacenza del vertice estratto dalla coda

    for(idx=1;idx<i_max;idx++)    {       //inizializzazione grafo
        if(grafo_list[idx] && idx != i_src) {
            color[idx] = 'w';
            pred[idx] = -1;
        }
    }

    color[i_src] = 'g'; //GRIGIO sul vertice sorgente
    pred[i_src]= -1;  //che non ha predecessori
    queue_enqueue(coda, i_src);
    while(!queue_check_empty(coda))    {    //ciclo fin quando non svuoto la coda
        idx = queue_dequeue(coda);    //estraggo la testa della Coda
        adj_curr = grafo_list[idx]->adj;  //prendo la Lista di Adiacenza
        while(adj_curr) {
            if(color[adj_curr->node->idx] == 'w')  { //se BIANCO
                color[adj_curr->node->idx] = 'g';   //coloro di GRIGIO
                pred[adj_curr->node->idx] = idx;      //assegno il suo predecessore
                queue_enqueue(coda, adj_curr->node->idx);   //inserisco l'indice nella coda per le future iterazioni
            }
            adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
        }
        color[idx] = 'b';  //completo la visita del nodo in NERO
    }
    free(color);
    free(coda);
    return pred;
}

//Stampa del percorso minimo fra due vertici definito dall'array dei predecessori
void graph_list_path_print(GRAPHlistlist *grafo_list, int i_src, int j, int *pred)  {
    if(i_src == j)
        graph_printNode(grafo_list[i_src]->elem, i_src, Print);
    else if(pred[j] == -1)
        printf("ATTENZIONE: non esiste alcun cammino tra la sorgente e la destinazione scelta \n\n");
    else    {
        graph_list_path_print(grafo_list, i_src, pred[j], pred, Print);
        graph_printNode(grafo_list[j]->elem, j, Print);
    }
}

//F6: Eliminazione del Grafo con annessi Liste di Adiacenza
GRAPHlist graph_list_deleteGRAPHlist(GRAPHlist grafo_list) {
    int idx, i_max = *((int *)grafo_list[0]);
    free(grafo_list[0]);
    for(idx=1;idx<=i_max;idx++){
        if(grafo_list[idx])
            grafo_list[idx] = graph_list_nodeFree(grafo_list[idx]);
    }
    return NULL;
}


//F7: Eliminazione del vertice con idx relativi archi entranti; ; ritorna il numero di vertici aggiornato
int graph_list_delVertex(GRAPHlist grafo_list, int idx_del, int n_vrtx)  {
    int idx;
    for(idx=1;idx<=*((int *)grafo_list[0]);idx++) {
        if(grafo_list[idx] && idx!=idx_del)
            ((GRAPHlistlist)grafo_list[idx])->adj = list_delArc(((GRAPHlistlist)grafo_list[idx])->adj, idx_del); //CHECK: passaggio del riferimento
        else if(idx==idx_del)    //elimino subito il vertice dell'indice scelto con la relativa lista
            grafo_list[idx] = graph_list_nodeFree(grafo_list[idx]);
    }
    if(idx_del == *((int *)grafo_list[0])) //aggiorno anche il valore del margine massimo dell'array
        *((int *)grafo_list[0]) -= 1;
    return n_vrtx-1;
}


//Liberazione della memoria allocata dinamicamente del vertice
GRAPHlistlist graph_list_nodeFree(GRAPHlistlist G_curr)	{
	G_curr->adj = list_delete(G_curr->adj);
	free(G_curr->elem);
	free(G_curr);
	return NULL;
}


//F8: Eliminazione dell'arco con controllo dei vertici adiacenti
void graph_list_delArc(GRAPHlist grafo_list, int idx_src) {
    if(((GRAPHlistlist)grafo_list[idx_src])->adj)    {
        int idx_del;
        GRAPHlist G_slave = NULL;
        G_slave = graph_list_mirror(grafo_list);
        graph_printNode(((GRAPHlistlist)grafo_list[idx_src])->elem, idx_src, Print);
        printf(": ");
        list_visit(((GRAPHlistlist)grafo_list[idx_src])->adj, Print, *G_slave);    //stampo e conto idx vertici adiacenti
        printf("\n\n");
        do  {
            printf("Quale indice dell'arco uscente vuoi eliminare dal vertice %d? ", ((GRAPHlistlist)grafo_list[idx_src])->idx);    //attualmente in uso come DEBUG per controllare se l'indice del vettore coincide con l'indice del dato interno
            idx_del = io_getInteger();
            if(G_slave[idx_del])    //in tal caso G_slave ha tutti gli archi uscenti mancanti
                printf("ATTENZIONE: arco NON presente per la destinazione scelta\n\n");
        }while(G_slave[idx_del]);
        ((GRAPHlistlist)grafo_list[idx_src])->adj = list_delArc(((GRAPHlistlist)grafo_list[idx_src])->adj, idx_del);    //eliminazione dell'arco
        graph_list_mirrorFree(G_slave);
    } else
        printf("ATTENZIONE: il vertice scelto non ha archi uscenti\n\n");
}

//F9: Conversione della struttura dati del Grafo da Lista di Adiacenza a Matrice

//N.B.: durante la conversione non verr� allocata nuova memoria. Verr� solo rilasciata la memoria per le Liste e per l'array struct GrafoLista
GRAPHlist graph_list_convert(GRAPHlist grafo_list)  {
    GRAPHlist grafo_mtrx = graph_mtrx_init(-1);  //con il parametro '-1' non alloco un nuovo contatore, siccome lo prendo da grafo_list
    LISTadj adj_curr = NULL;
    LISTadj adj_tmp = NULL;

    ((GRAPHlist)grafo_mtrx[0])[0] = grafo_list[0];   //prendo il riferimento, non copio il valore
    int idx;
    for(idx=1;idx<=*((int *)((GRAPHlist)grafo_mtrx[0])[0]);idx++)    {
        if(grafo_list[idx])
            graph_mtrx_insVertex(grafo_mtrx, idx, ((GRAPHlistlist)grafo_list[idx])->elem, Print);
    }

    printf("\n");

    for(idx=1;idx<=*((int *)((GRAPHlist)grafo_mtrx[0])[0]);idx++)    {
        if(grafo_list[idx]) {
            adj_curr = ((GRAPHlistlist)grafo_list[idx])->adj;   //prendo la Lista di Adiacenza del vertice attuale
            while(adj_curr) {
                graph_mtrx_insArc(grafo_mtrx, idx, adj_curr->node->idx, adj_curr->peso, NULL, -1);

                adj_curr->node = NULL;  //tolgo il riferimento al nodo, per evitare la perdita del dato nella deallocazione
                adj_tmp = adj_curr;
                adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente

                adj_tmp->next = NULL;   //tolgo il riferimento all'elemento successivo, per evitare la perdita del dato nella deallocazione
                free(adj_tmp);
            }
            ((GRAPHlistlist)grafo_list[idx])->elem = NULL;    //tolgo il riferimento al dato generico, per evitare la perdita del dato nella deallocazione
        }
    }
    free(grafo_list);   //deallocazione della Lista di Adiacenza
    return grafo_mtrx;
}


//F10: Trasposizione del Grafo in maniera efficiente T(n) = |V| + |E| e senza allocazione di nuova memoria, e con cambio dei riferimenti dei vertici
void graph_list_transpose(GRAPHlist grafo_list)    {
    int idx, i_max = *((int *)grafo_list[0]);
    LISTadj *L_arr_adj = NULL;    //creo un array con idx riferimenti alle Liste di Adiacenza di ogni vertice
    L_arr_adj = (struct ListaAdj **)malloc(sizeof(struct ListaAdj *) * i_max);

    for(idx=1;idx<=i_max;idx++) {  //Inizializzazione con copia dei riferimenti alle Liste
        if(grafo_list[idx])   {
            L_arr_adj[idx] = ((GRAPHlistlist)grafo_list[idx])->adj;     //memorizzo idx riferimenti nell'array delle Liste
            ((GRAPHlistlist)grafo_list[idx])->adj = NULL;             //tolgo idx riferimenti nel grafo per gli inserimenti di 'list_trasp_recv'
        }
    }
    for(idx=1;idx<=i_max;idx++) {  //Visita delle Liste e inserimento dei vertici nel grafo trasposto
        if(grafo_list[idx])
            L_arr_adj[idx] = list_trasp_recv(L_arr_adj[idx], ((GRAPHlistlist *)grafo_list), idx);    //N.B.: L_arr_adj[idx] diventa NULL, quindi nessuna perdita di dati in deallocazione
    }
    free(L_arr_adj);
}



//F11: Ricerca nel grafo di un arco di ritorno, ovvero di un ciclo
void graph_list_check_cycle(GRAPHlist grafo_list)  {
    int idx=1;
    while(!grafo_list[idx])   //vedo l'indice minimo del primo elemento presente attualmente nel grafo
        idx++;
    if(graph_list_DFS((GRAPHlistlist *)grafo_list, idx))  //se c'� un ciclo, lo notifico
        printf("Il grafo contiene un ciclo\n\n");
    else
        printf("Il grafo NON contiene un ciclo\n\n");
}


//Visita in profondit� con verifica di ciclicit�
int graph_list_DFS(GRAPHlistlist *grafo_list, int i_src)  {
    int idx, i_max = *((int *)grafo_list[0]), check_cycle = 0; //intero che controlla l'effettiva presenza di un ciclo
    int *pred = (int *)malloc(sizeof(int) * i_max);    //per futura utitlit�, dispongo anche l'array degli indici dei predecessori

    char *color = (char *)malloc(sizeof(char) * i_max);   //creo l'array dei colori associati ai vertici, quantificati in grafo_list[0]

    LISTadj adj_curr = NULL; //prendo gli elementi della lista di adiacenza del vertice estratto dalla coda

    for(idx=i_src;idx<=i_max;idx++)    {       //inizializzazione grafo
        if(grafo_list[idx])
            color[idx] = 'w';
            pred[idx] = -1;
    }

    adj_curr = grafo_list[i_src]->adj;   //prendo la Lista di Adiacenza del primo elemento
    while(adj_curr) {
        if(color[adj_curr->node->idx] == 'w')   //se BIANCO
            check_cycle = graph_list_DFS_visit(grafo_list, adj_curr->node->idx, pred, color, check_cycle); //visito l'elemento della lista di adiacenza
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
    }
    free(color);
    return check_cycle;
}

//Durante la visita in profondit�, posso notificare la presenza di un ciclo all'interno del grafo
int graph_list_DFS_visit(GRAPHlistlist *grafo_list, int idx_curr, int *pred, char *color, int check_cycle)    {
    LISTadj adj_curr = grafo_list[idx_curr]->adj; //prendo gli elementi della lista di adiacenza del vertice attuale
    color[idx_curr] = 'g'; //GRIGIO sul vertice attuale

    while(adj_curr)    {    //ciclo fin quando non svuoto la coda
        if(color[adj_curr->node->idx] == 'w')  { //se BIANCO
            pred[adj_curr->node->idx] = idx_curr;       //applico l'attuale vertice come predecessore di questo nodo adiacente
            check_cycle = graph_list_DFS_visit(grafo_list, adj_curr->node->idx, pred, color, check_cycle);    //visito il nodo appena incontrato
        } else if(!check_cycle && color[adj_curr->node->idx] == 'g')       //se mi ritrovo un GRIGIO, � un arco di ritorno (ciclo)
            check_cycle = 1;    //N.B.: � consono continuare l'algoritmo, invece di ritornare subito la notifica
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
    }
    color[idx_curr] = 'b';  //completo la visita del nodo in NERO
    return check_cycle;
}


//F4: Stampa del Grafo con le Liste di Adiacenza dei rispettivi vertici
void graph_list_print(GRAPHlist grafo_list, int showlist)   {
    int idx;
    for(idx=1;idx<=*((int *)grafo_list[0]);idx++) {
        if(grafo_list[idx])   {
            graph_printNode(((GRAPHlistlist)grafo_list[idx])->elem, idx, Print);
            if(showlist)    //si pu� richiedere dal parametro 'showlist' di mostrare la Lista di Adiacenza del vertice in esame
                printf(":");
                list_visit(((GRAPHlistlist)grafo_list[idx])->adj, Print, NULL);
            printf("\n");
        }
    }
}

//Copia idx riferimenti dei nodi del Grafo, utile per reperire la disponibilit� e idx dati dei nuovi vertici adiacenti a tempo costante
GRAPHlist graph_list_mirror(GRAPHlist grafo_list)    {
    int idx, i_max = *((int *)grafo_list[0]);

    GRAPHlist G_slave = NULL;
    G_slave = malloc(sizeof(struct GrafoLista *) * i_max);  //CHECK: forse inutile; Allocazione del vettore di supporto dei puntatori

    for(idx=0;idx<=i_max;idx++)
        G_slave[idx] = grafo_list[idx];
    return G_slave;
}

//Liberazione dell'array dei riferimenti
void graph_list_mirrorFree(GRAPHlist G_slave)    {
    int idx, i_max = *((int *)G_slave[0]);
    for(idx=0;idx<i_max;idx++)    {
        G_slave[idx] = NULL;
    }
    free(G_slave);
}
