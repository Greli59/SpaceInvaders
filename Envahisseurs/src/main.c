#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "Graphique/libgraph.h"
#include "entite.h"
#include "constants.h"


int vie = 3; // Nombre de vies initial du joueur
int cooldownDegats = 0;
int playerTookDamage = 0;


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
    int numLutinJoueurDegat= chargerLutin("../Lutins/invader_canon_ferraille.bmp", 1);


    // Variables pour la gestion du jeu
    int timer = 0;
    int animation = 0;
    int animation_state = 1;
    int dirJoueur = 0;
    int dirMonstres = 1;
    int cooldownTimer = 0;
    evenement evt;
    char touche;
    void *detail;
    int joueurLargeur;
    int joueurHauteur;

    tailleLutin(numLutinJoueur,&joueurLargeur,&joueurHauteur);



    // Initialisation des listes d'entités
    listeEntites listeMissiles = NULL;
    listeEntites listeBombes = NULL;
    listeEntites listeMonstres1 = NULL;
    listeEntites listeMonstres2 = NULL;
    listeEntites listeBoucliers = NULL;

    // Création des entités
    for (int i = 0; i < NB_MONSTRES; ++i) {
        entite monstre1 = {100 + i*50, 100, numLutinMonstre1,0};
        entite monstre2 = {100 + i*50, 200, numLutinMonstre2,0};
        listeMonstres1 = addHead(monstre1, listeMonstres1);
        listeMonstres2 = addHead(monstre2, listeMonstres2);
    }


    for (int i = 0; i < NB_BOUCLIERS; ++i) {
        entite bouclier = {(WIDTH/4 - largeurSprite(numLutinBouclier))/2 + i*(WIDTH/4), HAUTEUR_BOUCLIER, numLutinBouclier,0};
        listeBoucliers = addHead(bouclier, listeBoucliers);
    }


    // Création de l'entité joueur
    entite joueur = {WIDTH/2 - joueurLargeur/2, HAUTEUR_JOUEUR, numLutinJoueur,0};






    char vieString[2];
    vieString[0] = vie + '0';
    vieString[1] = '\0';
    int vieAffichage = lutinTexte(vieString,COULEUR_BLANC);

    int etatBord = 0; // 0 = aucun bord touché, 1 = bord gauche touché, -1 = bord droit touché

    while(1){


        // Lecture de l'appui des touches
        lireEvenement(&evt,&touche,&detail);

        /*
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
        */




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

        moveEntite(&joueur,dirJoueur,0,DELAY_JOUEUR);


        // Missiles lancés par le joueur

        // Pour gérer le temps entre chaque lancé possible de missile par le joueur, je vérifie si mon cooldown est égal à zéro et donc je peux tirer
        // Sinon, je décrémente mon cooldown jusqu’à ce qu'il atteigne ce zéro, cette étape se répète un certain nombre de fois, créant donc un temps d'attente
        //printf("cooldown = %d\n",cooldownTimer);
        if (cooldownTimer != 0){
                cooldownTimer--;
        }

        if (evt == toucheBas && touche == 'z' && cooldownTimer == 0){
            cooldownTimer = MISSILES_COOLDOWN;
            entite missile = {joueur.x+(largeurSprite(numLutinJoueur)/2)-(largeurSprite(numLutinMissile)/2), joueur.y, numLutinMissile,0}; // Le missile apparaît aux centres du joueur, et on doit soustraire sa propre largeur/2 du missile pour bien le centrer
            listeMissiles = addHead(missile, listeMissiles);
        }

        deplacerVertical(&listeMissiles, -1, DELAY_MISSILES);


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

        if (animation % (ANIMATION_TIMER / DELAY) == 0) {

            switch (animation_state){

                case 1:
                    changerLutinListeEntites(listeMonstres1,numLutinMonstre1bis);
                    animation_state = -1;
                    break;
                case -1:
                    changerLutinListeEntites(listeMonstres1,numLutinMonstre1);
                    animation_state = 1;
                    break;

            }

        }



        if (timer % (BOMBS_COOLDOWN / DELAY) == 0) {
            listeEntites pMonstre = listeMonstres2;
            int nombre_monstres = compteMonstres(listeMonstres2);
            if (nombre_monstres != 0){
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
                    lacherBombe(&listeBombes, pMonstre->ent.x + largeurSprite(pMonstre->ent.lutin)/2, pMonstre->ent.y, numLutinBombe);
                    //printf("Bombe lâchée par un monstre !\n");
                }
            }
        }

        deplacerVertical(&listeBombes, 1, DELAY_BOMBES);



        // Déplacement des monstres
        // Détection du bord et changement de direction des monstres
        if (toucheBord(listeMonstres1) || toucheBord(listeMonstres2)) { // Si un bord est touché par un monstre (peut importe lequel)
            if (etatBord == 0) {
                // Aucun bord n'a été touché précédemment


                // A modifier par la suite en ajoutant toutes les listes de monstres
                etatBord = toucheBord(listeMonstres1); // Récupère l'état du bord
                if (etatBord == 0) {
                    etatBord = toucheBord(listeMonstres2); // Vérifie le bord de la deuxième liste si nécessaire
                }


                //on change la direction des monstres
                dirMonstres *= -1; // Inverse la direction des monstres

                // On fait déscendre les monstres
                moveListeEntites(listeMonstres1, 0, DECALAGE_MONSTRES_VERTICAL, -1);
                moveListeEntites(listeMonstres2, 0, DECALAGE_MONSTRES_VERTICAL, -1);
            }
        } else {
            // Aucun bord n'est touché
            etatBord = 0;
        }

        moveListeEntites(listeMonstres1, dirMonstres * DECALAGE_MONSTRES_HORIZONTAL, 0, DELAY_MONSTRES);
        moveListeEntites(listeMonstres2, dirMonstres * DECALAGE_MONSTRES_HORIZONTAL, 0, DELAY_MONSTRES);



        /////////////////////////////////////



        // COLLISION

        /*
        if (collisionEntiteListe(joueur,listeBombes)){
            printf("collision vaisseau/bombes\n");
            joueur.lutin = numLutinJoueurDegat;
        }
        else joueur.lutin = numLutinJoueur;


        if (collisionEntiteListe(joueur,listeMonstres1) || collisionEntiteListe(joueur,listeMonstres2)){
            printf("collision vaisseau/monstres\n");
        }

        if (collisionListeListe(listeMissiles,listeMonstres1) || collisionListeListe(listeMissiles,listeMonstres2)){
            printf("collision missiles/monstres\n");
        }
        */


        //printf("vie = %d\n",vie);

        //printf("PlayerTookDamage = %d\n",playerTookDamage);
        if (playerTookDamage == 1) joueur.lutin = numLutinJoueurDegat;
        else joueur.lutin = numLutinJoueur;

        if (cooldownDegats > 0) {
            cooldownDegats--;
        }

        if (cooldownDegats == 0) playerTookDamage = 0;

        listeEntites pBombe = listeBombes;
        listeEntites precBombe = NULL;

        while (pBombe != NULL) {
            if (collisionEntiteEntite(joueur, pBombe->ent)) {
                if (cooldownDegats == 0) {
                    // Si le joueur peut subir des dégâts (cooldownDegats == 0), décrémente le nombre de vies
                    vie--;
                    playerTookDamage = 1;
                    // Réinitialise le cooldown des dégâts pour définir le temps d'attente entre deux dégâts
                    cooldownDegats = COOLDOWN_DEGATS;
                    // Supprime la bombe

                    char vieString[2];
                    vieString[0] = vie + '0';
                    vieString[1] = '\0';

                    vieAffichage = lutinTexte(vieString,COULEUR_BLANC);

                    supprimeEntite(&listeBombes, &precBombe, &pBombe);


                }
                break;
            }
            // Avance dans la liste des bombes
            precBombe = pBombe;
            pBombe = pBombe->suivant;
        }

        // Vérifie si le joueur a perdu toutes ses vies
        if (vie == 0) {
            printf("Game Over!\n");
            freeListeEntites(listeMissiles);
            freeListeEntites(listeBombes);
            freeListeEntites(listeBoucliers);
            freeListeEntites(listeMonstres1);
            freeListeEntites(listeMonstres2);
            fermerSurface();
            return 0;
        }



        // COLLISION MONSTRE / MISSILE
        // Ne fonctionne pas, si on tire 2 missiles ou plus => core dumped

        listeEntites pMissile = listeMissiles;
        listeEntites precMissile = NULL;
        listeEntites pMonstre = listeMonstres2;
        listeEntites precMonstre = NULL;

        int i = 0;
        while (pMissile != NULL) {
            //printf("i = %d\n",i);
            while (pMonstre != NULL){
                if (collisionEntiteEntite(pMonstre->ent, pMissile->ent)) {
                    printf("Collision %d\n",i);
                    printEntite(pMissile->ent);
                    printEntite(pMonstre->ent);



                    if (precMonstre == NULL) {
                        deleteHead(&listeMonstres2);
                    } else {
                        precMonstre->suivant = pMonstre->suivant;
                        free(pMonstre);
                        pMonstre = precMonstre->suivant;
                    }

                    if (precMissile == NULL) {
                        deleteHead(&listeMissiles);
                    } else {
                        precMissile->suivant = pMissile->suivant;
                        free(pMissile);
                        pMissile = precMissile->suivant;
                    }





                    break;
                }
                precMonstre = pMonstre;
                pMonstre = pMonstre->suivant;
            }
            precMissile = pMissile;
            pMissile = pMissile->suivant;
            i++;


            pMonstre = listeMonstres2;
            precMonstre = NULL;

        }



        // AFFICHAGE //

        rectanglePlein(0,0,WIDTH,HEIGHT,1);

        afficherListeEntite(listeMonstres1);
        afficherListeEntite(listeMonstres2);
        afficherListeEntite(listeBoucliers);
        afficherListeEntite(listeMissiles);
        afficherEntite(joueur);
        afficherListeEntite(listeBombes);
        afficherLutin(vieAffichage,50,50);

        majSurface();

        timer++;
        SDL_Delay(DELAY);
        //printf("%d ",timer);
        //fflush(stdout); // Utilisé pour des printf à la suite sans \n

    }
    return(1);
}


/* Choses à changer:
 * Fusionner la fonction pour deplacer les bombes et les missiles car elles font la même chose
 * Regrouper toute les listes d'entités dans une liste globale
 * si on tire plusieurs missiles on a des core dumped
 */

// Probleme: quand on on déplace le joueur puis on tire en continu, on peut sortir de l'ecran
// Si on reste appuyé sur le tir puis on se déplace, on ne tire plus et on ne sort pas de l'ecran
