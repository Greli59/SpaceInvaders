#include "entite.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Graphique/libgraph.h"

listeEntites addHead(entite x, listeEntites l){
    listeEntites tmp;
    tmp = malloc(sizeof(struct cellule));
    tmp->ent = x;
    tmp->suivant = l;
    l = tmp;
    return l;
}


void printEntite(entite ent){
    printf("ID = %d; (x,y) = (%d,%d)\n",ent.id,ent.x,ent.y);
}


void freeListeEntites(listeEntites l){
    if (l == NULL) return;
    freeListeEntites(l->suivant);
    free(l);
}

void deleteHead(listeEntites *l){
    if (*l != NULL){
        listeEntites tmp = *l;
        *l = (*l) -> suivant;
        free(tmp);
    }
    else printf("La liste est vide\n");
}


void printListeEntites(listeEntites l){
    listeEntites p;
    p = l;
    printf("[ ");
    while(p != NULL){
        printEntite(p->ent);
        p = p->suivant;
    }
    printf("]\n");
    return;
}

void afficherListeEntite(listeEntites l){
    listeEntites p;
    p = l;
    while(p != NULL){
        afficherLutin(p->ent.lutin, p->ent.x, p->ent.y);
        p = p->suivant;
    }
    return;
}

void afficherEntite(entite ent){
    afficherLutin(ent.lutin, ent.x, ent.y);
}


void moveEntite(entite * ent,int vx, int vy){
    (*ent).x += vx;
    (*ent).y += vy;
}

void moveListeEntites(listeEntites L, int vx, int vy){
    listeEntites p;
    p = L;
    while(p != NULL){
        moveEntite(&(p->ent),vx,vy);
        p = p->suivant;
    }
}


void changerLutinListeEntites(listeEntites L, int numLutin){
    listeEntites p;
    p = L;
    while(p != NULL){
        p->ent.lutin = numLutin;
        p = p->suivant;
    }
}
