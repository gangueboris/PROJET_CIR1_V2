# Projet de fin d'année CIR2022 : Cahier des charges
<ins>Auteurs </ins>
- GLACIAL Alban
- LE CORVIC Gwengann
- MEUNIER-CRIQUET Léandre

<ins>Date :</ins>
Jeudi 8 juin 2023

## Objectif

Réaliser une application de communication client-serveur permettant d'envoyer des requêtes via un site web afin de faire des recherches dans une base de données de films préalablement fournie

## Description du fonctionnement

![](schema_projet.png)

Un utilisateur formule sur un site internet une recherche dans la base de données. Cette requête est récupérée par une application JavaScript qui va l'écrire dans un fichier csv. Ce fichier texte sera alors lu par le serveur codé en C, qui va effectuer la recherche demandée et renvoyer la réponse sous la forme d'un autre fichier csv. Ce second fichier sera lu par l'application JavaScript, qui affichera sur la page internet le résultat de la recherche.

## Client

Le côté client sera composé d'un site internet codé en HTML et CSS (frontend) et d'une partie logiciel codée en JavaScript (backend). L'utilisateur pourra formuler, dans des champs de recherches, des requêtes afin de chercher des films dans une filmothèque.

La backend transformera la requête en fichier csv, puis attendra un fichier indiquant que le serveur a fini la recherche. Le site affichera alors à l'utilisateur le résultat de sa recherche.

### Fonctionnalités
L'utilisateur aura accès à une page web design composé : 
- d'une barre de recherche pour rechercher les films par réalisateur
- d'un menu déroulant pour rechercher les films par durée
- D'un premier bouton pour afficher le réalisateur ayant fait le plus de film
- D'un second bouton pour rediriger l'utilisateur vers une page classant les réalisateurs par nombre de films réalisés
- D'un dernier bouton pour fermer le serveur

Le backend JavaScript devra :
- Récupérer les informations remplies par l'utilisateur au clic d'un bouton et en faire un fichier csv
- Afficher les résultats et le temps d'éxecution de la requête sur le site internet
- Allumer le serveur au démarrage du site
- Attendre la création d'un fichier ready.txt lui indiquant que la recherche est finie
- Fermer le serveur si l'utilisateur quitte la page internet

## Serveur
Le serveur tournera dans le langage C. Au démarrage, à l'aide d'un fichier csv préalablement fourni, il devra créer diverses structures décrites plus bas, afin de faciliter la recherche dans la base de données.

Il attendra en permanence une requête de la partie client, qu'il devra lire et effectuer. Il renverra alors le résultat de l'exécution à la partie client.

### Fonctionnalités
Le serveur pourra gérer les recherches suivantes :
- Trouver tous les films d'un réalisateur
- Trouver le réalisateur avec le plus de films réalisés
- Réaliser un classement des réalisateurs par nombre de films réalisés
- Trouver tous les films d'une durée précise

<ins>Lors de ces recherches, le serveur calculera leur temps d'exécution, afin de pouvoir en informer l'utilisateur.</ins>

Il attendra en permanence à l'aide d'une boucle les requêtes de la partie client.

Il devra créer un fichier csv contenant le résultat de la recherche et un fichier texte ready.txt pour indiquer à la partie client la fin de la recherche

Il pourra également supprimer les structures créées à son démarrage à la demande du client, ou à la fermeture du site internet


## Structures

La partie client et la partie serveur utiliseront des fichiers csv pour communiquer. Ces fichiers doivent donc avoir une forme précise afin d'assurer le bon fonctionnement de l'application

- <ins>request.txt</ins> : Fichier csv contenant la requête du client.

Forme :
```txt
request;request_value
```
avec :

**request** la demande du client : chaque type de requête est représenté par un nombre.

| Valeur de request | Signification                                                   |
| ----------------- | --------------------------------------------------------------- |
| 0                 | Valeur de base de request : aucune requête du client            |
| 1                 | Rechercher les films par réalisateur                            |
| 2                 | Rechercher les films par durée                                  |
| 3                 | Afficher le réalisateur avec le plus de films réalisés          |
| 4                 | Afficher tous les réalisateurs par classement de films réalisés |
| 5                  |      Fermer le serveur                                                           |
| 6                 | Rechercher les films par categorie                               |

**request_value** ce que l'utilisateur recherche précisement

- <ins>result.txt</ins> : Fichier csv contenant le résultat de la requête (pour la recherche de films)
```txt
request
executionTime
movieName1;time1;category1
movieName2;time2;category2
movieName3;time3;category3
```
<ins>executionTime</ins> le temps d'exécution de la requête
une **chaine de caractères** représentant le nom du film
<ins>time</ins> un **float** représentant la durée du film
<ins>category</ins> une **chaine de caractères** représentant la catégorie du film

