#include "graph_sp.h"

//Visita in profondità dal solo albero di copertura partente dalla sorgente con applicazione dei vincoli
int *graph_sp_DFS(GRAPHlist grafo_lista, int idx_src, int idx_dst)  {
    int idx;
    int *pred = (int *)malloc(sizeof(int) * (grafo_lista->idx_max)+1);    //per futura utilità, dispongo anche l'array degli indici dei predecessori
    int *dist_dest = (int *)malloc(sizeof(int));    //distanza calcolata a partire dalla sorgente

    char *color = (char *)malloc(sizeof(char) * (grafo_lista->idx_max)+1);   //creo l'array dei colori associati ai vertici, quantificati in grafo_lista[0]

    for(idx=0;idx<=grafo_lista->idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_lista->vrtx[idx]->adj)
            color[idx] = 'w';
            pred[idx] = -1;
    }
    //N.B.: per poter riconoscere la presenza di (almeno) un percorso che raggiunga la destinazione, non visiterò altre radici bianchi al di fuori della sorgente
    *dist_dest = INT_MAX;
    printf("\t[DEBUG DFS] Partenza da sorgente [%d]\n", idx_src);    
    graph_sp_DFS_visit(grafo_lista->vrtx, idx_src, idx_src, idx_dst, pred, 0, dist_dest, color, 1); //parto solo dalla radice
    
    if(*dist_dest != INT_MAX)
        printf("Percorso TROVATO - Distanza complessiva: %d\n\n", *dist_dest);
    else
        printf("ATTENZIONE: non è stato trovato alcun percorso\n\n");
    free(color);
    return pred;
}

//Durante la visita in profondità ricorsiva
int graph_sp_DFS_visit(GRAPHvrtx *vrtx, int idx_curr, int idx_src, int idx_dst, int *pred, int dist_curr, int *dist_dest, char *color, int isAscent)    {
    printf("\t[DEBUG DFS] idx_curr[%d]%d - idx_src[%d]%d - idx_dst[%d]%d - dist_curr=%d - dist_dest=%d - isAscent=%d\n",
    idx_curr, vrtx[idx_curr]->height, idx_src, vrtx[idx_src]->height, idx_dst, vrtx[idx_dst]->height, dist_curr, *dist_dest, isAscent);    
    
    LIST adj_curr = vrtx[idx_curr]->adj; //prendo gli elementi della lista di adiacenza del vertice attuale
    color[idx_curr] = 'g'; //GRIGIO sul vertice attuale
    int ret = 0;
    
    printf("\t[DEBUG DFS] idx_curr[%d]%d Lettura Lista Adiacenza\n", idx_curr, vrtx[idx_curr]->height);            
    while(adj_curr)    {    //ciclo fin quando non svuoto la Lista
        printf("\t[DEBUG DFS] idx_curr[%d]%d - adj_idx[%d]%d \n", idx_curr, vrtx[idx_curr]->height, adj_curr->idx_vrtx_dst, vrtx[adj_curr->idx_vrtx_dst]->height);                    
        if(graph_sp_conditionElev(vrtx[idx_curr]->height, vrtx[adj_curr->idx_vrtx_dst]->height, isAscent, vrtx[idx_src]->height, vrtx[idx_dst]->height)) {  //se l'adiacente rispetta i vincoli richiesti
            if(color[adj_curr->idx_vrtx_dst] == 'w')  { //se BIANCO
                if(isAscent && (vrtx[idx_curr]->height > vrtx[adj_curr->idx_vrtx_dst]->height)) { //se il successore nella visita va in discesa
                    isAscent = 0;               //da ora in poi valgono solo percorsi in discesa
                    printf("\t[DEBUG DFS] Comincia la discesa\n");            
                }
                if(adj_curr->idx_vrtx_dst == idx_dst)   {              //se ho raggiunto la destinazione dal nodo attuale
                    printf("\t[DEBUG DFS] Destinazione RAGGIUNTA - dist_dest_new=%d - dist_dest=%d\n", dist_curr + adj_curr->weight, *dist_dest);            
                    
                    if(dist_curr + adj_curr->weight < *dist_dest)  {   //e la distanza accumulata fino alla destinazione è minore della distanza calcolata precedentemente 
                        *dist_dest = dist_curr + adj_curr->weight;     //aggiorno il valore della distanza accumulata fino alla destinazione
                        pred[adj_curr->idx_vrtx_dst] = idx_curr;       //applico l'attuale vertice come predecessore della destinazione
                        printf("\t[DEBUG DFS] Aggiornata distanza e predecessore\n");                                    
                        color[idx_curr] = 'w';                         //rimetto in BIANCO il nodo attuale in caso di presenza di altri percorsi calcolabili
                        return 1;                                      //non continuo la visita del prossimo adiacente e torno indietro
                    }
                } else if((ret = graph_sp_DFS_visit(vrtx, adj_curr->idx_vrtx_dst, idx_src, idx_dst, pred, dist_curr + adj_curr->weight, dist_dest, color, isAscent))) {   //visito il nodo appena incontrato
                    //se ret == '1', vuol dire che è stata trovata la destinazione, quindi assegno il predecessore
                    pred[adj_curr->idx_vrtx_dst] = idx_curr;       //applico l'attuale vertice come predecessore di questo nodo adiacente   
                    printf("\t[DEBUG DFS] Aggiornato predecessore da return\n");            
                    
                }                
            }
        }
        printf("\t[DEBUG DFS] Passaggio adiacente successivo\n\n");            
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente        
    }
    color[idx_curr] = 'w';  //rimetto in BIANCO il nodo per gli altri percorsi da visitare
    return ret;
}



