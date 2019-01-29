
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
//#include "hash.h"
//#include "hash_nodi.h"

typedef struct nodo_struct nodo;
typedef struct edge_struct arco;

typedef struct node_elem {

	struct node_elem* prev;
	struct node_elem* next;
	nodo*             info;

} nelem;

typedef struct edge_elem {

	struct edge_elem* prev;
	struct edge_elem* next;
	arco*             info;

} eelem;  // sta per "edge elem", elemento di una lista di archi


typedef struct nodo_struct {

	nelem* pos;    /* puntatore alla mia posizione nella lista dei nodi del grafo */
	int    id;     /* identificatore del nodo (per l'utente) */
	int    color;  /* marcatore per ogni uso */
	eelem* archi;  /* la lista degli archi del nodo */

} nodo;

typedef struct edge_struct {

	eelem* pos;       /* puntatore alla mia posizione nella lista degli archi del grafo */
	int    id;        /* identificatore del nodo (per l'utente) */
	nodo*  from;      /* il nodo from */
	nodo*  to;        /* il nodo to */
	eelem* frompos;   /* la mia posizione nella lista degli archi del nodo from */
	eelem* topos;     /* la mia posizione nella lista degli archi del nodo to */

} arco;

typedef struct grafo_struct {

	nelem* nodi;   /* lista dei nodi del grafo */
	eelem* archi;  /* lista degli archi del grafo */
	int numero_nodi;
	int numero_archi;
	int max_id_nodi;
	int max_id_archi;
} grafo;

/* crea un grafo vuoto */

grafo* new_grafo() {

	grafo* g = (grafo*)malloc(sizeof(grafo));

	g->nodi = NULL;
	g->archi = NULL;
	g->numero_nodi = 0;
	g->numero_archi = 0;
	g->max_id_nodi = 0;
	g->max_id_archi = 0;

	return g;
}

/* stampa il grafo */

void stampa_grafo(grafo* g) {

    printf("------stampa del grafo------------\n");
	printf("il grafo ha %d nodi e %d archi\n", 
			g->numero_nodi,
			g->numero_archi);

    nelem* ln = g->nodi;
    while( ln != NULL) {

    	printf("trovato il nodo %d\n", ln->info->id);
        
        eelem* la = ln->info->archi;
        while( la != NULL ) {

            arco* arco_corrente = la->info;
        	nodo* altro_nodo = opposto(ln->info, arco_corrente);
        	printf("\ttrovato l'arco %d verso %d\n", 
        		   arco_corrente->id,
        		   altro_nodo->id);
        	la = la->next;
        }
        ln = ln->next;
    }
    printf("------------------\n");

}


/* aggiungo un nodo al grafo */

nodo* aggiungi_nodo(grafo* g) {

	nodo* n = (nodo*)malloc(sizeof(nodo));
	// n->id = ++(g->max_id_nodi);
	n->id = g->max_id_nodi;
	n->color = 0;
	g->max_id_nodi++;
	n->archi = NULL;

	nelem* ne = (nelem*)malloc(sizeof(nelem));

	ne->prev = NULL;
	ne->info = n;
	ne->next = g->nodi;

	if(g->nodi != NULL) {
		g->nodi->prev = ne;
	} 
	g->nodi = ne;   // mi metto in testa alla lista dei nodi del grafo
	n->pos = ne;    // mi memorizzo la mia posizione in lista
	g->numero_nodi++;

	return n;
}

/* aggiunge un arco tra i due nodi specificati */

arco* aggiungi_arco(grafo* g, nodo* from, nodo* to) {

	arco* a = (arco*)malloc(sizeof(arco));

	a->id = g->max_id_archi;
	g->max_id_archi++;
	g->numero_archi++;

    a->from = from;
    a->to = to;

    a->pos = inserisci_arco_in_lista(&(g->archi),a);
    a->frompos = inserisci_arco_in_lista(&(from->archi),a);
    a->topos = inserisci_arco_in_lista(&(to->archi),a);

    return a;
}



/* Invariante: il nodo n ha l'arco a.
   Ritorna l'altro nodo dell'arco a. */

nodo* opposto(nodo* n, arco* a) {

	nodo* output = a->from;
	if ( output == n )
		output = a->to;
	return output;
}


