# SPACE INVADERS par Lilian Grévin

## Contrôles
- Utilisez **[Q]** pour aller à gauche et **[D]** pour aller à droite.
- Appuyez sur **[Z]** pour tirer.

## Modifications apportées sur les sprites
- Les sprites fournis ont été modifiés pour inclure des animations sur chaque type de monstre.
- Suppression des sprites non utilisés.

## Fonctionnalités
- Menu de démarrage, écran de fin (Victoire/Défaite).
- La vie du joueur est affichée en haut à gauche.
- Le joueur peut tuer les monstres en leur tirant dessus, mais il peut aussi neutraliser leurs bombes.
- Pas de Warning avec clang-tidy :)

## Problèmes Connus
- **Déplacements** : Les déplacements du joueur se passent sans problème tant que le joueur n'essaie pas de se déplacer et de tirer simultanément dans un certain ordre. Dans ce cas, il est possible de sortir de l'écran.
- **Boucliers** : Les boucliers sont affichés à l'écran mais n'ont pas de fonctionnalité active dans le jeu :/
- **Lâcher de bombes** : La gestion du lâcher de bombes permet uniquement aux monstres de la ligne la plus basse, encore en vie, de tirer. Cela signifie que si un seul monstre reste dans la ligne du bas, les monstres du dessus ne tireront pas, ce qui les rend vulnérables. Cette situation peut être exploitée par le joueur et n'est pas idéale pour l'expérience de jeu.

## Problèmes de mémoire avec Valgrind
Valgrind signale des problèmes d'allocation de mémoire, en particulier dans libgraph.c. Bien que tous les malloc aient été libérés, ces erreurs persistent :(
