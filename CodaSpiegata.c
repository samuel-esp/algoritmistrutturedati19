#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 6

//DOPO AVER DICHIARATO LE LIBRERIE DICHAIRO TRE VARIABILI GLOBALI (VALGONO OVUNQUE), L'ARRAY L'INDICE TOP SETTATO UNA POSIZIONE AL DI FUORI DELL'ARRAY, COSI COME L'INDICE TAIL//

int top = -1;
int tail = -1;
int array[MAXSIZE];

//====================================================================================================================================//

//INSERISCO LA FUNZIONE ENQUEUE: INSERIMENTO IN CODA//

void Enqueue(){

	int x;
	printf("inserisci un intero: ");
	scanf("%d", &x);

		if((tail+1)%MAXSIZE == top) 		//se l'espressione e' verificata l'array e' pieno
			printf("la coda e' piena");
   else if(top == -1 && tail == -1){		//se top e tail sono in posizione -1, vuol dire che l'array e' vuota, quindi possiamo incrementare entrambi	
			top = 0;
			tail = 0;
			array[tail] = x;
		}
	  else{									//in qualunque altro caso, tail va incrementata di 1, la sequente operazione di modulo e' "innocua" in quanto l'operando maxsize e' come se fosse 1 nella divisione
		tail = (tail+1)%MAXSIZE;
		array[tail] = x;
	}
}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE DEQUEUE: ELIMINAZIONE IN CODA//

void Dequeue(){

		if(top == -1 && tail == -1)			//se top e tail sono in posizione -1, allora la coda e' gia vuota in partenza
			printf("la coda e' gia' vuota\n");
   else	if(top==tail){						//se top e' nella stessa posizione di tail, allora si riportano entrambi alla configurazione di partenza (-1)
			top=-1;
			tail=-1;
}	
       else									//in ogni altro caso top viene incrementato, tutti i valori precedenti vengono quindi "dimenticati"
  			top=top+1;
}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE FRONT: RITORNA L'ELEMENTO IN CIMA//

void front(){

	printf("%d\n", array[top]);

}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE TAIL: RITORNA L'ELEMENTO IN CODA//

void coda(){

	printf("%d\n", array[tail]);

}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE SIZE: RITORNA LA DIMENSIONE DELLA CODA//

void size(){

	if(top== -1 & tail==-1) //la coda e' vuota perche' gli indici sono entrambi nulli
		printf("la coda ha: 0 elementi\n");
	else if(top==tail)		//top e tail sono coincidenti, vuol dire che c'e' almeno un elemento
		printf("la coda ha: 1 elemento\n");
	else if(top>tail)		
		printf("la coda ha: %d elementi\n", MAXSIZE-top+tail+1);
	else
		printf("la coda ha: %d elementi \n", tail-top+1);

}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE PRINT: STAMPA TUTTA LA CODA//

void Stampa(){

	if(top==-1 && tail==-1) //se top e tail sono -1 la lista e' vuota
		printf("la lista e' vuota\n");
	else if(top>tail){      //se top e' maggiore di tail allora stampo 2 segmenti (da top a maxsize-1 nel primo segmento e da 0 a tail nel secondo)
		for(int i=top; i<MAXSIZE; i++)
			printf("%d ", array[i]);
		for(int j=0; j<=tail; j++)
			printf("%d ", array[j]);	
	}
	else{					//se tail e' maggiore di top allora stampo 1 segmento solo che va da top a tail incluso
		for(int i=top; i<=tail; i++)
			printf("%d ", array[i]);
	}
}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE DI ISEMPTY: VERIFICA SE LA PILA E' VUOTA//

void isEmpty(){

	if(top == -1 && tail == -1) //se top e tail si trovano entrambi in posizione nulla allora la coda e' vuota
		printf("la coda e' vuota\n");
	else	//in ogni altro caso la coda contiene alemeno un elemento
		printf("la coda contiene almeno un elemento");

}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE EMPTY: SVUOTA LA CODA//

void Empty(){

	top = -1;	//resetto il valore di top in posizione nulla 
	tail = -1;	//resetto il valore di front in posizione nulla

}

//====================================================================================================================================//

//INSERISCO IL MENU//

int main(){

	int scelta; //memorizza la scelta che effettuera' l'utente dopo aver visualizzato il menu'

	while(scelta!=0){

		printf("\nCHE OPERAZIONE VUOI SVOLGERE?\n\n");
		printf("[1] -> ENQUEUE\n");
		printf("[2] -> DEQUEUE\n");
		printf("[3] -> FRONT\n");
		printf("[4] -> IS EMPTY\n");
		printf("[5] -> EMPTY\n");
		printf("[6] -> SIZE\n");
		printf("[7] -> STAMPA COMPLETA\n");
		printf("[8] -> TAIL\n");
		printf("[0] -> ESCI\n");
		printf("SCELTA: ");
		scanf("%d", &scelta);

		if(scelta==1){
			Enqueue();
		}

else	if(scelta==2){
			Dequeue();
		}
else	if(scelta==3){
			front();
		}
else	if(scelta==4){
			isEmpty();
		}
else	if(scelta==5){
			Empty();
		}
else	if(scelta==6){
			size();
		}
else	if(scelta==7){
			Stampa();
		}
else	if(scelta==8){
			coda();
		}

	}

printf("ARRIVEDERCI\n\n");

}