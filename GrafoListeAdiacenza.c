#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//DOPO AVER DICHIARATO LE LIBRERIE DICHAIRO LA STRUTTURA CHE COMPONE IL GRAFO//

typedef struct elist_struct {
	struct elist_struct* prev; //puntatore al nodo precedente
	struct elist_struct* next; //puntatore al nodo successivo
	int info; //campo info
} elist;


typedef struct grafo_liste_struct {

	int numero_nodi; //numero di nodi del grafo
	elist** adiacenti; //puntatore alla lista

}grafo_liste;

void inserisci_in_lista(elist** pl, int i) {

	elist* e = (elist*)malloc(sizeof(elist));
	e->prev = NULL;
	e->info = i;
	e->next = (*pl);

	if( (*pl) != NULL )
		(*pl)->prev = e;

	(*pl) = e;
}

grafo_matrice* matrice(grafo_liste* g) {

	grafo_matrice* gm = (grafo_matrice*)malloc(sizeof(grafo_matrice));

    gm->numero_nodi = g->numero_nodi;
    gm->matrice = (int**)calloc(gm->numero_nodi,sizeof(int*));
    int i;
    for( i = 0; i < gm->numero_nodi; i++) {
    	gm->matrice[i] = (int*)calloc(gm->numero_nodi,sizeof(int));
    }

    for( i = 0; i < g->numero_nodi; i++) {
    	elist* e = g->adiacenti[i];
    	while( e != NULL ) {
    		gm->matrice[i][e->info] = 1;
    		e = e->next;
    	}
    }
    return gm;
}

void stampa_grafo_liste(grafo_liste* g) {

    int i;
    for(i = 0; i < g->numero_nodi; i++) {
    	printf("nodo %d: ",i);
    	elist* e = g->adiacenti[i];
    	while ( e != NULL ){
    		printf("\t%d",e->info);
    		e = e->next;
    	}
    	printf("\n");
    }
}

int grado_uscita_liste(grafo_liste* g, int u) {

	int totale = 0;
    elist* e = g->adiacenti[u];
    while ( e != NULL ){
    	totale++;
    	e = e->next;
    } 
    return totale;
}

int grado_ingresso_liste(grafo_liste* g, int u) {

	int totale = 0;
	int i;
	for ( i = 0; i < g->numero_nodi; i++ ) {
		elist* e = g->adiacenti[i];
		while( e != NULL) {
			if (e->info == u) 
				totale++;
			e = e->next;
		}
	}
	return totale;
}

float grado_uscita_medio_liste(grafo_liste* g) {

	float somma_gradi = 0.0;
	int i;
	for (i = 0; i < g->numero_nodi ; i++ ) {
		somma_gradi += grado_uscita_liste(g,i);
	}
	// printf("somma_gradi = %f\n",somma_gradi);
	return somma_gradi/g->numero_nodi;
}

int grafo_semplice_liste(grafo_liste* g)  {

	int i;
	for (i = 0; i < g->numero_nodi; i++) {

		elist* e = g->adiacenti[i];
		while( e != NULL) {
			if( e->info == i ) return 0;
			e = e->next; 
		}
	}
	return 1;
}

int verifica_arco(grafo_liste* g, int u, int v) {

	elist* e = g->adiacenti[u];
	while( e !=  NULL) {
		if( e->info == v ) return 1;
		e = e->next;
	}
	return 0;
 }

 int verifica_non_orientato_liste(grafo_liste* g) {

	int i;
	for( i = 0; i < g->numero_nodi; i++) {
		elist* e = g->adiacenti[i];
		while ( e != NULL) {    // ho trovato un arco da i ad e->info
			if ( ! verifica_arco(g,e->info,i) )
				return 0;   // sei un grafo orientato
			e = e->next;
		}
	}
	return 1;
}