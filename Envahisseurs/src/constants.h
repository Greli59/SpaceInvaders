#ifndef CONSTANTS_H
#define CONSTANTS_H

#define HEIGHT 648
#define WIDTH 864
#define DELAY 1 //ms
#define TAILLE_POLICE 50
#define NB_MONSTRES 11 // Nombre de monstres présents par ligne
#define ECART_HORIZONTAL_MONSTRE 50 // Écart horizontal entre chaque monstre
#define ECART_VERTICAL_MONSTRE 50 // Écart entre chaque ligne de monstre (il faut considérer la hauteur des sprites !)
#define HAUTEUR_MONSTRES 25
#define NB_BOUCLIERS 4
#define HAUTEUR_BOUCLIER 500
#define HAUTEUR_JOUEUR 600
#define MISSILES_COOLDOWN 150 // Temps d'attente entre 2 tirs de missiles
#define BOMBS_COOLDOWN 350 // Temps d'attente entre 2 lâchers de bombes
#define ANIMATION_TIMER 250 // Temps entre les changements de sprites pour les animations
#define DECALAGE_MONSTRES_VERTICAL 50 // Distance en pixel parcourut entre chaque "saut" verticaux
#define DECALAGE_MONSTRES_HORIZONTAL 25 // Pareil mais horizontalement
#define DELAY_JOUEUR 0 // Combien d'image doit-on attendre avant de pouvoir déplacer le joueur, ici 0 = vitesse max
#define DELAY_MONSTRES 500 // Les monstres se déplacent toutes les 500 images
#define DELAY_MISSILES 1
#define DELAY_BOMBES 3
#define COOLDOWN_DEGATS 500 // Temps d'immortalité du joueur pour éviter de nourrir trop facilement
#define TEMPS_ECRAN_VICTOIRE_DEFAITE 2500
#define BOUILLIE_TEMPS_DE_VIE 50
#define VIE_JOUEUR 3 // Vie du joueur
#define ECART_VIE_JOUEUR 50 // Ecart en pixel entre les icones de vie
#define ECART_BORD_VIE_JOUEUR 15 // Écart en pixel entre les icônes de vie

#endif