OU

pour la recherche du premier realisateur
```txt
request
executionTime
realisator1;moviesNbr1
movieName1;time1;category1
movieName2;time2;category2
movieName3;time3;category3
```

OU 

pour le classement de realisateur
```txt
request
executionTime
realisator1;moviesNbr1
realisator2;moviesNbr2
...
```
avec les realisateurs dans l'ordre

<ins>realisator</ins> Le nom du réalisateur
<ins>moviesNbr</ins> le nombre de films du réalisateur

Si on reçoit une requete illisible pour le serveur :
```text
error
```

On aura également <ins>ready.txt</ins> : Un fichier texte vide permettant au client de savoir quand il peut lire le fichier result.txt

<ins> Pour le serveur :</ins>
- Les films seront représentés par leur **nom**, **réalisateur**, **catégorie** et **durée**
- Les réalisateurs seront représentés par leur **nom**,leur **nombre de films réalisés** et les **films** qu'ils ont réalisés


## Distribution des rôles
**Léandre MEUNIER-CRIQUET :** fonctions de créations, gestion de fichiers textes
**Alban GLACIAL :** fonctions de recherches et de destruction
**Gwengann LE CORVIC :** Partie Client

## Planning

| Séance         | Léandre                        | Alban                    | Gwengann            |
| -------------- | ------------------------------ | ------------------------ | ------------------- |
| Vendredi Matin | Fonctions de création          | Fonctions de recherche   | Site Internet       |
| Vendredi aprem | Fonctions de création          | Fonctions de recherche   | Site Internet       |
| Lundi Matin    | création, gestion des fichiers | Fonctions de destruction | Finition du site    |
| Lundi aprem    | Gestion des fichiers           | JS                       | JS                  |
| Mardi Matin    | Gestion des fichiers, JS       | JS                       | JS                  |
| Mardi aprem    | Test finaux                    | Test finaux              | Test finaux         |
| Merecredi      | Bonus, Tests finaux            | Bonus, Tests finaux      | Bonus, Tests finaux |

## Annexe : Précision sur les fonctions et les types de données utilisées

### JS
#### Données
- **string** <ins>requestedRealisator</ins> -> Le réalisateur demandé
- **number** <ins>requestedTime</ins> -> La durée demandée
- **bool** <ins>requestedFirst</ins> -> Si l'utilisateur demande le réalisateur avec le plus de films
- **bool** <ins>requestedRank</ins> -> Si l'utilisateur a demandé le classement des réalisateurs
- **number** <ins>executionTime</ins> -> Le temps d'exécution
- **FILE** <ins>resultFile</ins> -> Le fichier result.txt
- **FILE** <ins>requestFile</ins> -> Le fichier request.txt
- **bool** <ins>isReady</ins> -> Si le fichier ready.txt existe
- **bool** <ins>requestedClosing</ins> -> Si on veut fermer le serveur

#### Fonctions
- <ins>getRequest()</ins> -> Récupère dans les input requestedRealisator, requestedTime, requestedFirst, requestedRank, requestedClosing, puis appelle createRequest dans requestFile
- <ins>createRequest()</ins> ->Crée un fichier texte request.txt selon les valeurs des input HTML
- <ins>printOnWebsite()</ins> -> Lit le fichier result.txt et affiches son contenu sur la page HTML
- <ins>startServer()</ins> -> Lance le serveur C

### C

#### Dépendaces :
- La bibliothèque **time.h**
- La bibliothèque **stdio.h**
- La bibliothèque **stdlib.h**
- La bibliothèque **string.h**

#### Structures :

- **Film :**
```C
struct Film{
	char * name;
	char * realisator;
	float time; // en minutes
	char * category;
};
```
- **Réalisateur :**
```C
struct Realisator{
	char * name;
	int nbrMovies;
	Film ** movies;
}
```
- **Arbre construit selon le réalisateur :**
```C
struct Node_realisator{
	char character;
	int isName;
	Realisator * associateRealisator; //Tous les films de l'auteur
	Node_realisator ** childs;
	int childsNumber;
};
```
- **Tableau selon la durée :**
```C
Film_List ** byDuration;
```
Tableau contenant autant de cases mémoires que de durees possibles, avec un maximum predefini.
- **Tableau de classement par nombre de films :**
```C
Realisator ** byMoviesNumber;
```
Tableau trié par ordre décroissant selon le nombre de films du réalisateur

#### Données
- **Node_realisator \*** <ins>moviesByRealisator</ins> -> L'arbre de recherche des films par réalisateur
- des tableaux <ins>time_array</ins> et <ins>byMoviesNumber</ins>
- **int** <ins>isRunning</ins> -> Indique que le serveur tourne
- **FILE \*** <ins>requestFile</ins> -> La dernière requête récupérée

