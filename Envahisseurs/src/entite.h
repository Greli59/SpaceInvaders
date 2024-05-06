#include <stdio.h>

#define TAILLE_TYPE_ENTITE 20

typedef struct{
    int x; //coordonnée
    int y;
    int lutin; //stocker le numéro de lutin (peut changer au cours du jeu)
    int delay;
} entite;

struct cellule{
    entite ent;
    struct cellule *suivant;
};

typedef struct cellule * listeEntites;



void printEntite(entite ent);
listeEntites addHead(entite x, listeEntites l);
void freeListeEntites(listeEntites l);
void deleteHead(listeEntites *l);
void printListeEntites(listeEntites l);

void afficherListeEntite(listeEntites l);
void afficherEntite(entite ent);

void moveEntite(entite * ent,int vx, int vy, int seuil);
void moveListeEntites(listeEntites L, int vx, int vy, int seuil);

void changerLutinListeEntites(listeEntites L, int numLutin);
int toucheBord(listeEntites L);

void lacherBombe(listeEntites *listeBombes, int x, int y, int lutin);
void deplacerBombes(listeEntites *listeBombes, int vitesse);
void deplacerMissiles(listeEntites *listeMissiles, int vitesse);


int largeurSprite(int lutin);
int hauteurSprite(int lutin);
int compteMonstres(listeEntites listeMonstres);


int collisionEntiteEntite(entite ent1, entite ent2);
int collisionEntiteListe(entite ent, listeEntites listeEnt);
int collisionListeListe(listeEntites listeEnt1, listeEntites listeEnt2);
