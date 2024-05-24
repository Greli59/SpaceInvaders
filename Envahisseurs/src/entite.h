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
listeEntites addHead(entite ent, listeEntites liste);
listeEntites concatenerListes(listeEntites liste1, listeEntites liste2);
void freeListeEntites(listeEntites liste);
void deleteHead(listeEntites *pListe);
void supprimeEntite(listeEntites *pListe, listeEntites *prec, listeEntites *courant);
void printListeEntites(listeEntites liste);

void afficherListeEntite(listeEntites liste);
void afficherEntite(entite ent);

void moveEntite(entite * ent,int deplacementX, int deplacementY, int seuil);
void moveListeEntites(listeEntites liste, int deplacementX, int deplacementY, int seuil);

void changerLutinListeEntites(listeEntites liste, int numLutin);
int toucheBord(listeEntites liste);
bool monstreToucheBasEcran(listeEntites listeMonstres);

void lacherBombe(listeEntites *listeBombes, int posX, int posY, int lutin);
void deplacerVertical(listeEntites *liste, int vitesse, int delay);


int largeurSprite(int lutin);
int hauteurSprite(int lutin);
int compteMonstres(listeEntites listeMonstres);


bool collisionEntiteEntite(entite ent1, entite ent2);
bool collisionEntiteListe(entite ent, listeEntites listeEnt);
bool collisionListeListe(listeEntites listeEnt1, listeEntites listeEnt2);

void chargerBouillie(listeEntites *listeBouillie, int posX, int posY, int numLutinBouillie);
void gererBouillie(listeEntites *listeBouillie);

void collisionListeListeDestructive(listeEntites *listeEntites1, listeEntites *listeEntites2, listeEntites *listeBouillie, int numLutinBouillie);
