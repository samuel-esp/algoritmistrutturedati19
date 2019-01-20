#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*==========================================================================================================================*/

//DFS OGGETTI E RIFERIMENTI//

void funzione(){

    lem_nodi* en = g->nodi;

    while (en != NULL) {
        en->info->color = 0; // marco tutti i nodi con 0
        en = en->next;
    }

//SCRIVO IL RESTO DELLA CONSEGNA DELL'ESERCIZIO

}

void DFS(nodo* n, int mark) {

    n->color = mark; // coloro il nodo come visitato
    elem_archi ea = n->archi;

    while( ea != NULL){

        nodo* altro_nodo = ea->info->from;

            if( altro_nodo == n) {
                altro_nodo = ea->info->to;
            }
            if( altro_nodo->color == 0) { // se non e' gia' visitato...
            DFS(altro_nodo, mark); // ... lo visito e marco
            }

 ea = ea->next;
    
    }
} 

/*==========================================================================================================================*/

//DFS LISTE DI ADIACENZA//

void funzione()
{
    //marco tutti i nodi con 0
   
	for(i=0;i<n;i++)
        visited[i]=0;
 
    //SCRIVO IL RESTO DELLA CONSEGNA DELL'ESERCIZIO
}
 
void DFS(int i){
    node *p;
   
	printf("\n%d",i);
    p=G[i];
    visited[i]=1;
    while(p!=NULL)
    {
       i=p->vertex;
       
	   if(!visited[i])
            DFS(i);
        p=p->next;
    }
}

/*==========================================================================================================================*/

//DFS MATRICE DI ADIACENZA

void funzione(){

    //marco tutti i nodi con 0
   for(i=0;i<n;i++)
        visited[i]=0;
 
    //SCRIVO IL RESTO DELLA CONSEGNA DELL'ESERCIZIO
}
 
void DFS(int i)
{
    int j;
    visited[i]=1;
    
    for(j=0;j<n;j++)
        if(!visited[j]&&G[i][j]==1)
            DFS(j);
}