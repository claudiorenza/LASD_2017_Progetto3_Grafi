#include "list.h"

//Nuovo nodo della lista
LIST list_newNode(int idx_vrtx_dst, int weight)    {
    LIST node = NULL;
    if((node = (struct Lista *)malloc(sizeof(struct Lista)))) {
        node->idx_vrtx_dst = idx_vrtx_dst;  //destinazione
        node->weight = weight;  //peso
        node->next = NULL;
    } else
        printf("[MEM] ATTENZIONE: Problema di allocazione LIST - list_newNode. Riprovare\n");
    return node;
}

//Aggiunta di un nuovo nodo alla lista in testa e puntamento all'ultimo elemento
LIST list_insertHead(LIST lista, int idx_dst, int weight) {
    if(lista)   {
        LIST lista_new = list_newNode(idx_dst, weight);
        lista_new->next = lista;
        lista = lista_new;
    } else     //nel caso di lista vuota
        lista = list_newNode(idx_dst, weight);
    return lista;
}


//Eliminazione diretta di tutta la lista
LIST list_delete(LIST L_curr) {
    if(L_curr)  {
        L_curr->next = list_delete(L_curr->next);
        free(L_curr);
    }
    return NULL;
}



//Eliminazione elemento della lista
LIST list_delKey(LIST lista, int key) {
    LIST L_curr = lista;
    LIST L_prev = NULL;
    while(L_curr && L_curr->idx_vrtx_dst != key) {   //ciclo fin quando non trovo la chiave
        L_prev = L_curr;
        L_curr = L_curr->next;
    }
    if(L_curr)  {   //se è stata trovata la chiave (ovvero, il ciclo si è fermato su un nodo)
        if(L_prev)  //se si tratta di un nodo interno (ovvero, non è la testa della lista)
            L_prev->next = L_curr->next; //assegno al next del nodo precedente, il nodo successivo presente nell'elemento da cancellare
        else //se si tratta invece della testa
            lista = L_curr->next; //cambio la testa di tutta la lista
        L_curr->next = NULL;    //CHECK: vedere se ci sono problemi
        free(L_curr);   //dealloco il nodo
    } else  
        printf("ATTENZIONE: elemento della lista non presente\n\n");
    return lista;
}


//Visita/Stampa della lista
int list_visit(LIST L_curr) {  //con L_slave ottengo l'elenco dei vertici disponibili per l'adiacenza a tempo costante
    int conta = 0;
    while(L_curr) {
        printf("-> %d ", L_curr->idx_vrtx_dst);
        conta++;
        L_curr = L_curr->next;
    }
    return conta;
}

//Ricerca elemento della lista
int list_visit_searchIdx(LIST L_curr, int idx) { 
    while(L_curr) {
        if(L_curr->idx_vrtx_dst == idx)
            return L_curr->weight;
        L_curr = L_curr->next;
    }
    return -1;
}