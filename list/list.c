#include "list.h"

//Nuovo nodo della lista
LIST list_newNode(int vrtx_dst, int weight)    {
    LIST node = (struct Lista *)malloc(sizeof(struct Lista));
    node->vrtx_dst = salita;
    node->weight = weight;
    node->next = NULL;
    printf("DEBUG newNode: [%d]\n", node->key);
    return node;
}

//Aggiunta di un nuovo nodo alla lista in testa e puntamento all'ultimo elemento
void list_insertHead(LIST lista, int key) {
    if(lista)   {
        LIST tmp = lista->next;
        lista = list_newNode(key);
        lista->next = tmp;
    } else     //nel caso di lista vuota
        lista = list_newNode(key);
}


//Eliminazione elemento della lista
void list_delKey(LIST lista, int key) {
    LIST L_curr = lista;
    LIST L_prev = NULL;
    while(L_curr && L_curr->key != key) {   //ciclo fin quando non trovo la chiave
        L_prev = L_curr;
        L_curr = L_curr->next;
    }
    if(L_curr)  {   //se è stata trovata la chiave (ovvero, il ciclo si è fermato su un nodo)
        if(L_prev)  //se si tratta di un nodo interno (ovvero, non è la testa della lista)
            L_prev->next = L_curr->next; //assegno al next del nodo precedente, il nodo successivo presente nell'elemento da cancellare
        else //se si tratta invece della testa
            lista = L_curr->next; //cambio la testa di tutta la lista
        L_curr->next = NULL;
        free(L_curr);   //dealloco il nodo
    } else  
        printf("ATTENZIONE: elemento della lista non presente\n\n");
}

//Stampa della Lista
void list_print(LIST L_curr) {
    while(L_curr) {   //ciclo fin quando non trovo la chiave
        printf("%d -> ", L_curr->key);
        L_curr = L_curr->next;
    }
    printf("\n");
}
