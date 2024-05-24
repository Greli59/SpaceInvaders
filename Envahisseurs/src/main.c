#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "Graphique/libgraph.h"
#include "entite.h"
#include "constants.h"

                            /* PROTOTYPES */

void deplacementJoueur(evenement evt, char touche, entite *joueur, int *dirJoueur, int joueurLargeur);

void printEvenement(evenement evt, char touche);

void libererJeu(listeEntites listeMissiles,
                listeEntites listeBombes,
                listeEntites listeMonstres1,
                listeEntites listeMonstres2,
                listeEntites listeMonstres3,
                listeEntites listeMonstres4,
                listeEntites listeBoucliers,
                listeEntites listeBouillie,
                listeEntites listeVieJoueur);

void afficherMenuDemarrage();

void gererTirsMissiles(entite *joueur, listeEntites *listeMissiles, int numLutinJoueur, int numLutinMissile, int *cooldownTimer, evenement evt, char touche);

void gererAnimationMonstres(listeEntites *listeMonstres1,
                            listeEntites *listeMonstres2,
                            listeEntites *listeMonstres3,
                            listeEntites *listeMonstres4,
                            int numLutinMonstre1, int numLutinMonstre1bis,
                            int numLutinMonstre2, int numLutinMonstre2bis,
                            int numLutinMonstre3, int numLutinMonstre3bis,
                            int *animation_state, int * animation);

void gererLancerBombesMonstres(listeEntites *listeMonstres1,
                               listeEntites *listeMonstres2,
                               listeEntites *listeMonstres3,
                               listeEntites *listeMonstres4,
                               listeEntites *listeBombes,
                               int numLutinBombe,
                               const int *timer);

void deplacerMonstres(listeEntites *listeMonstres1, listeEntites *listeMonstres2, listeEntites *listeMonstres3, listeEntites *listeMonstres4, int *dirMonstres, int *etatBord);

void gestionDegatsJoueur(listeEntites *listeBombes,
                         entite *joueur,
                         int *vie,
                         int *playerTookDamage,
                         int *cooldownDegats,
                         int numLutinJoueurDegat,
                         int numLutinJoueur,
                         listeEntites *listeVieJoueur);






// Fonction pour générer un nombre aléatoire entre min et max
int randInRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}


// Variables pour la gestion du jeu

int vie = VIE_JOUEUR; // Nombre de vies initial du joueur
int cooldownDegats = 0;
int playerTookDamage = 0;
int timer = 0;
int animation = 0;
int animation_state = 1;
int dirJoueur = 0;
int dirMonstres = 1;
int cooldownTimer = 0;
evenement evt;
char touche;
void *detail;

// Variable utilisée pour le changement de direction des monstres
int etatBord = 0; // 0 = aucun bord touché, 1 = bord gauche touché, -1 = bord droit touché


