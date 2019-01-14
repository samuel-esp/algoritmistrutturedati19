#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*CODA DA IMPLEMENTARE*/

//======================================================================================================================//

typedef struct queue_struct {

    nodo* info;
    struct queue_struct* prev;
    struct queue_struct* next;

} qelem;

typedef struct {

    qelem* first;
    qelem* last;

} queue;

queue* new_queue() {
    queue* q = (queue*)malloc(sizeof(queue));

    q->first = NULL;
    q->last = NULL;
    return q;
}

/* inserisce un intero in coda. Quando inserisco metto
   gli elementi all'inzio della lista. */

void enqueue(queue* q, nodo* n) {

    qelem* e = (qelem*)malloc(sizeof(qelem));
    e->info = n;
    e->prev = NULL;
    e->next = q->first;

    if( q->first != NULL ) {
        q->first->prev = e;
        q->first = e;
    } else {
        q->first = e;
        q->last = e;
    }
}

/* estrae il nodo piu' vecchio dalla coda. Ritorno
   l'ultimo elemento della coda. Assumo che la coda 
   abbia almeno un elemento. */

nodo* dequeue(queue* q) {

    nodo* output = q->last->info;

    if (q->last->prev == NULL) {  /* sto rimuovendo il solo 
                                     elemento della coda */
        free(q->last);
        q->first = NULL;
        q->last = NULL;
    } else {

        qelem* cancellami = q->last;
        q->last->prev->next = NULL;
        q->last = q->last->prev;
        free(cancellami);
    }

    return output;
}

//======================================================================================================================//

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

/* verifica se la coda e' vuota */

int is_empty(queue* q) {
    return q->first == NULL;
}


void bfs(grafo* g, nodo* n) {

    /* inizializzo tutte le marcature a zero */

    nelem* ln = g->nodi;
    while( ln != NULL ) {
    	ln->info->color = 0;
    	ln = ln->next; 
    }
    
    queue* q = new_queue();

    enqueue(q,n);
    n->color = 1; 
    
    while( ! is_empty(q) ) {

    	nodo* m = dequeue(q);
    	eelem* le = m->archi;
    	while( le != NULL ) {
    		nodo* altro_nodo = opposto(m,le->info);
    		if( altro_nodo->color == 0 ) {
    			altro_nodo->color = 1;
    			enqueue(q,altro_nodo);
    		}
    		le = le->next;
    	}
    }
}

/* Esegue una visita in ampiezza a cominciare dal nodo n 
   senza inizializzare a zero tutti i marcatori dei nodi. */

void bfs_senza_inizializzazione(grafo* g, nodo* n) {
  
    queue* q = new_queue();

    enqueue(q,n);
    n->color = 1; 
    
    while( ! is_empty(q) ) {

    	nodo* m = dequeue(q);
    	eelem* le = m->archi;
    	while( le != NULL ) {
    		nodo* altro_nodo = opposto(m,le->info);
    		if( altro_nodo->color == 0 ) {
    			altro_nodo->color = 1;
    			enqueue(q,altro_nodo);
    		}
    		le = le->next;
    	}
    }
}

/* Esegue una visita in ampiezza del grafo per determinare
   se e' connesso o meno. */

int is_connected(grafo* g) {

    if( g->numero_nodi == 0) return 1;  /* convenzionalmente
                                           assumo che un grafo 
                                           vuoto sia connesso */
    bfs(g,g->nodi->info);

    int tutti_marcati = 1;  
    nelem* ln = g->nodi;
    while( ln != NULL ) {

        if( ln->info->color == 0 ) {  // nodo non visitato
            tutti_marcati = 0;
        }
        ln = ln->next;
    }
    return tutti_marcati;
}

/* Esegue una serie di visite in ampiezza del grafo e 
   ritorna il numero delle sue componenti connesse. */

