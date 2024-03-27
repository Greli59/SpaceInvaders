#include <stdio.h>

typedef struct{
    int id;
    int x;
    int y;
} entite;


struct cellule{
    entite ent;
    struct cellule *suivant;
};

typedef struct cellule * listeEntite;


void printEntite(entite ent);

listeEntite addHead(entite x, listeEntite l);




void freeListEntite(listeEntite l);

void deleteHead(listeEntite *l);


void printListEntite(listeEntite l);