int main(){

    srand(time(NULL)); // Initialisation du temps pour la gestion du hasard
    creerSurface(WIDTH,HEIGHT,"test"); // Création de la surface
    choisirPolice("../Lutins/INVASION2000.TTF", TAILLE_POLICE);


    // Chargement des lutins

    const int numLutinMissile = chargerLutin("../Lutins/invader_missile.bmp", COULEUR_NOIR);
    const int numLutinBombe = chargerLutin("../Lutins/invader_bombe.bmp", COULEUR_NOIR);

    const int numLutinMonstre1 = chargerLutin("../Lutins/invader_monstre2_1.bmp", COULEUR_NOIR);
    const int numLutinMonstre1bis = chargerLutin("../Lutins/invader_monstre2_2.bmp", COULEUR_NOIR);

    const int numLutinMonstre2 = chargerLutin("../Lutins/invader_monstre1_1.bmp", COULEUR_NOIR);
    const int numLutinMonstre2bis = chargerLutin("../Lutins/invader_monstre1_2.bmp", COULEUR_NOIR);

    const int numLutinMonstre3 = chargerLutin("../Lutins/invader_monstre3_1.bmp", COULEUR_NOIR);
    const int numLutinMonstre3bis = chargerLutin("../Lutins/invader_monstre3_2.bmp", COULEUR_NOIR);

    const int numLutinBouclier = chargerLutin("../Lutins/invader_bouclier.bmp", COULEUR_NOIR);
    const int numLutinJoueur = chargerLutin("../Lutins/invader_canon.bmp", COULEUR_NOIR);
    const int numLutinJoueurDegat= chargerLutin("../Lutins/invader_canon_ferraille.bmp", COULEUR_NOIR);

    const int lutinVictoire = lutinTexte("You WIN !",COULEUR_BLANC);
    const int lutinDefaite = lutinTexte("GAME OVER",COULEUR_BLANC);

    const int numLutinBouillie = chargerLutin("../Lutins/invader_monstre_bouillie.bmp", COULEUR_NOIR);



    // Taille du joueur très utilisée dans le code
    int joueurLargeur;
    int joueurHauteur;
    tailleLutin(numLutinJoueur,&joueurLargeur,&joueurHauteur);



    // Initialisation des listes d'entités
    listeEntites listeMissiles = NULL;
    listeEntites listeBombes = NULL;
    listeEntites listeMonstres1 = NULL;
    listeEntites listeMonstres2 = NULL;
    listeEntites listeMonstres3 = NULL;
    listeEntites listeMonstres4 = NULL;
    listeEntites listeBoucliers = NULL;
    listeEntites listeBouillie = NULL;
    listeEntites listeVieJoueur = NULL;

    // Création des entités
    int x_origin_monstre = (WIDTH - (NB_MONSTRES-1)*ECART_HORIZONTAL_MONSTRE - largeurSprite(numLutinMonstre1))/2; // Hyp : Tous les monstres font la même taille
    for (int i = 0; i < NB_MONSTRES; ++i) {
        entite monstre1 = {x_origin_monstre + i*ECART_HORIZONTAL_MONSTRE, HAUTEUR_MONSTRES + ECART_VERTICAL_MONSTRE, numLutinMonstre2,0};
        entite monstre2 = {x_origin_monstre + i*ECART_HORIZONTAL_MONSTRE, HAUTEUR_MONSTRES + ECART_VERTICAL_MONSTRE*2, numLutinMonstre1,0};
        entite monstre3 = {x_origin_monstre + i*ECART_HORIZONTAL_MONSTRE, HAUTEUR_MONSTRES + ECART_VERTICAL_MONSTRE*3, numLutinMonstre1,0};
        entite monstre4 = {x_origin_monstre + i*ECART_HORIZONTAL_MONSTRE, HAUTEUR_MONSTRES + ECART_VERTICAL_MONSTRE*4, numLutinMonstre3,0};

        listeMonstres1 = addHead(monstre1, listeMonstres1);
        listeMonstres2 = addHead(monstre2, listeMonstres2);
        listeMonstres3 = addHead(monstre3, listeMonstres3);
        listeMonstres4 = addHead(monstre4, listeMonstres4);
    }

    for (int i = 0; i < NB_BOUCLIERS; ++i) {
        entite bouclier = {(WIDTH/4 - largeurSprite(numLutinBouclier))/2 + i*(WIDTH/4), HAUTEUR_BOUCLIER, numLutinBouclier,0};
        listeBoucliers = addHead(bouclier, listeBoucliers);
    }

    for (int i = 0; i < VIE_JOUEUR; ++i) {
        entite vieJoueur = {ECART_BORD_VIE_JOUEUR + i*ECART_VIE_JOUEUR, ECART_BORD_VIE_JOUEUR, numLutinJoueur,0};
        listeVieJoueur = addHead(vieJoueur, listeVieJoueur);
    }

    // Création de l'entité joueur
    entite joueur = {WIDTH/2 - joueurLargeur/2, HAUTEUR_JOUEUR, numLutinJoueur,0};


    afficherMenuDemarrage(); // Affiche un menu demandant au joueur d'appuyer sur une touche



    // Boucle principale
    while(1){

        // Lecture de l'appui des touches
        lireEvenement(&evt,&touche,&detail);
        //printEvenement(evt,touche); // Pour débugger

        // Déplacement du joueur
        deplacementJoueur(evt, touche, &joueur, &dirJoueur, joueurLargeur);
        moveEntite(&joueur,dirJoueur,0,DELAY_JOUEUR);


        // Missiles lancés par le joueur
        // Pour gérer le temps entre chaque lancé possible de missile par le joueur, je vérifie si mon cooldown est égal à zéro et donc je peux tirer
        // Sinon, je décrémente mon cooldown jusqu’à ce qu'il atteigne ce zéro, cette étape se répète un certain nombre de fois, créant donc un temps d'attente
        gererTirsMissiles(&joueur, &listeMissiles, numLutinJoueur, numLutinMissile, &cooldownTimer, evt, touche);


        // Quitter le jeu
        if (evt == quitter){
            // On libère la mémoire
            libererJeu(listeMissiles,listeBombes,listeMonstres1,listeMonstres2,listeMonstres3,listeMonstres4,listeBoucliers,listeBouillie,listeVieJoueur);
            return(1);
        }

        gererAnimationMonstres(
            &listeMonstres1, &listeMonstres2, &listeMonstres3, &listeMonstres4,
            numLutinMonstre1, numLutinMonstre1bis,
            numLutinMonstre2, numLutinMonstre2bis,
            numLutinMonstre3, numLutinMonstre3bis,
            &animation_state, &animation);



        gererLancerBombesMonstres(&listeMonstres1,
                                  &listeMonstres2,
                                  &listeMonstres3,
                                  &listeMonstres4,
                                  &listeBombes,
                                  numLutinBombe,
                                  &timer);



        // Déplacement des monstres
        deplacerMonstres(&listeMonstres1, &listeMonstres2, &listeMonstres3, &listeMonstres4, &dirMonstres, &etatBord);


        // Collisions Joueur / Bombes
        gestionDegatsJoueur(&listeBombes, &joueur, &vie, &playerTookDamage, &cooldownDegats, numLutinJoueurDegat, numLutinJoueur, &listeVieJoueur);


        // Vérifie si le joueur a perdu toutes ses vies ou si un monstre touche le bas de l'écran
        if (vie == 0
            || monstreToucheBasEcran(listeMonstres1)
            || monstreToucheBasEcran(listeMonstres2)
            || monstreToucheBasEcran(listeMonstres3)
            || monstreToucheBasEcran(listeMonstres4)) {

            // printf("Game Over!\n");
            rectanglePlein(0,0,WIDTH,HEIGHT,1);
            int largeurTexte;
            int hauteurTexte;
            tailleLutin(lutinDefaite, &largeurTexte, &hauteurTexte);
            afficherLutin(lutinDefaite, WIDTH/2 - largeurTexte/2, HEIGHT/2 - hauteurTexte/2);
            majSurface();
            SDL_Delay(TEMPS_ECRAN_VICTOIRE_DEFAITE);
            libererJeu(listeMissiles,listeBombes,listeMonstres1,listeMonstres2,listeMonstres3,listeMonstres4,listeBoucliers,listeBouillie,listeVieJoueur);
            return 0;
        }


        // Vérifie si tous les monstres sont morts
        if (listeMonstres1 == NULL && listeMonstres2 == NULL && listeMonstres3 == NULL && listeMonstres4 == NULL){

            // printf("You win!\n");
            rectanglePlein(0,0,WIDTH,HEIGHT,1);
            int largeurTexte;
            int hauteurTexte;
            tailleLutin(lutinVictoire, &largeurTexte, &hauteurTexte);
            afficherLutin(lutinVictoire, WIDTH/2 - largeurTexte/2, HEIGHT/2 - hauteurTexte/2);
            majSurface();
            SDL_Delay(TEMPS_ECRAN_VICTOIRE_DEFAITE);
            libererJeu(listeMissiles,listeBombes,listeMonstres1,listeMonstres2,listeMonstres3,listeMonstres4,listeBoucliers,listeBouillie,listeVieJoueur);
            return 0;
        }


        // Collisions Missiles / Monstres et Bombes
        collisionListeListeDestructive(&listeMissiles, &listeMonstres1, &listeBouillie, numLutinBouillie);
        collisionListeListeDestructive(&listeMissiles, &listeMonstres2, &listeBouillie, numLutinBouillie);
        collisionListeListeDestructive(&listeMissiles, &listeMonstres3, &listeBouillie, numLutinBouillie);
        collisionListeListeDestructive(&listeMissiles, &listeMonstres4, &listeBouillie, numLutinBouillie);
        collisionListeListeDestructive(&listeMissiles, &listeBombes, &listeBouillie, numLutinBouillie);


        gererBouillie(&listeBouillie);


        // AFFICHAGE //
        rectanglePlein(0,0,WIDTH,HEIGHT,1);
        afficherListeEntite(listeMonstres1);
        afficherListeEntite(listeMonstres2);
        afficherListeEntite(listeMonstres3);
        afficherListeEntite(listeMonstres4);
        afficherListeEntite(listeBoucliers);
        afficherListeEntite(listeMissiles);
        afficherListeEntite(listeBouillie);
        afficherListeEntite(listeVieJoueur);
        afficherEntite(joueur);
        afficherListeEntite(listeBombes);

        majSurface();

        timer++;
        SDL_Delay(DELAY);
        //printf("%d ",timer);
        //fflush(stdout); // Utilisé pour des printf à la suite sans \n




    }
    return(1);
}






