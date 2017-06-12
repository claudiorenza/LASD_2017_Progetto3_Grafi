/*Solo alla sorgente, si cerca un arco in salita; durante la visita, invece, vedo i percorsi solo in salita se la destinazione
è più in alto rispetto alla posizione attuale, altrimenti posso vedere sia in salita che in discesa.
Appena si passa ad un nodo in cui arco è in discesa, tutti i successivi nodi da visitare dovranno essere in discesa.
Usare parametro "isDiscesa", che si comporta come la mancanza di archi adiacenti per un nodo.

Nella creazione del grafo, creare un percorso idoneo allo sviluppo dell'algoritmo, creando anche percorsi alternativi più brevi
ma che non rispettano i vincoli proposti dalla traccia, sia un percorso alternativo valido ma con pesi diversi


*/

//Visita in profondità dal solo albero di copertura partente dalla sorgente con applicazione dei vincoli
int *graph_sp_DFS(GRAPHlist grafo_lista, int idx_src, int idx_dst)  {
    int idx;
    int *pred = (int *)malloc(sizeof(int) * (grafo_lista->idx_max)+1);    //per futura utilità, dispongo anche l'array degli indici dei predecessori

    char *color = (char *)malloc(sizeof(char) * (grafo_lista->idx_max)+1);   //creo l'array dei colori associati ai vertici, quantificati in grafo_lista[0]

    for(idx=0;idx<=grafo_lista->idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_lista->vrtx[idx]->adj)
            color[idx] = 'w';
            pred[idx] = -1;
    }
    //N.B.: per poter riconoscere la presenza di (almeno) un percorso che raggiunga la destinazione, non visiterò altre radici bianchi al di fuori della sorgente
    graph_sp_DFS_visit(vrtx, idx_src, idx_src idx_dst, pred, color, 1); //parto solo dalla radice

    free(color);
    return pred;
}

//Durante la visita in profondità ricorsiva
void graph_sp_DFS_visit(GRAPHvrtx *vrtx, int idx_curr, int idx_src, int idx_dst, int *pred, char *color, int isAscent)    {
    LIST adj_curr = vrtx[idx_curr]->adj; //prendo gli elementi della lista di adiacenza del vertice attuale
    color[idx_curr] = 'g'; //GRIGIO sul vertice attuale

    while(adj_curr)    {    //ciclo fin quando non svuoto la Lista
        if(color[adj_curr->idx_vrtx_dst] == 'w' && graph_sp_conditionElev(vrtx[idx_curr]->height, vrtx[adj_curr->idx_vrtx_dst]->height,
                                                                        isAscent, vrtx[idx_src]->height, vrtx[idx_dst]->height))  { //se BIANCO
            pred[adj_curr->idx_vrtx_dst] = idx_curr;       //applico l'attuale vertice come predecessore di questo nodo adiacente

            if(isAscent && (vrtx[idx_curr]->height > vrtx[adj_curr->idx_vrtx_dst]->height)) //se il successore nella visita va in discesa
                isAscent = 0; //da ora in poi valgono solo percorsi in discesa

            graph_sp_DFS_visit(grafo_lista, adj_curr->idx_vrtx_dst, idx_src, idx_dst, pred, color, isAscent);    //visito il nodo appena incontrato
        }
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
    }
    color[idx_curr] = 'b';  //completo la visita del nodo in NERO
}



//Semplificazione delle condizioni per l'inserimento in coda di elementi adiacenti
//N.B.: per una migliore comprensione, invece di inserire tutte le condizioni in un unico 'if', possiamo analizzare separatamente i casi validi per l'inserimento in coda
int graph_sp_conditionElev(int height_curr, int height_adj, int isAscent, int height_src, int height_dst)  {
    int ret = 0;    //inizializzazione a 0 (nel caso nessuna condizione sia verificata, la funzione ritornerà 0)
    if(height_src == height_curr || height_curr <= height_dst) {   //Se parto dalla sorgente, oppure la destinazione è situata più in alto,
        if(height_curr <= height_adj)   {        //devo necessariamente salire o passare all'adiacente posto alla stessa altitudine.
            if(height_adj != height_dst)       //Se salendo non trovo già la destinazione,
                ret = 1;                            //inserisco il nodo adiacente in coda.
        }
    } else if(height_curr > height_dst)    {    //Se, invece, mi trovo più in alto rispetto alla destinazione,
        if(isAscent)    {                       //Se sto salendo (il predecessore è più in basso, oppure salivo dopo aver passato un'intersezione posta allo stesso livello)  
            ret = 1;                            //posso sia salire che scendere, o percorrere l'adiacente posto alla stessa altitudine
        } else {                                //Se sto scendendo (il predecessore è più in alto, oppure scendevo dopo aver passato un'intersezione posta allo stesso livello),
            if(height_curr => height_adj && height_adj => height_dst) //devo necessariamente scendere, o percorrere l'adiacente posto alla stessa altitudine, non andando oltre al di sotto del nodo di destinazione
                ret = 1;                            //inserendo solo i nodi adiacenti in discesa.
        }                    
    }
    return ret;
}





