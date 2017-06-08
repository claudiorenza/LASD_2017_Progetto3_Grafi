#include <stdio.h>
#include <time.h>
#include "graph/graph_func.h"


int main()  {
    srand(time(NULL));		//funzione per la generazione casuale di valori
	
	grafo_list = graph_list_init();
	
    do	{
		io_clearScreen();
		printf("\t\tProgetto 3 - Gruppo 32 - MENU PRINCIPALE\n");
        int choiceMenu;

        printf("1. Genera un Grafo\n");
        printf("2. Inserisci un nuovo vertice\n");
        if(grafo_list->n_vrtx != 0) {
            printf("3. Inserisci un nuovo arco\n"); //controllo archi disponibili (controllo vertici adiacenti)
            printf("4. Visualizza il grafo\n");
            printf("5. Visita il Grafo in BFS\n");
            printf("6. Visita il Grafo in DFS\n");
            printf("7. Cancella il grafo\n");
            printf("8. Cancella un vertice\n");
            printf("9. Cancella un arco\n");
            printf("10. Calcola percorso per la corsa in salita e discesa\n");
        }
        printf("\n");
        printf("11. Esci\n");
        printf("\n\n");

        do {
            printf("SCELTA: ");
            if(((choiceMenu = io_getInteger()) < 1 || choiceMenu > 11) || (!grafo_list && (choiceMenu > 3 && choiceMenu < 11)))
                printf("ATTENZIONE: Valore non valido\n\n");
        }while((choiceMenu < 1 || choiceMenu > 11) || (!grafo_list && (choiceMenu > 3 && choiceMenu < 11)));

		io_clearScreen();
		switch(choiceMenu)	{
			case 1:
				printf("GENERAZIONE GRAFO\n\n");
                treeABR_func_average();
				break;
			case 2:
				printf("INSERIMENTO NUOVO VERTICE\n\n");
				treeABR_func_merge();
				break;
			case 3:
				printf("INSERIMENTO NUOVO ARCO\n\n");                
				treeABR_func_main();
				break;
            case 4:
				printf("STAMPA DEL GRAFO\n\n");
                treeABR_func_average();
				break;
			case 5:
				printf("VISUALIZZAZIONE IN BFS\n\n");
				treeABR_func_merge();
				break;
			case 6:
				printf("VISUALIZZAZIONE IN DFS\n\n");            
				treeABR_func_main();
				break;
            case 7:
				printf("CANCELLAZIONE DEL GRAFO\n\n");
                treeABR_func_average();
				break;
			case 8:
				printf("CANCELLAZIONE DEL VERTICE\n\n");
				treeABR_func_merge();
				break;
			case 9:
				printf("CANCELLAZIONE DELL'ARCO\n\n");                
				treeABR_func_main();
				break;
            case 10:
				printf("CALCOLO PERCORSO IN SALITA E DISCESA\n\n");                
				treeABR_func_main();
				break;
			case 11:
				printf("\n");
				printf("SESSIONE TERMINATA\n\n");
		}
	}while(choiceMenu != 11);
	
	io_clearScreen();
	return 1;
}
