#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


struct Lista    {
    int idx_vrtx_dst;
    int weight;
    struct Lista *next;
};
typedef struct Lista * LIST;    //elemento della lista


LIST list_newNode(int idx_vrtx_dst, int weight);

LIST list_insertHead(LIST lista, int key);

LIST list_delKey(LIST lista, int key);

int list_visit(LIST L_curr, LIST *L_slave);

#endif // LIST_H_INCLUDED
