#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Graphique/libgraph.h"
#include "entite.h"


#define HEIGHT 768
#define WIDTH 1024
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

    int numLutinBombe = chargerLutin("../Lutins/invader_bombe.bmp", 1);
    listeEntites listeBombes = NULL;


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
    //int dirJoueur = 1;
    int dirMonstres1 = 1;
    int dirMonstres2 = 1;



    evenement evt;
    char touche;
    void *detail;


    while(1){

        /*
        listeEntites p;
        p = listeMonstres1;
        while(p != NULL){
            (p->ent.x)++;
            p = p->suivant;
        }
        */

        lireEvenement(&evt,&touche,&detail);


        if (evt == toucheBas){
            printf("%d = ",touche);
            printf("%c\n",touche);
        }
        else if (evt == toucheHaut){
            printf("Haut\n");
        }
        else if (evt == quitter){
            printf("Quitter\n ");
        }


        if (evt == toucheBas && touche == 'q' && joueur.x>0){
            moveEntite(&joueur,-10,0);
        }
        if (evt == toucheBas && touche == 'd' && joueur.x<WIDTH-50){
            moveEntite(&joueur,10,0);
        }


        if (evt == quitter){
            fermerSurface();
            freeListeEntites(listeBombes);
            freeListeEntites(listeBoucliers);
            freeListeEntites(listeMonstres1);
            freeListeEntites(listeMonstres2);
            return(1);
        }

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





          // BOMBES


        /*
        if (timer == 50) {
            lacherBombe(&listeBombes, 100, 100, numLutinBombe);
            printf("bombe lachée\n");
        }
toucheBas
        listeEntites pMonstre2 = listeMonstres2;
        if (timer <300 && animation == 15) {
            while (pMonstre2 != NULL) {
                lacherBombe(&listeBombes, pMonstre2->ent.x, pMonstre2->ent.y, numLutinBombe);
                pMonstre2 = pMonstre2->suivant;
            }
        }

        deplacerBombes(&listeBombes, 2, HEIGHT-100);
        */


        //-------

        /*
        if (joueur.x>WIDTH || joueur.x<0) {
            dirJoueur *= -1;
        }


        moveEntite(&joueur,dirJoueur*10,0);
        */

        if (toucheBord(listeMonstres1,HEIGHT,WIDTH)) {
            dirMonstres1 *= -1;
            moveListeEntites(listeMonstres1, 0, 15);
        }

         if (toucheBord(listeMonstres2,HEIGHT,WIDTH)) {
            dirMonstres2 *= -1;
            moveListeEntites(listeMonstres2, 0, 15);
        }


        moveListeEntites(listeMonstres1, 5 * dirMonstres1, 0);
        moveListeEntites(listeMonstres2, 5 * dirMonstres2, 0);

        rectanglePlein(0,0,WIDTH,HEIGHT,1);

        afficherListeEntite(listeMonstres1);
        afficherListeEntite(listeMonstres2);
        afficherListeEntite(listeBoucliers);
        afficherEntite(joueur);
        afficherListeEntite(listeBombes);

        majSurface();

        timer++;
        SDL_Delay(DELAY);
        //printf("%d ",timer);
        fflush(stdout);
/*
        if (timer>600){
            fermerSurface();
            printf("\n");
            freeListeEntites(listeBombes);
            freeListeEntites(listeBoucliers);
            freeListeEntites(listeMonstres1);
            freeListeEntites(listeMonstres2);
            return(1);
        }
        */
    }
    printf("\n");


    SDL_Quit();
    return(1);
}
