#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 101

//DOPO AVER DICHIARATO LE LIBRERIE DICHAIRO DUE VARIABILI GLOBALI (VALGONO OVUNQUE), L'ARRAY E L'INDICE TOP SETTATO UNA POSIZIONE AL DI FUORI DELL'ARRAY//

int array[MAXSIZE];
int top = -1;

//====================================================================================================================================//

//INSERISCO LA FUNZIONE DI PUSH: INSERIMENTO IN TESTA//

void Push(){

	int x; //elemento che l'utente vuole inserire nella pila
	printf("inserisci un intero: ");
	scanf("%d", &x);

	//implemento l'algoritmo di inserimento dell'elemento scelto

	if(top == MAXSIZE-1) //se top e' arrivato alla fine dell'array non potra' piu' inserire nulla
		printf("errore overflow\n");
	else{
		top++; 
		array[top] = x; //altrimenti, dopo aver aumentato di una posizione top, inserisco l'elemento x
	}
}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE DI POP: STAMPA DELL'ELEMENTO IN CIMA//

void Top(){

	printf("%d\n", array[top]);
}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE DI POP: ELIMINA L'ELEMENTO IN CODA//

void Pop(){

	if(top==-1) //se l'indice top si trova in posizione nulla (-1), non c'e' nulla da eliminare
		printf("errore non ci sono elementi da elimanre\n");
	else		//se l'array si trova in qualunque altra posizione, decrementare la variabile top, in modo che una volta che l'utente inserira' un nuovo elemento, vi sara' una sovrascrizione.
		top = top -1; 

}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE DI ISEMPTY: VERIFICA SE LA PILA E' VUOTA//

void isEmpty(){

	if(top==-1) //se l'indice top si trova in posizione nulla, la lista e' vuota
		printf("la pila e' vuota\n");
	else		//se l'indice e' invece in qualunque altra posizione l'array non e' vuoto
		printf("la pila contiene almeno un elemento\n");

}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE DI POP: ELIMINA L'ELEMENTO IN CODA//

void Empty(){

	top = -1; //assegno la posizione -1 all'indice
	printf("la pila e' stata cancellata");

}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE SIZE: CONTROLLA QUANTI ELEMENTI SONO PRESENTI//

void Size(){

	printf("la pila contiene: %d elementi\n", top+1); //top+1 mi da il numero degli elementi presenti nella pila
}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE STAMPA: STAMPA TUTTI GLI ELEMENTI ALL'INTERNO DELLA PILA//

void Stampa(){

	if(top!=-1){
	for(int i = 0; i <= top; i++) //fino a quando non arrivo a top, stampo ogni indice presente nell'array
		printf("%d\n", array[i]);
		}
	else
		printf("Nulla Da Stampare\n"); 

}

//====================================================================================================================================//

//INSERISCO IL MENU//

int main(){

	int scelta; //memorizza la scelta che effettuera' l'utente dopo aver visualizzato il menu'

	while(scelta!=0){

		printf("CHE OPERAZIONE VUOI SVOLGERE?\n\n");
		printf("[1] -> PUSH\n");
		printf("[2] -> TOP\n");
		printf("[3] -> POP\n");
		printf("[4] -> IS EMPTY\n");
		printf("[5] -> EMPTY\n");
		printf("[6] -> SIZE\n");
		printf("[7] -> STAMPA COMPLETA\n");
		printf("[0] -> ESCI\n");
		printf("SCELTA: ");
		scanf("%d", &scelta);

		if(scelta==1){
			Push();
		}

else	if(scelta==2){
			Top();
		}
else	if(scelta==3){
			Pop();
		}
else	if(scelta==4){
			isEmpty();
		}
else	if(scelta==5){
			Empty();
		}
else	if(scelta==6){
			Size();
		}
else	if(scelta==7){
			Stampa();
		}

	}

printf("ARRIVEDERCI\n\n");

}