/* inserisce un arco in una lista di archi passata come 
   parametro (per riferimento). Ritorna un puntatore al 
   list-item utilizzat. */

eelem* inserisci_arco_in_lista(eelem** pla, arco* a) {

	eelem* e = (eelem*)malloc(sizeof(eelem));
	e->info = a;
	e->prev = NULL;
	e->next = (*pla);

	if( (*pla) != NULL ) {
		(*pla)->prev = e;
	}
	(*pla) = e;
	return e;
}

/* rimuove un arco da una lista di archi passata come 
   parametro (per riferimento).  */

void rimuovi_arco_dalla_lista(eelem** pla, eelem* e) {

	if( e->prev != NULL ) {  // non sono il primo della lista
		e->prev->next = e->next;
	} else {  // sono il primo della lista
		(*pla) = e->next;
	}
	if( e->next != NULL ) {  // non sono l'ultimo della lista
		e->next->prev = e->prev;
	}
	free(e);
}

/* Precondizioni: l'arco a appartiene al grafo g.
   Rimuovo l'arco dal grafo e da tutte le liste che lo
   contengono */

void rimuovi_arco(grafo* g, arco* a) {

	g->numero_archi--;
	rimuovi_arco_dalla_lista(&(g->archi),a->pos);
	rimuovi_arco_dalla_lista(&(a->from->archi),a->frompos);
	rimuovi_arco_dalla_lista(&(a->to->archi),a->topos);

	free(a);
}

/* Precondizioni: il nodo n appartiene al grafo g.
   Rimuovo il nodo dal grafo e da tutte le liste che lo
   contengono */

void rimuovi_nodo(grafo* g, nodo* n) {

	eelem* e = n->archi;
	while( e != NULL ) {

		eelem* prossimo_elemento = e->next;
		rimuovi_arco(g,e->info);
		e = prossimo_elemento;
	}

	g->numero_nodi--;

	if( n->pos->prev == NULL ) {  // sono il primo della lista
		g->nodi = n->pos->next;
	} else {  // c'e' un nodo che mi precede
		n->pos->prev->next = n->pos->next;
	}

	if( n->pos->next != NULL ) {  // non sono l'ultimo della lista
		n->pos->next->prev = n->pos->prev;
	}
	free(n->pos);
	free(n);
}

/* Visita in profodita' del grafo a partire dal nodo dato */

void DFS(grafo* g, nodo* n) {

    // marco tutti i nodi come non visitati
    //
    nelem* ln = g->nodi;
    while( ln != NULL ) {
        ln->info->color = 0;
        ln = ln->next;
    }

    if( g->numero_nodi > 0)
        DFS_visit(n);

}

void DFS_visit(nodo* n) {

    n->color = 1;  // marco il nodo n come visitato
    eelem* pla = n->archi;  // pla = puntatore ad una lista di archi
    while ( pla != NULL ) {
        arco* e = pla->info;
        nodo* altro_nodo = opposto(n,e);
        if( altro_nodo->color == 0 ) {
            DFS_visit(altro_nodo);
        }
        pla = pla->next;
    }

}

/* Conta le componenti connesse */

int numero_componenti_connesse(grafo* g) {

    int numero_cc = 0;

    // marco tutti i nodi come non visitati
    //
    nelem* ln = g->nodi;
    while( ln != NULL ) {
        ln->info->color = 0;
        ln = ln->next;
    }  


    ln = g->nodi;
    while( ln != NULL ) {
        if( ln->info->color == 0 ) {
            numero_cc++;  
            DFS_visit(ln->info);
        }
        ln = ln->next;
    }

    return numero_cc;
}

/* Cuore ricorsivo di una visita in profondita'. Mentre visito
   marco i nodi visitati con il marcatore m passato come parametro. */

void DFS_visit_marcatore(nodo* n, int m) {

    n->color = m;  // marco il nodo n come visitato
    eelem* pla = n->archi;  // pla = puntatore ad una lista di archi
    while ( pla != NULL ) {
        arco* e = pla->info;
        nodo* altro_nodo = opposto(n,e);
        if( altro_nodo->color == 0 ) {
            DFS_visit_marcatore(altro_nodo,m);
        }
        pla = pla->next;
    }
}

/* Cuore ricorsivo di una visita in profondita'. Mentre visito
   marco i nodi visitati con il marcatore m passato come parametro 
   e conto i nodi e gli archi incontrati. */

