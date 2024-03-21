#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Graphique/libgraph.h"

#define HEIGHT 720
#define WIDTH 1280
#define DELAY 10 //ms

int main(){
    creerSurface(WIDTH,HEIGHT,"test");
    //chargerSurface("test");

    //rectanglePlein(250,250,250,250,0);

    int bjr = lutinTexte("bonjour",COULEUR_BLANC);
    int numLutin = chargerLutin("../Lutins/millepatte_champi.bmp",0);

    afficherLutin(numLutin,250,250);
    int i =0;
    while(1){
        if (i==100){
                afficherLutin(bjr,250,100);
        }

        if (i>200){
            rectanglePlein(0,0,500,500,1);

            afficherLutin(numLutin,i+150,100);

        }

        if (i>350){
            fermerSurface();
            return(1);
        }
        i++;
        majSurface();
        SDL_Delay(DELAY);
        printf("%d\n",i);
    }
    return(1);
}
