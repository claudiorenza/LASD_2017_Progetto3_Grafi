#include "graph_list.h"

//Inizializzazione del Grafo, con elementi da riempire con vertici
GRAPHlist graph_list_init()   {
    GRAPHlist grafo_lista = NULL;
    if((grafo_lista = (struct GrafoLista *)malloc(sizeof(struct GrafoLista)))    //allocazione della struct per il grafo
    && (grafo_lista->vrtx = (struct GrafoVertice **)calloc(MAX_graph, sizeof(struct GrafoVertice *)))    //array dei puntatori ai vertici del Grafo (inizializzati a NULL)
    && (grafo_lista->heights = (struct Lista **)calloc(MAX_graph, sizeof(struct Lista *))))  { //array delle altezze registrate (inizializzati a NULL)
        grafo_lista->n_vrtx = 0;
        grafo_lista->idx_max = 0;   //in questo campo verrà registrato e aggiornato l'ultimo indice utilizzato dai vertici del grafo
    } else {
        printf("[MEM] ATTENZIONE: Problema di allocazione ");
        if(!grafo_lista)
            printf("GRAPHlist ");
        else if(!(grafo_lista->vrtx))
            printf("GRAPHvrtx * ");
        else if(!(grafo_lista->heights))
            printf("LIST * ");
        printf("- graph_list_init\n");
        exit(1);
    }
    return grafo_lista;
}
    
    
//Selettore di inserimento di duplicati
void graph_list_dupEnabler(GRAPHlist grafo_lista)   {
    char confirm;
    do	{
        printf("Il nuovo Grafo può contenere duplicati? (S/N): ");
        confirm = io_getChar();
        if(confirm == 's' || confirm == 'S')	
            grafo_lista->dup = 1;			//imposto il flag per il possibile inserimento di altezze duplicate
        else if(confirm == 'n' || confirm == 'N')
            grafo_lista->dup = 0;
        else if(confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N')
            printf("ATTENZIONE: Comando non valido\n\n");
    }while(confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N');
}


//Estrazione dei caratteri da file per la realizzazione del grafo
void graph_list_parse(GRAPHlist grafo_lista, FILE *file)    {
    int idx, idx_src, n_elem,cursor = 0;
    
    printf("Numero elementi: %d\n", (n_elem = io_fgetInteger(file)));
    printf("Duplicati: ");
    if(grafo_lista->dup == io_fgetInteger(file))
        printf("Ammessi\n");
    else
        printf("NON ammessi\n");
    io_pressKey();

    while(((cursor = fgetc(file)) == '\n')) //vado avanti finché non trovo un nuovo carattere
		;
    ungetc(cursor,file);

    for(idx=0;idx<n_elem;idx++)    {
        graph_list_insVertex(grafo_lista, io_fgetInteger(file), io_fgetInteger(file), -1);	
        //N.B. in caso di duplicati accettati, weight == -1 indica la lettura da file, quindi gli archi adiacenti vengono caricati dopo;
        
        //printf("DEBUG: inserimento - %d/%d\n", idx, n_elem);
        //io_pressKey();
        
    }
    while(((cursor = fgetc(file)) == '\n')) //vado avanti finché non trovo un nuovo carattere
        ;
    ungetc(cursor,file);
    while(cursor != EOF)  {
        idx_src = io_fgetInteger(file);
        //printf("DEBUG: vertice partenza - %d\n", idx_src);                
        while(((cursor = fgetc(file)) != EOF) && cursor != '\n') {   
            //printf("DEBUG: cursor esterno %c\n", cursor);            
            ungetc(cursor,file);    //rimetto l'ultimo carattere nel file*/       
            //printf("DEBUG: nuovo adiacente\n");
            grafo_lista->vrtx[idx_src]->adj = list_insertHead(grafo_lista->vrtx[idx_src]->adj, io_fgetInteger(file), io_fgetInteger(file)); //inserimento in testo nella Lista di Adiacenza di idx_src
            //io_pressKey();  
        }

    }
}


//Inserimento/Allocazione di un nuovo vertice nel Grafo e nella Lista di Adiacenza
void graph_list_insVertex(GRAPHlist grafo_lista, int idx, int height, int weight) {     //se il peso è = 0, trattasi di inserimento manuale e non generazione randomica
    if(idx == -1)    {   //se non è stato indicato manualmente l'indice del vertice
        do  {
            idx++;
        }while(idx<=grafo_lista->idx_max && grafo_lista->vrtx[idx]);  //cerco il primo vertice disponibile 
    }
    if(idx > grafo_lista->idx_max) {   //se ho superato il margine massimo, aggiorno il suo contatore
        grafo_lista->idx_max = idx;      
    }
    if((grafo_lista->vrtx[idx] = (struct GrafoVertice *)malloc(sizeof(struct GrafoVertice))))  {  //assegno un puntatore al vertice
        grafo_lista->vrtx[idx]->adj = NULL;             //Lista di Adiacenza da riempire;
        
        if(height == -1)  { //se non è stato indicato manualmente l'altezza
            if(!(grafo_lista->dup))    {   //se non è possibile inserire nodi nella stessa altezza
                while(grafo_lista->heights[height = random_num(0,MAX_graph-1)])  //cerco un'altezza casuale disponibile
                    ;
            } else  {   //se posso inserire duplicati, va bene qualsiasi valore
                height = random_num(0, MAX_graph-1);  //verrà scelta un altezza randomicamente;
            }
        }
        if(grafo_lista->dup && grafo_lista->heights[height] && weight != -1)  {    //se è possibile inserire duplicati ed esiste già un nodo che ha la stessa altezza...; weight == -1 indica la lettura del grafo da file
            if(weight == 0) //se non ho impostato un peso per l'inserimento di un singolo vertice con altezza già presente
                weight = random_num(1, MAX_weight);  //applicherò un peso casuale all'arco adiacente della stessa altezza
            graph_list_insArc(grafo_lista, idx, grafo_lista->heights[height]->idx_vrtx_dst, weight);   //...applico subito questo nuovo nodo all'adiacente del vertice posto alla stessa altezza
        }
        grafo_lista->heights[height] = list_insertHead(grafo_lista->heights[height], idx, -1);  //inserisco un elemento nella lista delle altezze con l'identificativo del nodo associato             
        grafo_lista->vrtx[idx]->height = height;        //assegno l'altezza al vertice creato        
        
        grafo_lista->n_vrtx += 1;                              //aggiorno la grandezza del grafo
        printf("Vertice %d correttamente inserito nel Grafo in altezza %d\n", idx, grafo_lista->vrtx[idx]->height);        
    } else  {
        printf("[MEM] ATTENZIONE: Problema di allocazione GRAPHvrtx - graph_list_insVertex\n");
        exit(1);
    }
}


//Inserimento di un nuovo arco per un grafo non orientato con controllo dei vertici disponibili
void graph_list_insArc(GRAPHlist grafo_lista, int idx_src, int idx_dst, int weight) {
    grafo_lista->vrtx[idx_src]->adj = list_insertHead(grafo_lista->vrtx[idx_src]->adj, idx_dst, weight); //inserimento in testo nella Lista di Adiacenza di idx_src
    grafo_lista->vrtx[idx_dst]->adj = list_insertHead(grafo_lista->vrtx[idx_dst]->adj, idx_src, weight); //inserimento in testo nella Lista di Adiacenza di idx_dst (grafo non orientato)    
}

//Eliminazione del Grafo con annesse Liste di Adiacenza e con le Liste delle Altezze precedentemente registrate
void graph_list_deleteGraph(GRAPHlist grafo_lista) {
    int idx;
    for(idx=0;idx<=grafo_lista->idx_max;idx++){
        if(grafo_lista->vrtx[idx])  {
            if(grafo_lista->vrtx[idx]->adj)  
                grafo_lista->vrtx[idx]->adj = list_delete(grafo_lista->vrtx[idx]->adj); //elimino tutta la Lista puntata ricorsivamente
            grafo_lista->heights[grafo_lista->vrtx[idx]->height] = list_delKey(grafo_lista->heights[grafo_lista->vrtx[idx]->height], idx); //elimino la corrispondente altezza nell'array delle altezze
        }
	    free(grafo_lista->vrtx[idx]);   //dealloco il puntatore del vertice
        grafo_lista->vrtx[idx] = NULL;
    }
	grafo_lista->n_vrtx = 0;
    grafo_lista->idx_max = 0;
}

//Eliminazione del vertice con i relativi archi entranti e uscenti (grafo non orientato)
void graph_list_delVertex(GRAPHlist grafo_lista, int idx_del)  {
    grafo_lista->vrtx[idx_del]->adj = graph_list_delVertex_undirectedArcs(grafo_lista, grafo_lista->vrtx[idx_del]->adj, idx_del);  //eliminazione degli archi entranti al vertice e la sua Lista di Adiacenza
    grafo_lista->heights[grafo_lista->vrtx[idx_del]->height] = list_delKey(grafo_lista->heights[grafo_lista->vrtx[idx_del]->height], idx_del); //elimino la corrispondente altezza nell'array delle altezze
    free(grafo_lista->vrtx[idx_del]);    //dealloco il vertice
    grafo_lista->vrtx[idx_del] = NULL;   //rendo disponibile lo spazio nel caso di inserimento di un nuovo vertice

    if(idx_del == grafo_lista->idx_max) {//se il vertice da eliminare è proprio l'ultimo, aggiorno anche il valore del margine massimo dell'array
        do{ //cerco il minimo vertice disponibile
            grafo_lista->idx_max -= 1;   //decremento fin quando non trovo un vertice presente
        }while(grafo_lista->idx_max > 0 && !(grafo_lista->vrtx[grafo_lista->idx_max]));
    }
    grafo_lista->n_vrtx -= 1;
}

//Eliminazione diretta di tutta la Lista di Adiacenza con gli archi entranti associati
LIST graph_list_delVertex_undirectedArcs(GRAPHlist grafo_lista, LIST L_curr, int idx_del) {
    if(L_curr)  {
        L_curr->next = graph_list_delVertex_undirectedArcs(grafo_lista, L_curr->next, idx_del);
        grafo_lista->vrtx[L_curr->idx_vrtx_dst]->adj = list_delKey(grafo_lista->vrtx[L_curr->idx_vrtx_dst]->adj, idx_del);    //eliminazione dell'arco entrante
        free(L_curr);   //deallocazione dell'arco uscente
    }
    return NULL;
}

//Eliminazione manuale dell'arco con controllo dei vertici adiacenti
void graph_list_delArc(GRAPHlist grafo_lista, int idx_src) {
    if(grafo_lista->vrtx[idx_src]->adj)    {
        int idx_del;
        GRAPHvrtx *vrtx_slave = graph_list_vrtx_mirror(grafo_lista);

        printf("%d: ", idx_src);
        graph_list_adjVisit(grafo_lista->vrtx[idx_src]->adj, grafo_lista->vrtx, vrtx_slave);    //stampo e conto i vertici adiacenti, controllando la disponibilità di vertici collegabili
        printf("\n\n");
        do  {
            printf("Quale indice dell'arco uscente vuoi eliminare dal vertice %d? ", idx_src);   
            if(!(grafo_lista->vrtx[(idx_del = io_getInteger())]))
                printf("ATTENZIONE: vertice di destinazione NON presente\n\n");                
            else if(vrtx_slave[idx_del])    //in tal caso vrtx_slave ha tutti gli archi uscenti mancanti
                printf("ATTENZIONE: arco NON presente nella Lista di Adiacenza\n\n");
        }while(!(grafo_lista->vrtx[idx_del]) || vrtx_slave[idx_del]);
        graph_list_vrtx_mirrorFree(vrtx_slave, grafo_lista->idx_max);        
        grafo_lista->vrtx[idx_src]->adj = list_delKey(grafo_lista->vrtx[idx_src]->adj, idx_del);    //eliminazione dell'arco uscente
        grafo_lista->vrtx[idx_del]->adj = list_delKey(grafo_lista->vrtx[idx_del]->adj, idx_src);    //eliminazione dell'arco entrante
    } else
        printf("ATTENZIONE: il vertice scelto non ha archi uscenti\n\n");
}

//Visualizzazione del percorso fra due vertici in BFS o DFS
void graph_list_path(GRAPHlist grafo_lista, int idx_src, int idx_dst, int mode)  {   //mode == 0 -> BFS; mode == 1 -> DFS
    if(idx_src != idx_dst)  {
        int *pred = NULL;
        if(!mode)   //BFS
            pred = graph_list_BFS(grafo_lista, idx_src);
        else        //DFS
            pred = graph_list_DFS(grafo_lista, idx_src);
        graph_list_path_print(grafo_lista, idx_src, idx_dst, pred);
    } else
        printf("ATTENZIONE: Sorgente e destinazione coincidono\n\n");
}

//Stampa del percorso minimo fra due vertici definito dall'array dei predecessori
void graph_list_path_print(GRAPHlist grafo_lista, int idx_src, int idx_dst, int *pred)  {
    if(idx_src == idx_dst)
        printf("%d ", idx_src);
    else if(pred[idx_dst] == -1)   
        printf("ATTENZIONE: non esiste alcun cammino tra la sorgente e la destinazione scelta\n\n");
    else    {
        graph_list_path_print(grafo_lista, idx_src, pred[idx_dst], pred);
        printf("-> %d ", idx_dst);
    }
}


//Visita in ampiezza con creazione e ritorno dell'array degli indici dei predecessori
int *graph_list_BFS(GRAPHlist grafo_lista, int idx_src)  {
    int idx;
    int *pred = (int *)calloc((grafo_lista->idx_max)+1, sizeof(int));    //creo l'array degli indici dei predecessori

    char *color = (char *)malloc(sizeof(char) * (grafo_lista->idx_max)+1);   //creo l'array dei colori associati ai vertici, quantificati in grafo_lista[0]

    QUEUE coda = queue_init(grafo_lista->idx_max);  //creo una coda che ha una grandezza massima del numero dei vertici del Grafo
    LIST adj_curr = NULL; //prendo gli elementi della lista di adiacenza del vertice estratto dalla coda

    for(idx=0;idx<=grafo_lista->idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_lista->vrtx[idx] && idx != idx_src) {
            color[idx] = 'w';
            pred[idx] = -1;
        }
    }

    color[idx_src] = 'g'; //GRIGIO sul vertice sorgente
    pred[idx_src] = -1;  //che non ha predecessori

    queue_enqueue(coda, idx_src);   //inserisco in coda la sorgente
    while(!queue_isEmpty(coda))    {    //ciclo fin quando non svuoto la Lista
        idx = queue_dequeue(coda);    //estraggo la testa della Coda
        adj_curr = grafo_lista->vrtx[idx]->adj;  //prendo la Lista di Adiacenza dell'elemento appena estratto
        while(adj_curr) {
            if(color[adj_curr->idx_vrtx_dst] == 'w')  { //se BIANCO (white)
                color[adj_curr->idx_vrtx_dst] = 'g';   //coloro di GRIGIO (grey)
                pred[adj_curr->idx_vrtx_dst] = idx;      //assegno il suo predecessore
                queue_enqueue(coda, adj_curr->idx_vrtx_dst);   //inserisco l'indice nella coda per le future iterazioni
            }
            adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
        }
        color[idx] = 'b';  //completo la visita del nodo in NERO (black)
    }
    free(color);
    free(coda);
    return pred;
}


//Visita in profondità
int *graph_list_DFS(GRAPHlist grafo_lista, int idx_src)  {
    int idx;
    int *pred = (int *)malloc(sizeof(int) * (grafo_lista->idx_max)+1);    //l'array degli indici dei predecessori

    char *color = (char *)malloc(sizeof(char) * (grafo_lista->idx_max)+1);   //creo l'array dei colori associati ai vertici, quantificati in grafo_lista[0]

    for(idx=0;idx<=grafo_lista->idx_max;idx++)    {       //inizializzazione grafo
        if(grafo_lista->vrtx[idx])
            color[idx] = 'w';
            pred[idx] = -1;
    }

    graph_list_DFS_visit(grafo_lista->vrtx, idx_src, pred, color); //visito l'elemento della lista di adiacenza dalla sorgente

    for(idx=0;idx<=grafo_lista->idx_max;idx++) {    //vedo i restanti alberi di copertura
        if(grafo_lista->vrtx[idx] && color[idx] == 'w')   //se esiste il vertice ed è BIANCO
            graph_list_DFS_visit(grafo_lista->vrtx, idx, pred, color); //visito l'elemento della lista di adiacenza
    }
    free(color);
    return pred;
}

//Durante la visita in profondità, posso notificare la presenza di un ciclo all'interno del grafo
void graph_list_DFS_visit(GRAPHvrtx *vrtx, int idx_curr, int *pred, char *color)    {
    LIST adj_curr = vrtx[idx_curr]->adj; //prendo gli elementi della lista di adiacenza del vertice attuale
    color[idx_curr] = 'g'; //GRIGIO sul vertice attuale
    while(adj_curr)    {    //ciclo fin quando non svuoto la Lista
        if(color[adj_curr->idx_vrtx_dst] == 'w')  { //se BIANCO
            pred[adj_curr->idx_vrtx_dst] = idx_curr;       //applico l'attuale vertice come predecessore di questo nodo adiacente
            graph_list_DFS_visit(vrtx, adj_curr->idx_vrtx_dst, pred, color);    //visito il nodo appena incontrato
        }
        adj_curr = adj_curr->next;  //passo al prossimo vertice adiacente
    }
    color[idx_curr] = 'b';  //completo la visita del nodo in NERO
}

//Stampa del Grafo con la Lista di Adiacenza dei rispettivi vertici
void graph_list_print(GRAPHlist grafo_lista)   {
    int idx;
    for(idx=0;idx<=grafo_lista->idx_max;idx++) {
        if(grafo_lista->vrtx[idx])   { //se esiste il vertice nell'array
            printf("[%d]%d: ", idx, grafo_lista->vrtx[idx]->height);    //stampo l'indice del vertice e l'altezza associata
            graph_list_adjVisit(grafo_lista->vrtx[idx]->adj, grafo_lista->vrtx, NULL); //passo la lista di adiacenza del vertice attuale
            printf("\n");
        } 
    }
}


//Visita/Stampa ed eventuale confronto con Lista di Adiacenza in mirroring
int graph_list_adjVisit(LIST L_curr, GRAPHvrtx *vrtx, GRAPHvrtx *vrtx_slave) {  //con L_slave ottengo l'elenco dei vertici disponibili per l'adiacenza a tempo costante
    int conta = 0;
    while(L_curr) {
        if(vrtx)    //se ho passato l'array dei vertici, stampo gli elementi della lista
            printf("-> [%d]%d (%d) ", L_curr->idx_vrtx_dst, vrtx[L_curr->idx_vrtx_dst]->height, L_curr->weight);
        if(vrtx_slave)
            vrtx_slave[L_curr->idx_vrtx_dst] = NULL; //tolgo il riferimento al vertice nell'array in modo da segnalare successivamente che esso sia già presente nella Lista di Adiacenza
        conta++;
        L_curr = L_curr->next;
    }
    return conta;
}

//Copia i riferimenti dei nodi del Grafo, utile per reperire la disponibilità e i dati dei nuovi vertici adiacenti a tempo costante
GRAPHvrtx *graph_list_vrtx_mirror(GRAPHlist grafo_lista)    {
    int idx;
    GRAPHvrtx *vrtx_slave = NULL;
    if((vrtx_slave = (GRAPHvrtx *)calloc((grafo_lista->idx_max)+1, sizeof(GRAPHvrtx)))) {     //array slave delle Liste di Adiacenza da riferire
        for(idx=0;idx<=grafo_lista->idx_max;idx++)
            vrtx_slave[idx] = grafo_lista->vrtx[idx];    //copio i riferimenti delle Liste di Adiacenza di tutti i nodi (disponibili e non);
    }

    return vrtx_slave;
}

//Stampa del Grafo con la Lista di Adiacenza dei rispettivi vertici
void graph_list_vrtx_mirrorPrint(GRAPHvrtx *vrtx_slave, int idx_max)   {
    int idx;
    for(idx=0;idx<=idx_max;idx++) {
        if(vrtx_slave[idx])    //se esiste il vertice nell'array dei vertici disponibili
            printf("[%d]%d\n", idx, vrtx_slave[idx]->height);
    }
    printf("\n");
}

//Liberazione dell'array dei riferimenti
void graph_list_vrtx_mirrorFree(GRAPHvrtx *vrtx_slave, int idx_max)    {
    int idx;
    for(idx=0;idx<idx_max;idx++)    {   //assicuro che non ho i riferimenti ai nodi del vertice, evitando di liberare la loro memoria quando eseguo 'free'
        vrtx_slave[idx] = NULL;
    }
    free(vrtx_slave);
}
