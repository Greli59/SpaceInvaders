#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "Graphique/libgraph.h"
#include "entite.h"
#include "constants.h"



// Fonction pour générer un nombre aléatoire entre min et max
int randInRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main(){
    srand(time(NULL)); // Initialisation du temps pour la gestion du hasard
    creerSurface(WIDTH,HEIGHT,"test"); // Création de la surface


    // Chargement des lutins
    int numLutinMissile = chargerLutin("../Lutins/invader_missile.bmp", 1);
    int numLutinBombe = chargerLutin("../Lutins/invader_bombe.bmp", 1);
    int numLutinMonstre1 = chargerLutin("../Lutins/invader_monstre2_1.bmp", 1);
    int numLutinMonstre1bis = chargerLutin("../Lutins/invader_monstre2_2.bmp", 1);
    int numLutinMonstre2 = chargerLutin("../Lutins/invader_monstre1_1.bmp", 1);
    int numLutinBouclier = chargerLutin("../Lutins/invader_bouclier.bmp", 1);
    int numLutinJoueur = chargerLutin("../Lutins/invader_canon.bmp", 1);

    // Initialisation des listes d'entités
    listeEntites listeMissiles = NULL;
    listeEntites listeBombes = NULL;
    listeEntites listeMonstres1 = NULL;
    listeEntites listeMonstres2 = NULL;
    listeEntites listeBoucliers = NULL;

    // Création des entités
    for (int i = 0; i < NB_MONSTRES; ++i) {
        entite monstre1 = {100 + i*50, 100, numLutinMonstre1};
        entite monstre2 = {100 + i*50, 200, numLutinMonstre2};
        listeMonstres1 = addHead(monstre1, listeMonstres1);
        listeMonstres2 = addHead(monstre2, listeMonstres2);
    }

    for (int i = 0; i < NB_BOUCLIERS; ++i) {
        entite bouclier = {125 + i*75, 400, numLutinBouclier};
        listeBoucliers = addHead(bouclier, listeBoucliers);
    }

    // Création de l'entité joueur
    entite joueur = {250, 500, numLutinJoueur};



    // Variables pour la gestion du jeu
    int timer = 0;
    int animation = 0;
    int dirJoueur = 0;
    int dirMonstres1 = 1;
    int dirMonstres2 = 1;
    int cooldownTimer = 0;
    evenement evt;
    char touche;
    void *detail;
    int joueurLargeur;
    int joueurHauteur;

    tailleLutin(numLutinJoueur,&joueurLargeur,&joueurHauteur);



    while(1){


        // Lecture de l'appui des touches
        lireEvenement(&evt,&touche,&detail);

        // Test pour connaitres les appuis de touches
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





        // Déplacement du joueur

        if (evt == toucheBas && touche == 'q' && joueur.x>0){
            //moveEntite(&joueur,-10,0);
            dirJoueur = -1;
        }
        else if (evt == toucheBas && touche == 'q' && joueur.x<0){
            dirJoueur = 0;
        }
        else if (evt == toucheBas && touche == 'd' && joueur.x<WIDTH-joueurLargeur){
            //moveEntite(&joueur,10,0);
            dirJoueur = 1;
        }
        else if (evt == toucheBas && touche == 'd' && joueur.x>WIDTH-joueurLargeur){
            dirJoueur = 0;
        }
        else if ((evt == toucheHaut && touche == 'q')||(evt == toucheHaut && touche == 'd')){
            dirJoueur = 0;
        }

        moveEntite(&joueur,dirJoueur*8,0);




        // Missiles lancés par le joueur

        // Pour gérer le temps entre chaque lancé possible de missile par le joueur, je vérifie si mon cooldown est égal à zéro et donc je peux tirer
        // Sinon, je décrémente mon cooldown jusqu’à ce qu'il atteigne ce zéro, cette étape se répète un certain nombre de fois, créant donc un temps d'attente
        printf("cooldown = %d\n",cooldownTimer);
        if (cooldownTimer != 0){
                cooldownTimer--;
        }

        if (evt == toucheBas && touche == 'z' && cooldownTimer == 0){
            cooldownTimer = COOLDOWN;
            entite missile = {joueur.x+(largeurSprite(numLutinJoueur)/2)-(largeurSprite(numLutinMissile)/2), joueur.y, numLutinMissile}; // Le missile apparaît aux centres du joueur, et on doit soustraire sa propre largeur/2 du missile pour bien le centrer
            listeMissiles = addHead(missile, listeMissiles);
        }

        deplacerMissiles(&listeMissiles, 10);



        // Quitter le jeu
        if (evt == quitter){

            // On libère la mémoire
            freeListeEntites(listeMissiles);
            freeListeEntites(listeBombes);
            freeListeEntites(listeBoucliers);
            freeListeEntites(listeMonstres1);
            freeListeEntites(listeMonstres2);

            fermerSurface();
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




        if (timer % 50 == 0) {
            listeEntites pMonstre = listeMonstres2;
            int nombre_monstres = compteMonstres(listeMonstres2);
            int monstre_choisi = rand() % nombre_monstres; // Choix aléatoire d'un monstre

            // Parcourir la liste des monstres jusqu'à atteindre le monstre choisi
            int monstre_actuel = 0;
            while (pMonstre != NULL && monstre_actuel < monstre_choisi) {
                pMonstre = pMonstre->suivant;
                monstre_actuel++;
            }

            // Vérifier si un monstre a été trouvé
            if (pMonstre != NULL) {
                // Lâcher une bombe depuis ce monstre
                lacherBombe(&listeBombes, pMonstre->ent.x, pMonstre->ent.y, numLutinBombe);
                printf("Bombe lâchée par un monstre !\n");
            }
        }

        deplacerBombes(&listeBombes, 2);



        // Déplacement des monstres
        // A changer pour que tout les monstres changent de directions si un seul des monstres touche le bord, et pas seulement ligne par ligne de monstres
        if (toucheBord(listeMonstres1)) {
            dirMonstres1 *= -1;
            moveListeEntites(listeMonstres1, 0, 15);
        }
         if (toucheBord(listeMonstres2)) {
            dirMonstres2 *= -1;
            moveListeEntites(listeMonstres2, 0, 15);
        }


        moveListeEntites(listeMonstres1, 5 * dirMonstres1, 0);
        moveListeEntites(listeMonstres2, 5 * dirMonstres2, 0);

        rectanglePlein(0,0,WIDTH,HEIGHT,1);

        afficherListeEntite(listeMonstres1);
        afficherListeEntite(listeMonstres2);
        afficherListeEntite(listeBoucliers);
        afficherListeEntite(listeMissiles);
        afficherEntite(joueur);
        afficherListeEntite(listeBombes);

        majSurface();

        timer++;
        SDL_Delay(DELAY);
        //printf("%d ",timer);
        fflush(stdout);

    }
    return(1);
}