//Semplificazione delle condizioni per l'inserimento in coda di elementi adiacenti
//N.B.: per una migliore comprensione, invece di inserire tutte le condizioni in un unico 'if', possiamo analizzare separatamente i casi validi per l'inserimento in coda
int graph_sp_conditionElev(int height_curr, int height_adj, int isAscent, int height_src, int height_dst)  {
    int ret = 0;    //inizializzazione a 0 (nel caso nessuna condizione sia verificata, la funzione ritornerà 0)
    printf("\t\t[DEBUG COND] h_curr=%d - h_adj=%d - isAscent=%d - h_src=%d - h_dst=%d\n", height_curr, height_adj, isAscent, height_src, height_dst);    
    if(height_src == height_curr || height_curr <= height_dst) {   //Se parto dalla sorgente, oppure la destinazione è situata più in alto,
        printf("\t\t[DEBUG COND] Sorgente o altezza inferiore alla destinazione\n");            
        if(height_curr <= height_adj /*&& isAscent */)   {        //devo necessariamente salire o passare all'adiacente posto alla stessa altitudine.
            printf("\t\t[DEBUG COND] In salita\n");            
            if(height_adj != height_dst)     //Se salendo non trovo già la destinazione,
                ret = 1;
            else
                printf("\t\t[DEBUG COND] Durante la salita ho trovato la destinazione\n");                            
        }
    } else if(height_curr > height_dst)    {    //Se, invece, mi trovo più in alto rispetto alla destinazione,
        printf("\t\t[DEBUG COND] Altezza superiore alla destinazione\n");                    
        if(isAscent)    {                       //Se sto salendo (il predecessore è più in basso, oppure salivo dopo aver passato un'intersezione posta allo stesso livello)  
            printf("\t\t[DEBUG COND] In salita\n");                        
            ret = 1;                            //posso sia salire che scendere, o percorrere l'adiacente posto alla stessa altitudine
        } else {                                //Se sto scendendo (il predecessore è più in alto, oppure scendevo dopo aver passato un'intersezione posta allo stesso livello),
            printf("\t\t[DEBUG COND] In DISCESA\n");                                    
            if(height_curr >= height_adj && height_adj >= height_dst) //devo necessariamente scendere, o percorrere l'adiacente posto alla stessa altitudine, non andando oltre al di sotto del nodo di destinazione
                ret = 1;                            //inserendo solo i nodi adiacenti in discesa.
        }                    
    }
    if(ret)
        printf("\t\t[DEBUG COND] Confermato\n");                        
    else
        printf("\t\t[DEBUG COND] NON confermato\n");                        
        
    return ret;
}

//Stampa del percorso minimo fra due vertici definito dall'array dei predecessori
void graph_sp_path_print(GRAPHvrtx *vrtx, int idx_src, int idx_dst, int *pred)  {
    if(idx_src == idx_dst)  {
        printf("%d ", idx_src);
    } else    {
        graph_sp_path_print(vrtx, idx_src, pred[idx_dst], pred);
        printf("-> %d ", idx_dst);
    }
}

