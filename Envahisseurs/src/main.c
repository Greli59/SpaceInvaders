#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Graphique/libgraph.h"
#include "entite.h"


#define HEIGHT 720
#define WIDTH 1280
#define DELAY 10 //ms

#define NB_MONSTRES 5
#define NB_BOUCLIERS 4



int main(){

    /*
    entite testEntite1 = {1,2,3,0};
    entite testEntite2 = {2,3,4,0};
    entite testEntite3= {7,1,2,0};
    entite testEntite4 = {2,3,9,0};
    printEntite(testEntite1);


    listeEntites L = NULL;

    L = addHead(testEntite1,L);
    printListeEntites(L);
    L = addHead(testEntite2,L);
    L = addHead(testEntite3,L);
    printListeEntites(L);
    deleteHead(&L);
    printListeEntites(L);


    printEntite((L->suivant)->ent);


    creerSurface(WIDTH,HEIGHT,"test");
    //chargerSurface("test");

    //rectanglePlein(250,250,250,250,0);

    int bjr = lutinTexte("bonjour",COULEUR_BLANC);
    int numLutin = chargerLutin("../Lutins/millepatte_champi.bmp",0);
*ent
    */



    /*
    int i =0;
    while(1){
        rectanglePlein(0,0,HEIGHT,WIDTH,1);


        if (i<200){
            afficherLutin(numLutin,250,250);
        }
        if (i>100){
                afficherLutin(bjr,250,100);


        }

        if (i>200){
            rectanglePlein(0,0,HEIGHT,WIDTH,1);

            afficherLutin(numLutin,i+150,100);

        }



        if (i>350){
            fermerSurface();
            return(1);
        }

        afficherListeEntite(listeMonstres);

        i++;
        majSurface();
        SDL_Delay(DELAY);
        printf("%d ",i);
        fflush(stdout);
    }
    printf("\n");
    */

    creerSurface(WIDTH,HEIGHT,"test");

    int numLutinMonstre1 = chargerLutin("../Lutins/invader_monstre2_1.bmp", 1);
    int numLutinMonstre1bis = chargerLutin("../Lutins/invader_monstre2_2.bmp", 1);

    listeEntites listeMonstres1 = NULL;
    for (int i = 0; i < NB_MONSTRES; ++i) {
        entite monstre = {i+1, 100 + i*50, 100, numLutinMonstre1};
        listeMonstres1 = addHead(monstre, listeMonstres1);
    }

    int numLutinMonstre2 = chargerLutin("../Lutins/invader_monstre1_1.bmp", 1);
    listeEntites listeMonstres2 = NULL;
    for (int i = 0; i < NB_MONSTRES; ++i) {
        entite monstre = {i+1, 100 + i*50, 200, numLutinMonstre2};
        listeMonstres2 = addHead(monstre, listeMonstres2);
    }

    int numLutinBouclier = chargerLutin("../Lutins/invader_bouclier.bmp", 1);
    listeEntites listeBoucliers = NULL;
    for (int i = 0; i < NB_BOUCLIERS; ++i) {
        entite bouclier = {i+1, 125 + i*75, 400, numLutinBouclier};
        listeBoucliers = addHead(bouclier, listeBoucliers);
    }

    int numLutinJoueur = chargerLutin("../Lutins/invader_canon.bmp", 1);
    entite joueur = {0,250,500,numLutinJoueur};


    int timer = 0;
    int animation = 0;
    while(1){

        /*
        listeEntites p;
        p = listeMonstres1;
        while(p != NULL){
            (p->ent.x)++;
            p = p->suivant;
        }
        */

        animation++;
        if (animation<10) {
            changerLutinListeEntites(listeMonstres1,numLutinMonstre1bis);
            //printf("test1");
        }
        else {
            changerLutinListeEntites(listeMonstres1,numLutinMonstre1);
            //printf("test2");
            if (animation>20) animation = 0;
        }

        moveEntite(&joueur,1,0);
        moveListeEntites(listeMonstres1,2,0);

        rectanglePlein(0,0,WIDTH,HEIGHT,1);

        afficherListeEntite(listeMonstres1);
        afficherListeEntite(listeMonstres2);
        afficherListeEntite(listeBoucliers);
        afficherEntite(joueur);

        majSurface();

        timer++;
        SDL_Delay(DELAY);
        printf("%d ",timer);
        fflush(stdout);

        if (timer>350){
            fermerSurface();
            return(1);
        }
    }
    printf("\n");



    return(1);
}