#### Fonctions
<ins>Création de la filmothèque</ins>

*Ces fonctions seront appelées au lancement du fichier C, lui-même lancé à l'ouverte du site internet. Ils liront un fichier csv contenant toutes les données sur les films*

- **Film \*** <ins>createMovie</ins>(**char \*** movieName, **char \*** realisatorName , **char \*** categoryName, float duration) -> Initialise un film et le renvoie
- **Realisator \*** <ins>createRealisator</ins>(**char \*** realisatorName, **int** nbrMovies) -> Initialise un réalisateur et le renvoie
- **Node_realisator \*** <ins>createRealisatorTree</ins>(**char \*** nom_fichier_csv) -> Crée un arbre où les films sont rangés selon leur réalisateur, permettant de rechercher le plus vite possible des films selon ce dernier.
- **Realisator \*\*** <ins>createByMoviesNumber</ins>(**char \*** nom_fichier_csv) -> Crée un tableau où les réalisateurs sont triés en fonction du nombre de films réalisés
- **Film \*\*\*** <ins>timeArray</ins>(**char \*** nom_fichier_csv) -> Crée des tableaux regroupant les films avec la même durée, puis range ces tableaux dans un tableau général, selon la durée des films

<ins>Suppression de la filmothèque</ins>

*Ces fonctions seront appelées à la fermeture du serveur*

- **void** <ins>freeRealisatorTree</ins>(**Node_realisator \*** realisatorTree) -> Supprimes l'arbre créée par createRealisatorTree
- **void** <ins>freeByMoviesNumber</ins>(**Realisator \*\*** byMoviesNumber) -> Supprimes le tableau créée par createByMoviesNumber
- **void** <ins>freeTimeArray</ins>(**Film \**\*\*** timeArray) -> Supprime le tableau créée par timeArray
 
<ins>Fonctions de recherche</ins>

*Pour chacune des fonctions de recherche, on lancera au début de celle-ci la fonction clock() de la bibliothèque time.h, puis une seconde fois à la fin de la fonction, afin de savoir le temps d'exécution de la requête. On écrira ce résultat dans un fichier result.txt*

- **Film_List \*** <ins>moviesByTime</ins>(**Film_List \*** byDuration, **int** duration) -> Recherche les films par durée. Pour cela, on accède au tableau time_array avec comme index *timeAsked - minTime*
*Exemple* : Si on veut accéder aux films de 125 minutes, et que les films les plus courts sont de 120 minutes, on sait que les films recherchés seront en 6ème dans time_array, soit à l'index 5.
- **Film_List \*** <ins>moviesByRealisator</ins>(**Node_realisator \*** root, **char \*** requestedRealisator ) -> Cherche tous les films d'un réalisateur en parcourant un arbre selon l'algorithme avancée trie
- **Realisator \***  <ins>topRealisator</ins>(**byMovieNumber \*** byMoviesNumber) -> Renvoie le premier élément de byMoviesNumber, qui correspond au réalisateur avec le plus de film

<ins>Fonctions de gestions des fichiers textes</ins>

*On listera ici toutes les fonctions gérant les fichiers textes permettant au client et au serveur de communiquer*

- **void** <ins>readRequest</ins>(**FILE \*** requestFile, **Node_Realisator \*** tree, **byMovieNumber \*** byMoviesNumber,  ) -> Lit le fichier request.txt et appelle une des fonctions de recherches selon son contenu. Appellera les fonctions créant result.txt
- **void** <ins>filmResult</ins>(**Film_List \*** movies, **float** executionTime, **int** type) -> Créé un fichier result.txt contenant tous les films dans le tableau movies
- **void** <ins>realisatorResult</ins>(**Realisator \*** realisator, **float** executionTime) -> Créé un fichier result.txt contenant les informations du réalisateur en paramètre
- **void** <ins>rankResult</ins>(**byMovieNumber \*** realisators) -> Créé un fichier result.txt contenant les informations de tous les réalisateurs, dans l'ordre du tableau en paramètre

## Logs
- <ins>Lundi 12 juin : </ins>
Création d'une fonction readCSV, qui lit une seule fois le fichier csv, créant des structures qu'elle envoit aux fonctions créant les structures de recherhce

Changement de structure de byMovieNumber de tableau à lcaa

- <ins>Mardi  13 juin : </ins>

Changement de Films dans la struct Realisator, qui passe d'un tableau à une liste chainee
Retrait des valeurs minTime et maxTime
Changement de type de moviesByRealisator
Changement de parametre de filmResult
Changement de parametre de realisatorResult
Precision sur la forme de result.txt
Cgt de parametre sur topRealisator
Cgt param rankResult
Refonte time_array
Cgt param moviesByTime