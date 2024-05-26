# CY' FEST

Une brève description du projet 

Ce projet consiste en un programme permettant à des organisateurs de festival de pouvoir attribuer des concerts à des salles, créer différentes catégorie et attribuer un nombre de rangées par catégorie et un nombre de sièges par rangées en fonction de ce que desir l'organisateur, attribuer des prix à chaque catégorie il peut aussi ajouter une fosse.
Ce projet permet aussi aux participants de réserver leur place pour chaque concert.

## Comment faire pour que le programme compile et qu'il s'exécute ?

Veuillez d'abord à mettre le dossier "Projet" dans un répertoire que vous pouvez accéder depuis votre terminal. Ensuite, il faut dans votre terminal et dans le bon répertoire contenant le dossier, écrire "make" et appuyer sur "Entrez" une fois cette action exécutée tous les fichiers devrez être compilés et prêt à être exécuter, ainsi il vous suffira d'écrire "./exec" pour pouvoir exécuter le programme. 

## Comment ça fonctionne ?

Nous allons maintenant expliquer le fonctionnement global du programme. Tout d'abord, il est demandé de faire un choix parmi 4 propositions. Vous pouvez en effet accéder au mode manager si vous le souhaitez gérer les différentes scènes ou vous pouvez décider d'accéder au mode festivalier qui permet de voir les différentes salles disponibles et réserver sa place, vous pouvez également retourner au menu et mettre fin au programme. Il suffit de taper le numéro associé à l'action que vous souhaitez réaliser pour pouvoir accéder aux différents modes évidemment tout sera afficher. En cas de mauvaise commande, le choix vous sera redemandé.

### Le mode manager

Si vous décidez d'accéder au mode manager, vous pourrez décider de créer une salle, attribuée un concert à une salle, modifier une salle ou encore modifier un concert. Il est bien sûr possible de retourner au menu.

Si vous le souhaitez, vous pouvez créer une salle à partir de rien en choisissant le nom de la salle, son nombre de rangées, son nombre de rangées par catégorie.
A noter : vous ne pouvez pas créer plus de 9 salles aussi le nombre de rangées et de sièges sont aussi limités au nombre de 9.

Si vous souhaitez modifier un concert, il faudra bien évidemment le faire avant le début de celui-ci ou attendre la fin du concert. Il vous sera demandé quel concert vous souhaitez modifier, si vous voulez ajouter une fosse et il sera possible de changer la date du concert.

Si vous souhaitez modifier une salle, vous pourrez le faire uniquement avant ou après le concert. Les éléments que vous pourrez modifier sont le nombre de rangées, le nombre de rangées par catégorie pour les catégories A et B la catégorie C elle, sera constitué de tous les autres rangées de sièges n'étant pas en catégorie A ou en B, le nombre de sièges par rangées.

Si vous souhaitez attribuer un concert à une salle, vous pourrez attribuer un concert à une salle qui n'est pas déjà prise.

Il vous sera aussi possible en tant que manager de choisir les prix des places en fonction de leur catégorie.

### Le mode festivalier

En tant que festivalier, vous devrez tout d'abord choisir dans quelle salle vous souhaitez réserver. Il sera bien évidemment impossible de réserver si une salle est déjà complète. Ensuite, il vous sera possible de réserver la place de votre choix avant le début du concert. Les différentes places déjà réservées, leur catégorie et leur prix vous seront affichées.


## Ce que l'on a utilisé

**Langage de programmation:** Langage C

**Les differentes bibliothèques utilisées:** stdio.h, string.h, stdlib.h, time.h;

**Référence pour les couleurs:** http://sdz.tdct.org/sdz/des-couleurs-dans-la-console-linux.html


## Référence pour les couleurs

| Color             | Hex                                                                |
| ----------------- | ------------------------------------------------------------------ |
| Vert | ![#00ff00.](https://via.placeholder.com/10/00ff00?text=+) #00ff00 32|
|  Jaune | ![#ffff00](https://via.placeholder.com/10/ffff00?text=+) #ffff00 33|
| Magenta | ![#ff00ff](https://via.placeholder.com/10/ff00ff?text=+) #ff00ff  35|


## Auteurs

- yehouenoum@cy-tech.fr

- abalemarca@cy-tech.fr

- touminorah@cy-tech.fr



