#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//DOPO AVER DICHIARATO LE LIBRERIE DICHAIRO LA STRUTTURA CHE COMPONE IL GRAFO//

typedef struct grafo_matrice_struct {

	int numero_nodi; //numero di nodi appartenti al grafo
	int** matrice; //puntatore alla matrice (primo elemento)

} grafo_matrice;

//DOPO AVER DICHIARATO LE LIBRERIE DICHAIRO LA STRUTTURA CHE COMPONE LA LISTA//

grafo_liste* matrice_a_lista(grafo_matrice* g){

	grafo_liste* g_out = (grafo_liste*)malloc(sizeof(grafo_liste)); //dichiaro un puntatore a grafo liste e alloco memoria per il grafo da restituire a fine funzione
	g_out->numero_nodi = g->numero_nodi; //i numeri nodi delle due strutture sono equivalenti essendo questa una traduzione
	g_out->adiacenti = (elist**)calloc(g->numero_nodi,sizeof(elist*)); //funzione calloc e' una malloc ma dopo aver creato spazio, inizializza anche la memoria

    int i, j; //dichiaro due contatori

    for( i = 0; i < g->numero_nodi; i++ ) {
    	for( j = 0; j < g->numero_nodi; j++ ) {
    		if( g->matrice[i][j] == 1 )
    			inserisci_in_lista(&(g_out->adiacenti[i]), j); //scruto tutta la matrice e utilizzo la funzione inserisci lista per inserire l'elemento nella lista
    			// inserisci_in_lista(g_out->adiacenti+i, j);
    	}
    }
    return g_out;

}

void stampa_grafo_matrice(grafo_matrice* g) {

	int i, j; //prendo due contatori
	for(i = 0; i < g->numero_nodi; i++ ) {
		for( j = 0 ; j < g->numero_nodi; j++) {
		printf("\t%d", g->matrice[i][j]); //scorro e stampo ogni elemento conservato nella matrice
	    }
	    printf("\n");
	}
}

int grado_uscita_matrice(grafo_matrice* g, int u) {

	int grado = 0;
	int i;
	for (i = 0; i < g->numero_nodi ; i++ ) { 
		grado += g->matrice[u][i];
	}
	return grado;
}


int grado_ingresso_matrice(grafo_matrice* g, int u) {

	int grado = 0;
	int i;
	for (i = 0; i < g->numero_nodi ; i++ ) {
		grado += g->matrice[i][u];
	}
	return grado;
}

float grado_uscita_medio_matrice(grafo_matrice* g) {

	float somma_gradi = 0.0;
	int i;
	for (i = 0; i < g->numero_nodi ; i++ ) {
		somma_gradi += grado_uscita(g,i);
	}
	// printf("somma_gradi = %f\n",somma_gradi);
	return somma_gradi/g->numero_nodi;
}

int grafo_semplice_matrice(grafo_matrice* g) {

	int i;
	for( i = 0 ; i < g->numero_nodi; i++ ) {
		if (g->matrice[i][i] ==1)
			return 0; 
	}
	return 1;
}

int verifica_non_orientato_matrice(grafo_matrice* g) {

	int i, j;

	for (i = 0; i < g->numero_nodi; i++) {
		for (j = 0; j <= i ; j++) {
			if ( g->matrice[i,j] != g->matrice[j,i])
				return 0;  // sei un grafo orientato
		}
	}
	return 1;
}