//Visita e calcolo delle distanze a ritroso, dalla destinazione
void graph_sp_calculate(GRAPHlist grafo_lista, int *pred, int idx_src, int idx_dst)  {
    int idx;
    int *vrtx_visited = (int *)calloc((grafo_lista->idx_max)+1, sizeof(int)); //array dei vertici visitati con le distanze calcolate, inizializzati a 0
    SUCC *sp_succ_up = (struct Successore **)calloc((grafo_lista->idx_max)+1, sizeof(struct Successore *));    //creo l'array degli indici dei Successori per percorsi in salita
    SUCC *sp_succ_down = (struct Successore **)calloc((grafo_lista->idx_max)+1, sizeof(struct Successore *));    //creo l'array degli indici dei Successori per percorsi in discesa

    for(idx=0;idx<=grafo_lista->idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_lista->vrtx[idx]) {
            sp_succ_up[idx] = (struct Successore *)malloc(sizeof(struct Successore));
            sp_succ_up[idx]->succ = -1;
            sp_succ_up[idx]->dist = INF;

            sp_succ_down[idx]  = (struct Successore *)malloc(sizeof(struct Successore));
            sp_succ_down[idx]->succ = -1;   
            sp_succ_down[idx]->dist = INF;
        }
    }

    
    sp_succ_up[idx_dst]->dist = 0;      //inizializzazione distanza del percorso dal nodo di destinazione
    sp_succ_down[idx_dst]->dist = 0;

    graph_sp_calculate_visit(vrtx, pred, sp_succ_up, sp_succ_down, idx_src, idx_dst, 1); //visito l'elemento della lista di adiacenza, con rilevazione della salita dalla destinazione

    graph_sp_printPath(vrtx, sp_succ_up, sp_succ_down, idx_src, idx_dst);
}

