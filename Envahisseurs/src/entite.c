#include "entite.h"
#include <stdio.h>
#include <stdlib.h>


listeEntite addHead(entite x, listeEntite l){
    listeEntite tmp;
    tmp = malloc(sizeof(struct cellule));
    tmp->ent = x;
    tmp->suivant = l;
    l = tmp;
    return l;
}


void printEntite(entite ent){
    printf("ID = %d; (x,y) = (%d,%d)\n",ent.id,ent.x,ent.y);
}


void freeListEntite(listeEntite l){
    if (l == NULL) return;
    freeListEntite(l->suivant);
    free(l);
}

void deleteHead(listeEntite *l){
    if (*l != NULL){
        listeEntite tmp = *l;
        *l = (*l) -> suivant;
        free(tmp);
    }
    else printf("La liste est vide\n");
}


void printListEntite(listeEntite l){
    listeEntite p;
    p = l;
    printf("[ ");
    while(p != NULL){
        printEntite(p->ent);
        p = p->suivant;
    }
    printf("]\n");
    return;
}
