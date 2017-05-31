#include "list.h"

//Nuovo nodo della lista
LISTel list_newNode(int vrtx_dst, int weight)    {
    LISTel node = NULL;
    if(node = (struct Lista *)malloc(sizeof(struct Lista))) {
        node->vrtx_dst = vrtx_dst;  //destinazione
        node->weight = weight;  //pesto
        node->next = NULL;
        printf("DEBUG newNode: dst: %d\n", node->vrtx_dst);
    } else
        printf("[MEM] ATTENZIONE: Problema di allocazione LISTel - list_newNode. Riprovare\n");
    return node;
}

//Aggiunta di un nuovo nodo alla lista in testa e puntamento all'ultimo elemento
void list_insertHead(LIST lista, int idx_dst, int weight) {
    if(*lista)   {
        LISTel tmp = (*lista)->next;
        *lista = list_newNode(idx_dst, weight);
        (*lista)->next = tmp;
    } else     //nel caso di lista vuota
        *lista = list_newNode(idx_dst, weight);
}


//Eliminazione diretta di tutta la lista
LISTel list_delete(LISTel L_curr) {
    if(L_curr)  {
        L_curr->next = list_delete(L_curr->next);
        free(L_curr);
    }
    return NULL;
}



//Eliminazione elemento della lista
void list_delKey(LIST lista, int key) {
    LISTel L_curr = *lista;
    LISTel L_prev = NULL;
    while(L_curr && L_curr->key != key) {   //ciclo fin quando non trovo la chiave
        L_prev = L_curr;
        L_curr = L_curr->next;
    }
    if(L_curr)  {   //se è stata trovata la chiave (ovvero, il ciclo si è fermato su un nodo)
        if(L_prev)  //se si tratta di un nodo interno (ovvero, non è la testa della lista)
            L_prev->next = L_curr->next; //assegno al next del nodo precedente, il nodo successivo presente nell'elemento da cancellare
        else //se si tratta invece della testa
            *lista = L_curr->next; //cambio la testa di tutta la lista
        L_curr->next = NULL;    //CHECK: vedere se ci sono problemi
        free(L_curr);   //dealloco il nodo
    } else  
        printf("ATTENZIONE: elemento della lista non presente\n\n");
}


//Visita/Stampa ed eventuale confronto con Lista di Adiacenza in mirroring
int list_visit(LISTel L_curr, LIST *L_slave) {  //con L_slave ottengo l'elenco dei vertici disponibili per l'adiacenza a tempo costante
    int conta = 0;
    while(L_curr) {
        printf("-> %d[%d]", L_curr->vrtx_dst, L_curr->weight);
        if(L_slave)
            L_slave[L_curr->vrtx_dst] = NULL; //tolgo il riferimento al vertice nell'array in modo da segnalare successivamente che esso sia già presente nella Lista di Adiacenza
        conta++;
        L_curr = L_curr->next;
    }
    return conta;
}