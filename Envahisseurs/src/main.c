#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Graphique/libgraph.h"

int main(){
    creerSurface(500,500,"test");
    chargerSurface("test");

    //rectanglePlein(250,250,250,250,0);

    int bjr = lutinTexte("bonjour",0);
    int numLutin = chargerLutin("../Lutins/invader_monstre2_1.bmp",1);

    afficherLutin(numLutin,250,250);
    int i =0;
    while(1){
        if (i==100){
                afficherLutin(bjr,250,100);
        }

        if (i==200){
            rectanglePlein(0,0,500,500,1);

            afficherLutin(numLutin,400,100);

        }

        if (i>350){
            fermerSurface();
            return(1);
        }
        i++;
        majSurface();
        SDL_Delay(10);
        //printf("%d\n",i);
    }
    return(1);
}
