#include <stdio.h>
#include <stdbool.h>

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
void supprimeEntite(listeEntites *pliste, listeEntites *prec, listeEntites *courant);
void printListeEntites(listeEntites l);

void afficherListeEntite(listeEntites l);
void afficherEntite(entite ent);

void moveEntite(entite * ent,int vx, int vy, int seuil);
void moveListeEntites(listeEntites L, int vx, int vy, int seuil);

void changerLutinListeEntites(listeEntites L, int numLutin);
int toucheBord(listeEntites L);

void lacherBombe(listeEntites *listeBombes, int x, int y, int lutin);
void deplacerVertical(listeEntites *liste, int vitesse, int delay);


int largeurSprite(int lutin);
int hauteurSprite(int lutin);
int compteMonstres(listeEntites listeMonstres);


bool collisionEntiteEntite(entite ent1, entite ent2);
bool collisionEntiteListe(entite ent, listeEntites listeEnt);
bool collisionListeListe(listeEntites listeEnt1, listeEntites listeEnt2);