//Durante la visita in ampiezza di ogni nodo predecessore, vengono registrati i successori a salire e a scendere a partire dalla sorgente
void graph_sp_calculate_visit(GRAPHvrtx *vrtx, int *pred, int idx_curr, SUCC *sp_succ_up, SUCC *sp_succ_down, int idx_src, int isAscent, int *vrtx_visited)    {
    LIST adj_curr = vrtx[idx_curr]->adj; //prendo gli elementi della lista di adiacenza del vertice attuale
    int idx_pred;   //indice del predecessore
    printf("DEBUG: visita [%d]%d\n", idx_curr, vrtx[idx_curr]->height);
    while(adj_curr)    {    //ciclo fin quando non svuoto la lista di adiacenza
        printf("DEBUG: adj [%d]%d\n", adj_curr->idx_vrtx_dst, vrtx[adj_curr->idx_vrtx_dst]->height);
        if(adj_curr->idx_vrtx_dst != pred[idx_curr])     { //se l'adiacente non è un predecessore
            if(!vrtx_visited[adj_curr->idx_vrtx_dst] && graph_sp_conditionElev(vrtx[idx_curr]->height, vrtx[adj_curr->idx_vrtx_dst]->height, !isAscent, vrtx[idx_src]->height, vrtx[idx_dst]->height)) { //controllo se un adiacente è elegibile per la visita in profondità, escludendo vertici già calcolati
                if((graph_sp_conditionSucc_high(vrtx[idx_curr]->height, vrtx[adj_curr->idx_vrtx_dst]->height, !isAscent) && sp_succ_up[idx_curr]->succ != adj_curr->idx_vrtx_dst) //se l'ADIACENTE è posto più in alto e non è associato come suo successore a salire
                || (graph_sp_conditionSucc_low(vrtx[idx_curr]->height, vrtx[adj_curr->idx_vrtx_dst]->height, !isAscent) && sp_succ_down[idx_curr]->succ != adj_curr->idx_vrtx_dst)) { //oppure l'ADIACENTE è posto più un basso e non è associato come suo successore a scendere
                    if(!isAscent && (vrtx[idx_curr]->height > vrtx[adj_curr->idx_vrtx_dst]->height)) //se, continuando il percorso a ritroso ero in discesa e l'adiacente da visitare in DFS è in discesa
                        graph_sp_calculate_DFS_visit(vrtx, pred, adj_curr->idx_vrtx_dst, sp_succ_up, sp_succ_down, idx_src, idx_dst, isAscent, vrtx_visited) //visito in profondità i vertici che partono da questa adiacenza per vedere se esistono percorsi alternativi migliori
                    else
                        graph_sp_calculate_DFS_visit(vrtx, pred, adj_curr->idx_vrtx_dst, sp_succ_up, sp_succ_down, idx_src, idx_dst, !isAscent, vrtx_visited) //visito in profondità i vertici che partono da questa adiacenza per vedere se esistono percorsi alternativi migliori
                        
                    
                    
                //N.B.: se attualmente la visita dei predecessori viene effettuata a ritroso, isAscent dovra essere l'opposto siccome questa visita verrà effettuata in avanti
                


                //se il percorso trovato dalla DFS ha una distanza minore rispetto a quella del suo successore attuale, effettuo lo scambio
                }
            }   
        }else   //se è un predecessore
            idx_pred = adj_curr->idx_vrtx_dst; //mi salvo temporaneamente questo indice
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente        
    }
    //Calcolo distanze con il PREDECESSORE
    if(graph_sp_conditionSucc_high(vrtx[idx_curr]->height, vrtx[idx_pred]->height, isAscent) //se il PREDECESSORE si trova più in alto, oppure alla stessa altezza e si sta salendo lungo il percorso a ritroso
    && sp_succ_down[idx_curr]->dist + adj_curr->weight < sp_succ_down[idx_pred]->dist) {  //con la distanza calcolata fino a quel punto più il peso dell'arco minore della distanza calcolata nell'adiacente
        sp_succ_down[idx_pred]->succ = idx_curr; //assegno il nodo attuale come successore a scendere del nodo PREDECESSORE
        sp_succ_down[idx_pred]->dist = sp_succ_down[idx_curr]->dist + adj_curr->weight;   //e aggiorno la distanza accumulata con il peso dell'arco visitato
    } else if(graph_sp_conditionSucc_low(vrtx[idx_curr]->height, vrtx[idx_pred]->height, isAscent) //se il PREDECESSORE si trova più in basso, oppure alla stessa altezza e si sta scendendo lungo il percorso a ritroso
    && sp_succ_up[idx_curr]->dist + adj_curr->weight < sp_succ_up[idx_pred]->dist) {   //con la distanza calcolata fino a quel punto più il peso dell'arco minore della distanza calcolata nell'adiacente
        sp_succ_up[idx_pred]->succ = idx_curr; //assegno il nodo attuale come successore a salire del nodo PREDECESSORE
        sp_succ_up[idx_pred]->dist = sp_succ_up[idx_curr]->dist + adj_curr->weight;   //e aggiorno la distanza accumulata con il peso dell'arco visitato
    }
    vrtx_visited[idx_curr] = 1; //segnalo che il vertice è stato visitato e calcolato


    if(idx_curr != idx_src) {   //se il nodo visitato non è la sorgente, continuo la visita
        if(isAscent && (vrtx[idx_curr]->height > vrtx[pred[idx_curr]]->height)) //se, continuando il percorso a ritroso, il predecessore successivo nel DFS da visitare va in discesa rispetto al nodo attuale
            isAscent = 0; //da ora in poi valgono solo percorsi in discesa
        graph_sp_calculate_visit(vrtx, pred, pred[idx_curr], sp_succ_up, sp_succ_down, idx_src, isAscent, vrtx_visited);    //visito il nodo precedente del DFS
    }
}

