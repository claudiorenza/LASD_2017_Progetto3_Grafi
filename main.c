#include <stdio.h>
#include <time.h>
#include "io/io.h"
#include "graph/graph_list.h"
#include "graph/graph_func.h"


int main()  {
    srand(time(NULL));		//funzione per la generazione casuale di valori
	
	GRAPHlist grafo_lista = graph_list_init();
	
	int choiceMenu;

    do	{
		io_clearScreen();
		printf("\t\tProgetto 3 - Gruppo 32 - MENU PRINCIPALE\n");

        printf("1. Genera un Grafo\n");
        printf("2. Inserisci un nuovo vertice\n");
        if(grafo_lista->n_vrtx != 0) {
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
            if(((choiceMenu = io_getInteger()) < 1 || choiceMenu > 11) || (!grafo_lista && (choiceMenu > 3 && choiceMenu < 11)))
                printf("ATTENZIONE: Valore non valido\n\n");
        }while((choiceMenu < 1 || choiceMenu > 11) || (!grafo_lista && (choiceMenu > 3 && choiceMenu < 11)));


		if(grafo_lista->n_vrtx == 0)	{
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

		io_clearScreen();
		switch(choiceMenu)	{
			case 1:
				printf("GENERAZIONE GRAFO\n\n");
                graph_func_generate(grafo_lista);
				break;
			case 2:
				printf("INSERIMENTO NUOVO VERTICE\n\n");
				graph_func_insertKey(grafo_lista);
				break;
			case 3:
				printf("INSERIMENTO NUOVO ARCO\n\n");                
				graph_func_insertEdge(grafo_lista);
				break;
            case 4:
				printf("STAMPA DEL GRAFO\n\n");
                graph_func_print(grafo_lista);
				break;
			case 5:
				printf("VISUALIZZAZIONE IN BFS\n\n");
				graph_func_BFS(grafo_lista);
				break;
			case 6:
				printf("VISUALIZZAZIONE IN DFS\n\n");            
				graph_func_DFS(grafo_lista);
				break;
            case 7:
				printf("CANCELLAZIONE DEL GRAFO\n\n");
                graph_func_delete(grafo_lista);
				break;
			case 8:
				printf("CANCELLAZIONE DEL VERTICE\n\n");
				graph_func_delVertex(grafo_lista);
				break;
			case 9:
				printf("CANCELLAZIONE DELL'ARCO\n\n");                
				graph_func_delEdge(grafo_lista);
				break;
            case 10:
				printf("CALCOLO PERCORSO IN SALITA E DISCESA\n\n");                
				//graph_func_sp();
				break;
			case 11:
				printf("\n");
				printf("SESSIONE TERMINATA\n\n");
		}
	}while(choiceMenu != 11);
	
	io_clearScreen();
	return 1;
}
