#  S2 UE Informatique - Projet CIR1

Ce projet porte sur l'implémentation d'un outil capable de générer des fichiers HTML sur la généalogie d'individus contenu dans un fichier CSV, a l'aide d'un programme en C.

## Structure du Projet

- `main.c` : Contient le code pour gérer les choix du menu et appeler les fonction adéquat
- `advanced.c` : Contient les principales fonctions d'ancètres et de fratries
- `htmlexport.c` : Contient les différentes fonction pour exporter le html
- `person.c` : Contient les fonctions pour initialiser une personne
- `population.c` : Contient les fonctions pour lire le fichier csv et la population
- `Makefile` : Fichier de configuration pour la compilation du projet.

## Utilisation

1. Aller dans le dossier src `cd src`.
2. Changer les permission du script `chmod +x script.sh`.
3. Compiler et executer le programme en utilisant la commande `./script.sh`.

## Modification de la population

1. Ajouter le fichier CSV de votre population dans le dossier `/ressources`.
2. Aller dans le main `/src/main.c`.
3. Modifier la ligne 8 `char* filename = "../ressources/NOM_DU_FICHIER";`.

## Auteur

- GANGUE Saan Boris
- CORVAISIER Antoine
- CORNIC Maël