void graph_sp_calculate_DFS_visit(GRAPHvrtx *vrtx, int *pred, int idx_curr, SUCC *sp_succ_up, SUCC *sp_succ_down, int idx_src, int idx_dst, int isAscent, int *vrtx_visited)   {
    LIST adj_curr = vrtx[idx_curr]->adj; //prendo gli elementi della lista di adiacenza del vertice attuale    
    printf("DEBUG visit in calc: adj [%d]%d - isAscent %d", idx_curr, vrtx[idx_curr]->height, isAscent);

    while(adj_curr)    {    //ciclo fin quando non svuoto la Lista
        if(graph_sp_conditionElev(vrtx[idx_curr]->height, vrtx[adj_curr->idx_vrtx_dst]->height, isAscent, vrtx[idx_src]->height, vrtx[idx_dst]->height))    { //se l'adiacente rispetta i vincoli richiesti
            if(vrtx_visited[adj_curr->idx_vrtx_dst])    {   //se il nodo adiacente è stato visitato e calcolato
                if((graph_sp_conditionSucc_high(vrtx[idx_curr]->height, vrtx[adj_curr->idx_vrtx_dst]->height, isAscent) //se l'adiacente si trova più in alto oppure alla stessa altezza e si sta salendo
                && sp_succ_up[idx_curr]->dist + adj_curr->weight < sp_succ_up[adj_curr->idx_vrtx_dst]->dist)    {   //con la distanza calcolata fino a quel punto più il peso dell'arco minore della distanza calcolata nell'adiacente
                    /*if(sp_succ_up[adj_curr->idx_vrtx_dst]->succ == -1) //e non è stato calcolato il suo successore a salire (dunque è un nodo "bianco")
                        graph_sp_DFS_visit(grafo_lista, adj_curr->idx_vrtx_dst, idx_src, idx_dst, pred, color, isAscent);    //visito il nodo appena incontrato/*/
                    sp_succ_up[idx_curr]->succ = adj_curr->idx_vrtx_dst;
                    sp_succ_up[idx_curr]->dist = sp_succ_up[adj_curr->idx_vrtx_dst]->dist + adj_curr->weight;   //e aggiorno la distanza accumulata con il peso dell'arco visitato
                        
                        //Caso base e ritorno la distanza e i successori
                } else if((graph_sp_conditionSucc_low(vrtx[idx_curr]->height, vrtx[adj_curr->idx_vrtx_dst]->height, isAscent)   //se l'adiacente si trova più in basso oppure alla stessa altezza e si sta scendendo
                && sp_succ_down[idx_curr]->dist + adj_curr->weight < sp_succ_down[adj_curr->idx_vrtx_dst]->dist)   {  //con la distanza calcolata fino a quel punto più il peso dell'arco minore della distanza calcolata nell'adiacente
                    /*if(sp_succ_down[adj_curr->idx_vrtx_dst]->succ == -1) //e se non è stato calcolato il suo successore a scendere (dunque è un nodo bianco)
                        graph_sp_calculate_DFS_visit(vrtx, pred, adj_curr->idx_vrtx_dst, sp_succ_up, sp_succ_down, idx_src, idx_dst, 0); //0 di isAscent impostato in maniera predefinita
                    */
                        
                    sp_succ_down[idx_curr]->succ = adj_curr->idx_vrtx_dst;
                    sp_succ_down[idx_curr]->dist = sp_succ_down[adj_curr->idx_vrtx_dst]->dist + adj_curr->weight;   //e aggiorno la distanza accumulata con il peso dell'arco visitato
                    
                    
                        //Caso base e ritorno la distanza e i successori                    
                }

            }
            
            
            
            
        }
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
    }


}

int graph_sp_conditionSucc_high(int heigth_curr, int heigth_adj, int isAscent)   {
    int ret = 0;
    if(heigth_adj > heigth_curr || (heigth_adj == heigth_curr && isAscent)) //se l'adiacente si trova più in alto oppure alla stessa altezza e si sta salendo
        ret = 1;
    return ret;
}
 
int graph_sp_conditionSucc_low(int heigth_curr, int heigth_adj, int isAscent)   {
    int ret = 0;
    if(heigth_adj < heigth_curr || (heigth_adj == heigth_curr && !isAscent)) //se l'adiacente si trova più in basso oppure alla stessa altezza e si sta scendendo
        ret = 1;
    return ret;
}