void deplacementJoueur(evenement evt, char touche, entite *joueur, int *dirJoueur, int joueurLargeur) {
    if (evt == toucheBas && touche == 'q' && joueur->x > 0) {
        *dirJoueur = -1;
    } else if (evt == toucheBas && touche == 'q' && joueur->x < 0) {
        *dirJoueur = 0;
    } else if (evt == toucheBas && touche == 'd' && joueur->x < WIDTH - joueurLargeur) {
        *dirJoueur = 1;
    } else if (evt == toucheBas && touche == 'd' && joueur->x > WIDTH - joueurLargeur) {
        *dirJoueur = 0;
    } else if ((evt == toucheHaut && touche == 'q') || (evt == toucheHaut && touche == 'd')) {
        *dirJoueur = 0;
    }
}





// Test pour connaître les appuis de touches
void printEvenement(evenement evt, char touche){
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
}




// Libère la mémoire
void libererJeu(listeEntites listeMissiles,
                listeEntites listeBombes,
                listeEntites listeMonstres1,
                listeEntites listeMonstres2,
                listeEntites listeMonstres3,
                listeEntites listeMonstres4,
                listeEntites listeBoucliers,
                listeEntites listeBouillie,
                listeEntites listeVieJoueur)
{
    freeListeEntites(listeMissiles);
    freeListeEntites(listeBombes);
    freeListeEntites(listeMonstres1);
    freeListeEntites(listeMonstres2);
    freeListeEntites(listeMonstres3);
    freeListeEntites(listeMonstres4);
    freeListeEntites(listeBoucliers);
    freeListeEntites(listeBouillie);
    freeListeEntites(listeVieJoueur);


    fermerSurface();
}





