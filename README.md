# Projet Tempest M1

## Compilation

Nous avons utilisé CMake pour configurer et compilé ce projet.
Afin d'avoir le fichier exécutable "Tempest" entre les commande suivant à la racine de ce projet.

- mkdir build
- cd build
- cmake -S ../ -B ./
- cmake --build ./

## Execution

Il suffit maintenant d'exectuer le fichier généré pour commencer à jouer :
- ./Tempest

## Comment jouer ?

Il est possible de navigué dans l'écran du choix de niveau à la fois au clavier; à l'aide des touche 'Q' et 'D' et des flèches gauche et droite ; mais aussi à l'aide de la souris. Pour sélectionner le niveau cliqué à la souris ou presser sur la touche 'Espace' ou 'Entrée'.
Une fois dans le niveau, déplacer le joueur (en Jaune) à l'aide des même touche que dans le menu. Tirer des missiles à l'aide de la touche 'Espace' uniquement.

Plusieurs types d'ennemie sont présents dans le jeu :
- les 'Carrés' violet inoffensif se déplace uniquement de droite à gauche. Score : 5 points.
- les 'Flippers' rouge, imprédictible, ils se déplacent de manière aléatoire de droite à gauche et sont ainsi difficiles à touché. Score : 20 points.
- les 'Spikers' vert, facile à éliminer, ils restent toujours dans la même ligne. Lorsqu'ils sont détruits ou atteignent la fin, il se divise en deux spikers (un dans chaque ligne adjacente). Score : 25 points.

Bon jeu !
by Ludocvi Paillat et Florent Lecoultre
