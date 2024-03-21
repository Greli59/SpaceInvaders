#include <stdio.h>
#include "Graphique/libgraph.h"

int main(){
    creerSurface(500,500,"test");
    chargerSurface("test");
    rectanglePlein(20,20,10,10,0);

    while(1){
        chargerSurface("test");
    }
    fermerSurface();
    return(1);
}
