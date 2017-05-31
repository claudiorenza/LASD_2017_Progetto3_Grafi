#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct CodaPrAlbero * PRQUEUEnode;


struct Lista    {
    int vrtx_dst;
    int weight;
    struct Lista *next;
};
typedef struct Lista ** LIST;   //puntatore all'elemento della lista
typedef struct Lista * LISTel;    //elemento della lista


LIST list_newNode(int vrtx_dst, int weight);

void list_insertHead(LIST lista, int key);

void list_delKey(LIST lista, int key);

int list_visit(LISTel L_curr, LIST *L_slave);

#endif // LIST_H_INCLUDED
