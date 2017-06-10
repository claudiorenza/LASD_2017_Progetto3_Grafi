/*Solo alla sorgente, si cerca un arco in salita; durante la visita, invece, vedo i percorsi solo in salita se la destinazione
è più in alto rispetto alla posizione attuale, altrimenti posso vedere sia in salita che in discesa.
Appena si passa ad un nodo in cui arco è in discesa, tutti i successivi nodi da visitare dovranno essere in discesa.
Usare parametro "isDiscesa", che si comporta come la mancanza di archi adiacenti per un nodo.

Nella creazione del grafo, creare un percorso idoneo allo sviluppo dell'algoritmo, creando anche percorsi alternativi più brevi
ma che non rispettano i vincoli proposti dalla traccia, sia un percorso alternativo valido ma con pesi diversi


*/

PRED *graph_sp_BFS(GRAPHlist grafo_lista, int idx_src, int idx_dst)   {
    int idx;
    PRED *sp_pred = (struct Predecessore **)calloc(grafo_list->idx_max, sizeof(struct Predecessore *));    //creo l'array degli indici dei predecessori

    QUEUE coda = queue_init(grafo_list->idx_max);  //creo una coda che ha una grandezza massima del numero dei vertici del Grafo
    LIST adj_curr = NULL; //prendo gli elementi della lista di adiacenza del vertice estratto dalla coda

    for(idx=0;idx<grafo_list->idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_list->vrtx[idx]) {
            sp_pred[idx] = (struct Predecessore *)malloc(sizeof(struct Predecessore));
            sp_pred[idx]->pred = -1;
            sp_pred[idx]->dist = INF;
        }
    }

    sp_pred[idx_src]->pred= -1;  //che non ha predecessori
    sp_pred[idx]->dist = 0;
    queue_enqueue(coda, idx_src);   //inserisco in coda la sorgente
    while(!queue_check_empty(coda))    {    //ciclo fin quando non svuoto la coda
        idx = queue_dequeue(coda);    //estraggo la testa della Coda
        adj_curr = grafo_list->vrtx[idx]->adj;  //prendo la Lista di Adiacenza dell'elemento appena estratto
        while(adj_curr) {
            if(sp_pred[adj_curr->idx_vrtx_dst]->pred != -1)  { //se non ha un predecessore
                sp_pred[adj_curr->idx_vrtx_dst]->pred = idx;      //assegno il suo predecessore
                sp_pred[adj_curr->idx_vrtx_dst]->dist = sp_pred[idx]->dist + adj_curr->weight;
                queue_enqueue(coda, adj_curr->idx_vrtx_dst);   //inserisco l'indice nella coda per le future iterazioni
            } else  {
                if(sp_pred[idx]->dist + adj_curr->weight < sp_pred[adj_curr->idx_vrtx_dst]->dist)   {
                    sp_pred[adj_curr->idx_vrtx_dst]->pred = idx;      //assegno il suo predecessore
                    sp_pred[adj_curr->idx_vrtx_dst]->dist = sp_pred[idx]->dist + adj_curr->weight;
                }
            }
            adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
        }
    }
    free(color);
    free(coda);
    return sp_pred;


}

//Visita in profondità con verifica di ciclicità
PRED *graph_sp_DFS(GRAPHlist grafo_list, int idx_src, int idx_dst)  {
    int idx; //intero che controlla l'effettiva presenza di un ciclo
    PRED *sp_pred = (struct Predecessore **)calloc(grafo_list->idx_max, sizeof(struct Predecessore *));    //creo l'array degli indici dei predecessori

    LIST adj_curr = NULL; //prendo gli elementi della lista di adiacenza del vertice estratto dalla coda

    for(idx=0;idx<grafo_list->idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_list->vrtx[idx]) {
            sp_pred[idx] = (struct Predecessore *)malloc(sizeof(struct Predecessore));
            sp_pred[idx]->pred = -1;
            sp_pred[idx]->dist = INF;
        }
    }

    adj_curr = grafo_list->vrtx[idx_src]->adj;   //prendo la Lista di Adiacenza del primo elemento
    while(adj_curr) {
        if(sp_pred[adj_curr->idx_vrtx_dst]->pred != -1)   //se non visitato
            graph_list_DFS_visit(grafo_list, adj_curr->idx_vrtx_dst, pred); //visito l'elemento della lista di adiacenza
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
    }
    free(color);
    return pred;
}

