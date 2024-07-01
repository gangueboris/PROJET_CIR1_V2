# S2 UE Informatique - Projet CIR1

### Présentation du projet
1. Objectifs
Le projet porte sur l'implémentation d'un outil capable de générer des fichier HTML à partir de certains informations formatés dans un fichier CSV.

**Contenu du fichier csv**
```
0,0,0,-,-,-,-
1,2,3,Hatton,Andrew,9/2/1801,Yorkshire 
2,0,0,Hatton,Steve,25/7/1775,Yorkshire 
3,0,0,Vockins,Mary,11/10/1777,West Yorkshire
```
2. Contraintes et exigences
- L'outil de génération doit être codé en langage C .
- L'ensemble des fichiers généré dois être statique.
- Obligation d'implémenter les fonctions fratrie et ancestors.
- Un fichier par personne; nom des fichiers html: [id_person]-fiche.html

3. Architecture du projet
![architecture](utils/img/architecture.png)

- Le noyau : Un programme C qui génère automatiquement un site 
- Les scripts : Un ensemble de scripts LINUX permettant d’utiliser simplement le noyau C 
- La sortie : Un ensemble de fichiers permettant d’afficher les résultats sous forme de site

**Architecture de sortie**
![architecture de sortie](utils/img/structure_sortie.png)

### Organisation du projet
```
projet_genealogie
├─ :open_file_folder: export               // Dossier contenant la sortie
|  └─ :page_facing_up: .html 
├─ :open_file_folder: ressources           // Dossier contenant les .csv
├─ :open_file_folder: scripts              // Dossier script linux
├─ :open_file_folder: others 
|  └─ .css
└─ :open_file_folder: src                  // Noyau du projet
    │  ├─ :page_facing_up: person.h
    │  ├─ :page_facing_up: person.c
    │  ├─ :page_facing_up: population.h
    │  ├─ :page_facing_up: population.c
    │  ├─ :page_facing_up: filemanager.h
    │  ├─ :page_facing_up: filemanager.c
    │  ├─ :page_facing_up: advanced.h
    │  ├─ :page_facing_up: advanced.c
    │  ├─ :page_facing_up: htmlexport.h
    │  ├─ :page_facing_up: htmlexport.c
    │  ├─ :page_facing_up: makefile
    │  └─ :open_file_folder: output
    └─ :page_facing_up: REAME.md
```


## Compilation et excécution du programme
1. Se rendre dans le dossier scripts
2. Modifier la permission sur le **script**  `chmod +x script.sh`
3. Compiler et executer le programme en utilisant la commande `./script.sh`.


## Modification de la population

1. Ajout d'un fichier ***csv** d'une population dans`/ressources`.
2. Se rendre dans le fichier **main.c** `/src/main.c`.
3. Modifier la ligne 89 `char* filename = "../ressources/NOM_DU_FICHIER";`.

## Membre de l'équipe:

- GANGUE Saan Boris
- CORVAISIER Antoine
- CORNIC Maël