void DFS_visit_contatori(nodo* n, int m, int* numero_nodi, int* numero_archi) {

    numero_nodi[m]++;
    n->color = m;  // marco il nodo n come visitato
    eelem* pla = n->archi;  // pla = puntatore ad una lista di archi
    while ( pla != NULL ) {
        numero_archi[m]++;
        arco* e = pla->info;
        nodo* altro_nodo = opposto(n,e);
        if( altro_nodo->color == 0 ) {
            DFS_visit_contatori(altro_nodo,m,numero_nodi,numero_archi);
        }
        pla = pla->next;
    }
}


/* Verifica se tutte le componenti connesse hanno lo stesso 
   numero di nodi */

int componenti_uguali(grafo* g) {

    int numero_cc = 0;

    // marco tutti i nodi come non visitati
    //
    nelem* ln = g->nodi;
    while( ln != NULL ) {
        ln->info->color = 0;
        ln = ln->next;
    }  


    ln = g->nodi;
    while( ln != NULL ) {
        if( ln->info->color == 0 ) {
            numero_cc++;  
            DFS_visit_marcatore(ln->info,numero_cc);
        }
        ln = ln->next;
    }

    /* contatore_nodi[i] mi dira' quanti nodi appartengono alla
       componente i. contatore_nodi[0] non e' utilizzato. L'ultima
       cella e' contatore_nodi[numero_cc]. */

    int* contatore_nodi = (int*)calloc(numero_cc+1,sizeof(int));

    ln = g->nodi;
    while( ln != NULL ) {
        contatore_nodi[ln->info->color]++;
        ln = ln->next;
    }

    int i;
    for( i = 2 ; i <= numero_cc; i++ ) {
        if( contatore_nodi[i] != contatore_nodi[1] )
            return 0;
    }

    return 1;

}


/* Verifica che tutte le componenti connesse del grafo siano 
   "bilanciate", cioe' abbiano tanti nodi quanti archi */

int componenti_bilanciate(grafo* g) {

    /* contatori dei nodi e degli archi delle componenti */

    int* numero_nodi = (int*)calloc(g->numero_nodi+1,sizeof(int));
    int* numero_archi = (int*)calloc(g->numero_nodi+1,sizeof(int));

    int numero_cc = 0;

    // marco tutti i nodi come non visitati
    //
    nelem* ln = g->nodi;
    while( ln != NULL ) {
        ln->info->color = 0;
        ln = ln->next;
    }  


    ln = g->nodi;
    while( ln != NULL ) {
        if( ln->info->color == 0 ) {
            numero_cc++;  
            DFS_visit_contatori(ln->info,numero_cc,numero_nodi,numero_archi);
        }
        ln = ln->next;
    }

    int i;
    for( i = 1; i <= numero_cc; i++) {
        if( numero_nodi[i] != numero_archi[i]/2 )
            return 0; // ho trovato una componente "sbilanciata"
    }

    return 1;

}

/* Verifica che tutte le componenti connesse del grafo siano 
   "bilanciate", cioe' abbiano tanti nodi quanti archi.
   Metodo alternativo che non fa uso dei contatori. */

int componenti_bilanciate_alt(grafo* g) {

    int numero_cc = 0;

    // marco tutti i nodi come non visitati
    //
    nelem* ln = g->nodi;
    while( ln != NULL ) {
        ln->info->color = 0;
        ln = ln->next;
    }  


    ln = g->nodi;
    while( ln != NULL ) {
        if( ln->info->color == 0 ) {
            numero_cc++;  
            DFS_visit_marcatore(ln->info,numero_cc);
        }
        ln = ln->next;
    }

    int i;
    for( i = 1 ; i <= numero_cc; i++) {
        int numero_nodi = 0; // di questa componente connessa
        int numero_archi = 0; // di questa componente connessa
        ln = g->nodi;
        while ( ln != NULL ) {
            if( ln->info->color == i ) {  // il nodo appartiene a questa cc
                numero_nodi++;
                eelem* pla = ln->info->archi;
                while ( pla != NULL) {
                    numero_archi++;
                    pla = pla->next; 
                }
            }
            ln = ln->next; 
        }
        if( numero_nodi != numero_archi/2 ) 
            return 0;
    } // passo alla prossima componente connessa
    return 1;

}