//Durante la visita in profondità, posso notificare la presenza di un ciclo all'interno del grafo
void graph_sp_DFS_visit(GRAPHlist grafo_list, int idx_curr, PRED *sp_pred)    {
    LIST adj_curr = grafo_list->vrtx[idx_curr]->adj; //prendo gli elementi della lista di adiacenza del vertice attuale

    while(adj_curr)    {    //ciclo fin quando non svuoto la coda
        if(sp_pred[adj_curr->idx_vrtx_dst]->pred != -1)  { //se BIANCO
            pred[adj_curr->idx_vrtx_dst] = idx_curr;       //applico l'attuale vertice come predecessore di questo nodo adiacente
            graph_list_DFS_visit(grafo_list, adj_curr->idx_vrtx_dst, pred);    //visito il nodo appena incontrato
        } else  {
            if(sp_pred[idx]->dist + adj_curr->weight < sp_pred[adj_curr->idx_vrtx_dst]->dist)   {
                sp_pred[adj_curr->idx_vrtx_dst]->pred = idx;      //assegno il suo predecessore
                sp_pred[adj_curr->idx_vrtx_dst]->dist = sp_pred[idx]->dist + adj_curr->weight;
            }
        }
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
    }
}





//Semplificazione delle condizioni per l'inserimento in coda di elementi adiacenti
//N.B.: per una migliore comprensione, invece di inserire tutte le condizioni in un unico 'if', possiamo analizzare separatamente i casi validi per l'inserimento in coda
int graph_sp_conditionAdj(int idx, int idx_src, int idx_dst, LIST adj_curr, PRED *bfs_pred)  {
    int ret = 0;    //inizializzazione a 0 (nel caso nessuna condizione sia verificata, la funzione ritornerà 0)
    if(idx == idx_src || idx < idx_dst) {   //Se parto dalla sorgente, oppure la destinazione è situata più in alto e sei appena salito,
        if(idx < adj_curr->idx_vrtx_dst)   {        //devo necessariamente salire, selezionando solo i nodi adiacenti in salita.
            if(adj_curr->idx_vrtx_dst != idx_dst)       //Se salendo non trovo già la destinazione,
                ret = 1;                            //inserisco il nodo adiacente in coda.
        }
    } else if(idx > idx_dst)    {           //Se, invece, mi trovo più in alto rispetto alla destinazione,
        if(bfs_pred[idx]->pred < idx)    {      //se il predecessore è più in basso rispetto alla posizione attuale (ho appena effettuato una salita)
            if(idx < adj_curr->idx_vrtx_dst && adj_curr->idx_vrtx_dst != idx_dst) //e salendo non trovo già la destinazione,
                ret = 1;                            //inserisco il nodo adiacente in coda.
            else if(idx > adj_curr->idx_vrtx_dst)       //In caso di discesa,
                ret = 1;                            //non esiste discriminante per l'inserimento.
        } else {                                //Se il predecessore è più in alto rispetto alla posizione attuale (ho appena effettuato una discesa),
            if(idx > adj_curr->idx_vrtx_dst && idx > idx_dst) //devo necessariamente scendere, non andando oltre al di sotto del nodo di destinazione
                ret = 1;                            //inserendo solo i nodi adiacenti in discesa.
        }                    
    }
    //N.B.: se "idx" è attualmente il nodo di destinazione "idx_dst", non visito i suoi nodi adiacenti (non entrerò in alcuna 'if' e ritornerò 0),
    //siccome dovrò eventualmente confrontare gli altri percorsi provenienti dai suoi adiacenti, come archi entranti 
    return ret;
}
