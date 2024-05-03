#include "entite.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Graphique/libgraph.h"
#include "constants.h"


/* FONCTIONS POUR LES LISTES CHAINEES */

// Ajoute une entité en tête de liste
listeEntites addHead(entite x, listeEntites l){
    listeEntites tmp;
    tmp = malloc(sizeof(struct cellule));
    tmp->ent = x;
    tmp->suivant = l;
    l = tmp;
    return l;
}

// Print les informations d'une entité
void printEntite(entite ent){
    printf("LUTIN = %d; (x,y) = (%d,%d)\n",ent.lutin,ent.x,ent.y);
}


// Libère la mémoire occupée par une liste d'entités
void freeListeEntites(listeEntites l){
    if (l == NULL) return;
    freeListeEntites(l->suivant);
    free(l);
}

// Supprime la tête d'une liste d'entités
void deleteHead(listeEntites *l){
    if (*l != NULL){
        listeEntites tmp = *l;
        *l = (*l) -> suivant;
        free(tmp);
    }
    else printf("La liste est vide\n");
}


// Print tous les éléments d'une liste d'entités
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

// Affiche les entités d'une liste en utilisant les sprites (lutins)
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

// Affiche une entité en utilisant son sprite (lutins)
void afficherEntite(entite ent){
    afficherLutin(ent.lutin, ent.x, ent.y);
}


// Déplace une entité
void moveEntite(entite * ent,int vx, int vy){
    (*ent).x += vx;
    (*ent).y += vy;
}

// Déplace toutes les entités d'une liste
void moveListeEntites(listeEntites L, int vx, int vy){
    listeEntites p;
    p = L;
    while(p != NULL){
        moveEntite(&(p->ent),vx,vy);
        p = p->suivant;
    }
}

// Change le sprite (lutin) de toutes les entités d'une liste
void changerLutinListeEntites(listeEntites L, int numLutin){
    listeEntites p;
    p = L;
    while(p != NULL){
        p->ent.lutin = numLutin;
        p = p->suivant;
    }
}


// Vérifie si au moins une entité d'une liste touche le bord de l'écran
int toucheBord(listeEntites L) {
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


// Lâche une bombe depuis une liste d'entités à une position donnée
void lacherBombe(listeEntites *listeBombes, int x, int y, int lutin) {
    entite bombe = {x, y, lutin};
    *listeBombes = addHead(bombe, *listeBombes);
    //printListeEntites(*listeBombes);
}


// Déplace les bombes selon une vitesse donnée et les supprime si elles sortent de l'écran
void deplacerBombes(listeEntites *listeBombes, int vitesse) {
    printf("%d\n",WIDTH);
    listeEntites prec = NULL;
    listeEntites courant = *listeBombes;
    while (courant != NULL) {
        // Déplacer la bombe
        moveEntite(&(courant->ent), 0, vitesse);
        // Vérifier si la bombe est sortie de l'écran
        if (courant->ent.y > HEIGHT - 100) {
            // La bombe est sortie de l'écran, nous devons la supprimer
            // Si la bombe à supprimer est en tête de liste
            if (prec == NULL) {
                // Mettre à jour le pointeur de tête de liste
                *listeBombes = courant->suivant;
                // Libérer la mémoire
                free(courant);
                // Avancer au prochain élément
                courant = *listeBombes;
            } else {
                // La bombe à supprimer n'est pas en tête de liste
                prec->suivant = courant->suivant;
                // Libérer la mémoire
                free(courant);
                // Avancer au prochain élément
                courant = prec->suivant;
            }
        } else {
            // La bombe est toujours à l'écran, passer à l'élément suivant
            prec = courant;
            courant = courant->suivant;
        }
    }
}


// Déplace les missiles selon une vitesse donnée et les supprime s'ils sortent de l'écran
void deplacerMissiles(listeEntites *listeMissiles, int vitesse) {
    listeEntites prec = NULL;
    listeEntites courant = *listeMissiles;
    while (courant != NULL) {
        // Déplacer le missile
        moveEntite(&(courant->ent), 0, -(vitesse));
        // Vérifier si le missile est sorti de l'écran
        if (courant->ent.y < 0) {
            // Le missile est sorti de l'écran, nous devons le supprimer
            // Si le missile à supprimer est en tête de liste
            if (prec == NULL) {
                // Mettre à jour le pointeur de tête de liste
                *listeMissiles = courant->suivant;
                // Libérer la mémoire
                free(courant);
                // Avancer au prochain élément
                courant = *listeMissiles;
            } else {
                // Le missile à supprimer n'est pas en tête de liste
                prec->suivant = courant->suivant;
                // Libérer la mémoire
                free(courant);
                // Avancer au prochain élément
                courant = prec->suivant;
            }
        } else {
            // Le missile est toujours à l'écran, passer à l'élément suivant
            prec = courant;
            courant = courant->suivant;
        }
    }
}



// Retourne la largeur d'un sprite à partir de son numéro de lutin
int largeurSprite(int lutin){
    int largeur;
    int hauteur;
    tailleLutin(lutin,&largeur,&hauteur);
    return largeur;
}

// Retourne la hauteur d'un sprite à partir de son numéro de lutin
int hauteurSprite(int lutin){
    int largeur;
    int hauteur;
    tailleLutin(lutin,&largeur,&hauteur);
    return hauteur;
}
// J'imagine qu'il est possible de mieux faire ces fonctions en regardant comment à été ecrit tailleLutin()




// Compte le nombre d'entités dans une liste
int compteMonstres(listeEntites listeMonstres) {
    int count = 0;
    listeEntites p = listeMonstres;
    while (p != NULL) {
        count++;
        p = p->suivant;
    }
    return count;
}

