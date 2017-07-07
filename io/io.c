#include "io.h"

//Input di stringa robusto, con troncamento nel caso si inseriscano più caratteri del dovuto
void io_getString(char *string, int length) {
	int idx;
	char c;
	for(idx=0;(idx<length && (c = getchar())!='\n' && c!=EOF);idx++)
		string[idx] = c;
	string[idx] = '\0';
}

//Input di interi robusto fino a 9 cifre
int io_getInteger() {
	char string[9];
	io_getString(string, 9);
	return atoi(string);	//conversione in valore intero
}

//Input di char
char io_getChar() {
	char string[2];
	io_getString(string, 2);
	return string[0];
}

//Input da file di interi
int io_fgetInteger(FILE *file)    {
	int cursor=0,num=0, lecture=0;

	while((cursor=fgetc(file)) != EOF && isdigit(cursor)) {
		printf("DEBUG: %c\n", cursor);		
		if(num <= ((INT_MAX - (cursor-'0'))/10)) {
			num = num*10 + (cursor-'0'); 
			lecture++;
		}
	    else
			printf("ATTENZIONE: il numero letto deve essere inferiore a 2147483648");
	}
	
	if(!lecture)
		printf("ATTENZIONE: numero non presente nel file\n");
	while(((cursor = fgetc(file)) == '\t') /*|| (cursor == '\n')*/ || (cursor == ' ')) //vado avanti finché non trovo un nuovo carattere
		;

	if(cursor == '\n')	{
		printf("DEBUG: Carattere Pronto alla Lettura - A capo!!!\n");
	} else
		printf("DEBUG: Carattere Pronto alla Lettura - %c\n", cursor);

	if(cursor != EOF)       	//se non è stato raggiunto l'End Of File
		ungetc(cursor,file);    //rimetto l'ultimo carattere nel file*/

	return num;
}

//Pulizia del terminale
void io_clearScreen()	{
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

//Pressione del tasto per continuare
void io_pressKey()	{
	printf("\n");
	printf("Premere invio per continuare...");
	getchar();
}