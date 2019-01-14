#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//DOPO AVER DICHIARATO LE LIBRERIE DICHAIRO LA STRUTTURA CHE COMPONE IL NODO DELL'ALBERO//

struct Nodo{

    int info; //informazione contenuta all'interno del nodo
    struct Nodo* left; //figlio sinistro
    struct Nodo* right; //figlio destro	
};

typedef struct Nodo* NODO;

//====================================================================================================================================//

NODO nuovonodo(int valore){

	NODO nuovo = (NODO)malloc(sizeof(struct Nodo)); //con questo passaggio si alloca la memoria necessaria a contenere un nuovo elemento

	nuovo->info = valore; //inserisco nel campo info il valore preso in consegna
	nuovo->left = NULL; //inserisco nel campo left NULL in quanto il nodo non ha figli
	nuovo->right = NULL; //inserisco nel campo right NULL in quanto il nodo non ha figli

	return nuovo;


}

NODO inserimento(NODO nodo, int valore){

	if(nodo == NULL)
		return nuovonodo(valore); //CASO I: il nodo in questione e' la radice che non e' stata ancora riempita

	else if(valore < nodo->info)
		nodo->left = inserimento(nodo->left, valore); //CASO II: valore piu' piccolo -> va nel sottoalbero sinistro

	else if(valore > nodo->info)
		nodo->right = inserimento(nodo->right, valore); //CASO III: valore piu' grande -> va nel sottoalbero destro


	return nodo;

}

void cancellazione_intera(NODO nodo){

	if(nodo == NULL)
		return;

	cancellazione_intera(nodo->left);
	cancellazione_intera(nodo->right);

	free(nodo);

}

NODO cancellazione_nodo(NODO nodo, int valore){

	if(nodo == NULL)
		return nodo;

	if(valore < nodo->info)
		nodo->left = cancellazione_nodo(nodo->left, valore);

	else if(valore > nodo->info)
		nodo->right = cancellazione_nodo(nodo->right, valore);

	else{

		if(nodo->left == NULL){

			NODO temp = nodo->right;
			free(nodo);
			return temp;
		}
		else if(nodo->right == NULL){
			NODO temp = nodo->left;
			free(nodo);
			return temp;
		}

	NODO temp = RicercaMinimo(nodo->right);
	nodo->info = temp->info;
	nodo->right = cancellazione_nodo(nodo->right, valore);
}

return nodo;

}

void Preordine(NODO nodo){

	if(nodo == NULL)
		return; //se il nodo e' nullo non c'e' nulla da stampare

	printf("%d\n", nodo->info); //PRIMA stampo POI ricorro

	Preordine(nodo->left); 
	Preordine(nodo->right);
}

void Postordine(NODO nodo){

	if(nodo == NULL)
		return; //nodo vuoto

	Postordine(nodo->left);
	Postordine(nodo->right);

	printf("%d\n", nodo->info); //PRIMA ricorro POI stampo

}

void Simmetrica(NODO nodo){

	if(nodo == NULL)
		return; //nodo vuoto

	Simmetrica(nodo->left); //ricorro prima sul sinistro

	printf("%d\n", nodo->info);

	Simmetrica(nodo->right); //ricorro sul destro

}

int Ricerca(NODO nodo, int chiave){

	int esistenza = 0;

	printf("inserisci il valore da cercare: ");
	scanf("%d", &chiave);

	if(nodo == NULL)
		esistenza = 0;
	if(nodo->info == chiave)
		esistenza = 1;
	else (Ricerca(nodo->left, chiave) || Ricerca(nodo->right, chiave));

	return esistenza;


}

int RicercaMassimo(NODO nodo){

	int max;

	if(nodo == NULL)
		max = -1; //non abbiamo nessun valore utile
	else{

		max = nodo->info; //prendiamo come riferimento il valore della radice

		int sinistra = RicercaMassimo(nodo->left); //ricorro a sinistra 
		int destra = RicercaMassimo(nodo->right); //ricorro a destra

		if(max<sinistra)
			max = sinistra;
		
		if(max<destra)
			max = destra;

	}

	return max;

}

