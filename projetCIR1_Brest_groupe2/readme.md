BURLOT Owen
SAVARY Coraline
PIAT Maelenn

# Réalisation d'un outil capable de générer un ensemble de fichiers HTML à partir de données formatées dans un fichier texte

## Structure du Projet

- `main.c` : Contient la fonction principale du programme.
- `population.c` : Contient les définitions des fonctions pour stocker la population dans une table de hachage.
- `person.c` : Contient les définitions des fonctions d'une personne (trouver fratrie, trouver une personne, ...).
- `person.h` : Contient les déclarations des fonctions des fichiers `person.c` et `population.c` et des structures de données nécessaires.
- `menu.c` : Contient les définitions des fonctions du menu.
- `menu.h` : Contient les déclarations des fonctions du menu.
- `htmlexport.c` : Contient les définitions des fonctions liées au html.
- `htmlexport.h` : Contient les déclarations des fonctions liées au html.
- `filemanager.c` : Contient la définition de la fonction pour lire le CSV.
- `filemanager.h` : Contient la déclaration de la fonction pour lire le CSV.
- `makefile` : Fichier de configuration pour la compilation du projet.
- `200.csv` : Fichier contenant toutes les données de la population cas 200 personnes.
- `10000.csv` : Fichier contenant toutes les données de la population cas 10 000 personnes.
- `arbre.css` : Fichier qui gère la mise en forme de la page web.
- `fond_page_html.png` : Image de fond pour le site de html.
- `profil.png` : Image de profil pour le site de html.
- `profil_vide.png` : Image de profil en point d'interrogation pour les inconnus sur le site de html.


## Utilisation

1. Compilez le programme en utilisant la commande `make`.
2. Exécutez le programme en utilisant la commande `./main`.
3. Parcourez le menu afin de trouver l'utilisation chercher en fonction de vos besoin.
4. Les fichiers HTML généré sont dans le dossier `export/`, écrit sous la forme : `id-info/arbre/fratrie.html` en fonction des besoins demandez précedement.
5. Pour supprimer tous les fichiers html, les .o et l'exécutable, il faut utiliser la commande `make clean`.

## Modifications

1. Modifiez la constante 'TABLE_SIZE' dans le fichier `person.h` pour correspondre à la taille voulue du fichier.
2. Modifiez la ligne 10 : `lireCSV(&pl,"resources/10000.csv");` du fichier : `main.c`, pour correspondre au fichier de donné voulu. 

## Réalisation
- Visual Studio Code