void afficherMenuDemarrage() {
    rectanglePlein(0, 0, WIDTH, HEIGHT, COULEUR_NOIR); // Ecran noir
    int startMenu = lutinTexte("Press any key to start", COULEUR_BLANC);
    int largeurTexte;
    int hauteurTexte;
    tailleLutin(startMenu, &largeurTexte, &hauteurTexte);
    afficherLutin(startMenu, WIDTH / 2 - largeurTexte / 2, HEIGHT / 2 - hauteurTexte / 2); // Affiche le texte au centre de la surface
    majSurface();

    // Lire les événements jusqu'à ce qu'une touche soit pressée
    evenement evt;
    char touche ;
    void *detail;
    do {
        lireEvenement(&evt, &touche, &detail);
    } while (evt != toucheBas);
}





void gererTirsMissiles(entite *joueur, listeEntites *listeMissiles, int numLutinJoueur, int numLutinMissile, int *cooldownTimer, evenement evt, char touche) {
    //printf("cooldown = %d\n",cooldownTimer);
    if (*cooldownTimer != 0) {
        (*cooldownTimer)--;
    }

    if (evt == toucheBas && touche == 'z' && *cooldownTimer == 0) {
        *cooldownTimer = MISSILES_COOLDOWN;
        entite missile = {joueur->x + (largeurSprite(numLutinJoueur) / 2) - (largeurSprite(numLutinMissile) / 2), joueur->y, numLutinMissile, 0};
        // Le missile apparaît au centre du joueur, et on doit soustraire sa propre largeur/2 du missile pour bien le centrer
        *listeMissiles = addHead(missile, *listeMissiles);
    }

    deplacerVertical(listeMissiles, -1, DELAY_MISSILES);
}




