#include "entite.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>
#include "Graphique/libgraph.h"
#include "constants.h"


                            /* FONCTIONS POUR LES LISTES CHAINEES */


// Ajoute une entité en tête de liste
listeEntites addHead(entite ent, listeEntites liste){
    listeEntites tmp;
    tmp = malloc(sizeof(struct cellule));
    tmp->ent = ent;
    tmp->suivant = liste;
    liste = tmp;
    return liste;
}

// Concatene deux listes chainées
listeEntites concatenerListes(listeEntites liste1, listeEntites liste2) {
    if (liste1 == NULL) {
        return liste2;
    }
    listeEntites temp = liste1;
    while (temp->suivant != NULL) {
        temp = temp->suivant;
    }
    temp->suivant = liste2;
    return liste1;
}

// Print les informations d'une entité
void printEntite(entite ent){
    printf("LUTIN = %d; (x,y) = (%d,%d)\n",ent.lutin,ent.x,ent.y);
}


// Libère la mémoire occupée par une liste d'entités
void freeListeEntites(listeEntites liste){
    if (liste == NULL) {return;}
    freeListeEntites(liste->suivant);
    free(liste);
}

// Supprime la tête d'une liste d'entités
void deleteHead(listeEntites *pListe){
    if (*pListe != NULL){
        listeEntites tmp = *pListe;
        *pListe = (*pListe) -> suivant;
        free(tmp);
    }
    else {printf("La liste est vide\n");}
}

// Supprime une entité d'une liste chainée
void supprimeEntite(listeEntites *pListe, listeEntites *prec, listeEntites *courant){
    if ((*prec) == NULL) {
        deleteHead(pListe);
        *courant = *pListe;
    } else {
        (*prec)->suivant = (*courant)->suivant;
        free(*courant);
        *courant = (*prec)->suivant;
    }
}

// Print tous les éléments d'une liste d'entités
void printListeEntites(listeEntites liste){
    listeEntites entiteCourante;
    entiteCourante = liste;
    printf("[ ");
    while(entiteCourante != NULL){
        printEntite(entiteCourante->ent);
        entiteCourante = entiteCourante->suivant;
    }
    printf("]\n");
}

// Affiche les entités d'une liste en utilisant les sprites (lutins)
void afficherListeEntite(listeEntites liste){
    //if (liste == NULL) printf("liste nulle ");
    listeEntites entiteCourante;
    entiteCourante = liste;
    while(entiteCourante != NULL){
        afficherLutin(entiteCourante->ent.lutin, entiteCourante->ent.x, entiteCourante->ent.y);
        entiteCourante = entiteCourante->suivant;
    }
}

// Affiche une entité en utilisant son sprite (lutins)
void afficherEntite(entite ent){
    afficherLutin(ent.lutin, ent.x, ent.y);
}


// Déplace une entité
void moveEntite(entite * ent,int deplacementX, int deplacementY, int seuil){ // On ne déplace l'entite que si elle à attendu suffisament
    // si on met un seuil de -1 c'est qu'on fait un déplacement instantanné sans prendre en compte le delai
    if (seuil == -1){
        (*ent).x += deplacementX;
        (*ent).y += deplacementY;
        return;
    }

    (*ent).delay++;
    if ((*ent).delay >= seuil){
        (*ent).x += deplacementX;
        (*ent).y += deplacementY;
        (*ent).delay = 0;
    }
}

// Déplace toutes les entités d'une liste
void moveListeEntites(listeEntites liste, int deplacementX, int deplacementY, int seuil){
    listeEntites entiteCourante;
    entiteCourante = liste;
    while(entiteCourante != NULL){
        moveEntite(&(entiteCourante->ent),deplacementX,deplacementY,seuil);
        entiteCourante = entiteCourante->suivant;
    }
}

// Change le sprite (lutin) de toutes les entités d'une liste
void changerLutinListeEntites(listeEntites liste, int numLutin){
    listeEntites entiteCourante;
    entiteCourante = liste;
    while(entiteCourante != NULL){
        entiteCourante->ent.lutin = numLutin;
        entiteCourante = entiteCourante->suivant;
    }
}


// Vérifie si au moins une entité d'une liste touche le bord de l'écran
int toucheBord(listeEntites liste) {
    listeEntites entiteCourante;
    entiteCourante = liste;
    while (entiteCourante != NULL) {
        if (entiteCourante->ent.x + largeurSprite(entiteCourante->ent.lutin) >= WIDTH) {return 1;} // Si au moins un monstre touche le bord droit, retourne 1
        if (entiteCourante->ent.x <= 0) {return -1;}
        entiteCourante = entiteCourante->suivant;
    }
    return 0; // Aucun monstre ne touche le bord
}


// Renvoie vrai si un monstre touche le bas de l'écran
bool monstreToucheBasEcran(listeEntites listeMonstres){
    listeEntites entiteCourante;
    entiteCourante = listeMonstres;
    while (entiteCourante != NULL) {
        if (entiteCourante->ent.y + hauteurSprite(entiteCourante->ent.lutin) >= HEIGHT) {return 1;}
        entiteCourante = entiteCourante->suivant;
    }
    return 0;
}

// Lâche une bombe depuis une liste d'entités à une position donnée
void lacherBombe(listeEntites *listeBombes, int posX, int posY, int lutin) {
    entite bombe = {posX, posY, lutin,0};
    *listeBombes = addHead(bombe, *listeBombes);
    //printListeEntites(*listeBombes);
}


