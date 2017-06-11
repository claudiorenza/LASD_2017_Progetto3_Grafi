/*Solo alla sorgente, si cerca un arco in salita; durante la visita, invece, vedo i percorsi solo in salita se la destinazione
è più in alto rispetto alla posizione attuale, altrimenti posso vedere sia in salita che in discesa.
Appena si passa ad un nodo in cui arco è in discesa, tutti i successivi nodi da visitare dovranno essere in discesa.
Usare parametro "isDiscesa", che si comporta come la mancanza di archi adiacenti per un nodo.

Nella creazione del grafo, creare un percorso idoneo allo sviluppo dell'algoritmo, creando anche percorsi alternativi più brevi
ma che non rispettano i vincoli proposti dalla traccia, sia un percorso alternativo valido ma con pesi diversi


*/


//Visita in profondità con verifica di ciclicità
void *graph_sp_DFS(GRAPHlist grafo_lista, int idx_src, int idx_dst)  {
    int idx;
    SUCC *sp_succ_up = (struct Successore **)calloc(grafo_lista->idx_max, sizeof(struct Successore *));    //creo l'array degli indici dei Successori per percorsi in salita
    SUCC *sp_succ_down = (struct Successore **)calloc(grafo_lista->idx_max, sizeof(struct Successore *));    //creo l'array degli indici dei Successori per percorsi in discesa

    char *color = (char *)malloc(sizeof(char) * grafo_lista->idx_max);   //creo l'array dei colori associati ai vertici


    for(idx=0;idx<grafo_lista->idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_lista->vrtx[idx]) {
            color[idx] = 'w';

            sp_succ_up[idx] = (struct Successore *)malloc(sizeof(struct Successore));
            sp_succ_up[idx]->succ = -1;
            sp_succ_up[idx]->dist = INF;

            sp_succ_down[idx]  = (struct Successore *)malloc(sizeof(struct Successore));
            sp_succ_down[idx]->succ = -1;   
            sp_succ_down[idx]->dist = INF;
        }
    }

    adj_curr = grafo_lista->vrtx[idx_src]->adj;   //prendo la Lista di Adiacenza del primo elemento
    graph_list_DFS_visit(grafo_lista, idx_src, idx_dst, color); //visito l'elemento della lista di adiacenza
    free(color);

    graph_sp_printPath;
}

//Durante la visita in profondità, cerco se nell'albero di copertura dalla sorgente esiste un percorso che raggiunge la destinazione
int graph_sp_DFS_visit(GRAPHlist grafo_lista, int idx_curr, int idx_dst, char *color)    {
    LIST adj_curr = grafo_lista->vrtx[idx_curr]->adj; //prendo gli elementi della lista di adiacenza del vertice attuale

    color[idx_curr] = 'g'; //GRIGIO sul vertice attuale
    if(idx_curr != idx_dst) {
        while(adj_curr)    {    //ciclo fin quando non svuoto la coda
            if(color[adj_curr->idx_vrtx_dst] == 'w')  { //se BIANCO
                ret = graph_list_DFS_visit(grafo_lista, adj_curr->idx_vrtx_dst, pred, color);    //visito il nodo appena incontrato
            }
            adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
        }
        color[idx_curr] = 'b';  //completo la visita del nodo in NERO
    }
}

    while(adj_curr)    {    //ciclo fin quando non svuoto la lista di adiacenza
        if(sp_succ[adj_curr->idx_vrtx_dst] != -1)  { //se BIANCO
            SUCC[adj_curr->idx_vrtx_dst] = idx_curr;       //applico l'attuale vertice come Successore di questo nodo adiacente
            graph_list_DFS_visit(grafo_lista, adj_curr->idx_vrtx_dst, SUCC);    //visito il nodo appena incontrato
        } else  {
            if(sp_succ[idx]->dist + adj_curr->weight < sp_succ[adj_curr->idx_vrtx_dst]->dist)   {
                sp_succ[adj_curr->idx_vrtx_dst]->SUCC = idx;      //assegno il suo Successore
                sp_succ[adj_curr->idx_vrtx_dst]->dist = sp_succ[idx]->dist + adj_curr->weight;
            }
        }
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
    }
}





//Semplificazione delle condizioni per l'inserimento in coda di elementi adiacenti
//N.B.: per una migliore comprensione, invece di inserire tutte le condizioni in un unico 'if', possiamo analizzare separatamente i casi validi per l'inserimento in coda
int graph_sp_conditionAdj(int idx, int idx_src, int idx_dst, LIST adj_curr, SUCC *bfs_SUCC)  {
    int ret = 0;    //inizializzazione a 0 (nel caso nessuna condizione sia verificata, la funzione ritornerà 0)
    if(idx == idx_src || idx < idx_dst) {   //Se parto dalla sorgente, oppure la destinazione è situata più in alto e sei appena salito,
        if(idx < adj_curr->idx_vrtx_dst)   {        //devo necessariamente salire, selezionando solo i nodi adiacenti in salita.
            if(adj_curr->idx_vrtx_dst != idx_dst)       //Se salendo non trovo già la destinazione,
                ret = 1;                            //inserisco il nodo adiacente in coda.
        }
    } else if(idx > idx_dst)    {           //Se, invece, mi trovo più in alto rispetto alla destinazione,
        if(bfs_SUCC[idx]->SUCC < idx)    {      //se il Successore è più in basso rispetto alla posizione attuale (ho appena effettuato una salita)
            if(idx < adj_curr->idx_vrtx_dst && adj_curr->idx_vrtx_dst != idx_dst) //e salendo non trovo già la destinazione,
                ret = 1;                            //inserisco il nodo adiacente in coda.
            else if(idx > adj_curr->idx_vrtx_dst)       //In caso di discesa,
                ret = 1;                            //non esiste discriminante per l'inserimento.
        } else {                                //Se il Successore è più in alto rispetto alla posizione attuale (ho appena effettuato una discesa),
            if(idx > adj_curr->idx_vrtx_dst && idx > idx_dst) //devo necessariamente scendere, non andando oltre al di sotto del nodo di destinazione
                ret = 1;                            //inserendo solo i nodi adiacenti in discesa.
        }                    
    }
    //N.B.: se "idx" è attualmente il nodo di destinazione "idx_dst", non visito i suoi nodi adiacenti (non entrerò in alcuna 'if' e ritornerò 0),
    //siccome dovrò eventualmente confrontare gli altri percorsi provenienti dai suoi adiacenti, come archi entranti 
    return ret;
}
