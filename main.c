#include <stdio.h>
#include <stdlib.h>

struct elem {
    int key;
};


int main()  {
    struct elem ***ok = NULL;
    ok = (struct elem ***)calloc(2, sizeof(struct elem **));
    ok[0] = (struct elem **)calloc(1, sizeof(struct elem *));
    if(ok[0] != NULL)   {
        printf("OK\n\n");
        *ok[0] = (struct elem *)malloc(sizeof(struct elem));
        (*ok[0])->key = 2;
        if(*ok[0] != NULL)
            printf(" %d\n\n", (*ok[0])->key);
        else
            printf("NO INSIDE\n\n");
    }
    else
        printf("NO\n\n");
    return 1;
}