void gererAnimationMonstres(listeEntites *listeMonstres1, listeEntites *listeMonstres2, listeEntites *listeMonstres3, listeEntites *listeMonstres4, int numLutinMonstre1, int numLutinMonstre1bis, int numLutinMonstre2, int numLutinMonstre2bis, int numLutinMonstre3, int numLutinMonstre3bis, int *animation_state, int *animation) {
    (*animation)++;
    if (*animation % (ANIMATION_TIMER / DELAY) == 0) {
        switch (*animation_state) {
            case 1:
                changerLutinListeEntites(*listeMonstres1, numLutinMonstre2bis);
                changerLutinListeEntites(*listeMonstres2, numLutinMonstre1bis);
                changerLutinListeEntites(*listeMonstres3, numLutinMonstre1bis);
                changerLutinListeEntites(*listeMonstres4, numLutinMonstre3bis);
                *animation_state = -1;
                break;
            case -1:
                changerLutinListeEntites(*listeMonstres1, numLutinMonstre2);
                changerLutinListeEntites(*listeMonstres2, numLutinMonstre1);
                changerLutinListeEntites(*listeMonstres3, numLutinMonstre1);
                changerLutinListeEntites(*listeMonstres4, numLutinMonstre3);
                *animation_state = 1;
                break;
        }
    }
}




void gererLancerBombesMonstres(listeEntites *listeMonstres1,
                               listeEntites *listeMonstres2,
                               listeEntites *listeMonstres3,
                               listeEntites *listeMonstres4,
                               listeEntites *listeBombes,
                               int numLutinBombe,
                               const int *timer) {

    if (*timer % (BOMBS_COOLDOWN / DELAY) == 0) {


        listeEntites listesMonstres[] = {*listeMonstres4, *listeMonstres3, *listeMonstres2, *listeMonstres1};
        listeEntites pMonstre = NULL;

        // Trouver la première liste non vide
        for (int i = 0; i < 4; i++) {
            if (listesMonstres[i] != NULL) {
                pMonstre = listesMonstres[i];
                break;
            }
        }


        int nombre_monstres = compteMonstres(pMonstre);
        if (nombre_monstres != 0) {
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
                lacherBombe(listeBombes, pMonstre->ent.x + largeurSprite(pMonstre->ent.lutin)/2, pMonstre->ent.y, numLutinBombe);
            }
        }
    }

    deplacerVertical(listeBombes, 1, DELAY_BOMBES);
}




