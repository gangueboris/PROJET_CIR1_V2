## ETUDE PRELEMINAIRE

### Présentation du projet
1. Objectifs
Le projet porte sur l'implémentation d'un outil capable de générer des fichier HTML à partir de certains informations formatés dans un fichier CSV.

2. Contraintes et exigences
- L'outil de génération doit être codé en langage C .
- L'ensemble des fichiers généré dois être statique.
- Obligation d'implémenter les fonctions fratrie et ancestors.
- nom des fichiers html: [id_person]-fiche.html

3. Architecture du projet
- Le noyau : Un programme C qui génère automatiquement un site 
- Les scripts : Un ensemble de scripts LINUX permettant d’utiliser simplement le noyau C 
- La sortie : Un ensemble de fichiers permettant d’afficher les résultats sous forme de site

![architecture](imgs\architecture.png)

### Organisation du projet
```
projet_genealogie
├─ export      (dossier contenant la sortie)
|    └─ .html
├─ ressources  (dossier contenant les .csv)
├─ scripts     (dossier script linux)
├─ others
|    └─ .css
└─   src       (noyau du projet)
    │  ├─ person.h
    │  ├─ person.c
    │  ├─ population.h
    │  ├─ population.c
    │  ├─ filemanager.h
    │  ├─ filemanager.c
    │  ├─ advanced.h
    │  ├─ advanced.c
    │  ├─ htmlexport.h
    │  ├─ htmlexport.c
    │  ├─ README.md
    │  └─  makefile
    └─ output  
```

### Planification et organisation des tâches
- Rédiger l'étude prélimaire
- Implémentation des fonctions
- Rédiger la présentation finale du projet


 

### À noter
J'ai cinq (5) jours pour présenter un projet satisfaisant, du 24/05/24 - 29/05/24.