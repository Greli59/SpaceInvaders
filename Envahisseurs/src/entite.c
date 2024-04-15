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
    //if (l == NULL) printf("liste nulle ");
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

int toucheBord(listeEntites L, int HEIGHT, int WIDTH) {
    listeEntites p;
    p = L;
    while (p != NULL) {
        if (p->ent.x <= 0 || p->ent.x >= WIDTH) {
            return 1; // Si au moins un monstre touche le bord, retourne 1
        }
        p = p->suivant;
    }
    return 0; // Aucun monstre ne touche le bord
}

void lacherBombe(listeEntites *listeBombes, int x, int y, int lutin) {
    entite bombe = {0, x, y, lutin};
    *listeBombes = addHead(bombe, *listeBombes);
    //printListeEntites(*listeBombes);
}

// A MODIFIER POUR NE PAS SUPPRIMER TOUTE LES BOMBES
void deplacerBombes(listeEntites *listeBombes, int vitesse, int HEIGHT) {
    int i = 1;
    listeEntites p = *listeBombes;
    while (p != NULL) {
        printListeEntites(*listeBombes);
        moveEntite(&(p->ent), 0, vitesse);
        if (p->ent.y > HEIGHT) {
            listeEntites tmp = p;
            p = p->suivant;
            deleteHead(&tmp);
            *listeBombes = p;
            printf("%d ",i);
            i++;
        } else {
            p = p->suivant;
        }
    }
}


int largeurSprite(int lutin){
    int largeur;
    int hauteur;
    tailleLutin(lutin,&largeur,&hauteur);
    return largeur;
}
