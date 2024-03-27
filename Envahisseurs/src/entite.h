#include <stdio.h>

#define TAILLE_TYPE_ENTITE 20

typedef struct{
    int id; //Chaque entite possede un identifiant indépendant de son 'lutin'
    int x; //coordonnée
    int y;
    int lutin; //stocker le numéro de lutin (peut changer au cours du jeu)
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

void moveEntite(entite * ent,int vx, int vy);
void moveListeEntites(listeEntites, int vx, int vy);

void changerLutinListeEntites(listeEntites L, int numLutin);
int toucheBord(listeEntites L, int HEIGHT, int WIDHT);

void lacherBombe(listeEntites *listeBombes, int x, int y, int lutin);
void deplacerBombes(listeEntites *listeBombes, int vitesse, int HEIGHT);
