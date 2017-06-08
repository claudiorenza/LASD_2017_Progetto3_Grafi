/*Solo alla sorgente, si cerca un arco in salita; durante la visita, invece, vedo i percorsi solo in salita se la destinazione
è più in alto rispetto alla posizione attuale, altrimenti posso vedere sia in salita che in discesa.
Appena si passa ad un nodo in cui arco è in discesa, tutti i successivi nodi da visitare dovranno essere in discesa.
Usare parametro "isDiscesa", che si comporta come la mancanza di archi adiacenti per un nodo.

Nella creazione del grafo, creare un percorso idoneo allo sviluppo dell'algoritmo, creando anche percorsi alternativi più brevi
ma che non rispettano i vincoli proposti dalla traccia, sia un percorso alternativo valido ma con pesi diversi


*/


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
