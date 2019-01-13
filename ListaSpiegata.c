#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//DOPO AVER DICHIARATO LE LIBRERIE DICHAIRO LA STRUTTURA CHE COMPONE IL NODO//

struct Nodo{
	int intero; //informazione che abbiamo nel nodo
	struct Nodo* next;	//riferimento al nodo successivo
};

typedef struct Nodo* NODO; //per comodita' rinomianiamo il riferimento al nodo successivo con la sola scritta NODO per pura comodita'

//====================================================================================================================================//

//INSERISCO LA FUNZIONE: INSERIMENTO IN TESTA: PRENDE IN CONSEGNA LA LISTA E UN INTERO I//

NODO inserisci_testa(NODO lista, int i){

	NODO head = malloc(sizeof(struct Nodo)); //alloco nella memoria un nodo, lo chiamo head in quanto sara' il primo al termine dell'esecuzione della funzione
	head->intero=i; //inserisco nel campo intero del nuovo nodo l'intero i che ho ricevuto in consegna dalla funzione
	head->next=lista; //collego next al nodo che prima stava in testa alla lista, di conseguenza il nodo appena creato diventera' il nuovo primo elemento

	return head; //il nodo verra' ritornato 
}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE: INSERIMENTO IN CODA: PRENDE IN CONSEGNA LA LISTA E UN INTERO I//

NODO inserisci_coda(NODO lista, int i){

	NODO coda = malloc(sizeof(struct Nodo)); //alloco nella memoria un nodo, lo chiamo coda in quanto verra' messo in ultima posizione al termine della funzione
	coda->intero=i; //inserisco nel campo intero del nuovo nodo l'intero i che ho ricevuto in consegna dalla funzione
	coda->next=NULL; //siccome coda e' l'ultimo elemento, il next deve avere NULL come collegamento successivo

	if(lista==NULL){
		lista=coda; //se la lista e' vuota, coda allora e' il primo elemento
	}
	else{
		NODO current; //dichiaro un nodo current, servira' per lo scorrimento della lista
		current = lista; //assegno current il valore della testa della lista, ovvero il primo elemento della lista
		while(current->next!=NULL)
			current = current->next; //scorro la lista fino a giungere all'ultimo elemento

		current->next=coda; //una volta arrivati all'ultimo elemento inserisco la coda, che sara' il nuovo ultimo elemento della lista
	}

	return lista; //siccome ho modificato la coda, la testa rimane invariata, per questo ritorno il riferimento originale

}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE NUOVO ELEMENTO: CONSENTE ALL'UTENTE DI MEMORIZZARE NUOVI ELEMENTI, ESSI VERRANO INSERITI UTILIZZANDO LE FUNZIONI SCRITTE IN PRECEDENZA//

NODO nuovo_elemento(NODO lista){

	int new_element;

	printf("utente inserisci un intero\n");
	scanf("%d", &new_element);

	return inserisci_testa(lista, new_element); //l'elemento viene spedito nelle funzioni scritte in precedenza; NOTA BENE: potevo usare inserisci_coda al posto di inserisci testa

}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE CANCELLAZIONE IN TESTA: PRENDE IN CONSEGNA LA LISTA//

NODO cancella_testa(NODO lista){

	NODO current; //dichiaro un nodo current, servira' come nodo di appoggio

	if(lista==NULL)
		printf("nulla da cancellare\n"); //se lista==NULL allora la lista e' gia' vuota
	else{
		current = lista->next; //assegno a current il secondo nodo della lista
		free(lista); //utilizzando free cancello il primo nodo della lista
	}

	return current; //al termine della funzione ritorniamo il secondo nodo, che sara' quindi diventato il nuovo primo

}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE CANCELLAZIONE IN CODA: PRENDE IN CONSEGNA LA LISTA//

NODO cancella_coda(NODO lista){

	NODO current; //dichiaro un nodo current, servira' per scorrere la lista
	NODO temp; //dichiaro un nodo temp, sara' un contenitore temporaneo 

	if(lista==NULL)
		printf("nulla da cancellare\n"); //se lista==NULL allora la lista e' gia vuota
	else if(lista->next==NULL){
		free(lista); //se lista->next==NULL allora siamo in presenza dell'ultimo nodo, lo eliminiamo
		lista=NULL;	//lista ritorna ad essere quindi vuota
	}
	else{
		current = lista; //aseggno la lista al nodo current per poterla scorrerla
		while(current->next->next!=NULL)
			current = current->next; //scorro la lista fino ad arrivare al penultimo nodo

		temp=current->next; //assegno alla variabile temp l'ultimo riferimento 
		free(temp); //cancello l'ultimo nodo 
		current->next=NULL;	//current di next a questo punto puntera' a null in quanto e' l'ultimo nodo rimasto dopo la cancellazione di temp
	}

	return lista; //ritorno la lista in quanto ho effettuato una cancellazione in coda


}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE STAMPA: PRENDE IN CONSEGNA LA LISTA, L'ELEMENTO E L'EVENTUALE INDICE DI ORDINAMENTO/

void stampaintero(int intero, int posizione){

	printf("Intero %d: %d\n", posizione, intero); //funzione che stampa l'intero, viene chiamato dalla funzione che scriveremo sotto

}

void stampalista(NODO lista){

	int i=1; //variabile contatore che identifica la posizione dell'elemento all'interno della lista

	if(lista==NULL)
		printf("lista vuota\n"); //se lista==NULL allora la lista e' vuota
	else{
		while(lista!=NULL){ 
			stampaintero(lista->intero, i); //scorro la lista e passo gli elementi di essa alla funzione scritta sopra, affinche li stampi sullo schermo dell'utente
			lista = lista->next;	//scorro la lista fino a che non e' nulla
			i++;	//nel frattempo incremento l'indice che mi identifica la posizone dell'elemento
		}

	}
}

//====================================================================================================================================//

//INSERISCO LA FUNZIONE CONTALISTA

void contalista(NODO lista){
	
	int lunghezza=0;

	while(lista!=NULL){
		lunghezza++;
		lista = lista->next;
	}

	printf("la lista conteine %d elementi", lunghezza);

}

//====================================================================================================================================//

//INSERISCO IL MENU//

int main(){

	int scelta; //memorizza la scelta che effettuera' l'utente dopo aver visualizzato il menu'

	NODO lista = NULL;

	while(scelta!=0){

		printf("\nCHE OPERAZIONE VUOI SVOLGERE?\n\n");
		printf("[1] -> INSERISCI IN TESTA\n");
		printf("[2] -> INSERISCI IN CODA\n");
		printf("[3] -> CANCELLA IN TESTA\n");
		printf("[4] -> CANCELLA IN CODA\n");
		printf("[5] -> STAMPA LISTA\n");
		printf("[0] -> ESCI\n");
		printf("SCELTA: ");
		scanf("%d", &scelta);

		if(scelta==1){
			lista = nuovo_elemento(lista);
		}

else	if(scelta==2){
			lista = nuovo_elemento(lista);
		}
else	if(scelta==3){
			lista = cancella_testa(lista);
		}
else	if(scelta==4){
			lista = cancella_coda(lista);
		}
else	if(scelta==5){
			stampalista(lista);

	}
else	if(scelta==6){
			contalista(lista);

	}

}

printf("ARRIVEDERCI\n\n");

}
