#include "queue.h"


//Inizializza della coda per valori interi
QUEUE queue_init(int n_vertex) {
    QUEUE coda = (int *)calloc(MAX_queue+2, sizeof(int));    //alloco due elementi in più per memorizzare l'indice della testa in coda[0] e della coda in coda[MAX_queue+1]
    coda[0] = 0;                //registro l'indice della testa in posizione 0
    coda[MAX_queue+1] = 1;      //e l'indice dell'ultimo elemento inseribile in posizione MAX_queue+1
    return coda;
}


//Controllo di coda vuota; ritorna 1 se la coda è vuota, altrimenti ritorna 0
int queue_isEmpty(QUEUE coda)  {
    return coda[0] == 0;
}


//Controllo di coda piena; ritorna 1 se la coda è piena, altrimenti ritorna 0
int queue_isFull(QUEUE coda)   {
    return coda[0] == coda[MAX_queue+1];
}


//Accoda un elemento 'key' dato in ingresso
void queue_enqueue(QUEUE coda, int key)  {
    if(!queue_isFull(coda)) {
        coda[coda[MAX_queue+1]] = key; //Inserisci valore in coda
        if(queue_isEmpty(coda))
            coda[0] = 1; //Se è vuota, sposto la testa in prima posizione
        coda[MAX_queue+1] = (coda[MAX_queue+1] % (MAX_queue)) + 1;
    } else
        printf("ATTENZIONE [QUEUE]: la coda � piena\n\n");
}


//Toglie un elemento dalla coda
int queue_dequeue(QUEUE coda)  {
    int key = 0;
    if(!queue_isEmpty(coda)) {
        key = coda[coda[0]]; // Prendo il valore in 'head' della coda
        coda[0] = (coda[0] % (MAX_queue)) + 1;
        if(queue_isFull(coda)) {    //se dopo l'estrazione, l'indice di testa e di coda coincidono, vuol dire che ho eliminato tutti gli elementi dalla coda
            coda[0] = 0;    //e resetto il tutto
            coda[MAX_queue+1] = 1;
        }
    } else
        printf("ATTENZIONE [QUEUE]: la coda è già vuota\n\n");
    return key;
}


//Liberazione efficiente della memoria allocata dinamicamente
void queue_delete(QUEUE coda)	{   //il parametro 'del_complete' == 1 libera memoria in fase di chiusura dell'applicazione
    int idx;
    for(idx=0;idx<MAX_queue+1;idx++)    {	//ciclo dal primo all'ultimo elemento della Coda
        coda[idx] = 0;   //azzero la coda
    }
    coda[0] = 0;                //registro l'indice della testa in posizione 0
    coda[MAX_queue+1] = 1;      //e l'indice dell'ultimo elemento inseribile in posizione MAX_queue+1
}

//Stampa la coda
void queue_print_recv(QUEUE coda) {
    if(!queue_isEmpty(coda)) {
        int key = queue_dequeue(coda);    //estraggo
        printf("%d ", key);               //stampo
        queue_print_recv(coda);             //passo al nodo successivo
        queue_enqueue(coda, key);         //lo rimetto in coda attualmente in ordine inverso (la chiamante dovrà effettuare la chiamata a reverse
    }
}

//Salva la coda in reverse
void queue_reverse(QUEUE coda)  {
    int key;
    if(!queue_isEmpty(coda)) {
        key = queue_dequeue(coda);
        queue_reverse(coda);
        queue_enqueue(coda, key);
    }
}


//Stampa la coda con riordino in prima posizione
void queue_print(QUEUE coda){
    queue_print_recv(coda); //Stampa la coda
    queue_reverse(coda);    //Riordina la coda prima di uscire
}