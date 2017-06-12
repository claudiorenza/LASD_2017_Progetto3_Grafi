#include "graph_sp.h"

//Visita in profondità dal solo albero di copertura partente dalla sorgente con applicazione dei vincoli
int *graph_sp_DFS(GRAPHlist grafo_lista, int idx_src, int idx_dst)  {
    int idx;
    int *pred = (int *)malloc(sizeof(int) * (grafo_lista->idx_max)+1);    //per futura utilità, dispongo anche l'array degli indici dei predecessori
    int *dist = (int *)malloc(sizeof(int) * (grafo_lista->idx_max)+1);    //distanza calcolata a partire dalla sorgente

    char *color = (char *)malloc(sizeof(char) * (grafo_lista->idx_max)+1);   //creo l'array dei colori associati ai vertici, quantificati in grafo_lista[0]

    for(idx=0;idx<=grafo_lista->idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_lista->vrtx[idx]->adj)
            color[idx] = 'w';
            pred[idx] = -1;
            dist[idx] = INT_MAX;
    }
    //N.B.: per poter riconoscere la presenza di (almeno) un percorso che raggiunga la destinazione, non visiterò altre radici bianchi al di fuori della sorgente
    dist[idx_src] = 0;
    graph_sp_DFS_visit(grafo_lista->vrtx, idx_src, idx_src, idx_dst, pred, dist, color, 1); //parto solo dalla radice

    free(color);
    return pred;
}

//Durante la visita in profondità ricorsiva
void graph_sp_DFS_visit(GRAPHvrtx *vrtx, int idx_curr, int idx_src, int idx_dst, int *pred, int *dist, char *color, int isAscent)    {
    LIST adj_curr = vrtx[idx_curr]->adj; //prendo gli elementi della lista di adiacenza del vertice attuale
    color[idx_curr] = 'g'; //GRIGIO sul vertice attuale

    while(adj_curr)    {    //ciclo fin quando non svuoto la Lista
        if(graph_sp_conditionElev(vrtx[idx_curr]->height, vrtx[adj_curr->idx_vrtx_dst]->height, isAscent, vrtx[idx_src]->height, vrtx[idx_dst]->height)) {  //se l'adiacente rispetta i vincoli richiesti
            if(color[adj_curr->idx_vrtx_dst] == 'w')  { //se BIANCO
                pred[adj_curr->idx_vrtx_dst] = idx_curr;       //applico l'attuale vertice come predecessore di questo nodo adiacente
                dist[adj_curr->idx_vrtx_dst] = dist[idx_curr] + adj_curr->weight; //sommo la distanza calcolata dal nodo corrente al successivo
                
                if(isAscent && (vrtx[idx_curr]->height > vrtx[adj_curr->idx_vrtx_dst]->height)) //se il successore nella visita va in discesa
                    isAscent = 0; //da ora in poi valgono solo percorsi in discesa
                graph_sp_DFS_visit(vrtx, adj_curr->idx_vrtx_dst, idx_src, idx_dst, pred, dist, color, isAscent);    //visito il nodo appena incontrato
            } else if(color[adj_curr->idx_vrtx_dst] == 'b')    {    //se è NERO, quindi un nodo già visitato
                if(dist[idx_curr] + adj_curr->weight < dist[adj_curr->idx_vrtx_dst])   {  //confronto la distanza calcolata fino a quel punto più il peso dell'arco dell'adiacente già visitato
                    pred[adj_curr->idx_vrtx_dst] = idx_curr;       //applico l'attuale vertice come predecessore di questo nodo adiacente
                    //N.B.: la distanza reale del percorso verrà calcolata una volta completato il dfs, ovvero durante la stampa
                }
            }
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
        }
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
            if(height_curr >= height_adj && (height_adj >= height_dst)) //devo necessariamente scendere, o percorrere l'adiacente posto alla stessa altitudine, non andando oltre al di sotto del nodo di destinazione
                ret = 1;                            //inserendo solo i nodi adiacenti in discesa.
        }                    
    }
    return ret;
}

//Stampa e calcolo del percorso minimo fra due vertici definito dall'array dei predecessori
int graph_sp_path_print(GRAPHvrtx *vrtx, int idx_src, int idx_dst, int *pred)  {
    int sum = 0;
    if(idx_src == idx_dst)  {
        printf("%d ", idx_src);
        sum = 0;
    } else if(pred[idx_dst] == -1)
        printf("ATTENZIONE: non esiste alcun cammino tra la sorgente e la destinazione scelta\n\n");
    else    {
        sum = graph_sp_path_print(vrtx, idx_src, pred[idx_dst], pred);
        sum += list_visit_searchIdx(vrtx[pred[idx_dst]]->adj, idx_dst);
        printf("-> %d ", idx_dst);
    }
    return sum;
}