// Déplace les bombes selon une vitesse donnée et les supprime si elles sortent de l'écran
void deplacerVertical(listeEntites *liste, int vitesse, int delay) {
    listeEntites prec = NULL;
    listeEntites courant = *liste;
    while (courant != NULL) {
        // Déplacer la bombe/missile
        moveEntite(&(courant->ent), 0, vitesse, delay);
        // Vérifier si la bombe/missile est sortie de l'écran
        if (courant->ent.y > HEIGHT || courant->ent.y < 0) {
            supprimeEntite(liste,&prec,&courant);
        } else {
            // La bombe/missile est toujours à l'écran, passer à l'élément suivant
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
    listeEntites entiteCourante = listeMonstres;
    while (entiteCourante != NULL) {
        count++;
        entiteCourante = entiteCourante->suivant;
    }
    return count;
}


// Creer une entite avec un sprite de bouillie et l'ajotue à la liste de bouillie
void chargerBouillie(listeEntites *listeBouillie, int posX, int posY, int numLutinBouillie) {
    entite bouillie = {posX, posY, numLutinBouillie, BOUILLIE_TEMPS_DE_VIE};
    *listeBouillie = addHead(bouillie, *listeBouillie);
}

// Supprime les bouillies apres avoir attendu un certain delai
void gererBouillie(listeEntites *listeBouillie) {
    listeEntites pBouillie = *listeBouillie;
    listeEntites precBouillie = NULL;

    while (pBouillie != NULL) {
        // Décrémente le délai de l'entité bouilli
        pBouillie->ent.delay--;

        // Si le délai tombe à zéro, supprime l'entité de la liste
        if (pBouillie->ent.delay <= 0) {
            if (precBouillie == NULL) {
                deleteHead(listeBouillie);
                pBouillie = *listeBouillie;
            } else {
                precBouillie->suivant = pBouillie->suivant;
                free(pBouillie);
                pBouillie = precBouillie->suivant;
            }
        } else {
            precBouillie = pBouillie;
            pBouillie = pBouillie->suivant;
        }
    }
}


                                            ////////////////
                                            // COLLISIONS //
                                            ////////////////


bool collisionEntiteEntite(entite ent1, entite ent2) {
    int largeur1;
    int hauteur1;
    int largeur2;
    int hauteur2;
    tailleLutin(ent1.lutin,&largeur1,&hauteur1);
    tailleLutin(ent2.lutin,&largeur2,&hauteur2);
    if (

        (ent1.y < ent2.y + hauteur2) &&
        (ent1.y + hauteur1 > ent2.y) &&
        (ent1.x < ent2.x + largeur2) &&
        (ent1.x + largeur1 > ent2.x)
    )
    {return 1;}

    return 0;
}


bool collisionEntiteListe(entite ent, listeEntites listeEnt){
    listeEntites entiteCourante;
    entiteCourante = listeEnt;
    while(entiteCourante != NULL){
        if (collisionEntiteEntite(ent,entiteCourante->ent)== 1) {return 1;}
        entiteCourante = entiteCourante->suivant;
    }
    return 0;
}

bool collisionListeListe(listeEntites listeEnt1, listeEntites listeEnt2){
    listeEntites entiteCourante;
    entiteCourante = listeEnt1;
    while(entiteCourante != NULL){
        if (collisionEntiteListe(entiteCourante->ent,listeEnt2)== 1) {return 1;}
        entiteCourante = entiteCourante->suivant;
    }
    return 0;
}




// Permet la suppréssion entre deux entité de deux listes lors d'une collision et fait apparaitre une 'explosion'
void collisionListeListeDestructive(listeEntites *listeEntites1, listeEntites *listeEntites2, listeEntites *listeBouillie, int numLutinBouillie) {
    listeEntites pEntite1 = *listeEntites1;
    listeEntites precEntite1 = NULL;

    // On parcours les deux listes, donc 2 boucles while
    while (pEntite1 != NULL) {
        listeEntites pEntite2 = *listeEntites2;
        listeEntites precEntite2 = NULL;

        while (pEntite2 != NULL) {
            if (collisionEntiteEntite(pEntite1->ent, pEntite2->ent)) {


                // Si il y a collision, on fait apparaitre un sprite "d'explosion" au centre du sprite de la cible
                int xBouillie = pEntite2->ent.x + (largeurSprite(pEntite2->ent.lutin) - largeurSprite(numLutinBouillie)) / 2;
                int yBouillie = pEntite2->ent.y + (hauteurSprite(pEntite2->ent.lutin) - hauteurSprite(numLutinBouillie)) / 2;

                chargerBouillie(listeBouillie, xBouillie, yBouillie, numLutinBouillie);

                if (precEntite2 == NULL) {
                    *listeEntites2 = pEntite2->suivant;
                    free(pEntite2);
                } else {
                    precEntite2->suivant = pEntite2->suivant;
                    free(pEntite2);
                }

                if (precEntite1 == NULL) {
                    *listeEntites1 = pEntite1->suivant;
                    free(pEntite1);
                    pEntite1 = *listeEntites1;
                } else {
                    precEntite1->suivant = pEntite1->suivant;
                    free(pEntite1);
                    pEntite1 = precEntite1->suivant;
                }

                break;
            }
            precEntite2 = pEntite2;
            pEntite2 = pEntite2->suivant;
        }

        if (pEntite1 != NULL) {
            precEntite1 = pEntite1;
            pEntite1 = pEntite1->suivant;
        }
    }
}