void deplacerMonstres(listeEntites *listeMonstres1, listeEntites *listeMonstres2, listeEntites *listeMonstres3, listeEntites *listeMonstres4, int *dirMonstres, int *etatBord) {
    // Détection du bord et changement de direction des monstres
    if (toucheBord(*listeMonstres1)
        || toucheBord(*listeMonstres2)
        || toucheBord(*listeMonstres3)
        || toucheBord(*listeMonstres4)) { // Si un bord est touché par un monstre (peu importe lequel)
        if (*etatBord == 0) {// Aucun bord n'a été touché précédemment
            *etatBord = toucheBord(*listeMonstres1); // Récupère l'état du bord
            if (*etatBord == 0) {
                *etatBord = toucheBord(*listeMonstres2); // Vérifie le bord de la ieme liste si nécessaire
            }
            if (*etatBord == 0) {
                *etatBord = toucheBord(*listeMonstres3);
            }
            if (*etatBord == 0) {
                *etatBord = toucheBord(*listeMonstres4);
            }

            *dirMonstres *= -1; // Inverse la direction des monstres

            // On fait descendre les monstres
            moveListeEntites(*listeMonstres1, 0, DECALAGE_MONSTRES_VERTICAL, -1);
            moveListeEntites(*listeMonstres2, 0, DECALAGE_MONSTRES_VERTICAL, -1);
            moveListeEntites(*listeMonstres3, 0, DECALAGE_MONSTRES_VERTICAL, -1);
            moveListeEntites(*listeMonstres4, 0, DECALAGE_MONSTRES_VERTICAL, -1);
        }
    } else {
        // Aucun bord n'est touché
        *etatBord = 0;
    }

    // On déplace les monstres horizontalement
    moveListeEntites(*listeMonstres1, *dirMonstres * DECALAGE_MONSTRES_HORIZONTAL, 0, DELAY_MONSTRES);
    moveListeEntites(*listeMonstres2, *dirMonstres * DECALAGE_MONSTRES_HORIZONTAL, 0, DELAY_MONSTRES);
    moveListeEntites(*listeMonstres3, *dirMonstres * DECALAGE_MONSTRES_HORIZONTAL, 0, DELAY_MONSTRES);
    moveListeEntites(*listeMonstres4, *dirMonstres * DECALAGE_MONSTRES_HORIZONTAL, 0, DELAY_MONSTRES);
}

void gestionDegatsJoueur(listeEntites *listeBombes,
                         entite *joueur,
                         int *vie,
                         int *playerTookDamage,
                         int *cooldownDegats,
                         int numLutinJoueurDegat,
                         int numLutinJoueur,
                         listeEntites *listeVieJoueur) {

    // Changement du sprite du joueur quand il prend un dégat
    if (*playerTookDamage == 1) {joueur->lutin = numLutinJoueurDegat;}
    else {joueur->lutin = numLutinJoueur;}

    if (*cooldownDegats > 0) {(*cooldownDegats)--;}
    if (*cooldownDegats == 0) {(*playerTookDamage) = 0;}

    listeEntites pBombe = *listeBombes;
    listeEntites precBombe = NULL;

    while (pBombe != NULL) {
        if (collisionEntiteEntite(*joueur, pBombe->ent)) {
            if (*cooldownDegats == 0) {
                // Si le joueur peut subir des dégâts (cooldownDegats == 0), décrémente le nombre de vies
                (*vie)--;
                (*playerTookDamage) = 1;
                // Réinitialise le cooldown des dégâts pour définir le temps d'attente entre deux dégâts
                (*cooldownDegats) = COOLDOWN_DEGATS;
                // Supprime la bombe
                supprimeEntite(listeBombes, &precBombe, &pBombe);
                // On enlève une vie de l'affichage
                deleteHead(listeVieJoueur);
            }
            break;
        }
        // Avance dans la liste des bombes
        precBombe = pBombe;
        pBombe = pBombe->suivant;
    }
}


// Probleme: quand on on déplace le joueur puis on tire en continu, on peut sortir de l'ecran
// Si on reste appuyé sur le tir puis on se déplace, on ne tire plus et on ne sort pas de l'ecran
