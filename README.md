
            ////////////////////////////////////
            / SPACE INVADERS par Lilian Grévin /
            ////////////////////////////////////



Déplacements : Utilisez [Q] pour aller à gauche et [D] pour aller à droite.
Appuyez sur [Z] pour tirer.



Modifications apportées sur les sprites:
    - Les sprites fournis ont été modifiés pour inclure des animations sur chaque type de monstre.
    - Suppression des sprites non utilisés



Fonctionnalités :
    - Menu de démarrage, écran de fin (Victoire/Défaite)
    - La vie du joueur est affichée en haut à gauche.
    - Le joueur peut tuer les monstres en leur tirant dessus, mais il peut aussi neutraliser leurs bombes.



Problèmes Connus :
    - Déplacements : Les déplacements du joueur se passent sans problème tant que le joueur n'essaie pas de se déplacer et de tirer simultanément dans un certain ordre. Dans ce cas, il est possible de sortir de l'écran.
    - Boucliers : Les boucliers sont affichés à l'écran mais n'ont pas de fonctionnalité active dans le jeu :/
    - Lâcher de bombes : La gestion du lâcher de bombes permet uniquement aux monstres de la ligne la plus basse, encore en vie, de tirer. Cela signifie que si un seul monstre reste dans la ligne du bas, les monstres du dessus ne tireront pas, ce qui les rend vulnérables. Cette situation peut être exploitée par le joueur et n'est pas idéale pour l'expérience de jeu.



Problèmes de mémoire avec Valgrind :

Valgrind signale des problèmes d'allocation de mémoire, en particulier dans libgraph.c. Bien que tous les malloc aient été libérés, ces erreurs persistent :(

Voici un exemple de rapport Valgrind :
==49583== 31,136 (30,992 direct, 144 indirect) bytes in 1 blocks are definitely lost in loss record 197 of 198
==49583==    at 0x48455EF: calloc (vg_replace_malloc.c:1328)
==49583==    by 0x49151A9: TTF_OpenFontIndexRW (in /usr/lib/x86_64-linux-gnu/libSDL_ttf-2.0.so.0.10.1)
==49583==    by 0x10B13F: choisirPolice (in /home/l/g/lgrevin/TPI/SpaceInvaders/Envahisseurs/src/project)
==49583==    by 0x10B166: initialiserTexte (in /home/l/g/lgrevin/TPI/SpaceInvaders/Envahisseurs/src/project)
==49583==    by 0x10B1C0: creerSurface (in /home/l/g/lgrevin/TPI/SpaceInvaders/Envahisseurs/src/project)
==49583==    by 0x109DC8: main (main.c:90)
