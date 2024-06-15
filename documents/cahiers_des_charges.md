# Projet de fin d'année CIR2024 : Cahier des charges
# Groupes 4

<ins>Auteurs </ins>
- GANGUE Saan Boris
- CORVAISIER Antoine
- CORNIC Maël

## Objectif
Génération d'arbres généalogiques à partir de données existantes

## Architecture globale du système
![](architecture.png)

## Architecture du système Site local

### Affichage des données contenant les informations généalogiques sur des personnes
-  Utiliser HTML, CSS et JS
-  Le noyau C génère les fichiers HTML : cette génération doit être automatique
- Le style des pages HTML, on utilise du CSS 
NB:  Site statique (généré 1 seule fois) et local

## Fonctionalités
- Lecture d'un fichier CSV avec le noyau C
- Possibilité d'effectuer des requêtes/traitements avec le menu ou via des scripts linux (au choix)
- Export de fichiers en HTML
- Visualisation en local du résultat via un 

## Description du projet

A faire plustard

## L'export HTML est géré par le noyau C

A faire plustard

## Création de menus/scripts linux

A faire plustard


Dépendances:
- strtok: librairie C qui permet de séparer une chaine de charatères à partir d'un charactère séparateur.
- atoi: converti ASCII to integer
- strncpy: permet de copier une chaîne de caractères en veillant à ne pas dépasser la taille du buffer.
- string.h


QUESTIONS:
- es ce que dans données on peut avoir des données manquantes au de la date d'anniversaire de style '_/10/2005' ou





/*
Helper function to add ancestors to the ancestors list
void addAncestors(population pop, Person* person, ancestors* ances) {
    if (person == NULL || person->id == 0) {
        ances->ancestorsList[ances->ancestorsSize++] = pop.popDatas[hash_O(pop, 0)];
        return; // If person is null or an unknown ancestor, do nothing
    }

    // Add the current person to the ancestors list
    ances->ancestorsList[ances->ancestorsSize++] = person;

    // Reallocate memory if capacity is reached
    if (ances->ancestorsSize == ances->capacity) {
        ances->capacity *= 2;
        ances->ancestorsList = realloc(ances->ancestorsList, ances->capacity * sizeof(Person*));
        if (ances->ancestorsList == NULL) {
            fprintf(stderr, "Memory reallocation failed for ancestorsList\n");
            exit(EXIT_FAILURE);
        }
    }

    // Recursively add the father and mother
    addAncestors(pop, person->p_father, ances);
    addAncestors(pop, person->p_mother, ances);
}
*/
/*
ancestors ancestorsPersons(population pop, Person* p) {
    // Initialize the ancestors structure
    ancestors ances;
    ances.ancestorsSize = 0;
    ances.capacity = pop.capacity; // Initial capacity
    ances.ancestorsList = calloc(ances.capacity, sizeof(Person*));
    if (ances.ancestorsList == NULL) {
        fprintf(stderr, "Memory allocation failed for ancestorsList\n");
        exit(EXIT_FAILURE);
    }

    // Start adding ancestors from the given person
    addAncestors(pop, p, &ances);

    return ances;
}
*/