int componenti_connesse(grafo* g) {

    /* inizializzo tutte le marcature a zero */

    nelem* ln = g->nodi;
    while( ln != NULL ) {
        ln->info->color = 0;
        ln = ln->next; 
    }   

    int cconnesse = 0;

    ln = g->nodi;
    while( ln != NULL ) {
        if( ln->info->color == 0) {
            cconnesse = cconnesse + 1;
            bfs_senza_inizializzazione(g,ln->info);
        }
        ln = ln->next;
    }

    return cconnesse;
}

void main() {

    grafo* g = new_grafo();

    nodo* n0 = aggiungi_nodo(g);
    printf("ho aggiunto un nodo con id %d\n",n0->id);
    nodo* n1 = aggiungi_nodo(g);
    printf("ho aggiunto un nodo con id %d\n",n1->id);
    nodo* n2 = aggiungi_nodo(g);
    printf("ho aggiunto un nodo con id %d\n",n2->id);
    nodo* n3 = aggiungi_nodo(g);
    printf("ho aggiunto un nodo con id %d\n",n3->id);
    nodo* n4 = aggiungi_nodo(g);
    printf("ho aggiunto un nodo con id %d\n",n4->id);
    nodo* n5 = aggiungi_nodo(g);
    printf("ho aggiunto un nodo con id %d\n",n5->id);
    nodo* n6 = aggiungi_nodo(g);
    printf("ho aggiunto un nodo con id %d\n",n6->id);

    stampa_grafo(g);

    arco* a0 = aggiungi_arco(g,n0,n1);
    printf("ho aggunto un arco con id %d tra %d e %d\n",
           a0->id, n0->id, n1->id);
    arco* a1 = aggiungi_arco(g,n0,n2);
    printf("ho aggunto un arco con id %d tra %d e %d\n",
           a1->id, n0->id, n2->id);
    printf("ho aggunto un arco con id %d tra %d e %d\n",
           (aggiungi_arco(g,n1,n3))->id, n1->id, n3->id);
    printf("ho aggunto un arco con id %d tra %d e %d\n",
           (aggiungi_arco(g,n1,n4))->id, n1->id, n4->id);
    printf("ho aggunto un arco con id %d tra %d e %d\n",
           (aggiungi_arco(g,n2,n3))->id, n2->id, n3->id);
    printf("ho aggunto un arco con id %d tra %d e %d\n",
           (aggiungi_arco(g,n2,n5))->id, n2->id, n5->id);
    printf("ho aggunto un arco con id %d tra %d e %d\n",
           (aggiungi_arco(g,n3,n5))->id, n3->id, n5->id);
    printf("ho aggunto un arco con id %d tra %d e %d\n",
           (aggiungi_arco(g,n3,n4))->id, n3->id, n4->id);
    printf("ho aggunto un arco con id %d tra %d e %d\n",
           (aggiungi_arco(g,n4,n6))->id, n4->id, n6->id);
    printf("ho aggunto un arco con id %d tra %d e %d\n",
           (aggiungi_arco(g,n5,n6))->id, n5->id, n6->id);

    stampa_grafo(g);

    // bfs(g,n0);

    if( is_connected(g) )
        printf("il grafo e' connesso!\n");
    else 
        printf("il grafo non e' connesso!\n");

    printf("ora rimuovo l'arco %d tra %d e %d\n",
           a0->id, a0->from->id, a0->to->id);
    rimuovi_arco(g,a0);
    printf("ora rimuovo l'arco %d tra %d e %d\n",
           a1->id, a1->from->id, a1->to->id);
    rimuovi_arco(g,a1);

    stampa_grafo(g);

    if( is_connected(g) )
        printf("il grafo e' connesso!\n");
    else 
        printf("il grafo non e' connesso!\n");

    printf("il numero delle componenti connesse e' %d\n", 
           componenti_connesse(g));


    printf("aggiungo (7)-----(8)\n");
    aggiungi_arco(g,aggiungi_nodo(g),aggiungi_nodo(g));

    printf("il numero delle componenti connesse e' %d\n", 
           componenti_connesse(g));



}