int altezza(NODO nodo){

	if(nodo == NULL)  //caso base: albero vuoto: altezza=-1 (PER CONVENZIONE TEORICA!)
		return -1;

	int l = altezza(nodo->left); //passo ricorsivo
	int r = altezza(nodo->right); //passo ricorsivo

	if(l>r)
		return l+1; //in base al sottoalbero left e right piu' grande tra i due, restituisco il valore
	else
		return r+1;

}

int contanodi(NODO nodo){

	if(nodo == NULL) 
		return 0; //passo base; albero vuoto ha 0 nodi (PER CONVENZIONE TEORICA!)

	int conteggio = 0;

	if(nodo->left && nodo->right)
		conteggio++; //aggiungo al conteggio se i nodi presentano figli

	conteggio = conteggio + contanodi(nodo->left) + contanodi(nodo->right); //ricorro sui figli e valuto la stessa proprieta'

	return conteggio; //ritorno il conteggio

}

int contafoglie(NODO nodo){

	if(nodo == NULL)
		return 0; //passo base: se l'albero non ha nodi non ha nemmeno foglie

	if(nodo->left == NULL && nodo->right=NULL)
		return 1; //passo 2: se i nodi non hanno figli allora sono foglie
	else
		return contafoglie(nodo->left) + contafoglie(nodo->right); //passo 3: altrimenti ricorro sui figli per vevedere se verifcano il passo 2

}

int completo(NODO nodo){

	int foglie == contafoglie(nodo);
	int altezza == altezza(nodo);

	if(2^altezza == foglie)
		return 1;
	else
		return 0;

}

int sommanodi(NODO nodo){

	if(nodo = NULL)
		return 0; //se il nodo e' nullo la somma e' 0
	else
		return nodo->info + sommanodi(nodo->left) + sommanodi(nodo->right); //ricorro sui figli sommando anche il valore contenuto nella radice

}

int esistefoglia(NODO nodo, int valore){

	if(nodo = NULL)
		return 0; //se la radice e' nulla, non esiste quello che cerchi

	if((n->info== valore) && (n->left == NULL) && (n->right == NULL))
		return 1; //se il valore e' stato trovato e il nodo verifica la condizione "foglia", allora abbiamo trovato quello che cerchiamo

	else esistefoglia(n->left, valore) || esistefoglia(n->right, valore); //altrimenti ricorro sui figli
}

int livello(NODO nodo,  int altezza){

	if(nodo == NULL)
		return 0; //se la radice e' nulla non abbiamo nodi sul livello iniziale

	if(altezza == 0)
		return 1; //se l'altezza e' 0 abbiamo un solo nodo 
 
	return livello(nodo->left, altezza) + livello(nodo->right, altezza); //ricorro sui figli fino ad arrivare all'altezza verificata e ritorno il numero dei nodi a tale altezza

}


//====================================================================================================================================//

//INSERISCO IL MENU//

int main(){

	int scelta; //memorizza la scelta che effettuera' l'utente dopo aver visualizzato il menu'

	while(scelta!=0){

		NODO root = NULL;

		printf("\nCHE OPERAZIONE VUOI SVOLGERE?\n\n");
		printf("[1] -> INSERIMENTO NODO\n");
		printf("[2] -> STAMPA PREORDER\n");
		printf("[3] -> STAMPA POSTORDER\n");
		printf("[4] -> STAMPA SIMMETRICA\n");
		printf("[5] -> RICERCA\n");
		printf("[6] -> MASSIMO\n");
		printf("[0] -> ESCI\n");
		printf("SCELTA: ");
		scanf("%d", &scelta);

		if(scelta==1){

		int valore;

		printf("inserisci il valore: ");
		scanf("%d", &valore);

		root = inserimento(root, valore);
		}

else	if(scelta==2){
			//Preordine(root);
		}
else	if(scelta==3){
			Postordine(root);
		}
else	if(scelta==4){
			Ordine(root);
		}
else	if(scelta==5){

		int chiave;

		printf("inserisci il valore da cercare: ");
		scanf("%d", &chiave);

		int risultato = Ricerca(root, chiave);		

		if(risultato==1)
			printf("ESISTENZA VERIFICATA\n");
		else
			printf("ESISTENZA NON VERIFICATA\n");

	}
else	if(scelta==6){

			int massimo = RicercaMassimo(root);

			printf("IL MASSIMO E': %d\n", massimo);

	}

}

printf("ARRIVEDERCI\n\n");

}
