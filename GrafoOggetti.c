#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//DOPO AVER DICHIARATO LE LIBRERIE DICHAIRO LA STRUTTURA CHE COMPONE IL GRAFO//

typedef struct node_elem {

	struct node_elem* prev;
	struct node_elem* next;
	nodo*             info;

} nelem;

typedef struct edge_elem {

	struct edge_elem* prev;
	struct edge_elem* next;
	arco*             info;

} eelem;


typedef struct nodo_struct {

	nelem* pos;    /* puntatore alla mia posizione nella lista dei nodi del grafo */
	int    id;     /* identificatore del nodo (per l'utente) */
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