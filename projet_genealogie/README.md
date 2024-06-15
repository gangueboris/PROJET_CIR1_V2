I y'a un problem au niveau de la fonction Person *initPerson(char *csvline), je n'arrive pas à afficher les derniers lignes.



Pour gérer le stockage de plusieurs fichiers, des millions de fichiers j'ai créer une capacity (taille fixe) et une variable size (nbre n'element actuelle).
Si la capacity est atteinte, et qu'il y'a encore des données à charger, je fait un realloc

pour la fratrie et la population j'ai designer ca afin de faire un realloc
- Faire la liste des fonctions ou j'ai alloué la mémoire, et faire un free

-- ATTENTION --
- Pour stocker les éléments dans le tableu, j'ai utiliser une fonction de hachage dans pour les récupérer,il faut que je passe par une cette fonction de hachage.

*** BUG ***
- La lecture de fonctionne pas sur les petits fichiers ??!!
- le realloc fait bugé pourquoi ?!: attention, le realloc gère déjà les free
- on parle de double free ??

To do:

- implementation fonction free (all)
- implementation fonction lié parent.
-faire un petit menu en C pour afficher:
. la population
. la fratrie
. la descendance d'une personne

il faut que j'implement une fonction de recherche dans la table de hachage

pour ajouter les personsau tableau, je dois faire un level order traversal.

--------------------------------------------------------------------------------------------------------------------------------------
** Idée pour le menu :
1. Afficher la fratrie d'une personne P
2. Afficher toute la géneration d'une personne P
3. Afficher tout les n premières personnes de la population
4. 
